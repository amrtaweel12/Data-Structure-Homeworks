#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "game_bot.h"
#include "interface.h"
#include "string.h"

int main()
{
 GameState *state = init_game_state(7, 6);
    char c;

    TreeNode * root = init_tree(state,5);
    node_count(root);
    while (get_game_status(state) == IN_PROGRESS)
    {
        print_available_moves(state);
    
        if(root->game_state->next_turn == true) {
            apply_move_to_tree(&root, best_move(root),5);
            print_game_state(root->game_state);
            state = root->game_state;
            continue;
        }
         printf("\nEnter your move for X: ");
        c = getchar();
        getchar();
        int move = c - '0';
        GameState *next_state = make_move(state, move);
        
        for(int i = 0; i < root->num_children; i++) {
            if(strcmp(next_state->board, root->children[i]->game_state->board) == 0){
        apply_move_to_tree(&root, i,5);
        free_game_state(next_state);
        break;
            }
        

        }

        print_game_state(root->game_state);
        
        state = root->game_state;
       
    }

    if (get_game_status(state) == DRAW)
    {
        printf("It is a draw");
    }
    else
    {
        printf("Player %d won!\n", get_game_status(state) + 1);
    }

    free_game_state(state);
    free(root);

    // play_game(7, 6, 6, false);
    return 0;
}
