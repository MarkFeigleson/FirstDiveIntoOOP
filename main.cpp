#include <iostream>
#include <string>
#include <vector>
#include <chrono> //required for time
#include <cstdlib> //required for random
#include "jets.h"

//global variable for win or lose states. used extern so they can be accessed in jets.cpp
extern bool playerDead;
extern bool enemyDead;

//global variable to assist in construction
extern char PresChoice;

//global variable for gameplay loop
bool PlayAgainChoice{false};

//scipt to get jet capabilities off of president picked
void presPicker();


//checks if someone is dead
void deathcheck();
//dice roller
int diceRollD5();
//intro
void mainIntro();
// gameplay loop restarter
void playAgainDecision();

int main()
{
srand(time(0));
presPicker();
mainIntro();
//main play loop
while (!PlayAgainChoice)
{
	playerJet Jobber(PresChoice);
	Jobber.setCallsign();
	Jobber.displayValues();
	EnemyJet Mig;
	while (!enemyDead && !playerDead)
	{
	Jobber.chooseAttack();
	}
playAgainDecision();
}
return 0;
}