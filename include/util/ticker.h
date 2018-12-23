#ifndef __DK_UTIL_TICKER_H__
#define __DK_UTIL_TICKER_H__

#include <chrono>
#include <thread>

namespace dk::util
{

class ticker
{
private:
	std::chrono::high_resolution_clock::time_point m_last;
	std::chrono::high_resolution_clock::duration   m_update_interval;

public:
	ticker(uint32_t UPS)
	{
		m_update_interval = std::chrono::high_resolution_clock::duration(std::chrono::seconds(1)) / UPS;
		m_last = std::chrono::high_resolution_clock::now();
	}

	void wait()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto diff = now - m_last;
		if (diff < m_update_interval)
			std::this_thread::sleep_for(m_update_interval - diff);

		m_last += m_update_interval;
	}
};

}

#endif  //  !__DK_UTIL_TICKER_H__
