#include <GL/glew.h>
#include "ResourceManager.h"
#include "graph/CubeMapTexture.h"
#include "graph/Texture.h"
#include "graph/Debug.h"

namespace dk::graph
{

CubeMapTexture::CubeMapTexture(ResourceManager* res_mgr) noexcept
	: Resource(res_mgr)
	, m_id(0)
{}

CubeMapTexture::~CubeMapTexture() noexcept
{
	this->destroy();
}

void CubeMapTexture::enable() const noexcept
{
	GL_CALL(glActiveTexture(GL_TEXTURE0));
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_id));
}

void CubeMapTexture::disable() const noexcept
{
	GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

Status CubeMapTexture::create(const TextureData& right, const TextureData& left, const TextureData& top,
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

Status CubeMapTexture::create(StringView right, StringView left, StringView top,
		StringView bottom, StringView front, StringView back) noexcept
{
	TextureData right_tex(nullptr);
	if (auto ret = m_res_mgr->load(right_tex, right); !ret)
		return ret;

	TextureData left_tex(nullptr);
	if (auto ret = m_res_mgr->load(left_tex, left); !ret)
		return ret;

	TextureData top_tex(nullptr);
	if (auto ret = m_res_mgr->load(top_tex, top); !ret)
		return ret;

	TextureData bottom_tex(nullptr);
	if (auto ret = m_res_mgr->load(bottom_tex, bottom); !ret)
		return ret;

	TextureData front_tex(nullptr);
	if (auto ret = m_res_mgr->load(front_tex, front); !ret)
		return ret;

	TextureData back_tex(nullptr);
	if (auto ret = m_res_mgr->load(back_tex, back); !ret)
		return ret;

	return create(right_tex, left_tex, top_tex, bottom_tex, front_tex, back_tex);
}

void CubeMapTexture::destroy() noexcept
{
	if (m_id != 0) {
		GL_CALL(glDeleteTextures(1, &m_id));
		m_id = 0;
	}
}

}
