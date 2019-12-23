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
