//http://vn.spoj.com/problems/ORDERSET/
#include <bits/stdc++.h>

using namespace std;

struct tree_node{
       tree_node* left;
       tree_node* right;
     //  tree_node* parrent;
       int data;
       int child;
       int height;
};
class AVL
{

    public:
        tree_node* root;

        AVL()
        {
           root = NULL;
        }

        bool isEmpty() const { return root==NULL; }
        void print_inorder();
        void inorder(tree_node*);
        void print_preorder();
        void preorder(tree_node*);
        void print_postorder();
        void postorder(tree_node*);
        void insert(int);
        tree_node* insert_(tree_node*,int);
        tree_node* deleteNode(tree_node*,int);
        tree_node* find(int);
        tree_node* minValueNode(tree_node*);
        tree_node* maxValueNode(tree_node*);
        tree_node* kthMaxValueNode(tree_node*,int);
        int getHeight(tree_node*);
        tree_node* right_rotate(tree_node*);
        tree_node* left_rotate(tree_node*);
        int getBalance(tree_node*);
        tree_node* ReBalance(tree_node*);
        int getChild(tree_node*);
        int coun(tree_node*,int); // count number of node->data < a

};

// Smaller elements go left
// larger elements go right
tree_node* AVL::kthMaxValueNode(tree_node* r,int k)
{
    if(r==NULL)
        return r;
    int numl = getChild(r->left);
    if(k-numl == 1)
        return r;
    if(k-numl > 1)
        return kthMaxValueNode(r->right,k-numl-1);
    else
        return kthMaxValueNode(r->left,k);
}
int AVL::getHeight(tree_node* x)
{
    if(x==NULL)
        return -1;
    return x->height;
}
int AVL::getChild(tree_node* x)
{
    if(x==NULL)
        return 0;
    return x->child;
}
tree_node* AVL::right_rotate(tree_node* Q)
{
    tree_node* P = Q->left;
    tree_node* B = P->right;
    Q->left = B;
    P->right = Q;
    Q->height = max(getHeight(Q->left),getHeight(Q->right))+1;
    P->height = max(getHeight(P->left),getHeight(P->right))+1;
    Q->child = getChild(Q->left)+getChild(Q->right) +1;
    P->child = getChild(P->left)+getChild(P->right) +1;

    return P;
}
tree_node* AVL::left_rotate(tree_node* P)
{
    tree_node* Q = P->right;
    tree_node* B = Q->left;
    P->right = B;
    Q->left = P;
    P->height = max(getHeight(P->left),getHeight(P->right))+1;
    Q->height = max(getHeight(Q->left),getHeight(Q->right))+1;
    P->child = getChild(P->left)+getChild(P->right) +1;
    Q->child = getChild(Q->left)+getChild(Q->right) +1;

    return Q;
}
tree_node* AVL::find(int d)
{
    tree_node* crr = root;
    while(crr!=NULL){
        if(crr->data==d)
            return crr;
        if(crr->data<d)
            crr = crr->right;
        else
            crr = crr->left;
    }
    return NULL;
}
int AVL::getBalance(tree_node* x)
{
    if(x==NULL)
         return 0;
    return getHeight(x->left)-getHeight(x->right);
}
tree_node* AVL::ReBalance(tree_node* curr)
{
    int balance = getBalance(curr);

    // If this curr becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
     if (balance > 1 && getBalance(curr->left)>0)
         return right_rotate(curr);

    // Right Right Case
     if (balance < -1 && getBalance(curr->right)<0)
         return left_rotate(curr);

    // Left Right Case
     if (balance > 1 && getBalance(curr->left)<=0)
     {
        curr->left =  left_rotate(curr->left);
        return right_rotate(curr);
     }

    // Right Left Case
     if (balance < -1 && getBalance(curr->right)>=0)
     {
        curr->right = right_rotate(curr->right);
        return left_rotate(curr);
     }
}
tree_node* AVL::insert_(tree_node* curr,int d)
{
    if(curr==NULL){
        tree_node* t = new tree_node;
        t->data = d;
        t->left = NULL;
        t->right = NULL;
//        t->parrent = NULL;
        t->child = 1;
        t->height = 0;
        return t;
    }
     if(d > curr->data){
        curr->right=insert_(curr->right,d);

//        curr->right->parrent = curr;
     }
     else{
        curr->left=insert_(curr->left,d);
//        curr->left->parrent = curr;
     }
     curr->height = max(getHeight(curr->right),getHeight(curr->left))+1;
     curr->child = getChild(curr->left)+getChild(curr->right)+1;
     int bl = getBalance(curr);
     if(bl>=-1 && bl<=1)
        return curr;
     else
        return ReBalance(curr);
}
void AVL::insert(int d)
{
    tree_node* t = new tree_node;

    t->data = d;
    t->left = NULL;
    t->right = NULL;
//    t->parrent = NULL;
    t->child = 1;
    t->height = 0;


    // is this a new tree?
    if(isEmpty()) root = t;
    else
    {
        root = insert_(root,d);

    }
}

