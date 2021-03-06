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
//RightPrism3d.h

#ifndef RIGHTPRISM3D_H
#define RIGHTPRISM3D_H

#include "Prism3d.h"
#include "../SolidExtruPolygon3d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"


//! @ingroup GEOM
//
//! @brief Right prism.
template<class PG>
class RightPrism3d : public Prism3d
  {
    SolidExtruPolygon3d<PG> extru;
  protected:
    inline unsigned int get_num_vertices_plgno(void) const
      { return extru.GetNumVertices(); }
  public:
    RightPrism3d(void) {}
    RightPrism3d(const PG &secc,const GEOM_FT &lng): Prism3d(), extru(secc,lng) {}
    RightPrism3d(const RightPrism3d<PG> &se): Prism3d(se), extru(se.extru) {}
    RightPrism3d<PG> &operator=(const RightPrism3d<PG> &se)
      {
	Prism3d::operator=(se);
	extru=se.extru;
        return *this;
      }
    inline virtual GeomObj *clon(void) const
      { return new RightPrism3d<PG>(*this); }
    inline void Offset(const GEOM_FT &offset)
      { extru.Offset(offset); }
    inline RightPrism3d<PG> GetOffset(const GEOM_FT &offset) const
      {
        RightPrism3d<PG> retval(*this);
        retval.Offset(offset);
        return retval;
      }
/*     inline virtual Polyhedron::v_ind_vertices IndVerticesFaceta(unsigned int faceta) const */
/*       { return extru.IndVerticesFaceta(faceta); } */
    const PG &Section(void) const
      { return extru.Section(); }
    PG &Section(void)
      { return extru.Section(); }
    //! @brief Return the object length.
    inline GEOM_FT getLength(void) const
      { return extru.getLength(); }
    //! @brief Return the object area.
    inline GEOM_FT getArea(void) const
      { return extru.getArea(); }
    //! @brief Return the object volume.
    inline GEOM_FT getVolume(void) const
      { return extru.getVolume(); }
    inline virtual GEOM_FT Ix(void) const
      { return extru.Ix(); }
    inline virtual GEOM_FT Iy(void) const
      { return extru.Iy(); }
    inline virtual GEOM_FT Iz(void) const
      { return extru.Iz(); }
    inline virtual GEOM_FT GetMax(unsigned short int i) const
    //Return el valor maximo de la coordenada i.
      { return extru.GetMax(i); }
    inline virtual GEOM_FT GetMin(unsigned short int i) const
    //Return el valor minimo de la coordenada i.
      { return extru.GetMin(i); }
    inline virtual unsigned int GetNumVertices(void) const
      { return extru.GetNumVertices(); }
    inline virtual unsigned int GetNumVerticesFaceta(unsigned int faceta) const
      { return extru.GetNumVerticesFaceta(faceta); }
    inline virtual unsigned int getNumEdges(void) const
      { return extru.getNumEdges(); }
    inline virtual unsigned int GetNumFacetas(void) const
      { return extru.GetNumFacetas(); }
    inline Pos3d Vertice(unsigned int i) const
      { return extru.Vertice(i); } 
/*     virtual v_ind_vertices IndVerticesArista(unsigned int arista) const */
/*       { return extru.IndVerticesArista(arista); } */
    BND3d Bnd(void) const
    //Return la extension del objeto.
      { return extru.Bnd(); }
    inline FT_matrix I(void) const
      { return extru.I(); }
    inline Pos3d getCenterOfMass(void) const
      { return extru.getCenterOfMass(); }
    inline Pos3d getCenterOfMassOfTop(void) const
      { return extru.getCenterOfMassOfTop(); }
    inline Pos3d getCenterOfMassOfBottom(void) const
      { return extru.getCenterOfMassOfBottom(); }
    inline Pos3d getCenterOfMassOfFacet(unsigned int faceta) const
      { return this->Faceta(faceta).getCenterOfMass(); }
    
  };

#endif
