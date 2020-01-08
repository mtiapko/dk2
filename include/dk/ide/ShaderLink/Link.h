#ifndef __DK_IDE_SHADER_LINK_LINK_H__
#define __DK_IDE_SHADER_LINK_LINK_H__

#include <cstddef>

namespace dk::ide::ShaderLink
{

class Link
{
private:
	size_t     m_external_id;
	class Pin* m_beg_pin;
	class Pin* m_end_pin;

public:
	Link(size_t external_id, class Pin* beg_pin, class Pin* end_pin) noexcept
		: m_external_id(external_id)
		, m_beg_pin(beg_pin)
		, m_end_pin(end_pin)
	{}

	size_t external_id() const noexcept { return m_external_id; }
	class Pin* beg_pin() const noexcept { return m_beg_pin; }
	class Pin* end_pin() const noexcept { return m_end_pin; }
};

}

#endif // !__DK_IDE_SHADER_LINK_LINK_H__
