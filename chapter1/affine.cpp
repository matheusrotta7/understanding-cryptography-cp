#include <bits/stdc++.h>

// using namespace std;

int main() {



  std::string s;
  std::cin >> s;

  int a = 15;
  int b = 22;


  for (int i = 0; i < s.length(); i++) {
    int test = ((((a * (s[i] - 97 - 22 + 26))) % 26) + 97);
    std::cout << (char) ((((a * (s[i] - 97 - 22 + 26))) % 26) + 97);
  }

  std::cout << std::endl;

  return 0;
}
