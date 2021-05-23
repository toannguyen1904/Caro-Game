#pragma once
#include<fstream>
using namespace std;
void FixConsoleWindow(int x, int y);
void Color(int c);
void GoToXY(int x, int y);
void Caro();
void SaveGame(int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i, ofstream &fOut);
void LoadGame(int a[][200], int &n, string &s1, string &s2, int &d1, int &d2, int &t, int &i, ifstream &fIn);
void AskSave(int x, int y, int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i);
void AskContinue(int x, int y, int a[][200], int n, string s1, string s2, int d1, int d2, int t, int &i);
void ClearScreen();
void Move1(int &y, char c);
void Cout1(int y);
void Move2(int &x, char c);
void Cout2(int x);
void Move3(int &x, char c);
void Cout3(int x);
string Standardized(string &s);
void Help();
void About();