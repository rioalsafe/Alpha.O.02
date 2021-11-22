
// Alpha.O.02Dlg.h: 헤더 파일
//

#pragma once


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
	enum { WIDTH = 30, OFFSET = 20 }; 
	int step = 0;
	int dol[19][19] = { 0, };
	

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	void WhoIsWinner(int sum);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

};
