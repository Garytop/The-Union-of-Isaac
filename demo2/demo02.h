#pragma warning(disable:4996)

#define WIDTH 960
#define HEIGTH 540

static int time = 200;

IMAGE bk_img, loading[56],
      startmenu[5], temp_menu1_img, temp_menu2_img;

//加载界面资源
void loadLoadingRes(void);
//加载界面显示
void showLoadingRes(void);

//加载开始菜单资源
void loadStartMenuRes(void);
//进入开始菜单
void showStartMenu(void);


//绘画透明图像
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
