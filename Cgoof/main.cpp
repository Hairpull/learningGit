// I followed along with Derek Banas' OOP lesson on YouTube and created a little battle simulator to study classes
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


class fighter {
public:

	fighter (string name, int attackMax, int blockMax, string battleCry = "Watch out!", string readyCry = "Oh boy!")
			{
			this->name=name;
			this->battleCry = battleCry;
			this->readyCry = readyCry;
			this->attackMax = attackMax;
			this->blockMax = blockMax;
			}
	
	string name;
	string shortDescription;
	string longDescription;
	string battleCry;
	string readyCry;
	int health = 100;
	int attack(){
		return rand() % this->attackMax;
	}
	int block(){
		return rand() % this->blockMax;
	}

	private:
	int attackMax;
	int blockMax;
	int strength = 50;
	int defense = 500;
	int initiative = 0;
			};

class roll{
	
};


class battle {
	
public:
	static void startFight(fighter& fighter1, fighter& fighter2)
	{
		printf("A fight has broken out between %s and %s!", fighter1.name.c_str(), fighter2.name.c_str());
		cout << endl;
		
		
		while(true)
		{
			if(battle::getAttackResult(fighter1, fighter2).compare("Game Over") == 0)
					{
						std::cout << "Game Over\n";
				break;
					}
			if(battle::getAttackResult(fighter2, fighter1).compare("Game Over") == 0)
			{
				std::cout << "Game Over\n";
		break;
			}
			
		}
	}
	
	static string getAttackResult(fighter& fighter1, fighter& fighter2)
	{
		int fighter1AttackAmount = fighter1.attack();
		int fighter2BlockAmount = fighter2.block();
		int damageToFighter2 = ceil(fighter1AttackAmount - fighter2BlockAmount);
		damageToFighter2 = (damageToFighter2 <= 0) ? 0 : damageToFighter2;
		fighter2.health = fighter2.health - damageToFighter2;
		
		printf("%s attacks %s and deals %d damage! \n", fighter1.name.c_str(), fighter2.name.c_str(), damageToFighter2);
		cout << endl;
		if (fighter2.health <= 0){
			fighter2.health = 0;
		}
		printf("%s is down to %d healh",fighter2.name.c_str(), fighter2.health);
		cout << endl;
		
		// slowdown the battle
		// usleep(50000);
		
		if(fighter2.health <= 0)
		{
		printf("%s has died and %s is victorious!", fighter2.name.c_str(), fighter1.name.c_str());
			cout << endl;
		return "Game Over";
		}
		else return "Fight Again";
	};
};

int main() {
	// had to static cast the returned value of time to an unsigned int to avoid compiler warnings
	srand(static_cast<unsigned int>(time(NULL)));
	
	fighter Terry("Terry", 75, 125, "Here I come puny boy!", "Let's go!");
	fighter Alex ("Alex", 90, 100, "Watch out for me!", "Not today buddy!");

	battle::startFight(Terry,Alex);

	return 0;
			};
