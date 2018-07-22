//
//  myDie.cpp
//  Cgoof
//
//  Created by Dustin Beck on 7/19/18.
//  Copyright © 2018 Dustin Beck. All rights reserved.
//


#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric>
#include <math.h>
#include <chrono>
#include <unistd.h>

using namespace std;

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
	
	int roll(){
		printf("Rolling %i sided die...\n",sides);
		int roll;
		int min = 1;
		int max = this->sides;
		

		
		roll = rand() % (max - min + 1) + min;
		
		return roll;
	}
};

int main(){
	int roll;

	myDie die;
	
	do {
		roll = die.roll();
		cout << roll << endl;
	}while (roll != 1);

	
	return 0;
}
