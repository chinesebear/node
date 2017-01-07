// nodePhyAddrBurnDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "nodePhyAddrBurn.h"
#include "nodePhyAddrBurnDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CnodePhyAddrBurnDlg �Ի���



CnodePhyAddrBurnDlg::CnodePhyAddrBurnDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CnodePhyAddrBurnDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnodePhyAddrBurnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CnodePhyAddrBurnDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1_READ, &CnodePhyAddrBurnDlg::OnBnClickedButton1Read)
	ON_BN_CLICKED(IDC_BUTTON2_WRITE, &CnodePhyAddrBurnDlg::OnBnClickedButton2Write)
	ON_BN_CLICKED(IDC_BUTTON3_CONNECT, &CnodePhyAddrBurnDlg::OnBnClickedButton3Connect)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CnodePhyAddrBurnDlg ��Ϣ�������

BOOL CnodePhyAddrBurnDlg::OnInitDialog()
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
	SetIcon(m_hIcon, FALSE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	int i;
	int index;
	CString cstr;
	CComboBox *pBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
	PortOwner = this->m_hWnd;

	for (i = 0, index = 0; i < 200; i++)
	{
		if (m_SerialPort.Open(i))
		{
			cstr.Format(_T("COM%d"), i);
			pBox->InsertString(index, cstr);
			//AfxMessageBox(cstr, MB_OKCANCEL | MB_ICONQUESTION);
			index++;
		}
		m_SerialPort.Close();
	}

	pBox->SetCurSel(0); //����Ϊ�����Ԫ��
	CEdit *pEdit5 = (CEdit*)GetDlgItem(IDC_EDIT5);
	pEdit5->SetWindowText(_T("00"));
	pEdit5->SetLimitText(2);
	CEdit *pEdit4 = (CEdit*)GetDlgItem(IDC_EDIT4);
	pEdit4->SetWindowText(_T("00"));
	pEdit4->SetLimitText(2);
	CEdit *pEdit3 = (CEdit*)GetDlgItem(IDC_EDIT3);
	pEdit3->SetWindowText(_T("00"));
	pEdit3->SetLimitText(2);
	CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT2);
	pEdit2->SetWindowText(_T("00"));
	pEdit2->SetLimitText(2);
	CEdit *pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit1->SetWindowText(_T("00"));
	pEdit1->SetLimitText(2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CnodePhyAddrBurnDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CnodePhyAddrBurnDlg::OnPaint()
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
HCURSOR CnodePhyAddrBurnDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CnodePhyAddrBurnDlg::OnCommRecvChar(WPARAM ch, LPARAM port)
{
	CString strTemp;
	strTemp.Format("%c", ch);
	AfxMessageBox(strTemp, MB_OKCANCEL | MB_ICONQUESTION);
	return 0;
}
bool CnodePhyAddrBurnDlg::CnodeConnect(void)
{
		CString strTemp;
		BYTE ch;
		/***check serial port***/
		m_SerialPort.Reset();
		m_SerialPort.Write("A",1);
		m_SerialPort.Read(&ch,1);
		//strTemp.Format("%c", ch);
		//AfxMessageBox(strTemp, MB_OKCANCEL | MB_ICONQUESTION);
		if(ch == 'B')
			return true;
		else
			return false;
}
void CnodePhyAddrBurnDlg::OnBnClickedButton1Read()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	BYTE ch[20];	
	if(CnodeConnect())
	{
		m_SerialPort.Reset();
		m_SerialPort.Write("R",1);
		m_SerialPort.RecvData(ch,6);
		strTemp.Format("%02X-%02X-%02X-%02X-%02X",
			ch[1],ch[2],ch[3],ch[4],ch[5]);
		AfxMessageBox(strTemp, MB_OKCANCEL | MB_ICONQUESTION);
		CEdit *pEdit5 = (CEdit*)GetDlgItem(IDC_EDIT5);
		strTemp.Format("%02X",ch[1]);
		pEdit5->SetWindowText(strTemp);
		CEdit *pEdit4 = (CEdit*)GetDlgItem(IDC_EDIT4);
		strTemp.Format("%02X",ch[2]);
		pEdit4->SetWindowText(strTemp);
		CEdit *pEdit3 = (CEdit*)GetDlgItem(IDC_EDIT3);
		strTemp.Format("%02X",ch[3]);
		pEdit3->SetWindowText(strTemp);
		CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT2);
		strTemp.Format("%02X",ch[4]);
		pEdit2->SetWindowText(strTemp);
		CEdit *pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);
		strTemp.Format("%02X",ch[5]);
		pEdit1->SetWindowText(strTemp);

	}
	else
	{
		AfxMessageBox("node connect failed", MB_OKCANCEL | MB_ICONQUESTION);
	}
}

