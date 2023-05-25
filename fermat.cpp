#include <iostream>
#include <numeric>
#include <cmath>

// pretpostavljamo da je N = p*q za proste brojeve p i q
std::pair<long long, long long> fermat_factorisation(int N) {
	long long x = std::floor(std::sqrt((long double)N)) + 1;
	
	// isprobavamo x_i = x + i za sve i >= 0
	// testiramo da li je z = sqrt(x^2 - n) ceo broj
	// ako jeste, faktori su (x - z) i (x + z)
	 
	for(int i = 0; i <= std::sqrt((long double)N); i++) {
	
		long double z = std::sqrt((long double)(x*x - N));
		
		if(std::floor(z) == z) {
			return {(long long)x - z, (long long)x + z};
		}
		x++;
	
	}
	
	return {0, 0};
}

int main() {

	int N;
	std::cout << "Unesi N\n";
	std::cin >> N;
	
	std::pair<long long, long long> F = fermat_factorisation(N);
	
	std::cout << F.first << ", " << F.second << '\n';


	return 0;
}
