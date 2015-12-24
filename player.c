/**
 * File: player.c
 * Purpose: Serves as a representation of a player in the 99 card game
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#include"player.h"

Player *createPlayer(char *name, short int level){

    if(!(MIN_LEVEL <= level && level <= MAX_LEVEL)){
        fprintf(stderr, "Levels for AI can only be 1, 2, or 3 (easy, medium, "
                " or hard, respectively)\n");
        exit(0);
    }

    // Create the new player
    Player *newPlayer = calloc(1, sizeof(Player));

    // Set the player's attributes
    newPlayer->name = name;
    newPlayer->level = level;
    newPlayer->numCards = NUM_STARTING_CARDS;
    newPlayer->numTokens = NUM_STARTING_TOKENS;
    for(int i = 0; i < NUM_STARTING_CARDS; i++){ 
        newPlayer->cards[i] = NULL; // Player wasn't dealt cards yet
    }

    return newPlayer;
}

void destroyPlayer(Player *deadMan){

    // Free the cards the player is holding
    for(int i = 0; i < NUM_STARTING_CARDS; i++){
        if(deadMan->cards[i]){
            free(deadMan->cards[i]);
        }
    }

    // Free the actual player
    free(deadMan);
}
