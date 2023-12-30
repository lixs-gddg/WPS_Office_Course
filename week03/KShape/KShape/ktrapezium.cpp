#include"ktrapezium.h"
KTrapezium::KTrapezium(double t, double b, double l, double r)
{
	if (t>0 && b>0 && l>0 && r>0 && l+r>abs(t-b) && abs(l-r)<abs(t-b))
	{
		m_topline = t;
		m_baseline = b;
		m_leftside = l;
		m_rightside = r;
	}
	else
	{
		m_topline = 0;
		m_baseline = 0;
		m_leftside = 0;
		m_rightside = 0;
		cout << "Illegal input" << endl;
	}
}

double KTrapezium::getHigh() const
{
	double longer_side=0, shorter_side;
	if (m_baseline > m_topline)
	{
		longer_side = m_baseline;
		shorter_side = m_topline;
	}
	else
	{
		longer_side = m_topline;
		shorter_side = m_baseline;
	}
	double bottom = longer_side - shorter_side;
	return ((sqrt((m_leftside + m_rightside + bottom) * (m_leftside + bottom - m_rightside) * (m_rightside + bottom - m_leftside) * (m_leftside + m_rightside - bottom))) / (2 * bottom));
}
double KTrapezium::getPerimeter() const
{
	return m_baseline + m_leftside + m_rightside + m_topline;
}
double KTrapezium::getArea() const
{
	return (m_baseline + m_topline)* getHigh() / 2;
}
string KTrapezium::getShape() const
{
	return "Trapezium";
}

