#pragma once
#include <vector>
#include "Observer.h"
#include "RootComponent.h"

namespace cycle
{
	class Observer;
	
	class Subject : public RootComponent
	{
	public:
		Subject(GameObject* owner);
		~Subject() override = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) noexcept = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) noexcept = delete;

		void Notify(const Event& message);
		void Update() override;

		void AddObserver(Observer* observer);
		void RemoveObserver(const Observer* observer);

	private:

		template <typename Type>
		struct Node
		{
			Node(Type* value, Node* pNext = nullptr);

			Node* pNext;
			Type* pData;
		};

		Node<Observer>* m_pFirstObserver{ new Node<Observer>{nullptr, nullptr} };
		int m_AmountObservers{};

		static const int MAX_PENDING{ 16 };
		int m_Head{};
		int m_Tail{};
		std::vector<Event> m_PendingEvents;

	};

	template <typename Type>
	Subject::Node<Type>::Node(Type* value, Node<Type>* pNext)
		: pNext(pNext)
		, pData(value)
	{
	}

}

