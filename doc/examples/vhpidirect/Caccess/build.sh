gcc -c cSharedVar.c -o cSharedVar.o &&
gcc -c main.c -o main.o &&
ghdl-llvm -a cAccess.vhd toplevel.vhd &&
ghdl-llvm -e -Wl,main.o -Wl,cSharedVar.o toplevel
./toplevel
rm *.o work-obj*.cf toplevel
