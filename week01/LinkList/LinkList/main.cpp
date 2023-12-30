#include"klinksolution.h"
using namespace std;
int main()
{
	LinkNode* head = new LinkNode(1);
	LinkNode* tempNode = head;
	KLinkSolution solution;
	for (int i = 2; i <= 5; i++)
	{
		tempNode->next = new LinkNode(i);
		tempNode = tempNode->next;
	}
	tempNode = head;
	while (tempNode != nullptr)
	{
		cout << tempNode->val << " ";
		tempNode = tempNode->next;
	}
	cout << endl;
	LinkNode* resultNode = solution.reverseKGroup(head, 2);
	tempNode = resultNode;
	while (tempNode != nullptr)
	{
		cout << tempNode->val << " ";
		tempNode = tempNode->next;
	}
	return 0;
}