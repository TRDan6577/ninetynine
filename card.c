/**
 * File: card.c
 * Purpose: Deals with creating cards and decks
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

// The special playing cards
#define KING 'k' // Passes the turn. Same thing as playing a card with dValue=0
#define QUEEN 'q' // Worth 10
#define JACK 'j' // Worth 10
#define ACE 'a' // Worth 1 or 11; player chooses
#define THREE 3 // Skips the next player's turn
#define FOUR 4 // Reverses play order
#define NINE 9 // Stack value becomes 99, regardless of previous value
#define TEN 10 // Player determine whether this means +-10

#include<ctype.h>
#include<stdbool.h>
#include<stdio.h>

/**
 * Purpose: Structure to represent a single card. Has the following attributes:
 *          1) Suit - Diamond, Spade, Heart, Club
 *          2) Value - 2 through 10, Jack, Queen, King, Ace
 */
typedef struct Card {
    char suit; // d, s, h, c
    char sValue; // String version of its value
    short int dValue; // Decimal value
    bool special; // If the card has some sort of special property
};

/**
 * Purpose: Creates a card
 * @param (char) suit - the suit of the card
 * @param (char) value - the value of the card 
 * @return (Card *) the newly made card
 */
Card *createCard(char suit, char value){
    
    // Create the new card
    Card *newCard = calloc(1, sizeof(Card));

    // Assign the known attributes
    newCard->suit = suit;
    newCard->sValue = value;

    // If value is a digit and not a face card or an ace
    if(isdigit(value)){

        // Make a temporary string to hold the suit
        char *temp;

        // And put the decimal value into the card instance
        newCard->dValue = (short int)strtol(&(newCard->sValue), &temp, 10);
    }
    // If value is a face card or an ace
    else{
        // Determine which card it is
        switch(value){
            // Kings are worth either 0
            // Aces are worth either 1 or 11
            case KING:
            case ACE:
                newCard->dValue = 0; // User determines value of card later
                break;

            // Both Queens and Jacks are worth 10
            case QUEEN:
            case JACK:
                newCard->dValue = 10;
                break;
        }
    }

    // Determine if the card is special (3, 4, 9, 10, K)
    if(value == THREE || value == FOUR || value == NINE || value == TEN){
        newCard->special = true;
    }
    else{
        newCard->special = false;
    }

    return newCard;
}
