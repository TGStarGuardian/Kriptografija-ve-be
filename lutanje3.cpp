#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

// taken from https://codeforces.com/blog/entry/23365
long long inv(long long a, long long b) {
	if(a < 0) return inv(b + (a % b), b);
	return a <= 1? 1 : b - inv(b % a, a) * b/a;
}

std::pair<int, int> add(std::pair<int, int>& P, std::pair<int, int>& Q, std::pair<int, int>& curve, int q) {
	if(P.first == q) return Q;
	if(Q.first == q) return P;
	
	if(P.first == Q.first && P.second == Q.second) {
		// 2P
		//  k = (3x^2 + A)*(2y)^(-1)
		if(std::gcd(2*P.second, q) != 1) return {q, 0}; 
		int k = ((3*P.first*P.first + curve.first) * inv(2*P.second, q)) % q;
		if(k < 0) k += q;
		// n = y - k*x
		int n = (P.second - k*P.first) % q;
		if(n < 0) n += q;
		int xr = (k*k - 2*P.first) % q;
		if(xr < 0) xr += q;
		int yr = (-(k*xr + n)) % q;
		if(yr < 0) yr += q;
		return {xr, yr};
	} else {
		// P + Q
		if(std::gcd(Q.first - P.first, q) != 1) return {q, 0};
		int k = ((Q.second - P.second) * inv(Q.first - P.first, q)) % q;
		if(k < 0) k += q;
		int n = (P.second - k*P.first) % q;
		if(n < 0) n += q;
		int xr = (k*k - P.first - Q.first) % q;
		if(xr < 0) xr += q;
		int yr = (-(k*xr + n)) % q;
		if(yr < 0) yr += q;
		return {xr, yr};
	}
}

int lutanje(std::pair<int, int>& curve, int q, std::pair<int, int>& G, std::pair<int, int>& R, int m) {
	std::vector<std::pair<int, int>> P = {{q, q}};
	std::vector<std::pair<int, int>> v = {{0, 0}};
	
	for(int i = 0; ; i++) {
		// beskonacno daleka tacka
		if(P[i].first == q || P[i].first <= 33) {
			P.push_back({add(P[i], R, curve, q)});
			v.push_back({v[i].first + 1, v[i].second});
		} else if(P[i].first > 33 && P[i].first < 68) {
			P.push_back({add(P[i], P[i], curve, q)});
			v.push_back({2*v[i].first, 2*v[i].second});
		} else {
			P.push_back({add(P[i], G, curve, q)});
			v.push_back({v[i].first, v[i].second + 1});
		}
		
		if(i > 0 && !(i % 2) && P[i].first == P[i/2].first && P[i].second == P[i/2].second) {
			return ((v[i/2].second - v[i].second) * inv(v[i].first - v[i/2].first, m)) % m;
		}
		// std::cout << "(" << P[i].first << ", " << P[i].second << ")\n";
	}
	
	return -1;
}

int main() {
	// y^2 = x^3 + Ax + B
	// u sustini, bitno je samo cuvati A i B
	std::pair<int, int> curve;
	std::cout << "Unesi A i B\n";
	std::cin >> curve.first >> curve.second;
	int q;
	std::cout << "Unesi q\n";
	std::cin >> q;
	std::pair<int, int> g;
	std::cout << "Unesi g\n";
	std::cin >> g.first >> g.second;	
	std::pair<int, int> R;
	
	std::cout << "Unesi R\n";
	std::cin >> R.first >> R.second;
	
	// trazimo x tako da je g^x = R
	int m;
	std::cout << "Unesi m\n";
	std::cin >> m;
	
	int x = lutanje(curve, q, g, R, m);
	
	if(x < 0) x += m;
	std::cout << x << '\n';
	
	return 0;
}