BYTE  CnodePhyAddrBurnDlg::CStringToHex(CString cstr)
{
	BYTE ch1,ch2;
	ch1 = *cstr;
	ch2 = *(cstr.Mid(1));
	if(ch1 ==  'A' || ch1 == 'a')
	{
		ch1 = 10*16;
	}
	else if(ch1 == 'B' || ch1 == 'b')
	{
		ch1 = 11*16;
	}
	else if(ch1 == 'C' || ch1 == 'c')
	{
		ch1 = 12*16;
	}
	else if(ch1 == 'D' || ch1 == 'D')
	{
		ch1 = 13*16;
	}
	else if(ch1 == 'E' || ch1 == 'e')
	{
		ch1 = 14*16;
	}
	else if(ch1 == 'F' || ch1 == 'f')
	{
		ch1 = 15*16;
	}
	else
	{
		if(ch1 >= '0' && ch1 <= '9')
		{
			ch1 = (ch1 - '0')*16;
		}
		else
		{
			AfxMessageBox("CStringToHex error1", MB_OKCANCEL | MB_ICONQUESTION);
		}
		
	}

	if(ch2 ==  'A' || ch2 == 'a')
	{
		ch2 = 10;
	}
	else if(ch2 == 'B' || ch2 == 'b')
	{
		ch2 = 11;
	}
	else if(ch2 == 'C' || ch2 == 'c')
	{
		ch2 = 12;
	}
	else if(ch2 == 'D' || ch2 == 'D')
	{
		ch2 = 13;
	}
	else if(ch2 == 'E' || ch2 == 'e')
	{
		ch2 = 14;
	}
	else if(ch2 == 'F' || ch2 == 'f')
	{
		ch2 = 15;
	}
	else
	{
		if(ch2 >= '0' && ch2 <= '9')
		{
			ch2= ch2 -'0';
		}
		else
		{
			AfxMessageBox("CStringToHex error2", MB_OKCANCEL | MB_ICONQUESTION);
		}
	}
	return (ch1+ch2);
}

void CnodePhyAddrBurnDlg::OnBnClickedButton2Write()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	BYTE ch[20];	
	if(CnodeConnect())
	{
		m_SerialPort.Reset();
		CEdit *pEdit5 = (CEdit*)GetDlgItem(IDC_EDIT5);
		pEdit5->GetWindowText(strTemp);
		ch[1] = CStringToHex(strTemp);
		CEdit *pEdit4 = (CEdit*)GetDlgItem(IDC_EDIT4);
		pEdit4->GetWindowText(strTemp);
		ch[2] = CStringToHex(strTemp);
		CEdit *pEdit3 = (CEdit*)GetDlgItem(IDC_EDIT3);
		pEdit3->GetWindowText(strTemp);
		ch[3] = CStringToHex(strTemp);
		CEdit *pEdit2 = (CEdit*)GetDlgItem(IDC_EDIT2);
		pEdit2->GetWindowText(strTemp);
		ch[4] = CStringToHex(strTemp);
		CEdit *pEdit1 = (CEdit*)GetDlgItem(IDC_EDIT1);
		pEdit1->GetWindowText(strTemp);
		ch[5] = CStringToHex(strTemp);
		m_SerialPort.Write("W",1);
		m_SerialPort.Write(ch+1,5);
		m_SerialPort.Read(ch,1);
		if(ch[0] == 'B')
		{
			AfxMessageBox("write node phy address success", MB_OKCANCEL | MB_ICONQUESTION);
		}
		else
		{
			AfxMessageBox("write node phy address fail", MB_OKCANCEL | MB_ICONQUESTION);
		}
	}
	else
	{
		AfxMessageBox("node connect failed", MB_OKCANCEL | MB_ICONQUESTION);
	}
}

void CnodePhyAddrBurnDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	/***close serial port***/
	m_SerialPort.Close();

	CDialogEx::OnClose();
}


void CnodePhyAddrBurnDlg::OnBnClickedButton3Connect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UINT PortNumber;
	CString SelectedCOM;
	GetDlgItemText(IDC_COMBO1, SelectedCOM);
	SelectedCOM = SelectedCOM.Mid(3);
	PortNumber = atoi(SelectedCOM);
	/***open serial port***/
	if (m_SerialPort.IsOpen())
	{
		m_SerialPort.Close();
	}
	//PortOwner = this->GetSafeHwnd();
	if(m_SerialPort.Open(PortNumber))
	{
		AfxMessageBox("COM OK!", MB_OKCANCEL | MB_ICONQUESTION);
	}
	else
	{
		AfxMessageBox("COM Failed!", MB_OKCANCEL | MB_ICONQUESTION);
	}
	
}
