#include <algorithm>
#include "resource_group.h"
#include "mem.h"

namespace dk
{

resource_group::~resource_group() noexcept /* override */
{
	this->destroy_all();
}

resource* resource_group::operator[](string_view tag) const noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend())
		return res->second;

	return nullptr;
}

bool resource_group::is_exists(const resource* res) const noexcept
{
	for (auto r: m_resources) {
		if (r == res)
			return true;
	}

	return false;
}

void resource_group::add(resource* res) noexcept
{
	m_resources.emplace_back(res);
}

void resource_group::add(resource* res, string_view tag) noexcept
{
	m_res_table[tag] = res;
	this->add(res);
}

bool resource_group::try_add(resource* res) noexcept
{
	if (this->is_exists(res))
		return false;

	this->add(res);
	return true;
}

bool resource_group::try_add(resource* res, string_view tag) noexcept
{
	if (m_res_table.find(tag) != m_res_table.cend())
		return false;

	if (this->is_exists(res))
		return false;

	this->add(res, tag);
	return false;
}

void resource_group::remove(resource* res) noexcept
{
	auto it = std::find(m_resources.cbegin(), m_resources.cend(), res);
	if (it != m_resources.cend())
		m_resources.erase(it);
}

void resource_group::remove(string_view tag) noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend()) {
		this->remove(res->second);
		m_res_table.erase(res);
	}
}

void resource_group::remove_all() noexcept
{
	m_resources.clear();
	m_res_table.clear();
}

void resource_group::destroy(resource* res) noexcept
{
	auto it = std::find(m_resources.begin(), m_resources.end(), res);
	if (it != m_resources.cend()) {
		m_resources.erase(it);
		mem_destroy(*it);
	}
}

void resource_group::destroy(string_view tag) noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend())
		this->destroy(res->second);
}

void resource_group::destroy_all() noexcept
{
	for (auto r: m_resources)
		mem_destroy(r);

	this->remove_all();
}


}
