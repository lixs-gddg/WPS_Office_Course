#include"ksostring.h"
int main()
{
	cout << "char：" << endl;
	KsoString<char> test;
	test.KsoStringAppend(3, "abc");
	cout << test.KsoStringSize() << endl;
	test.KsoStringPrint();
	test.KsoStringInsert(3, 'd');
	test.KsoStringPrint();
	test.KsoStringErase(3);
	test.KsoStringPrint();
	test.KsoStringAppend(3, "ddd");
	test.KsoStringPrint();
	test.KsoStringErase('d');
	test.KsoStringPrint();
	cout<<test.KsoStringGetBegin()->m_value<<endl;
	cout << test.KsoStringGetEnd()->m_value << endl;
	cout << test[0] << endl;
	cout << test[-1] << endl;
	cout << test[10] << endl;
	cout << "WCHAR：" << endl;
	KsoString<wchar_t> test2;
	test2.KsoStringAppend(3, L"一二三");
	cout << test2.KsoStringSize() << endl;
	test2.KsoStringPrint();
	test2.KsoStringInsert(3, L'四');
	test2.KsoStringPrint();
	test2.KsoStringErase(3);
	test2.KsoStringPrint();
	test2.KsoStringAppend(3,L"四四四");
	test2.KsoStringPrint();
	test2.KsoStringErase(L'四');
	test2.KsoStringPrint();
	return 0;
}