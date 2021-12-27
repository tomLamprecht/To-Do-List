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
    virtual std::vector<Reminder::Core::Model::List> getLists();
    virtual std::optional<Reminder::Core::Model::List> getList(int id);
    virtual std::optional<Reminder::Core::Model::List> postList(std::string name, int position);
    virtual std::optional<Reminder::Core::Model::List> putList(int id, std::string name, int position);
    virtual void deleteList(int id);
    virtual std::vector<Reminder::Core::Model::ReminderItem> getReminderItems(int listId);
    virtual std::optional<Reminder::Core::Model::ReminderItem> getReminderItem(int listId, int itemId);
    virtual std::optional<Reminder::Core::Model::ReminderItem> postReminderItem(int listId, std::string title, int position);
    virtual std::optional<Reminder::Core::Model::ReminderItem> putReminderItem(int listId, int itemId, std::string title, int position);
    virtual void deleteItem(int columnId, int itemId);
};

} // namespace Repository
} // namespace Reminder
