LIBRARY ieee;                                               
USE ieee.std_logic_1164.all;
USE ieee.numeric_std.all;

ENTITY tb IS
END tb;
ARCHITECTURE arc OF tb IS
-- constants                                                 
-- signals                                                   
SIGNAL x : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL y : STD_LOGIC_VECTOR(31 DOWNTO 0);
SIGNAL z : STD_LOGIC_VECTOR(63 DOWNTO 0);
signal prod : STD_LOGIC_VECTOR(63 DOWNTO 0);
COMPONENT Mult_Dadda32
	PORT (
	x : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	y : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
	z : OUT STD_LOGIC_VECTOR(63 DOWNTO 0)
	);
END COMPONENT;
BEGIN
	i1 : Mult_Dadda32
	PORT MAP (
-- list connections between master ports and signals
	x => x,
	y => y,
	z => z
	);
-- x[31]

        prod <= std_logic_vector(unsigned(x)*unsigned(y));
        
PROCESS
BEGIN
  x <= (0 => '1', others => '0');
  for i in 0 to 31 loop
    y <= (others => '0');
    y(i) <= '1';
    wait for 10 ns;
  end loop;
  wait for 10 ns;

  y <= (0 => '1', others => '0');
  for i in 0 to 31 loop
    x <= (others => '0');
    x(i) <= '1';
    wait for 10 ns;
  end loop;
  wait for 10 ns;
  
  wait;
end process;

END arc;
