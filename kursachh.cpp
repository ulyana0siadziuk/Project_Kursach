#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <io.h>
#include <stdio.h>
#include <cstring>
#include <windows.h>
using namespace std;

struct PetProduct {

	char NameItem[20];
	char Brand[25];
	char Type[20];
	bool Exist;
	int Cost;

};

void Create(FILE* file);
void View(FILE* file);
void Add(FILE* file);
void ViewByType2(FILE* file);
void Info(PetProduct* Item);
void SimpleSort(FILE* file);
void QuickSortF(FILE* file);
void QuickSort(PetProduct* arr, int left, int right);
void BinarySearchF(FILE* file);
int BinarySearch(PetProduct* Items, char* type, int left, int right);
bool isRussian(char a);

void Menu() {
	bool menu = 1;
	FILE* file = fopen("PetProducts.txt", "r");
	while (file == nullptr)
	{
		
		cout << "1. Создать файл." << endl;
		cout << "2. Выйти из программы" << endl;
		int c;
		while (!(cin >> c) )
		{
			system("cls");
			cout << "Неверный ввод! Повторите попытку.\n";
			cout << "1. Создать файл." << endl;
			cout << "2. Выйти из программы" << endl;

			cin.clear();
			cin.ignore(10000, '\n');
		}
		system("cls");
		switch (c)
		{
		case 1:
			file = fopen("PetProducts.txt", "w");
			break;
		case 2: return;
		default: cout << "Неверный ввод! Повторите попытку.\n";
		}
	}
	if (file != nullptr)
	{
		fclose(file);
	}
	while (menu != 0)
	{
		cout << "1. Пересоздать файл (очистка)." << endl;
		cout << "2. Просмотреть список товаров." << endl;
		cout << "3. Добавить товар." << endl;
		cout << "4. Линейный поиск товаров по виду питомца." << endl;
		cout << "5. Сортировка товаров (прямой выбор)." << endl;
		cout << "6. Сортировка товаров (QuickSort)." << endl;
		cout << "7. Двоичный поиск товаров по виду питомца." << endl;
		cout << "0. Выйти из программы." << endl;
		int choice;
		while (!(cin >> choice)) {
			system("cls");
			cout << "Такого варианта нет. Введите ещё раз.\n";
			cout << "1. Пересоздать файл (очистка)." << endl;
			cout << "2. Просмотреть список товаров." << endl;
			cout << "3. Добавить товар." << endl;
			cout << "4. Линейный поиск товаров по виду питомца." << endl;
			cout << "5. Сортировка товаров (прямой выбор)." << endl;
			cout << "6. Сортировка товаров (QuickSort)." << endl;
			cout << "7. Двоичный поиск товаров по виду питомца." << endl;
			cout << "0. Выйти из программы." << endl;

			cin.clear();
			cin.ignore(10000, '\n');
		}
		system("cls");

		switch (choice)
		{
		case 1: Create(file); break;
		case 2: View(file); break;
		case 3: Add(file); break;
		case 4: /*ViewByType(file);*/ ViewByType2(file); break;
		case 5: SimpleSort(file); break;
		case 6: QuickSortF(file); break;
		case 7: BinarySearchF(file); break; 
		case 0: menu = 0; cout << "Вы вышли из программы."<<endl; break;
		default: cout << "Такого варианта нет. Введите ещё раз.\n"; break;
		}
	}
}

