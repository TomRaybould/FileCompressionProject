#ifndef BITREE_H
#define BITREE_H


struct BiTreeNode_
{
    void    *data;
    struct  BiTreeNode_* left;
    struct  BiTreeNode_* right;
};

typedef struct BiTreeNode_ BiTreeNode;

int BiTreeNode_init(BiTreeNode** inited_node, void *data, BiTreeNode* left, BiTreeNode *right);


struct BiTree_
{
    int         size;
    void        (*destroy_data)(void* data);
    BiTreeNode  *root;
};

typedef struct BiTree_ BiTree;

int         BiTree_init(BiTree* tree, int size, BiTreeNode root, void (*destroy_data)(void* data));
BiTreeNode* BiTree_root(BiTree* tree);
int         BiTree_size(BiTree* tree);
int         BiTree_destory(BiTree *tree);

#endif