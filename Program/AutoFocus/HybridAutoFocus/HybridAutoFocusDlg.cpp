
// HybridAutoFocusDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HybridAutoFocus.h"
#include "HybridAutoFocusDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHybridAutoFocusDlg 对话框



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


// CHybridAutoFocusDlg 消息处理程序

BOOL CHybridAutoFocusDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHybridAutoFocusDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHybridAutoFocusDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHybridAutoFocusDlg::OnBnClickedGetmotors()
{
	// TODO: 在此添加控件通知处理程序代码
	std::vector<std::string> serialNumbers;//存储所得编号
	std::vector<TLI_DeviceInfo> vecDecviceInfo;//存储所得编号对应的信息
	int size = motor.getDevices(DEVICEID_TDC, serialNumbers, vecDecviceInfo);//获取编号、信息、数量

	if (size == 0) 
	{
		MessageBox(_T("No Motor. Please check "), _T("OK"), MB_OK);
	}
	CString deviceNum;//临时存储设备编号的CString变量
	for (int i = 0; i < size; i++)//遍历全部设备编号
	{
		deviceNum = serialNumbers[i].c_str();//转换
		m_MotorBox.AddString(deviceNum);//添加
	}
	m_MotorBox.SetCurSel(0);// 默认选择第一项 
}


void CHybridAutoFocusDlg::OnCbnSelchangeMotorbox()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strMotor;
	int nSel;

	nSel = m_MotorBox.GetCurSel();// 获取组合框控件的列表框中选中项的索引
	m_MotorBox.GetLBText(nSel, strMotor);// 根据选中项索引获取该项字符串   

	serialNo = utility.toString(strMotor);//存储到全局变量中
}



void CHybridAutoFocusDlg::OnBnClickedOpenmotor()
{
	// TODO: 在此添加控件通知处理程序代码
	if (motor.connect(serialNo) == false)
		MessageBox(_T("TDC打开失败"), _T("Warning"), MB_OK);
	else
		MessageBox(_T("TDC打开成功"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnBnClickedClosemotor()
{
	// TODO: 在此添加控件通知处理程序代码
	if (motor.disconnect(serialNo) == true)
		MessageBox(_T("TDC成功关闭"), _T("Message"), MB_OK);
	else
		MessageBox(_T("TDC关闭失败"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	motor.disconnect(serialNo);
	CDialogEx::OnClose();
}
