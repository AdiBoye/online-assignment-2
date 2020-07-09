#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))

using namespace std;

struct Node {
   int key;
   struct Node *left;
   struct Node *r;
}*r;

class avlTree {
   public:
      int height(Node *);
      int difference(Node *);
      Node *rightr_rotate(Node *);
      Node *leftl_rotate(Node *);
      Node *leftright_rotate(Node*);
      Node *rightleft_rotate(Node *);
      Node * balance(Node *);
      Node * insert(Node*, int);
      void show(Node*, int);
      avlTree() {
         r = NULL;
      }
};

int avlTree::height(Node *t) {
   int h = 0;
   if (t != NULL) {
      int leftHeight = height(t->left);
      int rightHeight = height(t->r);
      int maxHeight = max(leftHeight, rightHeight);
      h = maxHeight + 1;
   }
   return h;
}

int avlTree::difference(Node *t) {
   int leftHeight = height(t->left);
   int rightHeight = height(t->r);
   int b_factor = leftHeight - rightHeight;
   return b_factor;
}
Node *avlTree::rightr_rotate(Node *parent) {
   Node *t;
   t = parent->r;
   parent->r = t->left;
   t->left = parent;
   return t;
}

Node *avlTree::leftl_rotate(Node *parent) {
   Node *t;
   t = parent->left;
   parent->left = t->r;
   t->r = parent;
   return t;
}

Node *avlTree::leftright_rotate(Node *parent) {
   Node *t;
   t = parent->left;
   parent->left = rightr_rotate(t);
   return leftl_rotate(parent);
}

Node *avlTree::rightleft_rotate(Node *parent) {
   Node *t;
   t = parent->r;
   parent->r = leftl_rotate(t);
   return rightr_rotate(parent);
}

Node *avlTree::balance(Node *t) {
   int balFactor = difference(t);
   if (balFactor > 1) {
      if (difference(t->left) > 0)
         t = leftl_rotate(t);
      else
         t = leftright_rotate(t);
   } else if (balFactor < -1) {
      if (difference(t->r) > 0)
         t = rightleft_rotate(t);
      else
         t = rightr_rotate(t);
   }
   return t;
}

Node *avlTree::insert(Node *r, int v) {
   if (r == NULL) {
      r = new Node;
      r->key = v;
      r->left = NULL;
      r->r = NULL;
      return r;
   } else if (v< r->key) {
      r->left = insert(r->left, v);
      r = balance(r);
   } else if (v >= r->key) {
      r->r = insert(r->r, v);
      r = balance(r);
   } return r;
}

void avlTree::show(Node *p, int left) {
   int i;
   if (p != NULL) {
      show(p->r, left+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < left&& p != r; i++)
         cout << " ";
         cout << p->key;
         show(p->left, left + 1);
   }
}

int main() {

    int size;
    avlTree object;

    cout<<"Enter the total element of the tree"<<endl;
    cin>>size;

    int value;
    
    cout<<"------------------------"<<endl;

    for (int i = 0; i < size; i++) {
        cout<<"Enter value for location "<<i+1<<" and press ENTER to continue"<<endl;
        cin>>value;

        r = object.insert(r,value);
        
        object.show(r,1);

        cout<<endl;

    }

    return 0;



}