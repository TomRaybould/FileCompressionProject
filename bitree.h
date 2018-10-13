#ifndef BITREE_H
#define BITREE_H


struct BiTreeNode_
{
    void    *data;
    struct  BiTreeNode_* left;
    struct  BiTreeNode_* right;
};

typedef struct BiTreeNode_ BiTreeNode;

struct BiTree_
{
    int         size;
    void        (*destroy_data)(void* data);
    BiTreeNode  *root;
};

typedef struct BiTree_ BiTree;


int         BiTree_init         (BiTree *tree, void (*destroy_data)(void *data));
int         BiTree_ins_left     (BiTree *tree, BiTreeNode *parent_node, void *data);
int         BiTree_ins_right    (BiTree *tree, BiTreeNode *parent_node, void *data);
void        BiTree_rem_left     (BiTree *tree, BiTreeNode *parent_node);
void        BiTree_rem_right    (BiTree *tree, BiTreeNode *parent_node);
int         BiTree_merge        (BiTree *merged, void *merged_data, BiTree *left, BiTree *right);
BiTreeNode* BiTree_root         (BiTree *tree);
int         BiTree_size         (BiTree *tree);
void        BiTree_destory      (BiTree *tree);

#endif