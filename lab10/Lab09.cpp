#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>;
#include <fstream>;
#include <iomanip>;
#include <windows.h>;
#include <conio.h>;
using namespace std;
const int dl = 30;
const char F[] = "text1.txt";
struct park { char number[dl]; char name[dl]; char sename[2]; int numbm; park* next; };
void ds();
void input(park *&nach, park buf);
void output();
void output(park *nach, bool &e);
park* poisk(park *nach, park &buf, char *ss);
void main() {
	setlocale(LC_ALL, "Rus");
	bool e, e0;
	char ss[dl];
	park *park = NULL, *marsh = NULL, buf;
	ifstream fin;
	fin.open(F);
	while (!fin.eof()) {
		fin >> buf.number >> buf.name >> buf.sename[0] >> buf.sename[1] >> buf.numbm;
		if (strlen(buf.number) < 1) { break; };
		input(park, buf);
	};
	fin.close();
	ds(); e = 1;
	while (e) {
		switch (_getch()) {
		case '1':
			e0 = 1;
			output(park, e0);
			if (e0) { cout << "В парке нет автобусов!\n"; };
			break;
		case '2':
			e0 = 1;
			output(marsh, e0);
			if (e0) { cout << "На маршрутах нет автобусов!\n"; };
			break;
		case '3':
			cout << "Введите номер авбуса: "; cin >> ss; OemToCharA(ss, ss);
			if (ss[0] == '0') { cout << "Отмена!\n"; break; };
			park = poisk(park, buf, ss);
			if (ss[0] != '~') { cout << "Номер не найден!\n"; break; };
			input(marsh, buf);
			cout << "Перевод на маршрут выполнен успешно!\n";
			break;
		case '4':
			cout << "Введите номер авбуса: "; cin >> ss; OemToCharA(ss, ss);
			if (ss[0] == '0') { cout << "Отмена!\n"; break; };
			marsh = poisk(marsh, buf, ss);
			if (ss[0] != '~') { cout << "Номер не найден!\n"; break; };
			input(park, buf);
			cout << "Автобус успешно вернулся в парк!\n";
			break;
		case '9':
			system("cls"); ds();
			break;
		case '0':
			e = 0;
			break;
		};
	};
};
void ds() {
	cout << "Клавиши управления:\n"
		<< "'1' - вывод информации об автобусах в парке\n"
		<< "'2' - вывод информации об автобусах на маршруте\n"
		<< "'3' - перевод автобуса на маршрут\n"
		<< "'4' - перевод автобуса в парк\n"
		<< "'9' - меню\n"
		<< "'0' - выход\n";
};
void input(park *&nach, park buf) {
	if (nach == NULL) {
		nach = new park;
		nach->next = NULL;
		strcpy(nach->number, buf.number);
		strcpy(nach->name, buf.name);
		nach->sename[0] = buf.sename[0];
		nach->sename[1] = buf.sename[1];
		nach->numbm = buf.numbm;
	}
	else {
		input(nach->next, buf);
	};
};
void output() {
	cout << left << setw(dl) << "Номер автобуса" << setw(dl + 5) << "Фамилия и инициалы водителя" << setw(dl) << "Номер маршрута" << endl;
};
void output(park *nach, bool &e) {
	if (nach != NULL) {
		if (e) { output(); e = 0; };
		cout << left << setw(dl) << nach->number
			<< setw(dl - 8) << nach->name << nach->sename[0] << ". " << nach->sename[1] << ".       "
			<< right << setw(15) << nach->numbm << endl;
		output(nach->next, e);
	};
};
park* poisk(park *nach, park &buf, char *ss) {
	park *t;
	if (nach == NULL) {
		return nach;
	};
	if (nach != NULL) {
		if (strcmp(ss, nach->number) == 0) {
			ss[0] = '~';
			strcpy(buf.number, nach->number);
			strcpy(buf.name, nach->name);
			buf.sename[0] = nach->sename[0];
			buf.sename[1] = nach->sename[1];
			buf.numbm = nach->numbm;
			t = nach->next;
			delete nach;
			return t;
		};
		nach->next = poisk(nach->next, buf, ss);
	};
	return nach;
};