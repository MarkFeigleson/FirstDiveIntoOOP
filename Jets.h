#ifndef _JETS_H_
#define _JETS_H_
#include <string>
#include <iostream>
#include <vector>

class playerJet {
friend class EnemyJet;
private:
	std::string callsign{"Null"}; // just a name for the player
	std::string jetName{"Null"}; // tells the player the type of jet they get
	float pBaseAccuracy{0}; //used in attack check die rolls
	float pBaseAgility{0}; // used to reduce enemy attack die rolls against all weapons
	float pECMRating{0}; // used to reduce enemy attack die rolls against non-heat seaking missiles
	int pBonusorPenaltyAIM120{0}, pBonusorPenaltySidewinder{0}, pBonusorPenaltyCannon{0}; // used to make some weapons better or worse at certain range bands
	bool isLongRange{true}; // used for modifiers on attack range
	bool canUseAIM120 = true; //access to AIM-120 missile for AMRAAM combat. Might expand to C and D later
	bool canUseCannon = true; //access to cannon for dogfighting
	bool canUseSiderwinder = true; // access to sidewinder for short range missile fighting. Might expand for aim-9X later
	bool canUseSparrow = true; //access to sparrow for 90's AMRAAM combat, might add agility reduction due to the non-pitbull capability.
	
public:
		// allows player to enter a name
	void setCallsign();
	// displays values for debugging. will be presented different to player later
	void displayValues();
	
	//firing logic for the weapons
	
	void pHitChance();
	
	void aim120Fire();
	
	void cannonFire();
	
	void sidewinderFire();
	
	//attack choice
	void chooseAttack();
	
	//short or long ranged check
	void rangeBand();
	
	//enemy attack logic
	void enemyAtack();
	
	//constructor of of president choice
	playerJet(char prez);
	//destructor
	~playerJet(){

		};
	
};

class EnemyJet {
public:

std::string eJetName {"Mig-21"};
static constexpr  float eBaseAccuracy {70};
static constexpr  float eBaseAgility {.80};
static constexpr  float eECMRating {.90};



void displayEnemyValues();
};

#endif // _JETS_H_