void BinarySearchF(FILE* file)
{
	file = fopen("PetProducts.txt", "r+");
	QuickSortF(file);
	system("cls");
	int kol = 0;
	PetProduct Item;
	while (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5)
	{
		kol++;
	}
	rewind(file);//указатель в начало файла
	PetProduct* Items = new PetProduct[kol];

	for (int i = 0; i < kol; i++) 
	{
		fscanf(file, "%s %s %s %d %d\n", Items[i].Type, Items[i].NameItem, Items[i].Brand, &Items[i].Exist, &Items[i].Cost);
	}
	fclose(file);
	char type[20];
	cout << "Введите вид питомца: ";
	cin >> type;
	int foundIndex = BinarySearch(Items, type, 0, kol - 1);

	if (foundIndex != -1)
	{
		int startIndex = foundIndex;
		int endIndex = foundIndex;
		while (startIndex > 0 && strcmp(Items[startIndex - 1].Type, type) == 0)
		{
			startIndex--;
		}
		while (endIndex < kol - 1 && strcmp(Items[endIndex + 1].Type, type) == 0)
		{
			endIndex++;
		}
		for (int i = startIndex; i <= endIndex; i++)
		{
			if (strcmp(Items[i].Type, type) != 0)
			{
				break;
			}
			Info(&Items[i]);
		}
	}
	else
	{
		cout << "Вид питомца не найден.\n\n";
	}

	delete[] Items;
}

int BinarySearch(PetProduct* Items, char* type, int left, int right)
{
	if (left <= right)
	{ 
		int mid = (left + right) / 2;
		PetProduct item = Items[mid];

		if (strcmp(item.Type, type) == 0)
		{
			return mid;
		}
		else if (strcmp(item.Type, type) < 0)
		{
			return BinarySearch(Items, type, mid + 1, right);
		}
		else
		{
			return BinarySearch(Items, type, left, mid - 1);
		}
	}
	return -1;
}

void QuickSort(PetProduct* arr, int left, int right)
{
	int i = left, j = right;
	char p[20];
	strcpy(p, arr[(left + right) / 2].Type);

	while (i <= j)
	{
		while (strcmp(arr[i].Type, p) < 0)
			i++;
		while (strcmp(arr[j].Type, p) > 0)
			j--;
		if (i <= j)
		{
			PetProduct temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}

	if (left < j)
		QuickSort(arr, left, j);
	if (i < right)
		QuickSort(arr, i, right);
}


void QuickSortF(FILE* file)
{
	file = fopen("PetProducts.txt", "r+");
	if (file == nullptr)
	{
		cout << "Ошибка открытия файла." << endl;
		return;
	}
	PetProduct Item;
	int kolvo = 0;
	while (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5)
	{
		kolvo++;
	}
	PetProduct* Items = new PetProduct[kolvo];
	rewind(file);
	for (int i = 0; i < kolvo; i++)
	{
		fscanf(file, "%s %s %s %d %d\n", Items[i].Type, Items[i].NameItem, Items[i].Brand, &Items[i].Exist, &Items[i].Cost);
	}
	fclose(file);

	QuickSort(Items, 0, kolvo - 1);

	file = fopen("PetProducts.txt", "w");
	for (int i = 0; i < kolvo; i++)
	{
		fprintf(file, "%s %s %s %d %d\n", Items[i].Type, Items[i].NameItem, Items[i].Brand, Items[i].Exist, Items[i].Cost);
	}
	delete[] Items;
	fclose(file);
	cout << "Сортировка товаров (QuickSort) выполнена." << endl;
}

void  SimpleSort(FILE* file) {
	file = fopen("PetProducts.txt", "r+");
	if (file == nullptr)
	{
		cout << "Ошибка открытия файла." << endl;
		return;
	}
	PetProduct Item;
	int kolvo = 0;
	while (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5)
	{
		kolvo++;
	}
	PetProduct* Items = new PetProduct[kolvo];
	rewind(file);
	for (int i = 0; i < kolvo; i++)
	{
		fscanf(file, "%s %s %s %d %d\n", Items[i].Type, Items[i].NameItem, Items[i].Brand, &Items[i].Exist, &Items[i].Cost);
	}
	for (int i = 0; i < kolvo - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < kolvo; ++j)
		{
			if (strcmp(Items[j].Type, Items[minIndex].Type) < 0)
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			PetProduct temp = Items[i];
			Items[i] = Items[minIndex];
			Items[minIndex] = temp;
		}
	}
	freopen("PetProducts.txt", "w", file);
	for (int i = 0; i < kolvo; i++)
	{
		fprintf(file, "%s %s %s %d %d\n", Items[i].Type, Items[i].NameItem, Items[i].Brand, Items[i].Exist, Items[i].Cost);
	}
	delete[] Items;
	fclose(file);
	cout << "Сортировка по виду питомца выполнена." << endl;
}

