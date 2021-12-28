#include "Reminder.hpp"

using namespace Reminder::Core::Model;

ReminderItem::ReminderItem(int id, std::string givenTitle, int givenPosition, std::string givenTimestamp, bool givenFlag)
    : id(id), title(givenTitle), position(givenPosition), timestamp(givenTimestamp), flag(givenFlag) {}

int ReminderItem::getId() const {
    return id;
}

std::string ReminderItem::getTitle() const {
    return title;
}

int ReminderItem::getPos() const {
    return position;
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

void ReminderItem::setPos(int givenPos) {
    position = givenPos;
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
