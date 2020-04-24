#include "Jets.h"

//global for game state
bool playerDead {false};
bool enemyDead {false};

//restarts or ends the final loop
extern bool PlayAgainChoice;

//global used for president picker switch statement
char PresChoice{'z'};

//rolls d5 for threater text
int diceRollD5()
	{
	int roll;
	int min = 1;
	int max = 5;
	roll = rand() % (max - min +1) +min;
	return roll;
	}

	//represents a 2 range bands situation
	void playerJet::rangeBand(){
	char spacing{'z'};
		
	std::cout << "Do you (P)ush to closer range or (D)rag and continue to fight at longer range?" << std::endl;
	std::cin >> spacing;
	switch (spacing)
	{
	case 'p':
	case 'P':
	std::cout << "You kick on the after burners and head in for the merge" << std::endl;
	isLongRange = false;
	break;
	
	case 'd':
	case 'D':
	
	std::cout << "You keep the bandit on your 9 O'clock and reposition for another long ranged shot." << std::endl;
	isLongRange = true;
	break;
	
	default:
	std::cout << "Pick a valid option you palooka." << std::endl;
	std::cin >> spacing;
	}
	if (isLongRange == true){
	pBonusorPenaltyAIM120 = 10;
	pBonusorPenaltyCannon = -59;
	pBonusorPenaltySidewinder = -50;
	}
	else
	{
	pBonusorPenaltyAIM120 = -30;
	pBonusorPenaltyCannon = -10;
	pBonusorPenaltySidewinder = 10;
	}
	}
//my dice rollers for RNG
int diceRollD100()
	{
	int roll;
	int min = 1;
	int max = 100;
	roll = rand() % (max - min +1) +min;
	return roll;
	}
//Intro situation - theater randomizer setup
std::vector <std::string> theater {"Null", "Iraq", "Iran", "North Korea", "Syria", "Afghanistan"};

//intro text
void mainIntro(){
	int theaterRoll {0};
	theaterRoll = diceRollD5();
	std::cout << "It is your duty to defend the free world. After some diplomatic difficulties, you have been deployed to a nearby airbase in " <<  theater.at(theaterRoll) << "." <<
	std::endl << " you are briefed on an established no fly zone and it is your job to perform barrier combat air patrol to protect the free world." << std::endl <<
	"A few minutes later you find yourself in your jet, engines spooled up then feel the rush as you take off from the runway." << std::endl <<
	"Patrol seems to go on without event for a few hours, but as you finish an air to air refueling with a nearby tanker, you recieve a radio message from an AWACS" << std::endl <<
	"Outlaw bulleye 270 40,000 HOT you hear and can't help but smile as you see your first bandit on radar." << std::endl;
}

// displays values for debugging. will be presented different to player later
void playerJet::displayValues(){
	std::cout << "Your callsign is " << callsign << ", Flying in a " << jetName << " with a base accuracy of " << pBaseAccuracy << " with a base agility of " << pBaseAgility << 
	" and an ECM rating of " << pECMRating << std::endl;
	}
// allows player to enter a name
void playerJet::setCallsign(){
	std::string callsign_val;
	std::cout << "enter a callsign ";
	std::cin >> callsign_val;
	callsign = callsign_val;
		}
		
void EnemyJet::displayEnemyValues(){
	std::cout << "The enemy is a " << eJetName << " with a base accuracy of " <<  eBaseAccuracy << " and a base agility of " << eBaseAgility << " with an ECM rating of " 
	<< eECMRating;
}
	
//Probability of Kill lister for the player
	void playerJet::pHitChance(){
	float aim120Accuracy{.80};
	float aim120ChanceToHit{0};
	aim120ChanceToHit = ((pBaseAccuracy * aim120Accuracy * EnemyJet::eBaseAgility * EnemyJet::eECMRating) + pBonusorPenaltyAIM120);
	std::cout << "Your chance to hit with the AIM-120 is " << aim120ChanceToHit << " Percent." << std::endl;
	float cannonAccuracy{.75};
	float cannonChanceToHit{0};
	cannonChanceToHit = ((pBaseAccuracy * cannonAccuracy * EnemyJet::eBaseAgility) + pBonusorPenaltyCannon);
	std::cout << "Your chance to hit with the cannon is " << cannonChanceToHit << " Percent." << std::endl;
	float sidewinderAccuracy{.90};
	float sidewinderChanceToHit{0};
	sidewinderChanceToHit = ((pBaseAccuracy * sidewinderAccuracy * EnemyJet::eBaseAgility) + pBonusorPenaltySidewinder);
	std::cout << "Your chance to hit with the sidewinder is " << sidewinderChanceToHit << " Percent." << std::endl;
	}
	
