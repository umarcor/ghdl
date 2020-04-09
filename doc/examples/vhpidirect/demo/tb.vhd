use std.textio.line;

library ieee;
use ieee.std_logic_1164.all;

entity tb is
end;

architecture arch of tb is

  type rec_t is record
    r_char: character;
    r_int : integer;
  end record;

  type enum_t is (standby, start, busy, done);

  type int_vec_t is array(natural range <>) of integer;
  type real_vec_t is array(natural range <>) of real;
  type bool_vec_t is array(natural range <>) of boolean;
  type time_vec_t is array(natural range <>) of time;
  type rec_vec_t is array(natural range <>) of rec_t;
  type enum_vec_t is array(natural range <>) of enum_t;

  type real_2vec_t is array (natural range <>, natural range <>) of real;

  type int_2vec_t is array(natural range <>, natural range <>) of integer;
  type int_3vec_t is array(natural range <>, natural range <>, natural range <>) of integer;
begin
  process

    procedure testCinterface(
      v_logic     : std_logic   := 'H';
      v_ulogic    : std_ulogic  := 'Z';
      v_char      : character   := 'k';
      v_int       : integer     := -6;
      v_nat       : natural     := 9;
      v_pos       : positive    := 3;
      v_real      : real        := 3.34;
      v_bool      : boolean     := true;
      v_bit       : bit         := '1';
      v_time      : time        := 20 ns;
      v_rec       : rec_t       := ('y', 5);
      v_enum      : enum_t      := busy;
      v_str       : string      := "hellostr";
      v_vec_int   : int_vec_t   := (11, 22, 33, 44, 55);
      v_vec_real  : real_vec_t  := (0.5, 1.75, 3.33, -0.125, -0.67, -2.21);
      v_vec_bool  : bool_vec_t  := (false, true, true, false);
      v_vec_bit   : bit_vector  := ('1', '0', '1', '0');
      v_vec_time  : time_vec_t  := (1 ns, 50 ps, 1.34 us);
      v_vec_rec   : rec_vec_t   := (('x', 17),('y', 25));
      v_vec_enum  : enum_vec_t  := (start, busy, standby);
      v_2vec_real : real_2vec_t := ((0.1, 0.25, 0.5),(3.33, 4.25, 5.0));
      v_mat_int   : int_2vec_t  := ((11, 22, 33), (44, 55, 66));
      v_3d_int   : int_3vec_t   := ( ((11, 22, 33), (44, 55, 66)), ((77, 88, 99), (110, 121, 132)) )
    ) is
    begin assert false report "VHPIDIRECT testCinterface" severity failure; end;
    attribute foreign of testCinterface : procedure is "VHPIDIRECT testCinterface";

    function getString return string is
    begin assert false report "VHPIDIRECT getString" severity failure; end;
    attribute foreign of getString : function is "VHPIDIRECT getString";

    function getIntVec return int_vec_t is
    begin assert false report "VHPIDIRECT getIntVec" severity failure; end;
    attribute foreign of getIntVec : function is "VHPIDIRECT getIntVec";

    function getIntMat return int_2vec_t is
    begin assert false report "VHPIDIRECT getIntMat" severity failure; end;
    attribute foreign of getIntMat : function is "VHPIDIRECT getIntMat";

    function getInt3d return int_3vec_t is
    begin assert false report "VHPIDIRECT getInt3d" severity failure; end;
    attribute foreign of getInt3d : function is "VHPIDIRECT getInt3d";

    function getLine return line is
    begin assert false report "VHPIDIRECT getLine" severity failure; end;
    attribute foreign of getLine : function is "VHPIDIRECT getLine";

    constant g_str: string := getString;
    constant g_int_vec: int_vec_t := getIntVec;
    constant g_int_mat: int_2vec_t := getIntMat;
    constant g_int_3d: int_3vec_t := getInt3d;

    variable g_line: line := getLine;

    function getLogicValue(logic : std_logic) return integer is
    begin assert false report "VHPIDIRECT getLogicValue" severity failure; end;
    attribute foreign of getLogicValue : function is "VHPIDIRECT getLogicIntValue";

    function getUlogicValue(logic : std_ulogic) return integer is
    begin assert false report "VHPIDIRECT getUlogicValue" severity failure; end;
    attribute foreign of getUlogicValue : function is "VHPIDIRECT getLogicIntValue";

    function getBitValue(bitVal : bit) return integer is
    begin assert false report "VHPIDIRECT getBitValue" severity failure; end;
    attribute foreign of getBitValue : function is "VHPIDIRECT getLogicIntValue";

    procedure freeCPointers is
    begin assert false report "VHPIDIRECT freeCPointers" severity failure; end;
    attribute foreign of freeCPointers : procedure is "VHPIDIRECT freePointers";
    
    variable spareInt: integer;
  begin

    testCinterface(
      v_logic     => 'H',
      v_ulogic    => 'Z',
      v_char      => 'k',
      v_int       => -6,
      v_nat       => 9,
      v_pos       => 3,
      v_real      => 3.34,
      v_bool      => true,
      v_bit       => '1',
      v_time      => 20 ns,
      v_rec       => ('y', 5),
      v_enum      => busy,
      v_str       => "hellostr",
      v_vec_int   => (11, 22, 33, 44, 55),
      v_vec_real  => (0.5, 1.75, 3.33, -0.125, -0.67, -2.21),
      v_vec_bool  => (false, true, true, false),
      v_vec_bit   => ('1', '0', '1', '0'),
      v_vec_time  => (1 ns, 50 ps, 1.34 us),
      v_vec_rec   => (('x', 17),('y', 25)),
      v_vec_enum  => (start, busy, standby),
      v_2vec_real => ((0.1, 0.25, 0.5),(3.33, 4.25, 5.0)),
      v_mat_int   =>  ((11, 22, 33), (44, 55, 66)),
      v_3d_int    => ( ((11, 22, 33), (44, 55, 66)), ((77, 88, 99), (110, 121, 132)) )
    );

    report "g_str'length: " & integer'image(g_str'length) severity note;
    if g_str'length /= 0 then
      report "g_str: " & g_str severity note;
    end if;
    report "string: " & getString severity note;--g_str results from calling getString(), calling it again means a malloc'd pointer can be lost.

    report "g_int_vec'length: " & integer'image(g_int_vec'length) severity note;
    for x in g_int_vec'range loop
      report integer'image(x) & ": " & integer'image(g_int_vec(x)) severity note;
      assert g_int_vec(x) = 11*(x+1) severity warning;
    end loop;

    report "g_line: " & g_line.all severity note;
    report "getLine: " & getLine.all severity note;--g_line results from calling getLine(), calling it again means a malloc'd pointer can be lost.
    assert getLine.all = "HELLO WORLD" severity failure;

    assert 0 = getLogicValue('U') severity error;
    assert 1 = getLogicValue('X') severity error;
    assert 2 = getLogicValue('0') severity error;
    assert 3 = getLogicValue('1') severity error;
    assert 4 = getLogicValue('Z') severity error;
    assert 5 = getLogicValue('W') severity error;
    assert 6 = getLogicValue('L') severity error;
    assert 7 = getLogicValue('H') severity error;
    assert 8 = getLogicValue('-') severity error;

    assert 0 = getUlogicValue('U') severity error;
    assert 1 = getUlogicValue('X') severity error;
    assert 2 = getUlogicValue('0') severity error;
    assert 3 = getUlogicValue('1') severity error;
    assert 4 = getUlogicValue('Z') severity error;
    assert 5 = getUlogicValue('W') severity error;
    assert 6 = getUlogicValue('L') severity error;
    assert 7 = getUlogicValue('H') severity error;
    assert 8 = getUlogicValue('-') severity error;

    assert 0 = getBitValue('0') severity error;
    assert 1 = getBitValue('1') severity error;
    
    spareInt := 0;
    report "g_int_mat'length: " & integer'image(g_int_mat'length) severity note;
    for i in g_int_mat'range(1) loop
      for j in g_int_mat'range(2) loop
        spareInt := spareInt + 1;
        report "Asserting Mat [" & integer'image(i) & "," & integer'image(j) & "]: " & integer'image(g_int_mat(i, j)) severity note;
        assert g_int_mat(i, j) = 11*spareInt severity error;
      end loop ;
    end loop ;

    spareInt := 0;
    report "g_int_3d'length: " & integer'image(g_int_3d'length) severity note;
    for i in g_int_3d'range(1) loop
      for j in g_int_3d'range(2) loop
        for k in g_int_3d'range(3) loop
          spareInt := spareInt + 1;
          report "Asserting 3D [" & integer'image(i) & "," & integer'image(j) & "," & integer'image(k) & "]: " & integer'image(g_int_3d(i, j, k)) severity note;
          assert g_int_3d(i, j, k) = 11*spareInt severity error;
          end loop;
      end loop ;
    end loop ;

    freeCPointers;
    report "No errors/failures. Concluding testbench." severity note;
    wait;
  end process;
end;
