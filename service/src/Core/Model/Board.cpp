#include "Board.hpp"

using namespace Prog3::Core::Model;

Board::Board() {}

std::vector<List> &Board::getLists() {
    return lists;
}

void Board::setLists(std::vector<List> const &columns) {
    this->lists = columns;
}
