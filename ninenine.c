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
    short int numPlayers = argc-1; // Not const because the number of players can decrease
    Player *players[numPlayers];
    Card *deck[DECK_SIZE];
    Card *discardPile[DECK_SIZE];

    // Parse the command line arguments
    // i = 1 because the first arg is the name of the program
    for(int i = 1; i < argc; i++){

        char *playerName;
        char *playerDifficulty;
        char *temp; // A pointer needed for strtol

        playerName = strtok(argv[i], difficultyDelimiter); // Get player's name
        
        // If this is the user's player name, then the level is zero
        if(i == 1){
            // i-1 because we need to start at index zero in the array
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
                // i-2 because we can't free the NULL player
                cleanupPlayers(players, (short int)i-2);
                return EXIT_FAILURE;
            }
        }
    }

    // Fill the deck with cards and set the discard pile to empty
    initDeck(deck, discardPile);

    // Shuffle the deck and mix the order of the players
    shuffle(deck);
    shufflePlayers(players, numPlayers);

    // Deal the cards
    dealCards(players, numPlayers, deck);

    // Play the Game
    playGame(players, numPlayers, deck, discardPile);

    

    // Cleanup the cards and the players
    cleanupDeck(deck, discardPile);
    cleanupPlayers(players, numPlayers);

    return 0;
}

