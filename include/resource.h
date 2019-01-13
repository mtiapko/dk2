#ifndef __DK_RESOURCE_H__
#define __DK_RESOURCE_H__

namespace dk
{

enum class resource_type
{
	UNKNOWN = 0,
	SOUND_DATA,
	SOUND,
	SHADER_DATA,
	SHADER,
	TEXTURE_DATA,
	TEXTURE,
	MESH_DATA,  //  TODO: is it possible (is it needed) to load only mesh?
	MODEL_DATA,
	ENUM_SIZE
};

class resource
{
public:
	virtual ~resource() noexcept = default;

	virtual resource_type type() const noexcept { return resource_type::UNKNOWN; }
};

}

#endif  //  !__DK_RESOURCE_H__
