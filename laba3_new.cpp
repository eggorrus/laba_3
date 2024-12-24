#include <iostream>
#include <string>
#include <iomanip>

const int a_size = 15;
double arr1[a_size], arr2[a_size], arg1[a_size], arg2[a_size], a, b, c, xmax, xmin, minims[a_size/5];

using namespace std;

double F(double x) {
	int a_c = floor(a);
	int b_c = floor(b);
	int c_c = floor(c);
	if ((a_c | b_c) & (a_c | c_c)==0) {
		if (x < 0 && b != 0)
			return lround(a * x * x + b);
		else if (x > 0 && b == 0)
			return lround((x - a) / (x - c));
		else
			return lround(x / c);
	}
	else {
		if (x < 0 && b != 0)
			return (round((a * x * x + b) * 100)) / 100.0;
		else if (x > 0 && b == 0)
			return (round(((x - a) / (x - c)) * 100)) / 100.0;
		else
			return (round((x / c) * 100)) / 100.0;
	}
}

void min_max_search(double x1, double x2) {
	if (x1 > x2) {
		xmax = x1;
		xmin = x2;
	}
	else {
		xmin = x1;
		xmax = x2;
	}
}

void fill_arrays(double x1, double x2) {
	double rev_x1 = -x1;
	double rev_x2 = -x2;
	double x;
	min_max_search(x1, x2);
	double step = (xmax - xmin) / (a_size - 1);
	for (int i = 0; i < a_size; i++) {
		x = xmin + i * step;
		arg1[i] = x;
		arr1[i] = F(x);
	}
	min_max_search(rev_x1, rev_x2);
	for (int i = 0; i < a_size; i++) {
		x = xmin + i * step;
		arg2[i] = x;
		arr2[i] = F(x);
	}
}

void output_arrays(int command) {
	switch (command) {
	case 1: {
		for (int i = 0; i < a_size - 1; i++)
			cout << arr1[i] << " ";
		cout << arr1[a_size - 1] << endl;;
		break;
	}
	case 2:
	{
		for (int i = 0; i < a_size - 1; i++)
			cout << arr2[i] << " ";
		cout << arr2[a_size - 1] << endl;;
		break;
	}
	}
}

double min_search(int num) {
	double min = arr1[5 * (num - 1)];
	for (int i = 5 * (num - 1); i < 5 * num; i++) {
		if (min > arr1[i])
			min = arr1[i];
	}
	return min;
}

void sort_arr() {
	bool is_changed;
	for (int i = 0; i < a_size - 1; i++) {
		is_changed = false;  
		for (int j = 0; j < a_size - 1 - i; j++) {
			if (arr1[j] > arr1[j + 1]) {
				swap(arr1[j], arr1[j + 1]);  
				swap(arg1[j], arg1[j + 1]);
				is_changed = true;  
			}
		}
		if (!is_changed) {
			break;  
		}
	}
}

int repeat_search() {
	int repeat = 0;
	for (int i = 0; i < a_size; i++) {
		bool is_repeated = false;
		for (int j = 0; j < i; j++) {
			if (arr1[i] == arr1[j]) {
				is_repeated = true; 
				break;
			}
		}
		if (!is_repeated) { 
			int count = 1; 
			for (int j = i + 1; j < a_size; j++) {
				if (arr1[i] == arr1[j]) {
					count++; 
				}
			}
			if (count > 1) { 
				repeat++; 
			}
		}
	}
	return repeat; 
}

int power_2_search() {
	int num_of_pow=-1;
	for (int i = a_size - 1; i >= 0; i--) {
		if (floor(log2(arr1[i])) == log2(arr1[i])) {
			if (log2(arr1[i]) == log2(arr1[i - 1]) + 1)
				num_of_pow++;
			else break;
		}
	}
	if (num_of_pow == -1)
		return num_of_pow;
	else return (a_size-1)-(num_of_pow + 2);
}

int plus_search() {
	int plus_q = 0;
	for (int i = 0; i < a_size; i++) {
		if (arr1[i] > 0) plus_q++;
	}
	return plus_q;
}

int minus_search() {
	int minus_q = 0;
	for (int i = 0; i < a_size; i++) {
		if (arr2[i] < 0) minus_q++;
	}
	return minus_q;
}

