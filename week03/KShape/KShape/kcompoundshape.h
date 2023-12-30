#pragma once
#ifndef _KCOMPOUNDSHAPE_H_
#define _KCOMPOUNDSHAPE_H_
#include"kshape.h"
class KCompoundshape :public KShape
{
public:
	KCompoundshape();
	virtual void addShape(int n,KShape *pShape[]);
	virtual double getPerimeter() const;
	virtual double getArea() const;
	virtual string getShape() const;
private:
	int m_num;//组合图形的个数
	vector <KShape*> m_Shapes;//组合图形容器
};
#endif // !_KCOMPOUNDSHAPE_H_
