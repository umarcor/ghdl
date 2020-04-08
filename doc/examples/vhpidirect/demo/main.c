#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include <ghdl.h>

typedef struct rec_t {
  char    r_char;
  int32_t r_int;
} rec_t;

typedef enum {standby, start, busy, done} enum_t;

void testCinterface(
  char     v_logic,
  char     v_ulogic,
  char     v_char,
  int32_t  v_int,
  uint32_t v_nat,
  uint32_t v_pos,
  double   v_real,
  bool     v_bool,
  bool     v_bit,
  int64_t  v_time,
  rec_t*   v_rec,
  uint8_t  v_enum,
  ghdl_NaturalDimArr_t* v_str,
  ghdl_NaturalDimArr_t* v_vec_int,
  ghdl_NaturalDimArr_t* v_vec_real,
  ghdl_NaturalDimArr_t* v_vec_bool,
  ghdl_NaturalDimArr_t* v_vec_bit,
  ghdl_NaturalDimArr_t* v_vec_phy,
  ghdl_NaturalDimArr_t* v_vec_rec,
  ghdl_NaturalDimArr_t* v_vec_enum,
  ghdl_NaturalDimArr_t* v_2vec_real,
  ghdl_Natural2DimArr_t* v_mat_int
) {
  assert(v_logic == HDL_H);
  printf("v_logic  : %c\n", HDL_LOGIC_STATE[v_logic]);

  assert(v_ulogic == HDL_Z);
  printf("v_ulogic : %c\n", HDL_LOGIC_STATE[v_ulogic]);

  assert(v_char == 'k');
  printf("v_char : %c\n", v_char);

  assert(v_int == -6);
  printf("v_int  : %d\n", v_int);

  assert(v_nat == 9);
  printf("v_nat  : %d\n", v_nat);

  assert(v_pos == 3);
  printf("v_pos  : %d\n", v_pos);

  assert(v_real == 3.34);
  printf("v_real : %f\n", v_real);

  assert(v_bool == true);
  printf("v_bool : %d\n", v_bool);

  assert(v_bit == true);
  printf("v_bit  : %d\n", v_bit);

  assert(v_time == 20e6);
  printf("v_time : %ld\n", v_time);

  assert(v_rec != NULL);
  assert(v_rec->r_char == 'y');
  assert(v_rec->r_int == 5);
  printf("v_rec  : %p %c %d\n", v_rec, v_rec->r_char, v_rec->r_int);

  assert(v_enum == busy);
  printf("v_enum : %d %d\n", v_enum, busy);

  char* str = ghdlToString(v_str);
  printf("v_str  : %p '%s' [%ld]\n", v_str->array, str, strlen(str));

  int* len = malloc(2 * sizeof(int));

  int32_t* vec_int;
  ghdlToArray(v_vec_int, (void**)&vec_int, len, 1);
  assert(vec_int[0] == 11);
  assert(vec_int[1] == 22);
  assert(vec_int[2] == 33);
  assert(vec_int[3] == 44);
  assert(vec_int[4] == 55);
  printf("v_vec_int  : %p [%d]\n", vec_int, len[0]);

  double* vec_real;
  ghdlToArray(v_vec_real, (void**)&vec_real, len, 1);
  assert(vec_real[0] == 0.5);
  assert(vec_real[1] == 1.75);
  assert(vec_real[2] == 3.33);
  assert(vec_real[3] == -0.125);
  assert(vec_real[4] == -0.67);
  assert(vec_real[5] == -2.21);
  printf("v_vec_real : %p [%d]\n", vec_real, len[0]);

  bool* vec_bool;
  ghdlToArray(v_vec_bool, (void**)&vec_bool, len, 1);
  assert(vec_bool[0] == 0);
  assert(vec_bool[1] == 1);
  assert(vec_bool[2] == 1);
  assert(vec_bool[3] == 0);
  printf("v_vec_bool : %p [%d]\n", vec_bool, len[0]);

  bool* vec_bit;
  ghdlToArray(v_vec_bit, (void**)&vec_bit, len, 1);
  assert(vec_bit[0] == 1);
  assert(vec_bit[1] == 0);
  assert(vec_bit[2] == 1);
  assert(vec_bit[3] == 0);
  printf("v_vec_bit  : %p [%d]\n", vec_bit, len[0]);

  int64_t* vec_phy;
  ghdlToArray(v_vec_phy, (void**)&vec_phy, len, 1);
  assert(vec_phy[0] == 1e6);
  assert(vec_phy[1] == 50e3);
  assert(vec_phy[2] == 1.34e9);
  printf("v_vec_phy  : %p [%d]\n", vec_phy, len[0]);

  rec_t* vec_rec;
  ghdlToArray(v_vec_rec, (void**)&vec_rec, len, 1);
  assert(vec_rec[0].r_char == 'x');
  assert(vec_rec[0].r_int == 17);
  assert(vec_rec[1].r_char == 'y');
  assert(vec_rec[1].r_int == 25);
  printf("v_vec_rec  : %p [%d]\n", vec_rec, len[0]);

  uint8_t* vec_enum;
  ghdlToArray(v_vec_enum, (void**)&vec_enum, len, 1);
  assert(vec_enum[0] == start);
  assert(vec_enum[1] == busy);
  assert(vec_enum[2] == standby);
  printf("v_vec_enum : %p [%d]\n", vec_enum, len[0]);

  double* vec2_real_base;
  ghdlToArray(v_2vec_real, (void**)&vec2_real_base, len, 2);
  double (*vec2_real)[len[0]] = (double(*)[len[0]])vec2_real_base;
  assert(vec2_real[0][0] == 0.1);
  assert(vec2_real[0][1] == 0.25);
  assert(vec2_real[0][2] == 0.5);
  assert(vec2_real[1][0] == 3.33);
  assert(vec2_real[1][1] == 4.25);
  assert(vec2_real[1][2] == 5.0);
  printf("v_2vec_real : %p [%d, %d]\n", vec_enum, len[1], len[0]);

  printf("\nVerify GHDL Matrix in C\n");
  //print2d(v_mat_int);
  int* len2 = malloc(2 * sizeof(int));

  int32_t* mat_int;
  ghdlToArray(v_mat_int, (void**)&mat_int, len2, 2);
  for (int i = 0; i < len2[1]; i++)
  {
    for (int j = 0; j < len2[0]; j++)
    { 
      printf("C assert: %d == (val: %d) @ [%d,%d](%d)\n", 11*(i*len2[0]+j+1), mat_int[i*len2[1]+j], i, j, i*len2[1]+j);
      assert(mat_int[i*len2[0]+j] == 11*(i*len2[0]+j+1));
    }
  }
  printf("v_mat_int  : %p [%d,%d]\n\n", mat_int, len2[0], len2[1]);
}

