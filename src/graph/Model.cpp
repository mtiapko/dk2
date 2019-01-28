#include <GL/glew.h>
#include "graph/Debug.h"
#include "graph/Model.h"

namespace dk::graph
{

Model::Model() noexcept
	: m_vao(0)
	, m_vbo(0)
	, m_ibo(0)
{}

Model::~Model() noexcept /* override */
{
	this->destroy();
}

void Model::update() noexcept /* override */
{
	//  TODO: ????
}

void Model::render() noexcept /* override */
{
	GL_CALL(glBindVertexArray(m_vao));
	//  TODO: remove
	//GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GL_CALL(glDrawElements(GL_TRIANGLES, m_indx_count, GL_UNSIGNED_INT, 0));
}

Status Model::create(const ModelData& model_data) noexcept
{
	GL_CALL(glGenVertexArrays(1, &m_vao));
	GL_CALL(glBindVertexArray(m_vao));

	GL_CALL(glGenBuffers(1, &m_vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, model_data.vert.size() * sizeof(model_data.vert[0]),
		model_data.vert.data(), GL_STATIC_DRAW));

	/* vertex position */
	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0));

	/* vertex normal */
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float))));

	/* vertex UV */
	GL_CALL(glEnableVertexAttribArray(2));
	GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float))));

	GL_CALL(glGenBuffers(1, &m_ibo));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, model_data.indx.size() * sizeof(model_data.indx[0]),
		model_data.indx.data(), GL_STATIC_DRAW));

	GL_CALL(glBindVertexArray(0));
	//  XXX: unbind vbo and ibo?

	m_indx_count = model_data.indx.size();
	return Status::OK;
}

void Model::destroy() noexcept
{
	if (m_vao != 0) {
		GL_CALL(glDeleteVertexArrays(1, &m_vao));
		m_vao = 0;
	}

	if (m_vbo != 0) {
		GL_CALL(glDeleteBuffers(1, &m_vbo));
		m_vbo = 0;
	}

	if (m_ibo != 0) {
		GL_CALL(glDeleteBuffers(1, &m_ibo));
		m_ibo = 0;
	}
}

}
