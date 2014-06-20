
// LotteryTrendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LotteryTrend.h"
#include "LotteryTrendDlg.h"
#include "afxdialogex.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CLotteryTrendDlg 对话框



CLotteryTrendDlg::CLotteryTrendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLotteryTrendDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLotteryTrendDlg::OnOK()
{
	 CDialog::OnOK();
}

void CLotteryTrendDlg::OnCancel()
{
	//if (CanExit())
	//	CDialogEx::OnCancel();
	int key = MessageBox(_T("你真的要退出?"),_T("退出？"),MB_OKCANCEL);
	if(key == IDOK){
		CDialog::OnCancel();
	}
}

void CLotteryTrendDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	wl->saveSamples();
	CDialogEx::OnClose();
	// 析构对象，并保存对象数据
}

void CLotteryTrendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADD, m_add);
	DDX_Control(pDX, IDC_BW, m_bwtrend);
	DDX_Control(pDX, IDC_FORCAST, m_forcast);
	DDX_Control(pDX, IDC_GW, m_gwtrend);
	DDX_Control(pDX, IDC_SW, m_swtrend);
	DDX_Control(pDX, IDC_IMPORT, m_import);
	DDX_Control(pDX, IDC_LISTSAMPLES, m_listsamples);
	DDX_Control(pDX, IDC_NUM, m_num);
	DDX_Control(pDX, IDC_REWARD, m_reward);
	DDX_Control(pDX, IDC_HISTORYSUM, m_historysum);
	DDX_Control(pDX, IDC_SAVE, m_save);
	DDX_Control(pDX, IDC_SPECIAL, m_specialnum);
	DDX_Control(pDX, IDC_LISTCOUNT, m_listcount);
	DDX_Control(pDX, IDC_TRENDTITLE, m_trendtitle);
	DDX_Control(pDX, IDC_PREVIEW, m_preview);
}

BEGIN_MESSAGE_MAP(CLotteryTrendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CLotteryTrendDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_IMPORT, &CLotteryTrendDlg::OnBnClickedImport)
	ON_BN_CLICKED(IDC_FORCAST, &CLotteryTrendDlg::OnBnClickedForcast)
	ON_BN_CLICKED(IDC_SAVE, &CLotteryTrendDlg::OnBnClickedSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTSAMPLES, &CLotteryTrendDlg::OnDblclkListsamples)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTSAMPLES, &CLotteryTrendDlg::OnLvnItemchangedListsamples)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLotteryTrendDlg 消息处理程序

