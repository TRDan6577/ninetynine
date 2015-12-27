/**
 * File: player.h
 * Purpose: Header file for player.c
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#ifndef PLAYER_H
#define PLAYER_H

// Some defs

#include<stdio.h>
#include<stdlib.h>

#include"card.h"

#define NUM_STARTING_CARDS 3
#define NUM_STARTING_TOKENS 3
#define MAX_LEVEL 3 // Only three levels of AI
#define MIN_LEVEL 0 // The lowest level is a player

// Player structure

typedef struct player_t {
    char *name; // The name of the player
    short int numCards; // The number of cards in the player's hand
    short int numTokens; // The number of tokens left (lose 3 and you're out)
    Card *cards[3]; // Each player starts with 3 cards
    short int level; // The level of the AI. Zero indicates that it is a human
} Player;

// Function decs

/**
 * Purpose: Creates a new player for the 99 card game
 * @param (char *) name - the name of the new player
 * @param (short int) level - the level of the AI (zero if player is a person)
 * @return (Player *) the newly made player with the given name
 */
Player *createPlayer(char *name, short int level);

/**
 * Purpose: Cleans up after creating a new player
 * @param (Player*) deadMan - the player to kill - I mean free. Yeah not kill...
 */
void destroyPlayer(Player *deadMan);

/**
 * Purpose: Determines where in the list of cards that a player needs to be
 *          dealt his or her next card.
 * @param (Player *) player - the player that needs to be dealt a card
 * @return (short int) the position of the next card needed. If the player has a full
 *          hand, this returns -1.
 */
short int posOfCardNeeded(Player *player);

#endif
