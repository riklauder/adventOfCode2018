#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <limits>
#include <list>
#include <set>
#include <numeric>		
#include <iterator>
#include <functional>
#include <cstring>
#include <iterator>
#include <map>

using std::stoi;

struct nanobot {
	long x, y, z, r;
};

std::vector<std::string> split(std::string str, char dl) {
	std::string word = "";
	int num = 0;
	str = str + dl;
	int l = str.size();
	std::vector<std::string> substr_list;
	for (int i = 0; i < l; i++) {
		if (str[i] != dl)
			word = word + str[i];
		else {
			if ((int)word.size() != 0)
				substr_list.push_back(word);
			word = "";
		}
	}
	return substr_list;
}

void getnanos(std::vector<nanobot> &n) {
	std::string s;
	nanobot nano;
	char dl = ',';
	std::ifstream file("input.txt");
	while (getline(file, s)) {
		std::vector<std::string> spl = split(s, dl);
		nano.x = stoi(spl[0]);
		nano.y = stoi(spl[1]);
		nano.z = stoi(spl[2]);
		nano.r = stoi(spl[3]);
		n.push_back(nano);
	}
}

bool cmpFirst(std::pair<int, std::string> const& x,
	std::pair<int, std::string> const& y)
{
	return x.first < y.first;
}

int main() {
	std::vector<nanobot> nanobots;

	getnanos(nanobots);
	std::sort(nanobots.begin(), nanobots.end(),
		[](const nanobot &n0, const nanobot &n1) { return n0.r < n1.r; });
	auto &nanorange(nanobots.back());
	//returns max r selected from all nanobots
	long radius = nanorange.r;
	std::cout << "nano largest r: " << radius << std::endl;
	std::cout << "at position: (" << nanorange.x << "," << nanorange.y << "," << nanorange.z << ")" << std::endl;
	
	/*
	for (auto &i : nanobots) {
		i.x -= nanorange.x;
		i.y -= nanorange.y;
		i.z -= nanorange.z;
	}*/

	long countinrange = 0;
	for (auto &i : nanobots) {
		long nanodistance = std::abs(nanorange.x - i.x) + std::abs(nanorange.y - i.y) + std::abs(nanorange.z - i.z);
		if (nanodistance <= radius)
			countinrange++;
	}

	std::cout << "nanobots in ranget : " << countinrange << std::endl;
	std::cout << "Part 2: " << std::endl;

	std::vector<int> overlaps;
	for (int i = 0; i < nanobots.size(); i++) {
		overlaps.push_back(0);
		for (auto &j : nanobots) {
			int ndist = (std::abs(nanobots[i].x -j.x )) + (std::abs(nanobots[i].y - j.y)) + (std::abs(nanobots[i].z - j.z));
			int nrang = (nanobots[i].r + j.r);
			if (ndist < nrang)
				overlaps[i] += 1;
		}
			
	}
	
	std::vector<int> index;
	auto mxov = *std::max_element(overlaps.begin(), overlaps.end());
	std::vector<int>::iterator it = std::find(overlaps.begin(), overlaps.end(), mxov);
	
	while ((it = std::find(it, overlaps.end(), mxov)) != overlaps.end()) {
		auto mxovi = std::distance(overlaps.begin(), it);
		index.push_back(mxovi);
		it++;
	}

	std::cout << "max overlaps : " << mxov << std::endl;


	int result= 999999999;
	for (int i = 0; i < index.size(); i++) {
			int ndist = std::max(0, (int)(std::abs(0 - nanobots[index[i]].x) + std::abs(0 - nanobots[index[i]].y) + std::abs(0 - nanobots[index[i]].z))) - nanobots[index[i]].r;
			if (ndist < result)
				result = ndist;
	}

	std::cout << "result : " << result << std::endl;

	std::cout << "Part 2-2: " << std::endl;
	std::map<int, int> ranges;
	for (auto &i : nanobots) {
		int distfzero = (std::abs(i.x-0) + std::abs(i.y-0) + std::abs(i.z - 0));
		ranges.insert(std::pair<int, int>(std::max(0, distfzero - (int)i.r), 1));
		ranges.insert(std::pair<int, int>(distfzero + (int)i.r, -1));
	}
	int count = 0;
	int res = 0;
	int maxcount = 0;
	std::map<int, int>::iterator itr;
	for (auto itt = ranges.begin(); itt != ranges.end(); ++itt) {
		count += itt->second;
		if (count > maxcount) {
			res = itt->first;
			maxcount = count;
		}

	}

	std::cout << "result map : " << res << std::endl;

		return 0;
}
/*OUTPUT
nano largest r: 99557954
at position: (2228276,36324817,116599291)
nanobots in ranget : 232
Part 2:
max overlaps : 994
result : 52679606
Part 2-2:
result map : 82010396
*/