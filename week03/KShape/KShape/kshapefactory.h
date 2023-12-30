#pragma once
#ifndef _KSHAPEFACTORY_H_
#define _KSHAPEFACTORY_H_
#include"kcompoundshape.h"
#include"krectangle.h"
#include"kround.h"
#include"ksquare.h"
#include"ktrapezium.h"
#include"ktriangle.h"
class KShapeFactory
{
public:
	static KShape* productShape(const string name)
	{
		if (name == "Triangle")
		{
			double a, b, c;
			cout << "Input three sides of the triangle" << endl;
			cin >> a >> b >> c;
			return (new KTriangle(a, b, c));
		}
		else if (name == "Square")
		{
			double s;
			cout << "Input side of the square" << endl;
			cin >> s;
			return (new KSquare(s));
		}
		else if (name == "Rectangle")
		{
			double w, l;
			cout << "Input the width and length of the rectangle" << endl;
			cin >> w >> l;
			return (new KRectangle(w, l));
		}
		else if (name == "Trapezium")
		{
			double t, b, l, r;
			cout << "Input the topline baseline leftside rightside of the rectangle" << endl;
			cin >> t >> b >> l >> r;
			return (new KTrapezium(t, b, l, r));
		}
		else if (name == "Round")
		{
			double r;
			cout << "Input the radius of the round" << endl;
			cin >> r;
			return (new KRound(r));
		}
		else
			return nullptr;
	}
};
#endif // !_KSHAPEFACTORY_H_
