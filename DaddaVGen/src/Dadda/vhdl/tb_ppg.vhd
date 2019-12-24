LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;

entity tb_ppg is
end entity;

architecture arch of tb_ppg is
  component  mbe_ppg is
    generic(n : natural := 32);
  port(three_digits : in std_logic_vector(2 downto 0);--sign bit representation
       a : in std_logic_vector(N-1 downto 0);
       pp : out std_logic_vector(N downto 0);
       neg : out std_logic);
  end component;
  constant N : natural := 32;
  signal t : std_logic_vector(2 downto 0);
  signal a : std_logic_vector(N-1 downto 0);
  signal pp : std_logic_vector(N downto 0);
  signal n_neg : std_logic;
begin
  mbe: mbe_ppg generic map (N) port map(t, a, pp, n_neg);
  process
    
  begin
    t <= "100";
    for i in 0 to N - 1 loop
      a <= (others => '0');
      a(i) <= '1';
      wait for 10 ns;
    end loop;

    wait;
  end process;
  
end architecture;
