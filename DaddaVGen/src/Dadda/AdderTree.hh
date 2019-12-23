// Copyright (C) 2019 João Pedro de Omena Simas
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ADDERTREE_HH
#define ADDERTREE_HH
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <math.h>
#include <memory>
#include "Signal.hh"
#include "FA.hh"
#include "HA.hh"

class AdderTree {
protected:
  std::vector<std::shared_ptr<Adder>> Adders;
  // Dadda heights: 2, 3, 4, 6, 9, 13, 19, 28, 42, 63
  int n_adder = 0; //total number of adders
  static constexpr int NA = 0;
  std::map<int, std::vector<std::shared_ptr<Signal>>> PP_tree;

public:
  // @brief - set all partial product columns (tree configuration)
  std::map<int, std::vector<std::shared_ptr<Signal>>> setColumns(size_t N_bits);
  int getTreeSize();
  void addHalfAdder(int col);
  void addFullAdder(int col);
  void daddaReduction(size_t minReduction);
  void setDaddaAdders(size_t N_bits);
  // write VHDL code line by line
  void genVHDL(size_t N_bits);
};
#endif
