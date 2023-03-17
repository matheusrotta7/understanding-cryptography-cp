use num_bigint::BigUint;
use num_traits::{Zero, One};
use std::mem::replace;

// Calculate large fibonacci numbers.
fn fib(n: usize) -> BigUint {
    let mut f0: BigUint = Zero::zero();
    let mut f1: BigUint = One::one();
    for _ in 0..n {
        let f2 = f0 + &f1;
        // This is a low cost way of swapping f0 with f1 and f1 with f2.
        f0 = replace(&mut f1, f2);
    }
    f0
}



fn main() {
    println!("Hello, world!");
    let mut f0: BigUint = Zero::zero();
    let mut f1: BigUint = One::one();
    let mut f2 = &f1 + &f1;
    let mut result: BigUint = One::one();


    let mut i = 0;

    println!("{}", f2);
    while i < 644 {
        result = result * &f2;
        println!("2**{} = {}", i+1, result);
        i = i + 1;
    }

    // // This is a very large number.
    // println!("fib(1000) = {}", fib(1000));
}
