#pragma once
#include "lottery.h"
#include "list.h"
#include <deque>

template <typename T>
using Container = list<T>;

class History
{
public:

	void add(std::shared_ptr<Lottery<Container>> lot) {
		m_lotteries.push_back(lot);
	}
	std::vector< std::shared_ptr<Lottery<Container>>>::iterator begin() {
		return m_lotteries.begin();
	}
	std::vector< std::shared_ptr<Lottery<Container>>>::iterator end() {
		return m_lotteries.end();
	}

private:
	std::vector< std::shared_ptr<Lottery<Container>>> m_lotteries;
};

