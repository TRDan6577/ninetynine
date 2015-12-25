/**
 * File: ninenine.c
 * Purpose: The purpose of this program is to simulate a game of 99. 99 is a 
 *          card game whereby 2+ players must take turns one by one playing
 *          a card from his or her hand to try and get to the number 99 without
 *          going over. Read more about the game online.
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#include"ninenine.h"

/**
 * Purpose: The main runner for the program
 * @param (int) argc - the number of arrays in argv
 * @param (char**) argv - arrays of strings
 */
int main(int argc, char **argv){

    // Error check
    errorCheck(argc);

    // Important variables
    const short int numPlayers = argc-1;
    Player *players[numPlayers];
    Card *deck[DECK_SIZE];
    //Card *discardPile[DECK_SIZE];

    // Parse the command line arguments
    for(int i = 1; i < argc; i++){

        char *playerName;
        char *playerDifficulty;
        char *temp; // A pointer needed for strtol

        playerName = strtok(argv[i], difficultyDelimiter); // Get player's name
        
        // If this is the user's player name, then the level is zero
        if(i == 1){
            players[i-1] = createPlayer(playerName, HUMAN_PLAYER);
        }
        // Otherwise set the level to the level indicated by :X in the cmd args
        else{
            playerDifficulty = strtok(NULL, difficultyDelimiter);
            short int numericDifficulty = (short int)strtol(playerDifficulty, &temp, 10);
            players[i-1] = createPlayer(playerName, numericDifficulty);

            // If the Player * returned by createPlayer was NULL, an error
            // occurred and we need to clean up
            if(!(players[i-1])){
                cleanupPlayers(players, (short int)i-2); // i-2 because we can't free the NULL player
            }
        }
    }

    // Fill the deck with cards
    initDeck(deck);

    // Shuffle the deck
    shuffle(deck);

    // TODO: deal the cards -> make a function for this too!

    cleanupPlayers(players, numPlayers);
    cleanupDeck(deck);

    return 0;
}

void errorCheck(int argc){
    // If there were two command line arguments then print the usage message
    if(argc <= 2){
        fprintf(stderr, "usage: ninenine playerName AIPlayerName:difficulty "
                "[AIPlayerName:difficulty] ...\n");
        exit(0);
    }

    // If the number of AI is greater than 4 (so more than 5 players)
    if(argc > MAX_PLAYERS+1){
        fprintf(stderr, "The maximum number of players is 5 (user plus 4 AI)\n");
        exit(0);
    }
}

void cleanupPlayers(Player **players, short int numPlayers){
    // Clean up the players
    for(int i = 0; i < numPlayers; i++){
        destroyPlayer(players[i]);
    }
}

void cleanupDeck(Card *deck[DECK_SIZE]){
    for(int i = 0; i < DECK_SIZE; i++){
        if(deck[i]){
            free(deck[i]);
        }
    }
}
