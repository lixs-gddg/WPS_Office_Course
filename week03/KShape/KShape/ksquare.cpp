#include"ksquare.h"
KSquare::KSquare(double s)
{
	if (s > 0)
	{
		m_side = s;
	}
	else
	{
		m_side = 0;
		cout << "Illegal input" << endl;
	}
}

double KSquare::getPerimeter() const
{
	return 4 * m_side;
}
double KSquare::getArea() const
{
	return  m_side * m_side;
}
string KSquare::getShape() const
{
	return "Square";
}