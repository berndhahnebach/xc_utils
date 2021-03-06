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
//D2to3d.cc

#include "D2to3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d3/GeomGroup3d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"
#include "xc_utils/src/geom/lists/auxiliary.h"
#include "xc_utils/src/geom/pos_vec/Pos2dArray.h"
#include "xc_utils/src/geom/pos_vec/Pos3dArray.h"



//! @brief Constructor.
D2to3d::D2to3d(void): Surface3d(), ref() {}

//! @brief Constructor.
D2to3d::D2to3d(const Pos3d &o,const Pos3d &p,const Pos3d &q)
  : Surface3d(), ref(o,p,q)
  {}

//! @brief Constructor.
D2to3d::D2to3d(const Pos3d &o,const Vector3d &n,const Vector3d &i)
  : Surface3d(), ref(o,o+i,o+(n^i))
  {
    const Vector3d j= n^i;
    if(Abs2(j)>1e-3)
      std::cerr << getClassName() << "::" << __FUNCTION__
	        << "; error, vectors n= " << n
                << " and i= " << i << " are parallel." << std::endl;
  }

//! @brief Constructor.
D2to3d::D2to3d(const Pos3d &o)
  : Surface3d(), ref(o)
  {}

//! @brief Constructor.
D2to3d::D2to3d(const D2to3d &other)
  : Surface3d(other), ref(other.ref) {}

//! @brief Operador asignación.
D2to3d &D2to3d::operator=(const D2to3d &other) 
  {
    Surface3d::operator=(other);
    ref= other.ref;
    return *this;
  }


Pos3d D2to3d::to_3d(const Pos2d &p2d) const
  { return ref.GetPosGlobal(p2d); }

Segment3d D2to3d::to_3d(const Segment2d &sg2d) const
  { return Segment3d(to_3d(sg2d.Origen()),to_3d(sg2d.Destino())); }

Pos3dArray D2to3d::to_3d(const Pos2dArray &p2d) const
  {
    const size_t n_rows= p2d.getNumberOfRows();
    const size_t n_columns= p2d.getNumberOfColumns();
    Pos3dArray retval(n_rows,n_columns);
    for(size_t i=1;i<=n_rows;i++)
      for(size_t j=1;j<=n_columns;j++)
        retval(i,j)= to_3d(p2d(i,j));
    return retval;
  }


Pos2d D2to3d::to_2d(const Pos3d &p3d) const
  { return ref.GetPosLocal(p3d); }
void D2to3d::ThreePoints(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  {
    ref= Ref2d3d(p1,p2,p3);
  }
Plane D2to3d::getPlane(void) const
  { return ref.getXYPlane(); }

bool operator ==(const D2to3d &a,const D2to3d &b)
  { return ( a.ref == b.ref ); }

void D2to3d::Print(std::ostream &os) const
  { os << "Ref2d3d: " << ref << std::endl; }
