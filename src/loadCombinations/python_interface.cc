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
//python_interface.cxx

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/docstring_options.hpp>
#include "xc_utils/src/loadCombinations/coefs/GammaF.h"
#include "xc_utils/src/loadCombinations/coefs/CoefsPsi.h"
#include "xc_utils/src/loadCombinations/acciones/Accion.h"
#include "xc_utils/src/loadCombinations/acciones/ListaVRAccion.h"
#include "xc_utils/src/loadCombinations/acciones/FamiliaAcciones.h"
#include "xc_utils/src/loadCombinations/acciones/AccionesClasificadas.h"
#include "xc_utils/src/loadCombinations/load_combinations/LoadCombinationVector.h"
#include "xc_utils/src/loadCombinations/load_combinations/LoadCombinations.h"
#include "xc_utils/src/loadCombinations/load_combinations/LoadCombinationGenerator.h"

BOOST_PYTHON_MODULE(loadCombinations)
  {
    using namespace boost::python;
    using namespace cmb_acc;
    docstring_options doc_options;


    class_<std::vector<double> >("StdVectorDouble")
        .def(vector_indexing_suite<std::vector<double> >() );

#include "coefs/python_interface.tcc"
#include "acciones/python_interface.tcc"
#include "load_combinations/python_interface.tcc"
  }

