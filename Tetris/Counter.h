#pragma once
#include <map>

class Counter
{

private:

	std::map<std::string, int> m_CounterMap{};

public:

	int GetCounterIndex(const std::string& name);

	bool CheckCounter(const std::string& name, const  int times, const bool autoReset = false);

	void ResetCounter(std::string name);
};

