#pragma once
#ifndef _KSOSTRING_H_
#define _KSOSTRING_H_
#include <iostream>
#include <wchar.h>
#include <locale.h>
using namespace std;
template<typename T>
struct listNode
{
public:
	static_assert(sizeof(T) == sizeof(char) || sizeof(T) == sizeof(wchar_t), "The type of T is error");/*限制类型只能是char或者WCHAR*/
	T m_value;
	listNode* lastNode;
	listNode *nextNode;
	listNode():m_value(0),lastNode(nullptr),nextNode(nullptr){}
	listNode(T val):m_value(val),lastNode(nullptr),nextNode(nullptr){}
};
template<typename T>
class KsoString
{
public:
	KsoString()
	{
		beginNode = new listNode<T>();
		endNode = new listNode<T>();
		m_len = 0;
	}
	int KsoStringSize()
	{
		return m_len;
	}
	KsoString KsoStringInsert(int index,T character)//插入字符
	{
		if (index < 0 || index>m_len) return *this;
		listNode<T> *tempNode = new listNode<T>(character);
		if (index == 0)
		{
			tempNode->nextNode = beginNode;
			beginNode->lastNode = tempNode;
			beginNode = tempNode;
			m_len++;
			if (m_len == 1)
			{
				endNode = beginNode;
			}
			return *this;
		}
		if (index <= m_len - 1)
		{
			listNode<T> *curNode = beginNode;
			for (int i = 0; i < index; i++)
			{
				curNode = curNode->nextNode;
			}
			tempNode->lastNode = curNode->lastNode;
			tempNode->nextNode = curNode;
			curNode->lastNode->nextNode = tempNode;
			curNode->lastNode = tempNode;
			m_len++;
			return *this;
		}
		if (index == m_len)
		{
			endNode->nextNode = tempNode;
			tempNode->lastNode = endNode;
			endNode = tempNode;
			m_len++;
			return *this;
		}
	}
	KsoString KsoStringErase(int index)//删除index位置的字符
	{
		if (index < 0 || index >= m_len)
		{
			return *this;
		}
		listNode<T>* curNode = beginNode;
		if (index == 0)
		{
			beginNode = curNode->nextNode;
			beginNode->lastNode = nullptr;
			m_len--;
			delete curNode;
			return *this;
		}
		if (index < m_len - 1)
		{
			for (int i = 0; i < index; i++)
			{
				curNode = curNode->nextNode;
			}
			curNode->lastNode->nextNode = curNode->nextNode;
			curNode->nextNode->lastNode = curNode->lastNode;
			m_len--;
			delete curNode;
			return *this;
		}
		curNode = endNode;
		endNode = endNode->lastNode;
		endNode->nextNode = nullptr;
		m_len--;
		delete curNode;
		return *this;
	}
	KsoString KsoStringErase(T character)//删除所有character字符
	{
		for (int i = 0; i < KsoStringSize(); i++)
		{
			if (operator[](i) == character)
			{
				KsoStringErase(i);
				i--;
			}
		}
		return *this;
	}
	T operator [](int index)
	{
		if (index<0 || index>m_len - 1) return 0;
		listNode<T>* curNode = beginNode;
		for (int i = 0; i < index; i++)
		{
			curNode = curNode->nextNode;
		}
		return curNode->m_value;
	}
	KsoString KsoStringAppend(int n, const T* characters)//追加字符
	{
		if (n <= 0) return *this;
		for (int i = 0; i < n; i++)
		{
			KsoStringInsert(m_len, *(characters + i));
		}
		return *this;
	}
	void KsoStringPrint()//打印字符串
	{
		if (sizeof(beginNode->m_value) == sizeof(char))
		{
			for (int i = 0; i < KsoStringSize(); i++)
				cout << operator[](i);
			cout << endl;
		}
		else
		{
			setlocale(LC_ALL, "zh-CN");
			for (int i = 0; i < KsoStringSize(); i++)
				putwchar(operator[](i));
			cout << endl;
		}
	}
	listNode<T>* KsoStringGetBegin()
	{
		return beginNode;
	}
	listNode<T>* KsoStringGetEnd()
	{
		return endNode;
	}
private:
	listNode<T> *beginNode,*endNode;
	int m_len;
};

#endif // !_KSOSTRING_H_
