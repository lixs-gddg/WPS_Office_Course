#pragma once
#ifndef _KTRAPEZIUM_H_
#define _KTRAPEZIUM_H_
#include"kshape.h"
class KTrapezium :public KShape
{
public:
	KTrapezium(double t, double b, double l, double r);
	double getHigh()const;
	virtual double getPerimeter() const;
	virtual double getArea() const;
	virtual string getShape() const;
private:
	double m_topline, m_baseline, m_leftside, m_rightside;
};
#endif // !_KTRAPEZIUM_H_
