#pragma once
#ifndef _KMATRIX_H_
#define _KMATRIX_H_
#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
using namespace std;

template <typename T>
class KMatrix
{
public:
	KMatrix();
	KMatrix(int row , int column ); 
	KMatrix(const KMatrix<T>& matrix); 
	void  init(int row=0, int column=0);  
	int  getRows() const;
	int  getColumns() const; 
	void setData(int row, int col, T value);
	T  getData(int row, int col); 
	void  eraseRow(int row); 
	void eraseCol(int col);
	template <typename T1>
	friend KMatrix<T1> operator+(KMatrix<T1>a, KMatrix<T1>b);
	template <typename T1>
	friend KMatrix<T1> operator-(KMatrix<T1>a, KMatrix<T1>b);
	template <typename T1>
	friend KMatrix<T1> operator*(KMatrix<T1>a, KMatrix<T1>b);
	KMatrix<T> transpose(); 
	void print() const; 
	auto begin() const; //迭代访问器
	auto end() const;
	virtual void operator+=(const KMatrix<T>& b);
	virtual void operator-=(const KMatrix<T>& b);
	virtual void operator*=(const KMatrix<T>& b);
private:
	int m_rows, m_columns;
	vector <tuple<int, int, T>> m_matrix; //三元组，分别存储矩阵元素的行、列、值，压缩储存稀疏矩阵
	vector<tuple<int, int, T>>& getMatrix(); //获取矩阵
};

#endif // !_KMATRIX_H_
