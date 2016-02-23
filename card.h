/**
 * File: card.h
 * Purpose: Header file for card.c
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#ifndef CARD_H
#define CARD_H

/******************************************************************************
 *                           Includes and Defines                             *
 *****************************************************************************/


#define KING 'k' // Passes the turn. Same thing as playing a card with dValue=0
#define QUEEN 'q' // Worth 10
#define JACK 'j' // Worth 10
#define ACE 'a' // Worth 1 or 11; player chooses
#define THREE 3 // Skips the next player's turn
#define FOUR 4 // Reverses play order
#define NINE 9 // Stack value becomes 99, regardless of previous value
#define TEN 0 // Player decides +-10. Ten is 0 becuase chars can't be 10
#define DECK_SIZE 52 // Size of standard deck of cards
#define NUM_SUITS 4 // 4 different suits in a deck
#define NUM_VALUES 13 // 13 different values per suit (2-10, A, K, Q, J)

#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h> // For randomness


/******************************************************************************
 *                             Important Fields                               *
 *****************************************************************************/


/**
 * Purpose: Structure to represent a single card. Has the following attributes:
 *          1) Suit - Diamond, Spade, Heart, Club
 *          2) Value - 2 through 10, Jack, Queen, King, Ace
 */
typedef struct card_t {
    char suit; // d, s, h, c
    char sValue; // String version of its value
    short int dValue; // Decimal value
    bool special; // If the card has some sort of special property
} Card;

/**
 * Purpose: Gives all the avalible suits in an array
 */
static const char suits[NUM_SUITS] = {'c', 'd', 'h', 's'};

/**
 * Purpose: Gives all the avalible numbers in an arry
 */
static const char values[NUM_VALUES] = {'2', '3', '4', '5', '6', '7', '8', '9',
    '0', 'j', 'q', 'k', 'a'};


/******************************************************************************
 *                           Function Declarations                            *
 *****************************************************************************/


/**
 * Purpose: Creates a card
 * @param (char) suit - the suit of the card
 * @param (char) value - the value of the card
 * @return (Card *) the newly made card
 */
Card *createCard(char suit, char value);

/**
 * Purpose: Initializes the deck. The deck still needs to be shuffled
 * @param (Card **) deck - the empty deck to fill with cards
 * @param (Card **) discardPile - the pile to mark as empty
 */
void initDeck(Card *deck[DECK_SIZE], Card *discardPile[DECK_SIZE]);

/**
 * Purpose: Shuffles the cards in the deck. Credit for this function goes to
 *          Ben Pfaff (copyright 2004 Ben Pfaff) from 
 *          benpfaff.org/writing/clc/shuffle.html
 * @param (Card **) deck - the deck to shuffle
 */
void shuffle(Card *deck[DECK_SIZE]);

/**
 * Purpose: Puts all the cards in the deck and shuffles it as if the deck was
 *          newly made
 * @param (Card **) deck - the array of Card pointers that will hold all the
 *          cards after this function executes
 * @param (Card **) discardPile - the small amount of cards to be transferedto
 *          to deck
 * @param (short int) index - the number of cards to be moved from the
 *          discardPile to the deck. The deck must have empty positions for
 *          the size of index and the discardPile must have cards only up until
 *          the size of the index. (ex if index = 8, discardPile better have
 *          Card entries from [0..7] and deck must be empty from [0..7]
 */
void resetDeck(Card *deck[DECK_SIZE], Card *discardPile[DECK_SIZE], short int index);

#endif
