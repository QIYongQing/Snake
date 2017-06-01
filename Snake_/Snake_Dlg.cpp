
// Snake_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Snake_.h"
#include "Snake_Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <Windows.h>
#include "Resource.h"
#include<fstream>
#include <Vfw.H>
#include<cmath>
#include <mmsystem.h>
#include "sapi.h"
#include "sphelper.h"
#pragma comment(lib, "sapi.lib")
#pragma comment(lib, "WINMM.LIB") 
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSnake_Dlg �Ի���


//���캯��
CSnake_Dlg::CSnake_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSnake_Dlg::IDD, pParent)
	, m_mark(0)
	, m_life(4)
	, m_rank(1)
	, m_pass(1)
	, m_index(0)
	, m_markCopy(0)
	, m_AutoPath(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_start = false;
	//�ߵĳ�ʼ��
	m_snake.Snake_len = 4;       //��4
	m_snake.direction = 2;       //����
	m_snake.Snake_body[0].C_row = 2; m_snake.Snake_body[0].C_list = 8;
	m_snake.Snake_body[1].C_row = 2; m_snake.Snake_body[1].C_list = 7;
	m_snake.Snake_body[2].C_row = 2; m_snake.Snake_body[2].C_list = 6;
	m_snake.Snake_body[3].C_row = 2; m_snake.Snake_body[3].C_list = 5;
	m_snakeCopy = m_snake;
	//**********��¼
	ifstream fin("̰�����ز�\\��¼.txt", ios::in);
	int t;
	fin >> t;
	m_highest = t;
	fin.close();
	//***************************��������
	m_word = new Word[4287];
	ifstream FileIn("̰�����ز�\\2010���ѧӢ���ļ��ʻ�.txt",ios::in);
	char a[100] = {0};
	char b[100] = {0};
	int i = 0;
	while (!FileIn.eof())
	{
		FileIn.getline(a,100);
		FileIn.getline(b, 100);
		m_word[i].letter = a;
		m_word[i].note = b;
		i++;
	}
	FileIn.close();
	//************************************
	srand(time(NULL));
	int R = rand() % 4287;        //����ҵ������±�
    Letter = m_word[R].letter;
	int len = Letter.GetLength();
	//***************************��ʾ�ڱ༭��
	m_FoodLetter = Letter;
	m_FoodNote = m_word[R].note;
	//************************����һ�¶���
	Bean_len = len;
	m_bean = new Food[len];
	//************************��ʼ�����ӵ�����
	for (int i = 0; i < len; i++)
	{
		do
		{
			m_bean[i].L = Letter[i];        //���浥��
			m_bean[i].F_row = rand() % 25;
			m_bean[i].F_list = rand() % 25;
		} while (this->IsInBody(i)||this->Bean_same(i));
	}
}

void CSnake_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_mark);
	DDX_Text(pDX, IDC_EDIT2, m_highest);
	DDX_Text(pDX, IDC_EDIT3, m_life);
	DDX_Radio(pDX, IDC_RADIO1, m_rank);
	DDX_Text(pDX, IDC_EDIT4, m_FoodLetter);
	DDX_Text(pDX, IDC_EDIT5, m_FoodNote);
	DDX_Text(pDX, IDC_EDIT6, m_pass);
	DDX_Check(pDX, IDC_CHECK1, m_AutoPath);
}

BEGIN_MESSAGE_MAP(CSnake_Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSnake_Dlg::OnStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO1, &CSnake_Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSnake_Dlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSnake_Dlg::OnBnClickedRadio3)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &CSnake_Dlg::OnMusic)
	ON_BN_CLICKED(IDC_BUTTON3, &CSnake_Dlg::OnEndMusic)
END_MESSAGE_MAP()


// CSnake_Dlg ��Ϣ�������

