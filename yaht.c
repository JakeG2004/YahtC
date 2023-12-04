//  yaht-C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//define functions
int rollDice();
void play(int plays);
void score(int rolls[5]);
int swap(int rolls[5]);
void scoreUpper(int rolls [5]);

//define globals
int points = 0;
int usedones = 0;
int usedtwos = 0;
int usedthrees = 0;
int usedfours = 0;
int usedfives = 0;
int usedsixes = 0;
int usedtoak = 0;
int usedfoak = 0;
int usedsstr = 0;
int usedlstr = 0;
int usedfh = 0;
int usedyz = 0;
int usedchance = 0;
int bonus = 0;
bool scoredones = false;
bool scoredtwos = false;
bool scoredthrees = false;
bool scoredfours = false;
bool scoredfives = false;
bool scoredsixes = false;
bool scoredtoak = false;
bool scoredfoak = false;
bool scoredsstr = false;
bool scoredlstr = false;
bool scoredfh = false;
bool scoredyz = false;
bool scoredchance = false;

int main(void)
{
  //init
  srand(time(0));
  play(0);    

  if((usedones + usedtwos + usedthrees + usedfours + usedfives + usedsixes) >= 63)
			bonus = 35;
  
		printf("\n");		
		printf("Total points: %i\n", points);
		printf("Ones: %i\n", usedones);
		printf("Twos: %i\n", usedtwos);
		printf("Threes: %i\n", usedthrees);
		printf("Fours: %i\n", usedfours);
		printf("Fives: %i\n", usedfives);
		printf("Sixes: %i\n", usedsixes);
		printf("63 point bonus: %i\n", bonus);
		printf("Three of a Kind: %i\n", usedtoak);
		printf("Four of a kind: %i\n", usedfoak);
		printf("Small Straight: %i\n", usedsstr);
		printf("Large Straight: %i\n", usedlstr);
		printf("Full House: %i\n", usedfh);
		printf("Yahtzee: %i\n", usedyz);
		printf("Chance: %i\n", usedchance); 

        int tmp;
		printf("Press any key to Continue\n");  
		scanf("%d", &tmp);
		return 1;
}

void play(int plays)
{
	//make initial roll
	int rolls[5];
	  for(int i=0; i<5; i++)
	  {
	    rolls[i] = rollDice();
	    printf("%i", rolls[i]);
	  }
	  printf("\n");
	
	  for(int i = 0;i<2;i++)
	  {
		  //get nums to reroll as 5 digit string
		  char reroll [5];
		  printf("Input dice to reroll or 'p' to play\n");
		  scanf("%5s", &reroll);
		  //play
		  if(reroll[0] == 'p')
		  	break;
		
		//reroll selected dice
		  for(int j=0; j<5; j++)
		    {
		    	if(reroll[j] == 0)
		    		reroll[j] = 0;
		       	
		       	{
		       		int dig = (int)reroll[j] - 49;
		       		rolls[dig] = rollDice();
		       		printf("%i", rolls[j]);
		       	}
		    }
		    printf("\n");
		    printf("rerolls left: %i\n", 2 - i);
		}
		score(rolls);
	    plays++;
	    if(plays < 13)
	    {
	    	play(plays);
	    }
}

void score(int rolls[5])
{
	*rolls = swap(rolls);
	scoreUpper(rolls);
}

