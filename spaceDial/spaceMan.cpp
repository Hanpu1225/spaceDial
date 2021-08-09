#include<graphics.h>
#include<stdio.h>
#include"date_tool.h"

IMAGE imgs[71];//̫����ͼ��
IMAGE sz[11];//����
IMAGE sz2[10];//��

void drawDate() {
	char str[16] = "";
	int year, month, day;
	getDate(&year, &month, &day, str);

	setbkcolor(RGB(223, 230, 240));
	settextcolor(RGB(15, 15, 15));      //����������ɫ
	settextstyle(25, 0, "��������"); //����������ʽ΢���ź�
	outtextxy(70, 0, str); //��ָ��λ������ı�

	getWeek(year, month, day, str);
	outtextxy(65, 30, str);

	sprintf(str, "%d-%d", month, day);
	outtextxy(110, 30, str);
}


void drawTime() {
	static int last_hour = -1, last_minute = -1, last_second = -1;
	int hour, minute, second;
	getTime(&hour, &minute, &second);

	int posX = -130;
	int posY = -90;

	int h1 = hour / 10;
	int h2 = hour % 10;
	if (last_hour != hour)  putimage(posX, posY, &sz[h1]);
	posX += 50;
	if (last_hour != hour) putimage(posX, posY, &sz[h2]);

	posX += 50;
	posY += 15;
	static bool first = true;
	if (first) putimage(posX, posY, &sz[10]);
	posY += 30;
	if (first) putimage(posX, posY, &sz[10]);

	posX += 20;
	posY = -90;
	int m1 = minute / 10;
	int m2 = minute % 10;
	if (last_minute != minute) putimage(posX, posY, &sz[m1]);
	posX += 50;
	if (last_minute != minute) putimage(posX, posY, &sz[m2]);

	posX += 50;
	posY += 35;
	if (last_second / 10 != second / 10) putimage(posX, posY, &sz2[second / 10]);
	posX += 30;

	if (last_second % 10 != second % 10) putimage(posX, posY, &sz2[second % 10]);
	//����
	if (first || (hour == 0 && minute == 0 && second<3)) {
		drawDate();
	}

	first = false;
	last_hour = hour;
	last_minute = minute;
	last_second = second;
}


void initWinStyle()
{
	//���崰�ڵĳ��Ϳ�
	initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	HWND hwnd = GetHWnd();
	//SetWindowLong�޸Ĵ�������  GetWindowLong ����������Ϣ
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	//�޸Ĵ���Ϊ���㴰��
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);

	//���ô���Ϊ͸��Ч��
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_STYLE) | WS_EX_LAYERED);//������չ���ڷ��Ϊ�ֲ㴰�ڣ��������������滻ֵ
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);//���ô���͸���� LWA_COLORKEY͸����ʽ

	setbkcolor(RGB(0, 0, 0));//���ñ��������ɫ
	cleardevice();//ʹ�ñ�����ɫ������
}

void paintLine()
{
	//setorigin(GetSystemMetrics(SM_CXSCREEN - 200), 200);
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 200, 200);
	IMAGE bg;
	loadimage(&bg, "bg3.jpg", 400, 400, true);
	//putimage(0, 0, &bg);
	putimage(-200, -200, &bg);
	setlinecolor(BLACK);//����������ɫ
	setlinestyle(PS_SOLID, 8);//����������ʽΪʵ�ߣ����Ϊ8
	circle(0, 0, 203);
}

void loadPic()
{
	//����̫����ͼ������forѭ��
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		//sprintf_s �亯�������ǽ����ݸ�ʽ��������ַ���
		sprintf_s(imgName, sizeof(imgName), "img/human_%04d_ͼ�� %d.jpg", i, 71 - i);
		//loadimage ����ͼ���imgs����ָ��,ͼƬ�ļ���,ͼƬ��������,ͼƬ������߶ȣ��Ƿ���� IMAGE �Ĵ�С����ӦͼƬ
		loadimage(&imgs[i], imgName, 105, 105, true);
	}

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg", i);
		loadimage(&sz[i], imgName, 40, 70, true);//Сʱ ����
		loadimage(&sz2[i], imgName, 20, 35, true);//��
	}
	loadimage(&sz[10], "img/rect.jpg", 10, 10, true);//:

}
int main()
{
	initWinStyle();
	setorigin(GetSystemMetrics(SM_CXSCREEN - 200), 200);//��ϴ����������ԭ��*����Ҫ��
	paintLine();
	loadPic();
	int k = 0;
	while (true)
	{
		//��һ����ǰ�������ڴ��е�ͼ���������Ļ��
		putimage(-50, -15, &imgs[k]); //bufָ��Ҫ������ڴ���ͼ��
		k = (k + 1) % 71;

		drawTime();

		Sleep(20);
	}

	closegraph();

	system("pause");
	return 0;
}

