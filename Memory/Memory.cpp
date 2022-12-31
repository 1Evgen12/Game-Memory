#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

using namespace std;

void delete_element(int*& array, int &size, int index) {

	int* newmas = new int[size - 1];

	for (int i = 0; i < index; i++)
	{
		newmas[i] = array[i];
	}

	for (int i = index + 1; i < size + 1; i++)
	{
		newmas[i - 1] = array[i];
	}

	size--;
	delete[] array;
	array = newmas;
}
void show_field(int** field, int size, int **fog) {

	cout << endl<< "     ";
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ' ';
	}
	cout << endl;

	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		cout << "--";
	}
	cout << '-' << endl;


	for (int i = 0; i < size; i++)
	{
		if (i < 9)cout << "  ";
		else cout << ' ';

		cout<< i + 1 << ' ' << '|';

		for (int j = 0; j < size; j++)
		{
			if (fog[i][j] == 1) {
			cout << (char)field[i][j] << ' ';
			}
			else {
				cout << '?' << ' ';
			}
		}
		cout << "\b|" << endl;
	}
	cout << "    ";
	for (int i = 0; i < size; i++)
	{
		cout << "--";
	}
	cout << '-' << endl;

	cout << endl;

}
void total_time(int& hours, int& minuts, int& seconds, int total) {
	hours = total / 3600;
	total %= 3600;
	minuts = total / 60;
	total %= 60;
	seconds = total;
}

int main()
{
	setlocale(LC_ALL, "");
	srand(time(NULL));

	bool play = 1;

	while (play == 1) {

		int symbols_count = 26;
		int* symbols = new int[symbols_count];
		int index;
		int symbols_const[] = { 1,2,3,4,5,6,11,12,14,15,16,17,18,20,21,22, 23, 30,31,36,38,42,43,127,134,164 };

		for (int i = 0; i < symbols_count; i++) {
			symbols[i] = symbols_const[i];
		}

		cout << " ___ПАМЯТЬ___\n\n";
		int n{};
		int count_cards{};
		cout << " Введите размер поля: ";
		cin >> n;

		if (n > 10)
			n = 10;

		if (n <= 1)
			n = 2;
		
		int** field = new int* [n];
		int** fog = new int* [n] ;

		for (int i = 0; i < n; i++)
		{
			field[i] = new int [n] {};
			fog[i] = new int [n] {};
		}

		int pair{};

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (field[i][j] == 0) {

					if (symbols_count == 0) {
						symbols_count = 26;
						symbols = new int[symbols_count];
						for (int i = 0; i < symbols_count; i++) {
							symbols[i] = symbols_const[i];
						}
					}

					index = rand() % symbols_count;
					pair = symbols[index];
					count_cards++;
					field[i][j] = pair;
					int a{}, b{};

					if ( n % 2 == 0 || (n % 2 == 1 && count_cards != n)) {

						do {
							a = rand() % (n - i) + i;
							b = rand() % n;
						} while (field[a][b] != 0);

						count_cards++;
						field[a][b] = pair;
					}
					delete_element(symbols, symbols_count, index);
				}
			}
		}
		system("cls");

		time_t t1{}, t2{};
		t1 = time(NULL);
		int h{}, m{}, s{};
		int x{}, y{};
		int x2{}, y2{};
		int count_flips{};

		while (true) {

			show_field(field, n, fog);

			cout << " Введите координаты двух карт: ";
			if (count_flips < 4) cout << "\n Например 1 1 и 2 1\t";
			while (!(cin >> x && cin >> y ) || x < 1 || x > n || y < 1 || y > n)
			{
				cin.clear();
				cin.ignore();
			}
			x--;
			y--;

			while (!(cin >> x2 && cin >> y2) || x2 < 1 || x2 > n || y2 < 1 || y2 > n || (y2 - 1 == y && x2 - 1 == x)){
				cin.clear();
				cin.ignore();
				}

			x2--;
			y2--;

			if (field[x][y] == field[x2][y2]) {

				if (fog[x][y] == 0 && fog[x2][y] == 0) {
					PlaySound(L"t-r-r-n.wav", NULL, SND_ASYNC);
				}
				fog[x][y] = 1;
				fog[x2][y2] = 1;
				count_cards -= 2;
				system("cls");
			}
			
			else if ((fog[x][y] == 1 && fog[x2][y2] == 0) || (fog[x2][y2] == 1 && fog[x][y] == 0)) {
				PlaySound(L"mistake.wav", NULL, SND_ASYNC);
				system("cls");

			}
			else if(field[x][y] != field[x2][y2]){
				PlaySound(L"no-no.wav", NULL, SND_ASYNC);
				fog[x][y] = 1;
				fog[x2][y2] = 1;
				system("cls");
				show_field(field, n, fog);
				Sleep(2000);
				fog[x][y] = 0;
				fog[x2][y2] = 0;
				PlaySound(L"close.wav", NULL, SND_ASYNC);
				system("cls");
			}

			count_flips ++;

			bool detect_close_card = false;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (fog[i][j] == 0) {
						detect_close_card = true;
						break;
					}
					else if (n % 2 == 1 && count_cards == 1) {
						detect_close_card == false;
						break;
					}
				}
				if (detect_close_card == true) {
					break;
				}
			}

			if (detect_close_card == false) {
				system("cls");

				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < n; j++)
					{
						if (fog[i][j] == 0) {
							fog[i][j] = 1;
							break;
						}
					}
				}
				show_field(field, n, fog);
				cout << " Игра пройдена! \n";

				PlaySound(L"victory.wav", NULL, SND_SYNC);

				t2 = time(NULL);

				total_time(h, m, s, t2 - t1);

				cout << " Время игры ";
				
				if (h < 10) cout << '0';
				cout << h << ':';
				if (m < 10) cout << '0';
				cout << m << ':';
				if (s < 10) cout << '0';
				cout << s << endl;
				cout << " Количество переворотов карт: " << count_flips << endl;
				play = 0;
				break;
			}
		}

		for (int i = 0; i < n; i++)
		{
			delete[] field[i];
			delete[] fog[i];
		}
		delete[] field;
		delete[] fog;

		cout << endl << " Запустить новую игру?\n";
		cout << " 1 - сыграть еще раз\n";
		cout << " 0 - выйти\n";

		while (!(cin >> play)) {
			cin.clear();
			cin.ignore();
		}
		system("cls");
	}
}

