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
//SlidingVector2d.cc

#include "SlidingVector2d.h"





//! @brief Constructor.
SlidingVector2d::SlidingVector2d(const Pos2d &o,const Pos2d &p)
  : Vector2d(p-o), org(o) {}

//! @brief Moment of a sliding vector with respect to a point.
GEOM_FT SlidingVector2d::getMoment(const Pos2d &o) const
  {
    GEOM_FT retval(0.0);
    if(!this->Nulo()) //Si ESTE vector no es nulo.
      {
        Vector2d r= org - o;
        if(!r.Nulo()) //Si r no es nulo.
          if(!paralelos(r,*this)) //Si r y ESTE no son paralelos
            retval= r.x()*this->y()-this->x()*r.y();
      }
    return retval;
  }

GEOM_FT inverso(const GEOM_FT &p)
  { return GEOM_FT(1.0/p); }

SlidingVector2d operator/(const SlidingVector2d &m,const GEOM_FT &p)
  { return m*inverso(p); }

SlidingVector2d operator-(const SlidingVector2d &v)
  {
    SlidingVector2d neg(v);
    neg.Neg();
    return neg;
  }

