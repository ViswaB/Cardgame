#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cards.h"

int main( int argc, char* argv[] )
{
    srand( time( NULL ) );      // seed random values
    int n = 0;                  // stores number of cards each player starts with
    int i = 0;                  // stores current round number
    int count1 = 0;             // stores number of player 1's cards
    int count2 = 0;             // stores number of player 2' cards
    Card* player1 = NULL;       // player 1 linked list
    Card* player2 = NULL;       // player 2 linked list
    Card* c  = NULL;            // card to be added when a player wins

    printf( "\n============= CARD BATTLE GAME ============\n" );
    printf( "How many cards will each payer start with? ");
    scanf( "%d", &n );

        /* validate number of cards to start with */
    if( n <= 0 || isdigit( n ) != 0 )
    {
        printf( "Invalid Input. Enter an integer greater than zero( 0 )\n" );
        return 1;
    }
        
    printf( "\n============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n" );
    printf( "Start size: %d cards", n );

    player1 = buildDeck( n );           // build player 1 linked list( deck of cards )
    player2 = buildDeck( n );           // build player 2 linked list( deck of cards )
    
    printf( "\nPlayer 1 starting cards: " );
    printCards( player1 );              // prints player 1 deck( all cards in linked list )

    printf( "\nPlayer 2 starting cards: " );
    printCards( player2 );              // prints player 2 deck( all cards in linked list )
    printf( "\n" );

        /* The game process is below. The loop traverses through both player 1 and player 2 linked lists.
           Compares each card by the type and value of the card. Assigns rewards or penalties 
           based on comparison. */
    while( player1 != NULL && player2 != NULL )
    {
        printf( "\n----- ROUND %d -----\n", i + 1 );

        count1 = getLength( player1 );          // calculates length of player 1 linked list on every iteration of loop
        printf( "Player 1 (%d): ", count1 );
        printCard( player1 );                   // prints current card played by player 1
        printf( "\n" );

        count2 = getLength( player2 );          // calculates length of player 2 linked list on every iteration of loop
        printf( "Player 2 (%d): ", count2 );
        printCard( player2 );                   // prints current card  played by player 2
        printf( "\n" );

        if( player1->type == ATTACK && player2->type == ATTACK )
        {
            printf( "Both players ATTACK.\n");

            if( player1->value > player2->value )
            {
                printf( "Player 1 wins. Player 1 gets a new card\n" );
                c = createCard( );
                player1 = addCard( player1, c );

                printf( "Player 2 loses their next card into the abyss.\n" );
                if( player2->next != NULL )
                    player2 = removeCard( player2->next );
            }

            else if( player1->value < player2->value )
            {
                printf( "Player 2 wins. Player 2 gets a new card\n" );
                c = createCard( );
                player2 = addCard( player2, c );

                printf( "Player 1 loses their next card into the abyss.\n" );
                if( player1->next != NULL )
                    player1 = removeCard( player1->next );
            }

            else
            {
                printf( "It's a tie. Nothing happens.\n" );
            }
        }


        if( player1->type == ATTACK && player2->type == DEFEND )
        {   
            printf( "Player 1 ATTACKs and Player 2 DEFENDs.\n" );

            if( player1->value > player2->value )
            {
                printf( "Player 1 wins. Player 1 gets a new card.\n" );
                c = createCard( );
                player1 = addCard( player1, c );
            }

            else
            {
                printf( "Player 1 loses and Player 2 survives.\n" );
                printf( "Player 1 loses their next card into the abyss.\n" );
                if( player1->next != NULL )
                    player1 = removeCard( player1->next );
            }
        }


        if( player1->type == ATTACK && player2->type == RUN )
        {
            printf( "Player 1 ATTACKs and Player 2 RUNs.\n" );

            printf( "Player 2 loses their next card into the abyss.\n" );
            if( player2->next != NULL )
                player2 = removeCard( player2->next );
        }
        

        if( player1->type == DEFEND && player2->type == ATTACK )
        {   
            printf( "Player 2 ATTACKs and Player 1 DEFENDs.\n" );

            if( player1->value >=  player2->value )
            {
                printf( "Player 2 loses and Player 1 survives.\n" );
                printf( "Player 2 loses their next card into the abyss.\n" );
                if( player2->next != NULL )
                    player2 = removeCard( player2->next );
            }

            else
            {
                printf( "Player 2 wins. Player 2 gets a new card.\n" );
                c = createCard( );
                player2 = addCard( player2, c );
            }
        }

        
        if( player1->type == DEFEND && player2->type == DEFEND )
            printf( "Both players DEFEND. Nothing happens.\n" );
        

        if( player1->type == DEFEND && player2->type == RUN )
        { 
            printf( "Player 1 DEFENDs and Player2 RUNs.\n" );
            
            printf( "Player 1 gets a new card.\n" );
            c = createCard( );
            player1 = addCard( player1, c );
            
            printf( "Player 2 loses their next card into the abyss.\n" );
            if( player2->next != NULL )
                player2 = removeCard( player2->next );
        }


        if( player1->type == RUN && player2->type == ATTACK )
        {
            printf( "Player 2 ATTACKs and Player 1 RUNs.\n" );

            printf( "Player 1 loses their next card into the abyss.\n" );
            if( player1->next != NULL )
                player1 = removeCard( player1->next );
        }
        

        if( player1->type == RUN && player2->type == DEFEND )
        {    
            printf( "Player 2 DEFENDs and Player 1 RUNs.\n" );

            printf( "Player 2 gets a new card.\n" );
            c = createCard( );
            player2 = addCard( player2, c );

            printf( "Player 1 loses their next card into the abyss.\n" );
            if( player1->next != NULL )
                player1 = removeCard( player1->next );
        }
        

        if( player1->type == RUN && player2->type == RUN )
        {
            printf( "Both players RUN.\n" );

            printf( "Both players lose their next card into the abyss.\n" );
            if( player1->next != NULL )
                player1 = removeCard( player1->next );
            if( player2->next != NULL )
                player2 = removeCard( player2->next );
        }

        player1 = player1->next;
        player2 = player2->next;
        i++;
    }

    printf( "\n============ GAME OVER  =============\n" );
    
    printf( "\nPlayer1 ending cards: " );
    printCards( player1 );

    printf( "\nPlayer2 ending cards: " );
    printCards( player2 );

    printf( "\n" );

    if( player1 == NULL && player2 == NULL )
        printf( "\nBoth players ran out of cards. No winner.\n" );

    else if( player1 == NULL && player2 != NULL)
        printf( "\nPlayer 1 ran out of cards. Player 2 wins.\n" );
    
    else
        printf( "\nPlayer 2 ran out of cards. Player 1 wins.\n" );

    printf( "The end.\n" );
    printf( "\n" );
    
    destroyCards( player1 );
    destroyCards( player2 );

    return 0;

}

