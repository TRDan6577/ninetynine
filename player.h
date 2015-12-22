/**
 * File: player.h
 * Purpose: Header file for player.c
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#ifndef PLAYER_H
#define PLAYER_H

// Some defs

#define NUM_STARTING_CARDS 3
#define NUM_STARTING_TOKENS 3

// Player structure

typedef struct Player {
    char *name; // The name of the player
    short int numCards; // The number of cards in the player's hand
    short int numTokens; // The number of tokens left (lose 3 and you're out)
    Card *cards[3]; // Each player starts with 3 cards
};

// Function decs

/**
 * Purpose: Creates a new player for the 99 card game
 * @param (char *) name - the name of the new player
 * @return (Player *) the newly made player with the given name
 */
Player *createPlayer(char *name);

#endif
