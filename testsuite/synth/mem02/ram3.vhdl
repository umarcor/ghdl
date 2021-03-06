library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ram3 is
  port (val : out std_logic_vector (7 downto 0);
        waddr : std_logic_vector (2 downto 0);
        wdat : std_logic;
        clk : std_logic);
end ram3;

architecture behav of ram3 is
  signal mem : std_logic_vector(7 downto 0);
begin
  process (clk)
    variable ra : natural;
    variable wa : natural;
  begin
    if rising_edge (clk) then
      ra := to_integer(unsigned (waddr));
      mem(ra) <= wdat;
    end if;
  end process;

  --  As MEM is read in a whole, this is not a RAM.
  val <= mem;
end behav;
