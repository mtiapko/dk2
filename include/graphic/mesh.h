#ifndef __DK_MESH_H__
#define __DK_MESH_H__

#include "status.h"
#include "math/types.h"
#include "containers/vector.h"
#include "containers/string_view.h"

namespace dk
{

class mesh
{
//private:
public:
	vector<vec3f>    m_vertices;
	vector<vec3f>    m_normals;
	vector<vec3f>    m_uvs;
	vector<uint32_t> m_indices;

public:
	status load(string_view file_path);
};

}

#endif  //  !__DK_MESH_H__
