// DO NOT MODIFY eval_game_state FUNCTION
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "game_bot.h"


void eval_game_state(GameState *gs)
{
    GameStatus status = get_game_status(gs);
    if (status == PLAYER_1_WIN)
    {
        gs->evaluation = 1000;
        return;
    }
    else if (status == PLAYER_2_WIN)
    {
        gs->evaluation = -1000;
        return;
    }
    else if (status == DRAW)
    {
        gs->evaluation = 0;
        return;
    }

    // Count the number of 3s in a row
    int player_1_3 = 0;
    int player_2_3 = 0;

    // Count the number of 2s in a row with an extra space around
    int player_1_2 = 0;
    int player_2_2 = 0;

    // Check horizontal
    for (int i = 0; i < gs->height; i++)
    {
        for (int j = 0; j <= gs->width - 3; j++)
        {
            int index = i * gs->width + j;

            int x_count = (gs->board[index] == 'X') + (gs->board[index + 1] == 'X') + (gs->board[index + 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + 1] == 'O') + (gs->board[index + 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + 1] == '_') + (gs->board[index + 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check vertical
    for (int i = 0; i <= gs->height - 3; i++)
    {
        for (int j = 0; j < gs->width; j++)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width] == 'X') + (gs->board[index + 2 * gs->width] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width] == 'O') + (gs->board[index + 2 * gs->width] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width] == '_') + (gs->board[index + 2 * gs->width] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= gs->height - 3; i++)
    {
        for (int j = 0; j <= gs->width - 3; j++)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width + 1] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width + 2])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width + 1] == 'X') + (gs->board[index + 2 * gs->width + 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width + 1] == 'O') + (gs->board[index + 2 * gs->width + 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width + 1] == '_') + (gs->board[index + 2 * gs->width + 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= gs->height - 4; i++)
    {
        for (int j = gs->width - 1; j >= 2; j--)
        {
            int index = i * gs->width + j;
            // if (gs->board[index] != '_' &&
            //     gs->board[index] == gs->board[index + gs->width - 1] &&
            //     gs->board[index] == gs->board[index + 2 * gs->width - 2])
            // {
            //     if (gs->board[index] == 'X')
            //         player_1_3++;
            //     else
            //         player_2_3++;
            // }

            int x_count = (gs->board[index] == 'X') + (gs->board[index + gs->width - 1] == 'X') + (gs->board[index + 2 * gs->width - 2] == 'X');
            int o_count = (gs->board[index] == 'O') + (gs->board[index + gs->width - 1] == 'O') + (gs->board[index + 2 * gs->width - 2] == 'O');
            int empty_count = (gs->board[index] == '_') + (gs->board[index + gs->width - 1] == '_') + (gs->board[index + 2 * gs->width - 2] == '_');

            if (x_count == 3)
                player_1_3++;
            else if (o_count == 3)
                player_2_3++;
            else if (x_count == 2 && empty_count == 1)
                player_1_2++;
            else if (o_count == 2 && empty_count == 1)
                player_2_2++;
        }
    }

    gs->evaluation = 10 * (player_1_3 - player_2_3) + 3 * (player_1_2 - player_2_2);
}



void eval_game_tree(TreeNode *root) {
    if(root->num_children == -1) {
        eval_game_state(root->game_state);
        return;
    }else{
        for(int i = 0; i < root->num_children; i++){
            eval_game_tree(root->children[i]);
        }
    }
}
int get_min(TreeNode* node) {
    if(node->num_children == -1) {
        return node->game_state->evaluation;
    }
    int min_value = get_max(node->children[0]);
        for(int i = 1; i < node->num_children; i++) {

            int newvalue = get_max(node->children[i]);
            if(newvalue < min_value){
                min_value  =newvalue ;
            }
        }
        node->game_state->evaluation = min_value;
        return min_value;
}
int get_max(TreeNode* node) {
    if (node->num_children == -1)
    {
        return node->game_state->evaluation;
    }
        int max_value = get_min(node->children[0]);
        for(int i = 1; i < node->num_children; i++) {
            int newvalue = get_min(node->children[i]) ;
            if(newvalue > max_value){
                max_value  = get_min(node->children[i]);
            }
        }
        node->game_state->evaluation = max_value;
        return max_value;    
}
int best_move(TreeNode* root) {
    eval_game_tree(root);

    if (root->num_children == -1) {
        return -1;
    }

    int val = 0;
    if(root->game_state->next_turn) {
        val = get_min(root);
    } else {
        val = get_max(root);
    }

    for(int i = 0; i < root->num_children; i++) {
        if(root->children[i]->game_state->evaluation == val) {
            return i;
        }
    }

    exit(1);
}
