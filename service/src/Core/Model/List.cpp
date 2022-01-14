#include "List.hpp"

using namespace Reminder::Core::Model;

List::List(int id, std::string givenName)
    : id(id), name(givenName) {}

int List::getId() const {
    return id;
}

std::string List::getName() const {
    return name;
}

std::vector<ReminderItem> List::getReminders() const {
    return reminders;
}

void List::setID(int givenId) {
    id = givenId;
}

void List::setName(std::string givenName) {
    name = givenName;
}

void List::addReminder(ReminderItem &givenReminder) {
    reminders.push_back(givenReminder);
}
