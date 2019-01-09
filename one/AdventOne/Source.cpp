#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <limits>
#include <list>
#include <map>
#include <set>
#include <numeric>		
#include <iterator>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::istream;
using std::stoi;


bool frequencycalibrate(vector<long> &list, long &freq, std::set<long> &dupe) {
	bool fd = false;
	int index = 0;
	
	long freqchange = 0;
	std::string s;
	ifstream inputFile("input2.txt");
	while (getline(inputFile, s)) {
		freqchange = stoi(s);
		freq += freqchange;
		list.push_back(freq);
		if (dupe.find(freq) != dupe.end()) {
			std::cout << "duplicate frequency found:" << freq << std::endl;
			fd = true;
			return fd;
		}
		else {
			dupe.insert(freq);
		}

	}
	return fd;
}


int main() {
	/*full list f frequencies*/
	vector<long> freqlist;
	std::set<long> dupe;
	
	/*currrent frequency*/
	long frequency = 0;
	bool dupeindex = false;
	
	long listcycles=0;

	while (!dupeindex) {
		dupeindex = frequencycalibrate(freqlist, frequency, dupe);
		//std::cout << "sizes cycles:freqist " << listcycles++ << ":" << freqlist.size() << std::endl;
	}
	
	cout << "FINAL Frequency" << frequency << endl;

}
