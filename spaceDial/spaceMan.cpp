#include<graphics.h>
#include<stdio.h>
#include"date_tool.h"

IMAGE imgs[71];//太空人图像
IMAGE sz[11];//分钟
IMAGE sz2[10];//秒

void drawDate() {
	char str[16] = "";
	int year, month, day;
	getDate(&year, &month, &day, str);

	setbkcolor(RGB(223, 230, 240));
	settextcolor(RGB(15, 15, 15));      //设置字体颜色
	settextstyle(25, 0, "华文隶书"); //设置字体样式微软雅黑
	outtextxy(70, 0, str); //在指定位置输出文本

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
	//日期
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
	//定义窗口的长和宽
	initgraph(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	HWND hwnd = GetHWnd();
	//SetWindowLong修改窗口属性  GetWindowLong 检索窗口信息
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE - WS_CAPTION));
	//修改窗口为顶层窗口
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);

	//设置窗口为透明效果
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_STYLE) | WS_EX_LAYERED);//设置拓展窗口风格为分层窗口，第三个参数是替换值
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);//设置窗口透明度 LWA_COLORKEY透明方式

	setbkcolor(RGB(0, 0, 0));//设置背景填充颜色
	cleardevice();//使用背景颜色清理窗口
}

void paintLine()
{
	//setorigin(GetSystemMetrics(SM_CXSCREEN - 200), 200);
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 200, 200);
	IMAGE bg;
	loadimage(&bg, "bg3.jpg", 400, 400, true);
	//putimage(0, 0, &bg);
	putimage(-200, -200, &bg);
	setlinecolor(BLACK);//设置线条颜色
	setlinestyle(PS_SOLID, 8);//设置线条格式为实线，宽度为8
	circle(0, 0, 203);
}

void loadPic()
{
	//加载太空人图像，利用for循环
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		//sprintf_s 其函数功能是将数据格式化输出到字符串
		sprintf_s(imgName, sizeof(imgName), "img/human_%04d_图层 %d.jpg", i, 71 - i);
		//loadimage 保存图像的imgs对象指针,图片文件名,图片的拉伸宽度,图片的拉伸高度，是否调整 IMAGE 的大小以适应图片
		loadimage(&imgs[i], imgName, 105, 105, true);
	}

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg", i);
		loadimage(&sz[i], imgName, 40, 70, true);//小时 分钟
		loadimage(&sz2[i], imgName, 20, 35, true);//秒
	}
	loadimage(&sz[10], "img/rect.jpg", 10, 10, true);//:

}
int main()
{
	initWinStyle();
	setorigin(GetSystemMetrics(SM_CXSCREEN - 200), 200);//冲洗你设置坐标原点*很重要的
	paintLine();
	loadPic();
	int k = 0;
	while (true)
	{
		//将一个先前保存在内存中的图像输出到屏幕上
		putimage(-50, -15, &imgs[k]); //buf指向要输出的内存中图像
		k = (k + 1) % 71;

		drawTime();

		Sleep(20);
	}

	closegraph();

	system("pause");
	return 0;
}

