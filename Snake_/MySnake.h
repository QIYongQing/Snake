#pragma once

//***************����
//�ı�����8574��
//��4287������
struct Word
{
	//��ĸ��ע����˼
	CString letter;
	CString note;
};


//һ�����ķ���
struct Case
{
	int C_row;            //���ӵ���
	int C_list;           //���ӵ���
};

//ʳ��
struct Food
{
	int F_row;            //ʳ�����ڵ���
	int F_list;           //ʳ�����ڵ���
	bool HaveEat;         //�Ƿ񱻳���
	char L;               //��ĸ
	Food()
	{
		HaveEat = false;
		L = 0;
	}
};
//*****************************�Զ�Ѱ·
struct AutoPath
{
	int Flag;             //-1��ʾ�ϰ���
	CPoint Cur;        //��ǰ��
	int F;                  //·������
	AutoPath()
	{
		F = 1000;
		Flag = 0;
	}
};

class CMySnake
{
public:
	CMySnake();
	~CMySnake();
public:
	int Snake_len;                //�߳���
	Case Snake_body[1500];        //���������Ϊ1500������
	int direction;                //��ǰ���ķ���
	//1.�� 2.�� 3.�� 4.��
	Case ForwordUp();
	Case ForwordRight();
	Case ForwordDown();
	Case ForwordLeft();
};

