/**
 * File: player.c
 * Purpose: Serves as a representation of a player in the 99 card game
 * Author: Tom Daniels <trd6577@g.rit.edu>
 * Version Control: Git
 */

#include"player.h"

Player *createPlayer(char *name, short int level){

    // The level passed in must be between 0 and 3 inclusive
    if(!(MIN_LEVEL <= level && level <= MAX_LEVEL)){
        fprintf(stderr, "Levels for AI can only be 1, 2, or 3 (easy, medium, "
                " or hard, respectively)\n");
        return NULL;
    }

    // Create the new player
    Player *newPlayer = calloc(1, sizeof(Player));

    // Set the player's attributes
    newPlayer->name = name;
    newPlayer->level = level;
    newPlayer->numCards = NUM_STARTING_CARDS;
    newPlayer->inGame = true;
    newPlayer->inRound = true;
    newPlayer->numTokens = NUM_STARTING_TOKENS;
    for(int i = 0; i < NUM_STARTING_CARDS; i++){ 
        newPlayer->cards[i] = NULL; // Player wasn't dealt cards yet
    }

    return newPlayer;
}

void destroyPlayer(Player *deadMan){

    // Check to see if the player is NULL
    if(deadMan){
        // Free the cards the player is holding
        for(int i = 0; i < NUM_STARTING_CARDS; i++){
            if(deadMan->cards[i]){
                free(deadMan->cards[i]);
            }
        }

        // Free the actual player
        free(deadMan);
    }
}

short int posOfCardNeeded(Player *player){
    // Look through the player's hand one by one to determine the missing place
    // of the card
    short int i = 0;
    while(player->cards[i] && i < NUM_STARTING_CARDS){
        i++;
    }

    return i;
}

short int humanTurn(Player *player, short int runningTotal, bool *incrementor,
        Card *discardPile[DECK_SIZE], bool *skipPlayer, short int index){
    short int value; // Value to add to the running total
    short int cardChoosen; // The index of the card choosen
    printPlayerTurn(player, runningTotal); // Display the player's hand and some stats

    while(true){
        // Player should only enter {1|2|3}. Get char and purge the input stream
        printf("Pick a card (1,2,3): ");
        char c = getchar();
        __fpurge(stdin);

        // Check if the value entered is {1|2|3}. If not, ask again
        if(!(c > '0' && c < '4')){
            printf("Value entered is not 1, 2, or 3\n");
            continue;
        }

        cardChoosen = (c-'0')-1; // -1 to get the index

        // If the card choosen can have more than 1 value, determine the value
        // that the user wishes to use
        if(player->cards[cardChoosen]->special){
            
            if(player->cards[cardChoosen]->sValue == 'a'){
                // Get the value of the special card
                while(true){
                    printf("Please enter a value for the ace (1 or 11): ");
                    scanf("%hd", &value);
                    __fpurge(stdin);

                    // If a correct value was entered, break
                    if(value == 1 || value == 11){
                        break;
                    }
                    // Otherwise, loop until you get a correct answer
                }
            }

            if(player->cards[cardChoosen]->sValue == '9'){
                // Find number that makes the running total = 99
                value = 99-runningTotal;
            }

            if(player->cards[cardChoosen]->sValue == 't'){
                // Get the value of the special card
                while(true){
                    printf("please enter a value for the ten (10 or -10): ");
                    scanf("%hd", &value);
                    __fpurge(stdin);

                    // If a correct value was entered, break
                    if(value == -10 || value == 10){
                        break;
                    }
                    // Otherwise, loop until you get a correct answer
                }
            }

            if(player->cards[cardChoosen]->sValue == '4'){
                value = FOUR;
            }

            if(player->cards[cardChoosen]->sValue == '3'){
                value = THREE;
            }

        }
        else{
            value = player->cards[cardChoosen]->dValue;
        }
        
        // Determine if the value is valid to play
        if(runningTotal+value > 99){
            printf("Value of card chosen exceeds 99\n");
            continue;
        }

        // If you're here it means the card is valid. Break
        break;
    }

    // Clear the screen
    system("clear");

    // Do 3 and 4's special actions AFTER we've determined that they can
    // actually play the three or four
    if(player->cards[cardChoosen]->sValue == '4'){
        *incrementor = !(*incrementor); // Invert the incrementor
    }

    if(player->cards[cardChoosen]->sValue == '3'){
        *skipPlayer = true;
    }

    // Place the played card in the discard pile
    discardPile[index] = player->cards[cardChoosen];
    player->cards[cardChoosen] = NULL;

    // Add the value of the card to the discard pile
    return value;
}

