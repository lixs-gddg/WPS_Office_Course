#pragma once
#ifndef _KLINKSOLUTION_H_
#define _KLINKSOLUTION_H_
#include <iostream>

struct LinkNode
{
	int val;
	LinkNode* next;
	LinkNode() :val(0), next(nullptr) {}
	LinkNode(int x) :val(x), next(nullptr) {}
	LinkNode(int x, LinkNode* next) :val(x), next(next) {}
};

class KLinkSolution
{
public:
	LinkNode* reverseKGroup(LinkNode* head, int k);
};
#endif //__KLINKSOLUTION_H_
