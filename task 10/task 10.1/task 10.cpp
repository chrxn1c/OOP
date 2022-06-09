#include <string>
#include <vector>
#include <iostream>

std::vector <int> createPFunction(std::string& substring) {
	std::vector <int> p;
	for (int _ = 0; _ < substring.size(); _++)
		p.push_back(0);

	int i = 1, j = 0;

	while (i < substring.size())
		if (substring[j] == substring[i]) {
			p[i] = j + 1;
			i++;
			j++;
		}
		else {
			if (j == 0) {
				p[i] = 0;
				i++;
			}
			else
				j = p[j - 1];
		}
	
	return p;
}


int KMP(std::string source, std::string substring) {
	int i = 0, j = 0;
	std::vector <int> p = createPFunction(substring);

	while (i < source.size()) {

		if (source[i] == substring[j]) {
			i++; j++;
			if (j == substring.size()) 
				return i - j;
		}

		else {
			if (j > 0)
				j = p[j - 1];
			else
				i++;
		}
	}

	if (i == source.size())
		return -1;
}

int main() {
	std::string test = "лилила";
	int start = KMP(test, "лила");
	std::cout << start;

	return 0;
}