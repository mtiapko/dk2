#ifndef __DK_SHADER_PROGRAM_H__
#define __DK_SHADER_PROGRAM_H__

#include "graphic/shader.h"

namespace dk
{

class shader_program
{
private:
	GLuint m_shader_program;

public:
	shader_program() : m_shader_program(0) {}

	void enable() const;
	void disable() const;

	ret_code add_shader(const shader& shader) const;

	ret_code create();
	ret_code link();
};

}

#endif  //  !__DK_SADHER_PROGRAM_H__
