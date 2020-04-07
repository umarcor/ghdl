#include <stdio.h>

int sizeInt;
int* getIntArrSize();

int* intArray;
int* getintArray_ptr();
void promptIndexValue();

char finishedChar;
char* getFinished_ptr();
void promptFinished();

static const char VHDL_BIT_STATE[] = { 'U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-'};

enum VHDL_BIT_CHAR {
VHDL_U = 0,
VHDL_X = 1,
VHDL_0 = 2,
VHDL_1 = 3,
VHDL_Z = 4,
VHDL_W = 5,
VHDL_L = 6,
VHDL_H = 7,
VHDL_D = 8,
};
