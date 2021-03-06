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
//CombinationFactors.hxx
//Combination factors for an action.

#ifndef COMBINATIONFACTORS_H
#define COMBINATIONFACTORS_H

#include "xc_utils/src/kernel/CommandEntity.h"

namespace cmb_acc{

//! @ingroup CMBACC
//
//! @brief Coeficientes de simultaneidad de una acción.
class CombinationFactors: public CommandEntity
  {
  private:
    float psi_0; //!< To compute the combination value.
    float psi_1; //!< To compute the frequent value.
    float psi_2; //!< To compute the quasi-permanent value.
  public:
    //! @brief Default constructor.
    CombinationFactors(const float &p0= 1.0, const float &p1= 1.0, const float &p2= 1.0)
      : CommandEntity(),psi_0(p0), psi_1(p1), psi_2(p2) {}
    //! @brief Copy constructor
    const float &getCombinationFactor(short int r) const;
    void Print(std::ostream &os) const;
  };

 inline std::ostream &operator<<(std::ostream &os, const CombinationFactors &cf)
  {
    cf.Print(os);
    return os;
  }

} //fin namespace nmb_acc.

#endif
