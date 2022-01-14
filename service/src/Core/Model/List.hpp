#pragma once

#include "Reminder.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Reminder {
namespace Core {

namespace Model {

class List {
  public:
    List(int id, std::string givenName);
    ~List(){};

    int getId() const;
    std::string getName() const;
    std::vector<ReminderItem> getReminders() const;

    void setID(int givenId);
    void setName(std::string givenName);
    void addReminder(ReminderItem &givenItem);

  private:
    int id;
    std::string name;
    std::vector<ReminderItem> reminders;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
