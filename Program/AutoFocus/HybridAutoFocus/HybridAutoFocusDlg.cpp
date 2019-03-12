
// HybridAutoFocusDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HybridAutoFocus.h"
#include "HybridAutoFocusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHybridAutoFocusDlg �Ի���



CHybridAutoFocusDlg::CHybridAutoFocusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HYBRIDAUTOFOCUS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHybridAutoFocusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MotorBox, m_MotorBox);
}

BEGIN_MESSAGE_MAP(CHybridAutoFocusDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GetMotors, &CHybridAutoFocusDlg::OnBnClickedGetmotors)
	ON_CBN_SELCHANGE(IDC_MotorBox, &CHybridAutoFocusDlg::OnCbnSelchangeMotorbox)
	ON_BN_CLICKED(IDC_OpenMotor, &CHybridAutoFocusDlg::OnBnClickedOpenmotor)
	ON_BN_CLICKED(IDC_CloseMotor, &CHybridAutoFocusDlg::OnBnClickedClosemotor)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CHybridAutoFocusDlg ��Ϣ�������

BOOL CHybridAutoFocusDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHybridAutoFocusDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHybridAutoFocusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHybridAutoFocusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHybridAutoFocusDlg::OnBnClickedGetmotors()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	std::vector<std::string> serialNumbers;//�洢���ñ��
	std::vector<TLI_DeviceInfo> vecDecviceInfo;//�洢���ñ�Ŷ�Ӧ����Ϣ
	int size = motor.getDevices(DEVICEID_TDC, serialNumbers, vecDecviceInfo);//��ȡ��š���Ϣ������

	if (size == 0) 
	{
		MessageBox(_T("No Motor. Please check "), _T("OK"), MB_OK);
	}
	CString deviceNum;//��ʱ�洢�豸��ŵ�CString����
	for (int i = 0; i < size; i++)//����ȫ���豸���
	{
		deviceNum = serialNumbers[i].c_str();//ת��
		m_MotorBox.AddString(deviceNum);//���
	}
	m_MotorBox.SetCurSel(0);// Ĭ��ѡ���һ�� 
}


void CHybridAutoFocusDlg::OnCbnSelchangeMotorbox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strMotor;
	int nSel;

	nSel = m_MotorBox.GetCurSel();// ��ȡ��Ͽ�ؼ����б����ѡ���������
	m_MotorBox.GetLBText(nSel, strMotor);// ����ѡ����������ȡ�����ַ���   

	serialNo = utility.toString(strMotor);//�洢��ȫ�ֱ�����
}



void CHybridAutoFocusDlg::OnBnClickedOpenmotor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (motor.connect(serialNo) == false)
		MessageBox(_T("TDC��ʧ��"), _T("Warning"), MB_OK);
	else
		MessageBox(_T("TDC�򿪳ɹ�"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnBnClickedClosemotor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (motor.disconnect(serialNo) == true)
		MessageBox(_T("TDC�ɹ��ر�"), _T("Message"), MB_OK);
	else
		MessageBox(_T("TDC�ر�ʧ��"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	motor.disconnect(serialNo);
	CDialogEx::OnClose();
}
