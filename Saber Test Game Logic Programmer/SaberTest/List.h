#pragma once
#include <string>

// структуру ListNode модифицировать нельзя
struct ListNode
{
    ListNode* prev;
    ListNode* next;
    ListNode* rand; // указатель на произвольный элемент данного списка, либо NULL
    std::string data;
};


class List
{
public:
	List() : head(nullptr), tail(nullptr), count(0) {}

	void Serialize(FILE* file);		
	void Deserialize(FILE* file);
	

	void PushHead(std::string newData);

	void PushTail(std::string newData);

	void UpdateRandomPointers();

	ListNode* GetRandomListNode(int dice_roll);

	void PrintList();

private:
	
	ListNode* head;
	ListNode* tail;
	int count;
};
