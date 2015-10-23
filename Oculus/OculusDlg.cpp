// OculusDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// COculusDlg 대화 상자




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


// COculusDlg 메시지 처리기

BOOL COculusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void COculusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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

// Enter 키를 눌렀을 때 실행되는 메소드.
void COculusDlg::OnOK()
{
	this->EndTraceSession();
	CDialogEx::OnOK();
}

// ESC 키를 눌렀을 때 실행되는 메소드.
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

	// 리소스 해제.
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