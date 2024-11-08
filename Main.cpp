//5. Создать класс Decimal для работы с беззнаковыми целыми десятичными числами,
//используя для представления числа массив из 100 элементов типа unsigned char,
//каждый из которых является десятичной цифрой.Младшая цифра имеет меньший
//индекс(единицы – в нулевом элементе массива).Реализовать арифметические
//операции сложения, вычитания, умножения и операции сравнения.
//Граков
#include "Decimal.h"
#include <Windows.h>

using namespace std;

Decimal input_decimal_keyboard();
void print_operations_menu();
void print_input_menu();
int file_input(Decimal& dec1, Decimal& dec2);
int file_output(Decimal& result);

int main() {
	setlocale(LC_ALL, "Russian");
	Decimal a, b, result;
	int choice{ 0 };
	do {
		print_operations_menu();
		while (!(cin >> choice)) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Введите корректный пункт меню!\n";
		};
		switch (choice) {
		case 1: // сложение
			print_input_menu();
			cin >> choice;
			if (choice == 1) {
				a = input_decimal_keyboard();
				b = input_decimal_keyboard();
			}
			else if (choice == 2) {
				if (file_input(a, b) != 0)
					continue;
			}
			result = a + b;
			cout << "a + b = " << result << '\n';
			break;

		case 2: // вычитание
			print_input_menu();
			cin >> choice;
			if (choice == 1) {
				a = input_decimal_keyboard();
				b = input_decimal_keyboard();
			}
			else if (choice == 2) {
				if (file_input(a, b) != 0)
					continue;
			}
			result = a - b;
			cout << "a - b = " << result << '\n';
			break;

		case 3: // умножение
			print_input_menu();
			cin >> choice;
			if (choice == 1) {
				a = input_decimal_keyboard();
				b = input_decimal_keyboard();
			}
			else if (choice == 2) {
				if (file_input(a, b) != 0)
					continue;
			}
			result = a * b;
			cout << "a * b = " << result << '\n';
			break;

		case 4: // деление
			print_input_menu();
			cin >> choice;
			if (choice == 1) {
				a = input_decimal_keyboard();
				b = input_decimal_keyboard();
			}
			else if (choice == 2) {
				if (file_input(a, b) != 0)
					continue;
			}
			if (b[0] != 0 || b.get_size() > 1) {
				result = a / b;
				cout << "a / b = " << result << '\n';
			}
			else {
				cout << "Нельзя делить на ноль\n";
			}
			break;
		case 5: // сравнение
			print_input_menu();
			cin >> choice;
			if (choice == 1) {
				a = input_decimal_keyboard();
				b = input_decimal_keyboard();
			}
			else if (choice == 2) {
				if (file_input(a, b) != 0) {
					continue;
				}
			}
			if (a > b) cout << "a > b \n";
			if (a < b) cout << "a < b \n";
			if (a == b) cout << "a == b \n";
			break;

		case 6: // сохранение результата в файл
			file_output(result);
			break;

		case 7:
			cout << "Выход из программы.\n";
			break;

		default:
			cout << "Неверный пункт меню\n";
			break;
		}

	} while (choice != 7);
}


Decimal input_decimal_keyboard() {
	Decimal result;
	string input;
	bool valid = false;
	while (!valid) {
		cout << "Введите целое число (например, 123 или -123): ";
		cin >> input;
		valid = true;
		size_t start_index = 0;
		if (input[0] == '-') {
			start_index = 1;
		}
		for (size_t i = start_index; i < input.size(); ++i) {
			if (!isdigit(input[i])) {
				valid = false;
				cout << "Ошибка: Введите только цифры." << endl;
				break;
			}
		}
		if (valid) result = input;
	}
	return result;
}

void print_operations_menu() {
	cout << "1. Выполнить сложение\n";
	cout << "2. Выполнить вычитание\n";
	cout << "3. Выполнить умножение\n";
	cout << "4. Выполнить деление\n";
	cout << "5. Сравнение чисел \n";
	cout << "6. Сохранить результат в файл\n";
	cout << "7. Выход\n";
	cout << "Выберите пункт меню: ";
}

void print_input_menu() {
	cout << "1. Ввести данные с клавиатуры\n";
	cout << "2. Ввести данные с файла\n";
	cout << "Выберите пункт меню: ";
}

int file_input(Decimal& dec1, Decimal& dec2) {
	string file_name;
	cout << "Введите имя файла для загрузки: ";
	cin >> file_name;
	ifstream file(file_name);
	if (file.is_open()) {
		string num_str1, num_str2;
		if (!(file >> num_str1 >> num_str2))
		{
			cout << "Некорректные данные в файле\n";
			return -1;
		}
		dec1 = Decimal(num_str1);
		dec2 = Decimal(num_str2);
		file.close();
		cout << "Числа успешно загружены из файла: " << dec1 << " " << dec2 << endl;
	}
	else {
		cout << "Ошибка: не удалось открыть файл " << file_name << endl;
		return -1;
	}
	return 0;
}

int file_output(Decimal& result)
{
	if (result != NULL) {
		string file_name;
		cout << "Введите имя файла для сохранения: ";
		cin >> file_name;
		ofstream file(file_name);
		if (file.is_open()) {
			file << result << "\n";
			cout << "Результат успешно загружен в файл: " << file_name << endl;
			file.close();
		}
		else {
			cout << "Ошибка: не удалось открыть файл " << file_name << endl;
			return -1;
		}
	}
	else {
		cout << "Результат отсутствует\n";
		return -1;
	}
	return 0;
}
