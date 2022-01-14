#pragma once

#include <string>

namespace Reminder {
namespace Core {
namespace Model {

class ReminderItem {
  public:
    ReminderItem(int id, std::string givenTitle, std::string givenTimestamp, bool givenFlag);
    ~ReminderItem(){};

    int getId() const;
    std::string getTitle() const;
    std::string getTimestamp() const;
    bool isFlagged() const;

    void setID(int givenID);
    void setTitle(std::string givenTitle);
    void setTimestamp(std::string givenTime);
    void setFlagged(bool flag);

  private:
    int id;
    std::string title;
    std::string timestamp;
    bool flag;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
