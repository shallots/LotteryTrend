
// LotteryTrendDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#include "WLottery.h"

// CLotteryTrendDlg �Ի���
class CLotteryTrendDlg : public CDialogEx
{
// ����
public:
	CLotteryTrendDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOTTERYTREND_DIALOG };

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
	afx_msg void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	// �Զ���
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
