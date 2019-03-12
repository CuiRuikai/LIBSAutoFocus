
// HybridAutoFocusDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"stdafx.h"
#include"Motor.h"
#include"Utility.h"
#include "MVGigE.h" 
#include "MVImage.h" 


// CHybridAutoFocusDlg 对话框
class CHybridAutoFocusDlg : public CDialogEx
{
// 构造
public:
	CHybridAutoFocusDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HYBRIDAUTOFOCUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//定义电机对象
	Motor motor;
	//定义相机句柄
	std::string serialNo;

	//定义相机句柄对象 
	HANDLE m_hCam;
	//定义图像处理对象 
	MVImage m_image;
	//定义像素格式对象 
	MV_PixelFormatEnums m_PixelFormat;
	//采集标识 
	bool m_bRun;
	//通过回调函数获取图像数据信息 
	int OnStreamCB(MV_IMAGE_INFO *pInfo);
	//在Pictur Control空间中画出图象
	void DrawImage();

	//工具函数
	Utility utility;
public:
	CComboBox m_MotorBox;
	afx_msg void OnBnClickedGetmotors();
	afx_msg void OnCbnSelchangeMotorbox();
	afx_msg void OnBnClickedOpenmotor();
	afx_msg void OnBnClickedClosemotor();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOpencam();
	afx_msg void OnBnClickedClosecam();
	afx_msg void OnBnClickedStartfocus();
};
