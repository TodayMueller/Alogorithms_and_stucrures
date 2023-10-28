#include <iostream>
#include <string>
#include <Windows.h>
#include <cctype>
#include <vector>

using namespace std;

struct READER
{
	string key;
	string name;
	int birth_year;
	string address;
	string work;
};

struct BOOK
{
	string cipher;
	string authors;
	string name;
	string publish;
	int year;
	int total_cop;
	int stok_cop;
	struct BOOK* left;
	struct BOOK* right;
	int h = 1;
};

struct Reg
{
	string key;
	string cipher;
	string out_data;
	string in_data;
	//struct Reg* next;
};

struct List
{
	List* next;
	Reg reg;
};

int HashFunc(string key) {
	int hash = 0;
	hash += (key[0] == 'А' ? 0 : key[0] == 'В' ? 1 : 2) * 100;
	hash += key[1] + key[2] + key[3] + key[4] + key[5] + key[6] - 288;
	return hash * 19;
}

string CodeCheck() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	string code = "";
	string inp = "";
	int num0, num1, num2, num3, num4, num5, num6;
	while (1)
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << "Введие номер читательского билета: ";
		do {
			code += inp;
			inp = cin.get();
		} while (inp != "\n");
		if (code.length() == 7)
		{
			num0 = code[0];
			num1 = code[1];
			num2 = code[2];
			num3 = code[3];
			num4 = code[4];
			num5 = code[5];
			num6 = code[6];
			if (num0 == -64 || num0 == -62 || num0 == -41) {
				if ((num1 > 47) && (num1 < 58) && (num2 > 47) && (num2 < 58) && (num3 > 47) && (num3 < 58) && (num4 > 47) && (num4 < 58) && (num5 > 47) && (num5 < 58) && (num6 > 47) && (num6 < 58)) {
					break;
				}
			}
		}
		cout << "Неверный формат номера! Повторите ввод!\n";
		inp = "";
		code = "";
	}
	return code;
}

string TextCheck() {
	setlocale(LC_ALL, "Russian");
	string inp = "";
	string text = "";
	bool er;
	while (1) {
		er = 0;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		do {
			text += inp;
			inp = cin.get();
		} while (inp != "\n");
		for (int i = 0; i < text.length(); i++) {
			if (!(text[i] == 32 || text[i] == 34 || text[i] < 0 || (text[i] > 43 && text[i] < 58))) {
				er = 1;
			}
		}
		if (er == 0) break;
		else {
			text = "";
			inp = "";
			cout << "Данные указаны некорректно! Повторите ввод." << endl;
		}
	}
	return text;
}

int NumCheck() {
	string inp = "";
	string num = "";
	bool er;
	while (1) {
		er = 0;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		do {
			num += inp;
			inp = cin.get();
		} while (inp != "\n");
		for (int i = 0; i < num.length(); i++) {
			if (!(num[i] > 47 && num[i] < 58)) {
				er = 1;
			}
		}
		if (er == 0) break;
		else {
			num = "";
			inp = "";
			cout << "Данные указаны некорректно! Повторите ввод." << endl;
		}
	}
	return stoi(num);
}

string CipherCheck() {
	string inp = "";
	string cipher = "";
	bool er;
	while (1) {
		er = 0;
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		do {
			cipher += inp;
			inp = cin.get();
		} while (inp != "\n");
		if (cipher.length() == 6) {
			for (int i = 0; i < 6; i++) {
				if (!(cipher[i] > 47 && cipher[i] < 58)) {
					er = 1;
				}
			}
			if (er == 0) break;
		}
		cipher = "";
		inp = "";
		cout << "Данные указаны некорректно! Повторите ввод." << endl;
	}
	return cipher;
}

List* DeleteListVar(List*& Start, List*& End, string inp_cipher, string inp_code) {
	List* current = Start;
	string data;
	string origin;
	if (current == NULL) {
		return 0;
	}
	if (inp_cipher == "0") data = inp_code;
	else data = inp_cipher;
	do {
		if (inp_cipher == "0") origin = current->reg.key;
		else origin = current->reg.cipher;
		if (origin == data) {
			if (Start == End) {
				Start = NULL;
				End = NULL;
			}
			if (current == Start) {
				Start = current->next;
			}
			List* delme = current;
			while (1) {
				if (current->next == delme) {
					if (delme == End) {
						End = current;
						End->next = Start;
					}
					current->next = current->next->next;
					delme->next = NULL;
					break;
				}
				current = current->next;
			}
		}
		current = current->next;
	} while (current != Start);
	return 0;
}

