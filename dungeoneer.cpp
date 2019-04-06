// This code is protected by the MIT License.  See README.txt for more information.  If README.txt is not present, simply Google "MIT License".  Copyright 2018 John Nguyen.
/* 
 ___               __   ___  __          ___  ___ ___
|   \ |  | |\   | /  \ |    /  \ |\   | |    |    |  \
|   | |  | | \  | | _  |--- |  | | \  | |--- |--- |--/
|   | |  | |  \ | |  \ |    |  | |  \ | |    |    | \
|___/ \__/ |   \| \__/ |___ \__/ |   \| |___ |___ |  \

*/
// These are preprocessor directives -- they tell the compiler to "include" these specified libraries of pre-written functions into your code
#include <iostream> // Standard input and output
#include <string> // Class for dealing with groups of characters such as words or sentences
#include <stdlib.h> // This is the entire C++ standard library
#include "utils.h" // This is a local file that I wrote to reduce the amount of non-Dungeoneer-specific functions in this file

// Namespaces are prefixes for library functions that allow other functions outside of that namespace to have the same identifier
// For example, std::cout() will NOT call the same function as cout() unless a `using namespace std;` line is in the code.  `using namespace` calls are used so you don't have to type the namespace before every call of a library function
using namespace std;
using namespace utils;

class NPC { // The non-player character class.  Includes all the variables and member functions required for a good D&D character.
	protected: // These members can only be accessed from members of this class
		unsigned short int strg, cons, dext, intl, chas, wisd; // Ability scores
		bool isIncap; // Is the NPC incapacitated?
		bool isUndead; // Is it an undead(aka a zombie)?  (this determines whether it can be damaged by a cleric presenting their holy symbol, for example)
		string wepstr1, wepstr2, wepstr3;
	public: // These members can be accessed from anywhere
		unsigned short int damDie[3]; // Damage dies for the three attack slots
		string Name; // an identifying variable used to determine loot when an NPC is killed
		short int npcHP; // HP for the NPC
		short int maxHP; // Maximum HP
		unsigned short int ac; // This number is subtracted from damage dealt to the NPC, it represents the armor class
		bool isEnemy; // Whether to damage the enemy or the player
		bool isDead; // Used to validate kill messages so the attack function doesn't have to
		unsigned int ID; // A number that could in later versions be used to identify NPCs
		unsigned short int lvl; // Level
	// Member functions
		void dealDamage (int, bool, bool); // Attack
		void takeDamage (int); // Modify own HP
		void set (string, int, int, int, int, int, int, int, int, int, int, bool, int, int, string, string, string, int); // Same as the constructor but can be called at any time
		NPC (string, int, int, int, int, int, int, int, int, int, int, bool, int, int, string, string, string, int); // Set initial values, this is called a constructor and it has no type
};
// Predefining functions to prevent compilation errors
void act ();
void move ();
void attack (int, bool, bool);
void setClass ();
void updtLvl();

// Predefining variables to prevent compilation errors
unsigned short int init; // Unsigned short means from 0 to 255
unsigned short int cla;
int clas;
int atkRoll;
int lvl;
bool inCombat = false;

