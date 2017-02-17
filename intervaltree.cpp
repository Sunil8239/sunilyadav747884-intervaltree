#include <iostream>
 
using namespace std;
 
struct Interval
{
        int low, high;
};
 
struct IntTreeNode
{
        Interval *i; 
        int max;
        IntTreeNode *left, *right,*parent;
        char color;
};
class RBtree
{
      IntTreeNode*root;
      IntTreeNode *q;
   public :
      RBtree()
      {
              q=NULL;
              root=NULL;
      }
      void insert();
      void insertfix(IntTreeNode *);
      void leftrotate(IntTreeNode *);
      void rightrotate(IntTreeNode *);
      void del();
      IntTreeNode* successor(IntTreeNode *);
      void delfix(IntTreeNode *);
      void disp();
      void display( IntTreeNode *);
      void search();
};

 
 void RBtree::insert()
{
     int z,i=0;
     cout<<"\nEnter key of the node to be inserted: ";
     cin>>z;
     IntTreeNode *p,*q;
     IntTreeNode *t=new IntTreeNode;
     t->max=z;
     t->left=NULL;
     t->right=NULL;
     t->color='r';
     p=root;
     q=NULL;
     if(root==NULL)
     {
           root=t;
           t->parent=NULL;
     }
     else
     {
         while(p!=NULL)
         {
              q=p;
              if(p->max<t->max)
                  p=p->right;
              else
                  p=p->left;
         }
         t->parent=q;
         if(q->max<t->max)
              q->right=t;
         else
              q->left=t;
     }
     insertfix(t);
}
void RBtree::insertfix(IntTreeNode *t)
{
     IntTreeNode *u;
     if(root==t)
     {
         t->color='b';
         return;
     }
     while(t->parent!=NULL&&t->parent->color=='r')
     {
           IntTreeNode *g=t->parent->parent;
           if(g->left==t->parent)
           {
                        if(g->right!=NULL)
                        {
                              u=g->right;
                              if(u->color=='r')
                              {
                                   t->parent->color='b';
                                   u->color='b';
                                   g->color='r';
                                   t=g;
                              }
                        }
                        else
                        {
                            if(t->parent->right==t)
                            {
                                 t=t->parent;
                                 leftrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            rightrotate(g);
                        }
           }
           else
           {
                        if(g->left!=NULL)
                        {
                             u=g->left;
                             if(u->color=='r')
                             {
                                  t->parent->color='b';
                                  u->color='b';
                                  g->color='r';
                                  t=g;
                             }
                        }
                        else
                        {
                            if(t->parent->left==t)
                            {
                                   t=t->parent;
                                   rightrotate(t);
                            }
                            t->parent->color='b';
                            g->color='r';
                            leftrotate(g);
                        }
           }
           root->color='b';
     }
}

void RBtree::del()
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree." ;
           return ;
     }
     int x;
     cout<<"\nEnter the key of the node to be deleted: ";
     cin>>x;
     IntTreeNode *p;
     p=root;
     IntTreeNode *y=NULL;
     IntTreeNode *q=NULL;
     int found=0;
     while(p!=NULL&&found==0)
     {
           if(p->max==x)
               found=1;
           if(found==0)
           {
                 if(p->max<x)
                    p=p->right;
                 else
                    p=p->left;
           }
     }
     if(found==0)
     {
            cout<<"\nElement Not Found.";
            return ;
     }
     else
     {
         cout<<"\nDeleted Element: "<<p->max;
         cout<<"\nColour: ";
         if(p->color=='b')
     cout<<"Black\n";
    else
     cout<<"Red\n";

         if(p->parent!=NULL)
               cout<<"\nParent: "<<p->parent->max;
         else
               cout<<"\nThere is no parent of the node.  ";
         if(p->right!=NULL)
               cout<<"\nRight Child: "<<p->right->max;
         else
               cout<<"\nThere is no right child of the node.  ";
         if(p->left!=NULL)
               cout<<"\nLeft Child: "<<p->left->max;
         else
               cout<<"\nThere is no left child of the node.  ";
         cout<<"\nNode Deleted.";
         if(p->left==NULL||p->right==NULL)
              y=p;
         else
              y=successor(p);
         if(y->left!=NULL)
              q=y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q=NULL;
         }
         if(q!=NULL)
              q->parent=y->parent;
         if(y->parent==NULL)
              root=q;
         else
         {
             if(y==y->parent->left)
                y->parent->left=q;
             else
                y->parent->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->max=y->max;
         }
         if(y->color=='b')
             delfix(q);
     }
}

