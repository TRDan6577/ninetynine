/**
 * File: card.c
 * Purpose: Deals with creating cards and decks
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#include"card.h"

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
