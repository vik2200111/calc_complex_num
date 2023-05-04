
// MFCApplicationDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CMFCApplicationDlg



CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
	, m_editReal(_T(""))
	, m_editImag(_T(""))
	, m_editNumber(_T(""))
	, m_strView(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_editReal);
	DDX_Text(pDX, IDC_EDIT2, m_editImag);
	DDX_Text(pDX, IDC_EDIT4, m_editNumber);
	DDX_Text(pDX, IDC_EDIT3, m_strView);
}

BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFCApplicationDlg::OnBnClickedButtonShowAlgebraic)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFCApplicationDlg::OnBnClickedButtonShowTrigonometric)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationDlg::OnBnClickedButtonAddition)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplicationDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplicationDlg::OnBnClickedButtonDiv)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplicationDlg::OnBnClickedButtonMult)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplicationDlg::OnBnClickedButtonPairing)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplicationDlg::OnBnClickedButtonDegree)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplicationDlg::OnBnClickedButtonRoot)
	ON_BN_CLICKED(IDC_BUTTON11, &CMFCApplicationDlg::OnBnClickedButtonShowExponential)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCApplicationDlg

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplicationDlg::OnBnClickedButtonAdd()
{
	UpdateData(true);
	const wregex reg(L"^[-]?[0-9]+(.[0-9]{1,2})?$");
	if (regex_match(m_editReal.GetString(), m_editReal.GetString() + m_editReal.GetLength(), reg)
		&& regex_match(m_editImag.GetString(), m_editImag.GetString() + m_editImag.GetLength(), reg))
	{
		if (complexNumber == NULL)
			complexNumber = new ComplexNumber(_ttof(m_editReal), _ttof(m_editImag));
		else
			complexNumber->setComplex(_ttof(m_editReal), _ttof(m_editImag));

		m_editImag.Empty();
		m_editReal.Empty();

		MessageBox(L"Комплексное число добавлено", L"Успешно", MB_OK);
	}
	else
		MessageBox(L"Можно использовать только числа\r\nПример: 1 или 3.75 (Максимум 2 знака после запятой)", L"Ошибка", MB_OK);
	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonShowAlgebraic()
{
	UpdateData(true);

	if (complexNumber != NULL)
		m_strView.Format(L"z = %.2f + (%.2f)*i", complexNumber->getReal(), complexNumber->getImag());
	else
		MessageBox(L"Комплексные числа ещё не введены", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonShowTrigonometric()
{
	UpdateData(true);

	if (complexNumber != NULL)
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag());

		double rho = abs(z); 
		double phi = arg(z); 

		m_strView.Format(L"z = %.2f*(cos(%.2f) + i*sin(%.2f))", rho, phi, phi);
	}
	else
		MessageBox(L"Комплексные числа ещё не введены", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonAddition()
{
	UpdateData(true);
	const wregex reg(L"^[-]?[0-9]+(.[0-9]{1,2})?$");
	if (complexNumber != NULL && regex_match(m_editReal.GetString(), m_editReal.GetString() + m_editReal.GetLength(), reg)
		&& regex_match(m_editImag.GetString(), m_editImag.GetString() + m_editImag.GetLength(), reg))
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag()), r(_ttof(m_editReal), _ttof(m_editImag));
		m_strView.Format(L"Результат сложения:\r\nz = (%.2f + (%.2f)i) + (%.2f + (%.2f)i) = %.2f + (%.2f)i", z.real(), z.imag(), r.real(), r.imag(), (z + r).real(), (z + r).imag());

		m_editImag.Empty();
		m_editReal.Empty();
	}
	else
		MessageBox(L"Комплексные числа ещё не введены или некорректно введены числа для сложения", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonMinus()
{
	UpdateData(true);
	const wregex reg(L"^[-]?[0-9]+(.[0-9]{1,2})?$");
	if (complexNumber != NULL && regex_match(m_editReal.GetString(), m_editReal.GetString() + m_editReal.GetLength(), reg)
		&& regex_match(m_editImag.GetString(), m_editImag.GetString() + m_editImag.GetLength(), reg))
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag()), r(_ttof(m_editReal), _ttof(m_editImag));
		m_strView.Format(L"Результат вычитания:\r\nz = (%.2f + (%.2f)i) - (%.2f + (%.2f)i) = %.2f + (%.2f)i", z.real(), z.imag(), r.real(), r.imag(), (z - r).real(), (z - r).imag());

		m_editImag.Empty();
		m_editReal.Empty();
	}
	else
		MessageBox(L"Комплексные числа ещё не введены или некорректно введены числа для вычитания", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonDiv()
{
	UpdateData(true);
	const wregex reg(L"^[-]?[0-9]+(.[0-9]{1,2})?$");
	if (complexNumber != NULL && regex_match(m_editReal.GetString(), m_editReal.GetString() + m_editReal.GetLength(), reg)
		&& regex_match(m_editImag.GetString(), m_editImag.GetString() + m_editImag.GetLength(), reg))
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag()), r(_ttof(m_editReal), _ttof(m_editImag));
		m_strView.Format(L"Результат деления:\r\nz = (%.2f + (%.2f)i) / (%.2f + (%.2f)i) = %.2f + (%.2f)i", z.real(), z.imag(), r.real(), r.imag(), (z / r).real(), (z / r).imag());

		m_editImag.Empty();
		m_editReal.Empty();
	}
	else
		MessageBox(L"Комплексные числа ещё не введены или некорректно введены числа для деления", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonMult()
{
	UpdateData(true);
	const wregex reg(L"^[-]?[0-9]+(.[0-9]{1,2})?$");
	if (complexNumber != NULL && regex_match(m_editReal.GetString(), m_editReal.GetString() + m_editReal.GetLength(), reg)
		&& regex_match(m_editImag.GetString(), m_editImag.GetString() + m_editImag.GetLength(), reg))
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag()), r(_ttof(m_editReal), _ttof(m_editImag));
		m_strView.Format(L"Результат умножения:\r\nz = (%.2f + (%.2f)i) * (%.2f + (%.2f)i) = %.2f + (%.2f)i", z.real(), z.imag(), r.real(), r.imag(), (z * r).real(), (z * r).imag());

		m_editImag.Empty();
		m_editReal.Empty();
	}
	else
		MessageBox(L"Комплексные числа ещё не введены или некорректно введены числа для умножения", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonPairing()
{
	UpdateData(true);
	if (complexNumber != NULL)
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag());
		m_strView.Format(L"Результат сопряжения:\r\nz = %.2f + (%.2f)i", conj(z).real(), conj(z).imag());
	}
	else
		MessageBox(L"Комплексные числа ещё не введены", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonDegree()
{
	UpdateData(true);
	if (complexNumber != NULL && !m_editNumber.IsEmpty())
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag());
		m_strView.Format(L"Результат возведения в степень:\r\nz = %.2f + (%.2f)i", pow(z, _ttoi(m_editNumber)).real(), pow(z, _ttoi(m_editNumber)).imag());
		m_editNumber.Empty();
	}
	else
		MessageBox(L"Комплексные числа ещё не введены или некорректно введены числа для возведения в степень", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonRoot()
{
	UpdateData(true);
	if (complexNumber != NULL)
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag());
		m_strView.Format(L"Результат извлечения корня:\r\nz = %.2f + (%.2f)i", sqrt(z).real(), sqrt(z).imag());
	}
	else
		MessageBox(L"Комплексные числа ещё не введены", L"Ошибка", MB_OK);

	UpdateData(false);
}


void CMFCApplicationDlg::OnBnClickedButtonShowExponential()
{
	UpdateData(true);

	if (complexNumber != NULL)
	{
		std::complex<double> z(complexNumber->getReal(), complexNumber->getImag());

		double rho = abs(z);
		double phi = arg(z);

		m_strView.Format(L"z = %.2f * exp(i * %.2f)", rho, phi);
	}
	else
		MessageBox(L"Комплексные числа ещё не введены", L"Ошибка", MB_OK);

	UpdateData(false);
}
