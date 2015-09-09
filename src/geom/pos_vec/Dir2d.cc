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
//Dir2d.cc

#include "Dir2d.h"
#include "Vector2d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/geom/matriz_FT.h"

Dir2d::Dir2d(const Vector2d &v)
  : cgd(v.ToCGAL()) {}
Dir2d::Dir2d(const GEOM_FT &x,const GEOM_FT &y)
  : cgd(x,y) {}
Dir2d::Dir2d(const double &ang)
  : cgd(cos(ang),sin(ang)) {}
matriz_FT Dir2d::GetMatriz(void) const
  {
    matriz_FT retval(2,1,0.0);
    retval(1)= cgd.dx(); retval(2)= cgd.dy();
    return retval;
  }
Vector2d Dir2d::GetVector(void) const
  { return Vector2d(cgd); }

std::ostream &operator<<(std::ostream &stream,const Dir2d &n)
  {
    stream << "[[" << n.dx() << "][" << n.dy() << "]]";
    return stream;
  }
