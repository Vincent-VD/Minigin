#pragma once
#include <iostream>

#include "RootComponent.h"

namespace cycle
{
	class GameObject;

	enum class GameEvent
	{
		ENEMY_KILLED = 0
	};

	struct Event
	{
		GameEvent event{ GameEvent::ENEMY_KILLED };
		const GameObject* caller{ nullptr };
	};

	class Observer
	{
	public:
		Observer() = default;
		virtual ~Observer() = 0;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) noexcept = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) noexcept = delete;

		bool operator==(const Observer& other) const;

		virtual void OnNotify(const Event& message) = 0; //enum converted to int

	protected:
		enum class ObserverType
		{
			GameLoopObserver = 0
		};

		ObserverType m_Type{};
	};

	inline Observer::~Observer()
	{
		std::cout << "Destroying observer\n";
	}


}
