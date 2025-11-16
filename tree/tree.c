/* tree.c */
#include "tree.h"

Tree root = { .n = {
    .tag = (TagRoot | TagNode),
    .up = (struct u_node *)&root,
    .left = 0,
    .right = 0,
    .path = "/"  
}};

int main() {
  
  printf("%p\n", (void *)&root);
  
  return 0;
}
