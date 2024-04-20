#pragma once
#include <string>

using namespace std;

class Set 
{
private:
	// Flags for rotations
	bool leftleft, leftright, rightleft, rightright;

public:
	struct Data // Data for in crime report
	{
		string caseNum;
		string dateRptd;
		string dateOCC;
		string timeOCC;
		string areaName;
		Data()
		{
			this->caseNum = "";
			this->dateRptd = "";
			this->dateOCC = "";
			this->timeOCC = "";
			this->areaName = "";
		}
		Data(string caseNum, string dateRptd, string dateOCC, string timeOCC, string areaName)
		{
			this->caseNum = caseNum;
			this->dateRptd = dateRptd;
			this->dateOCC = dateOCC;
			this->timeOCC = timeOCC;
			this->areaName = areaName;
		}
	};

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

	void insert(string caseNum, string dateRptd, string dateOCC, string timeOCC, string areaName)
	{
		Data data = Data(caseNum, dateRptd, dateOCC, timeOCC, areaName);
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

	void printTree()
	{
		printer(head);
	}
	void printer(CrimeReport* head)
	{
		if (head != nullptr)
		{
			cout << head->data.caseNum << endl;
			printer(head->lchild);
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
		if (head->parent->rchild == head) 
		{
			if (head->parent->lchild == nullptr || head->parent->lchild->color == 'B') 
			{
				if (head->lchild != nullptr && head->lchild->color == 'R')
				{
					rightleft = true;
				}
				else if (head->rchild != nullptr && head->rchild->color == 'R')
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
		else 
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