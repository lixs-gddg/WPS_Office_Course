#include"klinksolution.h"
LinkNode* KLinkSolution::reverseKGroup(LinkNode* head, int k)
{
	LinkNode* frontHeadNode = new LinkNode();
	LinkNode* groupPreNode, * groupHeadNode, * groupTailNode, * curNode, * curNextNode;
	frontHeadNode->next = head;
	groupPreNode = frontHeadNode;
	groupHeadNode = head;
	while (groupHeadNode != nullptr)
	{
		groupTailNode = groupPreNode;
		for (int i = 0; i < k; i++) 
		{
			groupTailNode = groupTailNode->next;
			if (groupTailNode == nullptr) return frontHeadNode->next;
		}
		curNode = groupHeadNode;
		for (int i = 0; i < k - 1; i++)
		{
			curNextNode = curNode->next;
			curNode->next = groupTailNode->next;
			groupTailNode->next = curNode;
			curNode = curNextNode;
		}
		groupPreNode->next = groupTailNode;
		groupPreNode = groupTailNode;
		for (int i = 0; i < k - 1; i++)
		{
			groupPreNode = groupPreNode->next;
		}
		groupHeadNode = groupPreNode->next;
	}
	return frontHeadNode->next;
}