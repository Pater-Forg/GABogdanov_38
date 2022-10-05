#pragma once
#include <ctime>

struct Date {
	int year;
	int month;
	int day;

	Date() : year(1), month(1), day(1) {}
	Date(int y, int m, int d) : year(y), month(m), day(d) {}
	
	std::string toString() {
		std::string year_s = std::to_string(year);
		std::string month_s = std::to_string(month);
		std::string day_s = std::to_string(day);
		if (month < 10) month_s.insert(0, "0");
		if (day < 10) day_s.insert(0, "0");
		return day_s + "/" + month_s + "/" + year_s;
	}

	bool operator>(const Date& d) const {
		if (year > d.year) return true;
		if (year != d.year) return false;
		if (month > d.month) return true;
		if (month != d.month) return false;
		return (day > d.month);
	}
	bool operator<(const Date& d) const {
		if (year < d.year) return true;
		if (year != d.year) return false;
		if (month < d.month) return true;
		if (month != d.month) return false;
		return (day < d.month);
	}
	bool operator==(const Date& d) const {
		return (year == d.year && month == d.month && day == d.day);
	}
};