//enemy attack logic
void playerJet::enemyAtack(){
	float enemyHitChance{0};
	float enemyAttackRoll{0};
	enemyHitChance = (EnemyJet::eBaseAccuracy * pBaseAgility * pECMRating);
	std::cout << "Enemy has a " << enemyHitChance << " probability of kill" << std::endl;
	enemyAttackRoll = diceRollD100();
	std::cout << "The enemy rolled a " << enemyAttackRoll << std::endl;
	if (enemyAttackRoll <= enemyHitChance){
	std::cout << "You went down like a little bitch to an obsolete plane with a crap missile." << std::endl << "Way to go costing the US tax payers millions of buckazoids!" << std::endl;
	playerDead = true;
	}
	else{
	std::cout << "The enemy misses their attack" << std::endl;
	}
	}
	
//checks for who died and gives messages accordingly
void deathCheck()
{
	if (enemyDead == true)
	{
    std::cout << "The Winrar is you" << std::endl;
    }
	if (playerDead == true)
	{ 
	std::cout << "Kenshiro and Tronne Bonne says Thanks for Playing" << std::endl;
	}
}
// attack menu
void playerJet::chooseAttack()
	{
	rangeBand();
	pHitChance();
	char weaponChoice {'z'};
	std::cout << "Do you attack with the (C)annon, (A)im-120, (S)idewinder ?" << std::endl;
	std::cin >> weaponChoice;
	switch (weaponChoice)
		{
	case 'C':
    case 'c':
    playerJet::cannonFire();
	if(!enemyDead){
		enemyAtack();
	}
	deathCheck();
	break;
	
	case 'A':
    case 'a':
    playerJet::aim120Fire();
	if(!enemyDead){
		enemyAtack();
	}
	deathCheck();
	break;
	
	case 'S':
    case 's':
    playerJet::sidewinderFire();
	if(!enemyDead){
		enemyAtack();
	}
	deathCheck();
	break;
	
	default:
	std::cout << "Please pick a valid option" << std::endl;
	}
}

	//attack logic
	void playerJet::aim120Fire(){
	float aim120Accuracy{.80};
	float aim120ChanceToHit{0};
	float hitResultAIM120{0};
	aim120ChanceToHit = ((pBaseAccuracy * aim120Accuracy * EnemyJet::eBaseAgility) + pBonusorPenaltyAIM120);
	hitResultAIM120 = diceRollD100();
	std::cout << "You rolled " << hitResultAIM120 << std::endl;
	if (hitResultAIM120 <= aim120ChanceToHit){
		std::cout << "Your AIM-120 hits and destroys the enemy plane." << std::endl;
		enemyDead = true;
	}
	else{
		std::cout << "You missed like a chump! (Hey!) like a chump! (Hey!) like a chump!"<< std::endl;
	}
	}
	
	void playerJet::cannonFire(){
	float cannonAccuracy{.75};
	float cannonChanceToHit{0};
	float hitResultCannon{0};
	cannonChanceToHit = ((pBaseAccuracy * cannonAccuracy * EnemyJet::eBaseAgility) + pBonusorPenaltyCannon);
	hitResultCannon = diceRollD100();
	std::cout << "You rolled " << hitResultCannon << std::endl;
	if (hitResultCannon <= cannonChanceToHit){
		std::cout << "Your cannon fire rakes and destroys the enemy jet."<< std::endl;
		enemyDead = true;
	}
	else{
		std::cout << "You missed like a chump! (Hey!) like a chump! (Hey!) like a chump!"<< std::endl;
	}
	}
	
	void playerJet::sidewinderFire(){
	float sidewinderAccuracy{.90};
	float sidewinderChanceToHit{0};
	float hitResultSidewinder{0};
	sidewinderChanceToHit = ((pBaseAccuracy * sidewinderAccuracy * EnemyJet::eBaseAgility) + pBonusorPenaltySidewinder);
	hitResultSidewinder = diceRollD100();
	std::cout << "You rolled " << hitResultSidewinder << std::endl;
	if (hitResultSidewinder <= sidewinderChanceToHit){
		std::cout << "Your sidewinder hits and destroys the enemy plane."<< std::endl;
		enemyDead = true;
	}
	else{
		std::cout << "You missed like a chump! (Hey!) like a chump! (Hey!) like a chump!"<< std::endl;
	}
	}
	
