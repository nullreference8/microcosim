#ifndef DATABASE_CONTROLS_HPP
#define DATABASE_CONTROLS_HPP
#include <string>
#include "src/sqlite3/sqlite3.h"

namespace database {
  class Context {
    public:
      int InitDB();
      int RollbackDB();
      int SqlExec(std::string sql);
      int SqlQuery(std::string sql, int (*callback)(void *, int, char **, char **));
      bool PrepareDbAndStmt(sqlite3** db, sqlite3_stmt** stmt, std::string sql);
      bool FinishSqlConn(sqlite3** db, sqlite3_stmt** stmt);
      std::string QuoteSqlString(std::string value);
  };
}
#endif