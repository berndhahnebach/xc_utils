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
//VDesliz3d.cc

#include "VDesliz3d.h"
#include "xc_utils/src/geom/d1/Recta3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
VDesliz3d::VDesliz3d(const Pos3d &o,const Vector3d &v)
  : Vector3d(v), org(o) {}

//! @brief Constructor.
VDesliz3d::VDesliz3d(const Pos3d &o,const Pos3d &p)
  : Vector3d(p-o), org(o) {}

bool VDesliz3d::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(VDesliz3d) Procesando comando: " << cmd << std::endl;
    if(cmd == "pto_aplic")
      {
        org.LeeCmd(status);
        return true;
      }
    else if(cmd == "punto")
      {
        org= interpretaPos3d(status.GetString());
        return true;
      }
    else
      return Vector3d::procesa_comando(status);
  }

//! @brief Momento de un vector deslizante respecto a un eje.
//! Es el momento respecto a un punto
//! del eje proyectado sobre el eje.
GEOM_FT VDesliz3d::getMomento(const Recta3d &e) const
  { return dot(getMomento(e.Punto()),e.VDir().Normalizado()); }

//! @brief Momento de un vector deslizante respecto a un punto.
VDesliz3d VDesliz3d::getMomento(const Pos3d &o) const
  {
    VDesliz3d retval(o);
    if(!Nulo()) //Si ESTE vector no es nulo.
      {
        Vector3d r= org - o;
        if(!r.Nulo()) //Si r no es nulo.
          if(!paralelos(r,*this)) //Si r y ESTE no son paralelos
            retval= VDesliz3d(o,r^*this);
      }
    return retval;
  }

const Pos3d &VDesliz3d::getOrg(void) const
  { return org; }

const Pos3d VDesliz3d::getDest(void) const
  { return org+(const Vector3d &)(*this); }

const Vector3d &VDesliz3d::getVector(void) const
  { return *this; }

VDesliz3d operator-(const VDesliz3d &v)
  {
    VDesliz3d neg(v);
    neg.Neg();
    return neg;
  }
VDesliz3d  &VDesliz3d::operator*=(const GEOM_FT &p)
  {
    (*this)= VDesliz3d(getOrg(),getVector()*p);
    return *this;
  }

VDesliz3d operator*(const VDesliz3d &m,const GEOM_FT &p)
  { return VDesliz3d(m.getOrg(),m.getVector()*p); }

VDesliz3d operator*(const GEOM_FT &p,const VDesliz3d &m)
  { return m*p; }

VDesliz3d operator/(const VDesliz3d &m,const GEOM_FT &p)
  { return m*(1/p); }

//! @brief Devuelve una propiedad del objeto.
any_const_ptr VDesliz3d::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "VDesliz3d::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod=="getOrg")
      return any_const_ptr(org);
    if(cod=="getVector")
      {
        tmp_gp_vector3d= getVector();        
        return any_const_ptr(tmp_gp_vector3d);
      }
    else if(cod=="getMomentoRespectoPunto")
      {
        const Pos3d tmp= popPos3d(cod);
        tmp_gp_vdesliz3d= getMomento(tmp);
        return any_const_ptr(tmp_gp_vdesliz3d);
      }
    else if(cod=="getMomentoRespectoEje")
      {
        const Recta3d eje= popRecta3d(cod);
        tmp_gp_dbl= getMomento(eje);
        return any_const_ptr(tmp_gp_dbl);
      }
    else
      return Vector3d::GetProp(cod);
  }

std::ostream &operator<<(std::ostream &os,const VDesliz3d &v)
  {
    os << (const Vector3d &) v;
    os << " (O=" << v.org << ')';
    return os;
  }
