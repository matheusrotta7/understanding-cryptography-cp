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

void convert_string_into_vector_of_bits(std::string str, std::vector<bool> &vec) {
  int cur_pos = 0;
  for (int i = 0; i < str.length(); i++) {
    char cur_char = str[i];
    int char_intvalue = (int) cur_char;
    feed_charvalue_to_vector(char_intvalue, cur_pos, vec);
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

  // int cur_pos = 0;
  // for (int i = 0; i < plaintext_string.length(); i++) {
  //   char cur_char = plaintext_string[i];
  //   int char_intvalue = (int) cur_char;
  //   feed_charvalue_to_vector(char_intvalue, cur_pos, plaintext_vector);
  // }
  convert_string_into_vector_of_bits(plaintext_string, plaintext_vector);

  std::cout << "plaintext vector of bits is: ";
  print_vector_to_stdout(plaintext_vector);
  std::cout << std::endl;

  //also let's get the key from the file key.txt
  std::string key_string;
  std::ifstream keyfile_stream;

  keyfile_stream.open("key.txt");
  keyfile_stream >> key_string;
  keyfile_stream.close();
  std::cout << "key string is: " << key_string << std::endl;

  std::vector<bool> key_vector = std::vector<bool>(64, 0);

  convert_string_into_vector_of_bits(key_string, key_vector);

  std::cout << "key vector of bits is: ";
  print_vector_to_stdout(key_vector);
  std::cout << std::endl;


  // now we have to do the initial permutation
  std::vector<bool> initial_permutation = std::vector<bool>(64, 0);
  int ip_inv[64] = {40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41,  9, 49, 17, 57, 25}; //initial perm inverted
  int ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
               60, 52, 44, 36, 28, 20, 12, 4,
               62, 54, 46, 38, 30, 22, 14, 6,
               64, 56, 48, 40, 32, 24, 16, 8,
               57, 49, 41, 33, 25, 17,  9, 1,
               59, 51, 43, 35, 27, 19, 11, 3,
               61, 53, 45, 37, 29, 21, 13, 5,
               63, 55, 47, 39, 31, 23, 15, 7 };

  for (int i = 0; i < 64; i++) {
    initial_permutation[i] = plaintext_vector[ip[i] - 1];
  }

  std::cout << "After initial permutation: ";
  print_vector_to_stdout(initial_permutation);
  std::cout << std::endl;

  // now we split the 64 bits in two 32 bit parts, L0 and R0
  std::vector<bool> l0 = std::vector<bool>(32, false); //left side
  std::vector<bool> r0 = std::vector<bool>(32, false); //right side

  for (int i = 0; i < 32; i++) {
    l0[i] = initial_permutation[i];
  }

  for (int i = 32; i < 64; i++) {
    r0[i] = initial_permutation[i];
  }

  //before beginning the feistel network rounds
  //we should also make the permuted choice one (PC-1) of the key since it only happens once

  std::vector<bool> perm_choice_1 = std::vector<bool>(56, false);

  int pc1[56] = {57, 49, 41, 33, 25, 17,  9,  1,
                 58, 50, 42, 34, 26, 18, 10,  2,
                 59, 51, 43, 35, 27, 19, 11,  3,
                 60, 52, 44, 36, 28, 20, 12,  4,
                 31, 23, 15,  7, 62, 54, 46, 38,
                 30, 22, 14,  6, 61, 53, 45, 37,
                 29, 21, 13,  5, 28, 20, 12,  4}

  for (int i = 0; i < 56; i++) {
    perm_choice_1[i] = key_vector[pc1[i] - 1];
  }

  //split permuted choice one into C0 and D0
  std::vector<bool> c0 = std::vector<bool>(28, false);
  std::vector<bool> d0 = std::vector<bool>(28, false);

  for (int i = 0; i < 28; i++) {
    c0[i] = perm_choice_1[i];
  }

  for (int i = 28; i < 56; i++) {
    d0[i] = perm_choice_1[i];
  }

  // now we can begin the feistel network rounds, sixteen in total
  // we will use r0 and l0 vectors always as the previous values from rounds,
  // updating them when needed, so r0 = r_prev and l0 = l_prev
  for (int i = 0; i < 16; i++) {
    // r1 = l0 xor f(k1, r0)
    // l1 = r0
    std::vector<bool> r_res = std::vector<bool>(32, false); //r1 when i = 0
    std::vector<bool> l_res = std::vector<bool>(32, false); //l1 when i = 0

    // first we can copy r0 to l1 (l1 = r0)
    for (int j = 0; j < 32; j++) {
      l_res[j] = r0[j];
    }

    r_res = xor_vectors(l0, f_function(k1, r0));

  }




  return 0;
}
