#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>

struct Claim
{
  int64_t id;
  int64_t left_offset, top_offset, width, height;
};

std::istream &operator>>(std::istream &is, Claim &claim)
{
  char c;
  is >> c >> claim.id >> c >> claim.left_offset >> c >> claim.top_offset >> c
    >> claim.width >> c >> claim.height;
  return is;
}

int main(int argc, char *argv[])
{
  std::ifstream infile(argv[1]);
  std::vector<Claim> inputs(std::istream_iterator<Claim>(infile), {});

  constexpr int64_t N(1000);
  std::vector<int64_t> fabric(N * N, 0);

  for(auto &input : inputs)
    {
      for(int64_t x = input.left_offset; x < input.left_offset + input.width;
          ++x)
        for(int64_t y = input.top_offset; y < input.top_offset + input.height;
            ++y)
          ++fabric[x + N * y];
    }

  int64_t sum(0);
  for(auto &f : fabric)
    {
      if(f > 1)
        { ++sum;}
    }
  std::cout << "Part 1: " << sum << "\n";

  for(auto &input : inputs)
    {
      bool duplicated(false);
      for(int64_t x = input.left_offset;
          x < input.left_offset + input.width && !duplicated; ++x)
        for(int64_t y = input.top_offset;
            y < input.top_offset + input.height && !duplicated; ++y)
          {
            if(fabric[x + N * y] > 1)
              { duplicated = true; }
          }
      if(!duplicated)
        { std::cout << "Part 2: " << input.id << "\n"; }
    }
}