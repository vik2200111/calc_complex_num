
// MFCApplicationDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CMFCApplicationDlg
class CMFCApplicationDlg : public CDialogEx
{
// Создание
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	ComplexNumber* complexNumber;
public:
	CString m_editReal;
	CString m_editImag;
	CString m_editNumber;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonShowAlgebraic();
	CString m_strView;
	afx_msg void OnBnClickedButtonShowTrigonometric();
	afx_msg void OnBnClickedButtonAddition();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonDiv();
	afx_msg void OnBnClickedButtonMult();
	afx_msg void OnBnClickedButtonPairing();
	afx_msg void OnBnClickedButtonDegree();
	afx_msg void OnBnClickedButtonRoot();
	afx_msg void OnBnClickedButtonShowExponential();
};
