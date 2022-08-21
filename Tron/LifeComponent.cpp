#include "LifeComponent.h"

#include <iostream>

#include "GameObject.h"
#include "TextComponent.h"

LifeComponent::LifeComponent(cycle::GameObject* pOwner)
	: RootComponent(pOwner)
{
}

void LifeComponent::Hit()
{
	--m_Lives;

	if(m_Lives == 0)
	{
		std::cout << "DEAD\n";
	}
}


