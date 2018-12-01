#ifndef __DK_TEXTURE_H__
#define __DK_TEXTURE_H__

#include <SOIL2.h>
#include "log.h"
#include "status.h"
#include "graphic/gl.h"
#include "containers/string_view.h"

namespace dk
{

class texture
{
private:
	int32_t  m_height;
	int32_t  m_width;
	uint8_t* m_data;
	GLuint   m_tex;

public:
	void enable() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, m_tex)); }
	void disable() const { GL_CALL(glBindTexture(GL_TEXTURE_2D, 0)); }

	status create(std::string_view file_path)
	{
		auto beg = std::chrono::high_resolution_clock::now();
		m_data = SOIL_load_image(file_path.data(), &m_width, &m_height, nullptr, SOIL_LOAD_RGB);
		if (m_data == nullptr) {
			DK_LOG_ERROR("Failed to load texture from file '", file_path, "': ", SOIL_last_result());
			return status::ERROR;
		}

		GL_CALL(glGenTextures(1, &m_tex));
		this->enable();
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data));
		GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
		this->disable();

		SOIL_free_image_data(m_data);
		auto end = std::chrono::high_resolution_clock::now();
		auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
		DK_LOG_OK("Texture '", file_path, "' loaded (", dur.count() / 1000.0f, " ms): ", m_width, "x", m_height);
		return status::OK;
	}
};

}

#endif  //  !__DK_TEXTURE_H__
