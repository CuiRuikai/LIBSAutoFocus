
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
	, m_bRun(FALSE)//初始化运行标志
	, m_hCam(NULL)//初始化相机句柄
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
	ON_BN_CLICKED(IDC_OpenCam, &CHybridAutoFocusDlg::OnBnClickedOpencam)
	ON_BN_CLICKED(IDC_CloseCam, &CHybridAutoFocusDlg::OnBnClickedClosecam)
	ON_BN_CLICKED(IDC_StartFocus, &CHybridAutoFocusDlg::OnBnClickedStartfocus)
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
		return;
	}
	CString deviceNum;//临时存储设备编号的CString变量
	for (int i = 0; i < size; i++)//遍历全部设备编号
	{
		deviceNum = serialNumbers[i].c_str();//转换
		m_MotorBox.AddString(deviceNum);//添加
	}
	m_MotorBox.SetCurSel(0);// 默认选择第一项 
	serialNo = serialNumbers[0];
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
	motor.setSerialNo(serialNo);
	if (motor.connect() == false)
		MessageBox(_T("TDC打开失败"), _T("Warning"), MB_OK);
	else
		MessageBox(_T("TDC打开成功"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnBnClickedClosemotor()
{
	// TODO: 在此添加控件通知处理程序代码
	if (motor.disconnect() == true)
		MessageBox(_T("TDC成功关闭"), _T("Message"), MB_OK);
	else
		MessageBox(_T("TDC关闭失败"), _T("Message"), MB_OK);
}


void CHybridAutoFocusDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//相机关闭处理
	if (m_bRun != false)
	{
		MVStopGrab(m_hCam);
	}
	MVTerminateLib();
	//电机关闭处理
	motor.disconnect();
	CDialogEx::OnClose();
}


void CHybridAutoFocusDlg::OnBnClickedOpencam()
{
	// TODO: 在此添加控件通知处理程序代码
	int nCams = 0;//相机数量，默认为零
	MVGetNumOfCameras(&nCams);//读取相机数量

	if (nCams == 0)
	{
		MessageBox(_T("没有找到相机,请确认连接和相机的IP设置"), _T("提示"), MB_OK);
		return;
	}

	MVSTATUS_CODES r = MVOpenCamByIndex(0, &m_hCam);//按照编号打开相机，仅一个相机，打开0号，得到相机句柄
	if (m_hCam == NULL)//检验是否成功打开相机并获取句柄
	{
		if (r == MVST_ACCESS_DENIED)
			MessageBox(_T("无法打开相机，可能正被别的软件控制"), _T("提示"), MB_OK);
		else
			MessageBox(_T("无法打开相机"), _T("提示"), MB_OK);
		return;
	}
	//读取相机图象信息
	int w, h;//存储图像宽度，高度
	MVGetWidth(m_hCam, &w);//相机图像宽度
	MVGetHeight(m_hCam, &h);//相机图象高度
	MVGetPixelFormat(m_hCam, &m_PixelFormat);//相机图象像素格式

	m_image.CreateByPixelFormat(w, h, m_PixelFormat);//根据宽度、高度、和像素格式创建图像


	unsigned int minPacketSize, maxPacketSize;
	r = MVGetPacketSizeRange(m_hCam, &minPacketSize, &maxPacketSize);
	if (r != MVST_SUCCESS) {
		MessageBox(_T("获取包大小失败"), _T("提示"), MB_OK);
		return;
	}
	r = MVSetPacketSize(m_hCam, minPacketSize);
	if (r != MVST_SUCCESS) {
		MessageBox(_T("设置包大小失败"), _T("提示"), MB_OK);
		return;
	}
	MVSetExposureTime(m_hCam, 100000);//手动设置曝光时间

	//unsigned int minPacketDelay, maxPacketDelay;
	//r = MVGetPacketDelayRange(m_hCam, &minPacketDelay, &maxPacketDelay);
	//if (r != MVST_SUCCESS) {
	//	MessageBox(_T("获取包延迟失败"), _T("提示"), MB_OK);
	//	return;
	//}
	//r = MVSetPacketDelay(m_hCam, minPacketDelay);
	//if (r != MVST_SUCCESS) {
	//	MessageBox(_T("设置包延迟失败"), _T("提示"), MB_OK);
	//	return;
	//}
}


void CHybridAutoFocusDlg::OnBnClickedClosecam()
{
	// TODO: 在此添加控件通知处理程序代码
	MVStopGrab(m_hCam);//停止采集图像
	MVCloseCam(m_hCam);//断开相机连接
	m_bRun = false;//修改采集标志
}

void CHybridAutoFocusDlg::DrawImage()//在picture control 控件中显示获取的图像
{
	CRect rct;
	GetDlgItem(IDC_Pic)->GetClientRect(&rct);
	int dstW = rct.Width();
	int dstH = rct.Height();
	CDC *pDC = GetDlgItem(IDC_Pic)->GetDC();
	{
		pDC->SetStretchBltMode(COLORONCOLOR);
		m_image.Draw(pDC->GetSafeHdc(), 0, 0, dstW, dstH);
	}
	ReleaseDC(pDC);//记得释放
}

int CHybridAutoFocusDlg::OnStreamCB(MV_IMAGE_INFO *pInfo)//相应回调函数的处理
{
	MVInfo2Image(m_hCam, pInfo, &m_image);//将回调函数收到的图像信息转换为图像
	DrawImage();//绘制图像

	return 0;
}

int __stdcall StreamCB(MV_IMAGE_INFO *pInfo, ULONG_PTR nUserVal)//回调函数
{
	CHybridAutoFocusDlg *pDlg = (CHybridAutoFocusDlg*)nUserVal;
	return (pDlg->OnStreamCB(pInfo));
}



void CHybridAutoFocusDlg::OnBnClickedStartfocus()
{
	// TODO: 在此添加控件通知处理程序代码
	//设置快门模式，设置为连续采集模式
	TriggerModeEnums enumMode;
	MVGetTriggerMode(m_hCam, &enumMode);
	if (enumMode != TriggerMode_Off)
	{
		MVSetTriggerMode(m_hCam, TriggerMode_Off);
		Sleep(100);
	}

	MVStartGrab(m_hCam, StreamCB, (ULONG_PTR)this);//采集图像，并显示到pic
	m_bRun = true;

	Motion motion(motor, m_hCam, m_image, utility);
	int i=motion.moveAndGrabImgs(LENGTH_MIN,LENGTH_MAX,5,imgVec);
	

}
