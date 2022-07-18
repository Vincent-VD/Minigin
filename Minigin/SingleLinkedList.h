#pragma once
#include <string>

template <typename Type>
struct Node
{
	Node(Type* value, Node* pNext = nullptr);

	Node* pNext;
	Type* pData;
};

template <typename Type>
class SingleLinkedList final
{
public:
	SingleLinkedList();
	~SingleLinkedList() = default;
	SingleLinkedList(const SingleLinkedList& other) = delete;
	SingleLinkedList& operator=(const SingleLinkedList& other) = delete;
	SingleLinkedList(SingleLinkedList&& other)noexcept = delete;
	SingleLinkedList& operator=(SingleLinkedList&& other)noexcept = delete;

	void PushBack(Type* value);
	void Remove(Type* value);
	size_t Size() const;
	Type GetFront() const;
	Type GetBack() const;

	void Clear();

private:
	Node<Type>* m_pFirstNode;
	Node<Type>* m_pLastNode;
	size_t m_Size;
};

template <typename Type>
Node<Type>::Node(Type* value, Node<Type>* pNext)
	: pNext(pNext)
	, pData(value)
{
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList()
	: m_pFirstNode(nullptr)
	, m_pLastNode(nullptr)
	, m_Size(0)
{
	
}

template <typename Type>
void SingleLinkedList<Type>::PushBack(Type* value)
{
	Node<Type>* newLastNode{ new Node<Type>{value, nullptr} };
	if (m_pLastNode != nullptr)
	{
		m_pLastNode->pNext = newLastNode;
	}
	m_pLastNode = newLastNode;
	if (m_pFirstNode == nullptr)
	{
		m_pFirstNode = newLastNode;
	}
	++m_Size;
}

template <typename Type>
void SingleLinkedList<Type>::Remove(Type* value)
{
	Node<Type>* currNode{ m_pFirstNode };
	Node<Type>* prevNode{ nullptr };
	for(int iter = 0; iter < m_Size; ++iter)
	{
		if(currNode->pData == value)
		{
			if(prevNode != nullptr)
			{
				prevNode->pNext = currNode->pNext;
				delete currNode;
				if (m_Size == 1) { //First and last point to same address
					m_pFirstNode = m_pLastNode;
				}
				--m_Size;
				break;
			}
		}
		prevNode = currNode;
		currNode = currNode->pNext;
	}
}

template <typename Type>
size_t SingleLinkedList<Type>::Size() const
{
	return m_Size;
}