#include <algorithm>
#include "ResourceGroup.h"
#include "Mem.h"

namespace dk
{

ResourceGroup::~ResourceGroup() noexcept /* override */
{
	this->destroy_all();
}

Resource* ResourceGroup::operator[](StringView tag) const noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend())
		return res->second;

	return nullptr;
}

bool ResourceGroup::is_exists(const Resource* res) const noexcept
{
	for (auto r: m_resources) {
		if (r == res)
			return true;
	}

	return false;
}

void ResourceGroup::add(Resource* res) noexcept
{
	m_resources.emplace_back(res);
}

void ResourceGroup::add(Resource* res, StringView tag) noexcept
{
	m_res_table[tag] = res;
	this->add(res);
}

bool ResourceGroup::try_add(Resource* res) noexcept
{
	if (this->is_exists(res))
		return false;

	this->add(res);
	return true;
}

bool ResourceGroup::try_add(Resource* res, StringView tag) noexcept
{
	if (m_res_table.find(tag) != m_res_table.cend())
		return false;

	if (this->is_exists(res))
		return false;

	this->add(res, tag);
	return false;
}

void ResourceGroup::remove(Resource* res) noexcept
{
	auto it = std::find(m_resources.cbegin(), m_resources.cend(), res);
	if (it != m_resources.cend())
		m_resources.erase(it);
}

void ResourceGroup::remove(StringView tag) noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend()) {
		this->remove(res->second);
		m_res_table.erase(res);
	}
}

void ResourceGroup::remove_all() noexcept
{
	m_resources.clear();
	m_res_table.clear();
}

void ResourceGroup::destroy(Resource* res) noexcept
{
	auto it = std::find(m_resources.begin(), m_resources.end(), res);
	if (it != m_resources.cend()) {
		m_resources.erase(it);
		mem_destroy(*it);
	}
}

void ResourceGroup::destroy(StringView tag) noexcept
{
	auto res = m_res_table.find(tag);
	if (res != m_res_table.cend())
		this->destroy(res->second);
}

void ResourceGroup::destroy_all() noexcept
{
	for (auto r: m_resources)
		mem_destroy(r);

	this->remove_all();
}


}
