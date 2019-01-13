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
	MODEL_DATA,
	MODEL,
	ENUM_SIZE
};

class resource
{
public:
	virtual ~resource() noexcept = default;

	static resource_type type() noexcept { return resource_type::UNKNOWN; }
};

}

#endif  //  !__DK_RESOURCE_H__
