#include <stdio.h>
#include <assert.h>
typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
}node_t;


node_t *RootBegin(node_t *root)
{
    assert(NULL != root);

    while(NULL != root->left)
    {
        root = root->left;
    }
    return root;
}

node_t *RootEnd(node_t *root)
{
    assert(NULL != root);

    while(NULL != root->right)
    {
        root = root->right;
    }
    return root;
}


node_t *JoinAbove(node_t *runner)
{
    node_t *new_parent_top = NULL;
    node_t *new_parent_bottom = NULL;

    if (NULL != runner->parent)
    {
        runner->right->parent = runner->parent;
        runner->parent->left = runner->right;
    }
    else /*for root*/
    {
        runner->right->parent = NULL;     
    }
    
    new_parent_bottom = RootBegin(runner->right);
    new_parent_bottom->left = runner;
    runner->parent = new_parent_bottom;
    runner->right = NULL;
    return runner->parent;
}

node_t *BstToDll(node_t *bst_root)
{
    node_t *runner = bst_root;
    node_t *end = NULL;

    assert(NULL != bst_root);

    end = RootEnd(bst_root);
    runner = RootBegin(runner);
    while(end != runner)
    {
        if (NULL != runner->right)
        {
            runner = JoinAbove(runner);
        }
        else
        {
            runner = runner->parent;
        }
    }

    return runner;
}




int main()
{
    node_t arr[7] = {0};
    node_t *runner = NULL;
    size_t i = 0;

    arr[0].data = 7;
    arr[0].left = &arr[1];
    arr[0].right = &arr[2];
    arr[0].parent = NULL;

    arr[1].data = 3;
    arr[1].left = &arr[3];
    arr[1].right = &arr[4];
    arr[1].parent = &arr[0];

    arr[2].data = 9;
    arr[2].left = &arr[5];
    arr[2].right = &arr[6];
    arr[2].parent = &arr[0];

    arr[3].data = 1;
    arr[3].left = NULL;
    arr[3].right = NULL;
    arr[3].parent = &arr[1];

    arr[4].data = 4;
    arr[4].left = NULL;
    arr[4].right = NULL;
    arr[4].parent = &arr[1];

    arr[5].data = 8;
    arr[5].left = NULL;
    arr[5].right = NULL;
    arr[5].parent = &arr[2];
   
    arr[6].data = 10;
    arr[6].left = NULL;
    arr[6].right = NULL;
    arr[6].parent = &arr[2];
   
    runner = BstToDll(&arr[0]);
    while(runner != NULL)
    {
        printf("%d,\n",runner->data);
        runner = runner->left;
    }


   return 0;
}