short int computerTurn(Player *player, short int runningTotal, bool *incrementor,
        Card *discardPile[DECK_SIZE], bool *skipPlayer, short int index){

    short int value; // The value to be added to the stack
    short int cardChoice; // The index of the choosen card

    /*
    // This boolean determines if a level two player is going to play as a level
    // 1 or a level 3 player this turn
    bool level1 = false;

    // If the computer player's level is two, set the level for this turn
    if(player->level == 2){
        level1 = rand()%2;
    }

    if(player->level == 1 || level1){*/
    // Randomly pick a card until we find one to play
    while(1){
        bool canPlay[3] = {true, true, true}; // Assume we can play all cards

        cardChoice = rand()%3;

        // In order to prevent the possibility of never choosing a valid card,
        // if we pick an invalid card, just increment the card choice by one
        // until we can play a valid card.
        while(!canPlay[cardChoice]){
            cardChoice = (cardChoice+1)%3;
        }

        // Determine any special values (example: TEN can be +-10)
        if(player->cards[cardChoice]->special){

            // Determine value for a ten
            if(player->cards[cardChoice]->sValue == 't'){
                if(runningTotal+10 <= 99){
                    value = 10;
                }
                else{
                    value = -10;
                }
            }
            // Determine value for an ace
            else if(player->cards[cardChoice]->sValue == 'a'){
                if(runningTotal+11 <= 99){
                    value = 11;
                }
                else if(runningTotal+1 <= 99){
                    value = 1;
                }
                else{
                    canPlay[cardChoice] = false;
                    continue;
                }
            }
            else if(player->cards[cardChoice]->sValue == '9'){
                value = 99-runningTotal;
            }
            // Set the value for the rest of the cards as their dValue
            else{

                // If we can't play the card, note that and pick another
                if(player->cards[cardChoice]->dValue > 99){
                    canPlay[cardChoice] = false;
                    continue;
                }

                value = player->cards[cardChoice]->dValue;

            }
        }
        // Set the value as the dValue for all the other cards
        else{
            if(player->cards[cardChoice]->dValue > 99){
                canPlay[cardChoice] = false;
                continue;
            }

            value = player->cards[cardChoice]->dValue;
        }

        // If we made it here, the value choose is valid
        break;
    }
    /*}
    else{
        // Level three stuff here
    }*/

    if(player->cards[cardChoice]->sValue == '4'){
        *incrementor = !(*incrementor); // Invert the incrementor
    }

    if(player->cards[cardChoice]->sValue == '3'){
        *skipPlayer = true;
    }

    printf("[+] Player %s played %c with a value of %d\n", 
            player->name, player->cards[cardChoice]->sValue, value);
   
    // Place the played card in the discard pile
    discardPile[index] = player->cards[cardChoice];
    player->cards[cardChoice] = NULL;

    
    return value;
}

void shufflePlayers(Player** players, short int numPlayers){
    int j;
    for(int i = 0; i < numPlayers - 1; i++){
        j = i + rand() / (RAND_MAX / (numPlayers-i)+1);
        Player *temp = players[j];
        players[j] = players[i];
        players[i] = temp;
    }
}


/*
 *              PRINTING FUNCTIONS
 */


void printPlayerTurn(Player *p, short int runningTotal){
    // Print out the player's name and running total
    printf("%s's turn\n", p->name);
    printf("Running Total: %02hd\n", runningTotal);

    // Print the player's hand
    printf("Your Hand:\n");
    printf("            1                        2                        3\n");
    printTopBottomBoarder();
    printTopLines(p->cards[0]->sValue, p->cards[1]->sValue, 
            p->cards[2]->sValue);

    for(int i = 0; i < SIZE_OF_SUIT; i++){
        printf("  ");
        determineSuit(p->cards[0]->suit, i);
        printf("   ");
        determineSuit(p->cards[1]->suit, i);
        printf("   ");
        determineSuit(p->cards[2]->suit, i);
        printf("\n");
    }

    printBottomLines(p->cards[0]->sValue, p->cards[1]->sValue, 
            p->cards[2]->sValue);
    printTopBottomBoarder();
}

void determineSuit(char suit, int line){
    switch(suit){
        case 's':
            printSpade(line);
            break;

        case 'd':
            printDiamond(line);
            break;

        case 'h':
            printHeart(line);
            break;

        case 'c':
            printClub(line);
            break;
    }
}

void printTopLines(char value1, char value2, char value3){
    printf("  |%c                   |   |%c                   |   |%c                   |\n",
            value1, value2, value3);
    printf("  |                    |   |                    |   |                    |\n");
    printf("  |                    |   |                    |   |                    |\n");
}

void printBottomLines(char value1, char value2, char value3){
    printf("  |                    |   |                    |   |                    |\n");
    printf("  |                    |   |                    |   |                    |\n");
    printf("  |                   %c|   |                   %c|   |                   %c|\n",
            value1, value2, value3);

}

void printHeart(int line){
    switch(line){
        case 0:
            printf("|       __  __       |");
            break;

        case 1:
            printf("|      (  \\/  )      |");
            break;

        case 2:
            printf("|       \\    /       |");
            break;

        case 3:
            printf("|        \\  /        |");
            break;

        case 4:
            printf("|         \\/         |");
            break;
    }
}

void printClub(int line){
    switch(line){
        case 0:
            printf("|        ___         |");
            break;

        case 1:
            printf("|      _(   )_       |");
            break;

        case 2:
            printf("|     (__   __)      |");
            break;

        case 3:
            printf("|         ^          |");
            break;

        case 4:
            printf("|        /_\\         |");
            break;
    }
}

void printDiamond(int line){
    switch(line){
        case 0:
            printf("|         /\\         |");
            break;

        case 1:
            printf("|        /  \\        |");
            break;

        case 2:
            printf("|       <    >       |");
            break;

        case 3:
            printf("|        \\  /        |");
            break;

        case 4:
            printf("|         \\/         |");
            break;
    }
}

void printSpade(int line){
    switch(line){
        case 0:
            printf("|         ^          |");
            break;

        case 1:
            printf("|        / \\         |");
            break;

        case 2:
            printf("|       (   )        |");
            break;

        case 3:
            printf("|         ^          |");
            break;

        case 4:
            printf("|        /_\\         |");
            break;
    }
}

void printTopBottomBoarder(){
        printf("   --------------------     --------------------     "
                "--------------------\n");
}


