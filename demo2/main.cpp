#include "demo02.h"
#include<stdio.h>
#include<easyx.h>
#include<conio.h>

int main(void)
{
	initgraph(WIDTH, HEIGTH);
	loadLoadingRes();
	showLoadingRes();
	cleardevice();
	loadStartMenuRes();
	showStartMenu();
	_getch();
	closegraph();
	return 0;
}