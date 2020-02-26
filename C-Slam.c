#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define numofdices 5
#define numoffaces 6

//Declaring function RollDice to determine random faces in 5 dices
void RollDice(int dicearray[])
{
	int i;
	srand(time(NULL));
	for (i = 0; i < numofdices; i++)
	{
		dicearray[i] = rand() %6 + 1;
	}
}

//Declaring function FindNumofFaces to determine the number of same faces we got when using random number generator
int FindNumofFaces(int dicearray[],int b)
{
    int a = 0;
    int i;
    for (i = 0; i < numoffaces; i++)
    {
        if (dicearray[i] == b)
        {
            a = a + 1;
        }
    }
    return a;
}

void printResult(int resultbasis[])
{
    int TwoPair = 0, Threeofakind = 0, Fourofakind = 0, FullHouse = 0, CSlam = 0, SmallStraight = 0, LargeStraight = 0;
    int i;
    for (i = 0; i < numoffaces; i++)
    {
        //Checking to see if the random numbers form Small Straight
        if (resultbasis[i] != 0)
            SmallStraight += 1;
        else if((resultbasis[i] == 0) && SmallStraight < 4)
            SmallStraight = 0;
        else if((resultbasis[i] == 0) && SmallStraight == 4) //Special Case for the game with random number = {1,2,3,4,6}
            {
                SmallStraight = 4;
                break;
            }

        //Checking to see if the random numbers form Large Straight
        if (resultbasis[i] == 1)
            LargeStraight += 1;
        else if((resultbasis[i] == 0) && LargeStraight < 5)
            LargeStraight = 0;

        //Checking to see if the random numbers form Two Pair or Full House
        if (resultbasis[i] == 2)
        {
            int j;
            for (j = (i + 1); j < numoffaces; j++) //Even if there are 2 same faces, with this for-loop checking whether the rest 3 dices are same faces or not to determine Full House
            {
                if (resultbasis[j] == 2)
                    TwoPair = 4;
                if (resultbasis[j] == 3)
                    FullHouse = 5;
            }
        }

        //Checking to see if the random numbers form Three of a kind or Full House
        if (resultbasis[i] == 3)
        {
            int j;
            Threeofakind = 3;
            for (j = 0; j < numoffaces; j++) //Even if there are 3 same faces, with this for-loop checking whether the rest 2 dices are same faces or not to determine Full House
            {
                if (resultbasis[j] == 2)
                {
                    FullHouse = 5;
                    Threeofakind = 0;
                }
            }
        }


        //Checking to see if the random numbers form Four of a kind
        if (resultbasis[i] == 4)
        {
            Fourofakind = 4;
        }

        //Checking to see if the random numbers form CSlam
        if (resultbasis[i] == 5)
        {
            CSlam = 5;
        }
    }

    //Printing the desired results to the player
    if (Threeofakind == 3)
        printf("\nYou have 3-of-a-kind.");
    else if (Fourofakind == 4)
        printf("\nYou have 4-of-a-kind.");
    else if (SmallStraight == 4)
        printf("\nYou have Small Straight.");
    else if (LargeStraight == 5)
        printf("\nYou have Large Straight.");
    else if (CSlam == 5)
        printf("\nYou have CSlam. Congrats!");
    else if (TwoPair == 4)
        printf("\nYou have 2 pairs.");
    else if (FullHouse == 5)
        printf("\nYou have Full House.");
    else
        printf("\nYou have nothing.");
}

int main()
{
	printf("Sujan Dumaru \n");
	printf("UTA ID: 1001539502 \n");

	int dices[numofdices]; //Creating array to store the random numbers generated for the game
    int numberofReRolls = 4; //Maximum Number of Re-Rolls allowed in the game
    char exit[20];
    int loopbreaker = 1;


        do
        {
            RollDice(dices); //Calling function RollDice to determine the random numbers
            printf("\nYou rolled: \n");

            //Printing the obtained random numbers to the player
            int i;
            for (i = 0; i < numofdices; i++)
            {
                printf(" %d ", dices[i]);
            }

            int HowMany[numoffaces];
            int b;
            //Determining the number of same face player got in each game by calling function FindNumofFaces
            for(b = 0; b < numoffaces; b++)
            {
                HowMany[b] = FindNumofFaces(dices, b + 1);
            }

            printResult(HowMany); //Calling function printResult to print the outcome of the game as per obtained dices

            //Asking the player whether to re-roll or not
            printf("\n \nDo you want to re-roll? ");
            scanf("%s", exit);

            loopbreaker = loopbreaker + 1; //Count the number of times the game is played
			
            //Letting the player know that they reached the maximum re-roll times even if the player enter "yes" after re-rolling 2 times
            if (loopbreaker == numberofReRolls && (strcmp(exit,"y") == 0 || strcmp(exit,"yes") == 0 || strcmp(exit,"Y") == 0 || strcmp(exit,"Yes") == 0))
            {
                    printf("\nYou have reached maximum limit to re-roll. \n");
                    break;
            }
        }while (strcmp(exit,"y") == 0 || strcmp(exit,"yes") == 0 || strcmp(exit,"Y") == 0 || strcmp(exit,"Yes") == 0); //Ending the game as per the player's desired input

	return 0;

}
