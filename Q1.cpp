#include<iostream>
#include<stdlib.h>
#include<stack>


using namespace std;

class bstNode
{
    public:
    bstNode()
    {
        left = right = parent = 0;
        el=-1;
    }
    bstNode(const int& e, bstNode *p = 0, bstNode *l = 0, bstNode *r = 0)
    {
        el = e; left = l; right = r; parent = p;
        color = false;
    }
    int el;
    bool color;
    bstNode *left, *right, *parent;
};

class bst
{
    public:
    bst()
    {
        root = 0;
    }

    ~bst()
    {
        clear();
    }

    void clear()
    {
        clear(root);
        root = 0;
    }

    bool isEmpty()
    {
        return root == 0;
    }

    int search(int& el)
    {
        return search(root,el);
    }

    void iterative_Preorder();
    void iterative_Inorder();
    void insert(int&);
    void insert_fixup(bstNode*);
    void delete_fixup(bstNode*);
    void left_rotate(bstNode*);
    void right_rotate(bstNode*);
    void find_And_DeleteByCopying(int&);
    void delete_By_Copying(bstNode*&);

    protected:
    bstNode* root;
    void clear(bstNode*);
    int search(bstNode*,int&);

    void visit(bstNode* p)
    {
        if(p->el==-1)
            return;

        cout <<"\nElement: "<< p->el <<"\t Color: ";

        if(p->color)
            cout<<"Black";
        else 
            cout<<"Red";
    }
};

int bst::search(bstNode* p,int& el)
{
    while (p != 0)
    {
        if (el == p->el)
        {
            cout<<"\n"<<p->el<<"color :";

            if(p->color)
                cout<<"black";
            else
                cout<<"red";

            return 0;
        }
        else if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }
    return -1;
}

void bst::iterative_Preorder()
{
    stack<bstNode*> travStack;
    bstNode *p = root;
    if (p != 0)
    {
        travStack.push(p);
        while (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
            visit(p);

            if (p->right != 0)
                travStack.push(p->right);

            if (p->left != 0)
                travStack.push(p->left);
        }
    }
}

void bst::insert(int& el)
{
    bstNode *p = root, *prev = 0;
    while (p != 0)
    {
        prev = p;
        if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }

    if (root == 0)
        p = root = new bstNode(el);
    else if (el < prev->el)
        p = prev->left = new bstNode(el,prev);
    else
        p = prev->right = new bstNode(el,prev);

    insert_fixup(p);
}

void bst::left_rotate(bstNode* x)
{
    bstNode* y=x->right;
    x->right=y->left;

    if(y->left!=0)
        (y->left)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->left)
        (x->parent)->left=y;
    else
        (x->parent)->right=y;

    y->left=x;
    x->parent=y;
}

void bst::right_rotate(bstNode* x)
{
    bstNode* y=x->left;
    x->left=y->right;

    if(y->right!=0)
        (y->right)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->right)
        (x->parent)->right=y;
    else
        (x->parent)->left=y;

    y->right=x;
    x->parent=y;
}
void bst::delete_fixup(bstNode* x)
{
    bstNode* w;
    bstNode* nil=new bstNode();
    nil->color=true;

    while(x!=root && x->color)
    {
        if(x==(x->parent)->left)
        {
            w=((x->parent)->right)?((x->parent)->right):nil;
            if(!(w->color))
            {
                w->color=true;
                (x->parent)->color=false;
                left_rotate(x->parent);
                w=((x->parent)->right)?((x->parent)->right):nil;
            }

            if((w->left)?(w->left)->color:true && (w->right)?(w->right)->color:true)
            {
                w->color=false;
                x=x->parent;
            }
            else
            {
                if((w->right)?(w->right)->color:true)
                {
                    if(w->left)
                        (w->left)->color=true;

                    w->color=false;
                    right_rotate(w);
                    w=((x->parent)->right)?((x->parent)->right):nil;
                }
                w->color=(x->parent)->color;
                (x->parent)->color=true;
                if(w->right)
                    (w->right)->color=true;

                left_rotate(x->parent);
                x=root;
            }
        }
        else
        {
            w=((x->parent)->left)?((x->parent)->left):nil;
            if(!(w->color))
            {
                w->color=true;
                (x->parent)->color=false;
                right_rotate(x->parent);
                w=((x->parent)->left)?((x->parent)->left):nil;
            }

            if((w->left)?(w->left)->color:true && (w->right)?(w->right)->color:true)
            {
                w->color=false;
                x=x->parent;
            }
            else
            {
                if((w->left)?(w->left)->color:true)
                {
                    if(w->right)
                        (w->right)->color=true;

                    w->color=false;
                    left_rotate(w);
                    w=((x->parent)->left)?((x->parent)->left):nil;
                }
                w->color=(x->parent)->color;
                (x->parent)->color=true;
                if(w->left)
                    (w->left)->color=true;
                    
                right_rotate(x->parent);
                x=root;
            }
        }
    }
    x->color=true;
}

