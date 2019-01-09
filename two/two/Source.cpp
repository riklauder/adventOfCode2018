#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <limits>
#include <numeric>	
#include <iterator>
#include <string>
#include <set>
#include <cstring>
#include <map>


void getboxes(std::vector<std::string> &b) {
	std::string s;
	std::ifstream file("input.txt");
	while (getline(file, s)) 
		b.push_back(s);
}

void dupes(std::string &s, int &d, int &t) {
	// initialize an array to hold the count of occurrances
	int counts[std::numeric_limits<unsigned char>::max()] = { 0 };
	bool deux = false;
	bool trois = false;

	for (unsigned char u : s) 
		++counts[u];

	// find the chars which count is equal to 3 then 4
	for (unsigned char u : s) {
		if (counts[u] == 3 && trois == false) {
			trois = true;
			t += 1;
		}
		if (counts[u] == 2 && deux == false) {
			deux = true;
			d += 1;
		}
	}

}

void diffs(std::vector<std::string> &b) {
	int u = 0;
	int box = 0;
	for (auto &i : b) {
		int diff = 0;
		for (auto &j : b) {
			for (int k = 0; k < i.size(); k++) {
				if (i[k] != j[k]) {
					diff++;
					u = k;
				}
				if (diff > 1) {
					diff = 0;
					break;
				}
			}
			if (diff == 1) {
				std::cout << "result : ";
				for (int k = 0; k < j.size(); k++) {
					if (k != u)
						std::cout << j[k];
				}
				std::cout << std::endl;
			}
		}
	}
}

int main() {
	std::vector<std::string> boxes;
	int deux = 0;
	int trois = 0;

	getboxes(boxes);

	std::cout << "part 1" << std::endl;
	for (auto i : boxes) {
		dupes(i, deux, trois);
	}

	int checksum = deux * trois;

	std::cout << "checksum is :" << checksum << std::endl;

	std::cout << "part 2" << std::endl;
	diffs(boxes);
	

	
}