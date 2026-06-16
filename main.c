#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct{
    int value;
    int display;
}Card;

Card deck[52] = {
                {2, 2},{2, 2},{2, 2},{2, 2},
                {3, 3},{3, 3},{3, 3},{3, 3},
                {4, 4},{4, 4},{4, 4},{4, 4},
                {5, 5},{5, 5},{5, 5},{5, 5},
                {6, 6},{6, 6},{6, 6},{6, 6},
                {7, 7},{7, 7},{7, 7},{7, 7},
                {8, 8},{8, 8},{8, 8},{8, 8},
                {9, 9},{9, 9},{9, 9},{9, 9},
                {10, 10},{10, 10},{10, 10},{10, 10},
                {10, 11},{10, 11},{10, 11},{10, 11}, // Display code for jack
                {10, 12},{10, 12},{10, 12},{10, 12}, // Display code for queen
                {10, 13},{10, 13},{10, 13},{10, 13}, // Display code for king
                {1, 14},{1, 14},{1, 14},{1, 14} // Display code for ace
            };
int cardDrawIterator = 0; //iterator for the drawing of cards in getTopCard()
bool game = true;
int userChoice = 0;
Card playerHand[5] = {};
Card dealerHand[5] = {};
int P_handPositionIterator = 1; // iterators for the position cards are put into in the hand for: Player
int D_handPositionIterator = 1; //                                                                Dealer
bool lastChance = false; // true if the player earns 21, and the dealer ai gets a chance to tie


void swap(Card *list, int index1, int index2) {
    Card temp = list[index1];
    list[index1] = list[index2];
    list[index2] = temp;
}

int sum(Card *list, int length) {
    int total = 0;
    for(int i = 0; i < length; i++) {
       total += list[i].value;
    }
    return total;
}

void shuffle(Card *deck, int length) {
    for(int i = length - 1; i > 0; i--) {
        int swappedCardIndex = rand() % (i + 1);
        swap(deck, i, swappedCardIndex);
    }
}
int size, int hand) { //function to return a drawn card without the use of a dynamic array
    Card cardDrawn = deck[cardDrawIterator];
    int aceChoice;
    if(cardDrawn.display == 14) {
        if(hand == 0) {
            printf("You have drawn an ace, would you like it to be a 1 or 11?: ");
            scanf("%d", &aceChoice);
        }
        else if(sum(dealerHand, 5) > 10) {
            aceChoice = 1;
        }
        else {
            aceChoice = 11;
        }
    cardDrawn.value = aceChoice;
    }
    cardDrawIterator++;
    return cardDrawn;
}

const char* displayCard(Card card) {
    switch(card.display) {
        case 2:  return "2";
        case 3:  return "3";
        case 4:  return "4";
        case 5:  return "5";
        case 6:  return "6";
        case 7:  return "7";
        case 8:  return "8";
        case 9:  return "9";
        case 10: return "10";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        case 14: return "Ace";
    }
}

void outCards(Card *hand) {
    for(int i = 0; i < 5; i++) {
        if(playerHand[i].display == 0) {
            continue;
        }
        printf("%s, ", displayCard(playerHand[i]));
    }
}

void turnType(int situ) { //determines what to do based on the user input  
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
                if(playerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(playerHand[i]));
            }
            printf("\n");
            
            printf("Dealers cards:\n");
            printf("?, ");
            for(int i = 1; i < 5; i++) {
                if(dealerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(dealerHand[i]));
            }
            printf("\n");
            printf("Your total is now %d\n", sum(playerHand, 5));
            if(sum(playerHand, 5) == 21) {
                printf("WOW, but it could still be a draw!\n");
                lastChance = true;
            }
            break;
            
        case 1: //player decides to hit
            if(playerHand[4].display != 0) {
                printf("You cannot draw any more cards\n");
                break;
            }

            playerHand[P_handPositionIterator] = getTopCard(deck, 52, 0);
            printf("\nYou drew a card\nIt is a %s\n", displayCard(playerHand[P_handPositionIterator]));
            printf("Your cards:\n");
            for(int i = 0; i < 5; i++) {
                if(playerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(playerHand[i]));
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
                if(dealerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(dealerHand[i]));
            }
            printf("\n");

            
            if(playerHand[4].value != 0) {
                printf("You cannot draw any more cards\n");
                break;
            }
            else {
                printf("Your total is now %d\n", sum(playerHand, 5));
            }
            break;

        case 2: //player decides to stand    
            printf("\nThe dealer flips his first card: It is a %s\n", displayCard(dealerHand[0]));
            printf("Your cards:\n");
            for(int i = 0; i < 5; i++) {
                if(playerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(playerHand[i]));
            }
            printf("\n");
            
            printf("Dealers cards:\n");
            for(int i = 0; i < 5; i++) {
                if(dealerHand[i].value == 0) {
                    continue;
                }
                printf("%s, ", displayCard(dealerHand[i]));
            }
            printf("\n");
            while(sum(dealerHand, 5) < 17 && dealerHand[4].value == 0) {
                dealerHand[D_handPositionIterator] = getTopCard(deck, 52, 1);
                printf("The dealer draws a card\nIt is a %s\n", displayCard(dealerHand[D_handPositionIterator]));
                D_handPositionIterator++;
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
    shuffle(deck, 52);
    
    int choice = 0;
    turnType(0);
    while(game) {
        P_handPositionIterator++;
        if(lastChance) {
            turnType(2);
            break;
        }
        printf("What will you do?: \n1 = Hit 2 = Stand\n");
        scanf("%d", &choice);
        turnType(choice);
    }
}
