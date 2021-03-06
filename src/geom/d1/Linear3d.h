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
//Linear3d.h

#ifndef LINEAR3D_H
#define LINEAR3D_H

#include "../d3/GeomObj3d.h"


//! @ingroup GEOM
//
//! @brief Base class for the objects involving a single dimension
//! in a three-dimensional space.
class Linear3d : public GeomObj3d
  {
  public:
    Linear3d(void): GeomObj3d(){}
    ~Linear3d(void) {}
    inline virtual unsigned short int Dimension(void) const
      { return 1; }
    //! @brief Return the object area.
    virtual GEOM_FT getArea(void) const
      { return 0.0; }
    //! @brief Return the volume of the object.
    virtual GEOM_FT getVolume(void) const
      { return 0.0; }
    //@brief Return true if the points is on sobre la Linea.
    virtual bool In(const Pos3d &p, const double &tol= 0.0) const= 0;
    //Return the intersection of the line with the plane
    // defined by the equation coord_i= d.
/*     virtual list_Pos3d Int(unsigned short int i, const double &d) const= 0; */
/*     inline list_Pos3d intx(const double &x) */
/*     //Return the intersection of the line with a plane x=cte. */
/*       { return Int(1,x); } */
/*     inline list_Pos3d inty(const double &y) */
/*     //Return the intersection of the line with a plane y=cte. */
/*       { return Int(2,y); } */
/*     inline list_Pos3d intz(const double &z) */
/*     //Return the intersection of the line with a plane z=cte. */
/*       { return Int(3,z); } */
  };
#endif



