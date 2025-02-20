#pragma once
#include <string>
#include <vector>
using namespace std;

//Thomas Klaesges

class hashMap {
private:
	int probes{ 0 };
	int size{ 0 };
	int capac{ 53 };
	double load{ 0 };
	string* hmap = new string[capac];


public:
	hashMap() {
		for (int i = 0; i < capac; i++) {
			hmap[i] = "";
		}
	}

	//Returns first letter of the string as an index
	int hash(string s){
		int x{ s[0] - 97 };

		return x;
	}

	//Inserts at the closest available index
	bool insert(string s) {
		probes = 0;
		bool collision{ false };
		int ind{ hash(s) };
		if (lookup(s)) {
			probes++;
			return collision;
		}
		else {
			for (int i = 0; i < capac; i++) {
				if (hmap[(ind + i) % capac] != "") {
					collision = true;
					probes++;
				}
				else {
					hmap[(ind + i) % capac] = s;
					load += 1;
					break;
				}
			}
		}
		return collision;
	}

	//Looks for a string within the hash map array, returns true if found, returns false if not
	bool lookup(string s) {
		bool look{ false };
		int ind{ hash(s) };
		for (int i = 0; i < capac; i++) {
			if (hmap[(ind + i) % capac] != "") {
				if (hmap[(ind + i) % capac].compare(s) == 0) {
					look = true;
					break;
				}
				else {
					look = false;
				}
			}
		}
		return look;
	}

	void clear() {
		for (int i = 0; i < capac; i++) {
			hmap[i] = "";
		}
		load = 0;
	}
	//Returns decimal representing how much of the hash map is full
	double getLoad() { return load/capac; }
	//Returns amount of probes that the previous insert call performed
	int getProbes() { return probes; }
	//Resets the probe number to 0
	void clearProbes() { probes = 0; }

	//Returns hash map as a vector 
	vector<string> dump() {
		vector<string> vec;
		for (int i = 0; i < capac; i++) {
			vec.push_back(hmap[i]);
		}
		return vec;
	}
};