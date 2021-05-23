#pragma once
void ResetData(int a[][200], int n);
void DrawBoard(int a[][200], int n, string s1, string s2, int d1, int d2, int i);
void StartGame(int a[][200], int n, string s1, string s2, int d1, int d2, int i);
void Move(int n, int &x, int &y, char c);
int Law(int a[][200], int n);
void Process1(int x, int y, int a[][200], int n, string s1, string s2, int &d1, int &d2, int t, int &i);
void Process2(int x, int y, int a[][200], int n, string s1, string s2, int &d1, int &d2, int t, int &i);
void CheckBoard(int a[][200], int n, string s1, string s2, int d1, int d2, int t, int i);
void GameMenu();