bool ReaderExist(READER* Mass, string code) {
	int iter = 1;
	int HashCode = HashFunc(code);
	if (Mass[HashCode].key == code)
	{
		return 1;
	}
	else
		while (1)
		{
			HashCode += iter * iter++;
			if ((HashCode > 5000) || (Mass[HashCode].key.size() == 0))
			{
				return 0;
			}
			if (Mass[HashCode].key == code)
			{
				return 1;
			}
		}

}

void InputReader(READER* Mass, int* UsedNum)
{
	string code = CodeCheck();
	if (!ReaderExist(Mass, code)) {
		int HashCode = HashFunc(code);
		int iter = 1;
		cout << "Заполните данные о читателе" << endl;
		cout << "Имя: ";
		string name = TextCheck();
		cout << "Год рождения: ";
		int year = NumCheck();
		cout << "Адрес: ";
		string addres = TextCheck();
		cout << "Место работы: ";
		string work = TextCheck();
		if ((Mass[HashCode].key.size() == 0) || (Mass[HashCode].key == "deleted"))
		{
			cout << "Сохранено в ячейку " << HashCode << '\n';
			Mass[HashCode].key = code;
			Mass[HashCode].name = name;
			Mass[HashCode].birth_year = year;
			Mass[HashCode].address = addres;
			Mass[HashCode].work = work;
			for (int i = 0; i < 5000; i++)
			{
				if ((UsedNum[i] == -2) || (UsedNum[i] == -1))
				{
					UsedNum[i] = HashCode;
					break;
				}
			}
		}
		else
			while (Mass[HashCode].key.size() != 0)
			{
				HashCode += iter * iter++;
				if (HashCode > 5000)
				{
					cout << "Нет подходящих ячеек для сохранения нового элемента с таким ключём!\n";
					break;
				}
				if ((Mass[HashCode].key.size() == 0) || (Mass[HashCode].key == "deleted"))
				{
					cout << "Сохранено" << '\n';
					Mass[HashCode].key = code;
					Mass[HashCode].name = name;
					Mass[HashCode].birth_year = year;
					Mass[HashCode].address = addres;
					Mass[HashCode].work = work;
					for (int i = 0; i < 5001; i++)
					{
						if ((UsedNum[i] == -2) || (UsedNum[i] == -1))
						{
							UsedNum[i] = HashCode;
							break;
						}
					}
					break;
				}
			}
	}
	else {
		cout << "Читатель с таким номером уже зарегестрирован! " << endl;
	}
}

void ReaderDelete(READER* Mass, int* UsedNum, List* Start, List* End)
{
	int iter = 1;
	string code = CodeCheck();
	int HashCode = HashFunc(code);
	if (Mass[HashCode].key == code)
	{
		cout << "Данные о читателе" << endl;
		cout << "\n" "Номер билета: " << Mass[HashCode].key << '\n' << "Имя: " << Mass[HashCode].name << '\n' << "Год рождения: " << Mass[HashCode].birth_year << '\n' << "Адрес: " << Mass[HashCode].address <<
			'\n' << "Место работы: " << Mass[HashCode].work << '\n' << "Выберете действие:\n1 - Удалить элемент\n0 - Выход\n";
		{
			int flag;
			cin >> flag;
			if (flag == 1)
			{
				Mass[HashCode].key = "deleted";
				for (int i = 0; i < 5000; i++)
				{
					if (UsedNum[i] == -2)
						break;
					else if (UsedNum[i] == HashCode)
					{
						UsedNum[i] = -1;
						break;
					}
				}
			}
		}
	}
	else
		while (1)
		{
			HashCode += iter * iter++;
			if ((HashCode > 5000) || (Mass[HashCode].key.size() == 0))
			{
				cout << "В таблице нет такого элемента!\n";
				break;
			}
			if (Mass[HashCode].key == code)
			{
				cout << "\nВ ячейке " << HashCode << " хранится: " << Mass[HashCode].key << '\n' << "Выберете действие : \n1 - Удалить элемент\n0 - Выход\n";
				int flag;
				cin >> flag;
				if (flag == 1)
				{
					Mass[HashCode].key = "deleted";
					for (int i = 0; i < 5000; i++)
					{
						if (UsedNum[i] == -2)
							break;
						else
							if (UsedNum[i] == HashCode)
							{
								UsedNum[i] = -1;
								break;
							}
					}
				}
				break;
			}
		}
	DeleteListVar(Start, End, "0", code);
}

