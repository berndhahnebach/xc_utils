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
//SqLiteObject

#include "SqLiteObject.h"
#include "SqLiteDatabase.h"
#include "SqLiteQuery.h"
#include "boost/algorithm/string/trim.hpp"
#include "xc_utils/src/utils/sqlitepp/StderrLog.h"


SqLiteObject::map_sql_objs SqLiteObject::SqLiteObjs;

//! @brief Borra las consultas.
void SqLiteObject::borra_queries(void)
  {
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++)
      {
        SqLiteQuery *tmp= dynamic_cast<SqLiteQuery *>((*i).second);
        if(tmp)
          {
            delete (*i).second;
            (*i).second= nullptr;
            SqLiteObjs.erase(i);            
          }
      }
  }

//! @brief Borra las bases de datos.
void SqLiteObject::borra_databases(void)
  {
    borra_queries(); //Primero consultas y luego bases de datos.
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++)
      {
        SqLiteDatabase *tmp= dynamic_cast<SqLiteDatabase *>((*i).second);
        if(tmp)
          {
            delete (*i).second;
            (*i).second= nullptr;
            SqLiteObjs.erase(i);            
          }
      }
  }

//! @brief Borra todos los objetos.
void SqLiteObject::borra_objetos(void)
  {
    borra_databases(); //Borramos consultas y después bases de datos.
    for(sql_objs_iterator i= SqLiteObjs.begin();i!=SqLiteObjs.end();i++) //Borramos el resto de objetos.
      {
        delete (*i).second;
        (*i).second= nullptr;
      }
    SqLiteObjs.clear();
  }

//! @brief Inerts the object into the container.
void SqLiteObject::insert_object(const std::string &nmb,SqLiteObject *ptr)
  {
    assert(ptr);
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto ya existe.
      {
        std::cerr << "No se pudo crear el objeto: '" 
                  << nmb << "' ya existe." << std::endl;
        delete ptr; //Liberamos la memoria.
      }
    else
      SqLiteObjs[nmb]= ptr;
  }

//! @brief Return un puntero al objeto cuyo nombre se pasa como parámetro (si existe). 
SqLiteObject *SqLiteObject::busca_objeto(const std::string &nmb)
  {
    SqLiteObject *retval= nullptr;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= (*i).second;
    return retval;
  }


//! @brief Constructor.
SqLiteObject::SqLiteObject(void)
  {}

//! @brief Destructor.
SqLiteObject::~SqLiteObject(void)
  {}

void SqLiteObject::clearAll(void)
  { borra_objetos(); }

//! @brief Crea la base de datos con el nombre que se pasa como parametro.
void SqLiteObject::NuevaDatabase(const std::string &nmb)
  { 
    SqLiteObject *ptr= new SqLiteDatabase(nmb);
    if(ptr)
      insert_object(nmb,ptr);
    else
      std::cerr << "SqLiteObject::NuevoObjetoSql; el puntero al objeto es nulo." << std::endl;
  }

//! @brief Crea la consulta el nombre que se pasa como parametro.
void SqLiteObject::NuevaQuery(const std::string &nmb,const std::string &nmb_db)
  { 
    SqLiteDatabase *ptr_db= getDatabase(nmb_db);
    if(ptr_db)
      ptr_db->NuevaQuery(nmb);
    else
      std::cerr << "No se encontró la base de datos: " << nmb_db << std::endl;

  }


//! @brief Preprocesa una text string que contiene una sentencia SQL.
std::string SqLiteObject::preprocesa_str_sql(const std::string &str) const
  {
    return boost::trim_copy_if(str,boost::is_any_of("\""));
  }


//! @brief Return la base de datos cuyo nombre se pasa como parámetro. 
SqLiteDatabase *SqLiteObject::getDatabase(const std::string &nmb)
  {
    SqLiteDatabase *retval= nullptr;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= dynamic_cast<SqLiteDatabase *>((*i).second);
    return retval;
  }

//! @brief Return la consulta cuyo nombre se pasa como parámetro. 
SqLiteQuery *SqLiteObject::getQuery(const std::string &nmb)
  {
    SqLiteQuery *retval= nullptr;
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      retval= dynamic_cast<SqLiteQuery *>((*i).second);
    return retval;
  }

//! @brief Borra del contenedor el objeto cuyo nombre se pasa como parámetro. 
void SqLiteObject::BorraObjeto(const std::string &nmb)
  {
    sql_objs_iterator i= SqLiteObjs.find(nmb);
    if(i!= SqLiteObjs.end()) //El objeto existe.
      {
        delete (*i).second;
        (*i).second= nullptr;
        SqLiteObjs.erase(i);
      }
  }

