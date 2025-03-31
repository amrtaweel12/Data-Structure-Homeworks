#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
TreeNode *init_node(GameState *gs)
{
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->children = NULL;
    newNode->game_state = gs;
    newNode->num_children = -1;
    return newNode;
}
TreeNode *init_tree(GameState *gs, int depth)
{
    TreeNode *root = init_node(gs);
    bool *avaliable_moves_bool = (bool *)malloc(sizeof(bool) *gs->width);
    for(int i = 0; i < gs->width; i++) {
        avaliable_moves_bool[i] = false;
    }
    int number_of_moves = available_moves(gs, avaliable_moves_bool);
    if (depth == 1 || get_game_status(gs) != 3)
    {
        free(avaliable_moves_bool);
        return root;
    }

    
    root->num_children = number_of_moves;
    root->children = (TreeNode **)malloc(sizeof(TreeNode *) * number_of_moves);
    int number_of_new_state = 0; //this check how many new state was created to add it to the tree
   
       
        for (int z = 0; z < gs->width; z++)
        {
            if (avaliable_moves_bool[z] == true)
            {
                 GameState *new_state = make_move(gs, z);
                

                root->children[number_of_new_state] = init_tree(new_state, depth - 1);
                 number_of_new_state++;
            }
        }
        free(avaliable_moves_bool);
        return root;
    
}
void free_tree(TreeNode *root) {
    int children_number = root->num_children;
    if (children_number != -1)
    {
       for(int i =0; i < children_number; i++) {
        free_tree(root->children[i]);
        
       }
       free(root->children);
       free_game_state(root->game_state);
       free(root);
    }else{
        free_game_state(root->game_state);
        free(root);
    }
    
}
void expand_tree(TreeNode *root) {
    if(get_game_status(root->game_state) != 3) {
        return;
    }
    if(root->num_children == -1) {
        bool *moves =(bool*) malloc(sizeof(bool) * root->game_state->width);
        for(int z = 0; z < root->game_state->width; z++) {
            moves[z] = false;
        }
        int number_of_avalible_moves = available_moves(root->game_state, moves);
        int created_leaves = 0;
        if(number_of_avalible_moves != 0) {
            root->children = (TreeNode**) malloc(sizeof(TreeNode*) * number_of_avalible_moves);
            root->num_children = number_of_avalible_moves;
        for(int i =0; i < root->game_state->width; i++){
            if(moves[i] == true) {
                GameState* newstate = make_move(root->game_state,i);
                root->children[created_leaves] = init_node(newstate);
                created_leaves++;
                    
                
                
                
            } 
        }   
        }
        free(moves);

    }else {
        int num_of_children = root->num_children;
        for(int i = 0; i < num_of_children; i++){
            expand_tree(root->children[i]);
        }
    }
    
}
int node_count(TreeNode *root) {
    int x =0;
    if(root == NULL) {
        return 0;
    }else {
        x++;
        int avalible_children = root->num_children;
        if(avalible_children == -1) {
            return x;
        }else{
            for(int  i = 0; i < avalible_children; i++) {
                x += node_count(root->children[i]);
            }
            return x;
        }
    }
}
