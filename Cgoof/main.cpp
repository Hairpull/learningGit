// I followed along with Derek Banas' OOP lesson on YouTube and created a little battle simulator to study classes.
// Never intended to make this code public, so it's not entirely commented. Primarily using this file to learn how Git works.
// -DB

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <numeric>
#include <math.h>
#include <chrono>
#include <unistd.h>


using namespace std;

class item {
	friend class fighter;
public:
	int defMod = 0;
	int attMod = 0;
	string itemName = "";
	
	item(string name, int aMod, int dMod){
		this->itemName = name;
		this->attMod = aMod;
		this->defMod = dMod;
		printf("%s appears on the battlefield! \n", itemName.c_str());
	}
	item(){
		itemName = "item";
		attMod = 0;
		defMod = 0;
	}
};

class fighter {
	friend class battle;
public:

	fighter (string name, int attackMax, int blockMax, string battleCry = "Watch out!", string readyCry = "Oh boy!")
			{
			this->name=name;
			this->battleCry = battleCry;
			this->readyCry = readyCry;
			this->attackMax = attackMax;
			this->blockMax = blockMax;
			}
	string getName(){
		return name;
	}
	
	void getStats(){
		printf ("Name: %s\nAttack: %i\nBlock: %i\nHealth: %i\n\n",this->name.c_str(), this->attack(), this->block(), this->health);
	}
	public:
	string name;
	string shortDescription;
	string longDescription;
	string battleCry;
	string readyCry;
	int health = 100;
	
	// aMod and dMod are variables for storing any item-related attack or defense mods
	int aMod = 0;
	int dMod = 0;
	
	int attack(){
		return rand() % this->attackMax +1;
	}
	int block(){
		return rand() % this->blockMax;
	}
	
	string equip(item& gear){
		

		aMod = gear.attMod;
		dMod = gear.defMod;
		
		printf("%s equipped %s\n",  name.c_str(), gear.itemName.c_str());
		return "";
	}

private:
	int attackMax;
	int blockMax;
	int strength = 50;
	int defense = 500;
	int initiative = 0;
			};

// Die system
/*
 
class myDie {
public:
	int sides = 6;
	
	myDie(int sides){
		this->sides = sides;
		srand(time(0));
	}
	myDie(){
		sides = 6;
		srand(time(0));
	}
	
	int roll(fighter roller){
		string report = roller.name.c_str();
		printf(report.c_str());
		printf(" is rolling %i sided die...\n",sides);
		int roll;
		int min = 1;
		int max = this->sides;
		
		
		
		roll = rand() % (max - min + 1) + min;
		
		return roll;
	}
};

*/

class battle {
	
public:
	static void startFight(fighter& fighter1, fighter& fighter2)
	{
		printf("\nA fight has broken out between %s and %s!\n", fighter1.name.c_str(), fighter2.name.c_str());
		cout << endl;
		
		
		while(true)
		{
			// fighter 1 attacks fighter2
			
			if(battle::getAttackResult(fighter1, fighter2).compare("Game Over") == 0)
					{
						std::cout << "Game Over\n";
				break;
					}
			
			// fighter 2 attacks fighter1
			
			if(battle::getAttackResult(fighter2, fighter1).compare("Game Over") == 0)
					{
				std::cout << "Game Over\n";
				break;
					}
			
		}
	}
	
	static string getAttackResult(fighter& fighter1, fighter& fighter2)
	{
		
		int fighter1AttackAmount = fighter1.attack() + fighter1.aMod;
		int fighter2BlockAmount = fighter2.block() + fighter1.dMod;
		
		int damageToFighter2 = ceil(fighter1AttackAmount - fighter2BlockAmount);
		damageToFighter2 = (damageToFighter2 <= 0) ? 0 : damageToFighter2;
		fighter2.health = fighter2.health - damageToFighter2;
		
		// battle dialogue
		battleDialogue(fighter1, fighter2);
		// fighters attack each other
		
		if (fighter2BlockAmount >= fighter1AttackAmount){
			printf("%s blocks %s's attack! %s deals %d damage! \n", fighter2.name.c_str(), fighter1.name.c_str(), fighter1.name.c_str(), damageToFighter2);
		}
		else {
		printf("%s attacks %s and deals %d damage! \n", fighter1.name.c_str(), fighter2.name.c_str(), damageToFighter2);
		};
		
		
		cout << endl;
		if (fighter2.health <= 0){
			fighter2.health = 0;
		}
		printf("%s is down to %d healh\n",fighter2.name.c_str(), fighter2.health);
		cout << endl;
		
		
		// slowdown the battle
		// usleep(50000);
		
		if(fighter2.health <= 0)
		{
		printf("%s has died and %s is victorious!\n", fighter2.name.c_str(), fighter1.name.c_str());
			cout << endl;
		return "Game Over";
		}
		else return "Fight Again";
	};
	
	static void battleDialogue(fighter& fighter1, fighter& fighter2){
		int roll = rand() % 10 + 1;
		// printf("Roll: %i\n",roll);
		
		if (roll == 1){
			printf("%s : %s\n",fighter1.name.c_str(),fighter1.battleCry.c_str()); // fighter one shouts their battlecry
			printf("%s : %s\n\n",fighter2.name.c_str(),fighter2.readyCry.c_str());  // fighter 2 responds with their readycry
			}
		if (roll == 10){
			printf("%s : %s\n",fighter2.name.c_str(),fighter2.battleCry.c_str());
			printf("%s : %s\n\n",fighter1.name.c_str(),fighter1.readyCry.c_str());
			}
		else{};
		
		
		

		
		};
};

int main() {
	// had to static cast the returned value of time to an unsigned int to avoid compiler warnings
	srand(static_cast<unsigned int>(time(NULL)));

	item Armor("Armor", 0, 10);
	item Axe("Axe", 10, 0);
	fighter Terry("Terry", 75, 125, "Here I come puny boy!", "Let's go!");
	fighter Alex ("Alex", 90, 100, "Watch out for me!", "Not today buddy!");
	Alex.getStats();
	Terry.getStats();
	
	Terry.equip(Armor);
	Alex.equip(Axe);
	
	battle::startFight(Terry,Alex);

	return 0;
			};
