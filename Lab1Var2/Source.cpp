#include <iostream>  // cout
#include <cstdlib>   // srand, rand
#include <ctime>     // time
#include <map>       // map

// ASCII code for english letter 'a'
const int ASCII_FIRST_LETTER_CODE_LC = 97;
// ASCII code for english letter 'z'
const int ASCII_LAST_LETTER_CODE_LC = 122;

/*
 * Generates random string from english letters (lower case)
 * 
 * @param str Reference for string to fill
 * @param size Length of the generated string
 */
void generateRandomString(std::string& str, int size);

int main() {
	// initialize random seed
	std::srand(std::time(nullptr));
	// length of the generated string
	const int N = 10000;
	// the string to fill
	std::string str = "";
	// generate random string from english letters
	std::cout << "Generating string..." << std::endl;
	generateRandomString(str, N);

	// associative container to store pair of <letter, number>
	std::map<char, int> letter_dict;
	// fill the map
	for (int code = ASCII_FIRST_LETTER_CODE_LC; code <= ASCII_LAST_LETTER_CODE_LC; code++) {
		letter_dict.insert(std::pair<char, int>((char)code, 0));
	}
	// counting letters
	std::cout << "Calculating..." << std::endl;
	for (auto& letter : str) {
		letter_dict[letter] += 1;
	}
	// print the result
	for (auto& pair : letter_dict) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
	std::cout << "Press <Enter> to quit" << std::endl;
	std::getchar();
	return 0;
}

void generateRandomString(std::string& str, int size) {
	// clear string
	str.clear();

	// fill the string with english letters
	for (int i = 0; i < size; i++) {
		int ascii_code = ASCII_FIRST_LETTER_CODE_LC +
			(std::rand() % (ASCII_LAST_LETTER_CODE_LC - ASCII_FIRST_LETTER_CODE_LC + 1));
		str += (char)ascii_code;
	}
}