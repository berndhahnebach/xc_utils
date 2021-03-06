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
//SlidingVector3d.cc

#include "SlidingVector3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"





//! @brief Constructor.
SlidingVector3d::SlidingVector3d(const Pos3d &o,const Vector3d &v)
  : Vector3d(v), org(o) {}

//! @brief Constructor.
SlidingVector3d::SlidingVector3d(const Pos3d &o,const Pos3d &p)
  : Vector3d(p-o), org(o) {}

//! @brief Moment of a sliding vector with respect to an axis.
//! Is the moment with respect to an axis point
//! projected onto the axis.
GEOM_FT SlidingVector3d::getMoment(const Line3d &e) const
  { return dot(getMoment(e.Point()),e.VDir().Normalizado()); }

//! @brief Moment of a sliding vector with respect to a point.
SlidingVector3d SlidingVector3d::getMoment(const Pos3d &o) const
  {
    SlidingVector3d retval(o);
    if(!Nulo()) //Si ESTE vector no es nulo.
      {
        Vector3d r= org - o;
        if(!r.Nulo()) //Si r no es nulo.
          if(!paralelos(r,*this)) //Si r y ESTE no son paralelos
            retval= SlidingVector3d(o,r^*this);
      }
    return retval;
  }

const Pos3d &SlidingVector3d::getOrg(void) const
  { return org; }

const Pos3d SlidingVector3d::getDest(void) const
  { return org+(const Vector3d &)(*this); }

const Vector3d &SlidingVector3d::getVector(void) const
  { return *this; }

SlidingVector3d operator-(const SlidingVector3d &v)
  {
    SlidingVector3d neg(v);
    neg.Neg();
    return neg;
  }
SlidingVector3d  &SlidingVector3d::operator*=(const GEOM_FT &p)
  {
    (*this)= SlidingVector3d(getOrg(),getVector()*p);
    return *this;
  }

SlidingVector3d operator*(const SlidingVector3d &m,const GEOM_FT &p)
  { return SlidingVector3d(m.getOrg(),m.getVector()*p); }

SlidingVector3d operator*(const GEOM_FT &p,const SlidingVector3d &m)
  { return m*p; }

SlidingVector3d operator/(const SlidingVector3d &m,const GEOM_FT &p)
  { return m*(1/p); }

std::ostream &operator<<(std::ostream &os,const SlidingVector3d &v)
  {
    os << (const Vector3d &) v;
    os << " (O=" << v.org << ')';
    return os;
  }
