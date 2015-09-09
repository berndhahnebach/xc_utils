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
//GmGrupo2d.cc

#include "GmGrupo2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include <plotter.h>
#include <iostream>

#include "xc_utils/src/geom/pos_vec/Dir2d.h"
#include "xc_utils/src/geom/d0/Punto2d.h"
#include "xc_utils/src/geom/d1/Recta2d.h"
#include "xc_utils/src/geom/d1/SemiRecta2d.h"
#include "xc_utils/src/geom/d1/Segmento2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/Triangulo2d.h"
#include "xc_utils/src/geom/trf/Trf2d.h"

GEOM_FT GmGrupo2d::inercia(const Recta2d &e) const
//Devuelve el momento de inercia respecto a la recta e
  {
    if(objetos.empty()) return 0.0;
    if(!igual_dimension())
      {
        cerr << "¡Ojo!, GmGrupo2d::inercia: los objetos del grupo tienen distintas dimensiones." << endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->I(e));
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->I(e);
    return retval;
  }

GEOM_FT GmGrupo2d::Ix(void) const
//Momento de inercia respecto al CDG en ejes locales.
  { return inercia(Recta2d(Cdg(),Dir2d(1.0,0.0))); }
GEOM_FT GmGrupo2d::Iy(void) const
//Momento de inercia respecto al CDG en ejes locales.
  { return inercia(Recta2d(Cdg(),Dir2d(0.0,1.0))); }
GEOM_FT GmGrupo2d::Pxy(void) const
  {
    cerr << "GmGrupo2d::Pxy no implementada, se devuelve 0." << endl;
    return 0.0;
  }

bool GmGrupo2d::procesa_comando(CmdStatus &status)
  {
    //cerr << "(GmGrupo2d) Procesando comando: " << cmd << endl;
    if(status.Cmd() == "punto2d")
      {
        Punto2d p;
        p.LeeCmd(status);
        push_back(p);
        return true;
      }
    else if(status.Cmd() == "segmento2d")
      {
        Segmento2d s;
        s.LeeCmd(status);
        push_back(s);
        return true;
      }
    else if(status.Cmd() == "semirrecta2d")
      {
        SemiRecta2d sr;
        sr.LeeCmd(status);
        push_back(sr);
        return true;
      }
    else if(status.Cmd() == "recta2d")
      {
        Recta2d r;
        r.LeeCmd(status);
        push_back(r);
        return true;
      }
    else if(status.Cmd() == "triangulo2d")
      {
        Triangulo2d t;
        t.LeeCmd(status);
        push_back(t);
        return true;
      }
    else
      return GmGrupo<GeomObj2d>::procesa_comando(status);
  }

Pos2d GmGrupo2d::Cdg(void) const
  {
    if(objetos.empty()) return Pos2d();
    if(!igual_dimension())
      {
        cerr << "¡Ojo!, GmGrupo2d::Cdg: los objetos del grupo tienen distintas dimensiones." << endl;
      }
    register pdeque_geom_obj::const_iterator i(objetos.begin());
    GEOM_FT area_i= (*i)->AreaCdg();
    Vector2d num= (*i)->Cdg().VectorPos()*area_i;
    GEOM_FT denom(area_i);
    i++;
    for(;i!=objetos.end();i++)
      {
        area_i= (*i)->AreaCdg();
        num= num + (*i)->Cdg().VectorPos()*area_i;
        denom+= area_i;
      }
    num= num*(1/denom);
    return Origen2d+num;
  }

//! @brief Aplica a los puntos la transformación que se pasa como parámetro.
void GmGrupo2d::Transforma(const Trf2d &trf2d)
  {
    for(pdeque_geom_obj::iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Transforma(trf2d);
  }

void GmGrupo2d::SalvaCmd(std::ostream &os,const std::string &indent) const
  {
    const std::string str_indent= indent + "  ";
    os << indent << "\\lista_geom" << endl;
    os << str_indent << '{' << endl;
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->SalvaCmd(os,str_indent+"  ");
    os << str_indent << "}\\c{fin lista_geom}" << endl;
  }
void GmGrupo2d::Print(std::ostream &stream) const
  {
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Print(stream);
  }
void GmGrupo2d::Plot(Plotter &plotter) const
  {
    for(register pdeque_geom_obj::const_iterator i= objetos.begin();i!=objetos.end();i++)
      (*i)->Plot(plotter);
  }

