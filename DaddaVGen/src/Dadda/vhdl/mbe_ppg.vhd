library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

--partial product encoder-generator
--receives 3 consecutive binary digits and calculates the product
--of the resulting radix-4 mbe digit with the number a
entity mbe_ppg is
  generic(n : natural := 32);
  port(three_digits : in std_logic_vector(2 downto 0);--sign bit representation
       a : in std_logic_vector(N-1 downto 0);
       pp : out std_logic_vector(N downto 0);
       neg : out std_logic);
end mbe_ppg;

architecture arch of mbe_ppg is
  signal s_inc : std_logic;
begin
  with three_digits select pp <=
    (others => '0') when "000" | "111",
    '0'&a when "001" | "010",
    a&'0' when "011",
    --check this
    not ('0'&a) when "110" | "101",
    not (a&'0') when "100",
    (others => 'X') when others;
  
  with three_digits select neg <=
    '0' when "000" | "111" | "001" | "010" | "011",
    '1' when "110" | "101" | "100",
    'X' when others;
end architecture;
