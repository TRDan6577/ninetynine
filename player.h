/**
 * File: player.h
 * Purpose: Header file for player.c
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#ifndef PLAYER_H
#define PLAYER_H

/*****************************************************************************
 *                                                                           *
 *                          Includes and Defines                             *
 *                                                                           *
 *****************************************************************************/

#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>

#include"card.h"

#define NUM_STARTING_CARDS 3
#define NUM_STARTING_TOKENS 3
#define MAX_LEVEL 3 // Only three levels of AI
#define MIN_LEVEL 0 // The lowest level is a player
#define SIZE_OF_SUIT 5 // Number of lines required to draw the suit

/*****************************************************************************
 *                                                                           *
 *                           Player Structure                                *
 *                                                                           *
 *****************************************************************************/

typedef struct player_t {
    char *name; // The name of the player
    short int numCards; // The number of cards in the player's hand
    short int numTokens; // The number of tokens left (lose 3 and you're out)
    Card *cards[3]; // Each player starts with 3 cards
    short int level; // The level of the AI. Zero indicates that it is a human
    bool inGame; // Tells whether the player is still in the game or not
    bool inRound; // Tells whether the player is still in the round or not
} Player;

/*****************************************************************************
 *                                                                           *
 *                         Function Declarations                             *
 *                                                                           *
 *****************************************************************************/

/**
 * Purpose: Creates a new player for the 99 card game
 * @param (char *) name - the name of the new player
 * @param (short int) level - the level of the AI (zero if player is a person)
 * @return (Player *) the newly made player with the given name
 */
Player *createPlayer(char *name, short int level);

/**
 * Purpose: Cleans up after creating a new player
 * @param (Player*) deadMan - the player to kill - I mean free
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

/**
 * Pre: Player can actually play a card
 * Purpose: Gives the user a chance to enter a card from stdin. Cards are printed
 *          to stdout via another function call (print playerTurn) and the player
 *          must choose the first, second, or third card {1|2|3}. This function
 *          also determines if the player chooses a card that goes over 99.
 * @param (Player *) player - the player playing the turn
 * @param (short int) runningTotal - the total value of the stack of cards
 * @param (bool *) incrementor - a pointer to a bool. Determines turn order
 * @param (Card **) discardPile - the array of Card* that have been played
 * @param (short int*) turnTracker - keeps track of whose turn it is
 * @param (short int) index - the index into the discardPile
 * @return (short int) the numerical value to add to the stack
 */
short int humanTurn(Player *player, short int runningTotal, bool *incrementor,
        Card *discardPile[DECK_SIZE], short int *turnTracker, short int index);

/*****************************************************************************
 *                                                                           *
 *                           Drawing Functions                               *
 *                                                                           *
 *****************************************************************************/


/**
 * Purpose: Prints a nice output for the player to view before choosing a card
 *          to play from his or her hand
 * @param (Player *) p - the player's hand to print out
 * @param (short int) runningTotal - the current value of all the cards played
 */
void printPlayerTurn(Player *p, short int runningTotal);

/**
 * Purpose: Prints the top and bottom boarders of the card
 */
void printTopBottomBoarder();

/**
 * Purpose: Prints the top few lines of the cards
 * @param (char) value1 - the value of the first card
 * @param (char) value2 - the value of the second card
 * @param (char) value3 - the value of the third card
 */
void printTopLines(char value1, char value2, char value3);

/**
 * Purpose: Prints the bottom few lines of the cards
 * @param (char) value1 - the value of the first card
 * @param (char) value2 - the value of the second card
 * @param (char) value3 - the value of the third card
 */
void printBottomLines(char value1, char value2, char value3);

/**
 * Purpose: Determines which function to call depending on the suit of the card
 *          and calls that function to print the correct line
 * @param (char) suit - the suit of the card
 * @param (int) line - the line number to print
 */
void determineSuit(char suit, int line);

/**
 * Purpose: Prints out the heart onto a card
 * @param (int) line - which line in the drawing to draw
 */
void printHeart(int line);

/**
 * Purpose: Prints out the spade onto a card
 * @param (int) line - which line in the drawing to draw
 */
void printSpade(int line);

/**
 * Purpose: Prints out the diamond onto a card
 * @param (int) line - which line in the drawing to draw
 */
void printDiamond(int line);

/**
 * Purpose: Prints out the club onto a card
 * @param (int) line - which line in the drawing to draw
 */
void printClub(int line);

/**
 * Purpose: Randomize the order in which players play cards
 * @param (Player**) players - the list of players
 * @param (short int) numPlayers - the number of players
 */
void shufflePlayers(Player** players, short int numPlayers);


#endif
