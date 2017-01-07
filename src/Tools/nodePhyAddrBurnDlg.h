
// nodePhyAddrBurnDlg.h : 头文件
//

#pragma once
//#include "SerialPort.h"
#include "ComBase.h"

// CnodePhyAddrBurnDlg 对话框
class CnodePhyAddrBurnDlg : public CDialogEx
{
// 构造
public:
	CnodePhyAddrBurnDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_NODEPHYADDRBURN_DIALOG };

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
	CComBase m_SerialPort;
	LPCSTR SerialRxBuf[1024];
	HWND PortOwner;
	afx_msg void OnBnClickedButton1Read();
	afx_msg void OnBnClickedButton2Write();
	afx_msg LRESULT OnCommRecvChar(WPARAM wParam, LPARAM port);
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3Connect();
	bool CnodeConnect(void);
	BYTE CStringToHex(CString cstr);
};
