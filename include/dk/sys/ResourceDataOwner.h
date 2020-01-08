#ifndef __DK_SYS_RESOURCE_DATAOWNER_H__
#define __DK_SYS_RESOURCE_DATAOWNER_H__

#include "dk/sys/ResourceOwner.h"
#include "dk/Assert.h"

namespace dk::sys
{

template<typename ResourceDataT>
class ResourceDataOwner : public ResourceOwner
{
private:
	ResourceDataT* m_resource_data = nullptr;

public:
	~ResourceDataOwner() noexcept { this->set_resource_data(nullptr); }

	ResourceDataT* resource_data() const noexcept { return m_resource_data; }

	void set_resource_data(ResourceDataT* res_data) noexcept
	{
		if (m_resource_data != nullptr) {
			auto old_res_data = m_resource_data;
			old_res_data->remove_resource_owner(this);
			if (old_res_data->resource_owners().empty()) {
				if (old_res_data->resource_creator() != nullptr)
					old_res_data->resource_creator()->delete_resource(old_res_data);
			}
		}

		if (res_data != nullptr)
			res_data->add_resource_owner(this);

		m_resource_data = res_data;
	}

	void remove_resource_slave(Resource* res_data) noexcept override
	{
		DK_ASSERT(res_data == m_resource_data, "Does not own this resource");
		m_resource_data = nullptr;
		// XXX: check if still own resource?
	}

	// TODO: add parameter 'bool add_resource_data = true'?
	Status create_from_resource_data(ResourceDataT* res_data) noexcept
	{
		this->set_resource_data(res_data);
		return this->create();
	}

	virtual Status create() noexcept = 0;
};

}

#endif // !__DK_SYS_RESOURCE_DATAOWNER_H__
