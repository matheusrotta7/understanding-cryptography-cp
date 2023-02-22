#include <bits/stdc++.h>

// using namespace std;

int main() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution distr(0, 25);

  std::vector<float> letter_frequencies = std::vector<float>(26);
  letter_frequencies[0] = 0.0817f; //a
  letter_frequencies[1] = 0.0150f; //b
  letter_frequencies[2] = 0.0278f; //c
  letter_frequencies[3] = 0.0425f; //d
  letter_frequencies[4] = 0.1270f; //e
  letter_frequencies[5] = 0.0223f; //f
  letter_frequencies[6] = 0.0202f; //g
  letter_frequencies[7] = 0.0609f; //h
  letter_frequencies[8] = 0.0697f; //i
  letter_frequencies[9] = 0.0015f; //j
  letter_frequencies[10] = 0.0077f; //k
  letter_frequencies[11] = 0.0403f; //l
  letter_frequencies[12] = 0.0241f; //m
  letter_frequencies[13] = 0.0675f; //n
  letter_frequencies[14] = 0.0751f; //o
  letter_frequencies[15] = 0.0193f; //p
  letter_frequencies[16] = 0.0010f; //q
  letter_frequencies[17] = 0.0599f; //r
  letter_frequencies[18] = 0.0633f; //s
  letter_frequencies[19] = 0.0906f; //t
  letter_frequencies[20] = 0.0276f; //u
  letter_frequencies[21] = 0.0098f; //v
  letter_frequencies[22] = 0.0236f; //w
  letter_frequencies[23] = 0.0015f; //x
  letter_frequencies[24] = 0.0278f; //y
  letter_frequencies[25] = 0.0278f; //z

  std::vector<std::string> message = std::vector<std::string>();

  std::vector<int> occurence = std::vector<int>(26); //a - z

  std::vector<char> mapping = std::vector<char>(26);

  mapping[22] = 'i';
  mapping[1] = 't';
  mapping[15] = 'h';
  mapping[17] = 'e';
  mapping[11] = 'b';
  mapping[21]= 'c';
  mapping[12]= 'a';
  mapping[9]= 'o';
  mapping[18]= 'p';
  mapping[20]= 'r';
  mapping[23] = 'f';
  mapping[24] = 'm';
  mapping[4] = 'v';

  std::vector<bool> letter_used = std::vector<bool>(26, false);

  letter_used[8] = true;
  letter_used[19] = true;
  letter_used[7] = true;
  letter_used[4] = true;
  letter_used[1] = true;
  letter_used[2] = true;
  letter_used[0] = true;
  letter_used[14] = true;
  letter_used[15] = true;
  letter_used[17] = true;
  letter_used[5] = true;
  letter_used[12] = true;
  letter_used[21] = true;

  std::vector<bool> letter_searched = std::vector<bool>(26, false);

  letter_searched[22] = true;
  letter_searched[1] = true;
  letter_searched[15] = true;
  letter_searched[17] = true;
  letter_searched[11] = true;
  letter_searched[21] = true;
  letter_searched[12] = true;
  letter_searched[9] = true;
  letter_searched[18] = true;
  letter_searched[20] = true;
  letter_searched[23] = true;
  letter_searched[24] = true;
  letter_searched[4] = true;

  std::cout << "Hello World, Motherfucker!" << std::endl;

  int total = 0;

  std::string s = "test";
  while (std::cin >> s) {
    message.push_back(s);
    // std::cout << s << std::endl;
    for (int i = 0; i < s.length(); i++) {
      char cur_char = s[i];
      if (std::isalpha(cur_char)) {
        int pos = ((int) s[i]) - 97; // lowercase letter offset is 97 check ascii table
        occurence[pos]++;
        total++;
      }
    }
  }

  for (int i = 0; i < 26; i++) {
    std::cout << (char) (i + 97) << " ";
  }

  std::cout << std::endl;

  std::cout << "total occurence: " << std::endl;


  for (int i = 0; i < 26; i++) {
    std::cout << (char) (i + 97) << ": " << occurence[i] << " ";
  }

  std::cout << "relative occurence: " << std::endl;

  for (int i = 0; i < 26; i++) {
    std::cout << (char) (i + 97) << ": " << (float) occurence[i] / (float) total << " ";
  }

  std::cout  << std::endl;

  std::cout << "trying to match letter frequency in the text with probabilistic letter frequency for english language" << std::endl;

  for (int k = 12; k >= 0; k--) {

    int i = -23;
    while(true) {
      i = distr(gen) % 26;
      if (!letter_searched[i]) {
        letter_searched[i] = true;
        goto yolo;
      }
    }
    yolo:
    float cur_occ = (float) occurence[i] / (float) total;
    float smallest_offset = 100;
    int smallest_index = -1;
    for (int j = 0; j < 26; j++) {
      if (!letter_used[j]) {
        std::cout << letter_frequencies[j] << std::endl;
        std::cout << cur_occ << std::endl;
        float cur_offset = fabs(cur_occ - letter_frequencies[j]);
        // std::cout << cur_offset << std::endl;
        if (cur_offset < smallest_offset) {
          smallest_index = j;
          smallest_offset = cur_offset;
        }
      }
    }
    letter_used[smallest_index] = true;
    mapping[i] = (char) (smallest_index + 97);
  }

  std::cout << "current mapping found: " << std::endl;

  for (int i = 0; i < 26; i++) {
    std::cout << mapping[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "trying to decrypt the message with a poor table: " << std::endl;

  for (int i = 0; i < message.size(); i++) {
    std::string cur_str = message[i];
    for (int j = 0; j < cur_str.length(); j++) {
      char cur_char = cur_str[j];
      if (std::isalpha(cur_char)) {
        std::cout << mapping[cur_char-97];
      } else {
        std:: cout << cur_char;
      }
    }
  }
  std::cout << std::endl;


  return 0;
}