BOOL CSnake_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_path = _T("̰�����ز�\\");
	StartPause = 1;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSnake_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSnake_Dlg::OnPaint()
{
	//��ʼ����Ϸ����
	CPaintDC pDC(this);
	//������
	CBitmap Bitmap;
	Bitmap.LoadBitmapW(IDB_BITMAP2);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&pDC);
	MemDC.SelectObject(&Bitmap);
	Bitmap.Detach();             //���룬�����´�ʹ��
	//********************************������ 20*20�ĸ���
	for (int i = 0; i < 25; i++)
	for (int j = 0; j < 25; j++)
	{
		pDC.StretchBlt(20 * i, 20 * j, 20, 20, &MemDC, 0, 0, 48, 48, SRCCOPY);
	}
	//*******************************************����ͷ
	Bitmap.LoadBitmapW(IDB_BITMAP3);
	MemDC.SelectObject(&Bitmap);
	pDC.StretchBlt(20 * m_snake.Snake_body[0].C_list,20 * m_snake.Snake_body[0].C_row, 20, 20, &MemDC, 0, 0, 48, 48, SRCCOPY);
	Bitmap.Detach();
	//*******************************************������
	Bitmap.LoadBitmapW(IDB_BITMAP4);
	MemDC.SelectObject(&Bitmap);
	for (int i = 1; i < m_snake.Snake_len; i++)
		pDC.StretchBlt(20 * m_snake.Snake_body[i].C_list,20 * m_snake.Snake_body[i].C_row, 20, 20, &MemDC, 0, 0, 48, 48, SRCCOPY);
	Bitmap.Detach();
	//*******************************************����
	if (::LoadImage(NULL, m_path + L"a.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION) == false)
	{
		MessageBox(_T("δ�ҵ�ָ���زģ������ز��Ƿ���ָ��λ�ã�"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	//******************************************С�ж�һ��
	//**********��������
	for (int i = 0; i <Bean_len ; i++)
	{
		//***********************************************����
		HBITMAP hbmp = (HBITMAP)::LoadImage(NULL, m_path + (CString)Letter[i] +L".bmp", 
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Bitmap.Attach(hbmp);
		BITMAP temp;
		Bitmap.GetBitmap(&temp);
		MemDC.SelectObject(&Bitmap);
		pDC.StretchBlt(20 * m_bean[i].F_list, 20 * m_bean[i].F_row, 20, 20, &MemDC, 0, 0,temp.bmWidth, temp.bmHeight, SRCCOPY);
		Bitmap.Detach();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSnake_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSnake_Dlg::OnStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (StartPause % 2 == 0)
		m_start = false;
	else
		m_start = true;
	StartPause++;
	//����һ����ʱ��
	if (m_rank==0)
		SetTimer(1, 200, NULL);
	else if (m_rank==1)
		SetTimer(1, 100, NULL);
	else
		SetTimer(1, 50, NULL);
	//this->Voice(Letter);
}

//*********************���ɵĶ����Ƿ�������,�ڶ�����Ҳ����
bool CSnake_Dlg::IsInBody(int i)
{
	//���ӵ��е��������Ҷ��ӵ��е�������,���Ҳ��������ͷ��ǰһ��
	for (int j = 0; j < m_snake.Snake_len; j++)
	if (m_bean[i].F_row == m_snake.Snake_body[j].C_row&&m_bean[i].F_list == m_snake.Snake_body[j].C_list)
	{
		return true;
	}
	if (m_bean[i].F_row == 2 && m_bean[i].F_list == 9)
		return true;
	return false;
}
//**********************�ڶ�����Ҳ����
bool CSnake_Dlg::Bean_same(int i)
{
	for (int j = 0; j < i; j++)
	{
		if ((m_bean[i].F_list == m_bean[j].F_list&&m_bean[i].F_row == m_bean[j].F_row))
			return true;
	}
	return false;
}

//*********************************�Ե������ˣ��Դ��ӣ�����-1
bool  CSnake_Dlg::EatBean()
{
	for (int i = 0; i < Bean_len;i++)
	if (m_snake.Snake_body[0].C_row == m_bean[i].F_row&&m_snake.Snake_body[0].C_list == m_bean[i].F_list&&m_bean[i].HaveEat==false)
	{
		//*******************����i����ǰ�Ե������ĸ�����
		TempDex = i;
		return true;
	}
	return false;
}
//******************************�Ե���ȷ�Ķ���
bool CSnake_Dlg::EatRight()
{
	if (m_bean[TempDex].L==Letter[m_index])
	{
		m_bean[TempDex].HaveEat = true;
		m_index++;
		return true;
	}
	else
		return false;
}
//********************************��Ϸ������
bool  CSnake_Dlg::GameOver()
{
	//ע��ǽ��0��25�����ӣ�ײǽ��
	if (m_snake.Snake_body[0].C_row <0 || m_snake.Snake_body[0].C_row >=25
		|| m_snake.Snake_body[0].C_list <0 || m_snake.Snake_body[0].C_list >= 25)
		return true;
	//�����Լ�ײ�����Լ�
	if (HeadBody() == true)
		return true;
	return false;
}
//*********************************����
bool  CSnake_Dlg::Pass()
{
	for (int i = 0; i < Bean_len; i++)
	if (m_bean[i].HaveEat == false)
		return false;
	return true;
}
//********************************�Լ�ײ�����Լ�
bool CSnake_Dlg::HeadBody()
{
	for (int i = 1; i < m_snake.Snake_len; i++)
	if (m_snake.Snake_body[0].C_row == m_snake.Snake_body[i].C_row&&m_snake.Snake_body[0].C_list == m_snake.Snake_body[i].C_list)
	{
		return true;
	}
	return false;
}

void CSnake_Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	if (m_start == true)
	{
		Case CaseTemp;
		CClientDC dc(this);
		CBitmap Bitmap;
		CDC dcMemory;
		dcMemory.CreateCompatibleDC(&dc);
		switch (m_snake.direction)
		{
		case 1:              //��
			CaseTemp = m_snake.ForwordUp();
			break;
		case 2:              //��
			CaseTemp = m_snake.ForwordRight();
			break;
		case 3:              //��
			CaseTemp = m_snake.ForwordDown();
			break;
		case 4:              //��
			CaseTemp = m_snake.ForwordLeft();
			break;
		}
		//********************
		//if (m_pass > 5)
		//{
		//	m_start = false;
		//	MessageBox(_T("��ͨ�أ�"), _T("��ϲ"), MB_OK);
		//	if (m_mark > m_highest)
		//	{
		//		MessageBox(_T("��ˢ�¼�¼!"), _T("��ʾ"), MB_OK);
		//		ofstream fout("̰�����ز�\\��¼.txt", ios::out);
		//		fout << m_mark;
		//		fout.close();
		//		m_highest = m_mark;
		//	}
		//	UpdateData(false);
		//}
		if (GameOver() == true)
		{
			m_start = false;
			m_life--;
			UpdateData(false);
			//*****************����ֵ����
			if (m_life <= 0)
			{
				if (MessageBox(_T("Game over!���Ƿ������Ϸ��"), _T("�ź�"), MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)
				{
					CString str;
					str = "GAME OVER!!!";
					CFont font;
					font.CreateFont(60, 30, 0, 0, FW_THIN, 0, 0, 0, DEFAULT_CHARSET, OUT_STROKE_PRECIS, CLIP_STROKE_PRECIS, DRAFT_QUALITY, FIXED_PITCH | FF_MODERN, LPCTSTR(str));
					dc.SetTextColor(RGB(0, 200, 0));
					dc.SelectObject(&font);
					dc.TextOut(162, 200, str);
					GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
					return;
				}
				m_life += 4;
				UpdateData(false);
			}
			MessageBox(_T("������1���������¿�ʼ"), _T("��ʾ"), MB_OK);
			m_index = 0;
			m_snake = m_snakeCopy;
			this->ClearAndBean();
		}
		//*******************************ͨ���ˣ�
		if (this->Pass() == true)
		{
			m_start = false;
			m_snake = m_snakeCopy;
			m_pass++;
			UpdateData(false);
			MessageBox(_T("��ϲ���أ�"), _T("��ʾ"), MB_OK);
			//***********ԭ���Ķ��Ӳ�Ҫ��
			delete[]m_bean;
			srand(time(NULL));
			int R = rand() % 4287;        //����ҵ������±�
			Letter = m_word[R].letter;
			int len = Letter.GetLength();
			//***************************��ʾ�ڱ༭��
			m_FoodLetter = Letter;
			m_FoodNote = m_word[R].note;
			UpdateData(false);
			//************************����һ�¶��ӵĳ���
			Bean_len = len;
			m_bean = new Food[len];
			//************************��ʼ�����ӵ�����
			for (int i = 0; i < len; i++)
			{
				do
				{
					m_bean[i].L = Letter[i];
					m_bean[i].F_row = rand() % 25;
					m_bean[i].F_list = rand() % 25;
				} while (this->IsInBody(i) || this->Bean_same(i));
			}
			//**************************�ѻ������һ��
			m_index = 0;
			m_snake = m_snakeCopy;
			this->ClearAndBean();
		}
		//**************************�Զ�Ѱ·
		if (m_AutoPath==true)
			this->FindPath();
		//************************���߳Ե�����
		if (this->EatBean() == true)
		{
			if (EatRight() == true)
			{
				m_mark += 100;
				m_markCopy += 100;
				if (m_markCopy >= 1000)
				{
					m_start = false;
					MessageBox(_T("��������һ����"), _T("��ʾ"), MB_OK);
					m_life++;
					m_start = true;
					m_markCopy -= 1000;
				}
				//����+1
				m_snake.Snake_len++;
				//����仯
				m_snake.Snake_body[m_snake.Snake_len - 1].C_row = CaseTemp.C_row;
				m_snake.Snake_body[m_snake.Snake_len - 1].C_list = CaseTemp.C_list;
			}
			//********************************�Դ�����,����-1,��������
			else if (EatRight() == false)
			{
				m_life--;
				m_start = false;
				MessageBox(_T("�Դ���ĸ������ֵ��1������������"), _T("��ʾ"), MB_OK);
				m_index = 0;
				m_snake = m_snakeCopy;
				//**************************�ѻ������һ��
				this->ClearAndBean();
			}
			UpdateData(false);
		}
		//******************************������β
		Bitmap.LoadBitmapW(IDB_BITMAP2);
		dcMemory.SelectObject(&Bitmap);
		dc.StretchBlt(20 * CaseTemp.C_list, 20 * CaseTemp.C_row, 20, 20, &dcMemory, 0, 0,48, 48, SRCCOPY);
		Bitmap.Detach();
		//********************************����ͷ
		Bitmap.LoadBitmapW(IDB_BITMAP3);
		dcMemory.SelectObject(&Bitmap);
		dc.StretchBlt(20 * m_snake.Snake_body[0].C_list, 20 * m_snake.Snake_body[0].C_row, 20, 20, &dcMemory, 0, 0, 48, 48, SRCCOPY);
		Bitmap.Detach();
		//**********************************����
		Bitmap.LoadBitmapW(IDB_BITMAP4);
		dcMemory.SelectObject(&Bitmap);
		for (int i = 1; i < m_snake.Snake_len; i++)
			dc.StretchBlt(20 * m_snake.Snake_body[i].C_list,20 * m_snake.Snake_body[i].C_row, 20, 20, &dcMemory, 0, 0, 48, 48, SRCCOPY);
		Bitmap.Detach();
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CSnake_Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN != pMsg->message)
		return CWnd::PreTranslateMessage(pMsg);
	if (pMsg->message==WM_KEYDOWN)
	{
		//*********�����Զ�Ѱ·��Ͳ��ü�����
		if (m_AutoPath == true)
			return true;
		if (m_start == false)
			return false;
		//���� w
		if ((pMsg->wParam=='W') && m_snake.direction != 3)
		{
			m_snake.direction = 1;
		}
		//���� s
		if ((pMsg->wParam=='S') && m_snake.direction != 1)
		{
			m_snake.direction = 3;
		}
		//���� a
		if ((pMsg->wParam=='A') && m_snake.direction != 2)
		{
			m_snake.direction = 4;
		}
		//���� d
		if ((pMsg->wParam=='D') && m_snake.direction != 4)
		{
			m_snake.direction = 2;
		}
	}
	return true;
}


void CSnake_Dlg::OnBnClickedRadio1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetTimer(1, 200, NULL);
	m_rank = 0;
}


void CSnake_Dlg::OnBnClickedRadio2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetTimer(1, 100, NULL);
	m_rank = 1;
}


void CSnake_Dlg::OnBnClickedRadio3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SetTimer(1, 50, NULL);
	m_rank = 2;
}

//***************************д��������
void CSnake_Dlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_mark > m_highest)
	{
		ofstream fout("̰�����ز�\\��¼.txt", ios::out);
		fout << m_mark;
		fout.close();
	}
	delete[]m_word;
	delete[]m_bean;
	CDialogEx::OnClose();
}
//***************************��ս��沢������
void  CSnake_Dlg::ClearAndBean()
{
	//******************************��Ҫ
	for (int i = 0; i < Bean_len; i++)
		m_bean[i].HaveEat = false;
	CClientDC pDC(this);
	//������
	CBitmap Bitmap;
	Bitmap.LoadBitmapW(IDB_BITMAP2);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&pDC);
	MemDC.SelectObject(&Bitmap);
	Bitmap.Detach();             //���룬�����´�ʹ��
	for (int i = 0; i < 25; i++)
	for (int j = 0; j < 25; j++)
	{
		pDC.StretchBlt(20 * i, 20 * j, 20, 20, &MemDC, 0, 0, 48, 48, SRCCOPY);
	}
	Bitmap.Detach();
	this->OnPaint();
	//**********��������
	for (int i = 0; i < Bean_len; i++)
	{
		//***********************************************����
		HBITMAP hbmp = (HBITMAP)::LoadImage(NULL, m_path +
			(CString)Letter[i] + L".bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		Bitmap.Attach(hbmp);
		BITMAP temp;
		Bitmap.GetBitmap(&temp);
		MemDC.SelectObject(&Bitmap);
		pDC.StretchBlt(20 * m_bean[i].F_list, 20 * m_bean[i].F_row, 20, 20, &MemDC, 0, 0, temp.bmWidth, temp.bmHeight, SRCCOPY);
		Bitmap.Detach();
	}
}

void CSnake_Dlg::OnMusic()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��������
	hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)ThreadFunc,
		NULL,
		0,
		&ThreadID);
}

