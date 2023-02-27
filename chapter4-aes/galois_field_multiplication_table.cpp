#include <bits/stdc++.h>

void feed_charvalue_to_vector(int char_intvalue, int cur_pos, std::vector<bool> &plaintext_vector) {
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

std::vector<bool> polynomial_modulo(std::vector<bool> unmodded_poly, int m, std::vector<bool> irred_poly) {
  // we need to know the irreducible polynomial that is being used and
  // then left shift it until necessary, if the polynomial is already of
  // order less than m we don't need to do anything
  std::vector<bool> result = std::vector<bool>(m, false);
  int size = unmodded_poly.size();
  int first_bit = -33;
  for (int i = 0; i < size; i++) {
    if (unmodded_poly[i] != 0) {
      first_bit = i;
      break;
    }
  }

  int highest_deg = size-1-first_bit;
  if (highest_deg > m) {
    int offset = highest_deg - m;

  } else {
    for (int i = 0; i < m; i++) {
      result[m-1-i] = unmodded_poly[size-1-i];
    }
  }
}

std::vector<bool> polynomial_multiply(std::vector<bool> a, std::vector<bool> b, std::vector<bool> irred_poly) {
  int m = a.size();
  std::vector<bool> unmodded_res = std::vector<bool>((m-1)*2 + 1, false);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      bool c = a[i] && b[i];
      int deg = (m-1-i) + (m-1-j);
      unmodded_res[deg] = unmodded_res[deg] ^ c;
    }
  }
  return polynomial_modulo(unmodded_res, m, irred_poly);
}

int int main(int argc, char const *argv[]) {


  //this program will generate the multiplication table for the
  //extension fields of the form GF(2^m)

  int m;
  string irr_poly_string;

  std::cout << "please enter the desired order m: " << std::endl;
  std::cin >> m;

  std::cout << "please enter the desired irreducible polynomial: " << std::endl;
  std::cin >> irr_poly_string;

  std::vector<bool> irred_poly = std::vector<bool>(m, false);
  for (int i = 0; i < m; i++) {
    char cur_bit = irr_poly_string[i];
    if (cur_bit == '0') {
      irred_poly[i] = false;
    } else {
      irred_poly[i] = true;
    }
  }

  // the elements of the Galois Field with extension field 2^m are
  // polynomials of order m, and its coefficients belong to the prime field GF(2)
  // therefore, they are bits

  std::vector<bool> a = std::vector<bool>(m, false);
  std::vector<bool> b = std::vector<bool>(m, false);

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      feed_charvalue_to_vector(i, 0, a);
      feed_charvalue_to_vector(j, 0, b);

      std::vector<bool> result = polynomial_multiply(a, b, irred_poly);
    }
  }
  return 0;
}
