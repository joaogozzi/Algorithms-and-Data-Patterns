#pragma once
#include <iostream>

struct Node
{
    int data = 0;
    Node* next = nullptr;
};

class LinkedList
{
public:
    int RandomNumber(int min, int max)
    {
        return min + (rand() % (max - min + 1));
    }

    Node* CreateNode(Node* prevNode, int data)
    {
        // TODO - finish with the video
        Node* newNode;

        newNode->data = data;

        return newNode;
    }

    void DeleteList(Node* head)
    {
        if (head != nullptr)
        {
            DeleteList(head->next);
            delete head;
            head = nullptr;
        }
    }

    bool IsLinkedListCyclical(Node* head)
    {
        Node* slowNode = nullptr;
        Node* fastNode = nullptr;

        while (slowNode != nullptr && fastNode != nullptr && fastNode->next != nullptr)
        {
            slowNode = slowNode->next;
            fastNode = fastNode->next->next;

            if (slowNode == fastNode)
            {
                return true;
            }

            return false;
        }
    }

    void Exercise1LinkedLists()
    {
        int maxNumbers = 20;
        int min = 1;
        int max = 100;
        Node* head = nullptr;
        Node* prevNode = nullptr;

        for (int i = 0; i < maxNumbers; ++i)
        {
            prevNode = CreateNode(prevNode, RandomNumber(min, max));

            if (head == nullptr)
            {
                head = prevNode;
            }
        }

        prevNode->next = head;

        if (IsLinkedListCyclical(head))
        {
            std::cout << "List is Cyclical\n";
        }
        else
        {
            Node* tmp = head;
            while (tmp != nullptr)
            {
                std::cout << tmp->data << " ";
                tmp = tmp->next;
            }

            DeleteList(head);
        }

        std::cout << "\n\n";
    }
};