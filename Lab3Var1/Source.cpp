#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include "Employee.h"

/*
 * Generate full name from random parts
 * 
 * @param fn_file name of file with first names
 * @param mn_file name of file with middle names
 * @param ln_file name of file with last names
 * @return string with full name
 */
std::string genFullName(std::string fn_file, std::string mn_file, std::string ln_file);
/*
 * Generate gender (male/female)
 * 
 * @return string with gender
 */
std::string genGender();
/*
 * Generate random date from given range of age
 * 
 * @param min_age minimal age of employee
 * @param max_age maximal age of employee
 * @return date of birth struct
 */
Date genDateOfBirth(int min_age, int max_age);
/*
 * Count number of lines in file
 * 
 * @param filename name of file
 * @return number of lines or -1 if file doesn't exist
 */
int countNumberOfLines(std::string filename);
/*
 * Randomly fill vector of employees
 * 
 * @emps array to fill
 */
void randFillArrayOfEmployees(std::vector<Employee>& emps);
/*
 * Find all employees with given full name
 * 
 * @param emps array with employees
 * @param fn full name
 * @return array with found employees
 */
std::vector<Employee> selectByFullName(const std::vector<Employee>& emps, const std::string fn);
/*
 * Generates a slice of employees from an array by year of birth (more or less)
 * 
 * @param emps array with employees
 * @param year year to form slice
 * @param op more or less
 */
std::vector<Employee> selectByYearOfBirth(const std::vector<Employee>& emps, int year, char op);
/*
 * Print statistics by gender
 * 
 * @param emps array with employees
 */
void printStatisticsByGender(const std::vector<Employee>& emps);
/*
 * Sort array of employees by age
 * 
 * @param emps array with employees
 * @param is_desc is sort descending
 */
void sortByAge(std::vector<Employee>& emps, bool is_desc);
/*
 * Print info about employees
 * 
 * @param emps array with employees
 */
void printEmployees(std::vector<Employee>& emps);

/*
 * Print message, clear stdin and ignore INT_MAX characters or till new line
 *
 * @param msg message to print
 */
void fixInputError(const char* msg);

/*
 * Reads operation from user and calls the corresponding function
 * 
 * @param emps array with employees
 */
void controller(std::vector<Employee>& emps);

/*
 * Print full names of employees to stdout
 */
void printNames(const std::vector<Employee>& emps);

/*
 * Reads line from file of given number
 * 
 * @param filename name of file
 * @param n number of line
 * @return line
 */
std::string readLine(std::string filename, int n);

/*
 You need to write a program that:
 The "Employee" structure will be implemented with the following fields:
  * Full name
  * Gender
  * Year of Birth (Date Structure)
 An array has been created that stores N workers, the number is read from the keyboard.
 N workers filled or generated.
 Functions are written that:
  * Conducts a search in the array of employees and finds an employee by full name.
  * Generates a slice of employees from an array by year of birth (more or less).
  * Displays employee statistics by gender.
  * Sorts an array of employees by age (all date components are taken into account).
 */
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
	printNames(emps);
	controller(emps);
	
	return 0;
}

std::string genFullName(std::string fn_file, std::string mn_file, std::string ln_file) {
	static int fn_count = countNumberOfLines(fn_file);
	static int mn_count = countNumberOfLines(mn_file);
	static int ln_count = countNumberOfLines(ln_file);

	int fn_line = std::rand() % (fn_count + 1);
	int mn_line = std::rand() % (mn_count + 1);
	int ln_line = std::rand() % (ln_count + 1);

	if (fn_line == -1 || mn_line == -1 || ln_line == -1)
		return "";

	std::string first_name = readLine(fn_file, fn_line);
	std::string middle_name = readLine(mn_file, mn_line);
	std::string last_name = readLine(ln_file, ln_line);

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
		max_day = 28;
	}

	int r_day = min_day + std::rand() % (max_day - min_day + 1);
	return Date(r_year, r_month, r_day);
}

int countNumberOfLines(std::string filename) {
	std::ifstream fin(filename);
	if (!fin) return -1;
	int count = 0;
	std::string s;
	while (!fin.eof()) {
		fin >> s;
		count++;
	}
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

void sortByAge(std::vector<Employee>& emps, bool is_desc) {
	std::sort(emps.begin(), emps.end(), [is_desc](const Employee& left, const Employee& right) {
		return (is_desc) ? left.date_of_birth < right.date_of_birth : 
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

void controller(std::vector<Employee>& emps) {
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
			std::cout << "Selection:\n" << std::endl;
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
			std::cout << "Selection:" << std::endl;
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
}

void printNames(const std::vector<Employee>& emps) {
	for (int i = 0; i < emps.size(); i++) {
		std::cout << i + 1 << ". " << emps[i].full_name << std::endl;
	}
}

std::string readLine(std::string filename, int n) {
	std::ifstream fin(filename);
	if (!fin || fin.peek() == EOF) return "";
	std::string res;
	for (int i = 0; i < n && !fin.eof(); i++) {
		fin >> res;
	}
	if (fin.eof()) res = "";
	return res;
}