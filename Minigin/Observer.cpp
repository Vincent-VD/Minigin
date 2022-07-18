#include "Observer.h"

bool cycle::Observer::operator==(const Observer& other) const
{
	if(other.m_Type == m_Type)
	{
		return true;
	}
	return false;
}

