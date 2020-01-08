#ifndef __DK_RESOURCE_H__
#define __DK_RESOURCE_H__

#include "dk/containers/StringView.h"
#include "dk/containers/Vector.h"
#include "dk/Log.h"

#define DK_RESOURCE_TYPE_INFO(type) \
	ResourceType resource_type() const noexcept override { return ResourceType::type; } \
	static constexpr ResourceType get_resource_type() noexcept { return ResourceType::type; }

namespace dk
{

enum class ResourceType
{
	UNKNOWN = 0,

	WINDOW_DATA,
	WINDOW,
	RENDERER_CONTEXT,

	SUB_SHADER_DATA,
	SUB_SHADER,

	SHADER_DATA,
	SHADER,

	TEXTURE_DATA,
	TEXTURE,

	MESH_DATA,
	MESH,

	MATERIAL,
	SUB_MODEL,
	MODEL,

	RESOURCE_TYPE_SIZE
};

static constexpr StringView ResourceTypeNames[(int)ResourceType::RESOURCE_TYPE_SIZE] = {
	[(int)ResourceType::UNKNOWN]          = "UNKNOWN",
	[(int)ResourceType::WINDOW_DATA]      = "WINDOW_DATA",
	[(int)ResourceType::WINDOW]           = "WINDOW",
	[(int)ResourceType::RENDERER_CONTEXT] = "RENDERER_CONTEXT",
	[(int)ResourceType::SUB_SHADER_DATA]  = "SUB_SHADER_DATA",
	[(int)ResourceType::SUB_SHADER]       = "SUB_SHADER",
	[(int)ResourceType::SHADER_DATA]      = "SHADER_DATA",
	[(int)ResourceType::SHADER]           = "SHADER",
	[(int)ResourceType::TEXTURE_DATA]     = "TEXTURE_DATA",
	[(int)ResourceType::TEXTURE]          = "TEXTURE",
	[(int)ResourceType::MESH_DATA]        = "MESH_DATA",
	[(int)ResourceType::MESH]             = "MESH",
	[(int)ResourceType::MATERIAL]         = "MATERIAL",
	[(int)ResourceType::SUB_MODEL]        = "SUB_MODEL",
	[(int)ResourceType::MODEL]            = "MODEL"
};

namespace sys
{
	class ResourceCreator;
	class ResourceOwner;
}

// TODO:
// template<ResourceType Type>
// class ResourceWithType (XXX: tmp name) : public Resource { return Type... };
// class Shader : public ResourceWithType<SHADER> { ... };
class Resource
{
private:
	sys::ResourceCreator*       m_resource_creator = nullptr;
	Vector<sys::ResourceOwner*> m_resource_owners;

public:
	// TODO: Resource(sys::ResourceCreator* creator) noexcept : m_resource_creator(creator) {}
	virtual ~Resource() noexcept { this->remove_all_resource_owners(); }

	virtual ResourceType resource_type() const noexcept = 0;

	// TODO: virtual Resource* duplicate() noexcept = 0;

	sys::ResourceCreator* resource_creator() const noexcept;
	void set_resource_creator(sys::ResourceCreator* creator) noexcept;

	// TODO: add mutex
	const Vector<sys::ResourceOwner*>& resource_owners() const noexcept;
	void add_resource_owner(sys::ResourceOwner* owner) noexcept;
	void remove_resource_owner(sys::ResourceOwner* owner) noexcept;
	void remove_all_resource_owners() noexcept;

	// TODO: virtual Status create() noexcept = 0; ???
	virtual void destroy() noexcept {}; // TODO: '= 0;' to detect not implemented
};

}

#endif // !__DK_RESOURCE_H__
