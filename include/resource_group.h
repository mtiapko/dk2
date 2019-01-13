#ifndef __DK_RESOURCE_GROUP_H__
#define __DK_RESOURCE_GROUP_H__

#include "resource.h"
#include "containers/vector.h"
#include "containers/hash_table.h"
#include "containers/string_view.h"

namespace dk
{

class resource_group final: public resource
{
private:
	hash_table<string_view, resource*> m_res_table;
	vector<resource*>                  m_resources;

public:
	~resource_group() noexcept override;

	resource* operator[](string_view tag) const noexcept;

	bool is_exists(const resource* res) const noexcept;

	void add(resource* res) noexcept;
	void add(resource* res, string_view tag) noexcept;

	bool try_add(resource* res) noexcept;
	bool try_add(resource* res, string_view tag) noexcept;

	void remove(resource* res) noexcept;
	void remove(string_view tag) noexcept;
	void remove_all() noexcept;

	void destroy(resource* res) noexcept;
	void destroy(string_view tag) noexcept;
	void destroy_all() noexcept;
};

}

#endif  //  !__DK_RESOURCE_GROUP_H__
