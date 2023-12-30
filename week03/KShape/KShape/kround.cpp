#include"kround.h"
KRound::KRound(double r)
{
	if (r > 0)
	{
		m_radius = r;
	}
	else
	{
		m_radius = 0;
	}
}

double KRound::getPerimeter() const
{
	return 2 * PI * m_radius;
}
double KRound::getArea() const
{
	return PI * m_radius * m_radius;
}
string KRound::getShape() const
{
	return "Round";
}