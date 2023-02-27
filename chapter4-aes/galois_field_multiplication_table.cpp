#include <bits/stdc++.h>

std::vector<bool> int_value_to_bit_vector(int value, int m) {
  std::vector<bool> result = std::vector<bool>(m, false);
  // std::stack<bool> bit_stack;
  int pos = m-1;
  while (value != 0) {
    bool cur_bit = value % 2;
    value /= 2;
    result[pos--] = cur_bit;
  }
  return result;
}

std::vector<bool> left_shift(std::vector<bool> vec, int offset) {
  int vec_size = vec.size();
  int final_size = vec_size + offset;
  std::vector<bool> result = std::vector<bool>(final_size, false);
  for (int i = 0; i < vec_size; i++) {
    result[i] = vec[i]; //copying doesn't reach the end and we have offset left over zeroes
  }
  return result;
}

int degree_of(std::vector<bool> poly) {
  int size = poly.size();
  for (int i = 0; i < size; i++) {
    if (poly[i] != 0) {
      int first_bit = i;
      return size-1-first_bit;
    }
  }
  return 0;

}

std::vector<bool> xor_vectors(std::vector<bool> a, std::vector<bool> b) {
  int size = a.size();
  std::vector<bool> result = std::vector<bool>(size, false);
  for (int i = 0; i < size; i++) {
    result[i] = a[i] ^ b[i];
  }
  return result;
}


void print_vector_to_stdout(std::vector<bool> vec) {
  for (int i = 0; i < vec.size(); i++) {
    std::cout << (int) vec[i];
  }
}

void print_vector_to_stdout(std::vector<bool> vec, int m) {
  if (vec.size() < m) {
    int diff = m - vec.size();
    for (int i = 0; i < diff; i++) {
      std::cout << "0";
    }
  }
  print_vector_to_stdout(vec);
}

std::vector<bool> strip_trailing_zeros(std::vector<bool> poly) {
  if (poly.size() == 0) {
    return poly;
  }

  std::vector<bool> result = std::vector<bool>();
  int size = poly.size();
  bool is_zero_seq = true;
  for (int i = 0; i < size; i++) {
    if (is_zero_seq && poly[i] == false) {
      // don't add to result poly
    } else {
      is_zero_seq = false;
      result.push_back(poly[i]);
    }
  }

  return result;


}



std::vector<bool> polynomial_modulo(std::vector<bool> unmodded_poly, int m, std::vector<bool> irred_poly) {
  // we need to know the irreducible polynomial that is being used and
  // then left shift it until necessary, if the polynomial is already of
  // order less than m we don't need to do anything
  int size = unmodded_poly.size();
  std::vector<bool> result = std::vector<bool>(m, false);
  std::vector<bool> mask = std::vector<bool>(size, false);
  std::vector<bool> cur_modulo = std::vector<bool>(size, false);

  int highest_deg = degree_of(unmodded_poly);
  cur_modulo = strip_trailing_zeros(unmodded_poly);
  if (highest_deg >= m) {
    while (highest_deg >= m) {
      int offset = highest_deg - m;
      mask = left_shift(irred_poly, offset);
      cur_modulo = xor_vectors(cur_modulo, mask);
      cur_modulo = strip_trailing_zeros(cur_modulo);
      highest_deg = (degree_of(cur_modulo));
    }
    return cur_modulo;


  } else {
    for (int i = 0; i < m; i++) {
      result[m-1-i] = unmodded_poly[size-1-i];
    }
    return result;
  }
}

std::vector<bool> polynomial_multiply(std::vector<bool> a, std::vector<bool> b, std::vector<bool> irred_poly) {
  int m = a.size();
  std::vector<bool> unmodded_res = std::vector<bool>((m-1)*2 + 1, false);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      bool c = a[i] && b[j];
      int pos = i+j; // the smaller the i the bigger the degree...
      unmodded_res[pos] = unmodded_res[pos] ^ c;
    }
  }
  return polynomial_modulo(unmodded_res, m, irred_poly);
}

int main(int argc, char const *argv[]) {


  //this program will generate the multiplication table for the
  //extension fields of the form GF(2^m)

  int m;
  std::string irr_poly_string;

  std::cout << "please enter the desired order m: " << std::endl;
  std::cin >> m;

  std::cout << "please enter the desired irreducible polynomial: " << std::endl;
  std::cin >> irr_poly_string;

  std::vector<bool> irred_poly = std::vector<bool>(m+1, false);
  for (int i = 0; i < m+1; i++) {
    char cur_bit = irr_poly_string[i];
    if (cur_bit == '0') {
      irred_poly[i] = false;
    } else {
      irred_poly[i] = true;
    }
  }

  // the elements of the Galois Field with extension field 2^m are
  // polynomials of order m-1, and its coefficients belong to the prime field GF(2)
  // therefore, they are bits. m coefficients in total

  std::vector<bool> a = std::vector<bool>(m, false);
  std::vector<bool> b = std::vector<bool>(m, false);

  int power_val = (int) pow(2,m);

  for (int i = 0; i < power_val; i++) {
    for (int j = 0; j < power_val; j++) {
      a = int_value_to_bit_vector(i, m);
      b = int_value_to_bit_vector(j, m);

      std::vector<bool> result = polynomial_multiply(a, b, irred_poly);

      print_vector_to_stdout(a, m);
      std::cout << " x ";
      print_vector_to_stdout(b, m);
      std::cout << " = ";
      print_vector_to_stdout(result, m);
      std::cout << std::endl;
    }
  }
  return 0;
}
