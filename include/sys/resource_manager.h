#ifndef __DK_SYS_RESOURCE_MANAGER_H__
#define __DK_SYS_RESOURCE_MANAGER_H__

#include "resource.h"
#include "containers/vector.h"

namespace dk::sys
{

class resource_manager
{
public:
	vector<resource*> m_resources;

public:
	resource_manager() noexcept = default;
	~resource_manager() noexcept;

	bool is_exists(const resource* res) const noexcept;

	void add(resource* res) noexcept;

	void remove(resource* res) noexcept;
	void remove_all() noexcept;

	void destroy(resource* res) noexcept;
	void destroy_all() noexcept;
};

}

#endif  //  !__DK_SYS_RESOURCE_MANAGER_H__
