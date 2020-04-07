.. program:: ghdl
.. _QuickStart:C_Access:

`C Access` example
=====================

The files
---------

The VHPIDIRECT method of accessing C-side variables and functions from VHDL requires these variables and functions to be declared
in a package. Each function's `foreign` attribute is set to highlight that the function has a foreign C-side definition, as per
:ref:`foreign_declarations`. 

This example starts with :file:`c_access.vhdl`:

.. literalinclude:: cAccess.vhd
   :language: vhdl

Assuming, for now, that these foreign functions perform as their names indicate they should, the toplevel test bench is defined next (:file:`toplevel.vhdl`):

.. literalinclude:: toplevel.vhd
   :language: vhdl

Perhaps this example's flow is clearer by now: the testbench will use an integer array from C, the size of which is defined in C. 
It will use a C-side function to prompt the user to set the value for index zero and then print and adjust all of the other indices. 
Then the user is prompted to conclude the simulation or repeat the process.


The C functions and variables that GHDL accesses are kept in a separate header/code pair. :file:`cSharedVar.h`:

.. literalinclude:: cSharedVar.h
   :language: c

And :file:`cSharedVar.c`:

.. literalinclude:: cSharedVar.c
   :language: c


These are also exposed to the custom entry point in :file:`main.c`:

.. literalinclude:: main.c
   :language: c

It is seen that the array's length is established, and its contents filled with square numbers, before the GHDL simulation happens. 
After that, the array is read out.

Compilation
-----------

- Firstly, the HDL files must be analysed by GHDL, producing object files for each (:ref:`Analysis:command`). 
- Before the elaboration step, the object files of all `.c` files being used are needed, so compile each with `gcc -c main.c -o main.o`.
- Elaborate with each C-side object file and finally the name of the toplevel entity. See :ref:`Starting_a_simulation_from_a_foreign_program` and :ref:`Linking_with_foreign_object_files`.
    - The elaboration step is only possible with a GCC or LLVM backend. See :ref:`Elaboration:command`.
- Execute the produced executable.

The compilation steps should look something like :file:`build.sh`:

.. literalinclude:: build.sh
    :language: sh