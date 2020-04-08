library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

use work.cAccess.all;

entity toplevel is
end entity toplevel;

architecture RTL of toplevel is

begin
	
	process
	begin		
		report "array length: " & integer'image(c_intArr.all'length);
		
		c_promptIndexValue(0);

		for i in 1 to c_intArr.all'right loop
			report "c_intArr[" & integer'image(i) &"] = " &  integer'image(c_intArr.all(i)) & ". Set to: " & integer'image(2*c_intArr.all(i));
			c_intArr.all(i) := 2*c_intArr.all(i);
		end loop;
		
		c_promptFinished;
		if(c_finished.all = '1') then
			wait;
		end if;
		report "c_finished = " & std_ulogic'image(c_finished.all);
	end process;
		

end architecture RTL;
