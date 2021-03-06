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
//CommandEntity.h

#ifndef ENTCMD_H
#define ENTCMD_H

#include "EntityWithProperties.h"
#include <map>
#include <set>
#include <deque>
#include <stack>
#include "xc_utils/src/utils/text/text_string.h"
#include "xc_utils/src/kernel/ErrLogFiles.h"
#include <boost/python.hpp>

namespace boost
  {
    class any;
  }

typedef enum{FALLO,CONTINUA,COMPLETADO} resul_lectura;

//! @ingroup KERNEL
//
//! @brief Objet that can execute python scripts.
class CommandEntity: public EntityWithProperties
  {
  private:
    static ErrLogFiles err_log_files; //!< Streams para errores y avisos.
    std::map<std::string, boost::python::object> python_dict; //!< Variables de Python.
  protected:

    static CommandEntity *entcmd_cast(boost::any &data);


    template <class T>
    void string_to(T &,const std::string &) const;
  public:
    CommandEntity(CommandEntity *owr= nullptr);

    CommandEntity *Owner(void);
    const CommandEntity *Owner(void) const;

    const std::string &getLogFileName(void) const;
    void setLogFileName(const std::string &);
    const std::string &getErrFileName(void) const;
    void setErrFileName(const std::string &);    

    void clearPyProps(void);
    bool hasPyProp(const std::string &);
    boost::python::object getPyProp(const std::string &str);
    void setPyProp(std::string str, boost::python::object val);
    boost::python::object evalPy(boost::python::object dict,const std::string &);
    boost::python::object execPy(boost::python::object dict,const std::string &);
    boost::python::object execFilePy(boost::python::object dict,const std::string &);
  };

#endif
