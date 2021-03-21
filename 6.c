#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct local_ptr                                        //defination of structure
{
    int data;                                                   //to store data
    struct local_ptr *left;                                     //address of left pointer
    struct local_ptr *right;                                    //address of right pointer
    struct local_ptr *parent;                                   //address of parent
}local_ptr;

void pre_order(local_ptr *node)                                      //function to print pre order sequence
{
    if(node == NULL)
    {
        return;
    }
    printf("%d ",node->data);
    pre_order(node->left);
    pre_order(node->right);
}

void right_rotate(local_ptr* node)                              //function of right rotation
{
    local_ptr *gp,*p,*c;
    gp = node->parent->parent;
    p = node->parent;
    c = node->right;
    node->parent = gp;
    node->right = p;
    p->parent = node;
    p->left = c;
    if(gp != NULL)
    {
        if(gp->data > node->data)
            gp->left = node;
        else
            gp->right = node;
    }
    if(c != NULL)
        c->parent = p;
}
void left_rotate(local_ptr* node)                               //function of left rotation
{
    local_ptr *gp,*p,*c;
    gp = node->parent->parent;
    p = node->parent;
    c = node->left;
    node->parent = gp;
    node->left = p;
    p->parent = node;
    p->right = c;
    if(gp != NULL)
    {
        if(gp->data > node->data)
            gp->left = node;
        else
            gp->right = node;
    }
    if(c != NULL)
        c->parent = p;
}
void rotate(local_ptr* node)                                    //function to modify overall tree and make the inserted or searched value root node
{
    if(node->parent == NULL)
    {
        return ;
    }
    else if(node->parent->parent == NULL)
    {

        if(node->parent->left == node)
        {
            right_rotate(node);
        }

        else
        {
            left_rotate(node);
        }
        return rotate(node);
    }
    else
    {
        local_ptr *gp = node->parent->parent;
        if(gp->left != NULL)
        {
            if(gp->left->left == node)
            {
                right_rotate(node->parent);
                right_rotate(node);
                return rotate(node);
            }
            if(gp->left->right == node)
            {
                left_rotate(node);
                right_rotate(node);
                return rotate(node);
            }
        }
        if(gp->right != NULL)
        {
            if(gp->right->left == node)
            {
                right_rotate(node);
                left_rotate(node);
                return rotate(node);
            }
            if(gp->right->right == node)
            {
                left_rotate(node->parent);
                left_rotate(node);
                return rotate(node);
            }
        }
        return rotate(node);
    }
}

local_ptr* search(local_ptr *node, int key)                         //function to search the key
{
    if(node->data == key)
    {
        rotate(node);
        return node;
    }
    if(node->data > key)
    {
        return search(node->left,key);
    }
    if(node->data < key)
    {
        return search(node->right,key);
    }
}
local_ptr* insert(local_ptr *node, local_ptr *parent, int key)         //function to insert a value in tree
{
    if(node == NULL)
    {
        node = (local_ptr*)malloc(sizeof(local_ptr));
        node->data = key;
        node->parent = parent;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if(node->data > key)
    {
        node->left = insert(node->left,node,key);
        return node;
    }
    if(node->data < key)
    {
        node->right = insert(node->right,node,key);
        return node;
    }
}
int main(void)
{
    int k;
    scanf("%d",&k);
    local_ptr *node;
    node = NULL;                                            //initialising the node to be NULL
    while(k == 1 || k == 2)
    {
        if(k == 1)                                          //if k = 1 then insert
        {
            int n;
            printf("Write key to be inserted: ");
            scanf("%d",&n);
            node = insert(node,NULL,n);
            node = search(node,n);
            printf("Pre-order transversal: ");
            pre_order(node);
            printf("\n");
        }
        if(k == 2)
        {
            int n;
            printf("Write key to be searched: ");
            scanf("%d",&n);
            node = search(node,n);
            printf("Pre-order transversal: ");
            pre_order(node);
            printf("\n");
        }
        scanf("%d",&k);
    }
	return 0;
}