void RBtree::delfix(IntTreeNode *p)
{
    IntTreeNode *s;
    while(p!=root&&p->color=='b')
    {
          if(p->parent->left==p)
          {
                  s=p->parent->right;
                  if(s->color=='r')
                  {
                         s->color='b';
                         p->parent->color='r';
                         leftrotate(p->parent);
                         s=p->parent->right;
                  }
                  if(s->right->color=='b'&&s->left->color=='b')
                  {
                         s->color='r';
                         p=p->parent;
                  }
                  else
                  {
                      if(s->right->color=='b')
                      {
                             s->left->color=='b';
                             s->color='r';
                             rightrotate(s);
                             s=p->parent->right;
                      }
                      s->color=p->parent->color;
                      p->parent->color='b';
                      s->right->color='b';
                      leftrotate(p->parent);
                      p=root;
                  }
          }
          else
          {
                  s=p->parent->left;
                  if(s->color=='r')
                  {
                        s->color='b';
                        p->parent->color='r';
                        rightrotate(p->parent);
                        s=p->parent->left;
                  }
                  if(s->left->color=='b'&&s->right->color=='b')
                  {
                        s->color='r';
                        p=p->parent;
                  }
                  else
                  {
                        if(s->left->color=='b')
                        {
                              s->right->color='b';
                              s->color='r';
                              leftrotate(s);
                              s=p->parent->left;
                        }
                        s->color=p->parent->color;
                        p->parent->color='b';
                        s->left->color='b';
                        rightrotate(p->parent);
                        p=root;
                  }
          }
       p->color='b';
       root->color='b';
    }
}

// A function to create a new interval search tree node
IntTreeNode * newNode(Interval i)
{
    IntTreeNode *temp = new IntTreeNode;
    temp->i = new Interval(i);
    temp->max = i.high;
    temp->left = temp->right = NULL;
};
void RBtree::leftrotate(IntTreeNode *p)
{
     if(p->right==NULL)
           return ;
     else
     {
           IntTreeNode *y=p->right;
           if(y->left!=NULL)
           {
                  p->right=y->left;
                  y->left->parent=p;
           }
           else
                  p->right=NULL;
           if(p->parent!=NULL)
                y->parent=p->parent;
           if(p->parent==NULL)
                root=y;
           else
           {
               if(p==p->parent->left)
                       p->parent->left=y;
               else
                       p->parent->right=y;
           }
           y->left=p;
           p->parent=y;
     }
}
void RBtree::rightrotate(IntTreeNode *p)
{
     if(p->left==NULL)
          return ;
     else
     {
         IntTreeNode *y=p->left;
         if(y->right!=NULL)
         {
                  p->left=y->right;
                  y->right->parent=p;
         }
         else
                 p->left=NULL;
         if(p->parent!=NULL)
                 y->parent=p->parent;
         if(p->parent==NULL)
               root=y;
         else
         {
             if(p==p->parent->left)
                   p->parent->left=y;
             else
                   p->parent->right=y;
         }
         y->right=p;
         p->parent=y;
     }
}

