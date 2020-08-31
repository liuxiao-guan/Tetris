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
	int x;//������������ʼ������
	int y;//������������ʼ������
	int key1 = 1;//�����ж��Ƿ�Ҫ�����µķ���
	int locationx = 0;//�ڷ�����ʾ���з���ĺ�����
	int locationy = 0;//�ڷ�����ʾ���з����������
	unsigned int nIndex = 0;//�������������ֵ
	char g_nSquare = -1;//��������ı��
	char g_nLine = -1;//��תʱ����ĳ���
	char g_nList = -1;//��תʱ����ĳ���
	char g_arryBackGroud[20][10] = { 0 };//��������
	char g_nScore = 0;//����
	char g_arrySquare[2][4] = { 0 };//�����γɵ�����
public:
	gBackGroud(int x, int y,int locationx, int locationy) :x(x), y(y),locationx(locationx), locationy(locationy) {};
	//��ȡ���߸ı�һЩ����
	int getX() { return x; }
	int getY() { return y; }
	void setkey1_0() { key1 = 0; return; }
	void setkey1_1() { key1 = 1; return; }
	int get_g_nSquare() { return g_nSquare; }//��������ı��
	void getg_nLineplus() { g_nLine++; return; }
	void getg_nListplus() { g_nList++; return; }
	void getg_nListreduce() { g_nList--; return; }
	char getg_nScore() { return g_nScore; }
	char* get_g_arryBackGroud() { return *g_arryBackGroud; }

	//������Ϣ
	void OnLeft(HWND hWnd);
	void OnRight(HWND hWnd);
	void OnChangeSquare(HWND hWnd);
	
	//�����ƶ������
	void Squaredown();//��������
	void Squareleft();//��������
	void Squareright();//��������
	void ChangeSquare();//��תǰ���ַ���
	void ChangeLineSquare();//�жϲ���ת�����η��飬
	int CreatRandomSquare();//�����������

	//�жϷ����˶�����ε����� return 1 ���ԣ�return 0��������
	int CanSquareDown();//�жϷ����Ƿ����ֹͣ���䣬���׵����
	int CanSquareLeft();//�жϷ����Ƿ����߽�
	int CanSquareLeft1();//�жϷ�������Ƿ��з���
	int CanSquareRight();//�жϷ����ұ��Ƿ����߽�
	int CanSquareRight1();//�жϷ����ұ��Ƿ��з���
	int CanSquareChange();//ǰ���ַ�������תʱ�Ƿ������߽磬�Ƿ�����������

	//����һЩ����
	void Change1to2();//���䵽�׵ķ�����2ֵ
	void ShowSquare2(HDC HMemDC,int red,int green,int blue);// ��ʾֵΪ2�ķ���
	void PaintSquare(HDC HMemDC);//��ʾ����
	void ShowNextSquare(HDC HMemDC, int red, int green, int blue);//��ʾ��һ������
	void CopySquareToBack();//����������ķ������������ϣ���û����ʾ
	void DestroyOneLine();//����һ��
	int CanGameOver(HWND hWnd);//�ж���Ϸ�Ƿ���Խ���
};
	void onPaint(HDC hDC);//��ֽ�ϻ��ã����Ҵ��ݸ�����
	void OnCreate();//��ʼ��������Ϣ
	//��ʱ����Ϣ����������Ϣ
	void OnReturn(HWND hWnd);//����return��Ϣ,������ʱ��
	void OnTimer1(HWND hWnd);//��ʱ����Ӧ��Ϣ,�������Ʋ���ʾ
	void OnTimer2(HWND hWnd);
	void OnDown1(HWND hWnd);
	void OnDown2(HWND hWnd);
	void ShowScore(HDC HMemDC);//��ʾ����
#endif // !1