void bst::insert_fixup(bstNode* z)
{
    bstNode* y;
    bstNode* inil=new bstNode();
    inil->color=true;
    while((z->parent)!=0 && ((z->parent)->parent)!=0 && !((z->parent)->color))
    {
        if(z->parent==((z->parent)->parent)->left)
        {
            y=(((z->parent)->parent)->right)?(((z->parent)->parent)->right):inil;
            if(!(y->color))
            {
                (z->parent)->color=true;
                y->color=true;
                ((z->parent)->parent)->color=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->right)
                {
                    z=z->parent;
                    left_rotate(z);
                }
                (z->parent)->color=true;
                ((z->parent)->parent)->color=false;
                right_rotate((z->parent)->parent);
            }
        }
        else
        {
            y=(((z->parent)->parent)->left)?(((z->parent)->parent)->left):inil;
            if(!(y->color))
            {
                (z->parent)->color=true;
                y->color=true;
                ((z->parent)->parent)->color=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->left)
                {
                    z=z->parent;
                    right_rotate(z);
                }
                                (z->parent)->color=true;
                ((z->parent)->parent)->color=false;
                left_rotate((z->parent)->parent);
            }
        }
    }
    root->color=true;
}

void bst::find_And_DeleteByCopying(int& el)
{
    bstNode *node = root, *prev = 0;
    while (node != 0)
    {
        if (node->el == el)
            break;

        prev = node;

        if (el < node->el)
            node = node->left;
        else
            node = node->right;
    }

    if (node != 0 && node->el == el)
    {
        if (node == root)
            delete_By_Copying(root);
        else if (prev->left == node)
            delete_By_Copying(prev->left);
        else
            delete_By_Copying(prev->right);
    }
    else if (root != 0)
        cout << "Element is not in the tree\n";
    else
        cout << "The tree is empty\n";
}
void bst::delete_By_Copying(bstNode*& node)
{
    bool check,check2;
    bstNode *previous, *tmp = node,*par=node->parent;
    bstNode *cnil=new bstNode();
    cnil->color=true;
    cnil->parent=par;

    if (node->right == 0)
    {
        node = node->left;
        check=false;
    }
    else if (node->left == 0)
    {
        node = node->right;
        check=false;
    }
    else
    {
        tmp = node->left;
        previous = node;
        while (tmp->right != 0)
        {
            previous = tmp;
            tmp = tmp->right;
        }

        node->el = tmp->el;
        node->color = tmp->color;

        if(tmp->left)
            (tmp->left)->parent=previous;
        else
            cnil->parent=previous;
            
        if (previous == node)
        {
            previous ->left = tmp->left;
            check=true;
            check2=false;
        }
        else
        {
            previous ->right = tmp->left;
            check=true;
            check2=true;
        }
    }

    if(tmp->color)
    {
        if(!check)
        {
            if(!node)
                node=cnil;

            node->parent=par;
            delete_fixup(node);

            if(par && par->left==cnil)
                par->left=0;
            else if(par && par->right==cnil)
                par->right=0;
        }
        else if(check2)
        {
            if(!previous->right)
                previous->right=cnil;

            delete_fixup(previous->right);

            if(previous->right==cnil)
                previous->right=0;
        }
        else
        {
            if(!previous->left)
                previous->left=cnil;

            delete_fixup(previous->left);

            if(previous->left==cnil)
                previous->left=0;
        }
    }
    delete cnil;
    delete tmp;
}

void bst::clear(bstNode * p)
{
    if(p!=0)
    {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

void bst::iterative_Inorder()
{
    stack<bstNode*> travStack;
    bstNode *p = root;
    while (p != 0)
    {
        while (p != 0)
        {
            if (p->right)
            travStack.push(p->right);
            travStack.push(p);
            p = p->left;
        }

        p = travStack.top();
        travStack.pop();

        while (!travStack.empty() && p->right == 0)
        {
            visit(p);
            p = travStack.top();
            travStack.pop();
        }

        visit(p);

        if (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
        }
        else
            p = 0;
    }
}

int main()
{
    bst t1;
    int dtchoice;
    do
    {
        int x;
        system("cls");
        cout<<"Enter your choice.\n1.Insertion.\n2.Deletion.\n3.Search a number.\n4.Display its preorder and inorder transversals.\n5.Exit.\n";
        cin>>dtchoice;

        switch(dtchoice)
        {
            case 1: system("cls");
                        cout<<"\nEnter the number to be inserted in tree.\n";
                        cin>>x;
                        t1.insert(x);
                        break;

            case 2: system("cls");
                        cout<<"\nEnter number to be deleted.\n";
                        cin>>x;
                        t1.find_And_DeleteByCopying(x);
                        system("pause");
                        break;

            case 3: system("cls");
                        if(t1.isEmpty())
                        cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nEnter number to be searched.\n";

                        cin>>x;
                        int a=t1.search(x);
                        if(a==-1)
                            cout<<"\nNumber is not present.";}

                        system("pause");
                        break;

            case 4: system("cls");
                        if(t1.isEmpty())
                            cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nPreorder:\n";

                        t1.iterative_Preorder();
                        cout<<"\nInorder:\n";
                        t1.iterative_Inorder();}
                        system("pause");
                        break;

            case 5: system("cls");
                        exit(0);
                        break;

            default:system("cls");
                cout<<"Enter correct choice.";
            }
    }while(true);
    return 0;
}

