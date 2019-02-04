#include <GL/glew.h>
#include "Assert.h"
#include "graph/Debug.h"
#include "graph/CubeMap.h"
#include "graph/Texture.h"
#include "sys/ResourceManager.h"

namespace dk::graph
{

/* static */ GLuint  CubeMap::s_vao;
/* static */ GLuint  CubeMap::s_vbo;
/* static */ GLfloat CubeMap::s_cube_map_vertices[] = {
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,

	/**/ -1.0f, -1.0f,  1.0f,
	/**/ -1.0f, -1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f, -1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/ -1.0f, -1.0f,  1.0f,

	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,

	/**/ -1.0f, -1.0f,  1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f, -1.0f,  1.0f,
	/**/ -1.0f, -1.0f,  1.0f,

	/**/ -1.0f,  1.0f, -1.0f,
	/**/  1.0f,  1.0f, -1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/  1.0f,  1.0f,  1.0f,
	/**/ -1.0f,  1.0f,  1.0f,
	/**/ -1.0f,  1.0f, -1.0f,

	/**/ -1.0f, -1.0f, -1.0f,
	/**/ -1.0f, -1.0f,  1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/  1.0f, -1.0f, -1.0f,
	/**/ -1.0f, -1.0f,  1.0f,
	/**/  1.0f, -1.0f,  1.0f
};

CubeMap::CubeMap() noexcept
	: m_id(0)
{}

CubeMap::~CubeMap() noexcept
{
	this->destroy();
}

/* static */ Status CubeMap::init() noexcept
{
	GL_CALL(glGenVertexArrays(1, &s_vao));
	GL_CALL(glBindVertexArray(s_vao));

	GL_CALL(glGenBuffers(1, &s_vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, s_vbo));

	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_cube_map_vertices), s_cube_map_vertices, GL_STATIC_DRAW));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	GL_CALL(glEnableVertexAttribArray(0));

	GL_CALL(glBindVertexArray(0));
	return Status::OK;
}

void CubeMap::render() const noexcept
{
	DK_ASSERT(s_vao != 0, "CubeMap::init() required before CubeMap::render()");

	GL_CALL(glDepthMask(GL_FALSE));
	GL_CALL(glBindVertexArray(s_vao));
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));
	GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 36));
	GL_CALL(glDepthMask(GL_TRUE));
}

Status CubeMap::create(const TextureData& right, const TextureData& left, const TextureData& top,
	const TextureData& bottom, const TextureData& front, const TextureData& back) noexcept
{
	GL_CALL(glGenTextures(1, &m_id));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));

	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, Texture::to_gl_fmt(right), right.width(), right.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, right.data()));
	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, Texture::to_gl_fmt(left), left.width(), left.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, left.data()));
	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, Texture::to_gl_fmt(top), top.width(), top.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, top.data()));
	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, Texture::to_gl_fmt(bottom), bottom.width(), bottom.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, bottom.data()));
	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, Texture::to_gl_fmt(front), front.width(), front.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, front.data()));
	GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, Texture::to_gl_fmt(back), back.width(), back.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, back.data()));

	GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	return Status::OK;
}

Status CubeMap::create(StringView right, StringView left, StringView top,
		StringView bottom, StringView front, StringView back) noexcept
{
	TextureData right_tex;
	if (auto ret = sys::ResourceManager::load(right_tex, right); !ret)
		return ret;

	TextureData left_tex;
	if (auto ret = sys::ResourceManager::load(left_tex, left); !ret)
		return ret;

	TextureData top_tex;
	if (auto ret = sys::ResourceManager::load(top_tex, top); !ret)
		return ret;

	TextureData bottom_tex;
	if (auto ret = sys::ResourceManager::load(bottom_tex, bottom); !ret)
		return ret;

	TextureData front_tex;
	if (auto ret = sys::ResourceManager::load(front_tex, front); !ret)
		return ret;

	TextureData back_tex;
	if (auto ret = sys::ResourceManager::load(back_tex, back); !ret)
		return ret;

	return create(right_tex, left_tex, top_tex, bottom_tex, front_tex, back_tex);
}

void CubeMap::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteTextures(1, &m_id));
		m_id = 0;
	}
}

}
