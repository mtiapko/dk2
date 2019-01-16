#ifndef __DK_RESOURCE_H__
#define __DK_RESOURCE_H__

namespace dk
{

enum class ResourceType
{
	UNKNOWN = 0,
	SOUND_DATA,
	SOUND,
	SHADER_DATA,
	SHADER,
	TEXTURE_DATA,
	TEXTURE,
	MODEL_DATA,
	MODEL,
	ENUM_SIZE
};

class Resource
{
public:
	virtual ~Resource() noexcept = default;

	static ResourceType type() noexcept { return ResourceType::UNKNOWN; }
};

}

#endif  //  !__DK_RESOURCE_H__
