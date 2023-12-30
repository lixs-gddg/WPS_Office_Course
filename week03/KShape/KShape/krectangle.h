#pragma once
#ifndef _KRECTANGLE_H_
#define _KRECTANGLE_H_
#include"kshape.h"
class KRectangle : public KShape
{
public:
	KRectangle(double w, double l);
	virtual double getPerimeter() const;
	virtual double getArea() const;
	virtual string getShape() const;
private:
	double m_width, m_length;
};
#endif // !_KRECTANGLE_H_
