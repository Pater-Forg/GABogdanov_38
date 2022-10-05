#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "Employee.h"

std::string genFullName(std::string fn_file, std::string mn_file, std::string ln_file);
std::string genGender();
Date genDateOfBirth(int min_age, int max_age);
int countNumberOfLines(std::ifstream& fin);
void randFillArrayOfEmployees(std::vector<Employee>& emps);
std::vector<Employee> selectByFullName(const std::vector<Employee>& emps, const std::string fn);
std::vector<Employee> selectByYearOfBirth(const std::vector<Employee>& emps, int year, char op);
void printStatisticsByGender(const std::vector<Employee>& emps);
void sortByAge(std::vector<Employee>& emps, bool isDesc);
void printEmployees(std::vector<Employee>& emps);

/*
 * Print message, clear stdin and ignore INT_MAX characters or till new line
 *
 * @param msg message to print
 */
void fixInputError(const char* msg);

int main() {
	std::srand(std::time(nullptr));
	int n = 0;
	std::cout << "Enter number of employees [1, 100]\n> ";
	std::cin >> n;
	if (std::cin.fail() || n < 1 || n > 100) {
		fixInputError("Ivalid size");
		return 0;
	}
	std::vector<Employee> emps(n);
	randFillArrayOfEmployees(emps);
	for (int i = 0; i < n; i++) {
		std::cout << i + 1 << ". " << emps[i].full_name << std::endl;
	}

	std::vector<Employee> selection;
	std::string fname;
	int year = 0;
	char oper = '\0';
	int option = 0;
	bool cond = true;
	const char* msg = "\nSelect option:\n"
		"[1] Find employee by full name\n"
		"[2] Print selection by year of birth\n"
		"[3] Print statistics by gender\n"
		"[4] Sort by age and print\n"
		"[5] Print this message\n"
		"[0] Exit";
	std::cout << msg << std::endl;
	while (cond) {
		std::cout << "> ";
		std::cin >> option;
		if (std::cin.fail()) {
			fixInputError("Number expected");
			continue;
		}
		switch (option)
		{
		case 1:
			std::cout << "Enter full name" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, fname);
			selection = selectByFullName(emps, fname);
			std::cout << "Selection:\n- - -" << std::endl;
			printEmployees(selection);
			break;
		case 2:
			std::cout << "Enter year" << std::endl;
			std::cin >> year;
			if (std::cin.fail()) {
				fixInputError("Number expected");
				continue;
			}
			std::cout << "Choose comparation [>/<]" << std::endl;
			std::cin >> oper;
			if (std::cin.fail()) {
				fixInputError("Char expected");
				continue;
			}
			selection = selectByYearOfBirth(emps, year, oper);
			std::cout << "Selection:\n- - -" << std::endl;
			printEmployees(selection);
			break;
		case 3:
			printStatisticsByGender(emps);
			break;
		case 4:
			std::cout << "[A]scending or [D]escending?" << std::endl;
			std::cin >> oper;
			if (std::cin.fail()) {
				fixInputError("Char expected");
				continue;
			}
			if (toupper(oper) == 'A')
				sortByAge(emps, false);
			else if (toupper(oper) == 'D')
				sortByAge(emps, true);
			else {
				fixInputError("Wrong option");
				continue;
			}
			printEmployees(emps);
			break;
		case 5:
			std::cout << msg << std::endl;
			break;
		case 0:
			cond = false;
			break;
		default:
			fixInputError("Wrong option");
			break;
		}
	}
	return 0;
}

std::string genFullName(std::string fn_file, std::string mn_file, std::string ln_file) {
	std::ifstream fn_stream(fn_file);
	std::ifstream mn_stream(mn_file);
	std::ifstream ln_stream(ln_file);

	if (!fn_stream || !mn_stream || !ln_stream) return "";

	static int fn_count = countNumberOfLines(fn_stream);
	static int mn_count = countNumberOfLines(mn_stream);
	static int ln_count = countNumberOfLines(ln_stream);

	int fn_line = std::rand() % (fn_count + 1);
	int mn_line = std::rand() % (mn_count + 1);
	int ln_line = std::rand() % (ln_count + 1);

	std::string first_name;
	std::string middle_name;
	std::string last_name;

	for (int i = 0; i < fn_line; i++) {
		fn_stream >> first_name;
	}
	for (int i = 0; i < mn_line; i++) {
		mn_stream >> middle_name;
	}
	for (int i = 0; i < ln_line; i++) {
		ln_stream >> last_name;
	}

	return first_name + " " + middle_name + " " + last_name;
}

