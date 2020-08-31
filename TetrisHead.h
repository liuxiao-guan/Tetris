#ifndef TETRI_SHEAD
#define TETRI_SHEAD
#include <Windows.h>
#include <time.h>
#include <sys/timeb.h>
#include <random>
#define DEF_TIMER 1234
#define HEIGHT 600
#define WIDTH 790
#define VK_S  0X53 
#define VK_A  0X41 
#define VK_D  0X44
#define VK_W  0X57

class gBackGroud {
private:
	int x;//整个背景的起始横坐标
	int y;//整个背景的起始纵坐标
	int key1 = 1;//用来判断是否要产生新的方块
	int locationx = 0;//在分数显示栏中方块的横坐标
	int locationy = 0;//在分数显示栏中方块的纵坐标
	unsigned int nIndex = 0;//随机产生的索引值
	char g_nSquare = -1;//各个方块的标号
	char g_nLine = -1;//旋转时矩阵的初行
	char g_nList = -1;//旋转时矩阵的初列
	char g_arryBackGroud[20][10] = { 0 };//背景数组
	char g_nScore = 0;//分数
	char g_arrySquare[2][4] = { 0 };//方块形成的数组
public:
	gBackGroud(int x, int y,int locationx, int locationy) :x(x), y(y),locationx(locationx), locationy(locationy) {};
	//获取或者改变一些变量
	int getX() { return x; }
	int getY() { return y; }
	void setkey1_0() { key1 = 0; return; }
	void setkey1_1() { key1 = 1; return; }
	int get_g_nSquare() { return g_nSquare; }//各个方块的标号
	void getg_nLineplus() { g_nLine++; return; }
	void getg_nListplus() { g_nList++; return; }
	void getg_nListreduce() { g_nList--; return; }
	char getg_nScore() { return g_nScore; }
	char* get_g_arryBackGroud() { return *g_arryBackGroud; }

	//按键消息
	void OnLeft(HWND hWnd);
	void OnRight(HWND hWnd);
	void OnChangeSquare(HWND hWnd);
	
	//方块移动与变形
	void Squaredown();//方块下落
	void Squareleft();//方块左移
	void Squareright();//方块右移
	void ChangeSquare();//旋转前五种方块
	void ChangeLineSquare();//判断并旋转长条形方块，
	int CreatRandomSquare();//随机产生方块

	//判断方块运动与变形的条件 return 1 可以，return 0，不可以
	int CanSquareDown();//判断方块是否可以停止下落，到底的情况
	int CanSquareLeft();//判断方块是否触碰边界
	int CanSquareLeft1();//判断方块左边是否有方块
	int CanSquareRight();//判断方块右边是否触碰边界
	int CanSquareRight1();//判断方块右边是否有方块
	int CanSquareChange();//前五种方块在旋转时是否触碰到边界，是否有其他方块

	//其他一些操作
	void Change1to2();//把落到底的方块变成2值
	void ShowSquare2(HDC HMemDC,int red,int green,int blue);// 显示值为2的方块
	void PaintSquare(HDC HMemDC);//显示方块
	void ShowNextSquare(HDC HMemDC, int red, int green, int blue);//显示下一个方块
	void CopySquareToBack();//将随机产生的方块贴到背景上，但没有显示
	void DestroyOneLine();//消除一行
	int CanGameOver(HWND hWnd);//判断游戏是否可以结束
};
	void onPaint(HDC hDC);//在纸上画好，并且传递给窗口
	void OnCreate();//初始化窗口消息
	//定时器消息，即按键消息
	void OnReturn(HWND hWnd);//按键return消息,创建定时器
	void OnTimer1(HWND hWnd);//定时器响应消息,方块下移并显示
	void OnTimer2(HWND hWnd);
	void OnDown1(HWND hWnd);
	void OnDown2(HWND hWnd);
	void ShowScore(HDC HMemDC);//显示分数
#endif // !1

