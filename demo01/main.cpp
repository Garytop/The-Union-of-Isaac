#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>

void StartUp(void);
void initializemap(void);
void initializeissac(void);
void initializestart(void);
void menu(void);

int main(void)
{
	initgraph(1440,810,0);
	menu();
	StartUp();
	_getch();
	closegraph();
	return 0;
}
