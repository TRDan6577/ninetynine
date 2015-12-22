/**
 * File: ninenine.h
 * Purpose: Header file for ninenine functions
 * Author: Tom Daniels <trd6577@g.rit.edu>
 */

#ifndef NINENINE_H
#define NINENINE_H

/******************************************************************************
 *                           Includes and Defines                             *
 *****************************************************************************/


#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_PLAYERS 5

static const char userDelimiter = " "; // The splitter for strtok
static const char difficultyDelimiter = ":"; // Another splitter for strtok
static const short int numPlayers; // The number of players


/******************************************************************************
 *                           Function Declarations                            *
 *****************************************************************************/


/**
 * Purpose: Checks the command line arguments for general errors such as a 
 *          player count that exceeds 5. Specific errors such as an incorrect
 *          difficulty level is not checked here. If an error is found, the
 *          function prints a message to stderr and exits
 * @param (int) argc - the number of arrays in argv
 * @param (char**) argv - arrays of strings
 */
void errorCheck(int argc, char **argv);

#endif
