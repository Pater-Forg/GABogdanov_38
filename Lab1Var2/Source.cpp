#include <iostream>  // cout
#include <cstdlib>   // srand, rand
#include <ctime>     // time
#include <map>       // map

// ASCII код для буквы "a" английского алфавита
const int ASCII_FIRST_LETTER_CODE_LC = 97;
// ASCII код для буквы "z" английского алфавита
const int ASCII_LAST_LETTER_CODE_LC = 122;

/*
 * Генерирует строку из случайных символов английского алфавита (в нижнем регистре)
 * 
 * @param str ссылка на строку для заполнения
 * @param size желаемая длина строки
 */
void generateRandomString(std::string& str, int size);

int main() {
	// задаем семя для ГПСЧ
	std::srand(std::time(nullptr));
	// длина генерируемой строки
	const int N = 10000;
	// строка для заполнения
	std::string str = "";
	// генерируем строку из случайных символов английского алфавита
	generateRandomString(str, N);

	// ассоциативный контейнер для хранения пар <буква, количество>
	std::map<char, int> letter_dict;
	// заполняем словарь, устанавливая количество букв в 0
	for (int code = ASCII_FIRST_LETTER_CODE_LC; code <= ASCII_LAST_LETTER_CODE_LC; code++) {
		letter_dict.insert(std::pair<char, int>((char)code, 0));
	}

	// считаем буковы
	for (auto& letter : str) {
		letter_dict[letter] += 1;
	}

	// выводим результат
	for (auto& pair : letter_dict) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}

	return 0;
}

void generateRandomString(std::string& str, int size) {
	// очищаем строку
	str.clear();

	// заполняем строку случайными символами английского алфавита
	for (int i = 0; i < size; i++) {
		int ascii_code = ASCII_FIRST_LETTER_CODE_LC +
			(std::rand() % (ASCII_LAST_LETTER_CODE_LC - ASCII_FIRST_LETTER_CODE_LC + 1));
		str += (char)ascii_code;
	}
}