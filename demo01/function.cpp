#include<stdio.h>
#include<easyx.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>

void StartUp(void);
void initializemap(void);
void initializeissac(void);
void initializestart(void);
void menu(void);
int create_location(int px);


int create_location(int px)//�����������
{
	int ans = rand() % px;
	return ans;
}

//���˵�����
void menu(void)
{
	IMAGE menu;
	loadimage(&menu, "./menu./menu2.png", 1440, 810);
	putimage(0, 0, &menu);

	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	roundrect(300, 110, 1100, 300, 10, 10);
	roundrect(300, 380, 1100, 570, 10, 10);

	int x = 0, y = 0;
	while (1)
	{
		ExMessage msg;
		if (peekmessage(&msg, EX_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				if (msg.x >= 300 && msg.x <= 1100 && msg.y >= 110 && msg.y <= 300)
				{
					cleardevice();
					StartUp();
				}
				else if (msg.x >= 300 && msg.x <= 1100 && msg.x >= 380 && msg.y <= 570)
					cleardevice();
				break;
			}
		}
	}
}

//��ʼ����
void StartUp(void)
{
	initgraph(1440, 810);

	//��ʼ����
	initializestart();
	outtextxy(720, 405, "Press any key to start");
	_getch();
	cleardevice();

	//��ʼ����ͼ
	initializemap();

	//��ʼ����ɫ
	int x, y;
	srand((unsigned)time(0));
	do {
		x = create_location(1440);
		y = create_location(810);
	} while (x < 380 || x>1200 || y < 250 || y > 800);
	setorigin(x, y);
	initializeissac();
}

//��ʼ����ͼ
void initializemap(void)
{
	IMAGE img;
	loadimage(&img, ".././Texture./Map./room_000.png", 1440, 810);
	putimage(0, 0, &img);
}

//��ʼ����ʼ��ʾҳ��
void initializestart(void)
{
	IMAGE img;
	loadimage(&img, ".././Texture./Play./start_000.png", 1440, 810);
	putimage(0, 0, &img);
}

//��ʼ������
void initializeissac(void)
{
	IMAGE img1;
	IMAGE img2;
	loadimage(&img1, ".././Texture./Play./Issac_Loot_1.png", 50, 50);
	loadimage(&img2, ".././Texture./Play./Issac_Loot_2.png", 50, 50);
	putimage(0,0,&img1, SRCPAINT);
	putimage(0, 0, &img2, SRCAND);
}
