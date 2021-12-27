#pragma once

#include <string>

namespace Reminder {
namespace Core {
namespace Model {

class ReminderItem {
  public:
    ReminderItem(int id, std::string givenTitle, int givenPosition, std::string givenTimestamp, bool givenFlag);
    ~ReminderItem(){};

    int getId() const;
    std::string getTitle() const;
    int getPos() const;
    std::string getTimestamp() const;
    bool isFlagged() const;

    void setID(int givenID);
    void setTitle(std::string givenTitle);
    void setPos(int givenPos);
    void setTimestamp(std::string givenTime);
    void setFlagged(bool flag);

  private:
    int id;
    std::string title;
    int position;
    std::string timestamp;
    bool flag;
};

} // namespace Model
} // namespace Core
} // namespace Reminder
