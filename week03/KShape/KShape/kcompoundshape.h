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
	int m_num;//���ͼ�εĸ���
	vector <KShape*> m_Shapes;//���ͼ������
};
#endif // !_KCOMPOUNDSHAPE_H_
