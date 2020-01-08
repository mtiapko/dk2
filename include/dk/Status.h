#ifndef __DK_STATUS_H__
#define __DK_STATUS_H__

namespace dk
{

class Status
{
private:
	int m_val;

public:
	static constexpr int OK      = 0;
	static constexpr int WARNING = 1;
	static constexpr int ERROR   = 2;
	static constexpr int FATAL   = 3;

	constexpr Status() noexcept : m_val(OK) {}
	constexpr Status(int val) noexcept : m_val(val) {}

	constexpr /* explicit */ operator int() const noexcept { return m_val; }
	constexpr explicit operator bool() const noexcept { return m_val == OK; }
};

}

#endif // !__DK_STATUS_H__
