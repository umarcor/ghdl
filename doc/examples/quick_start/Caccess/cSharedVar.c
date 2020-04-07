#include "cSharedVar.h"

int* getIntArrSize(){
    return &sizeInt;
}

int* getIntArr_ptr(){
    return intArray;
}

void promptIndexValue(int index){
    char strIn[8];

    printf("Enter a number for index %d: ", index);
    fgets(strIn, sizeof strIn, stdin);
    printf("\n");
    sscanf(strIn, "%d", &intArray[index]);
}


char* getFinished_ptr(){
    return &finishedChar;
}

void promptFinished(){
    char strIn[3];

    printf("Conclude simulation? (Y/n): ");
    fgets(strIn, sizeof strIn, stdin);
    printf("\n");
    if(strIn[0] == 'N' || strIn[0] == 'n'){
        finishedChar = VHDL_0;
    }
    else{
        finishedChar = VHDL_1;
    }
}