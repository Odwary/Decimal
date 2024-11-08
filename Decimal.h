#pragma once
#include <iostream>
#include <string>
#include <compare>
#include <fstream>

const int MASSIVE_SIZE = 100;

class Decimal {
private:
	unsigned char val[MASSIVE_SIZE] = { 0 };
	unsigned size{ 0 };
	bool is_negative{ false };//

public:
	Decimal(int value = 0) { *this = value; is_negative = false; }
	Decimal(const std::string& value) { *this = value; is_negative = false; }
	Decimal& operator=(int value);
	Decimal& operator=(const std::string& value);
	Decimal operator+(const Decimal& dec) const;
	Decimal operator-(const Decimal& dec) const;
	Decimal operator*(const Decimal& dec) const;
	Decimal operator/(const Decimal& dec) const;
	Decimal operator-() const;
	bool operator!=(const Decimal& other) const;
	bool operator==(const Decimal& other) const; // !=
	std::strong_ordering operator<=>(const Decimal& other) const {
		if (is_negative != other.is_negative) {
			return is_negative ? std::strong_ordering::less : std::strong_ordering::greater;
		}
		if (size != other.size) {
			return is_negative ? (size > other.size) <=> (other.size > other.size) : size <=>
				other.size;
		}
		for (int i = size - 1; i >= 0; --i) {
			if (val[i] != other.val[i]) {
				return is_negative ? (val[i] > other.val[i]) <=>
					(val[i] < other.val[i]) : val[i] <=> other.val[i];
			}
		}
		return std::strong_ordering::equal;
	}

	unsigned operator[](unsigned i) const { return (i < size) ? val[i] : 0; }
	unsigned get_size() const { return size; }
	std::string to_string() const;
	friend std::ostream& operator<<(std::ostream& os, const Decimal& digit);
	friend std::istream& operator>>(std::istream& is, Decimal& digit);
};

