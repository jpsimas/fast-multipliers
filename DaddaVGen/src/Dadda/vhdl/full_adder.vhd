library ieee;
use ieee.std_logic_1164.all;

entity full_adder is
  port(a   : in  std_logic;
       b   : in  std_logic;
       cin : in  std_logic;
       s   : out std_logic;
       cout : out std_logic);
end full_adder;

architecture behavior of full_adder is
  component half_adder
    port(a : in  std_logic;
         b : in  std_logic;
         s : out std_logic;
         cout : out std_logic);
  end component;
  
  signal s_1 : std_logic;
  signal c_1 : std_logic;
  signal c_2 : std_logic;
begin
  h0 : half_adder port map(a, b, s_1, c_1);
  h1 : half_adder port map(s_1, cin, s, c_2);
  cout <= c_1 or c_2;
end architecture;
