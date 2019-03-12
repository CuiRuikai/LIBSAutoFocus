
// HybridAutoFocusDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include"stdafx.h"
#include"Motor.h"
#include"Utility.h"


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
	Utility utility;
	Motor motor;
	std::string serialNo;
public:
	CComboBox m_MotorBox;
	afx_msg void OnBnClickedGetmotors();
	afx_msg void OnCbnSelchangeMotorbox();
	afx_msg void OnBnClickedOpenmotor();
	afx_msg void OnBnClickedClosemotor();
	afx_msg void OnClose();
};
