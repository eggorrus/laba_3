#include <iostream>
#include <cmath>

using namespace std;

double F(double x, double a, double b, double c) {
	if (x < 0 && b != 0)
		return a * x * x + b;
	else if (x > 0 && b == 0) {
		return (x - a) / (x - c);
	}
	else
		return x / c;
}

void vivod(double array[]) {
	for (int i = 0; i < 15; i++) {
		if (i != 14)
			cout << array[i] << " ";
		else
			cout << array[i] << endl;
	}
	return;
}

bool proverka(int array[], int ne_null) {
	int da = 0;
	for (int i = 1; i < sizeof(array); i++) {
		if (array[i] == array[i + 1]-1)
			da += 1;
	}
	if (da == ne_null)
		return true;
	else
		return false;
}

void table(double array[], int n) {
	cout << "            Массив #" << n <<"            "<< endl;
	cout << "________________________________________________________________________________" << endl;
	for (int i = 0; i < 15; i++) {
		cout << "|" << array[i];
		if (i == 14)
			cout << "|" << endl;
	}
	cout << "________________________________________________________________________________" << endl;
}

int main(int argc, char* argv[])
{
	bool interface = false;
	if (argc <= 1 || strcmp(argv[1], "false") != 0)
		interface = true;
	setlocale(LC_CTYPE, "rus");
	if(interface)
		cout << "Последовательно введите значения x1, x2, a, b, c в соответсвующем порядке." << endl;
	double x1, x2, a, b, c;
	cin >> x1 >> x2 >> a >> b >> c;
	double massiv1[15], massiv2[15];
	double step = (x2 - x1) / 14.0;
	for (int i = 0; i < 15; i++) {
		double x = x1 + i * step;
		massiv1[i] = F(x, a, b, c);
		int a_c = a;
		int b_c = b;
		int c_c = c;
		if (((a_c | b_c) & (a_c | b_c)) == 0)
			massiv1[i] = round(massiv1[i]);
		else
			massiv1[i] = round((massiv1[i]) * 100) / 100;
		double obrx1, obrx2;
		obrx1 = -x1;
		obrx2 = -x2;
		double step2 = (obrx1 - obrx2) / 14.0;
		x = obrx2 + step2 * i;
		massiv2[i] = F(x, a, b, c);
		if (((a_c | b_c) & (a_c | b_c)) == 0)
			massiv2[i] = round(massiv2[i]);
		else
			massiv2[i] = round((massiv2[i]) * 100) / 100;
	}
	if (interface) {
		table(massiv1, 1);
		table(massiv2, 2);
	}
	else {
		vivod(massiv1);
		vivod(massiv2);
	}
	for (int i = 0; i < 3; i++) {
		double min = massiv1[5 * i];
		for (int j = 0; j < 5; j++) {
			if (massiv1[5 * i + j] < min)
				min = massiv1[5 * i + j];
		}
		if (interface)
			cout << "Минимум " << i+1 << " пятерки: ";
		cout << min << endl;
	}
	double obr_massiv1[15];
	for (int i = 0; i < 15; i++) {
		obr_massiv1[i] = massiv1[i];
	}
	bool is_changed = true;
	while (is_changed) {
		is_changed = false;
		for (int j = 0; j < 14; j++) {
			if (obr_massiv1[j] > obr_massiv1[j + 1]) {
				swap(obr_massiv1[j], obr_massiv1[j + 1]);
				is_changed = true;
			}
		}
	}
	if (interface)
		table(obr_massiv1, 3);
	vivod(obr_massiv1);
	int povt = 0;
	for (int j = 0; j < 14; j++) {
		if (massiv1[j] == massiv1[j + 1])
			povt = povt + 1;
	}
	if (interface)
		cout << "Количество чисел всетрчающихся более одного раза: ";
	cout << povt << endl;
	int chisla[15];
	for (int j = 0; j < 15; j++)
		chisla[j] = 0;
	bool stepen = false;
	for (int i = 0; i < 15; i++) {
		if (floor(log2(massiv1[i]) == log2(massiv1[i]))) {
			stepen = true;
			for (int k = 0; k < 15; k++) {
				if (chisla[k] == 0) {
					chisla[k] = i;
					break;
				}
			}
		}
		else {
			stepen = false;
		}
	}
	int ne_null = 0;
	for (int h = 0; h < 15; h++) {
		if (chisla[h] != 0)
			ne_null += 1;
	}
	bool stepen2 = proverka(chisla, ne_null);
	if (interface)
		cout << "Номер элемента начиная с которого степени 2:";
	if (stepen2)
		cout << ne_null << endl;
	else
		cout << -1 << endl;

	double g[15], d[15];
	for (int i = 0; i < 15; i++)
	{
		g[i] = 0;
		d[i] = 0;
	}
	for (int i = 0; i < 15; i++) {
		if (massiv1[i] > 0) {
			for (int c = 0; c < 15; c++) {
				if (g[c] == 0) {
					g[c] = massiv1[i];
					break;
				}
				else continue;
			}
			massiv1[i] = 0;
		}
		if (massiv2[i] < 0) {
			for (int s = 0; s < 15; s++) {
				if (d[s] == 0) {
					d[s] = massiv2[i];
					break;
				}
				else continue;
			}
			massiv2[i] = 0;
		}
	}
	for (int i = 0; i < 15; i++) {
		if (massiv1[i] == 0) {
			for (int a = 0; a < 15; a++) {
				if (d[a] != 0) {
					massiv1[i] = d[a];
					d[a] = 0;
					break;
				}
				else continue;
			}
		}
	}
	for (int i = 0; i < 15; i++) {
		if (massiv2[i] == 0) {
			for (int a = 0; a < 15; a++) {
				if (g[a] != 0) {
					massiv2[i] = g[a];
					g[a] = 0;
					break;
				}
				else continue;
			}
		}
	}
	if (interface) {
		table(massiv1, 4);
		table(massiv2, 5);
	}
	else {
		vivod(massiv1);
		vivod(massiv2);
	}
}