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

#include "AdderTree.hh"

int main(int argc, char* argv[]) {
  int N_bits;
  if(argc == 1) {
    std::cout << "No number of bits given. Defaulting to 32." << std::endl;
    N_bits = 32;
  } else {
    N_bits = std::stoi(argv[1]);
  }

  std::cout << "Generating " << N_bits << "-bit multiplier" << std::endl;
  
  AdderTree tree;
   
  tree.setDaddaAdders(N_bits);
   
  tree.genVHDL(N_bits);
   
  return 0;
}
