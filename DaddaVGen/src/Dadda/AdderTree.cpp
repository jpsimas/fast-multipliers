#include "AdderTree.hh"

std::map<int, std::vector<std::shared_ptr<Signal>>> AdderTree::setColumns(size_t N_bits){
  std::map<int, std::vector<std::shared_ptr<Signal>>> columns;
  // i represents the counter for each column
  for(size_t i = 0; i <= N_bits; i++) {
    std::vector<std::shared_ptr<Signal>> column;
    // j represents the counter in each column
    auto it = column.begin();
    for(size_t j = 0; j <= i; j+=2) {
      // Signal P("P", i - j, j);
      // column->add(j, P);
      it = column.insert(it, std::make_shared<Signal>(Signal::signal_type::P, j, i - j));
      it++;
    }

    if(i%2 == 0) {
      it = column.insert(it, std::make_shared<Signal>(Signal::signal_type::S, i - 1));
      it++;
    }
      
    columns[i] = column;
  }
  for(size_t i = N_bits; i < 2*N_bits-1; i++) {
    std::vector<std::shared_ptr<Signal>> column;
    // j represents the counter in each column
    // int cnt = 0;
    auto it = column.begin();
    for(size_t j = i - N_bits + 1; j < N_bits; j++) {
      // Signal P("P", i - j, j);
      // column->add(cnt, P);
      // cnt++;
      it = column.insert(it, std::make_shared<Signal>(Signal::signal_type::P, j, i - j));
      it++;
    }
    columns[i] = column;
  }

  columns[2*N_bits-1] = std::vector<std::shared_ptr<Signal>>();
  return columns;
}

int AdderTree::getTreeSize(){
  size_t maxTreeSize = PP_tree.find(0)->second.size();
  for(size_t i = 1; i < PP_tree.size();  i ++){
    if (maxTreeSize < PP_tree.find(i)->second.size())
      maxTreeSize = PP_tree.find(i)->second.size();
  }
  return maxTreeSize;
}

void AdderTree::addHalfAdder(int col){
  auto S = std::make_shared<Signal>(Signal::signal_type::S, n_adder, NA);
  auto Cout = std::make_shared<Signal>(Signal::signal_type::Cout, n_adder, NA);
  auto it = PP_tree.find(col);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  auto half_adder = std::make_shared<HA>(it->second.at(0), it->second.at(1), S, Cout);
  n_adder++;

  it->second.erase(it->second.begin());
  it->second.erase(it->second.begin());
  it->second.push_back(S);

  it = PP_tree.find(col + 1);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  it->second.push_back(Cout);
		
  // @lgaia - debug
  //System.out.println("HA " + half_adder.toString() + ";");
  Adders.push_back(half_adder);
}

void AdderTree::addFullAdder(int col){
  auto S = std::make_shared<Signal>(Signal::signal_type::S, n_adder, NA);
  auto Cout = std::make_shared<Signal>(Signal::signal_type::Cout, n_adder, NA);
  auto it = PP_tree.find(col);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  auto full_adder = std::make_shared<FA>(it->second.at(0), it->second.at(1), it->second.at(2), S, Cout);
  n_adder++;
  
  it->second.erase(it->second.begin());
  it->second.erase(it->second.begin());
  it->second.erase(it->second.begin());
  it->second.push_back(S);

  it = PP_tree.find(col + 1);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  it->second.push_back(Cout);
		
  // @lgaia - debug
  //System.out.println("FA " + full_adder.toString() + ";");
  Adders.push_back(full_adder);
}

void AdderTree::daddaReduction(size_t minReduction){
  //System.out.println("Altura desejada: " + minReduction);
  // std::vector<Signal> column;  // pick a specific partial product column
  
  for(size_t col = 2; col < PP_tree.size(); col ++){
    auto column = PP_tree.find(col)->second;
    int n_loop = 0;
    while(column.size() > minReduction){
      if(column.size() > minReduction + 1)
	addFullAdder(col);
      else
	addHalfAdder(col);
      column = PP_tree.find(col)->second;
      n_loop++;
      if(n_loop > 1000000)
	throw std::runtime_error("too many loops. column.size() = " + std::to_string(column.size()) + ". minReduction = " + std::to_string(minReduction));
    }
  }
};

void AdderTree::setDaddaAdders(size_t N_bits){
  constexpr double ReductionRatio = 1.5;
  int height = 2;
  PP_tree = setColumns(N_bits);  // all partial product columns
  int maxSize = getTreeSize(); // Maximum column size

  while(ReductionRatio * height < maxSize)
    height = floor(height * ReductionRatio);
  
  while(maxSize > 2) {
    daddaReduction(height);
    // update maxSize and Dadda height
    maxSize = getTreeSize();
    height = ceil(height / ReductionRatio);
  }
    
  std::cout << ":DDDDD" << std::endl;
    
  // column 0 only has one partial product
  // column 1 will be left with S[0], the output of a half adder
  auto S = std::make_shared<Signal>(Signal::signal_type::S, NA, NA);
  auto Cout = std::make_shared<Signal>(Signal::signal_type::Cout, NA, NA);
  auto it = PP_tree.find(1);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  std::shared_ptr<HA> half_adder = std::make_shared<HA>(it->second.at(0), it->second.at(1), S, Cout);

  n_adder++;

  it->second.erase(it->second.begin());
  it->second.erase(it->second.begin());
  it->second.push_back(S);
  
  it = PP_tree.find(2);
  if(it == PP_tree.end())
    throw std::runtime_error("WAKE ME UP INSIDE");
  it->second.push_back(Cout);

  // @lgaia - debug
  //System.out.println("HA " + half_adder.toString() + ";");
  Adders.push_back(half_adder);

  for(size_t col = 2; col < PP_tree.size(); col ++){
    if(PP_tree.find(col)->second.size() == 2){
      addHalfAdder(col);
    }else if(PP_tree.find(col)->second.size() == 3){
      addFullAdder(col);
    }
  }
}

