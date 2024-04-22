#pragma once
#include <iostream>
#include <string>
#include <queue>
#include "data.h"

using namespace std;

class Set 
{
private:
	// Flags for rotations
	bool leftleft, leftright, rightleft, rightright;

public:
	struct CrimeReport // Nodes to store in set
	{
		Data data;
		CrimeReport(Data data)
		{
			this->data = data;
		}
		char color;
		CrimeReport* parent = nullptr;
		CrimeReport* lchild = nullptr;
		CrimeReport* rchild = nullptr;
	};
	CrimeReport* head;
	int size = 0;
	Set() // Constructor
	{
		// Main head
		head = nullptr;
		// Rotations
		leftleft = false;
		leftright = false;
		rightleft = false;
		rightright = false;

	}

	void insert(string caseNum, string dateOCC, string timeOCC, string areaName)
	{
		Data data = Data(caseNum, dateOCC, timeOCC, areaName);
		this->size++;
		if (head != nullptr)
		{
			head = insertHelper(head, data);
		}
		else
		{
			head = new CrimeReport(data);
			head->color = 'B';
		}
	}

	CrimeReport* insertHelper(CrimeReport* head, Data data);
	CrimeReport* rotateLeft(CrimeReport* report);
	CrimeReport* rotateRight(CrimeReport* report);

	bool inSet(CrimeReport* head, Data data);

	void printTree()
	{
		printer(head);
	}
	void printer(CrimeReport* head)
	{
		if (head != nullptr)
		{
			printer(head->lchild);
			cout << head->data.caseNum << endl;
			printer(head->rchild);
		}
	}
};

Set::CrimeReport* Set::insertHelper(CrimeReport* head, Data data)
{
	bool conflict = false;

	// Make sure head exists
	if (head == nullptr)
	{
		return new CrimeReport(data);
	}
	else if (data.caseNum < head->data.caseNum) // if caseNum < head
	{
		// insert left
		head->lchild = Set::insertHelper(head->lchild, data);
		head->lchild->parent = head;
		// Check for color conflict if this is not the head
		if (this->head != head)
		{
			if (head->lchild->color == 'R' && head->color == 'R')
			{
				conflict = true; // fix color after rotations
			}
		}
	}
	else // caseNum > head
	{
		// insert right
		head->rchild = insertHelper(head->rchild, data);
		head->rchild->parent = head;
		// Check for color conflict if this is not the head
		if (this->head != head)
		{
			if (head->rchild->color == 'R' && head->color == 'R')
			{
				conflict = true; // fix color after rotations
			}
		}
	}

	// Rotate if necessary
	if (leftleft) // Left case
	{
		// Left rotate
		head = Set::rotateLeft(head);
		// Color swap
		head->color = 'B';
		head->lchild->color = 'R';
		// Reset values
		leftleft = false;
	}
	else if (leftright) // Left right case
	{
		// Left rotate
		head->lchild = Set::rotateLeft(head->lchild);
		head->lchild->parent = head;
		// Right rotate
		head = Set::rotateRight(head);
		//Color swap
		head->color = 'B';
		head->rchild->color = 'R';
		//Reset values
		leftright = false;
	}
	else if (rightleft) // Right left case
	{
		// Right rotate
		head->rchild = Set::rotateRight(head->rchild);
		head->rchild->parent = head;
		// Left rotate
		head = Set::rotateLeft(head);
		// Color swap
		head->color = 'B';
		head->lchild->color = 'R';
		// Reset values
		rightleft = false;
	}
	else if (rightright) // Right case
	{
		// Right rotate
		head = Set::rotateRight(head);
		// Color swap
		head->color = 'B';
		head->rchild->color = 'R';
		// Reset values
		rightright = false;
	}


	if (conflict) // Color conflicts
	{
		if (head->parent->rchild == head)  // if right child
		{
			if (head->parent->lchild == nullptr || head->parent->lchild->color == 'B') // if no left child or left child is black
			{
				if (head->lchild != nullptr && head->lchild->color == 'R') // if left child exists and left child is red
				{
					rightleft = true;
				}
				else if (head->rchild != nullptr && head->rchild->color == 'R') // right child exists and right child is red
				{
					leftleft = true;
				}
			}
			else 
			{
				head->parent->lchild->color = 'B';
				head->color = 'B';
				if (head->parent != this->head)
				{
					head->parent->color = 'R';
				}
			}
		}
		else // Repeat for right side
		{
			if (head->parent->rchild == nullptr || head->parent->rchild->color == 'B') 
			{
				if (head->lchild != nullptr && head->lchild->color == 'R')
				{
					rightright = true;
				}
				else if (head->rchild != nullptr && head->rchild->color == 'R')
				{
					leftright = true;
				}
			}
			else 
			{
				head->parent->rchild->color = 'B';
				head->color = 'B';
				if (head->parent != this->head)
				{
					head->parent->color = 'R';
				}
			}
		}
		// Reset conflict
		conflict = false;
	}
	return head;
}

Set::CrimeReport* Set::rotateLeft(CrimeReport* report)
{
	CrimeReport* newHead = report->rchild;
	CrimeReport* temp = newHead->lchild;
	newHead->lchild = report;
	report->rchild = temp;
	report->parent = newHead;
	if (temp != nullptr)
	{
		temp->parent = report;
	}
	return newHead;
}

Set::CrimeReport* Set::rotateRight(CrimeReport* report)
{
	CrimeReport* newHead = report->lchild;
	CrimeReport* temp = newHead->rchild;
	newHead->rchild = report;
	report->lchild = temp;
	report->parent = newHead;
	if (temp != nullptr)
	{
		temp->parent = report;
	}
	return newHead;
}

bool Set::inSet(CrimeReport* head, Data data)
{
	if (head == nullptr)
	{
		return false;
	}

	if (data.caseNum < head->data.caseNum)
	{
		return inSet(head->lchild, data);
	}
	else if (data.caseNum > head->data.caseNum)
	{
		return inSet(head->rchild, data);
	}
	else // Equal to val
	{
		return true;
	}

}

Set setUnion(Set set1, Set set2)
{
	Set newSet = set1;
	queue<Set::CrimeReport*> queue;
	Set::CrimeReport* temp = set2.head;
	queue.push(temp);
	while (!queue.empty())
	{
		if (temp->lchild != nullptr)
		{
			queue.push(temp->lchild);
		}
		if (temp->rchild != nullptr)
		{
			queue.push(temp->rchild);
		}
		if (!newSet.Set::inSet(newSet.head, temp->data))
		{
			newSet.insert(temp->data.caseNum, temp->data.dateOCC, temp->data.timeOCC, temp->data.areaName);
		}
		queue.pop();
		if (queue.empty())
		{
			break;
		}
		temp = queue.front();
	}
	return newSet;
}