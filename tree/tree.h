/* tree.h */
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>
#include <errno.h>

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

struct s_node {
  struct u_node *up;
  struct s_node *letf;
  struct s_leaf *right;
  int8 path[256];
};
typedef struct s_node Node;

struct s_leaf {
  union u_tree *left;
  struct s_leaf *right;  
  int8 key[128];
  int8 *value;
  int16 size;
};
typedef struct s_leaf Leaf;
