#include"krectangle.h"
KRectangle::KRectangle(double w, double l)
{
	if (w > 0 && l > 0)
	{
		m_width = w;
		m_length = l;
	}
	else
	{
		m_width = 0;
		m_length = 0;
		cout << "Illegal input" << endl;
	}
}

double KRectangle::getPerimeter() const
{
	return 2 * (m_length + m_width);
}
double KRectangle::getArea() const
{
	return m_length * m_width;
}
string KRectangle::getShape() const
{
	return "Rectangle";
}