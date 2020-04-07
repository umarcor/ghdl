library ieee;
use ieee.std_logic_1164.all;

package cAccess is

	type int_ptr is access integer; -- represented C-side with int
	function c_intArrSize_ptr return int_ptr; -- represented C-side with int*
		attribute foreign of c_intArrSize_ptr :
		function is "VHPIDIRECT getIntArrSize"; -- getIntArrSize is the C-side function name

	shared variable c_sizeInt : int_ptr := c_intArrSize_ptr;

	type int_arr is array(0 to c_sizeInt.all-1) of integer;
	type int_arr_ptr is access int_arr; -- represented C-side with int*
	
	
	function c_intArr_ptr return int_arr_ptr;
		attribute foreign of c_intArr_ptr :
		function is "VHPIDIRECT getIntArr_ptr";
	procedure c_promptIndexValue(index: integer);
		attribute foreign of c_promptIndexValue :
		procedure is "VHPIDIRECT promptIndexValue";
		
	shared variable c_intArr : int_arr_ptr := c_intArr_ptr;	
	
	type char_ptr is access std_ulogic; -- represented C-side with char
	function c_finished_ptr return char_ptr;
		attribute foreign of c_finished_ptr :
		function is "VHPIDIRECT getFinished_ptr";
	
	procedure c_promptFinished;
		attribute foreign of c_promptFinished :
		procedure is "VHPIDIRECT promptFinished";

	shared variable c_finished : char_ptr := c_finished_ptr;	
end package cAccess;

package body cAccess is

	function c_intArrSize_ptr return int_ptr is
	begin
		assert false report "c_intArrSize_ptr VHPI" severity failure;
	end c_intArrSize_ptr;


	function c_intArr_ptr return int_arr_ptr is
	begin
		assert false report "c_intArr_ptr VHPI" severity failure;
	end c_intArr_ptr;
	procedure c_promptIndexValue(index: integer) is
	begin
		assert false report "c_promptIndexValue VHPI" severity failure;
	end c_promptIndexValue;

	function c_finished_ptr return char_ptr is
	begin
		assert false report "c_finished_ptr VHPI" severity failure;
	end c_finished_ptr;
	procedure c_promptFinished is
	begin
		assert false report "c_promptFinished VHPI" severity failure;
	end c_promptFinished;
end package body cAccess;
