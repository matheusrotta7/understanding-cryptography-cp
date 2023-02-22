#include <bits/stdc++.h>

// using namespace std;

int main() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution distr(0, 25);

  std::string s;
  std::cin >> s;

  int shift = distr(gen) % 26;
  for (shift = 0; shift < 26; shift++) {
    std::cout << "current shift: " << shift << std::endl;
    for (int i = 0; i < s.length(); i++) {
      std::cout << (char)( ((s[i] + shift - 97) % 26) + 97);
    }
    std::cout << std::endl << std::endl;
  }
  std::cout << std::endl;

  return 0;
}
