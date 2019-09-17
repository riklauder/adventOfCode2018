#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <map>
#include <set>

using std::string;
//https://www.reddit.com/r/adventofcode/comments/a2xef8/2018_day_4_solutions/
void getInput(std::vector<std::string>& input) {
	std::string s;
	std::ifstream file("input.txt");
	while (getline(file, s))
		input.push_back(s);
}


int main() {
	std::vector<string> lines;
	getInput(lines);


}