#include "pch.h"
#include "Counter.h"

int Counter::GetCounterIndex(const std::string& name)
{
	return m_CounterMap[name];
}

bool Counter::CheckCounter(const std::string& name,const  int times, const bool autoReset)
{
	// If the map already contains the counter
	if(m_CounterMap.count(name))
	{
		int& counterValue = m_CounterMap[name];
		counterValue += 1;

		if(counterValue >= times)
		{
			if(autoReset) ResetCounter(name);
			return false;
		}
	}
	else
	{
		m_CounterMap.insert({name,0});
	}

	return true;
}

void Counter::ResetCounter(std::string name)
{
	if (m_CounterMap.count(name))
	{
		m_CounterMap.erase(name);
	}
}
