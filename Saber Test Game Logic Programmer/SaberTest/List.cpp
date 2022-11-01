#include "List.h"
#include <random>
#include <iostream>
#include <unordered_map>

void List::Serialize(FILE* file)
{
	fwrite(&count,sizeof(count),1,file);
	std::unordered_map<ListNode*, int> rndIndecies;

	std::cout << "Serialize: " << count << "\n";
	PrintList();

	int counter = 0;

	auto currentNode = head;
	while (currentNode != nullptr)
	{		
		size_t sLength = currentNode->data.length();
		fwrite(&sLength, sizeof(sLength), 1, file);
		fwrite(currentNode->data.c_str(), sizeof(const char), sLength, file);
		
		rndIndecies.insert({ currentNode,counter });
		counter++;
		currentNode = currentNode->next;
	}

	currentNode = head;
	while (currentNode != nullptr)
	{		
		auto rndNodeNum = currentNode->rand == nullptr ? -1 : rndIndecies[currentNode->rand];
		
		fwrite(&rndNodeNum, sizeof(rndNodeNum), 1, file);

		std::cout << "Write Id rnd ref: " << rndNodeNum << "\n";

		currentNode = currentNode->next;
	}

	
	fclose(file);
}

void List::Deserialize(FILE* file)
{
	int nodeCount = 0;
	fread(&nodeCount, sizeof(nodeCount), 1, file);

	std::cout << "\nDeserialize: " << nodeCount << "\n";

	std::vector<ListNode*> nodes;
	nodes.reserve(nodeCount);
	
	for (auto i = 0; i < nodeCount; ++i)
	{
		size_t sLength;
		fread(&sLength, sizeof(sLength), 1, file);
	
		std::string dataString(sLength, '\0');
		fread(&dataString[0], sizeof(const char), (size_t)sLength, file);

		PushTail(dataString);
		nodes.push_back(tail);
		
	}

	for (auto i = 0; i < nodeCount; i++)
	{
		int val = 0;
		fread(&val, sizeof(val), 1, file);
		std::cout << "Id rnd ref: " << val<<"\n";

		if (val == -1)
		{
			nodes[i]->rand = nullptr;
		}
		else
		{
			nodes[i]->rand = nodes[val];
		}
		
	}

	PrintList();
	fclose(file);
	
}

void List::PushHead(std::string newData)
{
	// Create new node
	ListNode* newNode = new ListNode{ nullptr, nullptr, nullptr, newData };
	// Remember current head
	ListNode* oldHead = head;
	// If List not empty
	if (head != nullptr)
	{
		// For the current head pointer, set the previous pointer to a new pointer.
		head->prev = newNode;
		// For the new pointer, set the next pointer to a current head pointer.
		newNode->next = head;
	}
	// Set current head pointer to a new pointer
	head = newNode;
	// Increase the counter
	count++;
	// If old head pointer is NULL
	if (oldHead == nullptr)
	{
		// Then tail = head
		tail = head;
	}
}

void List::PushTail(std::string newData)
{
	// Create new node
	ListNode* newNode = new ListNode{ nullptr, nullptr, nullptr, newData };
	// Remember current tail
	ListNode* oldTail = tail;
	// If List not empty
	if (tail != nullptr)
	{
		// For the current tail pointer, set the next pointer to a new pointer.
		tail->next = newNode;
		// For the new pointer, set the prev pointer to a current tail pointer.
		newNode->prev = tail;
	}
	// Set current tail pointer to a new pointer
	tail = newNode;
	// Increase the counter
	count++;
	// If old tail == NULL
	if (oldTail == nullptr)
	{
		// Set head pointer to a tail pointer
		head = tail;
	}

}

void List::UpdateRandomPointers()
{
	// Set random pointers for all nodes from head to tail
	auto currentPointer = head;

	// Init random generator
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<int> distribution(0, count);

	while (currentPointer != nullptr)
	{
		// Get random index from 0 to count inclusive
		int dice_roll = distribution(generator);

		currentPointer->rand = GetRandomListNode(dice_roll);
		currentPointer = currentPointer->next;
	}
}

ListNode* List::GetRandomListNode(int dice_roll)
{
	// If list not empty
	if (count > 0)
	{
		// If random index == count
		if (dice_roll == count)
		{
			// Then random pointer is NULL
			return nullptr;
		}
		// Find pointer from head to random index 
		int index = 0;
		ListNode* rand = head;
		while (index < dice_roll)
		{
			rand = rand->next;
			index++;
		}
		// And return random pointer
		return rand;
	}
	// Return NULL if list empty
	return nullptr;
}

void List::PrintList()
{
	std::cout << "//-------------" << std::endl;
	auto currNode = head;
	while (currNode != nullptr)
	{
		std::cout << "Data: " << currNode->data <<	
			" Current: " << currNode <<
			" Next: " << currNode->next <<
			" Prev: " << currNode->prev <<
			" Rand: " << currNode->rand << std::endl;
		currNode = currNode->next;
	}
	std::cout << "//-------------" << std::endl << std::endl;
}