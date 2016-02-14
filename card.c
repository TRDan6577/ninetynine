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

    // Special case handling 10 becuase you cannot have a char that = 10
    if(!(value == '0')){
        newCard->sValue = value;
    }

    // If value is a digit and not a face card or an ace
    if(isdigit(value)){

        // If the svalue is zero, the dvalue must be +-10
        // If the svalue is four, the dvalue is zero 
        if(value == '0' || value == '4'){
            newCard->dValue = 0;
            if(value == '0'){
                newCard->sValue = 't';
            }
        }
        // Otherwise, convert the sValue to an int
        else{

            // Make a temporary string to hold the suit
            char *temp;

            // And put the decimal value into the card instance
            newCard->dValue = (short int)strtol(&(newCard->sValue), &temp, 10);
        }
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

    // Determine if the card is special (3, 4, 9, 10, A)
    if(value == '3' || value == '4' || value == '9' || value == '0' ||
            value == 'a'){
        newCard->special = true;
    }
    else{
        newCard->special = false;
    }

    return newCard;
}

void initDeck(Card *deck[DECK_SIZE], Card *discardPile[DECK_SIZE]){
    for(int i = 0; i < NUM_SUITS; i++){
        for(int j = 0; j < NUM_VALUES; j++){
            deck[NUM_VALUES*i+j] = createCard(suits[i], values[j]);
            discardPile[NUM_VALUES*i+j] = NULL;
        }
    }
}

void shuffle(Card *deck[DECK_SIZE]){

    // Seed the random number
    srand(time(NULL));

    int j;
    for(int i = 0; i < DECK_SIZE - 1; i++){
        j = i + rand() / (RAND_MAX / (DECK_SIZE-i)+1);
        Card *temp = deck[j];
        deck[j] = deck[i];
        deck[i] = temp;
    }
}