void getString(ghdl_NaturalDimArr_t* ptr) {
  *ptr = ghdlFromString("HELLO WORLD");
}

void getIntVec(ghdl_NaturalDimArr_t* ptr) {
  int32_t vec[6] = {11, 22, 33, 44, 55};
  int32_t len[1] = {5};
  int x;
  *ptr = ghdlFromArray(vec, len, 1);
  printf("\n1D Array values [%d]:\n", len[0]);
  for ( x=0 ; x<len[0] ; x++ ) {
    printf("[%d]: %d\n", x, vec[x]);
  }
}

int getFlatArrayIndex(int* dimIndex, int* lens, int dims){
  if(dims == 1){
    return dimIndex[0];
  }
  else{
    return dimIndex[dims-1] + (lens[dims-1]*getFlatArrayIndex(dimIndex, lens, dims-1));
  }
}

void getIntMat(ghdl_Natural2DimArr_t* ptr){
  int32_t mat[2][3];
  int32_t len[2] = {2, 3};
  int x, y;
  for ( x=0 ; x<len[0] ; x++ ) {
    for ( y=0 ; y<len[1] ; y++ ) {
      int ind[] = {x, y};
      int flatIndex = getFlatArrayIndex(ind, len, 2);
      mat[x][y] = 11*(flatIndex+1);
    }
  }
  *ptr = ghdlFromArray2d(mat, len, 2);
  printf("\n2D Array values [%d,%d]:\n", len[0], len[1]);
  for ( x=0 ; x<len[0] ; x++ ) {
    for ( y=0 ; y<len[1] ; y++ ) {
      printf("mat[%d][%d] = %d\t", x, y, mat[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

ghdl_AccNaturalDimArr_t* getLine() {
  return ghdlAccFromString("HELLO WORLD");
}

int getLogicIntValue(char logic){
  return 0 + logic;
}