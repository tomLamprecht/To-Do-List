#pragma once

#include "Api/Parser/ParserIf.hpp"
#include "Repository/RepositoryIf.hpp"

namespace Reminder {
namespace Core {
class Manager {
  private:
    Reminder::Repository::RepositoryIf &repository;
    Reminder::Api::Parser::ParserIf &parser;

  public:
    Manager(Reminder::Api::Parser::ParserIf &givenParser, Reminder::Repository::RepositoryIf &givenRepository);
    ~Manager();

    std::string getDatabase();
    std::string getLists();
    std::string postLists(std::string request);
    std::string putList(int listID, std::string request);
    std::string deleteLists(int listID);
    std::string getList(int listID);

    std::string getReminders(int listID);
    std::string postReminder(int listID, std::string request);

    std::string getReminder(int listID, int reminderID);
    std::string putItem(int listID, int reminderID, std::string request);
    std::string deleteItem(int listID, int reminderID);
};

} // namespace Core
} // namespace Reminder