void scoreUpper(int rolls[5])
{
	//init
	int ones, twos, threes, fours, fives, sixes, toak, value, foak, lstr, sstr, strtmp, fh, yz;
	ones = twos = threes = fours = fives = sixes = toak = value = foak = sstr = lstr = strtmp = yz = fh = 0;

	//iterate through string
	for(int i=0; i<5; i++)
	{
		//collect upper values
		if(rolls[i] == 1)
			ones += 1;
		if(rolls[i] == 2)
			twos += 1;
		if(rolls[i] == 3)
			threes += 1;
		if(rolls[i] == 4)
			fours += 1;
		if(rolls[i] == 5)
			fives += 1;
		if(rolls[i] == 6)
			sixes += 1;
		
		//combined total of dice
		value += rolls[i];

		//straight counter
		if((i > 0) && (rolls[i] == (rolls[i-1] + 1)))
		{
			strtmp += 1;
		}
	}

	//3 and 4 of a kind
	if(ones == 3 || twos == 3 || threes == 3 || fours == 3 || fives == 3 || sixes == 3)
	{
		toak = value;
	}

	if(ones == 4 || twos == 4 || threes == 4 || fours == 4 || fives == 4 || sixes == 4)
	{
		foak = value;
	}

	if(ones == 5 || twos == 5 || threes == 5 || fours == 5 || fives == 5 || sixes == 5)
	{
		yz = 50;
	}

	//straights
	if(strtmp >= 3)
		sstr = 30;
	if(strtmp == 4)
		lstr = 40;

	//full house (this one sucks)
	if((ones == 2 || twos == 2 || threes == 2 || fours == 2 || fives == 2 || sixes == 2) && toak != 0)
	{
		fh = 25;
	}
	//print totals for user if they havent been used
	if(scoredones == false)
		printf("1. Ones: %i\n", ones);
	if(scoredtwos == false)
		printf("2. Twos: %i\n", (twos * 2));
	if(scoredthrees == false)
		printf("3. Threes: %i\n", threes * 3);
	if(scoredfours == false)
		printf("4. Fours: %i\n", fours * 4);
	if(scoredfives == false)
		printf("5. Fives: %i\n", fives * 5);
	if(scoredsixes == false)
		printf("6. Sixes: %i\n", sixes * 6);
	if(scoredtoak == false)
		printf("7. Three of a kind: %i\n", toak);
	if(scoredfoak == false)
		printf("8. Four of a kind: %i\n", foak);
	if(scoredsstr == false)
		printf("9. Small Straight: %i\n", sstr);
	if(scoredlstr == false)
		printf("10. Large Straight: %i\n", lstr);
	if(scoredfh == false)
		printf("11. Full House: %i\n", fh);
	if(scoredyz == false)
		printf("12. Yahtzee: %i\n", yz);
	if(scoredchance == false)
		printf("13. Chance %i\n", value);
	
	//select points destination
	printf("Select desired destination for points: ");
	int choice;
	scanf("%d", &choice);

	//set used choices
	//Todo rework so that zeros dont show
	if(choice == 1 && scoredones == false)
	{
		points += ones;
		usedones = ones;
		scoredones  = true;
	}
	if(choice == 2 && scoredtwos == false)
	{
		points += (twos * 2);
		usedtwos = (twos * 2);
		scoredtwos = true;
	}
	if(choice == 3 && scoredthrees == false)
	{
		points += (threes * 3);
		usedthrees = (threes * 3);
		scoredthrees = true;
	}
	if(choice == 4 && scoredfours == false)
	{
		points += (fours * 4);
		usedfours = (fours * 4);
		scoredfours = true;
	}
	if(choice == 5 && scoredfives == false)
	{
		points += (fives * 5);
		usedfives = (fives * 5);
		scoredfives = true;
	}
	if(choice == 6 && scoredsixes == false)
	{
		points += (sixes * 6);
		usedsixes = (sixes * 6);
		scoredsixes = true;
	}
	if(choice == 7 && scoredtoak == false)
	{
		points += toak;
		usedtoak = toak;
		scoredtoak = true;
	}
	if(choice == 8 && scoredfoak == false)
	{
		points += foak;
		usedfoak = foak;
		scoredfoak = true;
	}
	if(choice == 9 && scoredsstr == false)
	{
		points += sstr;
		usedsstr = sstr;
		scoredsstr = true;
	}
	if(choice == 10 && scoredlstr == false)
	{
		points += lstr;
		usedlstr = lstr;
		scoredlstr = true;
	}
	if(choice == 11 && scoredfh == false)
	{
		points += fh;
		usedfh = fh;
		scoredfh = true;
	}
	if(choice == 12 && scoredyz == false)
	{
		points += yz;
		usedyz = yz;
		scoredyz = true;
	}
	if(choice == 13 && scoredchance == false)
	{
		points += value;
		usedchance = value;
		scoredchance = true;
	}

}

int swap(int rolls[5])
{
	//bubble sort rolls
	int tmp;
	int swaps;
	for(int i=0;i<4;i++)
	{
		if(rolls[i]>rolls[i+1])
		{
			tmp = rolls[i];
			rolls[i] = rolls[i+1];
			rolls[i+1] = tmp;
			swaps++;
		}
	}
	if(swaps != 0)
		swap(rolls);
	return *rolls;
}

int rollDice()
{
  return ((rand() % 6) + 1);
}
