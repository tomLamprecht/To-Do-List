#pragma once

#include "List.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace Prog3 {
namespace Core {
namespace Model {

class Board {
  public:
    Board();
    ~Board() {}

    std::vector<List> &getLists();
    void setLists(std::vector<List> const &columns);

  private:
    std::vector<List> lists;
};

} // namespace Model
} // namespace Core
} // namespace Prog3
