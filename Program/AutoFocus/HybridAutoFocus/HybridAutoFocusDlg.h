
// HybridAutoFocusDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include"stdafx.h"
#include"Motor.h"
#include"Utility.h"
#include "MVGigE.h" 
#include "MVImage.h" 


// CHybridAutoFocusDlg �Ի���
class CHybridAutoFocusDlg : public CDialogEx
{
// ����
public:
	CHybridAutoFocusDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HYBRIDAUTOFOCUS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//����������
	Motor motor;
	//����������
	std::string serialNo;

	//�������������� 
	HANDLE m_hCam;
	//����ͼ������� 
	MVImage m_image;
	//�������ظ�ʽ���� 
	MV_PixelFormatEnums m_PixelFormat;
	//�ɼ���ʶ 
	bool m_bRun;
	//ͨ���ص�������ȡͼ��������Ϣ 
	int OnStreamCB(MV_IMAGE_INFO *pInfo);
	//��Pictur Control�ռ��л���ͼ��
	void DrawImage();

	//���ߺ���
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