unsigned short int Str, Dex, Con, Intl, Wis, Cha, AC, XP;
unsigned short int DamDie [3] = { 8, 4, 8 };
unsigned short int inv [45];
unsigned short int splDie [20];
string splNames[20];
int spellID[3];
int wepID[3];
int wepDie[9];
int armorType;
string invNames [45];
unsigned short int lvlXP [50];
unsigned short int ScoreAssoc [3];
signed short int HP; // Signed short means from -127 to 127
unsigned short int maxHP;
int tempint;
string tempstrg;
// Predefining NPC "Enemy" (which is redefined and reused throughout Dungeoneer) to prevent compile errors
// Notice that this generic NPC is a flat character--its ability scores are all the same!
// An actual player would never create a character like this.(but its a good representation of a generic 1st level unclassed enemy)(and might be hilarious for a 1st-level wizard...)
NPC Enemy ("goblin", 13, 13, 13, 13, 13, 13, 6, 8, 4, 12, true, -1, 1, "scimitar", "light crossbow", "dagger", 2);
void setInvNames () { // Setting the array of names for the items in Dungeoneer.
invNames[1] = "longsword";
invNames[2] = "shortsword";
invNames[3] = "crossbow";
invNames[4] = "light crossbow";
invNames[5] = "dagger";
invNames[6] = "handaxe";
invNames[7] = "warhammer";
invNames[8] = "mace";
invNames[9] = "scimitar";
invNames[10] = "bolt";
invNames[11] = "arrows";
invNames[12] = "rope";
invNames[13] = "tinderbox";
invNames[14] = "mess kit";
invNames[15] = "canteen";
invNames[16] = "firewood";
invNames[17] = "crowbar";
invNames[18] = "holy symbol";
invNames[19] = "spellbook";
invNames[20] = "food";
invNames[21] = "bone";
invNames[22] = "metal";
invNames[23] = "light armor";
invNames[24] = "medium armor";
invNames[25] = "heavy armor";
invNames[26] = "clothes";
invNames[27] = "gold piece";
invNames[28] = "backpack";
invNames[29] = "FlexTape";
invNames[30] = "filled canteen";
}
void setSpellDies () {
	splDie[1] = 15;
	splDie[2] = 10;
	splDie[3] = 18;
	splDie[4] = 20;
	splDie[5] = 4;
	splDie[6] = 10;
	splDie[7] = 4;
	splDie[8] = 30;
	splDie[9] = 10;
	splDie[10] = 16;
	splNames[1] = "Magic Missile";
	splNames[2] = "Fireball";
	splNames[3] = "Burning Hands";
	splNames[4] = "Decapitation";
	splNames[5] = "Holy Symbol";
	splNames[6] = "Hyperdab";
	splNames[7] = "Nauseator";
	splNames[8] = "Inside-Out";
	splNames[9] = "Inflict Wounds";
	splNames[10] = "Thunderwave";
}
void setLvlInfo () {
	lvlXP[1] = 100;
	lvlXP[2] = 200;
	lvlXP[3] = 400;
	lvlXP[4] = 600;
	lvlXP[5] = 800;
	lvlXP[6] = 1000;
	lvlXP[7] = 1300;
	lvlXP[8] = 1600;
	lvlXP[9] = 1900;
	lvlXP[10] = 2100;
}
void wepDies () {
	wepDie[1] = 8;
	wepDie[5] = 4;
	wepDie[4] = 8;
	wepDie[6] = 6;
	wepDie[2] = 6;
	wepDie[3] = 10;
	wepDie[7] = 8;
	wepDie[8] = 12;
	wepDie[9] = 6;
}
void setMap () {
	x = 20;
	y = 20;
	bool inTown = true;
}
void NPC::dealDamage (int atkType, bool hasAdv, bool hasDis) { // Implement method of detecting the "side" of an NPC and therefore which NPC(or player) to damage when it attacks
	int atkRoll = toprand(20);
	int damage;
	if (hasAdv) {
		int atkRoll2 = toprand(20);
		if (atkRoll > atkRoll2) {}
		else
			atkRoll = atkRoll2;
	}
	if (hasDis) {
		int atkRoll2 = toprand(20);
		if (atkRoll < atkRoll2) {}
		else
			atkRoll = atkRoll2;
	}
	if (atkRoll >= 10 && isEnemy && !isDead && !isIncap) {
		damage = toprand(damDie[atkType]);
		damage = damage - AC; // Taking account for armor class
		damage = damage + getModifier(strg); // Adding strength modifier
		switch (atkType) {
			case 1:
				tempstrg = wepstr1;
				break;
			case 2:
				tempstrg = wepstr2;
				break;
			case 3:
				tempstrg = wepstr3;
				break;
		}
		if (damage >= 1) {
		HP = HP - damage;
		cout << "The " << Name << " attacks with his " << tempstrg << ", dealing " << damage << " damage.  You are now at " << HP << " HP." << endl;
		} else {
			cout << "Your armor deflects the " << Name  << "'s " << tempstrg << ", and you are unharmed." << endl;
		}
	} else if (atkRoll >= 10 && !isEnemy && !isDead && !isIncap) {
		damage = toprand(damDie[atkType]);
		damage = damage - ac; // Accounting for the enemy's armor class
		damage = damage + getModifier(strg); // Adding strength modifier
		Enemy.takeDamage (damage);
	} else if (atkRoll <= 9) 
		cout << "The " << Name << " attacks with their " << tempstrg << ", but the blow does not connect." << endl;
}
// Subtracts a specified number of hitpoints from the host NPC and incapacitates it/kills it depending upon the amount of damage taken
void NPC::takeDamage (int damage) {
	damage = damage - ac; // Accounting for armor class
	npcHP = npcHP - damage; // Subtracting damage
	if (npcHP <= 0) { // Dealing with what the damage taken does to the NPC
		if (abs(npcHP) >= maxHP) {// If the opposite of the NPC's hitpoint maximum is greater than the current number of hitpoints, kill the NPC
			isDead = true;
			if (Name == "wild boar") {
				inv[20] = inv[20] + toprand(15) + 20;
				XP+=25;
			} else if (Name == "wild dog") {
				inv[20] = inv[20] + toprand(5) + 5;
				XP+=25;
			} else if (Name == "wild turkey") {
				inv[20] = inv[20] + toprand(20) + 10;
				XP+=25;
			} else if (Name == "wild bull") {
				inv[20] = inv[20] + toprand(20) + 40;
				XP+=50;
			} else if (Name == "wild badger") {
				inv[20] = inv[20] + toprand(15) + 5;
				XP+=25;
			} else if (Name == "Phil Swift") {
				inv[29] = inv[29] + 100;
				cout << "You pick up 100 FlexTape from Phil Swift's earthly body as his soul returns to heaven.  You hear his voice telling you that FlexTape can be used to treat wounds instantly.\n";
				XP+=200;
			} else if (Name == "goblin") {
				inv[9]+=1; // Also gives you equipment of killed creature
				inv[24]+=1;
				inv[27]+=25;
				inv[4]+=1;
				inv[5]+=1;
				inv[10]+=20;
				XP+=75;
			} else if (Name == "thief") {
				inv[5]+=3;
				inv[27]+=10;
				inv[26]+=1;
				inv[17]+=1;
				inv[4]+=1;
				XP+=50;
			}
			updtLvl(); // Checks for XP leveling AFTER incrementing XP values
		}
		else {
		isIncap = true; // If not, render it unconcious
		//cout << "Kim Jong-Un attacks, dealing 9001 Communist Damage!" << endl;
		cout << "The " << Name << " falls unconscious. ";
		}
	} // This system is not completely accurate to D&D, as in the game most DMs have enemies die when they drop to 0 HP.  Also, this stores HP as a negative value--something not done in D&D.
}
// This function is basically the script that handles the input you stick here: "NPC joe (here);" upon object creation
// Note (for beginners) that there is no type specification; this is required for constructors
NPC::NPC (string name, int str, int con, int dex, int inl, int cha, int wis, int dam1, int dam2, int dam3, int Hp, bool enemy, int id, int LVL, string wep1, string wep2, string wep3, int Ac) {
	// Handling input values
	Name = name;
	strg = str;
	cons = con;
	dext = dex;
	intl = inl;
	chas = cha;
	wisd = wis;
	damDie[1] = dam1;
	damDie[2] = dam2;
	damDie[3] = dam3;
	npcHP = Hp;
	isEnemy = enemy;
	ID = id;
	lvl = LVL;
	// Setting other data
	maxHP = npcHP;
	isDead = false;
	isIncap = false;
	wepstr1 = wep1;
	wepstr2 = wep2;
	wepstr3 = wep3;
	ac = Ac;
}
void NPC::set (string name, int str, int con, int dex, int inl, int cha, int wis, int dam1, int dam2, int dam3, int Hp, bool enemy, int id, int LVL, string wep1, string wep2, string wep3, int Ac) {
	// Handling input values
	Name = name;
	strg = str;
	cons = con;
	dext = dex;
	intl = inl;
	chas = cha;
	wisd = wis;
	damDie[1] = dam1;
	damDie[2] = dam2;
	damDie[3] = dam3;
	npcHP = Hp;
	isEnemy = enemy;
	ID = id;
	lvl = LVL;
	// Setting other data
	maxHP = npcHP;
	isDead = false;
	isIncap = false;
	wepstr1 = wep1;
	wepstr2 = wep2;
	wepstr3 = wep3;
	ac = Ac;
}
void spell (int spellType) {
	inCombat = true;
	int atkRoll = toprand(20);
	if (atkRoll >= 10) {
		int damage = toprand(splDie[spellType]);
		damage = damage + getModifier(Intl);
		Enemy.takeDamage (damage);
		cout << "Your " << splNames[spellType] << " was a success!  Your enemy took " << damage << " damage.  They are now at " << Enemy.npcHP << " HP.\n";
		if (Enemy.isDead == true) {
			cout << "You killed your enemy.\n";
			Enemy.set ("goblin", 13, 13, 13, 13, 13, 13, 6, 8, 4, 12, true, -1, 1, "scimitar", "light crossbow", "dagger", 2);
			inCombat = false;
			act ();
		} else {
			Enemy.dealDamage (toprand(3), false, false);
		}
	} else if (atkRoll == 1) {
		HP -= 1;
		cout << "Your concentration was broken, rendering your spellcast ineffective.  The loss of concentration physically injured you, causing you to take 1 damage.\n";
		Enemy.dealDamage (toprand(3), true, false);
		act ();
	} else {
		cout << "You forgot some essential part of your spell's casting process, so the cast was ineffective.\n";
		Enemy.dealDamage (toprand(3), false, false);
		act ();
	}
}
void attack (int atkType, bool hasAdv, bool hasDis) {
	inCombat = true;
	int atkRoll = toprand(20);
	if (hasAdv) {
		int atkRoll2 = toprand(20);
		if (atkRoll > atkRoll2) {}
		else
			atkRoll = atkRoll2;
	}
	if (hasDis) {
		int atkRoll2 = toprand(20);
		if (atkRoll < atkRoll2) {}
		else
			atkRoll = atkRoll2;
	}
	if (atkRoll >= 10) {
		int damage = toprand(DamDie[atkType]);
		damage = damage + getModifier(ScoreAssoc[atkType]);
		Enemy.takeDamage (damage);
		cout << "You successfully damaged your target, dealing " << damage << " damage.  Your target is now at " << Enemy.npcHP << " HP. " << endl;
		if (Enemy.isDead == true) {
			cout << "You killed your enemy." << endl;
			Enemy.set ("goblin", 13, 13, 13, 13, 13, 13, 6, 8, 4, 12, true, -1, 1, "scimitar", "light crossbow", "dagger", 2);
			inCombat = false;
			act ();
		} else {
			Enemy.dealDamage (toprand(3), false, false);
			act();
		}
	} else if (atkRoll == 1) {
		HP = HP - 1;
		cout << "You failed so horribly to damage your target that you pulled a muscle.  -1 HP. You are now at " << HP << " HP." << endl;
		Enemy.dealDamage (toprand(3), true, false);
		act();
	} else {
		cout << "You failed to damage your target. " << endl;
		Enemy.dealDamage (toprand(3), false, false);
		act();
	}
}
void randomEvent () {
	int tempint = toprand(3);
	if (tempint == 1) {
		tempint = toprand(4);
		switch (tempint) {
			case 1:
				Enemy.set ("goblin", 13, 13, 13, 13, 13, 13, 6, 8, 4, 12, true, -1, 1, "scimitar", "light crossbow", "dagger", 2);
				cout << "You encounter a lone goblin on patrol.  You have the first move.\n";
				inCombat = true;
				act ();
				break;
			case 2:
				Enemy.set ("dire wolf", 16, 13, 18, 13, 18, 16, 8, 6, 4, 10, true, 2, 1, "teeth", "claws", "paws", 1);
				cout << "A dire wolf sneaks up on you from behind and pounces on your back.\n";
				Enemy.dealDamage (1, true, false);
				inCombat = true;
				act ();
				break;
			case 3:
				Enemy.set ("thief", 11, 11, 15, 15, 8, 8, 4, 8, 4, 12, true, -1, 1, "fists", "crowbar", "dagger", 1);
				cout << "A thief punches you in the guts as he pulls out a dagger, demanding you hand over your money.\n";
				Enemy.dealDamage (1, true, false);
				inCombat = true;
				act ();
				break;
			case 4:
				Enemy.set ("rat", 8, 11, 16, 1, 8, 1, 4, 6, 4, 6, true, -1, 1, "claws", "teeth", "claws", 0);
				cout << "A mangy rat leaps up and bites your leg.\n";
				Enemy.dealDamage(2, false, false);
				inCombat = true;
				act ();
				break;
		}
	} else if (tempint == 2) {
		tempint = toprand(6);
		switch (tempint) {
			case 1:
				cout << "You found an empty canteen with a hole in it.  +1 Metal\n";
				inv[22] = inv[22] + 1;
				break;
			case 2:
				cout << "You found a rusted longsword lying beside a suit of armor.  +3 Metal +1 Light Armor\n";
				inv[22] = inv[22] + 3;
				inv[23] = inv[23] + 1;
				break;
			case 3:
				cout << "A bird dropped a pair of pants on your head.  +1 Clothes\n";
				inv[26] += 1;
				break;
			case 4:
				cout << "An old backpack was given to you by some random peasant who is probably insane.  +1 Backpack\n";
				inv[28] += 1;
				break;
			case 5:
				cout << "A stack of firewood catches your attention.  +5 Firewood\n";
				inv[16] += 5;
				break;
			case 6:
				cout << "An apple fell out of a tree nearby.  +1 Food\n";
				inv[20] += 1;
				break;
		}
	} else if (tempint == 3) {
		tempint = toprand(6);
		switch (tempint) {
			case 1:
				cout << "An old man comes up to you and starts babbling about his stupid grandson.\n"; break;
			case 2:
				cout << "A peasant boy throws a rock at the back of your head. -1 HP\n";
				HP -= 1; break;
			case 3:
				cout << "A benevolent spirit visits you and tells you you're a hero.\n";
				break;
			case 4:
				cout << "A fish says hi.\n";
				break;
			case 5:
				cout << "You see a tree that appears to be growing lanterns on its branches.\n";
				break;
			case 6:
				cout << "You spot a cloak on the side of the road, but you pass it by.\n";
				break;
		}
	}
}
void mover () {
	if (inCombat == false) {
		cout << "Where do you want to go?  Check map.txt for options." << endl;
		string place;
		cin >> place;
		if (place == "hamville" || place == "1" || place == "Hamville") { newx = 20; newy = 20; }
		else if (place == "candleburg" || place == "2" || place == "Candleburg") { newx = 10; newy = 18; }
		else if (place == "hamfast" || place == "3" || place == "Hamfast") { newx = 15; newy = 6; }
		else if (place == "haultown" || place == "4" || place == "Haultown") { newx = 9; newy = 14; }
		else if (place == "fenburg" || place == "5" || place == "Fenburg") { newx = 29; newy = 3; }
		else if (place == "ashton" || place == "6" || place == "Ashton") { newx = 33; newy = 6; }
		else if (place == "rular" || place == "7" || place == "Rular") { newx = 29; newy = 11; }
		else if (place == "spearthrust" || place == "8" || place == "Spearthrust") { newx = 18; newy = 12; }
		else if (place == "barnville" || place == "9" || place == "Barnville") { newx = 24; newy = 29; }
		else if (place == "tallowton" || place == "10" || place == "Tallowton") { newx = 8; newy = 33; }
		else if (place == "starville" || place == "11" || place == "Starville") { newx = 11; newy = 36; }
		else if (place == "evensburg" || place == "12" || place == "Evensburg") { newx = 10; newy = 39; }
		else if (place == "lambburg" || place == "13" || place == "Lambburg") { newx = 22; newy = 35; }
		else if (place == "elventrade" || place == "14" || place == "Elventrade") { newx = 21; newy = 40; }
		else if (place == "ironforge" || place == "15" || place == "Ironforge") { newx = 32; newy = 39; }
		else if (place == "wharfton" || place == "16" || place == "Wharfton") { newx = 40; newy = 39; }
		else if (place == "fisherdock" || place == "17" || place == "Fisherdock") { newx = 44; newy = 41; }
		else if (place == "hammerton" || place == "18" || place == "Hammerton") { newx = 44; newy = 34; }
		else if (place == "hammertown" || place == "19" || place == "Hammertown") { newx = 37; newy = 33; }
		else if (place == "trident" || place == "20" || place == "Trident") { newx = 40; newy = 21; }
		else if (place == "silvanville" || place == "21" || place == "Silvanville") { newx = 24; newy = 14; }
		float dist = calcDist(newx, newy);
		int distint;
		distint = (int) dist / 2;
		if (dist == 0)
			cout << "You are in the town which you want to travel to." << endl;
		else {
			cout << "It will take " << distint << " days to reach " << place << ".  You will also eat " << distint << " days of rations.  Start traveling? ";
			string query;
			cin >> query;
			if (query == "yes" || query == "y") {
				setDay(distint);
				inv[20] = inv[20] - distint;
				x = newx;
				y = newy;
				int i = 1;
				do {
					cout << "On day " << i << " ...\n";
					i = i + 1;
					randomEvent();
				} while (i <= distint);
				cout << "You have traveled to " << place << " over the course of " << distint << " days.  You have " << inv[20] << " days of rations left.\n";
			} else if (query == "no" || query == "n") {
				cout << "You decide to stay where you are.\n";
			}
		}		
	} else
		cout << "You are in combat.";
	act ();
}
void updtLvl () {
	while (XP >= lvlXP[lvl+1]) {
		XP -= lvlXP[lvl + 1];
		lvl += 1;
	}
}
void ACT () { // This function is here so act() can be called from within itself
	act ();
}
void act () {
	if (HP > maxHP)
		HP = maxHP;
	/*if (!HP <= -maxHP) {*/
	cout << "What would you like to do? ";
	string act;
	cin >> act;
	if (inCombat == false) {
		/*if (act == "attack" || act == "1") {
			// weapon chooser
			int wep;
			cout << "Which weapon will you use? Choices: ";
			if (cla == 1)
				cout << "longsword(1), dagger(2), light crossbow(3) "; // Fighter loadout
			if (cla == 2)
				cout << "short sword(1), crossbow(2), handaxe(3) "; // Rogue loadout
			if (cla == 3)
				cout << "magic missile(1), dagger(2), fireball(3) "; // Wizard loadout
			if (cla == 4)
				cout << "silvered shortsword(1), warhammer(2), light crossbow(3) "; // Cleric loadout
			cin >> wep;
			attack (wep, true, false);
		}*/
		if (act == "attack" || act == "1") { // new & improved attack system
			int atkCls;
			int wep;
			int spl;
			cout << "Which class of attack do you want to perform?\n | 1 - Weapon | 2 - Spell |\n";
			cin >> atkCls;
			switch (atkCls) {
				case 1:
					cout << "You have chosen to use a weapon to attack.  Which weapon do you want to use? Choices:\n | Slot 1: " << invNames[wepID[1]] << " |\n | Slot 2: " << invNames[wepID[2]] << " |\n | Slot 3: " << invNames[wepID[3]] << "|\n";
					cin >> wep;
					if (wep == 1 && wepID[1] == -1) {
						cout << "Slot 1 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (wep == 2 && wepID[2] == -1) {
						cout << "Slot 2 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (wep == 3 && wepID[3] == -1) {
						cout << "Slot 3 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else {
						attack(wep, false, false);
					}
					break;
				case 2:
					cout << "You have chosen to cast a spell.  Which one do you want to cast? Choices:\n | Slot 1: " << splNames[spellID[1]] << " |\n | Slot 2: " << splNames[spellID[2]] << " |\n | Slot 3: " << splNames[spellID[3]] << "|\n";
					cin >> spl;
					if (spl == 1 && spellID[1] == -1) {
						cout << "Slot 1 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (spl == 2 && spellID[2] == -1) {
						cout << "Slot 2 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (spl == 3 && spellID[3] == -1) {
						cout << "Slot 3 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else {
						spell(spl);
						break;
					}
					break;
			}
			ACT ();
		}
		else if (act == "move" || act == "2" || act == "travel") { // Travel
			mover ();
		}
		else if (act == "longrest" || act == "3" || act == "long") { // Long rest
			HP = maxHP;
			cout << "You completed a long rest(8 hours), so you regained all lost hit points." << endl;
			ACT ();
		}
		else if (act == "shortrest" || act == "4" || act == "short") { // Short rest
			int ranD = toprand(4); // Calculating a random number to add to your current HP
			HP = HP + ranD;
			if (HP > maxHP) // Making sure current HP after addition isn't higher than your maximum HP
				HP = maxHP;
			cout << "You completed a short rest(1 hour), so you regained " << ranD << " HP." << endl;
			ACT ();
		}
		else if (act == "scan" || act == "look" || act == "6") {
			cout << "You look around and see... ";
			scan ();
			ACT ();
		}
		else if (act == "checkup" || act == "check" || act == "7") {
			cout << "HP: " << HP << " maxHP: " << maxHP << " Armor Class: " << AC << " Experience Points: " << XP << " XP Required for Next Level: " << lvlXP[lvl + 1] << " Level: " << lvl << endl;
			int i = 1;
			do {
				if (!inv[i] == 0)
					cout << "You have " << inv[i] << " " << invNames[i] << "(s). ";
				i = i + 1;
			} while (i <= 30);
			i = 1;
			cout << endl << "It is the " << day << "th day of the " << month << "th month, " << year << "." << endl;
			ACT ();
		}
		else if (act == "eat" || act == "8") {
			if (!inv[20] == 0) {
				inv[20] = inv[20] - 1;
				cout << "You ate one day's worth of rations.  You now have " << inv[20] << " days of rations left." << endl;
			} else {
				cout << "You don't have anything to eat.";
			}
			ACT ();
		}
		else if (act == "drink" || act == "9") {
			if (!inv[30] == 0) {
				cout << "You drank five swallows of water from your canteen." << endl;
			} else if (inv[15] != 0) {
				cout << "Your canteen is empty." << endl;
			} else {
				cout << "You don't have a canteen." << endl;
			}
			ACT ();
		}
		else if (act == "buyfood" || act == "grocery" || act == "10") {
			tempint = toprand(20);
			if (tempint >= 10) {
				cout << "You found a merchant willing to sell you food.  How much food do you want to buy? ";
				cin >> tempint;
				if (inv[27] >= tempint / 2) {
					inv[27] = inv[27] - (tempint / 2);
					inv[20] += tempint;
					cout << endl << "You bought " << tempint << " days of rations for " << tempint / 2 << " gold pieces.\n";
				} else {
					cout << endl << "You don't have enough gold pieces to buy the food.\n";
				}
			} else
				cout << "You couldn't find a merchant willing to sell you food.\n";
			ACT ();
		}
		else if (act == "buy" || act == "11" || act == "purchase") {
			tempint = toprand(20);
			float cost;
			if (tempint >= 10) {
				cout << "You found a merchant.  What do you want to buy? (enter an item ID from the table in the docs folder, however not all items can be purchased here)\n";
				cin >> tempint;
				switch (tempint) {
					case 1:
						cost = 20;
						break;
					case 2:
						cost = 18;
						break;
					case 3:
						cost = 25;
						break;
					case 4:
						cost = 20;
						break;
					case 5:
						cost = 5;
						break;
					/*case 6:
						cost = 6;
						break;
					case 7:
						cost = 25;
						break;
					case 8:
						cost = 30;
						break;
					case 9:
						cost = 15;
						break;*/
					case 10:
						cost = 0.25;
						break;
					case 11:
						cost = 0.2;
						break;
					case 12:
						cost = 2;
						break;
					case 13:
						cost = 4;
						break;
					case 14:
						cost = 4;
						break;
					case 15:
						cost = 1;
						break;
					case 16:
						cost = 0.25;
						break;
					case 17:
						cost = 2;
						break;
					/*case 18:
						cost = 0.5;
						break;
					case 19:
						cost = 35;
						break;*/
					case 20:
						cost = 0.5;
						break;
					/*case 21:
						cost = 0.1;
						break;
					case 22:
						cost = 0.5;
						break;*/
					case 23:
						cost = 10;
						break;
					case 24:
						cost = 15;
						break;
					case 25:
						cost = 30;
						break;
					case 26:
						cost = 0.5;
						break;
					case 28:
						cost = 1;
						break;
					/*case 29:
						cost = 20;
						break;*/
				}
				if (cost == 0){
					cout << "That item cannot be purchased from this merchant.\n";
				} else {
				cout << "How many " << invNames[tempint] << " do you want to purchase?  Each one will cost you " << cost << " gold pieces.\n";
				int tempint2;
				cin >> tempint2;
				if (inv[27] >= tempint2*cost) {
					inv[27] = inv[27] - tempint2*cost;
					inv[tempint] = inv[tempint] + tempint2;
					cout << "You bought " << tempint2 << " " << invNames[tempint] << "(s) for " << tempint2*cost << " gold pieces.\n";
				} else {
					cout << "You don't have enough gold pieces to buy " << tempint2 << " " << invNames[tempint] << "(s).\n";
				}
				}
			} else {
				cout << "You were not able to find a merchant willing to sell you goods.\n";
			}
			ACT();
		}
		else if (act == "hunt" || act == "12") {
			tempint = toprand(20);
			if (tempint >= 10) {
				switch (tempint) {
					case 10:
					case 11:
					case 12:
						Enemy.set ("wild boar", 14, 14, 10, 9, 9, 9, 6, 8, 4, 8, true, -2, 1, "claws", "teeth", "paws", 1);
						cout << "You encounter a wild boar. ";
						break;
					case 13:
					case 14:
					case 15:
						Enemy.set ("wild dog", 14, 14, 10, 9, 9, 9, 6, 6, 4, 6, true, -3, 1, "claws", "jaws", "dog doo", 1);
						cout << "You encounter a wild dog.";
						break;
					case 16:
						Enemy.set ("wild turkey", 14, 14, 10, 9, 9, 9, 0, 0, 0, 6, true, -4, 1, "feathers", "gobble", "tail", 1);
						cout << "You encounter a wild turkey.";
						break;
					case 17:
						Enemy.set ("wild bull", 16, 14, 10, 9, 9, 9, 8, 8, 10, 12, true, -5, 1, "hoof", "head", "horns", 1);
						cout << "You encounter a bull.";
						break;
					case 18:
					case 19:
					case 20:
						Enemy.set ("wild badger", 14, 14, 10, 9, 9, 9, 8, 6, 10, 10, true, -6, 1, "claws", "paws", "jaws", 1);
						cout << "You encounter a wild honey badger.";
						break;
				}
				ACT();
			} else {
				cout << "You couldn't find an animal suitable for consumption.";
				ACT();
			}
		}
		else if (act == "sell" || act == "13") {
			tempint = toprand(20);
			if (tempint >= 10) {
				cout << "You found a merchant willing to buy some of your goods.  What do you want to sell? (enter an item ID from the table in the docs folder)\n";
				cin >> tempint;
				float cost;
				switch (tempint) {
					case 1:
						cost = 20;
						break;
					case 2:
						cost = 18;
						break;
					case 3:
						cost = 25;
						break;
					case 4:
						cost = 20;
						break;
					case 5:
						cost = 5;
						break;
					case 6:
						cost = 6;
						break;
					case 7:
						cost = 25;
						break;
					case 8:
						cost = 30;
						break;
					case 9:
						cost = 15;
						break;
					case 10:
						cost = 0.25;
						break;
					case 11:
						cost = 0.2;
						break;
					case 12:
						cost = 2;
						break;
					case 13:
						cost = 4;
						break;
					case 14:
						cost = 4;
						break;
					case 15:
						cost = 1;
						break;
					case 16:
						cost = 0.25;
						break;
					case 17:
						cost = 2;
						break;
					case 18:
						cost = 0.5;
						break;
					case 19:
						cost = 35;
						break;
					case 20:
						cost = 0.5;
						break;
					case 21:
						cost = 0.1;
						break;
					case 22:
						cost = 0.5;
						break;
					case 23:
						cost = 10;
						break;
					case 24:
						cost = 15;
						break;
					case 25:
						cost = 30;
						break;
					case 26:
						cost = 0.5;
						break;
					case 28:
						cost = 1;
						break;
					case 29:
						cost = 20;
						break;
				}
				cout << "How many " << invNames[tempint] << "(s) do you wish to sell?  Each one will earn you " << cost << " gold pieces.\n";
				int tempint2;
				cin >> tempint2;
				if (inv[tempint] >= tempint2) {
					inv[tempint] = inv[tempint] - tempint2;
					inv[27] = inv[27] + tempint2*cost;
					cout << "You sold " << tempint2 << " " << invNames[tempint] << "(s) for " << cost*tempint2 << " gold pieces.\n";
				} else {
					cout << "You don't have " << tempint2 << " " << invNames[tempint] << "(s).\n";
				}
			} else {
				cout << "You were unable to find a merchant willing to buy your goods.\n";
			}
			ACT();
		}
		else if (act == "tendees" || act == "TENDEES!") {
			cout << "You: 'TENDEES, TENDEES, GIVE THEM NOW, YOU FAT, UNGRATEFUL, SLUGGISH SOW!'\n";
			cout << "Thousands of chicken tenders rain from the sky and grace the land! +1000 food!\n";
			inv[20] = inv[20] + 1000;
			ACT ();
		}
		else if (act == "midas" || act == "I_LIKE_GOLD_LLC") {
			cout << "You: 'KING MIDAS, GIVE ME YOUR POWER!'\n";
			cout << "King Midas: 'You idiot!... whatever, here you go!'\n";
			int i = 1;
			do {
				if (i != 45) {
					inv[27] = inv[27] + inv[i];
					inv[i] = 0;
				}
				i = i + 1;
			} while (i <= 28);
			cout << "In horror, you watch all of your possessions turn into gold pieces and fall to the ground in a shimmering heap around your now-naked feet!\n";
			ACT ();
		}
		else if (act == "philswift") {
			cout << "Phil Swift descends from heaven!\n";
			cout << "Phil Swift takes out a grinder!\n";
			cout << "Phil Swift: 'To show you the power of FlexTape, I'm gonna saw this adventurer in half!'\n";
			Enemy.set ("Phil Swift", 20, 16, 16, 16, 16, 16, 8, 12, 10, 20, true, -42, 1, "grinder", "smile", "FlexTape", 3); // Setting the Phil Swift megaboss
			Enemy.dealDamage (1, true, false);
			inCombat = true;
			ACT();
		}
		else if (act == "flextape") {
			cout << "How much FlexTape do you wish to use? Each meter of it will heal 10 HP.\n";
			cin >> tempint;
			if (inv[29] >= tempint) {
				cout << "You use " << tempint << " meters of FlexTape, healing yourself by " << tempint * 10 << " HP.\n";
				inv[29] = inv[29] - tempint;
				HP += tempint*20;
			} else {
				cout << "You don't have enough FlexTape.\n";
			}
			ACT ();
		}
		else if (act == "exit" || act == "quit" || act == "9001") {
			string query;
			cout << "Do you really want to quit Dungeoneer? If so, enter `y` or `yes`.  (Any other input will be regarded as no)\n";
			cin >> query;
			if (query == "y" || query == "yes")
				cout << "Goodbye...";
			else
				ACT();
		}
		else if (act == "black_market" || act == "14" || act == "purchase_black") {
			tempint = toprand(6);
			float cost;
			if (tempint == 1) {
				cout << "You found a black market merchant.  What do you want to buy? (enter an item ID from the table in the docs folder, however not all items can be purchased here)\n";
				cin >> tempint;
				switch (tempint) {
					case 6:
						cost = 6;
						break;
					case 7:
						cost = 25;
						break;
					case 8:
						cost = 30;
						break;
					case 9:
						cost = 15;
						break;
					case 18:
						cost = 0.5;
						break;
					case 19:
						cost = 35;
						break;
					case 21:
						cost = 0.1;
						break;
					case 22:
						cost = 0.5;
						break;
					case 29:
						cost = 20;
						break;
				}
				if (cost == 0){
					cout << "That item cannot be purchased from this merchant.\n";
				} else {
				cout << "How many " << invNames[tempint] << " do you want to purchase?  Each one will cost you " << cost << " gold pieces.\n";
				int tempint2;
				cin >> tempint2;
				if (inv[27] >= tempint2*cost) {
					inv[27] = inv[27] - tempint2*cost;
					inv[tempint] = inv[tempint] + tempint2;
					cout << "You bought " << tempint2 << " " << invNames[tempint] << "(s) for " << tempint2*cost << " gold pieces.\n";
					tempint2 = toprand(5);
					if (tempint2 >= 4) {
						cout << "After leaving the black market, an officer from the local militia confronts you.\n";
						Enemy.set ("militia", 15, 14, 14, 11, 10, 12, 8, 4, 8, 10, true, 2, 1, "longsword", "dagger", "light crossbow", 3); // Setting the militiaman's stats
						Enemy.dealDamage (toprand(3), false, false);
					}
				} else {
					cout << "You don't have enough gold pieces to buy " << tempint2 << " " << invNames[tempint] << "(s).\n";
				}
				}
			} else if (tempint == 2) {
				cout << "On your way to find a black market merchant, an officer from the local militia confronts you.\n";
				Enemy.set ("militia", 15, 14, 14, 11, 10, 12, 8, 4, 8, 10, true, 2, 1, "longsword", "dagger", "light crossbow", 3); // Setting the militiaman's stats
				Enemy.dealDamage (toprand(3), false, false);
			} 
			else {
				cout << "You were not able to find a black market merchant.\n";
			}
			ACT();
		}
		// else if (act == "talents" || act == "15") {} Opens the talents menu, where you can view available talents, enabled talents, learn new talents, level up old ones, and more!
		else if (act == "loadout" || act == "16") { // Opens the loadout editor where weapons, talents, armor, and more can be managed easily.
			cout << " | 1 - Edit Weapon Loadout |\n | 2 - Edit Armor |\n | 3 - Edit Magic Slots |\n";
			cin >> tempint;
			switch (tempint) {
				case 1:
					cout << "| Current Loadout: |\n | 1 - " << invNames[wepID[1]] << " |\n | 2 - " << invNames[wepID[2]] << " |\n | 3 - " << invNames[wepID[3]] << " |\n";
					cout << "Enter numbers 1-3 to change slot, enter 4 to exit without editing slots.";
					cin >> tempint;
					switch (tempint) {
						case 1:
							cout << "Enter the item ID of a weapon in your inventory to change it, or enter -1 to cancel this operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 9) {
								if (inv[tempint] >= 1) {
									wepID[1] = tempint;
									DamDie[1] = wepDie[tempint];
									cout << "Weapon Slot 1 successfully switched to " << invNames[tempint] << "!\n";
								}
								cout << "That's not a weapon!\n";
							}
							break;
						case 2:
							cout << "Enter the item ID of a weapon in your inventory to change it, or enter -1 to cancel this operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 9) {
								if (inv[tempint] >= 1) {
									wepID[2] = tempint;
									DamDie[2] = wepDie[tempint];
									cout << "Weapon Slot 2 successfully switched to " << invNames[tempint] << "!\n";
								}
								cout << "That's not a weapon!\n";
							}
							break;
						case 3:
							cout << "Enter the item ID of a weapon in your inventory to change it, or enter -1 to cancel this operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 9) {
								if (inv[tempint] >= 1) {
									wepID[3] = tempint;
									DamDie[3] = wepDie[tempint];
									cout << "Weapon Slot 3 successfully switched to " << invNames[tempint] << "!\n";
								}
								cout << "That's not a weapon!\n";
							}
							break;
						case 4:
							break;
					}
					break;
				case 2:
					cout << "You are currently wearing " << invNames[armorType + 22] << " .\n | 1 - Light Armor |\n | 2 - Medium Armor |\n | 3 - Heavy Armor |\n | 4 - Exit |\n";
					cin >> tempint;
					switch (tempint) {
						case 1:
							if (inv[23] >= 1) {
								AC = 1;
								armorType = 1;
								cout << "You have successfully equipped Light Armor.\n";
							} else {
								cout << "You don't have any Light Armor.\n";
								break;
							}
							break;
						case 2:
							if (inv[24] >= 1) {
								AC = 2;
								armorType = 2;
								cout << "You have successfully equipped Medium Armor.\n";
							} else {
								cout << "You don't have any Medium Armor.\n";
								break;
							}
							break;
						case 3:
							if (inv[25] >= 1) {
								AC = 3;
								armorType = 3;
								cout << "You have successfully equipped Heavy Armor.\n";
							} else {
								cout << "You don't have any Heavy Armor.\n";
								break;
							}
							break;
						case 4:
							break;
					}
					break;
				case 3:
					cout << " | Current Loadout: |\n | Slot 1: " << splNames[spellID[1]] << " | Slot 2: " << splNames[spellID[2]] << " | Slot 3: " << splNames[spellID[3]] << " |\n";
					cin >> tempint;
					switch (tempint) {
						case 1:
							cout << "Enter the spell ID which you want to equip from the table in the /docs folder.  Entering -1 will cancel the operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 10) {
								spellID[1] = tempint;
								cout << "Spell Slot 1 has been successfully changed to " << splNames[tempint] << "!\n";
							}
							break;
						case 2:
							cout << "Enter the spell ID which you want to equip from the table in the /docs folder.  Entering -1 will cancel the operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 10) {
								spellID[2] = tempint;
								cout << "Spell Slot 2 has been successfully changed to " << splNames[tempint] << "!\n";
							}
							break;
						case 3:
							cout << "Enter the spell ID which you want to equip from the table in the /docs folder.  Entering -1 will cancel the operation.\n";
							cin >> tempint;
							if (tempint == -1) {
								ACT ();
							} else if (tempint <= 10) {
								spellID[3] = tempint;
								cout << "Spell Slot 3 has been successfully changed to " << splNames[tempint] << "!\n";
							}
							break;
						case 4:
							break;
					}
			}
			ACT();
		} 
		else {
			cout << "Unacceptable input.  Refer to the README for more information." << endl;
			ACT ();
		}
	} else {
		/*if (act == "attack" || act == "1") { // Soon to be changed to a system that uses the player's inventory to determine weapons
			// weapon chooser
			int wep;
			cout << "Which weapon will you use? Choices: ";
			if (cla == 1)
				cout << "longsword(1), dagger(2), light crossbow(3) "; // Fighter loadout
			if (cla == 2)
				cout << "short sword(1), crossbow(2), handaxe(3) "; // Rogue loadout
			if (cla == 3)
				cout << "magic missile(1), dagger(2), fireball(3) "; // Wizard loadout
			if (cla == 4)
				cout << "silvered shortsword(1), warhammer(2), light crossbow(3) "; // Cleric loadout
			cin >> wep;
			attack (wep, true, false);
		}*/
		if (act == "attack" || act == "1") { // new & improved attack system
			int atkCls;
			int wep;
			int spl;
			cout << "Which class of attack do you want to perform?\n | 1 - Weapon | 2 - Spell |\n";
			cin >> atkCls;
			switch (atkCls) {
				case 1:
					cout << "You have chosen to use a weapon to attack.  Which weapon do you want to use? Choices:\n | Slot 1: " << invNames[wepID[1]] << " |\n | Slot 2: " << invNames[wepID[2]] << " |\n  | Slot 3: " << invNames[wepID[3]] << "|\n";
					cin >> wep;
					if (wep == 1 && wepID[1] == -1) {
						cout << "Slot 1 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (wep == 2 && wepID[2] == -1) {
						cout << "Slot 2 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (wep == 3 && wepID[3] == -1) {
						cout << "Slot 3 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else {
						attack(wep, false, false);
					}
					break;
				case 2:
					cout << "You have chosen to cast a spell.  Which one do you want to cast? Choices:\n | Slot 1: " << splNames[spellID[1]] << " |\n | Slot 2: " << splNames[spellID[2]] << " |\n | Slot 3: " << splNames[spellID[3]] << "|\n";
					cin >> spl;
					if (spl == 1 && spellID[1] == -1) {
						cout << "Slot 1 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (spl == 2 && spellID[2] == -1) {
						cout << "Slot 2 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else if (spl == 3 && spellID[3] == -1) {
						cout << "Slot 3 is currently empty.(This action has not cost you a turn)\n";
						break;
					} else {
						spell(spl);
						break;
					}
					break;
			}
			ACT ();
		}
		else if (act == "dodge" || act == "2") {
			cout << "You dodged away from your enemy's blow, giving him a disadvantage." << endl;
			Enemy.dealDamage(toprand(3), false, true);
			ACT();
		}
		else if (act == "disengage" || act == "3") {
			int ranD = rand() % 2;
			if (ranD == 1) {
				inCombat = false;
				cout << "You successfully escaped from your enemies." << endl;
				Enemy.set ("Enemy", 13, 13, 13, 13, 13, 13, 6, 8, 4, 12, true, -1, 1, "scimitar", "light crossbow", "dagger", 2);
				ACT ();
			} else {
				cout << "You could not escape.  Your movement cost you a turn, so your enemy attacks." << endl;
				Enemy.dealDamage (toprand(3), true, false);
				ACT ();
			}
		}
		else if (act == "flextape") {
			cout << "How much FlexTape do you wish to use? Each meter of it will heal 10 HP.\n";
			cin >> tempint;
			if (inv[29] >= tempint) {
				cout << "You use " << tempint << " meters of FlexTape, healing yourself by " << tempint * 10 << " HP.\n";
				inv[29] = inv[29] - tempint;
				HP += tempint*10;
			} else {
				cout << "You don't have enough FlexTape.\n";
			}
			ACT ();
		}
		else {
			cout << "Unacceptable input.  Refer to the README for more information." << endl;
			ACT ();
		}
	}
	/*} else {
		cout << "You have deceased.";
		getchar();
	}*/
}
void setClass () {
	switch (clas) {
		case 1:
			armorType = 3;
			Str = 15;
			Dex = 14;
			Con = 14;
			Intl = 11;
			Wis = 12;
			Cha = 10;
			wepID[1] = 1;
			wepID[2] = 5;
			wepID[3] = 4;
			spellID[1] = 20;
			spellID[2] = 20;
			spellID[3] = 20;
			DamDie[1] = 8;
			DamDie[2] = 4;
			DamDie[3] = 8;
			HP = 12;
			maxHP = 12;
			cla = 1;
			AC = 3;
			cout << "You are a fighter: a seasoned warrior proficient in nearly all methods of combat.  You are equipped with a longsword, a dagger, and a light crossbow and quiver of 20 bolts.  Over your broad shoulders is slung an explorer's pack, filled with useful items such as a tinderbox, a canteen, and a 50-foot rope." << endl;
			ScoreAssoc[1] = Str;
			ScoreAssoc[2] = Str;
			ScoreAssoc[3] = Dex;
			inv[1] = 1; // longsword
			inv[5] = 1; // dagger
			inv[4] = 1; // light crossbow
			inv[10] = 20; // bolts
			inv[12] = 1; // Rope
			inv[13] = 1; // Tinderbox
			inv[14] = 1; // Mess kit
			inv[15] = 1; // Canteen
			inv[20] = 10; // Food, measured in days
			inv[27] = 100; // Gold pieces
			inv[25] = 1;
			inv[28] = 1; // Backpack
			break;
		case 2:
			armorType = 1;
			Str = 14;
			Dex = 15;
			Con = 13;
			Intl = 11;
			Wis = 14;
			Cha = 8;
			wepID[1] = 2;
			wepID[2] = 3;
			wepID[3] = 6;
			spellID[1] = 20;
			spellID[2] = 20;
			spellID[3] = 20;
			DamDie[1] = 6;
			DamDie[2] = 10;
			DamDie[3] = 6;
			HP = 9;
			maxHP = 9;
			cla = 2;
			AC = 1;
			cout << "You are a rogue: a stealthy bandit skilled with the crossbow and wielding a shortsword.  You are equipped with a shortsword, a crossbow with 40 bolts, and a handaxe.  On your back you wear a thieve's pack, equipped with a crowbar, assorted knives, food, and a 50-foot rope." << endl;
			ScoreAssoc[1] = Str;
			ScoreAssoc[2] = Dex;
			ScoreAssoc[3] = Str;
			inv[2] = 1;
			inv[3] = 1;
			inv[5] = 3;
			inv[6] = 1;
			inv[20] = 5;
			inv[10] = 40;
			inv[12] = 1;
			inv[17] = 1;
			inv[13] = 1;
			inv[27] = 80;
			inv[23] = 1;
			inv[28] = 1;
			break;
		case 3:
			Str = 10;
			Dex = 12;
			Con = 14;
			Intl = 15;
			Wis = 13;
			Cha = 8;
			wepID[1] = 5;
			spellID[1] = 1;
			spellID[2] = 2;
			spellID[3] = 3;
			DamDie[1] = 4;
			HP = 8;
			maxHP = 8;
			cla = 3;
			AC = 1;
			cout << "You are a wizard: a person shrouded in both mystery and the star-spangled cloak that covers your shoulders.  You can cast the magic missile, fireball, and burning hands spells.  You also carry a dagger.  On your emaciated shoulders lays the burden of a mage's sack, containing all the material elements needed to cast your spells." << endl;
			ScoreAssoc[1] = Str;
			ScoreAssoc[2] = Str;
			ScoreAssoc[3] = Str;
			inv[5] = 1;
			inv[28] = 1;
			inv[27] = 120;
			inv[19] = 1;
			inv[15] = 1;
			inv[16] = 3;
			break;
		case 4:
			armorType = 2;
			Str = 14;
			Dex = 12;
			Con = 12;
			Intl = 14;
			Wis = 10;
			Cha = 14;
			wepID[1] = 2;
			wepID[2] = 7;
			wepID[3] = 4;
			spellID[1] = 20;
			spellID[2] = 20;
			spellID[3] = 20;
			DamDie[1] = 9;
			DamDie[2] = 8;
			DamDie[3] = 8;
			HP = 8;
			maxHP = 8;
			cla = 4;
			AC = 2;
			cout << "You are a cleric: a priest of a deity who definitely does not scorn warfare.  You carry a silvered shortsword, a warhammer, and a light crossbow with 20 bolts.  On your blessed back you carry a priest's pack, filled with holy water and the tools of your solemn profession." << endl;
			ScoreAssoc[1] = Str;
			ScoreAssoc[2] = Str;
			ScoreAssoc[3] = Dex;
			inv[2] = 1;
			inv[4] = 1;
			inv[7] = 1;
			inv[18] = 1;
			inv[28] = 1;
			inv[13] = 1;
			inv[14] = 1;
			inv[10] = 20;
			inv[15] = 1;
			inv[24] = 1;
			inv[27] = 75;
			break;
	}
}
int main () {
	cout << "Welcome to Dungeoneer!" << endl;
	cout << "You are an adventurer embarking on a daring mission to... ";
	int init = rand() % 5;
	setInvNames();
	setMap();
	setSpellDies();
	setLvlInfo();
	int XP = 0;
	int lvl = 1;
	switch (init) {
		case 0:
			cout << "save a kidnapped girl!" << endl;
			break;
		case 1:
			cout << "recover lost treasure!" << endl;
			break;
		case 2:
			cout << "redeem yourself in society!" << endl;
			break;
		case 3:
			cout << "stop a heathen horde from destroying your village!" << endl;
			break;
		case 4:
			cout << "loot dungeons and overall be an idiot!" << endl;
			break;
	}
	cout << "Which class will your adventurer be?  Choices: fighter(1), rogue(2), wizard(3), cleric(4)" << endl;
	cin >> clas;
	setClass ();
	cout << "Looking around, you see... ";
	scan ();
	HP = maxHP;
	act ();
	return 0;
}