//switch statement off of President choice to determine jet capabilities
playerJet::playerJet(char prez){
	switch(prez){
			case 'T':
			case 't':
			{
			std::string pJetName_val{"F-35 Lightning"};
			float pBaseAccuracy_val{100};
			float pBaseAgility_val{.75};
			float pECMrating_val{.50};
			jetName = pJetName_val;
			pBaseAccuracy = pBaseAccuracy_val;
			pBaseAgility = pBaseAgility_val;
			pECMRating = pECMrating_val;
			break;
			}
			
			case 'O': 
			case 'o':
			
			{
			std::string pJetName_val{"F-22 Raptor"};
			float pBaseAccuracy_val{100};
			float pBaseAgility_val{.65};
			float pECMrating_val{.70};
			jetName = pJetName_val;
			pBaseAccuracy = pBaseAccuracy_val;
			pBaseAgility = pBaseAgility_val;
			pECMRating = pECMrating_val;
			break;
			}
			case 'B':
			case 'b':
			{
			std::string pJetName_val{"F-15C Eagle"};
			float pBaseAccuracy_val{100};
			float pBaseAgility_val{.75};
			float pECMrating_val{.85};
			jetName = pJetName_val;
			pBaseAccuracy = pBaseAccuracy_val;
			pBaseAgility = pBaseAgility_val;
			pECMRating = pECMrating_val;
			break;
			}
			case 'C':
			case 'c':
			{
			std::string pJetName_val{"F-15C Eagle"};
			float pBaseAccuracy_val{100};
			float pBaseAgility_val{.75};
			float pECMrating_val{.85};
			jetName = pJetName_val;
			pBaseAccuracy = pBaseAccuracy_val;
			pBaseAgility = pBaseAgility_val;
			pECMRating = pECMrating_val;
			break;
			}
	}
	}
	
void presPicker()
	{
	std::cout << "Choose your commander-in-chief: " << std::endl << "(C)linton, (B)ush, (O)bama, or (T)rump: " << std::endl;
	std::string picker{"z"};
	std::cin >> PresChoice;
	switch(PresChoice)
	{
		case 'T':
		case 't':
			{
			std::cout << "You serve under Donald Trump, 45th President of the United States, 2016 - 2024 "<< std::endl;
			std::string pJetName_val{"F-35 Lightning"};
			break;
			}
		case 'O': 
		case 'o':
		{
			std::cout << "You serve under Barack Obama, 44th President of the United States, 2008 - 2016 "<< std::endl;
			break;
			}
		
		case 'B':
		case 'b':
		{
			std::cout << "You serve under George W. Bush, 43th President of the United States, 2000  2008 "<< std::endl;
			break;
			}
		
		case 'C':
		case 'c':
		{
			std::cout << "You serve under Bill Clinton, 42th President of the United States, 1992 - 2000 "<< std::endl;
			break;
			}
		
		default :
			{
			std::cout << "Please re-enter the first letter of the commander-in-cheif's name. " << std::endl;
			std::cin >> PresChoice;
			}
		}
	}
	
	
void playAgainDecision(){
	std::cout << "Play again? Y/N?" << std::endl;
	char finalchoice {'z'};
    std::cin >> finalchoice;
   if (finalchoice == 'y' || finalchoice == 'Y') 
	{
	   PlayAgainChoice = false;
	   playerDead = false;
	   enemyDead = false;
	   presPicker();
	   mainIntro();
   }
   else if (finalchoice == 'n' || finalchoice == 'N')
	{
	   PlayAgainChoice = true;
	   std::cout << "Kenshiro and Tronne Bonne says Thanks Again for Playing" << std::endl;
   }
   else
   {
	std::cout << "PICK Y or N FGT!" << std::endl;
	playerDead = true;
	enemyDead = true;
	}
	}