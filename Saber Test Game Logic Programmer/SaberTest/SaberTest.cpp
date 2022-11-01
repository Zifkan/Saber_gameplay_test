#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>

#include <iostream>
#include <vector>
#include "List.h"

void NodelistSerialize();

void NodelistDeserialize();

int main()
{
		
	NodelistSerialize();

	NodelistDeserialize();

	return 0;
}

void NodelistSerialize()
{
	List* list = new List();

	list->PushHead("Third");
	list->PushHead("Second");
	list->PushHead("First Head");
	list->PushTail("Tail");
	list->UpdateRandomPointers();

	FILE* file = fopen("serialized_list.bin", "wb");
	if (file != nullptr)
	{
		list->Serialize(file);
		fclose(file);
	}	

	delete list;
}

void NodelistDeserialize()
{

	FILE* file = fopen("serialized_list.bin", "rb");
	if (file != nullptr)
	{
		// Create new list
		List* deserializedList = new List();
		// Deserilized it
		deserializedList->Deserialize(file);
		fclose(file);

		// and delete it
		delete deserializedList;
	}
}
