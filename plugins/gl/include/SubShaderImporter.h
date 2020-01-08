#ifndef __DK_GL_SUB_SHADER_IMPORTER_H__
#define __DK_GL_SUB_SHADER_IMPORTER_H__

#include "dk/graph/SubShader.h"
#include "Common.h"

namespace gl
{

class SubShaderImporter final : public sys::ResourceImporter
{
private:
	Status import_sub_shader_data(graph::SubShaderData* data, StringView file_path) noexcept;
	Status import_sub_shader(graph::SubShader* sub_shader, StringView file_path) noexcept;

public:
	Resource* import(ResourceType type, StringView file_path) noexcept override;
	Status import(Resource* res, StringView file_path) noexcept override;

	void delete_resource(Resource* res) noexcept override;
};

}

#endif // !__DK_GL_SUB_SHADER_IMPORTER_H__
