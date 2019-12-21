// Copyright (C) 2019 João Pedro de Omena Simas
// Copyright (C) 2017 Henrique Ogawa, Lucas Gaia
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

#ifndef SIGNAL_HH
#define SIGNAL_HH

#include <string>

class Signal {
public:
  enum signal_type {P, S, Cout, Cin};
private:
  signal_type type;
  int x_i;
  int y_i;
public:


  Signal(signal_type type, int x_i, int y_i) : type(type), x_i(x_i), y_i(y_i) {
    if(type != P && type != S && type != Cout && type != Cin)
      throw std::runtime_error("Tried to create signal with invalid signal type.");
  }

  ~Signal() {
  }

  std::string toString(){
    switch(type) {
    case P:
      return std::string("P(") + std::to_string(x_i) + ")(" + std::to_string(y_i) + ")";
    case S:
      return std::string("S(") + std::to_string(x_i) + ")";
    case Cout:
      return std::string("Cout(") + std::to_string(x_i) + ")";
    case Cin:
      return std::string("Cin(") + std::to_string(x_i) + ")";
    default:
      throw std::runtime_error("Tried to call toString() on signal with invalid signal type.");
    }
  }

};

#endif