BOOL CLotteryTrendDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	wl = new WLottery();
	m_reward.SetLimitText(3);
	m_num.SetLimitText(5);

	// 设置listcontrol
	m_listsamples.InsertColumn(0,_T("期号"),LVCFMT_LEFT,100);
	m_listsamples.InsertColumn(1,_T("百"),LVCFMT_LEFT,50);
	m_listsamples.InsertColumn(2,_T("十"),LVCFMT_LEFT,50);
	m_listsamples.InsertColumn(3,_T("个"),LVCFMT_LEFT,50);

	m_listcount.SetWindowTextW(_T("0"));

	m_historysum.AddString(_T("60"));
	m_historysum.AddString(_T("80"));
	m_historysum.AddString(_T("120"));


	// 导入初始数据
	wl->importSamples("3Ddata.txt");
	Resetlist();
	
	int maxnum = wl->getMax();
	if(maxnum>0){
		CString tmpx;
		tmpx.Format(_T("%d"),maxnum);
		m_specialnum.SetWindowTextW(tmpx);

		tmpx.Format(_T("%d"),maxnum+1);
		m_num.SetWindowTextW(tmpx);
		tmpx.Empty();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLotteryTrendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLotteryTrendDlg::OnPaint()
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
HCURSOR CLotteryTrendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int CStringToInt(CString cstr,vector<int> &i){
	if(cstr.GetLength()<1)
		return 0;
	i.clear();
	int length = cstr.GetLength();
	char *p = (LPSTR)(LPCTSTR)cstr;
	for(int j=0; j<2*length; j=j+2)
	{
		int tmp = *(p+j) - 48;
		i.push_back(tmp);
	}
	return i.size();
}

int getInt(vector<int> i){
	int count = i.size();
	int k = 1;
	int sum = 0;
	for(vector<int>::iterator it = i.begin(); it!=i.end(); it++){
		int tmp = *it;
		for(int j=0; j<count-k; j++)
			tmp *= 10;
		sum+=tmp;
		k++;
	}
	return sum;
}
CString intToCST(int i){
	CString tmp;
	tmp.Format(_T("%d"),i);
	return tmp;
}
void CLotteryTrendDlg::Resetlist(){
	// 重新输出到listcontrol
	m_listsamples.DeleteAllItems();
	int nIndex=0;
	for(vector<WelfareLot>::iterator it = wl->samples.begin(); it!=wl->samples.end(); it++){
		nIndex = m_listsamples.InsertItem(nIndex,intToCST(it->num));
		m_listsamples.SetItemText(nIndex,1,intToCST(it->b));
		m_listsamples.SetItemText(nIndex,2,intToCST(it->s));
		m_listsamples.SetItemText(nIndex,3,intToCST(it->g));
		nIndex++;
	}
	
	int count = m_listsamples.GetItemCount();
	CString tmp;
	tmp.Format(_T("%d"),count);
	m_listcount.SetWindowTextW(tmp);
}
void CLotteryTrendDlg::OnBnClickedAdd()
{
	// 解析3D数据,添加3D码到历史数据
	CString num;
	CString reward;

	m_num.GetWindowTextW(num);
	m_reward.GetWindowTextW(reward);

	if(num.GetLength()<1 || reward.GetLength()!=3)
	{
		MessageBox(_T("请检查输入3D数据是否正确"));
		return;
	}
	WelfareLot tmp;
	vector<int> vnum;
	CStringToInt(num,vnum);
	tmp.num = getInt(vnum);
	vnum.clear();

	CStringToInt(reward,vnum);
	vector<int>::iterator it = vnum.begin();
	tmp.b = *it;
	tmp.s = *(it+1);
	tmp.g = *(it+2);
	wl->addSample(tmp);
	vnum.clear();
	// 重新输出样本到listcontrol
	Resetlist();
	// 设置选中
	int nIndex = wl->getSampleIndex(tmp.num);
	m_listsamples.SetItemState(nIndex,LVIS_SELECTED|LVIS_FOCUSED,LVIS_SELECTED|LVIS_FOCUSED);


	// 设置样本输入数据
	CString cnum;
	cnum.Format(_T("%d"),tmp.num+1);
	m_num.SetWindowTextW(cnum);
	m_reward.SetWindowTextW(_T(""));
	cnum.Empty();
	m_reward.SetFocus();
}

char* CStringToChar(CString cstr){
	if(cstr.GetLength()>255){
		return NULL;
	}
	wchar_t *ptrx;             
	char* bufx = new char[256];        // 目标存储空间
	for(int i=0; i<256; i++){
		bufx[i] = '\0';
	}
	int dslength = cstr.GetLength()>255?255:cstr.GetLength();
	ptrx=cstr.GetBuffer(dslength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrx, -1, bufx, sizeof(bufx), NULL, NULL);
	return bufx;
}

void CLotteryTrendDlg::OnBnClickedImport()
{
	// TODO: 在此添加控件通知处理程序代码
	//过滤器
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt||");
	TCHAR* filename=NULL;
	CFileDialog f_Export(true,
	_T("txt"),
	filename,
	OFN_OVERWRITEPROMPT |OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_CREATEPROMPT,
	szFilter,
	this);
	CString fpath;
	if(f_Export.DoModal() == IDOK)
	{
		fpath = f_Export.GetPathName();
	}else{
		return;
	}
	wchar_t *ptrx;             
	char bufx[256];        // 目标存储空间
	memset(bufx,'\0',256);
	int dslength = fpath.GetLength()>255?255:fpath.GetLength();
	ptrx=fpath.GetBuffer(dslength*sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)ptrx, -1, bufx, sizeof(bufx), NULL, NULL);
	int count = wl->importSamples(bufx);
	Resetlist();
	if(count>0){
		CString msg;
		msg.Format(_T("导入 %d 期3D开奖数据!"),count);
		MessageBox(msg);
	}
}

