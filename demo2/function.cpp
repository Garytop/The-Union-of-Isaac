#include"demo02.h"
#include<stdio.h>
#include<easyx.h>
#include<conio.h>

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
}

//加载界面显示
void showLoadingRes(void)
{
    for (int i = 0; i < 56; i++)
    {
        cleardevice();
        putimage(0, 0, &bk_img);
        putimage(400, 200, loading + i);
        Sleep(time += 5);
    }
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
    loadimage(startmenu + 0, _T("../Texture/Title/Logo.png"));
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
    drawAlpha(&temp_menu1_img, 400, 0, startmenu + 0);
    drawAlpha(&temp_menu1_img, 0, 0, startmenu + 1);
    putimage(0, 0, &temp_menu1_img);
    setbkmode(TRANSPARENT);
    settextstyle(20, 10, "微软黑体");
    settextcolor(BLACK);
    outtextxy(400, 250, "按任意键以继续");
    _getch();

    drawAlpha(&temp_menu2_img, 0, 0, startmenu + 2);
    drawAlpha(&temp_menu2_img, 400, 150, startmenu + 3);
    drawAlpha(&temp_menu2_img, 400, 250, startmenu + 4);
    putimage(0, 0, &temp_menu2_img);
}