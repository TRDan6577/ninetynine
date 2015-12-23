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

    errorCheck(int argc, char **argv);

    // Parse the command line arguments
    char *player = strtok(argv, userDelimiter); // First arg is program name

    player = strtok(argv, NULL); // User's player name

    char *playerInfo;

    // While there are players to add...
    while(player){
        playerInfo = strtok(player, difficultyDelimiter); // Get player's name
        // Check if it's the first player then add bots
    }
    
    return 0;
}

void errorCheck(int argc, char **argv){
    // If there were two command line arguments then print the usage message
    if(argc <= 2){
        fprintf(stderr, "usage: ninenine playerName AIPlayerName:difficulty "
                "[AIPlayerName:difficulty] ...\n");
        exit(0);
    }

    // If the number of AI is greater than 4 (so more than 5 players)
    if(argc > MAX_PLAYERS){
        fprintf(stderr, "The maximum number of players is 5 (user plus 4 AI)");
        exit(0);
    }
}
