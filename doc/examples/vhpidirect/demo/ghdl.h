#ifndef GHDL_TYPES_H
#define GHDL_TYPES_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Range/bounds of a dimension of an unconstrained array with dimensions of type 'natural'
typedef struct {
  int32_t left;
  int32_t right;
  int32_t dir;
  int32_t len;
} range_t;

// Unconstrained array with dimensions of type 'natural'
typedef struct {
  void* array;
  range_t* bounds;
} ghdl_NaturalDimArr_t;

// Access to an unconstrained array with 1 dimension of type 'natural'
typedef struct {
  range_t range;
  uint8_t array[];
} ghdl_AccNaturalDimArr_t;

/*
*  Print custom types
*/

void printAttributes(ghdl_NaturalDimArr_t* ptr, int dims) {
  printf("array: %p\n", ptr->array);
  printf("bounds: %p\n", ptr->bounds);
  int i;
  for(i = 0; i < dims; i++){
    printf("bounds[%d].left: %d\n", i+1, ptr->bounds[i].left);
    printf("bounds[%d].right: %d\n", i+1, ptr->bounds[i].right);
    printf("bounds[%d].dir: %d\n", i+1, ptr->bounds[i].dir);
    printf("bounds[%d].len: %d\n", i+1, ptr->bounds[i].len);
  }
}

/*
*  Convert a fat pointer of an unconstrained string, to a (null terminated) C string
*/

// @umarcor
char* ghdlToString(ghdl_NaturalDimArr_t* ptr) {
  assert(ptr != NULL);
  assert(ptr->bounds != NULL);
  int len = ptr->bounds[0].len;
  char* str = malloc(sizeof(char) * len + 1);
  strncpy(str, ptr->array, len);
  str[len] = '\0';
  return str;
}

// In the prototype, Bradley declares a value instead of a reference. Why?

// @bradleyharden
/*
char* ghdl_array_to_string(array_t array) {
  // Add a null character, because GHDL strings are not null-terminated
  char *string = malloc(array.range->len + 1);
  strncpy(string, array.array, array.range->len);
  string[array.range->len] = '\0';
  return string;
}
*/

/*
*  Convert a fat pointer of an uncontrained array with (up to 3) dimensions of type 'natural', to C types
*/

void ghdlToArray(ghdl_NaturalDimArr_t* ptr, void** vec, int* len, int num) {
  assert(ptr != NULL);
  assert(ptr->bounds != NULL);
  *vec = ptr->array;

  for (int i = 0; i < num; i++)
  {
    len[i] = ptr->bounds[num-i-1].len;
  }
}

/*
*  Convert a (null terminated) C string, to a fat pointer of an unconstrained string
*/

// @umarcor
/*
ghdl_NaturalDimArr_t* ghdlFromString(char* str) {
  uint32_t len = strlen(str);
  ghdl_NaturalDimArr_t* ptr = malloc(sizeof(ghdl_NaturalDimArr_t));
  ptr->array = malloc(sizeof(char) * len);
  strncpy((char*)(ptr->array), str, len);
  ptr->bounds = malloc(sizeof(bounds_t));
  bounds_t* b = ptr->bounds;
  b->dim_1.left = 1;
  b->dim_1.right = len;
  b->dim_1.dir = 0;
  b->dim_1.len = len;
  return ptr;
}
*/

// Again, the prototype I had (above) returns a reference instead of a value (Bradley's below)

// @bradleyharden
ghdl_NaturalDimArr_t ghdlFromString(char *string) {
  range_t *range = malloc(sizeof(range_t));
  assert(range != NULL);
  uint32_t len = strlen(string);
  range->left = 1;
  range->right = len;
  range->dir = 0;
  range->len = len;
  // Don't bother copying the string, because GHDL will do that anyway
  return (ghdl_NaturalDimArr_t){.array=string, .bounds=range};
}

// @RocketRoss
/*
*   Helper to setup the bounds_t for ghdlFromArray
*/

void ghdlSetRange(range_t* r, int len, bool reversed){
  if(!reversed){//to
    r->left = 0;
    r->right = len-1;
    r->dir = 0;
    r->len = len;
  }
  else{//downto
    r->left = len-1;
    r->right = 0;
    r->dir = 1;
    r->len = len;
  }
}

// @RocketRoss
/*
*  Convert C types representing an unconstrained array with a dimension of type 'natural', to a fat pointer
*/

ghdl_NaturalDimArr_t ghdlFromArray(void* vec, int* len, int dims) {
  range_t* b = malloc(sizeof(range_t)*dims);
  assert(b != NULL);

  int totalSize = 1;
  for (int i = 0; i < dims; i++)
  {
    totalSize *= len[i];
    ghdlSetRange(b+i, len[i], false);
  }
  
  void* a = malloc(sizeof(int)*totalSize);
  memmove(a, vec, sizeof(int)*totalSize);
  vec = a;
  return (ghdl_NaturalDimArr_t){.array= a, .bounds=b};
}

/*
*  Convert an access to an unconstrained string, to a (null terminated) C string
*/

char* ghdlAccToString(ghdl_AccNaturalDimArr_t *line) {
  // Add a null character, because GHDL strings are not null-terminated
  char *string = malloc(line->range.len + 1);
  strncpy(string, line->array, line->range.len);
  string[line->range.len] = '\0';
}

/*
*  Convert C types representing an unconstrained array with a dimension of type 'natural', to an access
*/

// TODO: support 2 and 3 dimensions
ghdl_AccNaturalDimArr_t* ghdlAccFromArray(uint32_t length, size_t bytes) {
  ghdl_AccNaturalDimArr_t *access = malloc(sizeof(ghdl_AccNaturalDimArr_t) + length * bytes);
  assert(access != NULL);
  access->range.left = 0;
  access->range.right = length - 1;
  access->range.dir = 0;
  access->range.len = length;
  return access;
}

/*
*  Convert a (null terminated) C string, to an access to an unconstrained string
*/

/*
// @umarcor
ghdl_AccNaturalDimArr_t* ghdlLineFromString(char *str) {
  uint32_t len = strlen(str);
  ghdl_AccNaturalDimArr_t *line = malloc(sizeof(ghdl_AccNaturalDimArr_t) + sizeof(char) * len);
  line->bounds.left = 1;
  line->bounds.right = len;
  line->bounds.dir = 0;
  line->bounds.len = len;
  strncpy(line->array, str, len);
  return line;
}
*/

// @bradleyharden
ghdl_AccNaturalDimArr_t* ghdlAccFromString(char *string) {
  uint32_t length = strlen(string);
  ghdl_AccNaturalDimArr_t *line = ghdlAccFromArray(length, 1);
  // New access objects default to numbering from 0,
  // but VHDL strings must be numbered from 1
  line->range.left++;
  line->range.right++;
  // Don't copy the null termination
  strncpy(line->array, string, length);
  return line;
}

/*  
*   Handle C char for the appropriate values in std_ulogic and std_logic.
*/

// @RocketRoss
static const char HDL_LOGIC_STATE[] = { 'U', 'X', '0', '1', 'Z', 'W', 'L', 'H', '-'};

enum HDL_LOGIC_CHAR {
HDL_U = 0,
HDL_X = 1,
HDL_0 = 2,
HDL_1 = 3,
HDL_Z = 4,
HDL_W = 5,
HDL_L = 6,
HDL_H = 7,
HDL_D = 8,
};

#endif
