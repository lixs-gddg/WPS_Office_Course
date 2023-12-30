#include"ktriangle.h"
KTriangle::KTriangle(double _side_a, double _side_b, double _side_c)
{
	if ((_side_a + _side_c > _side_b) && (_side_c + _side_b > _side_a) && (_side_a + _side_b > _side_c) && _side_a>0 && _side_b>0 &&_side_c>0)
	{
		m_side_a = _side_a;
		m_side_b = _side_b;
		m_side_c = _side_c;
	}
	else
	{
		m_side_a = 0;
		m_side_b = 0;
		m_side_c = 0;
		cout << "Illegal input" << endl;
	}
}

double KTriangle::getHigh() const
{
	if (m_side_a == 0 || m_side_b == 0 || m_side_c == 0) return 0;
	return ((sqrt((m_side_a + m_side_c + m_side_b) * (m_side_a + m_side_b - m_side_c) * (m_side_c + m_side_b - m_side_a) * (m_side_a + m_side_c - m_side_b))) / (2 * m_side_b));
}

double KTriangle::getPerimeter() const
{
	return m_side_a + m_side_b + m_side_c;
}

double KTriangle::getArea() const
{
	return m_side_b * getHigh() / 2;
}

string KTriangle::getShape() const
{
	return "Triangle";
}
