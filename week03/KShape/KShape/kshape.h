#pragma once
#ifndef _KSHAPE_H_
#define _KSHAPE_H_
#include<iostream>
#include<string>
#include<cmath>
#include<vector>
using namespace std;
class KShape
{
public:
	virtual double getPerimeter() const= 0;
	virtual double getArea() const= 0;
	virtual string getShape() const= 0;
};

#endif // !_KSHAPE_H_