IntTreeNode* RBtree::successor(IntTreeNode *p)
{
      IntTreeNode *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

void RBtree::disp()
{
     display(root);
}
void RBtree::display(IntTreeNode *p)
{
     if(root==NULL)
     {
          cout<<"\nEmpty Tree.";
          return ;
     }
     if(p!=NULL)
     {
                cout<<"\n\t NODE: ";
                cout<<"\n Key: "<<p->max;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->max;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->max;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->max;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;
    if(p->left)
    {
                 cout<<"\n\nLeft:\n";
     display(p->left);
    }
    /*else
     cout<<"\nNo Left Child.\n";*/
    if(p->right)
    {
     cout<<"\n\nRight:\n";
                 display(p->right);
    }
    /*else
     cout<<"\nNo Right Child.\n"*/
     }
}
void RBtree::search()
{
     if(root==NULL)
     {
           cout<<"\nEmpty Tree\n" ;
           return  ;
     }
     int x;
     cout<<"\n Enter key of the node to be searched: ";
     cin>>x;
     IntTreeNode *p=root;
     int found=0;
     while(p!=NULL&& found==0)
     {
            if(p->max==x)
                found=1;
            if(found==0)
            {
                 if(p->max<x)
                      p=p->right;
                 else
                      p=p->left;
            }
     }
     if(found==0)
          cout<<"\nElement Not Found.";
     else
     {
                cout<<"\n\t FOUND NODE: ";
                cout<<"\n Key: "<<p->max;
                cout<<"\n Colour: ";
    if(p->color=='b')
     cout<<"Black";
    else
     cout<<"Red";
                if(p->parent!=NULL)
                       cout<<"\n Parent: "<<p->parent->max;
                else
                       cout<<"\n There is no parent of the node.  ";
                if(p->right!=NULL)
                       cout<<"\n Right Child: "<<p->right->max;
                else
                       cout<<"\n There is no right child of the node.  ";
                if(p->left!=NULL)
                       cout<<"\n Left Child: "<<p->left->max;
                else
                       cout<<"\n There is no left child of the node.  ";
                cout<<endl;

     }
}

// a fuction to insert a node in this we will use lowest value of the interval to maintain bst property
IntTreeNode *insert(IntTreeNode *root, Interval i)
{
    
    if (root == NULL)
        return newNode(i);
 
    // Get low value of interval at root
    int l = root->i->low;
 
    // If root's low value is smaller, then new interval goes to
    // left subtree
    if (i.low < l)
        root->left = insert(root->left, i);
 
    // Else, new node goes to right subtree.
    else
        root->right = insert(root->right, i);
 
    // Update the max value of this ancestor if needed
    if (root->max < i.high)
        root->max = i.high;
 
    return root;
}
 
// function to check overlaping of interval
bool doOVerlap(Interval i1, Interval i2)
{
    if (i1.low <= i2.high && i2.low <= i1.high)
        return true;
    return false;
}
 
//interval search function
Interval *intervalSearch(IntTreeNode *root, Interval i)
{
    
    if (root == NULL)
        return NULL;
 
    // If given interval overlaps with root
    if (doOVerlap(*(root->i), i))
        return root->i;
 
    // If left child of root is present and max of left child is
    // greater than or equal to given interval, then i may
    // overlap with an interval is left subtree
    if (root->left != NULL && root->left->max >= i.low)
        return intervalSearch(root->left, i);
 
    // Else interval can only overlap with right subtree
    return intervalSearch(root->right, i);
}
 
void inorder(IntTreeNode *root)
{
    if (root == NULL)
        return;
 
    inorder(root->left);
 
    cout << "[" << root->i->low << ", " << root->i->high << "]" << " max = "
            << root->max << endl;
 
    inorder(root->right);
}
 
int main(int argc, char **argv)
{
 
    Interval ints[] = { { 15, 20 }, { 10, 30 }, { 17, 19 }, { 5, 20 },
            { 12, 15 }, { 30, 40 } };
    int n = sizeof(ints) / sizeof(ints[0]);
    IntTreeNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, ints[i]);
 
    cout << "In-order traversal is\n";
    inorder(root);
 
    Interval x = { 14, 16 };
    Interval y= {21,23};
 
    cout << "\nSearching for interval [" << x.low << "," << x.high << "]";
    Interval *res = intervalSearch(root, x);
    if (res == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << res->low << ", " << res->high << "]";
        
        
        cout << "\nSearching for interval [" << y.low << "," << y.high << "]";
    Interval *pes = intervalSearch(root, y);
    if (pes == NULL)
        cout << "\nNo Overlapping Interval";
    else
        cout << "\nOverlaps with [" << pes->low << ", " << pes->high << "]";
}

// output:
// In-order traversal is
// [5, 20] max = 20
// [10, 30] max = 30
// [12, 15] max = 15
// [15, 20] max = 40
// [17, 19] max = 40
//   [30, 40] max = 40

//Searching for interval [14,16]
//Overlaps with [15, 20]
// Searching for interval [21,23]
// Overlaps with [10, 30]

