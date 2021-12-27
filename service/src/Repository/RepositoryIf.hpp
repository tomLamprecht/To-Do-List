#pragma once

#include "Core/Model/Board.hpp"
#include <string>

namespace Reminder {
namespace Repository {
class RepositoryIf {
  public:
    virtual ~RepositoryIf() {}

    virtual std::string getDatabase() = 0;
};

} // namespace Repository
} // namespace Reminder