void IVToCString(CString &cstr,int* iv,int length=10){
	int i=0;
	cstr.Empty();
	while(i<length && iv[i] != -1 ){
		CString tmp;
		tmp.Format(_T("%d"),iv[i]);
		i++;
		cstr += tmp;
	}
}

void CLotteryTrendDlg::OnBnClickedForcast()
{
	// TODO: 在此添加控件通知处理程序代码
	CString his;
	m_historysum.GetWindowTextW(his);
	//MessageBox(his);
	if(his.GetLength()<1)
	{
		MessageBox(_T("请输入预测所需往期开奖数!"));
		m_historysum.SetFocus();
		return;
	}
	vector<int> ivtmp;
	CStringToInt(his,ivtmp);
	wl->historysum = getInt(ivtmp);
	ivtmp.clear();

	m_specialnum.GetWindowTextW(his);
	if(his.GetLength()<1)
	{
		MessageBox(_T("请输入预测期号!"));
		m_specialnum.SetFocus();
		return;
	}
	CStringToInt(his,ivtmp);
	wl->specialnum = getInt(ivtmp);
	ivtmp.clear();

	vector<int*> res;
	if(wl->forcastTrend(res)){
		CString cstr[3];
		int i = 0;
		for(vector<int*>::iterator it=res.begin(); it!=res.end(); it++){
			IVToCString(cstr[i],*it);
			i++;
		}
		m_bwtrend.SetWindowTextW(cstr[0]);
		m_swtrend.SetWindowTextW(cstr[1]);
		m_gwtrend.SetWindowTextW(cstr[2]);

		// 
		WelfareLot *pre = wl->getSample(wl->specialnum);
		CString cpre;
		cpre.Format(_T("%d 期开奖号为  %d %d %d"),pre->num,pre->b,pre->s,pre->g);
		m_preview.SetWindowTextW(cpre);
		cpre.Empty();

		CString title;
		title.Format(_T(" %d 期走势预测 "),wl->specialnum+1);
		m_trendtitle.SetWindowTextW(title);
		title.Empty();

	}else{
		MessageBox(_T("您所输入的3D开奖期号不在往期数据中或输入有误,请核对后再操作！"));
		return;
	}
}


void CLotteryTrendDlg::OnBnClickedSave()
{
	CString tmp;
	int count = 0;
	switch (wl->getStatus())
	{
	case MODIFY:
		count = wl->saveSamples();
		tmp.Format(_T("共保存 %d 期数据"),count);
		MessageBox(tmp);
		break;
	case SAVED:
		tmp.Format(_T("数据已保存"),count);
		MessageBox(tmp);
		break;
	default:
		break;
	}
}

void CLotteryTrendDlg::OnDblclkListsamples(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION pos = m_listsamples.GetFirstSelectedItemPosition();
	if(NULL == pos)
	{
		return;
	}
	CString ctmp;
	int nid = (int)m_listsamples.GetNextSelectedItem(pos);
	ctmp = m_listsamples.GetItemText(nid,0);
	m_listsamples.DeleteItem(nid);
	
	vector<int> itmp;
	CStringToInt(ctmp,itmp);

	wl->delSample(getInt(itmp));
	itmp.clear();

	int count = m_listsamples.GetItemCount();
	CString tmp;
	tmp.Format(_T("%d"),count);
	m_listcount.SetWindowTextW(tmp);
}


void CLotteryTrendDlg::OnLvnItemchangedListsamples(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

