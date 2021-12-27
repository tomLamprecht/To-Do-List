#include "SQLiteRepository.hpp"
#include "Core/Exception/NotImplementedException.hpp"
#include <filesystem>
#include <iostream>

using namespace std;
using namespace Reminder::Repository;
using namespace Reminder::Core::Model;
using namespace Reminder::Core::Exception;

#ifdef RELEASE_SERVICE
string const SQLiteRepository::databaseFile = "./data/reminder-app.db";
#else
string const SQLiteRepository::databaseFile = "../data/reminder-app.db";
#endif

SQLiteRepository::SQLiteRepository() : database(nullptr) {

    string databaseDirectory = filesystem::path(databaseFile).parent_path().string();

    if (filesystem::is_directory(databaseDirectory) == false) {
        filesystem::create_directory(databaseDirectory);
    }

    int result = sqlite3_open(databaseFile.c_str(), &database);

    if (SQLITE_OK != result) {
        cout << "Cannot open database: " << sqlite3_errmsg(database) << endl;
    }
    initialize();
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(database);
}

void SQLiteRepository::initialize() {
    int result = 0;
    char *errorMessage = nullptr;

    string sqlCreateTableList =
        "create table if not exists list("
        "id integer not null primary key autoincrement,"
        "name text not null,"
        "position integer not null UNIQUE);";

    string sqlCreateTableReminder =
        "create table if not exists reminder("
        "id integer not null primary key autoincrement,"
        "title text not null,"
        "timestamp text not null,"
        "position integer not null,"
        "list_id integer not null,"
        "unique (position, list_id),"
        "foreign key (list_id) references list (id));";

    result = sqlite3_exec(database, sqlCreateTableList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
    result = sqlite3_exec(database, sqlCreateTableReminder.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    createDummyData();
}

void SQLiteRepository::handleSQLError(int statementResult, char *errorMessage) {

    if (statementResult != SQLITE_OK) {
        cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

void SQLiteRepository::createDummyData() {

    cout << "creatingDummyData ..." << endl;

    int result = 0;
    char *errorMessage;
    string sqlInsertDummyColumns =
        "insert into list (name, position)"
        "VALUES"
        "(\"prepare\", 1),"
        "(\"running\", 2),"
        "(\"finished\", 3);";

    result = sqlite3_exec(database, sqlInsertDummyColumns.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    string sqlInserDummyItems =
        "insert into reminder (title, timestamp, position, list_id)"
        "VALUES"
        "(\"in plan\", date('now'), 1, 1),"
        "(\"some running task\", date('now'), 1, 2),"
        "(\"finished task 1\", date('now'), 1, 3),"
        "(\"finished task 2\", date('now'), 2, 3);";

    result = sqlite3_exec(database, sqlInserDummyItems.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::string SQLiteRepository::getDatabase() {
    string data = "";
    string sqlQuery = "SELECT * FROM list l, reminder r";
    int result = 0;
    char *errorMessage;
    result = sqlite3_exec(database, sqlQuery.c_str(), SQLiteRepository::queryCallback, &data, &errorMessage);
    handleSQLError(result, errorMessage);
    return data;
}

std::vector<List> SQLiteRepository::getLists() {
    throw NotImplementedException();
}

std::optional<List> SQLiteRepository::getList(int id) {
    throw NotImplementedException();
}
std::optional<List> SQLiteRepository::postList(std::string name, int position) {
    throw NotImplementedException();
}
std::optional<List> SQLiteRepository::putList(int id, std::string name, int position) {
    throw NotImplementedException();
}
void SQLiteRepository::deleteList(int id) {
    throw NotImplementedException();
}
std::vector<ReminderItem> SQLiteRepository::getReminderItems(int listId) {
    throw NotImplementedException();
}
std::optional<ReminderItem> SQLiteRepository::getReminderItem(int listId, int itemId) {
    throw NotImplementedException();
}
std::optional<ReminderItem> SQLiteRepository::postReminderItem(int listId, std::string title, int position) {
    throw NotImplementedException();
}
std::optional<ReminderItem> SQLiteRepository::putReminderItem(int listId, int itemId, std::string title, int position) {
    throw NotImplementedException();
}
void SQLiteRepository::deleteItem(int columnId, int itemId) {
    throw NotImplementedException();
}

int SQLiteRepository::queryCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    string *stringPointer = static_cast<string *>(data);
    for (int i = 0; i < numberOfColumns; i++) {
        *stringPointer = *stringPointer + columnNames[i] + ":" + fieldValues[i];
        if (i < numberOfColumns - 1)
            *stringPointer = *stringPointer + ",";
    }
    *stringPointer = *stringPointer + ";";
    return 0;
}
