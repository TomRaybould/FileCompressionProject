#include <stdlib.h>
#include "bitree.h"

int BiTree_init(BiTree* tree, void (*destroy_data)(void *)){

    tree -> size            = 0;
    tree -> destroy_data    = destroy_data;
    tree -> root            = NULL;

    return 0;
}

int BiTree_ins_left(BiTree* tree, BiTreeNode *parent_node, void *data){

    BiTreeNode *new_node;
    BiTreeNode **position;

    if(parent_node == NULL){
        //try to insert at root
        if(tree -> root != NULL){
            return -1;
        }

        position = &(tree -> root);

    }
    else{

        position = &(parent_node -> left);

    }

    new_node = malloc(sizeof(BiTreeNode));

    if(new_node == NULL){
        return -1;
    }

    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;

    *position = new_node;
    tree -> size++;

    return 0;

}

int BiTree_ins_right(BiTree* tree, BiTreeNode *parent_node, void *data){

    BiTreeNode *new_node;
    BiTreeNode **position;

    if(parent_node == NULL){
        //try to insert at root
        if(tree -> root != NULL){
            return -1;
        }

        position = &(tree -> root);

    }
    else{

        position = &(parent_node -> right);

    }

    new_node = malloc(sizeof(BiTreeNode));

    if(new_node == NULL){
        return -1;
    }

    new_node -> data = data;
    new_node -> left = NULL;
    new_node -> right = NULL;

    *position = new_node;
    tree -> size++;

    return 0;

}


int BiTree_merge(BiTree* merged, void *merged_data, BiTree *left, BiTree *right) {

    BiTree_init(merged, left -> destroy_data);

    BiTreeNode *new_node = malloc(sizeof(BiTreeNode));

    if(new_node == NULL){
        return -1;
    }

    new_node -> data    = merged_data;
    new_node -> left    = BiTree_root(left);
    new_node -> right   = BiTree_root(right);

    merged -> root = new_node;

    left -> root = NULL;
    left -> size = 0;

    right -> root = NULL;
    right -> size = 0;

    return 0;

}

void BiTree_rem_left(BiTree *tree, BiTreeNode *parent_node){
    BiTreeNode **node;

    if(BiTree_size(tree) <= 0){
        return;
    }

    if(parent_node == NULL){
        node = &(tree -> root);
    }
    else{
        node = &(parent_node -> left);
    }

    if(*node != NULL){

        if(tree -> destroy_data){
            tree -> destroy_data((*node) -> data);
        }

        BiTree_rem_left(tree, *node);
        BiTree_rem_right(tree, *node);

        free(*node);
        *node = NULL;
        tree -> size--;

    }

}

void BiTree_rem_right(BiTree *tree, BiTreeNode *parent_node){

    BiTreeNode **node;

    if(BiTree_size(tree) <= 0){
        return;
    }

    if(parent_node == NULL){
        node = &(tree -> root);
    }
    else{
        node = &(parent_node -> right);
    }

    if(*node != NULL){

        if(tree -> destroy_data){
            tree -> destroy_data((*node) -> data);
        }

        BiTree_rem_left(tree, *node);
        BiTree_rem_right(tree, *node);

        free(*node);
        *node = NULL;
        tree -> size--;

    }

}

int BiTree_size(BiTree *tree){
    return tree -> size;
}

BiTreeNode* BiTree_root(BiTree *tree){
    return tree -> root;
}

void BiTree_destroy(void *tree){

    BiTree_rem_right(tree, NULL);

}