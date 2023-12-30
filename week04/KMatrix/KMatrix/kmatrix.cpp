#include"kmatrix.h"

template <typename T>
KMatrix<T>::KMatrix()
{
	init(0, 0);
}


template <typename T>
KMatrix<T>::KMatrix(int row, int column)
{
	init(row, column);
}


template <typename T>
KMatrix<T>::KMatrix(const KMatrix<T>& matrix)
{
	init(matrix.getRows(), matrix.getColumns());
	auto it = matrix.begin();
	for (; it != matrix.end(); it++) {
		setData(get<0>(*it), get<1>(*it), get<2>(*it));
	}
}


template <typename T>
void KMatrix<T>::init(int row, int column)
{
	
	m_rows = row;
	m_columns = column;
	m_matrix.clear();
}

template <typename T>
int  KMatrix<T>::getRows() const
{
	return m_rows;
}


template <typename T>
int  KMatrix<T>::getColumns() const
{
	return m_columns;
}

template <typename T>
void   KMatrix<T>::setData(int row, int col, T value)//…Ë÷√÷µ
{
	if (row < 0 || col < 0 || row >= m_rows || col >= m_columns)
	{
		cout << "Illegal operation" << endl;
		return;
	}
	auto it = m_matrix.begin();
	auto index = it;
	for (; it != m_matrix.end(); it++)
	{
		if (get<0>(*it) == row && get<1>(*it) == col)
		{
			get<2>(*it) = value;
			return;
		}
		else
		{
			index = it;
			if (get<0>(*it) == row && get<1>(*it) > col)
			{
				break;
			}
		}
	}
	tuple<int, int, T> t(row, col, value);
	m_matrix.insert(it, t);
}


template <typename T>
T KMatrix<T>::getData(int row, int col)
{
	if (row < 0 || col < 0 || row >= m_rows || col >= m_columns)
	{
		cout << "Illegal operation" << endl;
		return NULL;
	}
	auto it = m_matrix.begin();
	for (; it != m_matrix.end(); it++)
	{
		if (get<0>(*it) == row && get<1>(*it) == col)
		{
			return get<2>(*it);
		}
		if (get<0>(*it) > row)
		{
			break;
		}
	}
	return 0;
}


template <typename T>
void KMatrix<T>::eraseRow(int row)
{
	if (row < 0 || row >= m_rows)
	{
		cout << "Illegal operation" << endl;
		return;
	}
	auto it = m_matrix.begin();
	for (; it != m_matrix.end();)
	{
		if(get<0>(*it)==row)
		{ 
			it = m_matrix.erase(it);
		}
		else
		{
			if (get<0>(*it) > row)
			{
				get<0>(*it) = get<0>(*it) - 1;
			}
			it++;
		}
	}
	m_rows--;
}


template <typename T>
void KMatrix<T>::eraseCol(int col)
{
	if (col < 0 || col >= m_columns)
	{
		cout << "Illegal operation" << endl;
		return;
	}
	auto it = m_matrix.begin();
	for (; it != m_matrix.end();)
	{
		if (get<1>(*it) == col)
		{
			it = m_matrix.erase(it);
		}
		else
		{
			if (get<1>(*it) > col)
			{
				get<1>(*it) = get<1>(*it) - 1;
			}
			it++;
		}
	}
	m_columns--;
}

template <typename T1>
KMatrix<T1> operator+(KMatrix<T1>a, KMatrix<T1>b)
{
	if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
	{
		cout << "Illegal operation" << endl;
		KMatrix<T1> ans(0, 0);
		return ans;
	}
	KMatrix<T1> ans(a.getRows(), a.getColumns());
	vector<vector<T1> > _a, _b;
	vector<T1> temp;
	for (int i = 0; i < a.getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = a.begin();
	for (; ita != a.end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getColumns(); j++)
		{
			T1 tempdata = _a[i][j] + _b[i][j];
			if (tempdata != 0)
			{
				ans.setData(i, j, tempdata);
			}
		}
	}
	return ans;
}

template <typename T1>
KMatrix<T1> operator-(KMatrix<T1>a, KMatrix<T1>b)
{
	if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
	{
		cout << "Illegal operation" << endl;
		KMatrix<T1> ans(0, 0);
		return ans;
	}
	KMatrix<T1> ans(a.getRows(), a.getColumns());
	vector<vector<T1> > _a, _b;
	vector<T1> temp;
	for (int i = 0; i < a.getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = a.begin();
	for (; ita != a.end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getColumns(); j++)
		{
			T1 tempdata = _a[i][j] - _b[i][j];
			if (tempdata != 0)
			{
				ans.setData(i, j, tempdata);
			}
		}
	}
	return ans;
}

