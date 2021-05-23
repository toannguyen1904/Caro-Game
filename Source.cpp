#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<fstream>
#include"General.h"
#include"Game.h"
using namespace std;
void FixConsoleWindow(int x, int y)
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, r.left, r.top, x, y, TRUE);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)& ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void Color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void GoToXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Caro()
{
	GoToXY(0, 3);
	cout << "               ********************                               **                                *****        *****************               ******************" << endl;
	cout << "             *******************                                ******                              *****      *********************           **********************" << endl;
	cout << "           *****                                              **********                            *****    *****               *****       *****                *****" << endl;
	cout << "         *****                                              *****    *****                          *****  *****                           *****                    *****" << endl;
	cout << "       *****                                              *****        *****                        **********                             *****                    *****" << endl;
	cout << "     *****                                              *****            *****                      ********                               *****                    *****" << endl;
	cout << "   *****                                              *****                *****                    *****                                  *****                    *****" << endl;
	cout << "  *****                                             ******************************                  *****                                  *****                    *****" << endl;
	cout << "   *****                                          **********************************                *****                                  *****                    *****" << endl;
	cout << "     *****                                      *****                            *****              *****                                  *****                    *****" << endl;
	cout << "       *****                                  *****                                *****            *****                                  *****                    *****" << endl;
	cout << "         *****                              *****                                    *****          *****                                  *****                    *****" << endl;
	cout << "           *****                          *****                                        *****        *****                                    *****                *****" << endl;
	cout << "             ******************         *****                                            *****      *****                                      **********************" << endl;
	cout << "               *******************    *****                                                *****    *****                                        ******************" << endl;
}
void ResetData(int a[][200], int n)
{
	int i, j;
	for (i = 0; i < 2 * n;)
	{
		for (j = 0; j < 4 * n;)
		{
			a[i][j] = 0;
			j = j + 4;
		}
		i = i + 2;
	}
}
void DrawBoard(int a[][200], int n, string s1, string s2, int d1, int d2, int i)
{
	int x, y;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			GoToXY(y, x);
			if (a[x][y] == 0) cout << ".";
			else if (a[x][y] == 1)
			{
				Color(252);
				cout << "X";
				Color(240);
			}
			else if (a[x][y] == 2)
			{
				Color(249);
				cout << "O";
				Color(240);
			}
			y = y + 4;
		}
		x = x + 2;
	}
	GoToXY(115, 3);
	cout << "SCORE BOARD";
	GoToXY(120, 5);
	cout << "-"; 
	GoToXY(116 - s1.length(), 5);
	cout << s1;
	GoToXY(118, 5);
	Color(240);
	cout << d1;
	Color(240);
	GoToXY(125, 5);
	cout << s2;
	GoToXY(122, 5);
	Color(240);
	cout << d2;
	Color(240);
	GoToXY(117, 10);
	cout << "TURN: ";
	if (i % 2 == 0)
	{
		Color(249);
		cout << s2;
	}
	else
	{
		Color(252);
		cout << s1;
	}
	GoToXY(114, 15);
	Color(240);
	cout << "NOTIFICATION:  ";
}
void StartGame(int a[][200], int n, string s1, string s2, int d1, int d2, int i)
{
	system("cls");
	ResetData(a, n);
	DrawBoard(a, n, s1, s2, d1, d2, i);
}
void Move(int n, int &x, int &y, char c)
{
	if (c == 'w' || c == 'W')
	{
		if (y > 0)
		{
			y = y - 2;
			GoToXY(x, y);
		}
	}
	if (c == 's' || c == 'S')
	{
		if (y < 2 * (n - 1))
		{
			y = y + 2;
			GoToXY(x, y);
		}
	}
	if (c == 'd' || c == 'D')
	{
		if (x < 4 * (n - 1))
		{
			x = x + 4;
			GoToXY(x, y);
		}
	}
	if (c == 'a' || c == 'A')
	{
		if (x > 0)
		{
			x = x - 4;
			GoToXY(x, y);
		}
	}
}
int Law(int a[][200], int n, int k)
{
	int i, j, s, l;
	s = 0;
	if (k == 1) l = 2;
	else if (k == 2) l = 1;
	for (i = 0; i < 2 * n; )
	{
		for (j = 0; j < 4 * (n - 1); )
		{
			if (a[i][j] == 0) s = 1;
			j = j + 4;
		}
		i = i + 2;
	}
	for (i = 0; i < 2 * (n - 1);)
	{
		for (j = 0; j <= 4 * (n - 1);)
		{
			if (j == 0)
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k && a[i][j + 16] == k)
				{
					if (a[i][j + 20] != l) return 1;
				}
			}
			else if (j == 4 * (n - 5))
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k)
				{
					if (a[i][j - 4] == 0 && a[i][j + 16] == 0) return 1;
					if (a[i][j - 4] != l && a[i][j + 16] == k) return 1;
				}
			}
			else
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k)
				{
					if (a[i][j - 4] == 0 && a[i][j + 16] == 0) return 1;
				}
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k && a[i][j + 16] == k)
				{
					if (a[i][j - 4] != l) return 1;
					if (a[i][j - 4] != l || a[i][j + 20] != l) return 1;
				}
			}
			j = j + 4;
		}
		i = i + 2;
	}
	for (j = 0; j <= 4 * (n - 1);)
	{
		for (i = 0; i < 2 * (n - 4);)
		{
			if (i == 0)
			{
				if (a[0][j] == k && a[2][j] == k && a[4][j] == k && a[6][j] == k && a[8][j] == k)
				{
					if (a[10][j] != l) return 1;
				}
			}
			else if (i == 2 * (n - 5))
			{
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k)
				{
					if (a[i - 2][j] == 0 && a[i + 8][j] == 0) return 1;
					if (a[i - 2][j] != l && a[i + 8][j] == k) return 1;
				}
			}
			else
			{
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k)
				{
					if (a[i - 2][j] == 0 && a[i + 8][j] == 0) return 1;
				}
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k && a[i + 8][j] == k)
				{
					if (a[i - 2][j] != l || a[i + 10][j] != l) return 1;
				}
			}
			i = i + 2;
		}
		j = j + 4;
	}
	for (i = 0; i <= 2 * (n - 3);)
	{
		for (j = 0; j <= 4 * (n - 1); )
		{
			if (i == 0 || j == 0)
			{
				if (a[i][j] == k && a[i + 2][j + 4] == k && a[i + 4][j + 8] == k && a[i + 6][j + 12] == k)
				{
					if (a[i + 8][j + 16] == k)
					{
						if (a[i + 10][j + 20] == k || a[i + 10][j + 20] == 0) return 1;
					}
				}
			}
			else if (a[i][j] == k && a[i + 2][j + 4] == k && a[i + 4][j + 8] == k && a[i + 6][j + 12] == k)
			{
				if (a[i - 2][j - 4] == 0 && a[i + 8][j + 16] == 0) return 1;
				if (a[i - 2][j - 4] == k && a[i + 8][j + 16] == 0) return 1;
				if (a[i - 2][j - 4] == 0 && a[i + 8][j + 16] == k) return 1;
			}
			if (i == 0 || j == 0)
			{
				if (a[i][j] == k && a[i + 2][j - 4] == k && a[i + 4][j - 8] == k && a[i + 6][j - 12] == k)
				{
					if (a[i + 8][j - 16] == k)
					{
						if (a[i + 10][j - 20] == k || a[i + 10][j - 20] == 0) return 1;
					}
				}
			}
			else if (a[i][j] == k && a[i + 2][j - 4] == k && a[i + 4][j - 8] == k && a[i + 6][j - 12] == k)
			{
				if (a[i - 2][j + 4] == 0 && a[i + 8][j - 16] == 0) return 1;
				if (a[i - 2][j + 4] == k && a[i + 8][j - 16] == 0) return 1;
				if (a[i - 2][j + 4] == 0 && a[i + 8][j - 16] == k) return 1;
			}
			j = j + 4;
		}
		i = i + 2;
	}
	if (s == 0) return 0;
}
void SaveGame(int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i, ofstream &fOut)
{
	int x, y, k1, k2;
	fOut << n << endl;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			fOut << a[x][y] << ' ';
			y = y + 4;
		}
		x = x + 2;
		fOut << endl;
	}
	k1 = 1;
	for (x = 0; x < s1.length(); x++) if (s1[x] == ' ') k1 = k1 + 1;
	fOut << endl << k1 << endl << s1 << endl;
	k2 = 1;
	for (x = 0; x < s2.length(); x++) if (s2[x] == ' ') k2 = k2 + 1;
	fOut << endl << k2 << endl << s2 << endl;
	fOut << endl << d1 << ' ' << d2 << endl;
	fOut << endl << t << endl;
	fOut << endl << i;
}
void AskSave(int x, int y, int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i)
{
	int x1, y1;
	char c;
	string s;
	x1 = 105;
	y1 = 27;
	GoToXY(105, 25);
	cout << "\aDO YOU WANT TO SAVE BEFORE EXITING ?";
	Cout3(x1);
	while (1)
	{
		GoToXY(x1, y1);
		c = _getch();
		Move3(x1, c);
		Cout3(x1);
		if (c == 13 || c == 8) break;
	}
	GoToXY(105, 25);
	Color(240);
	cout << "                                        ";
	GoToXY(105, 27);
	cout << "                                        ";
	if (c == 8) GoToXY(x, y);
	else
	{
		if (x1 == 105)
		{
			GoToXY(114, 25);
			rewind(stdin);
			cout << "ENTER A NAME: ";
			getline(cin, s);
			ofstream fOut;
			fOut.open(s, ios_base::out);
			SaveGame(a, n, s1, s2, d1, d2, t, i, fOut);
			fOut.close();
			Color(240);
			system("cls");
			Caro();
			GameMenu();
		}
		if (x1 == 125)
		{
			Color(240);
			system("cls");
			Caro();
			GameMenu();
		}
	}
}
void AskContinue(int x, int y, int a[][200], int n, string s1, string s2, int d1, int d2, int t, int &i)
{
	int x1, y1;
	char c;
	x1 = 105;
	y1 = 27;
	GoToXY(105, 25);
	cout << "_DO YOU WANT TO CONTINUE PLAYING ?_";
	Cout3(x1);
	while (1)
	{
		GoToXY(x1, y1);
		c = _getch();
		Move3(x1, c);
		Cout3(x1);
		if (c == 13 || c == 8) break;
	}
	if (c == 8)
	{
		GoToXY(105, 25);
		Color(240);
		cout << "                                        ";
		GoToXY(105, 27);
		cout << "                                        ";
		GoToXY(x, y);
	}
	else
	{
		Color(240);
		system("cls");
		if (x1 == 105)
		{
			StartGame(a, n, s1, s2, d1, d2, i);
			CheckBoard(a, n, s1, s2, d1, d2, t, i);
		}
		if (x1 == 125)
		{
			Caro();
			GameMenu();
		}
	}
}
void Process1(int x, int y, int a[][200], int n, string s1, string s2, int &d1, int &d2, int t, int &i)
{
	int k, l;
	if (a[y][x - 4] == 0)
	{
		Color(252);
		cout << "X";
		GoToXY(123, 10);
		Color(240);
		cout << "                                           ";
		GoToXY(128, 15);
		cout << "                                           ";
		GoToXY(123, 10);
		Color(249);
		cout << s2;
		Color(240);
		a[y][x - 4] = 1;
		i = i + 1;
		k = 1;
		l = Law(a, n, k);
		if (l == 1)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    " << s1 << " WIN    ";
			GoToXY(123, 10);
			Color(240);
			cout << "                                           ";
			d1 = d1 + 1;
			GoToXY(118, 5);
			Color(240);
			cout << d1;
			Color(240);
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
		if (l == 0)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    DRAW    ";
			GoToXY(123, 10);
			Color(240);
			cout << "                                           ";
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
	}
	else
	{
		GoToXY(128, 15);
		cout << "\aPlease mark on another position...";
	}
}
void Process2(int x, int y, int a[][200], int n, string s1, string s2, int &d1, int &d2, int t, int &i)
{
	int k, l;
	if (a[y][x - 4] == 0)
	{
		Color(249);
		cout << "O";
		GoToXY(123, 10);
		Color(240);
		cout << "                                           ";
		GoToXY(128, 15);
		cout << "                                           ";
		GoToXY(123, 10);
		Color(252);
		cout << s1;
		Color(240);
		a[y][x - 4] = 2;
		i = i + 1;
		k = 2;
		l = Law(a, n, k);
		if (l == 1)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    " << s2 << " WIN    ";
			GoToXY(123, 10);
			Color(240);
			cout << "                                           ";
			d2 = d2 + 1;
			GoToXY(122, 5);
			Color(240);
			cout << d2;
			Color(240);
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
		if (l == 0)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    DRAW    ";
			GoToXY(123, 10);
			Color(240);
			cout << "                                           ";
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
	}
	else
	{
		GoToXY(128, 15);
		cout << "\aPlease mark on another position...";
	}

}
void CheckBoard(int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i)
{
	int x, y, x1, y1, l, k;
	char c, c1;
	GoToXY(99, 1);
	Color(240);
	t = t + 1;
	cout << "_______________THE " << t;
	if (t % 10 == 1) cout << "st ";
	else if (t % 10 == 2) cout << "nd ";
	else if (t % 10 == 3) cout << "rd ";
	else cout << "th ";
	cout << "MATCH_______________";
	Color(240);
	if (n % 2 == 0)
	{
		x = (n / 2 - 1) * 4;
		y = (n / 2 - 1) * 2;
	}
	else
	{
		x = (n - 1) * 2;
		y = n - 1;
	}
	GoToXY(x, y);
	while (i <= n * n)
	{
		while (1)
		{
			c = _getch();
			if (c == 13)
			{
				x = x + 4;
				break;
			}
			else if (c == 8) AskSave(x, y, a, n, s1, s2, d1, d2, t, i);
			else Move(n, x, y, c);
		}
		if (i % 2 != 0) Process1(x, y, a, n, s1, s2, d1, d2, t, i);
		else Process2(x, y, a, n, s1, s2, d1, d2, t, i);
		GoToXY(x, y);
		if (x > 4 * (n - 1))
		{
			if (y < 2 * (n - 1)) y = y + 2;
			x = 4 * (n - 1);
			GoToXY(x, y);
		}
		else GoToXY(x, y);
	}
}
void ClearScreen()
{
	int i, j;
	Color(240);
	for (i = 25; i < 40; i++)
	{
		GoToXY(50, i);
		for (j = 0; j < 100; j++) cout << " ";
	}
}
void Move1(int &y, char c)
{
	if (c == 's' || c == 'S')
	{
		if (y < 33)
		{
			y = y + 2;
			GoToXY(75, y);
		}
		else if (y == 33)
		{
			y = 25;
			GoToXY(75, y);
		}
	}
	if (c == 'w' || c == 'W')
	{
		if (y > 25)
		{
			y = y - 2;
			GoToXY(75, y);
		}
		else if (y == 25)
		{
			y = 33;
			GoToXY(75, y);
		}
	}
}
void Cout1(int y)
{
	if (y == 25)
	{
		Color(15);
		cout << "         NEW GAME         ";
		Color(240);
		GoToXY(75, 27);
		cout << "         LOAD GAME        ";
		GoToXY(75, 29);
		cout << "           HELP           ";
		GoToXY(75, 31);
		cout << "           ABOUT          ";
		GoToXY(75, 33);
		cout << "           EXIT           ";
	}
	if (y == 27)
	{
		Color(15);
		cout << "         LOAD GAME        ";
		Color(240);
		GoToXY(75, 25);
		cout << "         NEW GAME         ";
		GoToXY(75, 29);
		cout << "           HELP           ";
		GoToXY(75, 31);
		cout << "           ABOUT          ";
		GoToXY(75, 33);
		cout << "           EXIT           ";
	}
	if (y == 29)
	{
		Color(15);
		cout << "           HELP           ";
		Color(240);
		GoToXY(75, 25);
		cout << "         NEW GAME         ";
		GoToXY(75, 27);
		cout << "         LOAD GAME        ";
		GoToXY(75, 31);
		cout << "           ABOUT          ";
		GoToXY(75, 33);
		cout << "           EXIT           ";
	}
	if (y == 31)
	{
		Color(15);
		cout << "           ABOUT          ";
		Color(240);
		GoToXY(75, 25);
		cout << "         NEW GAME         ";
		GoToXY(75, 27);
		cout << "         LOAD GAME        ";
		GoToXY(75, 29);
		cout << "           HELP           ";
		GoToXY(75, 33);
		cout << "           EXIT           ";
	}
	if (y == 33)
	{
		Color(15);
		cout << "           EXIT           ";
		Color(240);
		GoToXY(75, 25);
		cout << "         NEW GAME         ";
		GoToXY(75, 27);
		cout << "         LOAD GAME        ";
		GoToXY(75, 29);
		cout << "           HELP           ";
		GoToXY(75, 31);
		cout << "           ABOUT          ";
	}
}
void Move2(int &x, char c)
{
	if (c == 'd' || c == 'D' || c == 'a' || c == 'A')
	{
		if (x == 89) x = 69;
		else if (x == 69) x = 89;
		GoToXY(x, 27);
	}
}
void Cout2(int x)
{
	if (x == 69)
	{
		GoToXY(89, 27);
		Color(240);
		cout << "       NO       ";
		GoToXY(69, 27);
		Color(15);
		cout << "       YES       ";
	}
	if (x == 89)
	{
		GoToXY(69, 27);
		Color(240);
		cout << "       YES       ";
		GoToXY(89, 27);
		Color(15);
		cout << "       NO       ";
	}
}
void Move3(int &x, char c)
{
	if (c == 'd' || c == 'D' || c == 'a' || c == 'A')
	{
		if (x == 105) x = 125;
		else if (x == 125) x = 105;
		GoToXY(x, 27);
	}
}
void Cout3(int x)
{
	if (x == 105)
	{
		GoToXY(125, 27);
		Color(240);
		cout << "       NO       ";
		GoToXY(105, 27);
		Color(15);
		cout << "       YES       ";
	}
	if (x == 125)
	{
		GoToXY(105, 27);
		Color(240);
		cout << "       YES       ";
		GoToXY(125, 27); 
		Color(15);
		cout << "       NO       ";
	}
}
string Standardized(string &s)
{
	int i, j, n;
	char s0[50];
	n = s.length();
	for (i = 0; i < n; i++) s0[i] = s[i];
	s0[n] = '\0';
	while (s0[0] == ' ')
	{
		for (i = 0; i < n - 1; i++) s0[i] = s0[i + 1];
		n = n - 1;
	}
	while (s0[n - 2] == ' ')
	{
		s0[n - 2] = '\0';
		n = n - 1;
	}
	for (i = 1; i < n - 1; i++)
	{
		if (s0[i] == ' ' && s0[i + 1] == ' ')
		{
			for (j = i + 1; j < n - 1; j++) s0[j] = s0[j + 1];
		}
		n = n - 1;
		i = i - 1;
	}
	s = s0;
	return s;
}
void GameMenu()
{
	int x, y, n, a[200][200], i, j, d1, d2, t;
	char c1, c2;
	string s1, s2, s;
	string s01 = "PLAYER_1";
	string s02 = "PLAYER_2";
	x = 75;
	y = 25;
	rewind(stdin);
	GoToXY(x, y);
	Cout1(y);
	while (1)
	{
		while (1)
		{
			GoToXY(x, y);
			c1 = _getch();
			Move1(y, c1);
			Cout1(y);
			if (c1 == 13) break;
		}
		if (y == 25)
		{
			ClearScreen();
			GoToXY(79, 25);
			cout << "ENTER BOARDSIZE: ";
			cin >> n;
			while (n <= 5 || n >= 21)
			{
				GoToXY(65, 25);
				cout << "\aPLEASE REENTER BOARDSIZE (5 < BOARDSIZE < 21): ";
				cin >> n;
				cout << "    ";
			}
			GoToXY(65, 25);
			cout << "                                                            ";
			GoToXY(77, 25);
			Color(240);
			rewind(stdin);
			cout << "ENTER PLAYER_1's NAME: ";
			Color(252);
			getline(cin, s1);
			if (s1.length() == 0) s1 = s01;
			else Standardized(s1);
			GoToXY(77, 27);
			Color(240);
			rewind(stdin);
			cout << "ENTER PLAYER_2's NAME: ";
			Color(249);
			getline(cin, s2);
			if (s2.length() == 0) s2 = s02;
			else Standardized(s2);
			Color(240);
			d1 = 0;
			d2 = 0;
			t = 0;
			i = 1;
			StartGame(a, n, s1, s2, d1, d2, i);
			CheckBoard(a, n, s1, s2, d1, d2, t, i);
		}
		if (y == 27)
		{
			ClearScreen();
			GoToXY(70, 25);
			cout << "ENTER YOUR FILE's YOU WANT TO OPEN: ";
			getline(cin, s);
			ifstream fIn;
			fIn.open(s, ios_base::in);
			LoadGame(a, n, s1, s2, d1, d2, t, i, fIn);
			fIn.close();
			system("cls");
			DrawBoard(a, n, s1, s2, d1, d2, i);
			CheckBoard(a, n, s1, s2, d1, d2, t, i);
		}
		if (y == 29)
		{
			ClearScreen();
			Help();
			GoToXY(50, 34);
			Color(240);
			system("pause");
			Color(240);
			ClearScreen();
			GoToXY(x, y);
			Cout1(y);
		}
		if (y == 31)
		{
			ClearScreen();
			About();
			GoToXY(53, 34);
			Color(240);
			system("pause");
			Color(240);
			ClearScreen();
			GoToXY(x, y);
			Cout1(y);
		}
		if (y == 33)
		{
			x = 89;
			y = 27;
			ClearScreen();
			GoToXY(67, 25);
			cout << "\aARE YOU SURE THAT YOU WANT TO EXIT GAME ?";
			Cout2(x);
			while (1)
			{
				GoToXY(x, y);
				c2 = _getch();
				Move2(x, c2);
				Cout2(x);
				if (c2 == 13) break;
			}
			if (x == 69) exit(0);
			else 
			{
				ClearScreen();
				x = 75;
				y = 33;
				GoToXY(x, y);
				Cout1(y);
			}
		}
	}
}
void LoadGame(int a[][200], int &n, string &s1, string &s2, int &d1, int &d2, int &t, int &i, ifstream &fIn)
{
	int x, y, k1, k2;
	string sk1[50], sk2[50];
	fIn >> n;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			fIn >> a[x][y];
			y = y + 4;
		}
		x = x + 2;
	}
	fIn >> k1;
	for (i = 0; i < k1; i++)
	{
		fIn >> sk1[i];
		if (i == k1 - 1) s1 = s1 + sk1[i];
		else s1 = s1 + sk1[i] + ' ';
	}
	fIn >> k2;
	for (i = 0; i < k2; i++)
	{
		fIn >> sk2[i];
		if (i == k2 - 1) s2 = s2 + sk2[i];
		else s2 = s2 + sk2[i] + ' ';
	}
	fIn >> d1;
	fIn >> d2;
	fIn >> t;
	t = t - 1;
	fIn >> i;
}
void Help()
{
	ClearScreen();
	GoToXY(50, 25);
	cout << "Moving:";
	GoToXY(55, 26);
	cout << "Press 'W' to move up";
	GoToXY(55, 27);
	cout << "Press 'S' to move down";
	GoToXY(55, 28);
	cout << "Press 'D' to move right";
	GoToXY(55, 29);
	cout << "Press 'A' to move left";
	GoToXY(55, 30);
	cout << "After choosing position, press 'Enter' to mark ";
	Color(252);
	cout << "'X'";
	Color(240);
	cout << " or ";
	Color(249);
	cout << "'O'";
	Color(240);
	GoToXY(50, 31);
	cout << "While you are playing, if you want to exit the game,";
	GoToXY(50, 32);
	cout << "press 'BackSapce' and save the game if you want or press 'BackSapce' again to continue playing";
}
void About()
{
	GoToXY(53, 25);
	cout << "HO CHI MINH UNIVERSITY OF SCIENCE - FACULTY OF INFORMATION TECHNOLOGY";
	GoToXY(60, 27);
	cout << "19CTT1 - Group 8:";
	GoToXY(66, 28);
	cout << "1. Nguyen The Hai ............. 19120069";
	GoToXY(66, 29);
	cout << "2. Tran Duc Thuy .............. 19120138";
	GoToXY(66, 30);
	cout << "3. Nguyen Tien Toan ........... 19120399";
	GoToXY(66, 31);
	cout << "4. Phan Minh Triet ............ 19120039";
	GoToXY(66, 32);
	cout << "5. Huynh Ngoc Van ............. 19120155";
}