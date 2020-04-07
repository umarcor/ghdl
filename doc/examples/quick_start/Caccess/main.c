#include <malloc.h>

#include "cSharedVar.h"

extern int ghdl_main(char argc, char* argv[]);

int main(int argc, char const *argv[])
{
    char strIn[3];
    printf("Enter the Integer Array length [1-9]: ");
    fgets(strIn, sizeof strIn, stdin);
    printf("\n");
    sscanf(strIn, "%d", &sizeInt);

    if(sizeInt < 1)
        sizeInt = 1;
    
    intArray = malloc(sizeInt*sizeof(int));

    for (int i = 0; i < sizeInt; i++)
    {
        intArray[i] = i*i;
    }
    
    printf("ghdl_main return: %d\n", ghdl_main(0, NULL));
    printf("\n********************************\nghdl simulation completed.\n\n");

    for (int i = 0; i < sizeInt; i++)
    {
       printf("intArray[%d] = %d\n", i, intArray[i]);
    }

    return 0;
}


