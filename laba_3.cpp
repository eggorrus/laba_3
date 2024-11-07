#include <iostream>
#include <cmath>
#include <iomanip>

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

bool stepen2(double n) {
	if (floor(log2(n)) == log2(n))
		return true;
	else
		return false;
}

/*bool poryadok(int chisla[], int ne_null) {
	int tr = 0;
	for (int i = 0; i < 14; i++) {
		if (chisla[i]==chisla[i+1]-1) {
			tr += 1;
		}
	}
	if (tr == ne_null)
		return true;
	else
		return false;
}*/

void table(double array1[], double iksy[], int n) {
	cout << "Массив #" << n << endl;
	cout << "__________________________" << endl;
	cout << "|     F      | |     x   |" << endl;
	cout << "__________________________" << endl;
	for (int i=0; i<15; i++){
		cout << "| " << setw(10) << array1[i] << " | " << setw(10) << iksy[i] << " |" << endl;
	}
	cout << "__________________________" << endl;
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
	double iksy[15], iksy2[15];
	for (int i = 0; i < 15; i++) {
		double x = x1 + i * step;
		iksy[i] = x;
		massiv1[i] = F(x, a, b, c);
		int a_c = a;
		int b_c = b;
		int c_c = c;
		if (((a_c | b_c) & (a_c | b_c)) == 0)
			massiv1[i] = round(massiv1[i]);
		else
			massiv1[i] = round((massiv1[i]) * 100) / 100;
		double obrx1, obrx2, obrx;
		obrx1 = -x1;
		obrx2 = -x2;
		double step2 = (obrx1 - obrx2) / 14.0;
		obrx = obrx2 + step2 * i;
		iksy2[i] = obrx;
		massiv2[i] = F(obrx, a, b, c);
		if (((a_c | b_c) & (a_c | b_c)) == 0)
			massiv2[i] = round(massiv2[i]);
		else
			massiv2[i] = round((massiv2[i]) * 100) / 100;
	}
	if (interface) {
		table(massiv1, iksy, 1);
		table(massiv2, iksy2, 2);
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
				swap(iksy[j], iksy[j + 1]);
				is_changed = true;
			}
		}
	}
	if (interface)
		table(obr_massiv1,iksy, 3);
	else
		vivod(obr_massiv1);
	int povt = 0;
	for (int j = 0; j < 14; j++) {
		if (massiv1[j] == massiv1[j + 1])
			povt = povt + 1;
	}
	if (interface)
		cout << "Количество чисел всетрчающихся более одного раза: ";
	cout << povt << endl;
	int numOfPowers=0;
	for (int i = 14; i >= 0; i--) {
			if (stepen2(massiv1[i]))
				numOfPowers ++;
			else break;
	}
	if (numOfPowers != 0) {
		if (interface)
			cout << "Номер элемента, начиная с которого степени 2:" << 14 - numOfPowers << endl;
		else
			cout << 14 - numOfPowers << endl;
	}
	else {
		if (interface)
			cout << "Номер элемента, начиная с которого степени 2:" << -1 << endl;
		else
			cout << -1 << endl;
	}
	double g[15], d[15], plus_x[15], minus_x[15];
	for (int i = 0; i < 15; i++)
	{
		g[i] = 0;
		d[i] = 0;
		plus_x[i] = 0;
		minus_x[i] = 0;
	}
	for (int i = 0; i < 15; i++) {
		if (massiv1[i] > 0) {
			for (int c = 0; c < 15; c++) {
				if (g[c] == 0) {
					g[c] = massiv1[i];
					minus_x[c] = iksy[i];
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
					plus_x[s] = iksy2[i];
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
		table(massiv1, plus_x, 4);
		table(massiv2, minus_x, 5);
	}
	else {
		vivod(massiv1);
		vivod(massiv2);
	}
}