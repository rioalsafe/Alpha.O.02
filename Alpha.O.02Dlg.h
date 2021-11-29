
// Alpha.O.02Dlg.h: 헤더 파일
//

#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>

// CAlphaO02Dlg 대화 상자
class CAlphaO02Dlg : public CDialogEx
{
// 생성입니다.
public:

	CAlphaO02Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALPHAO02_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	enum { WIDTH = 30, OFFSET = 20, TURNTIME = 30 };//WIDTH (한칸의 간격), OFFSET(바둑판과 메인윈도우사이 간격), TURNTIME(제한시간)
	int step = 0;	//0, 1, 2 (돌이없다, 흑돌, 백돌)
	int dol[19][19] = { 0, }; //바둑판 2차원 배열
	int black_win_count = 0; //흑승리 카운트 ++
	int white_win_count = 0; //백승리 카운트 ++
	int turn; //현재 타이머시간
	int pause_count = 0;	// 0, 1 (타이머동작, 타이머정지)
	CString bWin = _T("BLACK WIN");
	CString wWin = _T("WHITE WIN");
	CString Tie = _T("TIE");

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	void WhoIsWinner(int sum); //승리검정
	void WhoIsLastWinner(void);
	void OnSave(void);	//로그 출력
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedSave();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox m_dol_log;
	CListBox m_timer;
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CListBox m_winner;
	afx_msg void OnBnClickedPause();
};
