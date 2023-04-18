// Prime number generation code
//
// written by Aaron Bloomfield, 2014

#include <iostream>
#include <string> 
using namespace std;

// yes, there are much faster -- and much better -- ways to check if a
// number is prime (see the Sieve of Eratosthenes, for one example),
// but this code will work correctly, it is fairly straightforward,
// and it is fast enough for our purposes in the hash lab
bool checkprime(unsigned int p) {
    if ( p <= 1 ) // 0 and 1 are not primes; the are both special cases
        return false;
    if ( p == 2 ) // 2 is prime
        return true;
    if ( p % 2 == 0 ) // even numbers other than 2 are not prime
        return false;
    for ( int i = 3; i*i <= p; i += 2 ) // only go up to the sqrt of p
        if ( p % i == 0 )
            return false;
    return true;
}

int getNextPrime (unsigned int n) {
    while ( !checkprime(++n) );
    return n; // all your primes are belong to us
}


long long hashString(string str) {
	int p = 83; 
	int m = 1e9 + 9;
	long long hash_value = 0; 
	long long p_pow = 1; 
	for (char c : str) {
		hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
	}	
	return hash_value; 
}

int main() {
    cout << "Enter number: ";
    cin >> x;
    cout << x << " is prime: " << checkprime(x) << endl;
    cout << "next higest prime: " << getNextPrime(x) << endl;
}
