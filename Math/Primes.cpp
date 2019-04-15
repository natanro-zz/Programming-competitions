
/*gera _upperbound_ primos em O(N log log N) via sieve of Eratosthenes
Tambem faz fatoração em primos, via de um long long
Para verificar se numeros são primos, faz-se o upperbound
no maximo a raiz do maior numero possivel*/

#include <bits/stdc++.h>
using namespace std;

typedef long long  ll;
typedef vector<int> vi;

class Primes {
private:
	ll _sieve_size;
	bitset<10000010> bs;  //10^7 should be enough for most problems
	vi primes;	     //list of primes

	void sieve(){
		for(ll i=2; i<= _sieve_size; i++) if(bs[i]){
			for(ll j=i*i; j<= _sieve_size; j+= i) bs[j]=0;
			primes.push_back((int)i);
		}
	}
public:
	Primes(ll upperbound){
		_sieve_size = upperbound + 1;  //+1 to include upperbound
		bs.set();		      //set all bits to 1
		bs[0] = bs[1] = 0;
		sieve();
	}
	bool isPrime(ll number){
		if(number <= _sieve_size) return bs[number];
		for(int i=0; i<(int)primes.size(); i++){
			if(number % primes[i] == 0) return false;
		}
		return true;
	}
	vi primesFactors(ll number){
		vi factors;
		ll PF_idx =0, PF = primes[PF_idx];
		while(number != 1 && (PF*PF <= number)){
			while(number % PF == 0){
				number /= PF;
				factors.push_back(PF);
			}
			PF = primes[++PF_idx];
		}
		if(number != 1) factors.push_back(number);  //especial case when number is a prime
		return factors;
	}

	/*Totiente de Euler calcula quantos inteiros menores que
	number são coprimos com number, i.e. quantos numeros tem
	gcd == 1 com number*/
	ll EulerPhi(ll number){
		ll PF_idx = 0, PF = primes[PF_idx], ans = number;
		while(number != 1 && PF*PF <= number){
			if(number % PF == 0) ans -= ans / PF;
			while(number % PF == 0) number /= PF;
			PF = primes[PF_idx++];
		}
		if(number != 1) ans -= ans / PF;
		return ans;
	}
};