void AdderTree::genVerilog(size_t N_bits){
  std::string filename = "Mult_Dadda" + std::to_string(N_bits);
  std::ofstream file;
  file.open("vhdl/" + filename + ".vhd", std::ofstream::out);
  
  // writer.write("`timescale 1ns / 1ps");
  
  file << "library ieee;";
  file << "\nuse ieee.std_logic_1164.all;";
	    
  file << "\n\nentity Mult_Dadda" + std::to_string(N_bits) + " is";
  file << "\ngeneric(N : natural := " + std::to_string(N_bits) + ");";

  file << "\nport(x : in std_logic_vector(N - 1 downto 0);";
  file << "\ny: in std_logic_vector(N - 1 downto 0);";
  file << "\nz : out std_logic_vector(2*N - 1 downto 0));";

  file << "\nend entity Mult_Dadda" + std::to_string(N_bits) + ";";

  file << "\narchitecture arch of Mult_Dadda" + std::to_string(N_bits) + " is";

  file << "\ncomponent full_adder is\nport(\na : in std_logic;\nb : in std_logic;\ncin : in  std_logic;\ns : out std_logic;\ncout : out std_logic);\nend component;";

  file << "\ncomponent half_adder is\nport(\na : in std_logic;\nb : in std_logic;\ns : out std_logic;\ncout : out std_logic);\nend component;\n";

  file << "\ncomponent mbe_ppg is\ngeneric(n : natural := 32);\nport(three_digits : in std_logic_vector(2 downto 0);--sign bit representation\na : in std_logic_vector(N-1 downto 0);\npp : out std_logic_vector(N downto 0);\nneg : out std_logic);\nend component;";

  file << "\n\ntype p_t is array (N downto 0) of std_logic_vector(N downto 0);";
  file << "\nsignal p : p_t;";
  file << "\nsignal neg : std_logic_vector(N/2 downto 0);";
  file << "\nsubtype s_t is std_logic_vector(" + std::to_string(n_adder) + " downto 0);";
  file << "\nsignal S : s_t;";
  file << "\nsubtype cout_t is std_logic_vector(" + std::to_string(n_adder) + " downto 0);";
  file << "\nsignal Cout : cout_t;";
  file << "\nsignal ppg0_three_digits, ppglast_three_digits : std_logic_vector(2 downto 0);";
  file << "\nbegin";
  // for(size_t i = 0; i < N_bits; i++) {
  //     for(size_t j = 0; j < N_bits; j++) {
  // 	    writer.write("\nP(" + i + ")(" + j + ") <= x(" + i + ") and y(" + j + ");");
  //     }
  // }
  file << "\nppg0_three_digits <= x(1 downto 0)&'0';";
  file << "\nppg0: mbe_ppg port map(ppg0_three_digits, y, P(0), neg(0));";
  file << "\nF0: for i in 1 to n/2-1 generate";
  file << "\nppgi: mbe_ppg port map(x(2*i + 1 downto 2*i - 1), y, P(2*i), neg(i));\nend generate;";
  file << "\nppglast_three_digits <= \"00\"&x(n - 1);";
  file << "\nppglast: mbe_ppg port map(ppglast_three_digits, y, P(n), neg(n/2));";
 
  int HAcnt = 1;
  int FAcnt = 1;
  for(auto& adder: Adders) {
    if (dynamic_cast<HA*>(adder.get())){
      file << "\nHA" + std::to_string(HAcnt) + " : half_adder port map" + adder->toString() + ";";
      HAcnt++;
    }
    else if (dynamic_cast<FA*>(adder.get())){
      file << "\nFA" + std::to_string(FAcnt) + " : full_adder port map" + adder->toString() + ";";
      FAcnt++;
    }
  }

  // output assignmens
  file << "\n\nz(" + std::to_string(2*N_bits-1) + ") <= Cout(" + std::to_string(n_adder-1) + ");";
  int t = 1 + 2;
  for(size_t i = (2*N_bits-2); i > 1; i--){
    file << "\nz(" + std::to_string(i) + ") <= S(" + std::to_string(n_adder-t) + ");";
    t++;
  }
  file << "\nz(1) <= S(0);";
  file << "\nz(0) <= P(0)(0);";

  file << "\nP(0)(" << N_bits + 1 << ") <= neg(0);";
  file << "\nP(0)(" << N_bits + 2 << ") <= neg(0);";
  file << "\nP(0)(" << N_bits + 3 << ") <= not neg(0);";

  for(size_t i = 1; i < N_bits/2; i++) {
    file << "\nP(" << i << ")(" << N_bits + 2*i + 1 << ") <= not neg(" << i << ");";
    file << "\nP(" << i << ")(" << N_bits + 2*i + 2 << ") <= \'1\';";    
  }

  file << "\n\nend architecture;";

  file.close();
}
