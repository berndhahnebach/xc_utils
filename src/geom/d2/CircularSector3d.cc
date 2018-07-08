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
//CircularSector3d.cc

#include "CircularSector3d.h"
#include "../cgal_types.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_basic/src/util/matem.h"
#include <plotter.h>

#include "xc_utils/src/geom/pos_vec/MatrizPos2d.h"
#include "xc_utils/src/geom/pos_vec/MatrizPos3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "boost/progress.hpp"


//! @brief Constructor de copia
CircularSector3d::CircularSector3d(const CircularSector3d &other)
  : D2to3d(other), sect_circ(other.sect_circ) {}

//! @brief Operador asignación.
CircularSector3d &CircularSector3d::operator=(const CircularSector3d &p)
  {
    D2to3d::operator=(p);
    sect_circ= p.sect_circ;
    return *this;
  }

//! @brief Constructor virtual.
D2to3d *CircularSector3d::clon(void) const
  { return new CircularSector3d(*this); }

//! @brief Constructor.
CircularSector3d::CircularSector3d(const Pos3d centro,const GEOM_FT &rad,const double &th1,const double &th2)
  : D2to3d(centro), sect_circ()
  { sect_circ= CircularSector2d(Circle2d(to_2d(centro),rad),th1,th2); }

//! @brief Constructor.
CircularSector3d::CircularSector3d(const GEOM_FT &rad2,const Pos3d &centro,const double &th1,const double &th2)
  : D2to3d(centro), sect_circ()
  { sect_circ= CircularSector2d(Circle2d(rad2,to_2d(centro)),th1,th2); }

CircularSector3d::CircularSector3d(const Pos3d &c,const double &r,const Vector3d &n,const Vector3d &Xaxis,const double &th1,const double &th2)
  : D2to3d(c,n,Xaxis), sect_circ()
  { sect_circ= CircularSector2d(Circle2d(to_2d(c),r),th1,th2); }

 
//! @brief Constructor; circular sector defined by three points p1->p2->p3.
CircularSector3d::CircularSector3d(const Pos3d &p1,const Pos3d &p2,const Pos3d &p3)
  : D2to3d(p1,p2,p3), sect_circ()
  {
    const Pos2d pA= to_2d(p1);
    const Pos2d pB= to_2d(p2);
    const Pos2d pC= to_2d(p3);
    const Circle2d C(pA,pB,pC);
    const Pos2d po= C.Centro();
    //Adjust the center and the coordinate system axis.
    ThreePoints(to_3d(po),p1,p3);
    const Pos2d pa= to_2d(p1);
    const Pos2d pb= to_2d(p2);
    const Pos2d pc= to_2d(p3);
    sect_circ= CircularSector2dThreepoints(pa,pb,pc);
  }

//! @brief Return el centro del círculo.
Pos3d CircularSector3d::Centro(void) const
  { return to_3d(sect_circ.Centro()); }

//! @brief Return the point inicial del arco.
Pos3d CircularSector3d::PInic(void) const
  { return to_3d(sect_circ.PInic()); }

//! @brief Return the point final del arco.
Pos3d CircularSector3d::PFin(void) const
  { return to_3d(sect_circ.PFin()); }

//! @brief Return the point medio del arco.
Pos3d CircularSector3d::PMed(void) const
  { return to_3d(sect_circ.PMed()); }

Pos3d CircularSector3d::getCenterOfMass(void) const
  { return Centro(); }

//! @brief Return the position of the arc centroid.
Pos3d CircularSector3d::ArcCentroid(void) const
  { return to_3d(sect_circ.ArcCentroid()); }

GEOM_FT CircularSector3d::getSquaredRadius(void) const
  { return sect_circ.getSquaredRadius(); }
GEOM_FT CircularSector3d::getRadius(void) const
  { return sect_circ.getRadius(); }
GEOM_FT CircularSector3d::Diametro(void) const
  { return sect_circ.Diametro(); }

double CircularSector3d::getAngle(const Pos3d &p) const
  { return sect_circ.getAngle(to_2d(p)); }

//! @brief Returns the parameter of the point in the arc (distance to the arc's first point measured over the arc)
double CircularSector3d::getLambda(const Pos3d &p) const
  { return sect_circ.getLambda(to_2d(p)); }

GEOM_FT CircularSector3d::Ix(void) const
  { return sect_circ.Ix(); }
GEOM_FT CircularSector3d::Iy(void) const
  { return sect_circ.Iy(); }
GEOM_FT CircularSector3d::Pxy(void) const
  { return sect_circ.Pxy(); }
GEOM_FT CircularSector3d::Iz(void) const
  { return sect_circ.Iz(); }

GEOM_FT CircularSector3d::GetMax(unsigned short int i) const
  {
    std::cerr << "CircularSector3d::GetMax(i), not implemented." << std::endl;
    return 1;
  }
GEOM_FT CircularSector3d::GetMin(unsigned short int i) const
  {
    std::cerr << "CircularSector3d::GetMin(i), not implemented." << std::endl;
    return -1;
  }

//! @brief Return true if the point is in the plane.
bool CircularSector3d::In(const Pos3d &p, const double &tol) const
  {
    if(getPlane().In(p,tol))
      return sect_circ.In(to_2d(p),tol);
    else
      return false;
  }

//! @brief Return n points equally spaced over the circle arc.
MatrizPos3d CircularSector3d::getArcPoints(const size_t &n) const
  {
    MatrizPos3d retval= to_3d(sect_circ.getArcPoints(n));
    return retval;
  }

void CircularSector3d::Print(std::ostream &os) const
  { os << sect_circ; }

bool operator ==(const CircularSector3d &a,const CircularSector3d &b)
  {
    if((const D2to3d &) a ==(const D2to3d &) b)  
      return ( a.sect_circ == b.sect_circ );
    else
      return false;
  }
