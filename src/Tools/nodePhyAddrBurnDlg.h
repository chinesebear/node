
// nodePhyAddrBurnDlg.h : ͷ�ļ�
//

#pragma once
//#include "SerialPort.h"
#include "ComBase.h"

// CnodePhyAddrBurnDlg �Ի���
class CnodePhyAddrBurnDlg : public CDialogEx
{
// ����
public:
	CnodePhyAddrBurnDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NODEPHYADDRBURN_DIALOG };

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
