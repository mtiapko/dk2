#include "dk/sys/ResourceOwner.h"
#include "dk/Resource.h"
#include "dk/Assert.h"

namespace dk
{

sys::ResourceCreator* Resource::resource_creator() const noexcept
{
	return m_resource_creator;
}

void Resource::set_resource_creator(sys::ResourceCreator* creator) noexcept
{
	m_resource_creator = creator;
}

const Vector<sys::ResourceOwner*>& Resource::resource_owners() const noexcept
{
	return m_resource_owners;
}

void Resource::add_resource_owner(sys::ResourceOwner* owner) noexcept
{
	m_resource_owners.emplace_back(owner);
}

void Resource::remove_resource_owner(sys::ResourceOwner* owner) noexcept
{
	owner->remove_resource_slave(this);
	std::erase(m_resource_owners, owner);
}

void Resource::remove_all_resource_owners() noexcept
{
	for (auto owner: this->resource_owners())
		owner->remove_resource_slave(this);

	// XXX: owners do not notify slaves about its removing
	m_resource_owners.clear();
	DK_ASSERT(m_resource_owners.empty(), "Not all owners removed");
}

}
