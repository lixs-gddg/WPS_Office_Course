#include"kshapefactory.h"
int main()
{
	/*简单工厂模式生成常规的5种形状*/
	KShape* K[5];
	K[0]= KShapeFactory::productShape("Triangle");
	cout << K[0]->getShape() << " " << K[0]->getPerimeter() << " " << K[0]->getArea() << endl;
	K[1] = KShapeFactory::productShape("Square");
	cout << K[1]->getShape() << " " << K[1]->getPerimeter() << " " << K[1]->getArea() << endl;
	K[2] = KShapeFactory::productShape("Rectangle");
	cout << K[2]->getShape() << " " << K[2]->getPerimeter() << " " << K[2]->getArea() << endl;
	K[3] = KShapeFactory::productShape("Trapezium");
	cout << K[3]->getShape() << " " << K[3]->getPerimeter() << " " << K[3]->getArea() << endl;
	K[4] = KShapeFactory::productShape("Round");
	cout << K[4]->getShape() << " " << K[4]->getPerimeter() << " " << K[4]->getArea() << endl;
	/*复合形状单独*/
	KCompoundshape KC;
	KC.addShape(5, K);
	cout << KC.getShape() << " " << KC.getPerimeter() << " " << KC.getArea() << endl;
	/*包含复合形状的复合形状*/
	KCompoundshape KC2;
	KShape* KT[6];
	for (int i = 0; i < 5; i++) KT[i] = K[i];
	KT[5] = &KC;
	KC2.addShape(6, KT);
	cout << KC2.getShape() << " " << KC2.getPerimeter() << " " << KC2.getArea() << endl;
	return 0;
}