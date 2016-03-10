//----------------------------------------------------------------------------
//  programa XC; cálculo mediante el método de los elementos finitos orientado
//  a la solución de problemas estructurales.
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
//python_interface.tcc

typedef std::vector<Accion> v_accion;
class_<v_accion >("v_accion")
  .def(vector_indexing_suite<v_accion >())
 ;

class_<LoadCombinationVector, bases<v_accion,EntCmd> >("LoadCombContainer")
  ;

class_<LoadCombinations, bases<EntCmd> >("Combinations")
  .add_property("getULSTransientCombinations", &LoadCombinations::getULSTransientCombinations)
  .add_property("getULSAccidentalCombinations", &LoadCombinations::getULSAccidentalCombinations)
  .add_property("getULSSeismicCombinations", &LoadCombinations::getULSSeismicCombinations)

  .add_property("getSLSCharacteristicCombinations", &LoadCombinations::getSLSCharacteristicCombinations)
  .add_property("getSLSFrequentCombinations", &LoadCombinations::getSLSFrequentCombinations)
  .add_property("getSLSQuasiPermanentCombinations", &LoadCombinations::getSLSQuasiPermanentCombinations)
;


class_<LoadCombinationGenerator, bases<EntCmd> >("LoadCombGenerator")
  .add_property("pondAcciones", make_function( &LoadCombinationGenerator::getPondAcciones, return_internal_reference<>() ), &LoadCombinationGenerator::setPondAcciones)
  .def("defPonderacion", make_function(&LoadCombinationGenerator::defPonderacion,return_internal_reference<>()))
  .def("insert", make_function(&LoadCombinationGenerator::inserta,return_internal_reference<>()))
  .def("genera", &LoadCombinationGenerator::genera)
  .add_property("getLoadCombinations", make_function(&LoadCombinationGenerator::getLoadCombinations,return_internal_reference<>()))
  ;
