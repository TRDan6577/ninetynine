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

/**
 * Purpose: The spliter for strtok. cmd args are PlayerName:difficulty level
 *          so this lets us split on colons.
 */
static const char *difficultyDelimiter = ":";

/**
 * Purpose: Keeps track of the number of cards dealt
 */
short int cardsDealt = 0;



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
 * Purpose: Frees the players
 * @param (Player **) players - the list of players playing the game
 * @param (short int) numPlayers - the number of players playing the game
 */
void cleanupPlayers(Player **players, short int numPlayers);

/**
 * Purpose: Frees the deck and the discard pile
 */
void cleanupDeck();

/**
 * Purpose: Starts a new round whereby this function gives three new cards to 
 *          each player in the game.
 * @param (Player **) players - the list of players
 * @param (short int) numPlayers - the number of players
 */
void dealCards(Player **players, short int numPlayers);

/**
 * Purpose: Deals a single card to a player
 * @param (Player *) player - the player to deal the card to
 * @param (short int) position - the position of the card in the player's list
 *          of cards to deal. When a player plays a card, its value in
 *          player->cards is changed to NULL. The position to deal the card is
 *          the first occurence of NULL
 */
void dealCard(Player *player, short int position);

/**
 * Purpose: Serves as the main running function for the game. Players put
 *          their cards in the discard pile and the game counts a running total
 *          in order to determine which player looses the round.
 * @param (Player **) players - the players playing the game
 * @param (short int) numPlayers - the number of players playing the game
 */
void playGame(Player **players, short int numPlayers);


#endif
