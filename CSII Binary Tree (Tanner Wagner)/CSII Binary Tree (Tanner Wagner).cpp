#include <iostream>
using namespace std;
#define COUNT 4

// After some research, free(), "Display amount of free and used memory in the system."
// Usually used with malloc() but doens't really apply to me because I have new()

struct MyNode
{
	int myData;
	MyNode* treeLeft;
	MyNode* treeRight;
};

MyNode* newNode(int myData)
{
	MyNode* node = new MyNode;
	node->myData = myData;
	node->treeLeft = node->treeRight = NULL;

	return node;
}

MyNode* nodeSearch(MyNode* myRoot, int myData)
{
	if (myRoot == NULL || myRoot->myData == myData)
	{
		return myRoot;
	}
	if (myRoot->myData < myData)
	{
		return nodeSearch(myRoot->treeRight, myData);
	}
	else
	{
		return nodeSearch(myRoot->treeLeft, myData);
	}
}

MyNode* insertNode(MyNode* myRoot, int myData)
{
	if (myRoot == NULL)
	{
		return newNode(myData);
	}
	if (myData < myRoot->myData)
	{
		myRoot->treeLeft = insertNode(myRoot->treeLeft, myData);
	}
	else if (myData > myRoot->myData)
	{
		myRoot->treeRight = insertNode(myRoot->treeRight, myData);
	}
	return myRoot;
}

MyNode* minValueNode(MyNode* node) // Needed for delete
{
	MyNode* myCurrent = node;

	while (myCurrent && myCurrent->treeLeft != NULL)
	{
		myCurrent = myCurrent->treeLeft;
	}
	return myCurrent;
}

MyNode* deleteNode(MyNode* myRoot, int myData)
{
	if (myRoot == NULL)
	{
		return myRoot;
	}
	if (myData < myRoot->myData)
	{
		myRoot->treeLeft = deleteNode(myRoot->treeLeft, myData);
	}
	else if (myData > myRoot->myData)
	{
		myRoot->treeRight = deleteNode(myRoot->treeRight, myData);
	}
	else
	{
		if (myRoot->treeLeft == NULL)
		{
			MyNode* myTemp = myRoot->treeRight;
			free(myRoot);
			return myTemp;
		}
		else if (myRoot->treeRight == NULL)
		{
			MyNode* myTemp = myRoot->treeLeft;
			free(myRoot);
			return myTemp;
		}
		MyNode* myTemp = minValueNode(myRoot->treeRight);
		myRoot->myData = myTemp->myData;
		myRoot->treeRight = deleteNode(myRoot->treeRight, myTemp->myData);
	}
	return myRoot;
}

void printNode(MyNode* myRoot, int mySpace)
{
	if (myRoot == NULL) // Base
	{
		return;
	}

	mySpace += COUNT;

	printNode(myRoot->treeRight, mySpace);
	printf("\n");

	for (int i = COUNT; i < mySpace; ++i)
	{
		printf("  ");
	}

	printf("%d\n", myRoot->myData);
	printNode(myRoot->treeLeft, mySpace);
}

void normPrint(MyNode* myRoot)
{
	printNode(myRoot, 0);
}

int main()
{
	// FIXME: crashes when deleting 1
	int myArr[] = { 5,3,7,1,4,6,9,8 };
	MyNode* myRoot = NULL;

	for (int myData : myArr)
	{
		myRoot = insertNode(myRoot, myData);
	}

	// For user:
	cout << "In-order traversal:" << endl << endl;
	normPrint(myRoot);
	deleteNode(myRoot, 8);
	cout << "In-order traversal after deletion:" << endl << endl;
	normPrint(myRoot);

	return 0;
}
// Final Draft: