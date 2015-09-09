//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//bool_op_poliedro3d.cc

#include "bool_op_poliedro3d.h"
#include <CGAL/Gmpz.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Quotient.h>
#include <CGAL/Nef_polyhedron_3.h>
#include "Poliedro3d.h"
#include <CGAL/cartesian_homogeneous_conversion.h>
#include <CGAL/Cartesian_converter.h>
#include "MapPoligonos.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"

typedef CGAL::Gmpz RT;
typedef CGAL::Homogeneous<RT> KernelHomog;
typedef CGAL::Polyhedron_3<KernelHomog> Polyhedron;
typedef CGAL::Nef_polyhedron_3<KernelHomog> Nef_pol3;
typedef CGAL::Cartesian<RT> KernelCart;
typedef Nef_pol3::Point_3 NPPoint;

inline NPPoint Pos3d_to_Point(const Pos3d &p3d)
  { return NPPoint(p3d.hx(),p3d.hy(),p3d.hz(),p3d.hw()); }

class Pos3d2Point
  {
  public:
   NPPoint operator()(const Pos3d &p) const
     { return Pos3d_to_Point(p); }
  };

struct GmpzConverter
  {
    GEOM_FT operator()(const CGAL::Quotient<RT> &g) const
      {
        return to_double(g);
      }
  };


CGPoint_3 Point_to_Pos3d(const Polyhedron::Vertex::Point &np)
  {
    
//     CGAL::Point_3< CGAL::Cartesian<CGAL::Quotient<RT> > > Q= homogeneous_to_quotient_cartesian(np);
//     CGAL::Cartesian_converter<CGAL::Cartesian<CGAL::Quotient<RT> >,GEOMKernel,GmpzConverter> conv;
    return CGPoint_3(to_double(np.hx()),to_double(np.hy()),to_double(np.hz()),to_double(np.hw()));
  }

class Point2Pos3d
  {
  public:
    CGPoint_3 operator()(const Polyhedron::Vertex::Point &np) const
     { return Point_to_Pos3d(np); }
  };


Nef_pol3 Poliedro3d_to_Nef_3(const CGPoliedro_3 &pol3)
  {
    typedef Polyhedron::HalfedgeDS HalfedgeDS;
    Polyhedron tmp;
    if(pol3.is_closed())
      {
        Build_tdest_polyhedron<CGPoliedro_3,HalfedgeDS,Pos3d2Point> bpoli(pol3);
        tmp.delegate(bpoli);
      }
    else
      std::cerr << "El poliedro no es cerrado." << std::endl;
    return Nef_pol3(tmp);
  }

CGPoliedro_3 Nef_3_to_Poliedro3d(Nef_pol3 &np)
  {
    typedef CGPoliedro_3::HalfedgeDS HalfedgeDS;
    CGPoliedro_3 retval;
    if(np.is_simple())
      {
        Polyhedron tmp;
        np.convert_to_Polyhedron(tmp);
        Build_tdest_polyhedron<Polyhedron,HalfedgeDS,Point2Pos3d> bpoli(tmp);
        retval.delegate(bpoli);
      }
    else
      std::cerr << "El poliedro no es simple." << std::endl;
    return retval;
  }

Poliedro3d Union(const Poliedro3d &a,const Poliedro3d &b)
  {
    Nef_pol3 nfa= Poliedro3d_to_Nef_3(a.cgpoliedro);
    Nef_pol3 nfb= Poliedro3d_to_Nef_3(b.cgpoliedro);
    Nef_pol3 nfu= nfa+nfb;
    return Poliedro3d(Nef_3_to_Poliedro3d(nfu));
  }
Poliedro3d Interseccion(const Poliedro3d &a,const Poliedro3d &b)
  {
    Nef_pol3 nfa= Poliedro3d_to_Nef_3(a.cgpoliedro);
    Nef_pol3 nfb= Poliedro3d_to_Nef_3(b.cgpoliedro);
    Nef_pol3 nfi= nfa*nfb;
    return Poliedro3d(Nef_3_to_Poliedro3d(nfi));
  }
Poliedro3d Diferencia(const Poliedro3d &a,const Poliedro3d &b)
  {
    Nef_pol3 nfa= Poliedro3d_to_Nef_3(a.cgpoliedro);
    Nef_pol3 nfb= Poliedro3d_to_Nef_3(b.cgpoliedro);
    Nef_pol3 nfd= nfa-nfb;
    return Poliedro3d(Nef_3_to_Poliedro3d(nfd));
  }
