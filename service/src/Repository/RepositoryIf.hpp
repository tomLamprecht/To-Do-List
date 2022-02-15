#pragma once

#include "Core/Model/Board.hpp"
#include "optional"
#include <string>

namespace Reminder {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual std::vector<Reminder::Core::Model::List> getLists() = 0;
    virtual std::optional<Reminder::Core::Model::List> getList(int id) = 0;
    virtual std::optional<Reminder::Core::Model::List> postList(std::string name) = 0;
    virtual std::optional<Reminder::Core::Model::List> putList(int id, std::string name) = 0;
    virtual void deleteList(int id) = 0;
    virtual std::vector<Reminder::Core::Model::ReminderItem> getReminderItems(int listId) = 0;
    virtual std::optional<Reminder::Core::Model::ReminderItem> getReminderItem(int itemId) = 0;
    virtual std::optional<Reminder::Core::Model::ReminderItem> postReminderItem(int listId, std::string title) = 0;
    virtual std::optional<Reminder::Core::Model::ReminderItem> putReminderItem(int itemId, std::string title, std::string timestamp, bool flag) = 0;
    virtual void deleteReminder(int id) = 0;
    virtual std::optional<Reminder::Core::Model::List> getRemindersWithFlag() = 0;
    virtual std::optional<Reminder::Core::Model::List> getRemindersWithTimestamp(std::string timestamp) = 0;
};

} // namespace Repository
} // namespace Reminder