void ViewByType2(FILE* file)
{
	file = fopen("PetProducts.txt", "r");
	char pet[20];

	PetProduct Item;
	char kind[20];
	cout << "Поиск по виду питомца\n";
	cout << "Введите вид питомца: ";
	cin >> kind;
	sprintf(pet, "%s.txt", kind);
	FILE* file2 = fopen(pet, "w");
	while (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5)
	{
		if (strcmp(kind, Item.Type) == 0)
		{
			Info(&Item);
			fprintf(file2, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, Item.Exist, Item.Cost);
		}
	}
	fclose(file2);
	fclose(file);
}

void Create(FILE* file)
{
	file = fopen("PetProducts.txt", "w");
	fclose(file);
	cout << "Файл был пересоздан.\n";
}

bool isRussian(char a) {
	return (a >= 'а' && a <= 'я') || (a >= 'А' && a <= 'Я');
}

void Add(FILE* file)
{
	file = fopen("PetProducts.txt", "a");
	PetProduct Item;

	do {
		cout << "Введите вид питомца: ";
		cin >> Item.Type;

		// Проверка на буквы
		bool valid = true;
		for (int i = 0; Item.Type[i] != '\0'; ++i) {
			if (!isalpha(Item.Type[i]) && !isRussian(Item.Type[i])) {
				valid = false;
				cout << "Ошибка: введите только буквы для вида питомца." << endl;
				break;
			}
		}
		if (valid) break; 

	} while (true); 

	cout << "Введите наименование товара: ";
	cin >> Item.NameItem;
	cout << "Введите бренд товара: ";
	cin >> Item.Brand;
	cout << "Введите наличие товара(1 - есть в наличие; 0 - отсутсвует): ";
	while (!(cin >> Item.Exist) || (Item.Exist < 0 || Item.Exist > 1))
	{
		cout << "Неверный ввод!\nВведите наличие товара(1 - есть в наличие; 0 - отсутсвует):";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	cout << "Введите стоимость товара: ";
	while (!(cin >> Item.Cost))
	{
		cout << "Неверный ввод!\nВведите стоимость товара:";
		cin.clear();
		cin.ignore(10000, '\n');
	}

	fprintf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, Item.Exist, Item.Cost);
	fclose(file);
}

void Info(PetProduct* Item)
{
	cout << "Вид питомца: " << Item->Type;
	cout << "\nНаименование товара: " << Item->NameItem;
	cout << "\nБренд товара: " << Item->Brand;
	if (Item->Exist == true)
	{
		cout << "\nНаличие: имеется";
	}
	else
	{
		cout << "\nНаличие: отсутствует";
	}
	cout << "\nСтоимость товара: " << Item->Cost << endl << endl;
}

void View(FILE* file)
{
	file = fopen("PetProducts.txt", "r");
	PetProduct Item;
	bool isEmpty = true;

	if (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5) {
		isEmpty = false;
		Info(&Item);

		while (fscanf(file, "%s %s %s %d %d\n", Item.Type, Item.NameItem, Item.Brand, &Item.Exist, &Item.Cost) == 5)
		{
			Info(&Item);
		}
	}

	if (isEmpty) {
		cout << "Список товаров пуст. Добавьте товары.\n";
	}

	fclose(file);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	system("color F"); 
	SetConsoleTitle(L"Структура списка товаров для животных в зоомагазине"); 
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	return 0;
}