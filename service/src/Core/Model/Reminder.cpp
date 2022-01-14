#include "Reminder.hpp"

using namespace Reminder::Core::Model;

ReminderItem::ReminderItem(int id, std::string givenTitle, std::string givenTimestamp, bool givenFlag)
    : id(id), title(givenTitle), timestamp(givenTimestamp), flag(givenFlag) {}

int ReminderItem::getId() const {
    return id;
}

std::string ReminderItem::getTitle() const {
    return title;
}

std::string ReminderItem::getTimestamp() const {
    return timestamp;
}

void ReminderItem::setID(int givenID) {
    id = givenID;
}

void ReminderItem::setTitle(std::string givenTitle) {
    title = givenTitle;
}

void ReminderItem::setTimestamp(std::string givenTime) {
    timestamp = givenTime;
}

void ReminderItem::setFlagged(bool givenFlag) {
    flag = givenFlag;
}

bool ReminderItem::isFlagged() const {
    return flag;
}
