﻿#include "kmatrix.h"
#include "kmatrix.cpp"
int main()
{
    //int型
    KMatrix<int> a(3, 3);
    a.setData(1, 1, 1);
    a.setData(1, 2, 4);
    a.setData(2, 2, 3);
    a.setData(2, 1, 1);
    a.setData(2, 0, 4);
    a.setData(0, 1, 3);
    cout << "矩阵a:" << endl;
    a.print();
    cout << "getData取a(1,2)处的值：";
    cout << a.getData(1, 2) << endl;
    cout << "a的转置矩阵：" << endl;
    a=a.transpose();
    a.print();
    cout << "setData改a(0,1)处的值为4：" << endl;
    a.setData(0, 1, 4);
    a.print();
    cout << "删除a第0行:" << endl;
    a.eraseRow(0);
    a.print();
    cout << "删除a第1列:" << endl;
    a.eraseCol(1);
    a.print();
    cout << "新建矩阵b，使其等于a:" << endl;
    KMatrix<int> b=a;
    b.print();
    KMatrix<int> c = a+b;
    cout << "新建矩阵c，使其等于a+b:" << endl;
    c.print();
    cout << "新建矩阵d，使其等于b-c:" << endl;
    KMatrix<int> d = b-c;
    d.print();
    cout << "新建矩阵x，使其等于a * b:" << endl;
    KMatrix<int> x = a * b;
    x.print();
    cout << "x矩阵init(4,4):" << endl;
    x.init(4, 4);
    x.print();
    cout << "b+=c后，b:" << endl;
    b += c;
    b.print();
    cout << "b-=c后，b:" << endl;
    b -= c;
    b.print();
    cout << "c*=b后，c:" << endl;
    c *= b;
    c.print();
    //double型
   /* KMatrix<double> a(3, 3);
    a.setData(1, 1, 1.2);
    a.setData(1, 2, 4.1);
    a.setData(2, 2, 3.3);
    a.setData(2, 1, 1.4);
    a.setData(2, 0, 4.6);
    a.setData(0, 1, 3.7);
    cout << "矩阵a:" << endl;
    a.print();
    cout << "getData取a(1,2)处的值：";
    cout << a.getData(1, 2) << endl;
    cout << "a的转置矩阵：" << endl;
    a = a.transpose();
    a.print();
    cout << "setData改a(0,1)处的值为4：" << endl;
    a.setData(0, 1, 4.0);
    a.print();
    cout << "删除a第0行:" << endl;
    a.eraseRow(0);
    a.print();
    cout << "删除a第1列:" << endl;
    a.eraseCol(1);
    a.print();
    cout << "新建矩阵b，使其等于a:" << endl;
    KMatrix<double> b = a;
    b.print();
    KMatrix<double> c = a + b;
    cout << "新建矩阵c，使其等于a+b:" << endl;
    c.print();
    cout << "新建矩阵d，使其等于b-c:" << endl;
    KMatrix<double> d = b - c;
    d.print();
    cout << "新建矩阵x，使其等于a * b:" << endl;
    KMatrix<double> x = a * b;
    x.print();
    cout << "x矩阵init(4,4):" << endl;
    x.init(4, 4);
    x.print();
    cout << "b+=c后，b:" << endl;
    b += c;
    b.print();
    cout << "b-=c后，b:" << endl;
    b -= c;
    b.print();
    cout << "c*=b后，c:" << endl;
    c *= b;
    c.print();*/
    return 0;
}

