#include <iostream>
#include <cmath>
#include <numeric>

// taken from https://codeforces.com/blog/entry/23365
long long inv(long long a, long long b) {
	if(a < 0) return inv(b + (a % b), b);
	return a <= 1? 1 : b - inv(b % a, a) * b/a;
}

std::pair<int, int> add(std::pair<int, int>& P, std::pair<int, int>& Q, std::pair<int, int>& curve, int q) {
	if(P.first == Q.first && P.second == Q.second) {
		// 2P
		//  k = (3x^2 + A)*(2y)^(-1)
		if(std::gcd(2*P.second, q) != 1) return {q, q}; 
		int k = ((3*P.first*P.first + curve.first) * inv(2*P.second, q)) % q;
		if(k < 0) k += q;
		// n = y - k*x
		int n = (P.second - k*P.first) % q;
		if(n < 0) n += q;
		int xr = (k*k - 2*P.first) % q;
		if(xr < 0) xr += q;
		return {xr, (q - (k*xr + n)) % q};
	} else {
		// P + Q
		if(std::gcd(Q.first - P.first, q) != 1) return {q, q};
		int k = ((Q.second - P.second) * inv(Q.first - P.first, q)) % q;
		if(k < 0) k += q;
		int n = (P.second - k*P.first) % q;
		if(n < 0) n += q;
		int xr = (k*k - P.first - Q.first) % q;
		if(xr < 0) xr += q;
		return {xr, (q - (k*xr + n)) % q};
	}
}

std::pair<int, int> ecfrac(int N, std::pair<int, int>& curve, std::pair<int, int>& R) {
	// sabiramo tacku R sa samom sobom dok ne naletimo na problem
	std::pair<int, int> tmp = R;
	std::pair<int, int> k = tmp;
	
	while(true) {
		tmp = add(tmp, R, curve, N);
		
		// moze da bude minus ispred, a to ne valja...
		if(tmp.first < 0) tmp.first += N;
		if(tmp.second < 0) tmp.second += N;
				
		if(tmp.first == N) {
			// onda smo zaboli problem
			// na osnovu prethodnog tmp racunamo p ili q
			if(k.first == R.first && k.second == R.second) {
				// racunamo NZD od 2R.second i N
				int p = std::gcd(2*R.second, N);
				return {p, N/p};
			} else {
				// racunamo NZD od R.second - k.second i N
				int x = (R.first - k.first) % N;
				if(x < 0) x += N;
				int p = std::gcd(x, N);
				return {p, N/p};
			}
		}
		k = tmp;
	}
	
	return {0, 0};
}

int main() {
	// y^2 = x^3 + Ax + B
	// u sustini, bitno je samo cuvati A i B
	std::pair<int, int> curve;
	std::cout << "Unesi A i B\n";
	std::cin >> curve.first >> curve.second;
	
	std::pair<int, int> R;
	
	std::cout << "Unesi R\n";
	std::cin >> R.first >> R.second;
	
	int N;
	std::cout << "Unesi N\n";
	std::cin >> N;
	
	//std::cout << inv(5, 10) << "\n";
	
	std::pair<int, int> PQ = ecfrac(N, curve, R);	
	
	std::cout << PQ.first << ", " << PQ.second << '\n';		
	
	return 0;
}
