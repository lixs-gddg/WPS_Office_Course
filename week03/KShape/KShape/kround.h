#pragma once
#ifndef _KROUND_H_
#define _KROUND_H_
#include"kshape.h"
#define PI 3.1415926
class KRound :public KShape
{
public:
	KRound(double r);
	virtual double getPerimeter() const;
	virtual double getArea() const;
	virtual string getShape() const;
private:
	double m_radius;
};
#endif // !_KROUND_H_
