#include "Decimal.h"

Decimal& Decimal::operator=(int value) {
	size = 0;
	if (value < 0)
		is_negative = true;
	value = abs(value);
	do {
		val[size++] = value % 10;
		value /= 10;
	} while (value > 0);
	return *this;
}

Decimal& Decimal::operator=(const std::string& value) {
	size = 0;
	if (value[0] == '-')
		is_negative = true;
	size_t start_index = is_negative ? 1 : 0;
	for (size_t i = value.size(); i-- > start_index;) {
		val[size++] = value[i] - '0';
	}
	return *this;
}

Decimal Decimal::operator+(const Decimal& dec) const {
	Decimal result;
	unsigned carry = 0;
	// Если оба числа имеют одинаковый знак
	if (is_negative == dec.is_negative) {
		result.is_negative = is_negative;
		result.size = std::max(size, dec.size);
		for (unsigned i = 0; i < result.size; ++i) {
			unsigned sum = (i < size ? val[i] : 0) + (i < dec.size ? dec.val[i] : 0) + carry;
			result.val[i] = sum % 10;
			carry = sum / 10;
		}
		if (carry) {
			result.val[result.size++] = carry;
		}
	}
	// Если числа с разными знаками
	else {
		if (is_negative) {
			result = dec - (-(*this));  // -A + B = B - A
		}
		else {
			result = *this - (-dec);  // A + (-B) = A - B
		}
	}
	return result;
}

Decimal Decimal::operator-(const Decimal& dec) const {
	Decimal result;
	unsigned carry{ 0 };
	if (is_negative != dec.is_negative) {
		return *this + (-dec);
	}
	bool this_is_smaller = (*this < dec);
	const Decimal& larger = this_is_smaller ? dec : *this;
	const Decimal& smaller = this_is_smaller ? *this : dec;
	result.size = larger.size;
	for (unsigned i = 0; i < result.size; ++i) {
		int diff = larger.val[i] - (i < smaller.size ? smaller.val[i] : 0) - carry;
		if (diff < 0) {
			diff += 10;
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.val[i] = diff;
	}
	while (result.size > 1 && result.val[result.size - 1] == 0) {
		--result.size;
	}
	if (is_negative && this_is_smaller) result.is_negative = false;
	else result.is_negative = this_is_smaller ? true : false;
	return result;
}

Decimal Decimal::operator*(const Decimal& dec) const {
	Decimal result;
	result.size = size + dec.size;

	for (unsigned i = 0; i < size; ++i) {
		unsigned carry = 0;
		for (unsigned j = 0; j < dec.size || carry; ++j) {
			unsigned temp = result.val[i + j] + val[i] * (j < dec.size ? dec.val[j] : 0)
				+ carry;
			result.val[i + j] = temp % 10;
			carry = temp / 10;
		}
	}
	while (result.size > 1 && result.val[result.size - 1] == 0) {
		--result.size;
	}
	result.is_negative = (is_negative != dec.is_negative);
	return result;
}

Decimal Decimal::operator/(const Decimal& dec) const {
	Decimal result;
	result.size = size;
	Decimal temp;
	//делимое
	Decimal dividend = *this;
	//делитель
	Decimal divisor = dec;
	dividend.is_negative = false;
	divisor.is_negative = false;
	for (int i = size - 1; i >= 0; --i) {
		// Сдвиг temp влево и добавление следующего разряда делимого
		temp = temp * 10 + dividend.val[i];
		// Подсчёт числа раз, которые dec может быть вычтен из temp
		unsigned count = 0;
		while ((temp >= divisor)) {
			temp = temp - divisor;
			++count;
		}
		// Сохранение количества вычитаний в результат
		result.val[i] = count;
	}
	// Удаление незначащих нулей
	while (result.size > 1 && result.val[result.size - 1] == 0) {
		--result.size;
	}
	result.is_negative = (is_negative != dec.is_negative);
	return result;
}

bool Decimal::operator!=(const Decimal& other) const
{
	return is_negative != other.is_negative && size != other.size &&
		std::equal(val, val + size, other.val);;
}

bool Decimal::operator==(const Decimal& other) const {
	return is_negative == other.is_negative && size == other.size &&
		std::equal(val, val + size, other.val);
}

Decimal Decimal::operator-() const
{
	Decimal result = *this;
	result.is_negative = !is_negative;
	return result;
}

std::string Decimal::to_string() const {
	std::string result = is_negative ? "-" : "";
	for (int i = size - 1; i >= 0; --i) {
		result += '0' + val[i];
	}
	return result.empty() ? "0" : result;
}

std::ostream& operator<<(std::ostream& os, const Decimal& digit) {
	os << digit.to_string();
	return os;
}

std::istream& operator>>(std::istream& is, Decimal& digit)
{
	std::string input;
	is >> input;
	digit = input;
	return is;
}
