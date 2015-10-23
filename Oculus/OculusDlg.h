// OculusDlg.h : ��� ����
//

#pragma once


// COculusDlg ��ȭ ����
class COculusDlg : public CDialogEx
{
// �����Դϴ�.
public:
	COculusDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	
	/*	Thread-related Method	*/
	void StartThread();
	void EndThread();


	/* Trace Session Method */
	void StartTraceSession();
	void EndTraceSession();


	// ���̾�α��� OnOK �� OnCancel.
	void	OnOK();
	void	OnCancel();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OCULUS_DIALOG };

// �����Դϴ�.
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	// �����带 �����ϴ� ����.
	// �����尡 �����ϱ⸦ ����ϴµ� ����ؾ� �� ���������̴�.
	// new�� �迭�� �Ҵ��� ��.
	CWinThread**	recvThread;
	
	// Thread�� ���¸� ��Ÿ���� �迭�� ����� ������.
	BOOL*			isThreadRunning;

	unsigned int devices;
};
