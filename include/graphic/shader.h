#ifndef __DK_SHADER_H__
#define __DK_SHADER_H__

#include <GL/gl.h>
#include "ret_code.h"
#include "containers/string_view.h"

namespace dk
{

enum class shader_type
{
	VERTEX_SHADER = 0,
	FRAGMENT_SHADER
};

class shader
{
private:
	GLuint m_shader;

	static GLenum convert_type(shader_type type);

public:
	GLuint get_native() const { return m_shader; }

	ret_code create(shader_type type, string_view src);
};

}

#endif  //  !__DK_SAHDER_H__
