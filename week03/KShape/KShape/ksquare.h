#pragma once
#ifndef _KSQUARE_H_
#define _KSQUARE_H_
#include"kshape.h"
class KSquare :public KShape 
{
public:
	KSquare(double s);
	virtual double getPerimeter() const;
	virtual double getArea() const;
	virtual string getShape() const;
private:
	double m_side;
};
#endif // !_KSQUARE_H_