tree_node * AVL::minValueNode(tree_node* node)
{
    tree_node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

tree_node * AVL::maxValueNode(tree_node* node)
{
    tree_node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->right != NULL)
        current = current->right;

    return current;
}
tree_node* AVL::deleteNode(tree_node *root,int key)
{
    //Locate the elemen
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            tree_node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            tree_node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        tree_node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    root->height = max(getHeight(root->left),getHeight(root->right))+1;
    root->child = getChild(root->left)+getChild(root->right)+1;
    int bl = getBalance(root);
     if(bl>=-1 && bl<=1)
        return root;
     else
        return ReBalance(root);
}

void AVL::print_inorder()
{
  inorder(root);
}

void AVL::inorder(tree_node* p)
{
    if(p != NULL)
    {
        if(p->left) inorder(p->left);
        cout<<" "<<p->data<<" ";
        if(p->right) inorder(p->right);
    }
    else return;
}

void AVL::print_preorder()
{
    preorder(root);
}

void AVL::preorder(tree_node* p)
{
    if(p != NULL)
    {
        cout<<" "<<p->data<<" ";
        if(p->left) preorder(p->left);
        if(p->right) preorder(p->right);
    }
    else return;
}

void AVL::print_postorder()
{
    postorder(root);
}
int AVL::coun(tree_node* x,int a)
{
    if(x==NULL) return 0;
    if(a>x->data){
        return coun(x->right,a)+1+getChild(x->left);
    }
    else
    {
        return coun(x->left,a);
    }
}
void AVL::postorder(tree_node* p)
{
    if(p != NULL)
    {
        if(p->left) postorder(p->left);
        if(p->right) postorder(p->right);
        cout<<" "<<p->data<<" ";
    }
    else return;
}



int n;
int a;
char c;
AVL tree;
map<int,int> mm;
int main()
{
  //  freopen("code.in","r",stdin);
   // freopen("code.ou1","w",stdout);
    scanf("%d\n",&n);
   // cout << n << endl;
    for(int i=1;i<=n;i++){
        scanf("%c",&c);
        scanf("%d\n",&a);
       //cout << c <<" ";
        if(c=='I'){
            if(mm[a]==0){
                tree.insert(a);
                mm[a] = 1;
            //    cout << c <<" ";
            }
        }
        if(c=='D'){
            if(mm[a]==1){
                mm[a] = 0;
                tree.root = tree.deleteNode(tree.root,a);
             //   cout << c <<" ";
            }
        }
        if(c=='K'){
            tree_node* tmp = tree.kthMaxValueNode(tree.root,a);
            if(tmp == NULL)
                printf("invalid\n");
            else
                printf("%d\n",tmp->data);
            //delete tmp;
        }
        if(c=='C'){
            printf("%d\n",tree.coun(tree.root,a));
        }
        //tree.print_inorder();
        //cout << endl;
    }
}
