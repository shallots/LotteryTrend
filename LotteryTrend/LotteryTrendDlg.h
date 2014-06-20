
// LotteryTrendDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "WLottery.h"

// CLotteryTrendDlg 对话框
class CLotteryTrendDlg : public CDialogEx
{
// 构造
public:
	CLotteryTrendDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOTTERYTREND_DIALOG };

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
	afx_msg void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	// 自定义
	WLottery* wl;

	void Resetlist();

	CButton m_add;
	CEdit m_bwtrend;
	CButton m_forcast;
	CEdit m_gwtrend;
	CEdit m_swtrend;
	CButton m_import;
	CListCtrl m_listsamples;
	CEdit m_num;
	CEdit m_reward;
	CComboBox m_historysum;
	CButton m_save;
	CEdit m_specialnum;
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedImport();
	CStatic m_listcount;
	afx_msg void OnBnClickedForcast();
	afx_msg void OnBnClickedSave();
	afx_msg void OnDblclkListsamples(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListsamples(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	CStatic m_trendtitle;
	CStatic m_preview;
};
