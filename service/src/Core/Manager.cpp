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

    return parser.convertToApiString(lists);
}

string Manager::postLists(std::string request) {
    int const dummyId = -1;
    std::optional<List> parsedListOptional = parser.convertListToModel(dummyId, request);
    if (!parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    List parsedList = parsedListOptional.value();

    std::optional<List> postedList = repository.postList(parsedList.getName(), parsedList.getPos());
    if (postedList) {
        return parser.convertToApiString(postedList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

string Manager::putList(int listID, std::string request) {
    std::optional<List> parsedListOptional = parser.convertListToModel(listID, request);

    if (!parsedListOptional.has_value()) {
        return parser.getEmptyResponseString();
    }

    List parsedList = parsedListOptional.value();

    std::optional<List> putList = repository.putList(listID, parsedList.getName(), parsedList.getPos());

    if (putList) {
        return parser.convertToApiString(putList.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

void Manager::deleteList(int listID) {
    repository.deleteList(listID);
}

string Manager::getList(int listID) {
    std::optional<List> list = repository.getList(listID);
    if (list) {
        return parser.convertToApiString(list.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

string Manager::getReminders(int listID) {
    std::vector<ReminderItem> items = repository.getReminderItems(listID);

    return parser.convertToApiString(items);
}
string Manager::postReminder(int listID, std::string request) {
    int const dummyId = -1;
    std::optional<ReminderItem> parsedReminderOptional = parser.convertReminderItemToModel(dummyId, request);
    if (!parsedReminderOptional.has_value())
        return parser.getEmptyResponseString();

    ReminderItem reminderItem = parsedReminderOptional.value();
    std::optional<ReminderItem> postedItem = repository.postReminderItem(listID, reminderItem.getTitle(), reminderItem.getPos());

    if (postedItem) {
        return parser.convertToApiString(postedItem.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

string Manager::getReminder(int listID, int reminderID) {
    std::optional<ReminderItem> reminder = repository.getReminderItem(listID, reminderID);

    if (reminder) {
        return parser.convertToApiString(reminder.value());
    } else {
        return parser.getEmptyResponseString();
    }
}

string Manager::putItem(int listID, int reminderID, std::string request) {
    return "putItem";
}

void Manager::deleteItem(int listID, int reminderID) {
}
