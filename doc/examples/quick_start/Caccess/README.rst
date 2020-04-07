.. program:: ghdl
.. _QuickStart:C_Access:

`C Access` example
=====================

The files
---------

The VHPIDIRECT method of accessing C-side variables and functions from VHDL requires these variables and functions to be declared
in a package. Each function's `foreign` attribute is set to highlight that the function has a foreign C-side definition, as per
:ref:`foreign_declarations`.

.. literalinclude:: c_access.vhdl
   :language: vhdl

Assuming, for now, that these foreign functions perform as their names indicate they should, the toplevel test bench is defined next.

.. literalinclude:: toplevel.vhdl
   :language: vhdl

Perhaps this example's flow is clearer by now: the testbench will use an integer array from C, the size of which is defined in C. 
It will use a C-side function to prompt the user to set the value for index zero and then print and adjust all of the other indices. 
Then the user is prompted to conclude the simulation or repeat the process.


The C functions and variables that GHDL accesses are kept in a separate .c/.h file:

.. literalinclude:: cSharedVar.h
   :language: c

.. literalinclude:: cSharedVar.c
   :language: c

These are also exposed to the custom entry point in main.c:

.. literalinclude:: main.c
   :language: c

Compilation
-----------

- Firstly, the HDL files must be analysed by GHDL, producing object files for each (:ref:`Analysis:command`). 
- Before the elaboration step, the object files for each `.c` file used is needed, so compile each with `gcc -c main.c -o main.o`.
- Elaborate with each C-side object file and finally the name of the toplevel entity. See :ref:`Starting_a_simulation_from_a_foreign_program` and :ref:`Linking_with_foreign_object_files`.
    - The elaboration step is only possible with a GCC or LLVM backend. See :ref:`Elaboration:command`.
- Execute the produced executable.

The compilation steps should look something like:

-- literalinclude:: build.sh
    :language: sh

.. code-block:: shell

  Hello world!

.. HINT::
   If a GCC/LLVM variant of `GHDL` is used:

   * :ref:`Analysis <Analysis:command>` generates a file, :file:`hello.o`, which is the object file corresponding to
     your `VHDL` program. This is not created with :ref:`mcode <BUILD>`. These kind of object files can be
     compiled into foreign programs (see :ref:`Linking_with_Ada`).
   * The :ref:`elaboration <Elaboration:command>` step is mandatory after running the analysis and prior to launching the
     simulation. This will generate an executable binary named :file:`hello_world`.
   * As a result, :option:`-r` is just a passthrough to the binary generated in the `elaboration`. Therefore, the
     executable can be run directly: ``./hello_world``. See :option:`-r` for more informartion.

.. HINT::

   :option:`-e` can be bypassed with :ref:`mcode <BUILD>`, since :option:`-r` actually elaborates the design and saves
   it on memory before running the simulation. But you can still use it to check for some elaboration problems.