template <typename T1>
KMatrix<T1> operator*(KMatrix<T1>a, KMatrix<T1>b)
{
	if (a.getColumns() != b.getRows())
	{
		cout << "Illegal operation" << endl;
		KMatrix<T1> ans(0, 0);
		return ans;
	}
	KMatrix<T1> ans(a.getRows(), b.getColumns());
	vector<vector<T1> > _a, _b;
	vector<T1> temp;
	for (int i = 0; i < a.getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = a.begin();
	for (; ita != a.end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	for (int i = 0; i < a.getRows(); i++)
	{
		for (int j = 0; j < a.getColumns(); j++)
		{
			T1 tempdata =0;
			for (int k = 0; k < b.getColumns(); k++)
			{
				tempdata += _a[i][k] * _b[k][j];
			}
			if (tempdata != 0)
			{
				ans.setData(i, j, tempdata);
			}
		}
	}
	return ans;
}

template<typename T>
void KMatrix<T>::operator+=(const KMatrix<T>&b)
{
	if (m_rows != b.getRows() || m_columns != b.getColumns())
	{
		cout << "Illegal operation" << endl;
		return;
	}
	vector<vector<T> > _a, _b;
	vector<T> temp;
	for (int i = 0; i < getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = begin();
	for (; ita != end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			T tempdata = _a[i][j]+_b[i][j];
			if (tempdata != 0)
			{
				setData(i, j, tempdata);
			}
		}
	}
}

template<typename T>
void KMatrix<T>::operator-=(const KMatrix<T>& b)
{
	if (m_rows != b.getRows() || m_columns != b.getColumns())
	{
		cout << "Illegal operation" << endl;
		return;
	}
	vector<vector<T> > _a, _b;
	vector<T> temp;
	for (int i = 0; i < getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = begin();
	for (; ita != end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < getColumns(); j++)
		{
			T tempdata = _a[i][j] - _b[i][j];
			if (tempdata != 0)
			{
				setData(i, j, tempdata);
			}
		}
	}
}

template<typename T>
void KMatrix<T>::operator*=(const KMatrix<T>& b)
{
	if (m_columns != b.getRows())
	{
		cout << "Illegal operation" << endl;
		return;
	}
	vector<vector<T> > _a, _b;
	vector<T> temp;
	for (int i = 0; i < getColumns(); i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < getRows(); i++)
	{
		_a.push_back(temp);
		_b.push_back(temp);
	}
	auto ita = begin();
	for (; ita != end(); ita++)
	{
		_a[get<0>(*ita)][get<1>(*ita)] = get<2>(*ita);
	}
	auto itb = b.begin();
	for (; itb != b.end(); itb++)
	{
		_b[get<0>(*itb)][get<1>(*itb)] = get<2>(*itb);
	}
	init(getRows(), b.getColumns());
	for (int i = 0; i < getRows(); i++)
	{
		for (int j = 0; j < b.getRows(); j++)
		{
			T tempdata = 0;
			for (int k = 0; k < b.getColumns(); k++)
			{
				tempdata += _a[i][k] * _b[k][j];
			}
			if (tempdata != 0)
			{
				setData(i, j, tempdata);
			}
		}
	}
}

template <typename T>
auto KMatrix<T>::begin() const
{
	return m_matrix.begin();
}


template <typename T>
auto KMatrix<T>::end() const
{
	return m_matrix.end();
}


template <typename T>
KMatrix<T> KMatrix<T>::transpose() 
{
	KMatrix<T> ans(m_columns, m_rows); 
	auto it = m_matrix.begin();
	for (; it != m_matrix.end(); it++) {
		ans.setData(get<1>(*it), get<0>(*it), get<2>(*it)); 
	}
	return ans;
}


template <typename T>
void KMatrix<T>::print() const
{
	if (m_rows * m_columns == 0)
	{
		cout << "Empty matrix" << endl;
		return;
	}
	auto it = m_matrix.begin();
	vector<vector<T> >ans;
	vector<T> temp;
	int x = 3;
	if (sizeof(T) == sizeof(int) || sizeof(T) == sizeof(short)) x = 3;
	else if (sizeof(T) == sizeof(float)|| sizeof(T) == sizeof(double) || sizeof(T) == sizeof(long)) x = 6;
	for (int i = 0; i < m_columns; i++)
	{
		temp.push_back(0);
	}
	for (int i = 0; i < m_rows; i++)
	{
		ans.push_back(temp);
	}
	for (; it != m_matrix.end(); it++)
	{
		ans[get<0>(*it)][get<1>(*it)] = get<2>(*it);
	}
	for (int i = 0; i < m_rows; i++)
	{
        for (int j = 0; j < m_columns; j++)
		{
			cout<< left << setw(x) << ans[i][j] << " ";
		}
		cout << endl;
	}	
}


template <typename T>
vector<tuple<int, int, T>>& KMatrix<T>::getMatrix()
{
	return m_matrix;
}