#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <limits>
#include <numeric>	
#include <string>
#include <cstring>

using std::string;
using std::stoi;

/*create single vector for every elf fabric claim listed in input*/
void getclaims(std::vector<string> &c) {
	std::string s;
	std::ifstream file("input.txt");
	while (getline(file, s))
		c.push_back(s);
}

/*for each claim obtain data - c=claimdata c0=id c1-2=bounds c3-4=dims*/
void processclaims(std::vector<string> &c, std::vector<std::vector<unsigned int>> &data) {

	for (int i = 0; i < c.size(); i++) {
		std::string s;
		s = c[i];
		string s1 = s.substr(1, s.find(" "));
		int id = stoi(s1);
		data[i].push_back(id);
		int bounds=s.find("@");
		string s2 = s.substr(bounds + 1, s.find(","));
		int top = stoi(s2);
		string s3 = s.substr(s.find(",")+1, s.find(":"));
		int left = stoi(s3);
		data[i].push_back(top);
		data[i].push_back(left);
		string s4 = s.substr(s.find(":") + 2, s.find("x"));
		int dw = stoi(s4);
		string s5 = s.substr(s.find("x") + 1, s.size());
		int dh = stoi(s5);
		data[i].push_back(dw);
		data[i].push_back(dh);
	}

}


void fillSuitMatrix(std::vector<std::vector<unsigned int>>& suit, int& id, int& top, int& left, int& w, int& h) {
	for (int l = left; l < left + w; l++){
		for (int i = top; i < top+h; i++){ 
			suit[i][l] += id;
			if (suit[i][l] > id)
				suit[i][l] = 9999;
			}
		}
	}


void buildClaimMatrix(std::vector<std::vector<unsigned int>>& suit, std::vector<std::vector<unsigned int>>& data) {
	for (int i = 0; i < data.size(); i++) {
		int id = data[i][0];
		int left = data[i][1];
		int top = data[i][2];
		int wid = data[i][3];
		int hi = data[i][4];
		fillSuitMatrix(suit, id, top, left, wid, hi);
	}
}

int main() {
	int suitDimensions = 1000;
	/*1000x1000 matrix will hold claim IDs - 0 for overlaps*/
	
	std::vector<std::vector<unsigned int>> suit(suitDimensions);
	for (int i = 0; i < suitDimensions; ++i) {
		std::vector<unsigned int> grid(suitDimensions);
		for (int l = 0; l < suitDimensions; ++l)
			grid[l] = 0;
		suit[i] = grid;
	}

	std::vector<string> claims;
	getclaims(claims);
	int numClaims = claims.size();

	/*for each claim c=claimdata c0=id c1-2=bounds c3-4=dims*/
	std::vector<std::vector<unsigned int>> claimdata(numClaims);
	int overlaps=0;
	processclaims(claims, claimdata);

	buildClaimMatrix(suit, claimdata);

	for (int i = 0; i < suitDimensions; i++)
		for (int j = 0; j < suitDimensions; j++)
			if (suit[i][j] == 9999)
				overlaps += 1;
	int sqover = std::sqrt(overlaps);

	/*Can be used to print patter
	for (int i = 0; i < suitDimensions; i++) {
		for (int j = 0; j < suitDimensions; j++)
			std::cout << suit[i][j] << " ";
		std::cout << std::endl;
	}*/

	std::cout << overlaps << " square inches have more than a single claim" << std::endl;
	
}

/*
104241 square inches have more than a single claim using data rovided
*/