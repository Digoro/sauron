// OculusDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "Oculus.h"
#include "OculusDlg.h"
#include "afxdialogex.h"
#include <evntcons.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


wchar_t path[MAX_PATH + 1];
OSVERSIONINFO osvi;

ULONG status = ERROR_SUCCESS;
ULONG BufferSize = 0;
TRACEHANDLE SessionHandle = 0;

EVENT_TRACE_PROPERTIES* pSessionProperties = NULL;
EVENT_TRACE_LOGFILE* pSessionLogFile = NULL;
EVENT_TRACE* pSession = NULL;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// COculusDlg ��ȭ ����




COculusDlg::COculusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COculusDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// Start thread.
	this->StartTraceSession();
}

void COculusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COculusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// COculusDlg �޽��� ó����

BOOL COculusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void COculusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void COculusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR COculusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COculusDlg::StartThread()
{
	/*
	this->recvThread		= new CWinThread*[devices];

	for (unsigned int i = 0 ; i < devices ; i++)
	{
		this->isThreadRunning[i] = TRUE;

		contarr_ptr[i].layer	= this;
		contarr_ptr[i].d_param	= i;

		this->recvThread[i] = AfxBeginThread(ProcessThread, NULL);
	}
	*/
};

UINT __cdecl ProcessThread(LPVOID param)
{
	return 0;
};

// Enter Ű�� ������ �� ����Ǵ� �޼ҵ�.
void COculusDlg::OnOK()
{
	this->EndTraceSession();
	CDialogEx::OnOK();
}

// ESC Ű�� ������ �� ����Ǵ� �޼ҵ�.
void COculusDlg::OnCancel()
{
	CDialogEx::OnCancel();
}



void COculusDlg::StartTraceSession()
{
	size_t slen = 0;
	

	FILETIME ftime;

    // Allocate memory for the session properties. The memory must
    // be large enough to include the log file name and session name,
    // which get appended to the end of the session properties structure.
    
	SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path);
	StringCbCat(path, MAX_PATH + 1, L"\\log.etl");
	StringCbLength(path, MAX_PATH + 1, &slen);
	slen += sizeof(wchar_t);

	BufferSize = sizeof(EVENT_TRACE_PROPERTIES) + slen + sizeof(KERNEL_LOGGER_NAME);
	pSessionProperties = (EVENT_TRACE_PROPERTIES*) malloc(BufferSize);
	//pSessionLogFile = (EVENT_TRACE_LOGFILE*) malloc(sizeof(EVENT_TRACE_LOGFILE));

    // Set the session properties. You only append the log file name
    // to the properties structure; the StartTrace function appends
    // the session name for you.

	ZeroMemory(pSessionProperties, BufferSize);
	//ZeroMemory(pSessionLogFile, sizeof(EVENT_TRACE_LOGFILE));
	//ZeroMemory(pSession, sizeof(EVENT_TRACE));

	pSessionProperties->Wnode.BufferSize = BufferSize;
	pSessionProperties->Wnode.Flags = WNODE_FLAG_TRACED_GUID;
	//pSessionProperties->Wnode.ClientContext = 1; //QPC clock resolution
	pSessionProperties->Wnode.ClientContext = 2; //System time resolution
	pSessionProperties->Wnode.Guid = SystemTraceControlGuid;

	pSessionProperties->EnableFlags = 0x00030207;
	
	//GetSystemTime

	/*
		(EVENT_TRACE_FLAG_PROCESS | EVENT_TRACE_FLAG_THREAD | EVENT_TRACE_FLAG_IMAGE_LOAD |
			EVENT_TRACE_FLAG_DISK_FILE_IO | EVENT_TRACE_FLAG_NETWORK_TCPIP | EVENT_TRACE_FLAG_REGISTRY);
	*/



	pSessionProperties->LogFileMode = /*EVENT_TRACE_FILE_MODE_SEQUENTIAL | */EVENT_TRACE_REAL_TIME_MODE;
	
	//pSessionProperties->MaximumFileSize = 128;  // 128 MB
	pSessionProperties->LoggerNameOffset = sizeof(EVENT_TRACE_PROPERTIES);
	pSessionProperties->LogFileNameOffset = sizeof(EVENT_TRACE_PROPERTIES) + sizeof(KERNEL_LOGGER_NAME); 
	StringCbCopy((LPWSTR) ((char*) pSessionProperties + pSessionProperties->LogFileNameOffset), slen, path);

	//pSessionLogFile->LoggerName = L"Tracing Test";
	//pSessionLogFile->ProcessTraceMode = PROCESS_TRACE_MODE_REAL_TIME;

	GetSystemTimeAsFileTime(&ftime);
	pSessionProperties->Wnode.TimeStamp.HighPart = ftime.dwHighDateTime;
	pSessionProperties->Wnode.TimeStamp.LowPart = ftime.dwLowDateTime;

    // Create the trace session.

    status = StartTrace((PTRACEHANDLE) &SessionHandle, KERNEL_LOGGER_NAME, pSessionProperties);

	if (ERROR_SUCCESS != status)
    {
        if (ERROR_ALREADY_EXISTS == status)
        {
			/* is already in use */
			MessageBox(L"The NT Kernel Logger session is already in use.\n");
        }
        else
        {
            /* Failed */
			MessageBox(L"EnableTrace() failed with " + status);
        }

        EndTraceSession();
    }

	/*
	status = OpenTrace(pSessionLogFile);
	if (status == INVALID_PROCESSTRACE_HANDLE) MessageBox(L"Error in OpenTrace!");
	*/
};



void COculusDlg::EndThread()
{
	// terminate all threads.
	HANDLE* handles = new HANDLE[devices];

	for (unsigned int i = 0 ; i < devices ; i++)
	{
		this->isThreadRunning[i] = FALSE;
		handles[i] = this->recvThread[i]->m_hThread;
	}
	WaitForMultipleObjects(devices, handles, TRUE, INFINITE);
	delete handles;

	// ���ҽ� ����.
	delete this->isThreadRunning;
	delete this->recvThread;
	//delete contarr_ptr;
};


void COculusDlg::EndTraceSession()
{
	if (SessionHandle)
	{
		status = ControlTrace(SessionHandle, KERNEL_LOGGER_NAME, pSessionProperties, EVENT_TRACE_CONTROL_STOP);

		if (ERROR_SUCCESS != status)
		{
			MessageBox(L"ControlTrace(stop) failed with " + status);
		}
	}

	if (pSessionProperties) free(pSessionProperties);
};