void ClearReaders(READER* Mass, int* UsedNum) {
	int Num = 0;
	for (int i = 0; i < 5001; i++)
	{
		if (UsedNum[i] != -2)
		{
			if (UsedNum[i] != -1)
			{
				Num++;
				Mass[UsedNum[i]].key = "deleted";
				UsedNum[i] = -1;

			}
		}
		else {
			cout << "Данные о читателях очищены" << endl;
			break;
		}
	}
	if (Num == 0)
		cout << "Таблица пуста\n";
}

void PrintReader(READER* Mass, int* UsedNum)
{
	int Num = 0;
	for (int i = 0; i < 5001; i++)
	{
		if (UsedNum[i] != -2)
		{
			if (UsedNum[i] != -1)
			{
				Num++;
				cout << "Данные о читателях" << endl;
				cout << "\n" "Номер билета: " << Mass[UsedNum[i]].key << '\n' << "Имя: " << Mass[UsedNum[i]].name << '\n' << "Год рождения: " << Mass[UsedNum[i]].birth_year << '\n' << "Адрес: " << Mass[UsedNum[i]].address <<
					'\n' << "Место работы: " << Mass[UsedNum[i]].work << '\n' << "Номер в хеш таблице: " << UsedNum[i] << '\n';

			}
		}
		else
			break;

	}
	if (Num == 0)
		cout << "Таблица пуста\n";
}

void ReaderFindKey(READER* Mass, int* UsedNum, List* Start) {
	int Num = 0;
	string key = CodeCheck();
	for (int i = 0; i < 5001; i++)
	{
		if (UsedNum[i] != -2)
		{
			if (UsedNum[i] != -1)
			{
				if (Mass[UsedNum[i]].key == key) {
					Num++;
					cout << "Данные о читателе" << endl;
					cout << "Имя: " << Mass[UsedNum[i]].name << '\n' << "Год рождения: " << Mass[UsedNum[i]].birth_year << '\n' << "Адрес: " << Mass[UsedNum[i]].address << '\n' << "Место работы: " << Mass[UsedNum[i]].work << '\n'
						<< "Шифры выданных книг: ";
					if (Start != NULL) {
						List* current = Start;
						do {
							if (current->reg.key == key) {
								cout << current->reg.cipher << " ";
							}
							current = current->next;
						} while (current != Start);
					}
					cout << '\n' << "Номер в хеш таблице: " << UsedNum[i] << '\n';
				}
			}
		}
		else
			break;
	}
	if (Num == 0) {
		cout << "Читатель с таким номером билета не найден.\n";
	}
}

void ReaderFindFio(READER* Mass, int* UsedNum) {
	int Num = 0;
	cout << "Введите фио:" << endl;
	string fio = TextCheck();
	for (int i = 0; i < 5001; i++)
	{
		if (UsedNum[i] != -2)
		{
			if (UsedNum[i] != -1)
			{
				if (Mass[UsedNum[i]].name == fio) {
					Num++;
					cout << "\n" "Номер билета: " << Mass[UsedNum[i]].key << '\n' << "Имя: " << Mass[UsedNum[i]].name << '\n';
				}
			}
		}
		else
			break;
	}
	if (Num == 0)
		cout << "Читатель с таким именем не найден.\n";
}

int height(BOOK* R) {
	if (R != NULL) return R->h;
	else return 0;
}

int height_dif(BOOK* R) {
	return height(R->right) - height(R->left);
}

void tree_height(BOOK* R) {
	int hl = height(R->left);
	int hr = height(R->right);
	if (hl > hr) R->h = hl + 1;
	else R->h = hr + 1;
}

BOOK* rotate_r(BOOK* p) {
	BOOK* q = p->left;
	p->left = q->right;
	q->right = p;
	tree_height(p);
	tree_height(q);
	return q;
}

BOOK* rotate_l(BOOK* q) {
	BOOK* p = q->right;
	q->right = p->left;
	p->left = q;
	tree_height(q);
	tree_height(p);
	return p;
}

BOOK* balance(BOOK* R) {
	tree_height(R);
	if (height_dif(R) == 2) {
		if (height_dif(R->right) < 0)
			R->right = rotate_r(R->right);
		return rotate_l(R);
	}
	if (height_dif(R) == -2) {
		if (height_dif(R->left) > 0)
			R->left = rotate_l(R->left);
		return rotate_r(R);
	}
	return R;
}

