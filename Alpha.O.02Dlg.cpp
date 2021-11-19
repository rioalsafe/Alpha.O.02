
// Alpha.O.02Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Alpha.O.02.h"
#include "Alpha.O.02Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAlphaO02Dlg 대화 상자



CAlphaO02Dlg::CAlphaO02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ALPHAO02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlphaO02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlphaO02Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CAlphaO02Dlg 메시지 처리기

BOOL CAlphaO02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.



void CAlphaO02Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic()) {} // 내 어플리케이션이 최소화 되었을 때 이렇게 처리하겠다는 조건문. 지금은 사용 X. 생략! 	} 
	else
	{

		CBrush MyBrush(RGB(248, 207, 143)); dc.SelectObject(&MyBrush);
		//설정한 색으로 사각형 영역 그리기 dc.Rectangle(10, 10, 10 + 20 * 9, 10 + 20 * 9)

		//CDialogEx::OnPaint(); 주석처리해준다!

		for (int x = 0; x < 18; x++)
		{
			for (int y = 0; y < 18; y++)
			{
				dc.Rectangle(
					OFFSET + x * WIDTH,
					OFFSET + y * WIDTH,
					OFFSET + WIDTH + 1 + x * WIDTH,
					OFFSET + WIDTH + 1 + y * WIDTH
				);
			}
		}

		dc.SelectStockObject(DC_BRUSH);
		for (int x = 0; x < 19; x++)
		{
			for (int y = 0; y < 19; y++)
			{
				if (dol[y][x]) // 0이면 그리지 않는다.
				{
					dc.SetDCBrushColor(0x00FFFFFF * (dol[y][x] - 1)); // +1한 값을 저장했으니 다시 -1을 하여 step값을 복구한다.
					dc.Ellipse(x * WIDTH + OFFSET - (WIDTH / 2), y * WIDTH + OFFSET - (WIDTH / 2), x * WIDTH + WIDTH + OFFSET - (WIDTH / 2), y * WIDTH + WIDTH + OFFSET - (WIDTH / 2));
				}
			}
		}
	}
}


void CAlphaO02Dlg::WhoIsWinner(int sum)
{
	if (sum == 10) AfxMessageBox(L"백돌 승리");
	else if (sum == 5) AfxMessageBox(L"흑돌 승리");

	// 승리 판정이 끝나면 화면이 모두 지워지고, 돌의 값이 들어있는 배열도 초기화하여 다음 게임을 진행할 수 있도록 했다. 
	RECT r;
	GetClientRect(&r);
	InvalidateRect(&r, NULL);
	memset(dol, 0, 4 * 19 * 19);
}


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAlphaO02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlphaO02Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CClientDC dc(this);

	int index_x = (point.x - OFFSET + (WIDTH / 2)) / WIDTH;
	int index_y = (point.y - OFFSET + (WIDTH / 2)) / WIDTH;

	if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0 && dol[index_y][index_x] == 0) {
		if (index_x < 19 && index_y < 19 && index_x >= 0 && index_y >= 0)
		{
			dc.SelectStockObject(DC_BRUSH);
			dc.SetDCBrushColor(step * 0x00FFFFFF);
			dc.Ellipse(
				index_x * WIDTH - (WIDTH / 2) + OFFSET,
				index_y * WIDTH - (WIDTH / 2) + OFFSET,
				index_x * WIDTH - (WIDTH / 2) + OFFSET + WIDTH,
				index_y * WIDTH - (WIDTH / 2) + OFFSET + WIDTH
			);

			dol[index_y][index_x] = step + 1; // 검은돌이면 0 + 1 , 흰돌이면 1+1 이 들어가게됨.
			step = !step;
		}

		if (dol[index_y][index_x] != 0) // 돌을 놓았을 때만 검사하도록!
		{
			for (int i = 0; i < 5; i++)
			{
				int sum = 0, j = 0;
				for (j = 0; j < 5; j++)
				{
					sum += dol[index_y - 4 + i + j][index_x - 4 + i + j];
					if (dol[index_y - 4 + i + j][index_x - 4 + i + j] == 0) break;
				}
				if (j == 5 && sum == 5) WhoIsWinner(sum);
				else if (sum == 10) WhoIsWinner(sum);
			}
			for (int i = 0; i < 5; i++)
			{
				int sum = 0, j = 0;
				for (j = 0; j < 5; j++)
				{
					sum += dol[index_y + 4 - i - j][index_x - 4 + i + j];
					if (dol[index_y + 4 - i - j][index_x - 4 + i + j] == 0) break;
				}
				//if (j == 5 && sum == 5) AfxMessageBox(L"흑돌 승리");
				if (j == 5 && sum == 5) WhoIsWinner(sum);
				else if (sum == 10) WhoIsWinner(sum);
			}
			for (int i = 0; i < 5; i++)
			{
				int sum = 0, j = 0;
				for (j = 0; j < 5; j++)
				{
					sum += dol[index_y][index_x - 4 + i + j];
					if (dol[index_y][index_x - 4 + i + j] == 0) break;
				}
				//if (j == 5 && sum == 5) AfxMessageBox(L"흑돌 승리");
				if (j == 5 && sum == 5) WhoIsWinner(sum);
				else if (sum == 10) WhoIsWinner(sum);
			}
			for (int i = 0; i < 5; i++)
			{
				int sum = 0, j = 0;
				for (j = 0; j < 5; j++)
				{
					sum += dol[index_y + 4 - i - j][index_x];
					if (dol[index_y + 4 - i - j][index_x] == 0) break;
				}
				if (j == 5 && sum == 5) WhoIsWinner(sum);
				else if (sum == 10) WhoIsWinner(sum);
			}
		}

		CDialogEx::OnLButtonDown(nFlags, point);
	}
}

