#include <stdlib.h>
#include <stdio.h>
#include "bitree.h"

int BiTree_init(BiTree* tree, void (*destroy_data)(void *), void (*print_data)(void *)){

    tree -> size            = 0;
    tree -> destroy_data    = destroy_data;
    tree -> root            = NULL;
    tree -> print_data      = print_data;

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

    BiTree_init(merged, left -> destroy_data, left -> print_data);

    BiTreeNode *new_node = malloc(sizeof(BiTreeNode));

    if(new_node == NULL){
        return -1;
    }

    new_node -> data    = merged_data;
    new_node -> left    = BiTree_root(left);
    new_node -> right   = BiTree_root(right);

    merged -> root = new_node;
    merged -> size = BiTree_size(left) + BiTree_size(right) + 1;

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

void print_inorder_recursive(BiTreeNode *node, void (*print_data)(void *)){
    if(node == NULL){
        return;
    }

    print_inorder_recursive(node -> left, print_data);
    print_data(node -> data);
    printf("\n");
    print_inorder_recursive(node -> right, print_data);
}

void BiTree_inorder_print(BiTree *tree){
    printf("Printing BiTree in order...\n");

    if(tree -> print_data == NULL){
        printf("No print function provided\n\n");
        return;
    }

    print_inorder_recursive(tree -> root, tree -> print_data);

}

void pop_level_order_recursive(BiTreeNode *node, BiTreeNode **nodes, int index){
    if(node == NULL){
        return;
    }

    nodes[index] = node;

    pop_level_order_recursive(node -> left, nodes, (index * 2) + 1);
    pop_level_order_recursive(node -> right, nodes, (index * 2) + 2);

}


void BiTree_level_order_print(BiTree *tree){
    printf("Printing BiTree level order...\n");

    if(tree -> print_data == NULL){
        printf("No print function provided\n\n");
        return;
    }

    int tree_size = 20;
    printf("tree size%d\n", tree -> size);

    BiTreeNode **nodes = malloc(sizeof(BiTreeNode*) * tree_size);

    pop_level_order_recursive(tree -> root, nodes, 0);

    for(int i = 0; i < tree_size; i++){
        printf("%d: ", i);

        if(nodes[i] == NULL){
            printf("NULL\n");
            continue;
        }

        tree -> print_data(nodes[i] -> data);
        printf("\n");
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