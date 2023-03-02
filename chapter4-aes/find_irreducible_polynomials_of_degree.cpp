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



std::vector<bool> polynomial_modulo(std::vector<bool> unmodded_poly, std::vector<bool> irred_poly) {
  // we need to know the irreducible polynomial that is being used and
  // then left shift it until necessary, if the polynomial is already of
  // order less than m we don't need to do anything
  int m = degree_of(irred_poly);
  int size = unmodded_poly.size();
  std::vector<bool> result = std::vector<bool>(m, false);
  std::vector<bool> mask = std::vector<bool>(size, false);
  std::vector<bool> cur_modulo = std::vector<bool>(size, false);

  int highest_deg = degree_of(unmodded_poly);
  cur_modulo = strip_trailing_zeros(unmodded_poly);
  if (highest_deg >= m) {
    while (highest_deg >= m) {
      int offset = highest_deg - m;
      mask = strip_trailing_zeros(left_shift(irred_poly, offset));
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

bool all_bit_are_zeroes(std::vector<bool> poly) {
  int size = poly.size();
  for (int i = 0; i < size; i++) {
    if (poly[i] == true) {
      return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[]) {


  //this program will find all irreducible polynomials of degree m

  int m;

  std::cout << "please enter the desired degree m: " << std::endl;
  std::cin >> m;

  std::vector<bool> test_poly;
  std::vector<bool> low_deg_poly;

  int test_poly_begin = (int) pow(2, m);
  int test_poly_end = (int) pow(2, m+1) - 1;
  int low_deg_begin = 2;
  int low_deg_end = (int) pow(2, m) - 1;


  for (int i = test_poly_begin; i <= test_poly_end; i++) {
    bool is_irreducible = true;
    test_poly = int_value_to_bit_vector(i, m+1);
    for (int j = low_deg_begin; j <= low_deg_end; j++) {
      low_deg_poly = int_value_to_bit_vector(j, m+1);

      std::vector<bool> result = polynomial_modulo(test_poly, low_deg_poly);
      if (all_bit_are_zeroes(result)) {
        is_irreducible = false;
        break;
      }
    }

    if (is_irreducible) {
      std::cout << "found irreducible polynomial: ";
      print_vector_to_stdout(test_poly, m);
      std::cout << std::endl;
    }
  }

  return 0;
}
