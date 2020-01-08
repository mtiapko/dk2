#include "dk/graph/Material.h"

namespace dk::graph
{

void Material::destroy() noexcept /* override */
{
	this->set_shader(nullptr);
	m_textures.clear();
	m_shader_args.clear();
}

}
