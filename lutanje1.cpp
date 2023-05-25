#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>

// F - funkcija
template<typename F>
// koristimo F&& - to je rvalue, jer funkciju metnemo u argument
std::pair<long long, long long> lutanje(F&& f, long long a0, long long N) {
	std::vector<long long> a = {a0 % N};
	
	for(int i = 1; ; i++) {
		// racunamo a_i
		a.push_back(f(a[i-1]) % N);
		
		std::cout << a[i] << '\n';
		// proveravamo a_2i i a_i
		if(!(i % 2)) {
			int x = std::gcd(a[i] - a[i/2], N);
			if(x > 1) {
				return {x, N/x};
			}
		}
		
		// bolesniji nacin - bez if
		// int x = !(i % 2)*std::gcd(a[i] - a[i/2, N]) + (i % 2);
		// if(x > 1) return {x, N/x};
	
	}
	
	return {0, 0};

}

int main() {

	int N;
	
	std::cout << "Unesi N\n";
	std::cin >> N;
	
	//std::pair<long long, long long> PQ = lutanje([](long long x) {return x*x + 1;}, 0, N);
	// moze i ovako
	 auto f = [](long long x) {return x*x + 1;};
	 auto PQ = lutanje(std::move(f), 0, N);
		
	std::cout << PQ.first << ", " << PQ.second << '\n';
	
	return 0;
}
