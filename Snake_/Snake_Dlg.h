
// Snake_Dlg.h : ͷ�ļ�
//

#pragma once

#include "MySnake.h"
#include "afxwin.h"
#include<stack>

// CSnake_Dlg �Ի���
class CSnake_Dlg : public CDialogEx
{
// ����
public:
	CSnake_Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SNAKE__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool m_start;
	//*********************��ʼ��ͣ
	int StartPause;
	afx_msg void OnStart();
	//�ļ�·��
	CString m_path;
	//�����
	CMySnake m_snake;
	//���ʳ��,��ֹһ��ʳ��
	Food* m_bean;
	//���ɵĶ����Ƿ�������
	bool IsInBody(int i);
	//�Ե�������
	bool EatBean();
	//��Ϸ����
	bool GameOver();
	//ײ�����Լ�
	bool HeadBody();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ����
	int m_mark;
	int m_markCopy;
	int m_highest;
	int m_life;
	// ��Ϸ�Ѷ�
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	int m_rank;
	//**********************�浥��
	Word* m_word;
	afx_msg void OnClose();
	//**********************���ӵĳ���
	int Bean_len;
	CString Letter;
	//******************���ӵ����껥����ͬ
	bool Bean_same(int i);
	CString m_FoodLetter;
	CString m_FoodNote;
	// �ؿ�
	int m_pass;
	//*********************����
	bool Pass();
	//******************����±꣬�Ƿ�Դ���
	int m_index;
	int TempDex;
	//********************�Ƿ�Ե�����ȷ�Ķ���
	bool EatRight();
	//********************�ߵĿ���������һ����
	CMySnake m_snakeCopy;
	//*********************��ս��沢������
	void ClearAndBean();
	afx_msg void OnMusic();
	//************************�������ֵĽ���
	HANDLE hThread;
	DWORD ThreadID;
	afx_msg void OnEndMusic();
	//*********************�Զ�Ѱ·�ĺ���
	void FindPath();
	BOOL m_AutoPath;
	void Voice(CString&);
};
//�����Ķ���
void ThreadFunc();