void arr_to_null(double arr[], int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

void sort_arrays() {
	int non_zero_index = 0;
	for (int i = 0; i < a_size; i++) {
		if (arr1[i] != 0) {
			arr1[non_zero_index] = arr1[i];
			non_zero_index++;
		}
	}
	non_zero_index = 0;
	for (int i = 0; i < a_size; i++) {
		if (arr2[i] != 0) {
			arr2[non_zero_index] = arr2[i];
			non_zero_index++;
		}
	}
}

void distribution() {
	double plus_q = plus_search();
	double minus_q = minus_search();
	double* tr_arr1 = new double[plus_q];
	double* tr_arg1 = new double[plus_q];
	arr_to_null(tr_arr1, plus_q);
	arr_to_null(tr_arg1, plus_q);
	double* tr_arr2 = new double[minus_q];
	double* tr_arg2 = new double[minus_q];
	arr_to_null(tr_arr2, minus_q);
	arr_to_null(tr_arg2, minus_q);
	for (int i = 0; i < a_size; i++) {
		if (arr1[i] > 0) {
			for (int j = 0; j < plus_q; j++) {
				if (tr_arr1[j] == 0) {
					tr_arr1[j] = arr1[i];
					tr_arg1[j] = arg1[i];
					arr1[i] = 0;
					arg1[i] = 0;
					break;
				}

			}
		}
		if (arr2[i] < 0) {
			for (int j = 0; j < minus_q; j++) {
				if (tr_arr2[j] == 0) {
					tr_arr2[j] = arr2[i];
					tr_arg2[j] = arg2[i];
					arr2[i] = 0;
					arg2[i] = 0;
					break;
				}
			}
		}
	}
	sort_arrays();
	for (int i = 0; i < a_size; i++) {
		if (arr1[i] == 0) {
			for (int j = 0; j < minus_q; j++) {
				if (tr_arr2[j] != 0) {
					arr1[i] = tr_arr2[j];
					arg1[i] = tr_arg2[j];
					tr_arr2[j] = 0;
					tr_arg2[j] = 0;
					break;
				}
			}
		}
		if (arr2[i] == 0) {
			for (int j = 0; j < plus_q; j++) {
				if (tr_arr1[j] != 0) {
					arr2[i] = tr_arr1[j];
					arg2[i] = tr_arg1[j];
					tr_arr1[j] = 0;
					tr_arg1[j] = 0;
					break;
				}
			}
		}
	}
	delete[] tr_arr1;
	delete[] tr_arr2;
	delete[] tr_arg1;
	delete[] tr_arg2;
}

int get_max_length(double arr[]) {
	int length = 2;
	int max=0;
	for (int i = 0; i < a_size; i++) {
		if ((floor(arr[i])/10 + 2) > max) {
			if (arr[i] < 0) max = size(to_string((int)arr[i])) + 2;
			else max = size(to_string((int)arr[i]))+2;
		}
	}
	return (length + max);
}

void table(double arr[], double arg[], int num) {
	int max_length_arr = get_max_length(arr);
	int max_length_arg = get_max_length(arg);
	int column_wide = max(max_length_arr, 1) + 2;
	int column_wide2 = max(max_length_arg, 1) + 2;
	cout << setw(((column_wide + column_wide2) / 2) + 4) << "Массив#" << num << endl;
	cout << setw(column_wide + column_wide2 + 3) << setfill('=') << "" << setfill(' ') << endl;
	cout << "|" << setw(column_wide-1) << "F" << "|"
		<< setw(column_wide2+1) << "x" << "|" << endl;
	cout << setw(column_wide + column_wide2 + 3) << setfill('=') << "" << setfill(' ') << endl;

	for (int i = 0; i < a_size; i++) {
		cout << "|" << setw(column_wide) << fixed << setprecision(2) << arr[i] << "|" << setw(column_wide2) << arg[i] << "|" << endl;
	}
	cout << setw(column_wide + column_wide2 + 3) << setfill('=') << "" << setfill(' ') << endl;
}

int main(int argc, char* argv[]) {
	setlocale(LC_CTYPE, "rus");
	bool is_human = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0) is_human = true;
	double x1, x2;
	if (is_human) cout << "Введите значения x1, x2, a, b, c:" << endl;
	cin >> x1 >> x2 >> a >> b >> c;
	fill_arrays(x1, x2);
	if (is_human) {
		table(arr1, arg1, 1);
		table(arr2, arg2, 2);
	}
	else {
		output_arrays(1);
		output_arrays(2);
	}
	for (int i = 0; i < (a_size / 5); i++) {
		minims[i] = min_search(i + 1);
	}
	if (is_human) {
		for (int i = 0; i < a_size / 5; i++)
			cout << "Минимум " << i + 1 << "-й пятерки:" << minims[i] << endl;;
	}
	else {
		for (int i = 0; i < (a_size / 5) - 1; i++)
			cout << minims[i] << " ";
		cout << minims[(a_size / 5) - 1] << endl;
	}
	sort_arr();
	if (is_human) table(arr1, arg1, 3);
	else output_arrays(1);
	cout << repeat_search() << endl;
	cout << power_2_search() << endl;
	distribution();
	if (is_human) {
		table(arr1, arg1, 4);
		table(arr2, arg2, 5);
	}
	else {
		output_arrays(1);
		output_arrays(2);
	}
}