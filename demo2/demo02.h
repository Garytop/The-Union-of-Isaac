#pragma warning(disable:4996)

#define WIDTH 960
#define HEIGTH 540

static int time = 200;

IMAGE bk_img, loading[56],
      startmenu[5], temp_menu1_img, temp_menu2_img;

//���ؽ�����Դ
void loadLoadingRes(void);
//���ؽ�����ʾ
void showLoadingRes(void);

//���ؿ�ʼ�˵���Դ
void loadStartMenuRes(void);
//���뿪ʼ�˵�
void showStartMenu(void);


//�滭͸��ͼ��
void drawAlpha(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
