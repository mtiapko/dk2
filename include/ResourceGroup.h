#ifndef __DK_RESOURCE_GROUP_H__
#define __DK_RESOURCE_GROUP_H__

#include "Resource.h"
#include "containers/Vector.h"
#include "containers/HashTable.h"
#include "containers/StringView.h"

namespace dk
{

class ResourceGroup final: public Resource
{
private:
	HashTable<StringView, Resource*> m_res_table;
	Vector<Resource*>                m_resources;

public:
	~ResourceGroup() noexcept override;

	Resource* operator[](StringView tag) const noexcept;

	bool is_exists(const Resource* res) const noexcept;

	void add(Resource* res) noexcept;
	void add(Resource* res, StringView tag) noexcept;

	bool try_add(Resource* res) noexcept;
	bool try_add(Resource* res, StringView tag) noexcept;

	void remove(Resource* res) noexcept;
	void remove(StringView tag) noexcept;
	void remove_all() noexcept;

	void destroy(Resource* res) noexcept;
	void destroy(StringView tag) noexcept;
	void destroy_all() noexcept;
};

}

#endif  //  !__DK_RESOURCE_GROUP_H__
