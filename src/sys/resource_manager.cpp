#include "mem.h"
#include "assert.h"
#include "sys/resource_manager.h"

namespace dk::sys
{

resource_manager::~resource_manager() noexcept
{
	this->destroy_all();
}

bool resource_manager::is_exists(const resource* res) const noexcept
{
	for (auto r: m_resources) {
		if (r == res)
			return true;
	}

	return false;
}

void resource_manager::add(resource* res) noexcept
{
	DK_ASSERT(!this->is_exists(res));
	m_resources.emplace_back(res);
}

void resource_manager::remove(resource* res) noexcept
{
	for (auto it = m_resources.cbegin(); it != m_resources.cend(); ++it) {
		if (*it == res) {
			m_resources.erase(it);
			break;
		}
	}
}

void resource_manager::remove_all() noexcept
{
	m_resources.clear();
}

void resource_manager::destroy(resource* res) noexcept
{
	for (auto it = m_resources.cbegin(); it != m_resources.cend(); ++it) {
		if (*it == res) {
			m_resources.erase(it);
			mem_destroy(res);
			break;
		}
	}
}

void resource_manager::destroy_all() noexcept
{
}

}
