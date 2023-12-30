#pragma once
#ifndef _KTRIANGLE_H_
#define _KTRIANGLE_H_
#include"kshape.h"

class KTriangle : public KShape
{
public:
	KTriangle(double _side_a, double _side_b, double _side_c);
	double getHigh()const;
	virtual double getPerimeter() const;
	virtual double getArea() const ;
	virtual string getShape() const ;
private:
	double m_side_a, m_side_b, m_side_c;
};
#endif // !_KTRIANGLE_H_
