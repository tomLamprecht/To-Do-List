#include "Manager.hpp"
#include <iostream>
#include <vector>

using namespace Reminder::Core;
using namespace Reminder::Core::Model;
using namespace Reminder::Api::Parser;
using namespace Reminder::Repository;
using namespace std;

Manager::Manager(ParserIf &givenParser, RepositoryIf &givenRepository)
    : parser(givenParser), repository(givenRepository) {
}

Manager::~Manager() {
}

string Manager::getDatabase() {

    return repository.getDatabase();
}

string Manager::getLists() {
    std::vector<List> lists = repository.getLists();
    return "getLists";
}

string Manager::postLists(std::string request) {

    return "postLists";
}
string Manager::putLists(int listID, std::string request) {

    return "putLists";
}

string Manager::deleteLists(int listID) {
    return "deleteLists";
}

string Manager::getList(int listID) {
    return "getList";
}

string Manager::getReminders(int listID) {
    return "getReminders";
}
string Manager::postReminder(int listID, std::string request) {
    return "postReminder";
}

string Manager::getReminder(int listID, int reminderID) {
    return "getReminder";
}

string Manager::putItem(int listID, int reminderID, std::string request) {
    return "putItem";
}

string Manager::deleteItem(int listID, int reminderID) {
    return "deleteItem";
}
