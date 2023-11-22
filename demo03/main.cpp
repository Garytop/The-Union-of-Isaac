#include <stdio.h>
#include <easyx.h>
#include <conio.h>

#pragma warning(disable:4996)

#define WIDTH 960
#define HEIGTH 540

static int time = 200;

IMAGE bk_img, loading[56], 
      startmenu[5], temp_menu1_img, temp_menu2_img,
      map_img, temp_map_img,
      issac_img;

//定义游戏角色结构体
typedef struct character {
    int x, y;
    int width, height; 
    int speed;
    int hp;
    int new_born_flag;
}CHARACTER;

CHARACTER isaac;

//加载界面资源
void loadLoadingRes(void);
//加载界面显示
void showLoadingRes(void);

//加载开始菜单资源
void loadStartMenuRes(void);
//进入开始菜单
void showStartMenu(void);
//鼠标操作开始菜单
void operateStartMenu(void);

//加载地图资源
void loadMapRes(void);
//加载以撒资源
void loadIsaacRes(void);
//显示地图
void showMap(void);
//开始游戏
void startGame(void);
//初始化数据
void data_init(void);


//绘画透明图像
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg);

int main(void)
{
	initgraph(WIDTH, HEIGTH);
	loadLoadingRes();
	showLoadingRes();
    cleardevice();
    loadStartMenuRes();
    showStartMenu();
    data_init();
    operateStartMenu();
    _getch();
	closegraph();
	return 0;
}

//加载界面资源
void loadLoadingRes(void)
{
    loadimage(&bk_img, _T("../Texture/Loading/bgblack.png"));
    char a[200] = { 0 };
    int i = 0;
    for (; i < 56; i++)
    {
        sprintf(a, "../Texture/Loading/loadimages-%03d.png", i + 1);
        loadimage(loading + i, a);
    }
    loadimage(startmenu + 0, _T("../Texture/Title/Logo.png"));
}

//加载界面显示
void showLoadingRes(void)
{
    for (int i = 0; i < 56; i++)
    {
        cleardevice();
        putimage(0, 0, &bk_img);
        putimage(400, 200, loading + i);
        Sleep(time);
    }
    putimage(250, 200, startmenu + 0);
    Sleep(2000);
}

//绘画透明图像
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg)
{
    DWORD* dst = GetImageBuffer(dstimg);
    DWORD* src = GetImageBuffer(srcimg);
    int src_width = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int dst_width = (dstimg == NULL ? getwidth() : dstimg->getwidth());
    int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

    int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
    int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;
    if (x < 0) { src += -x;				iwidth -= -x;	x = 0; }
    if (y < 0) { src += src_width * -y;	iheight -= -y;	y = 0; }

    dst += dst_width * y + x;

    for (int iy = 0; iy < iheight; ++iy)
    {
        for (int i = 0; i < iwidth; ++i)
        {
            int sa = ((src[i] & 0xff000000) >> 24);
            if (sa != 0)
            {
                if (sa == 255)
                    dst[i] = src[i];
                else
                    dst[i] = ((((src[i] & 0xff0000) >> 16) + ((dst[i] & 0xff0000) >> 16) * (255 - sa) / 255) << 16) | ((((src[i] & 0xff00) >> 8) + ((dst[i] & 0xff00) >> 8) * (255 - sa) / 255) << 8) | ((src[i] & 0xff) + (dst[i] & 0xff) * (255 - sa) / 255);
            }
        }
        dst += dst_width;
        src += src_width;
    }
}

//加载开始菜单资源
void loadStartMenuRes(void)
{
    loadimage(startmenu + 1, _T("../Texture/Title/Title1.png"), WIDTH, HEIGTH);
    loadimage(&temp_menu1_img, _T("../Texture/Title/Title1.png"), WIDTH, HEIGTH);
    loadimage(startmenu + 2, _T("../Texture/Title/Title2.png"), WIDTH, HEIGTH);
    loadimage(&temp_menu2_img, _T("../Texture/Title/Title2.png"), WIDTH, HEIGTH);
    loadimage(startmenu + 3, _T("../Texture/Title/NewRun.png"));
    loadimage(startmenu + 4, _T("../Texture/Title/Stats.png"));
}

//进入开始菜单
void showStartMenu(void)
{
    drawAlpha(&temp_menu1_img, 0, 0, startmenu + 1);
    putimage(0, 0, &temp_menu1_img);
    setbkmode(TRANSPARENT);
    settextstyle(20, 10, "Consolas");
    settextcolor(BLACK);
    outtextxy(370, 250, "Press Any Key to Start");
    _getch();

    drawAlpha(&temp_menu2_img, 0, 0, startmenu + 2);
    drawAlpha(&temp_menu2_img, 400, 150, startmenu + 3);
    drawAlpha(&temp_menu2_img, 400, 250, startmenu + 4);
    putimage(0, 0, &temp_menu2_img);
}

//鼠标操作开始菜单
void operateStartMenu(void)
{
    ExMessage msg;
    while (true)
    {
        if (peekmessage(&msg, EX_MOUSE))
        {
            switch (msg.message)
            {
            case WM_LBUTTONDOWN:
                if (msg.x >= 400 && msg.x <= 560 && msg.y >= 150 && msg.y <= 200)
                {
                    startGame();
				}
                else if (msg.x >= 400 && msg.x <= 560 && msg.y >= 250 && msg.y <= 300)
                {
					//查看统计
				}
				break;
            default:
				break;
            }
        }
	}
}

//加载地图资源
void loadMapRes(void)
{
    loadimage(&map_img, _T("../Texture/Map/room_000.png"), WIDTH, HEIGTH);
    loadimage(&temp_map_img, _T("../Texture/Map/room_000.png"), WIDTH, HEIGTH);
}

//加载以撒资源
void loadIsaacRes(void)
{
    loadimage(&issac_img, _T("../Texture/Play/Issac_Loot.png"));
}

//初始化数据
void data_init(void)
{
    isaac.x = 200;
    isaac.y = 200;
    //isaac.width = 40;
    //isaac.height = 40;
    //isaac.speed = 5;
    //isaac.hp = 3;
    //isaac.new_born_flag = 1;
}
//显示地图
void showMap(void)
{
    drawAlpha(&temp_map_img, 0, 0, &map_img);
    drawAlpha(&temp_map_img, isaac.x, isaac.y, &issac_img);
    putimage(0, 0, &temp_map_img);
}

//开始游戏
void startGame(void)
{
    loadMapRes();
    loadIsaacRes();
    showMap();
}