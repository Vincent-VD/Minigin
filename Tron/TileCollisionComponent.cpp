#include "TileCollisionComponent.h"

TileCollisionComponent::TileCollisionComponent(cycle::GameObject* pOwner, float left, float bottom, float width, float height, bool isDynamic)
	: BaseCollisionComponent(pOwner, left, bottom, width, height, isDynamic)
{
	
}

