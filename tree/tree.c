/* tree.c */
#include "tree.h"
#include <assert.h>
#include <stdlib.h>

Tree root = { .n = {
    .tag = (TagRoot | TagNode),
    .up = (struct u_node *)&root,
    .left = 0,
    .right = 0,
    .path = "/"  
}};

void zero(int8 *str, int16 size) {
    int8 *p;
    int16 n;

    for (n=0, p=str;n < size; p++, n++)
        *p = 0;
      
    return;
};

Node *create_node(Node *parent, int8 *path) {
     Node *n;
     int16 size;

     assert(parent);
     size = sizeof(struct s_node);
     n = (Node *)malloc(size);
     zero((int8 *)n, size);

     parent->right = n;
     
}

int main() {
  
  printf("%p\n", (void *)&root);
  
  return 0;
}
