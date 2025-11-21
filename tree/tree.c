/* tree.c */
#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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

     errno = NoError;
     assert(parent);
     size = sizeof(struct s_node);
     n = (Node *)malloc((int)size);
     zero((int8 *)n, size);

     parent->right = (struct s_leaf *)n;
     n->tag = TagNode;
     n->up = (struct u_node *)parent;
     strncpy((char *)n->path, (char *)path, 255);

     return n;
}

Leaf *find_last_linear(Node *parent) {
    Leaf *l;

    errno = NoError;
    assert(parent);
    
   if (!parent->right)
       return (NoError);
       
   for (l = parent->right; l->right; l = l->right);
   assert(l);

   return l;
}

Leaf *create_leaf(Node *parent, int8 *key, int8 *value, int16 count) {
    Leaf *l, *new;
    int16 size;

    assert(parent);
    l = find_last(parent);

    size = sizeof(struct s_leaf);
    new = (Leaf *)malloc(size);
    assert(new);
    
    if (!l)
        parent->right = new;
    else
        l->right = new;

    zero((int8 *)new, size);
    new->tag = TagLeaf;
    new->left = (!l) ?
        (Tree *)parent:
    (Tree *)l;

    strncpy((char *)new->key, (char *)key, 127);
    new->value = (int8 *)malloc(count);
    zero(new->value, count);
    assert(new->value);
    strncpy((char *)new->value, (char*)value, count);
    new->size = count;

    return new;    
}

int main() {
  Node *n, *n2;
  Leaf *l1, *l2;
  int8 *key, *value;
  int16 *size;

  n = create_node((Node *)&root,(int8 *)"/Users");
  assert(n);
  
  n2 = create_node(n,(int8 *)"/Users/login");
  assert(n2);
  
  key = (int8 *)"stabl";
  value = (int8 *)"abc77301aa";
  size = (int16 *)strlen((char *)value);
  
  l1 = create_leaf(n2, key, value, (int16) size);
  assert(l1);

  printf("%s\n", l1->value);
  

  printf("%p %p\n", n, n2);
  free(n2);
  free(n);
  return 0;
}
