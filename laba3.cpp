﻿#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int repeats(double arr[], int size) {
	int rep = 0;
	for (int i = 0; i < size; i++) {
		int c = 0;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] == arr[i]) {
				c++;
			}
		}
		if (c == 1)
			rep++;
	}
	return rep;
}

double rounds(double n) {
	n = round(n);
	if (n == -0)
		n = 0;
	return n;
}

double F(double x, double a, double b, double c) {
	if (x < 0 && b != 0)
		return a * x * x + b;
	else if (x > 0 && b == 0) {
		return(x - a) / (x - c);
	}
	else
		return x / c;
}

void table(double arr[], double arg[], int n) {
	cout << "Массив #" << n << endl;
	cout << "__________________________" << endl;
	cout << "|     F      | |     x   |" << endl;
	cout << "__________________________" << endl;
	for (int i = 0; i < 15; i++) {
		cout << "| " << setw(10) << arr[i] << " | " << setw(10) << arg[i] << " |" << endl;
	}
	cout << "__________________________" << endl;
}

void array_to_disp(double array[], int size) {
	for (int i = 0; i < size; i++) {
		if (i != size - 1)
			cout << array[i] << " ";
		else
			cout << array[i] << endl;
	}
	return;
}

bool power_of_two(double a) {
	if ((int)log2(a) == log2(a))
		return true;
	else
		return false;
}

int main(int argc, char* argv[]) {
	bool interface = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
		interface = true;
	setlocale(LC_CTYPE, "rus");
	const int size = 15;
	double x1, x2, x, a, b, c;
	if (interface)
		cout << "Последовательно введите значения x1, x2, a, b, c в соответсвующем порядке." << endl;
	cin >> x1 >> x2 >> a >> b >> c;
	double step;
	step = (x2 - x1) / (double)(size - 1);
	double arr1[size], arr2[size], arg1[size], arg2[size];
	for (int i = 0; i < size; i++) {
		if (x1 > x2)
			x = x2 + i * step;
		else
			x = x1 + i * step;
		arg1[i] = x;
		arr1[i] = F(x, a, b, c);
		int a_c = a;
		int b_c = b;
		int c_c = c;
		double min_x1, min_x2, min_x, step2;
		min_x1 = -x1;
		min_x2 = -x2;
		if (min_x1 > min_x2) {
			step2 = (min_x1 - min_x2) / (double)(size - 1);
			min_x = min_x2 + i * step2;
		}
		else {
			step2 = (min_x2 - min_x1) / (double)(size - 1);
			min_x = min_x1 + i * step2;
		}
		arg2[i] = min_x;
		arr2[i] = F(min_x, a, b, c);
		if (((a_c | b_c) & (a_c | b_c)) == 0) {
			arr1[i] = rounds(arr1[i]);
			arr2[i] = rounds(arr2[i]);
		}
		else {
			arr1[i] = rounds((arr1[i]) * 100) / 100.0;
			arr2[i] = rounds((arr2[i]) * 100) / 100.0;
		}
	}
	if (interface) {
		table(arr1, arg1, 1);
		table(arr2, arg2, 2);
	}
	else {
		array_to_disp(arr1, size);
		array_to_disp(arr2, size);
	}
	for (int i = 0; i < (size / 5.0); i++) {
		double min = arr1[5 * i];
		for (int j = 0; j < 5; j++) {
			if (arr1[5 * i + j] < min)
				min = arr1[5 * i + j];
		}
		if (interface)
			cout << "Минимум " << i + 1 << "-й пятерки равен " << min << endl;
		else
			cout << min << endl;
	}
	double in_range[size];
	for (int i = 0; i < size; i++)
		in_range[i] = arr1[i];
	bool is_changed = true;
	while (is_changed) {
		is_changed = false;
		for (int i = 0; i < size - 1; i++) {
			if (in_range[i] > in_range[i + 1]) {
				swap(in_range[i], in_range[i + 1]);
				swap(arg1[i], arg1[i + 1]);
				is_changed = true;
			}
		}
	}
	if (interface)
		table(in_range, arg1, 3);
	else
		array_to_disp(in_range, size);
	int repeat = repeats(arr1, size);
	if (interface)
		cout << "Количество повторяющихся чисел: ";
	cout << repeat << endl;
	int num_of_powers = 0;
	for (int i = size; i <= 0; i--) {
		if (power_of_two(arr1[i]) && power_of_two(arr1[i - 1])) {
			if ((int)log2(arr1[i]) == log2(arr1[i - 1]) + 1)
				num_of_powers++;
		}
		else break;

	}
	if (interface)
		cout << "Номер элемента, начиная с которого степени 2: ";
	if (num_of_powers != 0)
		cout << size - num_of_powers << endl;
	else
		cout << -1 << endl;
	double plus_arr[2 * size], min_arr[2 * size];
	int num_pl = 0, num_min = 0;
	for (int i = 0; i < size; i++) {
		if (arr1[i] < 0) {
			min_arr[num_min] = arr1[i];
			num_min++;
		}
	}
	for (int i = 0; i < size; i++) {
		if (arr2[i] < 0) {
			min_arr[num_min] = arr2[i];
			num_min++;
		}
	}
	for (int i = 0; i < size; i++) {
		if (arr2[i] > 0) {
			plus_arr[num_pl] = arr2[i];
			num_pl++;
		}
	}
	for (int i = 0; i < size; i++) {
		if (arr1[i] > 0) {
			plus_arr[num_pl] = arr1[i];
			num_pl++;
		}
	}
	for (int i = num_min; i < 2 * size; i++) {
		min_arr[i] = 0;
	}

	for (int i = num_pl; i < 2 * size; i++) {
		plus_arr[i] = 0;
	}

	if (num_min <= size) 
		array_to_disp(min_arr, size);
	if(num_min>size)
		array_to_disp(min_arr, num_min);
	if(num_pl<=size)
		array_to_disp(plus_arr, size);
	if (num_pl > size)
		array_to_disp(plus_arr, num_pl);
}
