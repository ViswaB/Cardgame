#include <stdio.h>
#include <stdlib.h>
#include "cards.h"


Card* createCard( )
{
    Card* newCard;

    newCard = ( Card* ) malloc( sizeof( Card ) );

    int r = rand() % 10;

    if( r >= 0 && r <= 3 )
    {
        newCard->type = ATTACK;
        newCard->value = rand() % 5 + 1;
    }

    else if( r >= 4 && r <= 8  )
    {
        newCard->type = DEFEND;
        newCard->value = ( rand() % ( 8 - 3 ) ) + 3;
    }

    else
    {
        newCard->type = RUN;
        newCard->value = rand() % 8 + 1;
    }

    newCard->next = NULL;

    return newCard;    
}


Card* removeCard( Card* head )
{
    Card* ptr = head;

    free( ptr );

    return head;
}


Card* addCard( Card* head, Card* c )
{
    Card* ptr;
    Card* prev = NULL;
    
    if( head == NULL || c->value > head->value )
    {
        c->next = head;
        head = c;
    }

    else
    {

        for( ptr = head; ptr != NULL; ptr = ptr->next )
        {
            if( c->value <= ptr->value )
            {
                if( ptr->next == NULL )
                {   
                    ptr->next = c;
                    break;
                }   
            }
            else
            {
                if( prev != NULL )
                {
                    c->next = ptr;
                    prev->next = c;
                    break;
                }
            }   
            prev = ptr;
        }
    }

    return head;
}


int getLength( Card* head )
{
    Card* ptr;
    int count = 0;

    for( ptr = head; ptr != NULL; ptr = ptr->next )
        count++;

    return count;
}


void printCard( Card* head )
{
    char c;

    if( head->type == ATTACK )
        c = 'A';

    else if( head->type == DEFEND )
        c = 'D';    

    else
        c = 'R';

    printf( "%c%d ", c, head->value );
}


void printCards( Card* head )
{
    if( head == NULL )
        return;

    printCard( head );
    
    printCards( head->next );
}


Card* buildDeck( int n )
{
    int i;
    Card* head = NULL;
    Card* card[ n ];

    for( i = 0; i < n; i++ )
    {
        card[ i ] = createCard( );
        head = addCard( head, card[ i ] );
    }

    return head;
}


Card* destroyCards( Card* head )
{
    Card* p = head;

    while( p != NULL )
    {
        Card* temp = p;
        p = p->next;
        free( temp );
    }

    return NULL;
}

