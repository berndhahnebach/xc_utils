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
//Cylinder.h
//Sólido de extrusión generado por un polígono.

#ifndef SOLIDEXTRUPLGNO3D_H
#define SOLIDEXTRUPLGNO3D_H

#include "SolidExtru3d.h"
#include "xc_utils/src/geom/d2/Circle3d.h"


//! @ingroup GEOM
//
//! @brief Cylinder.
class Cylinder : public SolidExtru3d<Circle3d>
  {
  public:
    typedef SolidExtru3d<Circle3d> solid_extru_cil;
  public:
    Cylinder(void);
    Cylinder(const Circle3d &secc,const GEOM_FT &lng);
    Cylinder &operator=(const Cylinder &se);
    virtual GeomObj *clon(void) const;

    BND3d Bnd(void) const;
    FT_matrix I(void) const;
    Pos3d getCenterOfMass(void) const;
  };






#endif