void errorCheck(int argc){
    // If there were two command line arguments then print the usage message
    if(argc <= 2){
        fprintf(stderr, "usage: ./ninenine playerName AIPlayerName:difficulty "
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

void cleanupDeck(Card *deck[DECK_SIZE], Card *discardPile[DECK_SIZE]){
    // Free the cards in the deck that haven't been dealt
    for(int i = 0; i < DECK_SIZE; i++){
        if(deck[i]){
            free(deck[i]);
        }
    }

    // Free the remaining cards in the discard pile
    for(int i = 0; i < DECK_SIZE; i++){
        if(discardPile[i]){
            free(discardPile[i]);
        }
    }
}

void dealCards(Player **players, short int numPlayers, Card *deck[DECK_SIZE]){
    // Pick the player to get the card
    for(int p = 0; p < numPlayers; p++){
        // Check to make sure the player's still in the game, then pick the card
        if(players[p]->inGame){
            for(int c = 0; c < NUM_STARTING_CARDS; c++){
                // Deal the card
                dealCard(players[p], posOfCardNeeded(players[p]), deck);
            }
        }
    }
}

void dealCard(Player *player, short int position, Card *deck[DECK_SIZE]){
    // Give the player the next card on top of the deck
    player->cards[position] = deck[cardsDealt];
    
    // Remove that card from the deck
    deck[cardsDealt] = NULL;

    // Increment the number of cards dealt
    cardsDealt++;
}

void preRound(Player **players, short int numPlayers){
    for(int i = 0; i < numPlayers; i++){
        if(players[i]->inGame){
            players[i]->inRound = true;
        }
    }
}

void playGame(Player **players, short int numPlayers, Card *deck[DECK_SIZE],
        Card *discardPile[DECK_SIZE]){

    // Players may be booted during the game. We need to keep track of the players
    short int playersStillPlaying = numPlayers;

    // Loop until there is only one player playing each round (a WINNER!!!)
    while(playersStillPlaying > 1){

        short int i = 0; // Need to keep track of where in Players we are
        short int runningTotal = 0;
        short int playersInRound = playersStillPlaying;
        short int playersAtBegin = playersStillPlaying;
        
        // Set all remaining players as playing the next round
        preRound(players, numPlayers);

        // Determines the order the players take turns. True increments i while
        // false decrements i as i iterates through the list of players
        bool *incrementor = malloc(sizeof(bool));
        *incrementor = true;

        // Tell us when we need to skip a player (because a 3 was played)
        bool *skipPlayer = malloc(sizeof(bool));
        *skipPlayer = false;

        // Play the round
        while(playersInRound > 1){

            // Determine if the player is no longer in the game or round, go to
            // the next player
            if(!(players[i]->inRound)){
                if(*incrementor){
                    i++;
                    i=i%numPlayers;
                }
                else{
                    i--;
                    if(i == -1){
                        i = numPlayers-1;
                    }
                }

                continue;
            }

            /*
             * DETERMINE IF THE PLAYER CAN PLAY ANY OF HIS OR HER CARDS
             */

            // Check to make sure the player can even play a card without 
            // going over 99
            bool canPlay = false; // Assume they can't play until proven otherwise

            for(int c = 0; c < NUM_STARTING_CARDS; c++){
                
                // Calculate the lowest value for any special card
                if(players[i]->cards[c]->special){

                    // Detemine value if card is an ace
                    if(players[i]->cards[c]->sValue == 'a' && 
                            runningTotal + 1 <= 99){
                        canPlay = true;
                    }

                    // If the card is a 4, 9, or 10, those can always be played
                    if(players[i]->cards[c]->sValue == 't' ||
                            players[i]->cards[c]->sValue == '9' ||
                            players[i]->cards[c]->sValue == '4'){
                        canPlay = true;
                    }

                    // Determine validity of 3
                    if(players[i]->cards[c]->sValue == '3' &&
                            runningTotal+THREE <= 99){
                        canPlay = true;
                    }

                }
                else{
                    if(runningTotal + players[i]->cards[c]->dValue <= 99){
                        canPlay = true;
                    }
                }

                if(canPlay){
                    break;
                }
            }

            /*
             * KICK THE PLAYER OR HAVE THE PLAYER TAKE A TURN DEPENDING ON
             * WHETHER OR NOT HER OR SHE CAN TAKE A TURN
             */

            // If the player can play, call the appropriate function for
            // taking a turn (depends on whether the player is human or a
            // computer
            if(canPlay){
                // Play a card and discard it
                runningTotal += (players[i]->level) ? 
                    (computerTurn(players[i], runningTotal, incrementor,
                                  discardPile, skipPlayer,
                                  cardsDealt-(playersAtBegin*NUM_STARTING_CARDS)))
                    : (humanTurn(players[i], runningTotal, incrementor,
                                  discardPile, skipPlayer,
                                  cardsDealt-(playersAtBegin*NUM_STARTING_CARDS)));
                // Draw a card
                dealCard(players[i], posOfCardNeeded(players[i]), deck);
            }
            else{
                // The player cannot play a card. Take away a token and remove
                // them from the current round
                printf("[-] Player %s is unable to play any cards. A token has been\n"
                        "\ttaken away from %s\n", players[i]->name, players[i]->name);
                players[i]->numTokens--;
                players[i]->inRound = false;
                playersInRound--;

                if(!players[i]->numTokens){
                    // If the player is out of tokens, they are removed from the
                    // game
                    printf("[-] Player %s is out of tokens and has been removed from\n"
                            "\tthe game\n", players[i]->name);
                    players[i]->inGame = false;
                    playersStillPlaying--;
                }
            }

            // Appropriately decide whose turn is next
            if(*incrementor){
                i++;
                i=i%numPlayers;
                if(*skipPlayer){
                    printf("[*] Player %s's turn was skipped\n", 
                            players[i]->name);
                    i++;
                    *skipPlayer = false;
                }
                i=i%numPlayers;
            }
            else{
                i--;
                if(i < 0){
                    i = numPlayers+i;
                }
                if(*skipPlayer){
                    printf("[*] Player %s's turn was skipped\n", 
                            players[i]->name);
                    i--;
                    *skipPlayer = false;
                }
                if(i < 0){
                    i = numPlayers+i;
                }
            }

        } // End of the round

        // If there's more than 1 person playing, then go through the list of
        // players, discard their hand, shuffle the deck and the discard pile
        // together and deal a new hand to the player still playing for the
        // next round
        if(playersStillPlaying > 1){
            short int cardsNotInDiscard = -1;
            for(int p = 0; p < numPlayers; p++){
                for(int c = 0; c < NUM_STARTING_CARDS; c++){

                    // If they have a card, put it in the discard pile
                    if(players[p]->cards[c]){
                        discardPile[cardsDealt-(p*NUM_STARTING_CARDS+c)+
                        cardsNotInDiscard] = players[p]->cards[c];
                        players[p]->cards[c] = NULL;
                    }
                    else{
                        cardsNotInDiscard--;
                    }
                }
            }

            printf("[*] End of the round! Starting a new round....\n\n");

            // Wait for user input to continue
            printf("Press any key to continue ");
            getchar();

            // Clear the screen
            system("clear");


            // Shuffle the discard pile and the deck together
            resetDeck(deck, discardPile, cardsDealt);
            
            cardsDealt = 0;

            // Deal new hands to the players still in the game
            dealCards(players, numPlayers, deck);
        }

        free(skipPlayer);
        free(incrementor);
    } // End of the game

    // Print the winner!
    for(int i = 0; i < numPlayers; i++){
        if(players[i]->inGame){ // The winner is the only player in the game
            printf("[*] The winner is %s!!!\n", players[i]->name);
        }
    }
}
