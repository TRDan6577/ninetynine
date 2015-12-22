/**
 * File: player.c
 * Purpose: Serves as a representation of a player in the 99 card game
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#include"player.h"

Player *createPlayer(char *name){

    // Create the new player
    Player *newPlayer = calloc(1, sizeof(Player));

    // Set the player's name
    newPlayer->name = name;

    // Set other default attributes
    newPlayer->numCards = NUM_STARTING_CARDS;
    newPlayer->numTokens = NUM_STARTING_TOKENS;
    for(int i = 0; i < NUM_STARTING_CARDS; i++){ 
        newPlayer->cards[i] = NULL; // Player wasn't dealt cards yet
    }

    return newPlayer;
}
