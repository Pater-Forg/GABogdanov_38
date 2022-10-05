#pragma once
#include <string>
#include "Date.h"

struct Employee {
	std::string full_name;
	std::string gender;
	Date date_of_birth;

	Employee() : full_name(""), gender(""), date_of_birth(Date()) {}
	Employee(std::string fn, std::string gen, Date birthday) :
		full_name(fn), gender(gen), date_of_birth(birthday) {}
};