# ninetynine
A terminal-based version of the card game 99. Amaze your friends with your kindergarden level addition skills!

## Synopsis
This program is for those that are desperately bored or REALLY like games that are largely about chance. The
basic rules and guidelines are as follows:
>Players take turns playing a single card from their hand onto a pile. A running total of the values of the cards
played is kept. If a player is unable to play a card without the value of the stack going over 99, he or she loses
a 'token' (basically just think of loosing a token as a strike in baseball; you get three and then you're out of
the game). The value of a card is based on the number, ex. 2 of heart is worth 2 on the stack. There are some 
exceptions. 

1. 3 has a value of three and the next player's turn is skipped
2. 4 has a value of zero and the turn order is reversed (turn order is not reversed if there are only two players)
3. 9 changes the value of the stack to 99. This occurs independently to the previous value of the stack
4. 10 can be +-10
5. Jacks and Queens are worth 10
6. Kings are worth 0
7. Aces are worth 1 or 11

## Code Example
(Note: used images because formatting the output in the README.md would have taken FOREVER)
![alt tag](https://raw.githubusercontent.com/TRDan6577/ninetynine/master/exampleOutput/gamePic1.JPG)
![alt tag](https://raw.githubusercontent.com/TRDan6577/ninetynine/master/exampleOutput/gamePic2.JPG)
![alt tag](https://raw.githubusercontent.com/TRDan6577/ninetynine/master/exampleOutput/gamePic3.JPG)

## Installation
> $git clone https://github.com/TRDan6577/ninetynine.git

Navigate to the directory where you downloaded it and compile and link with gcc. No special arguments required

## Running the Program
> $./ninenine <yourPlayerName> {computerPlayer:{1 | 2 | 3}} [morePlayers]...

You must have at least two players playing and cannot have a game with more than 5 players. Computer players
are created by placing a colon in a player's name followed by their difficulty. 1 for easiest and 3 for hardest

## Contributors
Thomas Daniels

Special Thanks to Jacob Huynh for the idea
