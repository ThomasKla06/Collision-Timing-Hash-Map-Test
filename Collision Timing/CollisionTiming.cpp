#include "Hashbrowns.h"
#include <string>
#include <iostream>
using namespace std;

//Thomas Klaesges
//~2.2 hours

int main() {

	double averageFirstC{ 0 };
	double majorCol{ 0 };
	double loadFactor{ 0 };
	double loadFactor1{ 0 };
	double avgProbes{ 0 };
	double avgProbes4{ 0 };
	double currAvg{ 0 };
	int totalProbes{ 0 };
	bool firstMajorC{ true };
	bool firstC{ true };
	bool firstLoadFactor{ true };
	bool firstLoadFactor1{ true };

	//vals[0] stores the sum of inserts where first collision occured, total number will be 1000
	//vals[1] stores sum of inserts where first major collision occured, total number will be 1000
	//vals[2] stores first load factor of 0.9, total occurences will be 1000
	//vals[3] stores first load factor of 1.0, total occurences will be 1000
	//vals[4] stores number of probes for the current simulation, total number of inserts will be 55,000
	//valls[5] stores total inserts before average probing was more than four, vals[6] will be number of values recorded for it
	//The array is structured this way to make it easy to calculate the average for each at the end of the program
	double vals[7] = { 0,0,0,0,0,0,0 };
	string randStr{ "" };
	hashMap hash;

	for (int i = 0; i < 1000; i++){

		//adds 45 random elements to the hashmap
		for (int j = 0; j < 55; j++) {
			//Makes a string of 5 random letters
			for (int k = 0; k < 5; k++) {
				randStr += 'a' + (rand() % 26);
			}

			//Inserts random string into the hashmap
			if (hash.insert(randStr)) {
				if (firstC) {
					firstC = false;
					vals[0] += j;
				}
				if (hash.getProbes() > 0) {
					currAvg = vals[4] / j;
					vals[4] += hash.getProbes();
					if (hash.getProbes() >= 27 && firstMajorC) {
						firstMajorC = false;
						vals[1] += j;
					}
				}
				if (hash.getLoad() - 0.9 >= 0.001 && firstLoadFactor) {
					firstLoadFactor = false;
					vals[2] += j;
				}
				if (hash.getLoad() == 1.0 && firstLoadFactor1) {
					firstLoadFactor1 = false;
					vals[3] += j;
				}
				if (currAvg >= 4.0) {
					vals[5] += j;
					vals[6]++;
				}

			}
			//resets the random string so the variable can be reused
			randStr = "";
			hash.clearProbes();
		}

		//for testing, not needed
		//vector<string> dump = hash.dump();
		//for (int i = 0; i < dump.size(); i++) {
		//	cout << dump[i] << " ";
		//}
		//cout << endl;

		//Clears the hash table so it can be reused for the next simulation
		hash.clear();
		totalProbes += vals[4];
		vals[4] = 0;
		firstC = true;
		firstMajorC = true;
		firstLoadFactor = true;
		firstLoadFactor1 = true;
	}
	
	//Calculate results
	averageFirstC = vals[0] / 1000;
	majorCol = vals[1] / 1000;
	loadFactor = vals[2] / 1000;
	loadFactor1 = vals[3] / 1000;
	avgProbes = totalProbes / 55000;
	avgProbes4 = vals[5] / vals[6];

	//test results
	cout << "First Collision average: " << averageFirstC << endl;
	cout << "First Major Collision(27 probes required) average: " << majorCol << endl;
	cout << "Average First Load Factor of 0.9: " << loadFactor << endl;
	cout << "Average First Load Factor of 1.0: " << loadFactor1 << endl;
	cout << "Average Number of Probes: " << avgProbes << endl;
	cout << "Average Number of inserts before average is above 4: " << avgProbes4 << endl;

}