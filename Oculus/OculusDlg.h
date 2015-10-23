// OculusDlg.h : 헤더 파일
//

#pragma once


// COculusDlg 대화 상자
class COculusDlg : public CDialogEx
{
// 생성입니다.
public:
	COculusDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	
	/*	Thread-related Method	*/
	void StartThread();
	void EndThread();


	/* Trace Session Method */
	void StartTraceSession();
	void EndTraceSession();


	// 다이얼로그의 OnOK 및 OnCancel.
	void	OnOK();
	void	OnCancel();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OCULUS_DIALOG };

// 구현입니다.
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// 스레드를 저장하는 변수.
	// 스레드가 종료하기를 대기하는데 사용해야 할 참조변수이다.
	// new로 배열을 할당할 것.
	CWinThread**	recvThread;
	
	// Thread의 상태를 나타내는 배열로 사용할 포인터.
	BOOL*			isThreadRunning;

	unsigned int devices;
};
