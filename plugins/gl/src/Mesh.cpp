#include <GL/glew.h>
#include "Debug.h"
#include "Mesh.h"

namespace gl
{

void Mesh::render() noexcept
{
	GL_CALL(glBindVertexArray(m_vao));
	GL_CALL(glDrawElements(GL_TRIANGLES, m_indx_count, GL_UNSIGNED_INT, nullptr));
	//  TODO: remove
	/*GL_CALL(glLineWidth(3.0f));
	glDisable(GL_POLYGON_OFFSET_FILL);
	GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	GL_CALL(glDrawElements(GL_TRIANGLES, m_indx_count, GL_UNSIGNED_INT, nullptr));

	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0f, 1.0f);
	GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
	GL_CALL(glDrawElements(GL_TRIANGLES, m_indx_count, GL_UNSIGNED_INT, nullptr));*/
}

Status Mesh::create() noexcept /* override */
{
	auto mesh_data = (graph::MeshData*)this->resource_data();

	GL_CALL(glGenVertexArrays(1, &m_vao));
	GL_CALL(glBindVertexArray(m_vao));

	GL_CALL(glGenBuffers(1, &m_vbo));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, mesh_data->vertices.size() * sizeof(mesh_data->vertices[0]),
		mesh_data->vertices.data(), GL_STATIC_DRAW));

	// TODO: use glGetAttribLocation(), sizeof() and offsetof()
	/* position */
	GL_CALL(glEnableVertexAttribArray(0)); // TODO: load id float standard mesh shader
	GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (GLvoid*)0));

	/* normal */
	GL_CALL(glEnableVertexAttribArray(1));
	GL_CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (GLvoid*)(3 * sizeof(float))));

	/* UV */
	GL_CALL(glEnableVertexAttribArray(2));
	GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (GLvoid*)(6 * sizeof(float))));

	/* tangent */
	GL_CALL(glEnableVertexAttribArray(3));
	GL_CALL(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (GLvoid*)(8 * sizeof(float))));

	/* bitangent */
	GL_CALL(glEnableVertexAttribArray(4));
	GL_CALL(glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (GLvoid*)(11 * sizeof(float))));

	GL_CALL(glGenBuffers(1, &m_ibo));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_data->indices.size() * sizeof(mesh_data->indices[0]),
		mesh_data->indices.data(), GL_STATIC_DRAW));

	GL_CALL(glBindVertexArray(0));
	// XXX: unbind vbo and ibo?

	m_indx_count = mesh_data->indices.size();
	return Status::OK;
}

void Mesh::destroy() noexcept /* override */
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
