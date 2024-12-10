#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

const int a_size = 15;

int get_max_length(double array[]) {
	int max_length = 0;
	for (int i = 0; i < a_size; i++) {
		ostringstream oss;
		oss << fixed << setprecision(2) << array[i];
		max_length = max(max_length, static_cast<int>(oss.str().length()));
	}
	return max_length;
}

void table(double arr[], double arg[], int num) {
	int max_length_arr = get_max_length(arr);
	int max_length_arg = get_max_length(arg);
	int column_wide = max(max_length_arr, 1) + 2; 
	int column_wide2 = max(max_length_arg, 1) + 2;
	cout << setw(((column_wide + column_wide2) / 2) + 4) << "Массив#" << num << endl;
	cout << setw(column_wide + column_wide2 + 1) << setfill('=') << "" << setfill(' ') << endl;
	cout << "|" << setw(column_wide - 1) << "F" << "|"
		<< setw(column_wide2 - 1) << "x" << "|" << endl;
	cout << setw(column_wide + column_wide2 + 1) << setfill('=') << "" << setfill(' ') << endl;

	for (int i = 0; i < a_size; i++) {
		cout << "|" << setw(column_wide - 1) << fixed << setprecision(2) << arr[i] << "|" << setw(column_wide2 - 1) << fixed << setprecision(2) << arg[i] << "|" << endl;
	}
	cout << setw(column_wide + column_wide2) << setfill('=') << "" << setfill(' ') << endl;
}

void integrate_arrays(double arr1[], double arr2[], double arg[], double sign_arg[]) {
	for (int i = 0; i < a_size; i++) {
		if (arr1[i] == -0) {
			for (int j = 0; j < a_size; j++) {
				if (arr2[j] != 0) {
					arr1[i] = arr2[j];
					arg[i] = sign_arg[j];
					arr2[j] = 0;
					sign_arg[j] = 0;
					break;
				}
			}
		}
	}
}

void scan_priority(double array[]) {
	for(int i = 0; i < a_size-1; i++) {
		if (array[i] == -0 && array[i + 1] != -0) {
			swap(array[i], array[i + 1]);
		}
	}
}

void search_of_signs(int num, double array[], double sign_array[], double arg[], double sign_arg[]) {
	if (num == 1) { 
		for (int i = 0; i < a_size; i++) {
			if (array[i] > 0) {
				for (int j = 0; j < a_size; j++) {
					if (sign_array[j] == 0) {
						sign_array[j] = array[i];
						sign_arg[j] = arg[i];
						break;
					}
				}
				array[i] = -0;
			}
		}
	}
	if (num == 2) { 
		for (int i = 0; i < a_size; i++) {
			if (array[i] < 0) {
				for (int j = 0; j < a_size; j++) {
					if (sign_array[j] == 0) {
						sign_array[j] = array[i];
						sign_arg[j] = arg[i];
						break;
					}
				}
				array[i] = -0;
				arg[i] = -0;
			}
		}
	}
}

void arr_to_null(double arr[]) {
	for (int i = 0; i < a_size; i++)
		arr[i] = 0;
}

int repeats(double arr[]) {
	int rep = 0;
	for (int i = 0; i < a_size; i++) {
		double c = 0;
		for (int j = i + 1; j < a_size; j++) {
			if (arr[j] == arr[i]) {
				c++;
			}
		}
		if (c == 1)
			rep++;
	}
	return rep;
}

bool power_of_two(double a) {
	if ((int)(log2(a)) == log2(a))
		return true;
	else return false;
}

int powers2_search(double arr[]) {
	int number=0;
	int powers;
	for (int i = a_size-1; i <=0; i--) {
		if (power_of_two(arr[i]) && power_of_two(arr[i - 1])) {
			if (log2(arr[i]) == log2(arr[i - 1]) + 1)
				number++;
		}
		if (i == 13 && number == 0)
			break;
	}
	if (number == 0) powers = -1;
	else powers = 14-number;
	return powers;
}

double F(double x, double a, double b, double c) {
	if (x < 0 && b != 0)
		return a * x * x + b;
	else if (x > 0 && b == 0)
		return (x - a) / (x - c);
	else return x / c;
}

double rounds(double n) {
	if (n == -0)
		n = 0;
	return n;
}

