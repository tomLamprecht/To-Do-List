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
        "flag integer not null,"
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
        "insert into reminder (title, timestamp, position, list_id, flag)"
        "VALUES"
        "(\"in plan\", date('now'), 1, 1, 1),"
        "(\"some running task\", date('now'), 1, 2, 0),"
        "(\"finished task 1\", date('now'), 1, 3, 1),"
        "(\"finished task 2\", date('now'), 2, 3, 0);";

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
    string itemSqlSelect = "SELECT id FROM list;";
    char *errorMessage = nullptr;
    vector<int> ids;
    int answer = sqlite3_exec(database, itemSqlSelect.c_str(), SQLiteRepository::getIdCallback, &ids, &errorMessage);
    handleSQLError(answer, errorMessage);

    if (answer != SQLITE_OK) {
        vector<List> emptyVector;
        return emptyVector;
    }
    vector<List> columns;

    for (auto id : ids) {
        optional<List> temp = getList(id);
        if (temp.has_value()) {
            columns.push_back(temp.value());
        }
    }
    return columns;
}

std::optional<List> SQLiteRepository::getList(int id) {
    string sqlSelect = "SELECT * FROM list WHERE id=" + to_string(id) + ";";
    char *errorMessage = nullptr;
    //this is done to reserve the needed memory
    List list(-1, "", 0);

    vector<ReminderItem> tempItems = getReminderItems(id);

    int result = sqlite3_exec(database, sqlSelect.c_str(), SQLiteRepository::getListCallback, &list, &errorMessage);
    handleSQLError(result, errorMessage);

    for (auto item : tempItems) {
        list.addReminder(item);
    }

    if (result != SQLITE_OK || list.getId() == -1)
        return nullopt;

    return list;
}
std::optional<List> SQLiteRepository::postList(std::string name, int position) {
    string sqlPostList =
        "INSERT INTO list('name', 'position') "
        "VALUES('" +
        name + "', '" + to_string(position) + "')";

    int result = 0;
    char *errorMessage = nullptr;

    result = sqlite3_exec(database, sqlPostList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int listId = sqlite3_last_insert_rowid(database);
        return List(listId, name, position);
    }

    return std::nullopt;
}

bool SQLiteRepository::checkIfListExist(int id) {
    int result = 0;
    char *errorMessage = nullptr;
    int gotCalled = 0;
    string sqlSelectList = "SELECT * FROM list WHERE id = " + to_string(id) + ";";
    result = sqlite3_exec(database, sqlSelectList.c_str(), SQLiteRepository::gotCalledCallback, &gotCalled, &errorMessage);
    handleSQLError(result, errorMessage);

    if (!gotCalled) {
        return false;
    }
    return true;
}

std::optional<List> SQLiteRepository::putList(int id, std::string name, int position) {
    int result = 0;
    char *errorMessage = nullptr;
    bool gotCalled = checkIfListExist(id);
    string sqlUpdateList = "UPDATE list SET name=\"" + name + "\", position = " + to_string(position) + " WHERE id = " + to_string(id) + ";";

    if (!gotCalled) {
        return std::nullopt;
    }

    vector<ReminderItem> items = getReminderItems(id);

    errorMessage = nullptr;
    result = sqlite3_exec(database, sqlUpdateList.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    List returnList(id, name, position);
    for (auto item : items) {
        returnList.addReminder(item);
    }
    return returnList;
}
void SQLiteRepository::deleteList(int id) {
    string sqlDelete = "DELETE FROM list WHERE id=" + to_string(id) + ";";
    char *errorMessage = nullptr;
    int result = 0;

    result = sqlite3_exec(database, sqlDelete.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);
}

std::vector<ReminderItem> SQLiteRepository::getReminderItems(int listId) {
    string itemSqlSelect = "SELECT * FROM reminder WHERE list_id=" + to_string(listId) + ";";
    char *errorMessage = nullptr;
    vector<ReminderItem> tempItems;
    vector<ReminderItem> *items = &tempItems;
    int answer = sqlite3_exec(database, itemSqlSelect.c_str(), SQLiteRepository::getReminderItemCallback, items, &errorMessage);
    handleSQLError(answer, errorMessage);

    if (answer != SQLITE_OK) {
        vector<ReminderItem> emptyVector;
        return emptyVector;
    }
    return tempItems;
}
std::optional<ReminderItem> SQLiteRepository::getReminderItem(int itemId) {
    string itemSqlSelect = "SELECT * FROM reminder WHERE id = " + to_string(itemId) + ";";
    char *errorMessage = nullptr;
    int result = 0;
    vector<ReminderItem> tempItems;
    result = sqlite3_exec(database, itemSqlSelect.c_str(), SQLiteRepository::getReminderItemCallback, &tempItems, &errorMessage);
    handleSQLError(result, errorMessage);

    if (result != SQLITE_OK || size(tempItems) == 0) {
        return std::nullopt;
    }
    return tempItems[0];
}

std::optional<ReminderItem> SQLiteRepository::postReminderItem(int listId, std::string title, int position) {
    bool listExist = checkIfListExist(listId);
    if (!listExist)
        return std::nullopt;

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto timestamp = oss.str();

    int result = 0;
    char *errorMessage = nullptr;
    string sqlPost = "INSERT INTO reminder('title', 'timestamp', 'position', 'list_id', 'flag') "
                     "VALUES (' " +
                     title + "', '" + timestamp + "', '" + to_string(position) + "' , '" + to_string(listId) + "' , " + "0);";

    result = sqlite3_exec(database, sqlPost.c_str(), NULL, 0, &errorMessage);
    handleSQLError(result, errorMessage);

    if (SQLITE_OK == result) {
        int itemId = sqlite3_last_insert_rowid(database);
        return ReminderItem(itemId, title, position, timestamp, 0);
    }
    return std::nullopt;
}

std::optional<ReminderItem> SQLiteRepository::putReminderItem(int listId, int itemId, std::string title, int position) {
    throw NotImplementedException();
}
void SQLiteRepository::deleteItem(int itemId) {
    throw NotImplementedException();
}

//--------------------------------------------------------------callback methods-------------------------------------------------------------

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

int SQLiteRepository::getListCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    List *list = static_cast<List *>(data);
    vector<std::string> values;
    for (int i = 0; i < numberOfColumns; i++) {
        values.push_back(*(fieldValues++));
    }
    int id = std::stoi(values[0]);
    string title = values[1];
    int position = std::stoi(values[2]);

    list->setID(id);
    list->setName(title);
    list->setPos(position);
    return 0;
}

bool to_bool(std::string const &s) {
    return s != "0";
}

int SQLiteRepository::getReminderItemCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    vector<ReminderItem> *items = static_cast<vector<ReminderItem> *>(data);
    vector<std::string> values;
    for (int i = 0; i < numberOfColumns; i++) {
        values.push_back(*(fieldValues++));
    }
    int id = std::stoi(values[0]);
    string title = values[1];
    string date = values[2];
    int position = std::stoi(values[3]);
    bool flag = to_bool(values[5]);
    ReminderItem temp(id, title, position, date, flag);
    items->push_back(temp);
    return 0;
}

int SQLiteRepository::getIdCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    if (numberOfColumns == 0) {
        return 0;
    }
    vector<int> *ids = static_cast<vector<int> *>(data);
    ids->push_back(stoi(fieldValues[0]));
    return 0;
}

int SQLiteRepository::gotCalledCallback(void *data, int numberOfColumns, char **fieldValues, char **columnNames) {
    int *intData = static_cast<int *>(data);
    (*intData) = 1;
    return 0;
}
