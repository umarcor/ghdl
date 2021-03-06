library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.TestPkg.all ;

entity TbTest is
end entity TbTest;

architecture rtl of TbTest is

  component test is
    port(
      input : in unsigned);
  end component test;

  signal Fred : unsigned(7 downto 0) ;
begin
  test_1 : test 
    port map (
      input => Fred 
    );
  
  process 
  begin 
    Fred <= X"00" ;
    wait for 1 ns ;
    for i in 1 to 10 loop
      Fred <= X"00" + i ; 
      wait for 1 ns ;
    end loop ;
    std.env.stop ;
  end process ; 
end architecture;