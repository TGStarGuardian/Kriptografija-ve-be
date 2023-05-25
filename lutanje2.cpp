#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>


// taken from https://codeforces.com/blog/entry/23365
long long inv(long long a, long long b){
	return a <= 1? 1 : b - inv(b % a, a) * b/a;
}

int lutanje(int g, int q, int y) {
	std::vector<int> c = {1};
	std::vector<std::pair<int, int>> v = {{0, 0}};
	
	for(int i = 0; ; i++) {
		if(c[i] <= 33) {
			c.push_back((c[i]*y) % q);
			v.push_back({v[i].first + 1, v[i].second});
		} else if(c[i] < 68) {
			c.push_back((c[i]*c[i]*c[i]) % q);
			v.push_back({3*v[i].first, 3*v[i].second});
		} else {
			c.push_back((c[i]*g) % q);
			v.push_back({v[i].first, v[i].second + 1});
		}
		
		std::cout << "c: "<< c[i] << '\n';
		
		if(i > 0 && !(i % 2) && c[i] == c[i/2]) {
			int b = (v[i/2].second - v[i].second) % (q - 1);
			int a = (v[i].first - v[i/2].first) % (q - 1);
			std::cout << a << ", " << b << '\n';
			return (b*inv(a, q - 1)) % (q - 1);
		}
	
	}
	
	return -1;
}

int main() {

	int g, q, x, y;
	
	std::cout << "q:";
	std::cin >> q;
	
	std::cout << '\n';
	
	std::cout << "g:";
	std::cin >> g;
	
	std::cout << '\n';
	
	std::cout << "y:";
	std::cin >> y;
	
	std::cout << '\n';
	
	x = lutanje(g, q, y);
	
	// ako je x >= 0, vracamo x
	// ako je x < 0, vracamo q - 1 - x
	// (x >= 0)*x + (x < 0) * (q - 1 + x)
	// (x >= 0)*x + (x < 0)*(q - 1) + (x < 0)*x
	// ((x >= 0) + (x < 0))*x + (x < 0)*(q - 1)
	std::cout << ((x >= 0) + (x < 0))*x + (x < 0)*(q - 1) << '\n';	
	
	return 0;
}
