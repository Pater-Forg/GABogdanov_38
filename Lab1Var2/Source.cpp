#include <iostream>  // cout
#include <cstdlib>   // srand, rand
#include <ctime>     // time
#include <map>       // map

// ASCII ��� ��� ����� "a" ����������� ��������
const int ASCII_FIRST_LETTER_CODE_LC = 97;
// ASCII ��� ��� ����� "z" ����������� ��������
const int ASCII_LAST_LETTER_CODE_LC = 122;

/*
 * ���������� ������ �� ��������� �������� ����������� �������� (� ������ ��������)
 * 
 * @param str ������ �� ������ ��� ����������
 * @param size �������� ����� ������
 */
void generateRandomString(std::string& str, int size);

int main() {
	// ������ ���� ��� ����
	std::srand(std::time(nullptr));
	// ����� ������������ ������
	const int N = 10000;
	// ������ ��� ����������
	std::string str = "";
	// ���������� ������ �� ��������� �������� ����������� ��������
	generateRandomString(str, N);

	// ������������� ��������� ��� �������� ��� <�����, ����������>
	std::map<char, int> letter_dict;
	// ��������� �������, ������������ ���������� ���� � 0
	for (int code = ASCII_FIRST_LETTER_CODE_LC; code <= ASCII_LAST_LETTER_CODE_LC; code++) {
		letter_dict.insert(std::pair<char, int>((char)code, 0));
	}

	// ������� ������
	for (auto& letter : str) {
		letter_dict[letter] += 1;
	}

	// ������� ���������
	for (auto& pair : letter_dict) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}

	return 0;
}

void generateRandomString(std::string& str, int size) {
	// ������� ������
	str.clear();

	// ��������� ������ ���������� ��������� ����������� ��������
	for (int i = 0; i < size; i++) {
		int ascii_code = ASCII_FIRST_LETTER_CODE_LC +
			(std::rand() % (ASCII_LAST_LETTER_CODE_LC - ASCII_FIRST_LETTER_CODE_LC + 1));
		str += (char)ascii_code;
	}
}