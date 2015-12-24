/**
 * File: ninenine.h
 * Purpose: Header file for ninenine.c. Includes function decs, includes, defs,
 *          and other information.
 * Author: Tom Daniels <trd6577@g.rit.edu>
 */

#ifndef NINENINE_H
#define NINENINE_H

/******************************************************************************
 *                           Includes and Defines                             *
 *****************************************************************************/


#define MAX_PLAYERS 5
#define NUM_CARDS_IN_DECK 52
#define HUMAN_PLAYER 0

#include"player.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

static const char *difficultyDelimiter = ":"; // Another splitter for strtok


/******************************************************************************
 *                              Global Variables                              *
 *****************************************************************************/


/**
 * Purpose: Holds all of the cards usable by the players
 */
Card *deck[NUM_CARDS_IN_DECK];

/**
 * Purpose: Holds all of the cards used by the players. When the discard pile
 *          becomes full (52 entries long), the deck is made to point to it
 *          and the discard points to the empty list of cards that was
 *          previously the deck
 */
Card *discard[NUM_CARDS_IN_DECK];


/******************************************************************************
 *                           Function Declarations                            *
 *****************************************************************************/


/**
 * Purpose: Checks the command line arguments for general errors such as a 
 *          player count that exceeds 5. Specific errors such as an incorrect
 *          difficulty level is not checked here. If an error is found, the
 *          function prints a message to stderr and exits
 * @param (int) argc - the number of arrays in argv
 */
void errorCheck(int argc);

/**
 * Purpose: Does the initial setup for the game engine. Gets the deck, shuffles
 *          the deck, and gets the players set up with their starting hands.
 */

#endif
