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
//SqLiteDatabase.h

#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "SqLiteObject.h"
#include <sqlite3.h>
#include "xc_utils/src/utils/sqlitepp/IError.h"
#include "xc_utils/src/utils/sqlitepp/Database.h"
#include "xc_utils/src/utils/sqlitepp/StderrLog.h"

//! @ingroup SQLITE
//
//!  @brief Clase para consulta SQL
class SqLiteDatabase: public SqLiteObject
  {
    static Database::Mutex mutex;
    static StderrLog log;
    Database db; //!< Base de datos SqLite.
    SqLiteQuery *defaultQuery;
    static sqlite3_stmt *tmpRes;
  public:
    SqLiteDatabase(const std::string &nmb);
    inline Database &getDB(void)
      { return db; }
    bool existeTabla(const std::string &nmbTabla) const;
    bool borraTabla(const std::string &nmbTabla);

    SqLiteQuery *getDefaultQuery(void);
    SqLiteQuery *NuevaQuery(const std::string &nmb);
  };
#endif