std::string genGender() {
	return ((std::rand() % 2) ? "male" : "female");
}

Date genDateOfBirth(int min_age, int max_age) {
	static time_t loc_t = std::time(nullptr);
	static int min_year = std::localtime(&loc_t)->tm_year - max_age + 1900;
	static int max_year = std::localtime(&loc_t)->tm_year - min_age + 1900;
	const int min_month = 1;
	const int max_month = 12;
	const int min_day = 1;
	int max_day = 31;

	int r_year = min_year + std::rand() % (max_year - min_year + 1);
	int r_month = min_month + std::rand() % (max_month - min_month + 1);

	if (r_month == 4 || r_month == 6 || r_month == 9 || r_month == 11) {
		max_day = 30;
	}

	if (r_month == 2) {
		// checking for leap year
		if (r_year % 400 == 0 || (r_year % 4 == 0 && r_year % 100 != 0)) {
			max_day = 29;
		} else {
			max_day = 28;
		}
	}

	int r_day = min_day + std::rand() % (max_day - min_day + 1);
	return Date(r_year, r_month, r_day);
}

int countNumberOfLines(std::ifstream& fin) {
	int count = 0;
	std::string s;
	while (!fin.eof()) {
		fin >> s;
		count++;
	}
	fin.seekg(0);
	return count;
}

void randFillArrayOfEmployees(std::vector<Employee>& emps) {
	for (int i = 0; i < emps.size(); i++) {
		std::string gender = genGender();

		std::string fn_file;
		std::string mn_file;
		std::string ln_file;
		if (gender == "male") {
			fn_file = "data\\fn_male.txt";
			mn_file = "data\\mn_male.txt";
		}
		else if (gender == "female") {
			fn_file = "data\\fn_female.txt";
			mn_file = "data\\mn_female.txt";
		}
		ln_file = "data\\surnames.txt";

		std::string full_name = genFullName(fn_file, mn_file, ln_file);
		Date birthday = genDateOfBirth(18, 70);
		Employee e = Employee(full_name, gender, birthday);
		emps[i] = e;
	}
}

std::vector<Employee> selectByFullName(const std::vector<Employee>& emps, const std::string fn) {
	std::vector<Employee> res;
	for (const Employee& e : emps)
	{
		if (e.full_name == fn) {
			res.push_back(e);
		}
	}
	return res;
}

std::vector<Employee> selectByYearOfBirth(const std::vector<Employee>& emps, int year, char op) {
	std::vector<Employee> res;
	for (const Employee& e : emps) {
		switch (op)
		{
		case '>':
			if (e.date_of_birth.year > year) res.push_back(e);
			break;
		case '<':
			if (e.date_of_birth.year < year) res.push_back(e);
			break;
		default:
			return res;
		}
	}
	return res;
}

void printStatisticsByGender(const std::vector<Employee>& emps) {
	int males = 0;
	int females = 0;
	for (const Employee& e : emps) {
		if (e.gender == "male") males++;
		else females++;
	}
	std::cout << "{\n  Males: " << males << ";\n  Females: " << females << ";\n}" << std::endl;
}

void sortByAge(std::vector<Employee>& emps, bool isDesc) {
	std::sort(emps.begin(), emps.end(), [isDesc](const Employee& left, const Employee& right) {
		return (isDesc) ? left.date_of_birth < right.date_of_birth : 
			left.date_of_birth > right.date_of_birth;
	});
}

void printEmployees(std::vector<Employee>& emps) {
	std::cout << "- - -" << std::endl;
	for (Employee& e : emps) {
		std::cout << std::setw(20) << std::left << "Full name:" << e.full_name << std::endl
			<< std::setw(20) << std::left << "Gender:" << e.gender << std::endl
			<< std::setw(20) << std::left << "Date of birth:" << e.date_of_birth.toString() << std::endl
			<< "- - -" << std::endl;
	}
}

void fixInputError(const char* msg) {
	std::cout << "[Error] " << msg << std::endl;
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}