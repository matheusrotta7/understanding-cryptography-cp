#include <bits/stdc++.h>

void print_vector_to_stdout(std::vector<bool> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << vec[i];
  }
}

void feed_charvalue_to_vector(int char_intvalue, int &cur_pos, std::vector<bool> &plaintext_vector) {
  //get binary representation of char_intvalue by iteratively dividing by two and feed it to the vector
  //doesn't look sharp or clean
  //maybe I should use masks to add the chars to a int64_t, but that decision is very commital
  std::stack<bool> bit_stack;
  while (char_intvalue != 0) {
    bool cur_bit = char_intvalue % 2;
    char_intvalue /= 2;
    bit_stack.push(cur_bit);
  }

  while (!bit_stack.empty()) {
    // std::cout << bit_stack.top() <<" ";
    plaintext_vector[cur_pos++] = bit_stack.top();
    bit_stack.pop();
  }
}

int main(int argc, char const *argv[]) {

  // input will be 64 bits of plaintext, we will get it cin
  // for now a simple generation of 64 bits of cyphertext, later we can work with padding
  // and encrypting larger files

  // first get 64 bits from stdin
  int64_t plaintext;
  // std::cin >> plaintext;
  // std::cout << plaintext << std::endl;

  std::vector<bool> plaintext_vector = std::vector<bool>(64, 0);


  std::string plaintext_string;
  std::cin >> plaintext_string; //adjusted to be exactly 64 bits for now
  std::cout << "plaintext string is: " << plaintext_string << std::endl;

  int cur_pos = 0;
  for (int i = 0; i < plaintext_string.length(); i++) {
    char cur_char = plaintext_string[i];
    int char_intvalue = (int) cur_char;
    feed_charvalue_to_vector(char_intvalue, cur_pos, plaintext_vector);
  }

  std::cout << "plaintext vector of bits is: ";
  print_vector_to_stdout(plaintext_vector);
  std::cout << std::endl;

  // now we have to do the initial permutation
  std::vector<bool> initial_permutation = std::vector<bool>(64, 0);
  int ip_dest[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41,  9, 49, 17, 57, 25}; //bit 1 goes to pos 40, bit 2 goes to pos 8, etc.

  for (int i = 0; i < 64; i++) {
    initial_permutation[ip_dest[i] - 1] = plaintext_vector[i];
  }

  std::cout << "After initial permutation: ";
  print_vector_to_stdout(initial_permutation);
  std::cout << std::endl;

  return 0;
}
