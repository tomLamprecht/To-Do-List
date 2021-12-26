#pragma once

#include "Repository/RepositoryIf.hpp"
#include "sqlite3.h"
#include <string>

namespace Reminder {
namespace Repository {

class SQLiteRepository : public RepositoryIf {
  private:
    sqlite3 *database;

  public:
    static int queryCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames);

    SQLiteRepository();
    virtual ~SQLiteRepository();
    void initialize();
    void createDummyData();

    void handleSQLError(int statementResult, char *errorMessage);
    static std::string const databaseFile;

    virtual std::string getDatabase();
};

} // namespace Repository
} // namespace Reminder