bool condition(int a_c, int b_c, int c_c) {
	if ((a_c | b_c) & (a_c | c_c) == 0)
		return true;
	else return false;
}

void output(double arr[]) {
	for (int i = 0; i < a_size - 1; i++)
		cout << arr[i] << " ";
	cout << arr[a_size - 1] << endl;
}

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "rus");
	bool interface = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0) interface = true;
	double x1, x2, a, b, c, step, x, m_x1, arg1[a_size], arg2[a_size];
	cin >> x1 >> x2 >> a >> b >> c;
	if (x2 > x1) {
		step = (x2 - x1) / 14;
		m_x1 = x1;
	}
	else {
		step = (x1 - x2) / 14;
		m_x1 = x2;
	}
	int a_c, b_c, c_c;
	a_c = (int)a;
	b_c = (int)b;
	c_c = (int)c;
	double arr1[a_size], arr2[a_size];
	if (condition(a_c, b_c, c_c)) {
		for (int i = 0; i < a_size; i++) {
			x = m_x1 + step * i;
			arg1[i] = x;
			arr1[i] = round(F(x, a, b, c));
		}
	}
	else {
		for (int i = 0; i < a_size; i++) {
			x = m_x1 + step * i;
			arg1[i] = x;
			arr1[i] = (round((F(x, a, b, c)*100))/100.0);
		}
	}
	double min_x1, min_x2, m_x2;
	min_x1 = -x1;
	min_x2 = -x2;
	if (min_x1 > min_x2)
		m_x2 = min_x2;
	else
		m_x2 = min_x1;
	if (condition(a_c, b_c, c_c)) {
		for (int i = 0; i < a_size; i++) {
			x = m_x2 + step * i;
			arg2[i] = x;
			arr2[i] = round(F(x, a, b, c));
		}
	}
	else {
		for (int i = 0; i < a_size; i++) {
			x = m_x2 + step * i;
			arg2[i] = x;
			arr2[i] = (round((F(x, a, b, c) * 100)) / 100.0);
		}
	}
	for (int i = 0; i < a_size; i++) {
		arr1[i] = rounds(arr1[i]);
		arr2[i] = rounds(arr2[i]);
	}
	if (interface) {
		table(arr1, arg1, 1);
		table(arr2, arg2, 2);
	}
	else {
		output(arr1);
		output(arr2);
	}
	for (int i = 0; i < (a_size / 5.0); i++) {
		double minimum = arr1[5 * i];
		for (int j = 0; j < 5; j++) {
			if (arr1[5 * i + j] < minimum)
				minimum = arr1[5 * i + j];
		}
		if(interface) cout << "Минимум " << i + 1 << "-й пятерки:" << endl;
			cout << minimum << endl;
	}
	double in_range[a_size], arg_range[a_size];
	for (int i = 0; i < a_size; i++) {
		in_range[i] = arr1[i];
		arg_range[i] = arg1[i];
	}
	bool is_changed = true;
	while (is_changed) {
		is_changed = false;
		for (int i = 0; i < a_size - 1; i++) {
			if (in_range[i] > in_range[i + 1]) {
				swap(in_range[i], in_range[i + 1]);
				swap(arg_range[i], arg_range[i + 1]);
				is_changed = true;
			}
		}
	}
	if (interface) table(in_range, arg_range, 3);
	else output(in_range);
	if (interface) cout << "Количество чисел, встречающихся в массиве более одного раза:" << endl;
	cout << repeats(arr1) << endl;
	if (interface) cout << "Номер элемента, начиная с которого до конца идут степени 2:" << endl;
	cout << powers2_search(arr1) << endl;
	double plus[a_size], minus[a_size], sign_arg1[a_size], sign_arg2[a_size];
	arr_to_null(plus);
	arr_to_null(minus);
	arr_to_null(sign_arg1);
	arr_to_null(sign_arg2);
	search_of_signs(1, arr1, plus, arg1, sign_arg1);
	search_of_signs(2, arr2, minus, arg2, sign_arg2);
	scan_priority(arr1);
	scan_priority(arr2);
	integrate_arrays(arr1, minus, arg1, sign_arg2);
	integrate_arrays(arr2, plus, arg2, sign_arg1);
	if (interface) {
		table(arr1, arg1, 4);
		table(arr2, arg2, 5);
	}
	else {
		output(arr1);
		output(arr2);
	}
}