void ThreadFunc()
{
	PlaySound(L"̰�����ز�\\����.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


void CSnake_Dlg::OnEndMusic()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	PlaySound(NULL, NULL, NULL);
}
//****************************�Զ�Ѱ·�ĺ���
void CSnake_Dlg::FindPath()
{
	AutoPath Point[25][25];       //����ĸ���
	for (int i = 0; i < 25; i++)
	for (int j = 0; j < 25; j++)
	{
		Point[i][j].Cur = CPoint(i, j);
	}
	//*************������Ϊ�ϰ���
	for (int i = 0; i < m_snake.Snake_len; i++)
	{
		Point[m_snake.Snake_body[i].C_list][m_snake.Snake_body[i].C_row].Flag = -1;
	}
	//**************��ʼ�㣬��ֹ��
	AutoPath P_start, P_end;
	P_start = Point[m_snake.Snake_body[0].C_list][m_snake.Snake_body[0].C_row];
	//***************�ر����е��ʣ�ֻ������ǰ����
	for (int i = 0; i < Letter.GetLength(); i++)
	{
		//************���û�б��ԣ����ϰ��ﴦ��
		if (m_bean[i].HaveEat==false)
			Point[m_bean[i].F_list][m_bean[i].F_row].Flag = -1;
	}
	Point[m_bean[m_index].F_list][m_bean[m_index].F_row].Flag = 0;
	P_end = Point[m_bean[m_index].F_list][m_bean[m_index].F_row];
	//*********************************************** 
	AutoPath* temp = &P_start;
	//************���ڵ��ĸ�����
	AutoPath* Other = new AutoPath[4];
	Other[0] = Point[temp->Cur.x][temp->Cur.y - 1];
	Other[1] = Point[temp->Cur.x][temp->Cur.y + 1];
	Other[2] = Point[temp->Cur.x - 1][temp->Cur.y];
	Other[3] = Point[temp->Cur.x + 1][temp->Cur.y];
	for (int i = 0; i < 4; i++)
	{
		if (Other[i].Flag == -1)
			continue;
		else
		{
			int t = abs(Other[i].Cur.x - P_end.Cur.x) + abs(Other[i].Cur.y - P_end.Cur.y);
			Other[i].F = t;
		}
	}
	//***********�ҳ��������
	AutoPath Tem;
	for (int i = 0; i < 4; i++)
	if (Tem.F>Other[i].F)
		Tem = Other[i];
	CPoint p = Tem.Cur;
	//*************************�ҳ�·��
	if (m_snake.Snake_body[0].C_row+1== p.y)
		m_snake.direction = 3;       //����
	else if (m_snake.Snake_body[0].C_row-1 == p.y)
		m_snake.direction = 1;        //����
	else if (m_snake.Snake_body[0].C_list+1 == p.x)
		m_snake.direction = 2;        //����
	else if (m_snake.Snake_body[0].C_list-1 == p.x)
		m_snake.direction = 4;        //����
	delete[]Other;
}

//*************************����
void CSnake_Dlg::Voice(CString&find)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ISpVoice *pSpVoice;        // ��ҪCOM�ӿ�
	::CoInitialize(NULL);         // COM��ʼ��
	// ��ȡISpVoice�ӿ�
	CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER, IID_ISpVoice, (void**)&pSpVoice);
	pSpVoice->SetVolume(60);
	pSpVoice->Speak(find, SPF_DEFAULT, NULL);
	pSpVoice->Release();
	::CoUninitialize();
}