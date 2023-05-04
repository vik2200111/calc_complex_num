class ComplexNumber
{
private:
	double real;
	double imag;
public:

	ComplexNumber(double real, double imag)
	{
		this->real = real;
		this->imag = imag;
	}

	double getReal() { return real; }
	double getImag() { return imag; }

	void setComplex(double real, double imag)
	{ 
		this->real = real;
		this->imag = imag;
	}

};