BOOK* BookSearch(BOOK*& R, int cipher, int k) {
	if (cipher == stoi(R->cipher)) {
		switch (k)
		{
		case 0:
			return R;
		case 1:
		{
			if (R->stok_cop > 0) {
				R->stok_cop -= 1;
				return R;
			}
			else {
				cout << "Данной книги нет в наличии" << endl;
				return NULL;
			}
		}
		case 2:
		{
			R->stok_cop += 1;
			return R;
		}
		default:
			break;
		}
		return R;
	}
	if (cipher < stoi(R->cipher)) {
		if (R->left == NULL) {
			BOOK* R = new BOOK();
			return NULL;
		}
		BookSearch(R->left, cipher, k);
	}
	else {
		if (R->right == NULL) {
			BOOK* R = new BOOK();
			return NULL;
		}
		BookSearch(R->right, cipher, k);
	}
}

BOOK* tree_min(BOOK* R) {
	if (R->left == NULL) return R;
	else tree_min(R->left);
}

BOOK* remmin(BOOK* R) {
	if (R->left == NULL) return R->right;
	R->left = remmin(R->left);
	return balance(R);
}

BOOK* BookDelete(BOOK* R, int cipher) {
	if (R == NULL) return 0;
	if (cipher < stoi(R->cipher))
		R->left = BookDelete(R->left, cipher);
	else if (cipher > stoi(R->cipher))
		R->right = BookDelete(R->right, cipher);
	else {
		BOOK* l = R->left;
		BOOK* r = R->right;
		delete R;
		if (r == NULL) return l;
		BOOK* min = tree_min(r);
		min->right = remmin(r);
		min->left = l;
		return balance(min);
	}
	return balance(R);
}

void badCharHeuristic(string str, int size, vector<int>& badChar) {
	for (int i = 0; i < 256; i++) {
		badChar[i] = -1;
	}
	for (int i = 0; i < size; i++) {
		badChar[64 + (int)str[i]] = i;
	}
}

bool bm_search(string text, string pattern) {
	bool res = 0;
	int textSize = text.size();
	int patternSize = pattern.size();

	vector<int> badChar(256, 0);
	badCharHeuristic(pattern, patternSize, badChar);

	int shift = 0;
	while (shift <= (textSize - patternSize)) {
		int j = patternSize - 1;
		while (j >= 0 && pattern[j] == text[shift + j]) {
			j--;
		}
		if (j < 0) {
			res = 1;
			shift += (shift + patternSize < textSize) ? patternSize - badChar[64 + text[shift + patternSize]] : 1;
		}
		else {
			shift += max(1, j - badChar[64 + text[shift + j]]);
		}
	}
	return res;
}

BOOK* ClearBook(BOOK* R) {
	if (R == NULL) return 0;
	while (R != NULL) {
		R = BookDelete(R, stoi(R->cipher));
	}
}

BOOK* push(BOOK*& R, int cipher) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	if (R == NULL) {
		BOOK* root = new BOOK;
		root->cipher = to_string(cipher);
		cout << "Автор: ";
		root->authors = TextCheck();
		cout << "Название: ";
		root->name = TextCheck();
		cout << "Издательство: ";
		root->publish = TextCheck();
		cout << "Год издания: ";
		root->year = NumCheck();
		cout << "Количество экземпляров всего: ";
		root->total_cop = NumCheck();
		cout << "Количество экземпляров на складе: ";
		root->stok_cop = NumCheck();
		root->right = NULL;
		root->left = NULL;
		R = root;
		return R;
	}
	if (cipher < stoi(R->cipher)) push(R->left, cipher);
	else push(R->right, cipher);
	R = balance(R);
}

