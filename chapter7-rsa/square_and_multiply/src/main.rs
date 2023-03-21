fn main() {
    let x = 3;
    let e = 197;
    let m = 101;

    println!("Using the square and multiply algorithm, x^e mod m is: {}", mod_exp(x, e, m));
}

//created by chatgpt! 
fn mod_exp(base: u64, exp: u64, modulus: u64) -> u64 {
    let mut result = 1;
    let mut base = base % modulus;
    let mut exp = exp;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * base) % modulus;
        }
        exp >>= 1;
        base = (base * base) % modulus;
    }

    result
}
