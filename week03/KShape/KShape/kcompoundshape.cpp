#include"kcompoundshape.h"
KCompoundshape::KCompoundshape()
{
	m_num = 0;
}
void KCompoundshape::addShape(int n, KShape* pShape[])
{
	for (int i = 0; i < n; i++)
	{
		if (pShape[i] == nullptr) break;
		m_Shapes.push_back(pShape[i]);
		m_num++;
	}
}
double KCompoundshape::getPerimeter() const
{
	double result = 0;
	for (int i = 0; i < m_num; i++)
	{
		result += m_Shapes[i]->getPerimeter();
	}
	return result;
}
double KCompoundshape::getArea() const
{
	double result = 0;
	for (int i = 0; i < m_num; i++)
	{
		result += m_Shapes[i]->getArea();
	}
	return result;
}
string KCompoundshape::getShape() const
{
	return "Compoundshape";
}