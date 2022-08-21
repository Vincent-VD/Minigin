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
		Event() = default;

		Event(GameEvent gameEvent, const GameObject* caller, std::string& tag)
			: m_Event(gameEvent)
			, m_Caller(caller)
			, m_Tag(tag)
		{
		}

		~Event() = default;
		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		void operator=(const Event& other)
		{
			m_Event = other.m_Event;
			m_Caller = other.m_Caller;
			m_Tag = other.m_Tag;
		}
		void operator=(Event&& other) noexcept
		{
			m_Event = other.m_Event;
			m_Caller = other.m_Caller;
			m_Tag = other.m_Tag;
		}

		GameEvent m_Event{ GameEvent::ENEMY_KILLED };
		const GameObject* m_Caller{ nullptr };
		std::string m_Tag{};
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
			GameLoopObserver = 0,
			HUD = 1
		};

		ObserverType m_Type{};
	};

	inline Observer::~Observer()
	{
		
	}


}
