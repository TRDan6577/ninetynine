/**
 * File: card.h
 * Purpose: Header file for card.c
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#define KING 'k' // Passes the turn. Same thing as playing a card with dValue=0
#define QUEEN 'q' // Worth 10
#define JACK 'j' // Worth 10
#define ACE 'a' // Worth 1 or 11; player chooses
#define THREE 3 // Skips the next player's turn
#define FOUR 4 // Reverses play order
#define NINE 9 // Stack value becomes 99, regardless of previous value
#define TEN 10 // Player determines whether this means +-10

#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

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
 * Purpose: Creates a card
 * @param (char) suit - the suit of the card
 * @param (char) value - the value of the card
 * @return (Card *) the newly made card
 */
Card *createCard(char suit, char value);