void PrintBook(BOOK* R, string cipher_inp, int mode) {
	setlocale(LC_ALL, "Russian");
	if (R == NULL) return;
	PrintBook(R->left, cipher_inp, mode);
	switch (mode)
	{
	case(0):
	{
		cout << "Шифр: ";
		cout << R->cipher << endl;
		cout << "Автор: ";
		cout << R->authors << endl;
		cout << "Название: ";
		cout << R->name << endl;
		cout << "Издательство: ";
		cout << R->publish << endl;
		cout << "Год издания: ";
		cout << R->year << endl;
		cout << "Количество экземпляров всего: ";
		cout << R->total_cop << endl;
		cout << "Количество экземпляров на складе: ";
		cout << R->stok_cop << endl << endl;
	}
	case(1):
	{
		if (R->cipher == cipher_inp) {
			cout << "Шифр: ";
			cout << R->cipher << endl;
			cout << "Автор: ";
			cout << R->authors << endl;
			cout << "Название: ";
			cout << R->name << endl;
			cout << "Издательство: ";
			cout << R->publish << endl;
			cout << "Год издания: ";
			cout << R->year << endl;
			cout << "Количество экземпляров всего: ";
			cout << R->total_cop << endl;
			cout << "Количество экземпляров на складе: ";
			cout << R->stok_cop << endl << endl;
		}
	}
	}
	PrintBook(R->right, cipher_inp, mode);
}

void BookFindCipher(List* Start, BOOK* root, READER* Mass, int* UsedNum) {
	int Num = 0;
	string key;
	cout << "Введите шифр книги: ";
	string cipher = CipherCheck();
	if (BookSearch(root, stoi(cipher), 0) != 0) {
		PrintBook(root, cipher, 1);
	}
	if (Start != NULL) {
		List* current = Start;
		do {
			if (current->reg.cipher == cipher) {
				key = current->reg.key;
				for (int i = 0; i < 5001; i++)
				{
					if (UsedNum[i] != -2)
					{
						if (UsedNum[i] != -1)
						{
							if (Mass[UsedNum[i]].key == key) {
								cout << "Книга была выдана:" << endl;
								cout << "Имя: " << Mass[UsedNum[i]].name << '\n' << "Номер билета: " << Mass[UsedNum[i]].key << endl << endl;
								break;
							}
						}
					}
					else
						break;
				}
			}
			current = current->next;
		} while (current != Start);
	}
}

void BookFindFio(BOOK* R, string inp) {
	if (R == NULL) return;
	BookFindFio(R->left, inp);
	if (bm_search(R->authors, inp) || bm_search(R->name, inp)) {
		cout << "Шифр: ";
		cout << R->cipher << endl;
		cout << "Автор: ";
		cout << R->authors << endl;
		cout << "Название: ";
		cout << R->name << endl;
		cout << "Издательство: ";
		cout << R->publish << endl;
		cout << "Год издания: ";
		cout << R->year << endl;
		cout << "Количество экземпляров всего: ";
		cout << R->total_cop << endl;
		cout << "Количество экземпляров на складе: ";
		cout << R->stok_cop << endl << endl;
	}
	BookFindFio(R->right, inp);
}

List* ListSort(List*& Start, List*& End) {
	if (Start == NULL) {
		return 0;
	}
	bool swapped = true;
	while (swapped) {
		swapped = false;
		List* current = Start;
		do {
			if (stoi(current->reg.cipher) > stoi(current->next->reg.cipher)) {
				swap(current->reg, current->next->reg);
				swapped = true;
			}
			current = current->next;
		} while (current != End);
		if (!swapped) {
			break;
		}
		List* tail = current;
		current = End;
		do {
			if (stoi(current->reg.cipher) < stoi(current->next->reg.cipher)) {
				swap(current->reg, current->next->reg);
				swapped = true;
			}
			current = current->next;
		} while (current != Start);
		Start = current;
	}
}

List* DeleteList(List*& Start, List*& End, BOOK*& root) {
	List* current = Start;
	if (current == NULL) {
		cout << "Список пуст." << endl;
		return 0;
	}
	string inp_key = CodeCheck();
	cout << "Введите шифр: ";
	string inp_cipher = CipherCheck();
	do {
		if ((current->reg.cipher == inp_cipher) && (current->reg.key == inp_key)) {
			if (Start == End) {
				Start = NULL;
				End = NULL;
				BookSearch(root, stoi(inp_cipher), 2);
				cout << "Успешно" << endl;
				return 0;
			}
			if (current == Start) {
				Start = current->next;
			}
			List* delme = current;
			while (1) {
				if (current->next == delme) {
					if (delme == End) {
						End = current;
						End->next = Start;
					}
					current->next = current->next->next;
					delme->next = NULL;
					ListSort(Start, End);
					BookSearch(root, stoi(inp_cipher), 2);
					cout << " Успешно! " << endl;
					return 0;
				}
				current = current->next;
			}
		}
		current = current->next;
	} while (current != Start);
	cout << "Элемент не найден." << endl;
	return 0;
}

