#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int deck[52] = {2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,1,1,1,1};
int randIter = 0;
bool game = true;
int userChoice = 0;
int playerHand[5] = {};
int dealerHand[5] = {};
int inc = 1;
bool lastChance = false;

int moveToBack(int *list, int index, int length) {
    int last = length - 1;
    int temp = list[index];
    list[index] = list[last];
    list[last] = temp;
}

int sum(int *list, int length) {
    int total = 0;
    for(int i = 0; i < length; i++) {
       total += list[i];
    }
    return total;
}

int getTopCard(int *deck, int size, int hand) { //function to return a drawn card without the use of a dynamic array
    int handTot;
    int topcard;
    
    if(hand == 0) {
        handTot = sum(playerHand, 5);
    }
    else {
        handTot = sum(dealerHand, 5);
    }
    int topcardI;
    topcardI = rand() % (size - randIter);
    
    if(deck[topcardI] == 1) {
        int acechoice = 0;
        if(hand == 0) {
            printf("You drew an ace\nWould you like it to be a 1 or an 11?: ");
            scanf("%d", &acechoice);
            moveToBack(deck, topcardI, size - randIter);
            randIter++;
            return acechoice;
        }
        else {
            if(sum(dealerHand, 5) + 11 > 21) {
                acechoice = 1;
            }
            else {
                acechoice = 11;
            }
            moveToBack(deck, topcardI, size - randIter);
            randIter++;
            return acechoice;
        }
    }
    moveToBack(deck, topcardI, size - randIter);

    topcard = deck[size - randIter - 1];
    randIter++;
    return topcard;
}



int turnType(int situ) { //determines what to do based on the user input  
    switch(situ) {
        case 0: //begining of the game
            printf("\nDealer draws two cards\n");
            printf("You draw two cards\n");
            
            dealerHand[0] = getTopCard(deck, 52, 1); //gives dealer two cards
            dealerHand[1] = getTopCard(deck, 52, 1);
            
            playerHand[0] = getTopCard(deck, 52, 0); //gives player two cards
            playerHand[1] = getTopCard(deck, 52, 0);
            
            printf("Your cards:\n");
            for(int i = 0; i < 5; i++) {
                printf("%d, ", playerHand[i]);
                if(playerHand[i] == 0) {
                    continue;
                }
            }    
            printf("\n");
            
            printf("Dealers cards:\n");
            printf("?, ");
            for(int i = 1; i < 5; i++) {
                printf("%d, ", dealerHand[i]);
                if(dealerHand[i] == 0) {
                    continue;
                }
            }
            printf("\n");
            printf("Your total is now %d\n", sum(playerHand, 5));
            if(sum(playerHand, 5) == 21) {
                printf("WOW, but it could still be a draw!\n");
                lastChance = true;
            }
            break;
            
        case 1: //player decides to hit
            if(playerHand[4] != 0) {
                printf("You cannot draw any more cards\n");
                break;
            }

            playerHand[inc] = getTopCard(deck, 52, 0);
            printf("\nYou drew a card\nIt is a %d\n", playerHand[inc]);
            printf("Your cards:\n");
            for(int i = 0; i < 5; i++) {
                printf("%d, ", playerHand[i]);
                if(playerHand[i] == 0) {
                    continue;
                }
            }    
            printf("\nYour total is now %d\n", sum(playerHand, 5));
            
            if(sum(playerHand, 5) > 21) {
                printf("You bust :(\n");
                game = false;
                break;
            }
            else if(sum(playerHand, 5) == 21) {
                printf("Nice, but it could still be a draw!\n");
                lastChance = true;
                break;
            }

            printf("Dealers cards:\n");
            printf("?, ");
            for(int i = 1; i < 5; i++) {
                printf("%d, ", dealerHand[i]);
                if(dealerHand[i] == 0) {
                    continue;
                }
            }
            printf("\n");

            
            if(playerHand[4] != 0) {
                printf("You cannot draw any more cards\n");
                break;
            }
            else {
                printf("Your total is now %d\n", sum(playerHand, 5));
            }
            break;

        case 2: //player decides to stand    
            printf("\nThe dealer flips his first card: It is a %d\n", dealerHand[0]);
            printf("Your cards:\n");
            for(int i = 0; i < 5; i++) {
                printf("%d, ", playerHand[i]);
                if(playerHand[i] == 0) {
                    continue;
                }
            }    
            printf("\n");
            
            printf("Dealers cards:\n");
            for(int i = 0; i < 5; i++) {
                printf("%d, ", dealerHand[i]);
                if(dealerHand[i] == 0) {
                    continue;
                }
            }
            printf("\n");
            int incLoop = inc;
            while(sum(dealerHand, 5) < 17 && dealerHand[4] == 0) {
                dealerHand[incLoop] = getTopCard(deck, 52, 1);
                printf("The dealer draws a card\nIt is a %d\n", dealerHand[incLoop]);
                incLoop++;
            }
            printf("Their total is now %d\n", sum(dealerHand, 5));
            if(sum(dealerHand, 5) > 21) {
                printf("The dealer busts and you win!");
                game = false;
            }
            else if(sum(playerHand, 5) > sum(dealerHand, 5)) {
                printf("Your total: %d\n", sum(playerHand, 5));
                printf("You win!");
                game = false;
            }
            else if(sum(playerHand, 5) < sum(dealerHand, 5)) {
                printf("Your total: %d\n", sum(playerHand, 5));
                printf("You lose :(\nDidn't you know that the house always wins?");
                game = false;
            }
            else {
                printf("Your total: %d\n", sum(playerHand, 5));
                printf("It's a draw!");
                game = false;
            }
            break;
    }           
}

int main(void) {
    srand(time(NULL));
    
    int choice = 0;
    turnType(0);
    while(game) {
        inc++;
        if(lastChance) {
            turnType(2);
            break;
        }
        printf("What will you do?: \n1 = Hit 2 = Stand\n");
        scanf("%d", &choice);
        turnType(choice);
    }
}