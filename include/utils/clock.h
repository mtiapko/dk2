#ifndef __DK_CLOCK_H__
#define __DK_CLOCK_H__

#include <chrono>
#include <thread>

namespace dk
{

class clock
{
private:
	std::chrono::high_resolution_clock::time_point m_last;
	std::chrono::high_resolution_clock::duration   m_update_interval;

public:
	clock(uint32_t UPS)
	{
		m_update_interval = std::chrono::high_resolution_clock::duration(std::chrono::seconds(1)) / UPS;
		m_last = std::chrono::high_resolution_clock::now();
	}

	bool is_elapsed()
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto diff = now - m_last;
		if (diff > m_update_interval) {
			m_last += m_update_interval;
			return true;
		}

		return false;
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

#endif  //  !__DK_CLOCK_H__