void AddList(Reg reg, List*& Start, List*& End, BOOK*& root, READER* Mass) {
	string key, cipher, out_data, in_data;
	cout << "Введите дату выдачи книги: " << endl;
	out_data = TextCheck();
	cout << "Введите дату сдачи книги: " << endl;
	in_data = TextCheck();
	while (1)
	{
		cout << "Введите шифр книги: " << endl;
		cipher = CipherCheck();
		key = CodeCheck();
		if ((ReaderExist(Mass, key) == 1) && (BookSearch(root, stoi(cipher), 1) != NULL)) {
			break;
		}
		else
			cout << "Данные указаны некорректно!" << endl;
	}
	reg.cipher = cipher;
	reg.key = key;
	reg.in_data = in_data;
	reg.out_data = out_data;
	List* NewElem = new List;
	NewElem->reg = reg;
	if (Start == NULL) {
		Start = End = NewElem;
	}
	else {
		End->next = NewElem;
		End = NewElem;
	}
	NewElem->next = Start;
	ListSort(Start, End);
	cout << " " << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int x = -1;
	string tab = "-----";
	for (int i = 0; i < 4; i++)
	{
		tab += tab;
	}
	int UsedNum[5000];
	READER Massive[5000];
	BOOK* root = NULL;
	List* Start = NULL;
	List* End = NULL;
	Reg reg;
	for (int i = 0; i < 5000; i++)
	{
		UsedNum[i] = -2;
	}
	while (x != 0)
	{
		cout << tab << '\n' << "Выберете действие:\n1  - Добавить читателя\n2  - Удалить читателя\n3  - Вывести список читателей\n4  - Очистить данные о читателях\n5  - Найти читателя по номеру читательского билета\n"
			<< "6  - Найти читателя по ФИО\n7  - Добавить книгу\n8  - Удалить книгу\n9  - Вывести список книг\n10 - Очистка данных о книгах\n11 - Найти книгу по автору или названию\n12 - Найти книгу по шифру\n13 - Выдача книги читателю\n"
			<< "14 - Приём книги от читателя\n0 - Выход\n" << tab << endl;
		try {
			cin >> x;
			if (cin.fail()) throw exception("Ошибка входных данных!");
		}
		catch (exception& ex) {
			while (cin.fail()) {
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail());
				cout << ex.what() << "\nПовторите ввод: ";
				cin >> x;
			}
		}
		cout << endl;
		switch (x)
		{
		case 1:
		{
			InputReader(Massive, UsedNum);
			break;
		}
		case 2:
		{
			ReaderDelete(Massive, UsedNum, Start, End);
			break;
		}
		case 3:
		{
			PrintReader(Massive, UsedNum);
			break;
		}
		case 4:
		{
			ClearReaders(Massive, UsedNum);
			break;
		}
		case 5:
		{
			ReaderFindKey(Massive, UsedNum, Start);
			break;
		}
		case 6:
		{
			ReaderFindFio(Massive, UsedNum);
			break;
		}
		case 7:
		{
			cout << "Заполните информацию о книге:" << endl;
			cout << "Шифр: ";
			string cipher = CipherCheck();
			if (root != NULL) {
				if (BookSearch(root, stoi(cipher), 0) != NULL) cout << "Этот шифр уже занят!\n";
				else root = push(root, stoi(cipher));
			}
			else root = push(root, stoi(cipher));
			break;
		}
		case 8:
		{
			cout << "Введите шифр книги, которую необходимо удалить" << endl;
			string cipher = CipherCheck();
			root = BookDelete(root, stoi(cipher));
			DeleteListVar(Start, End, cipher, "0");
			break;
		}
		case 9:
		{
			PrintBook(root, "", 0);
			break;
		}
		case 10:
		{
			root = ClearBook(root);
			break;
		}
		case 11:
		{
			cout << "Введите строку для поиска: ";
			string inp = TextCheck();
			BookFindFio(root, inp);
			break;
		}
		case 12:
		{
			BookFindCipher(Start, root, Massive, UsedNum);
			break;
		}
		case 13:
		{
			AddList(reg, Start, End, root, Massive);
			break;
		}
		case 14:
		{
			DeleteList(Start, End, root);
			break;
		}
		default:
			cout << "Данные указаны некорректно! Повторите ввод." << endl;
		}
	}
}