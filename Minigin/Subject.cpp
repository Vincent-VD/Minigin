#include "Subject.h"

#include <iostream>

cycle::Subject::Subject(GameObject* owner)
	: RootComponent(owner)
	, m_pFirstObserver(new Node<Observer>(nullptr, nullptr))
	, m_PendingEvents(std::vector<cycle::Event>(MAX_PENDING))
{
	
}

void cycle::Subject::Notify(const Event& message)
{
	m_PendingEvents[m_Tail] = message;
	m_Tail = (m_Tail + 1) % MAX_PENDING;
}

void cycle::Subject::Update()
{
	Node<Observer>* currNode(m_pFirstObserver);
	while (currNode != nullptr)
	{
		for(int iter = m_Head; iter < m_Tail; ++iter)
		{
			Event message{ m_PendingEvents[iter]};
			currNode->pData->OnNotify(message);
			m_Head = (m_Head + 1) % MAX_PENDING;
		}
		currNode = currNode->pNext;
	}
}


void cycle::Subject::AddObserver(Observer* observer)
{
	Node<Observer>* newNode{ new Node<Observer>{observer, m_pFirstObserver} };
	m_pFirstObserver = newNode;
	++m_AmountObservers;
}

void cycle::Subject::RemoveObserver(const Observer* observer)
{
	Node<Observer>* currNode{ m_pFirstObserver };
	Node<Observer>* prevNode{ nullptr };
	while(currNode != nullptr)
	{
		if(currNode->pData == observer)
		{
			if(prevNode != nullptr)
			{
				prevNode->pNext = currNode->pNext;
			}
			else
			{
				m_pFirstObserver = currNode->pNext;
			}
			delete currNode;
			--m_AmountObservers;
			break;
		}
		prevNode = currNode;
		currNode = currNode->pNext;
	}
}

//void cycle::Subject::Clear()
//{
//	std::cout << "\nWARNING: THIS FUNCTION DOES NOT DESTROY OBSERVERS!\n";
//}
