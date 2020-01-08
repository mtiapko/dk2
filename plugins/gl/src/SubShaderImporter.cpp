#include "dk/containers/UniquePtr.h"
#include "dk/os/File.h"
#include "dk/Mem.h"
#include "dk/Log.h"
#include "SubShaderImporter.h"

namespace gl
{

Status SubShaderImporter::import_sub_shader_data(graph::SubShaderData* data, StringView file_path) noexcept
{
	String src;
	if (auto err = os::File::read(src, file_path); !err)
		return err;

	data->file_path = file_path;
	data->source = std::move(src);
	return Status::OK;
}

Status SubShaderImporter::import_sub_shader(graph::SubShader* sub_shader, StringView file_path) noexcept
{
	graph::SubShaderData* data = dk_mem_new(graph::SubShaderData);
	data->set_resource_creator(this);

	if (auto err = this->import_sub_shader_data(data, file_path); !err)
		return err;

	if (file_path.ends_with(StringView("vert.glsl"))) data->type = graph::SubShaderType::VERTEX;
	else if (file_path.ends_with(StringView("frag.glsl"))) data->type = graph::SubShaderType::FRAGMENT;
	else {
		DK_LOG_ERROR("Failed to determine sub shader type. Rename to '*vert.glsl' or '*frag.glsl'");
		return Status::ERROR;
	}

	return sub_shader->create_from_resource_data(data);
}

Resource* SubShaderImporter::import(ResourceType type, StringView file_path) noexcept /* override */
{
	if (type == ResourceType::SUB_SHADER_DATA) {
		UniquePtr<graph::SubShaderData> data(dk_mem_new(graph::SubShaderData));
		if (auto err = this->import_sub_shader_data(data.get(), file_path); !err)
			return nullptr;

		return (Resource*)data.release();
	} else if (type == ResourceType::SUB_SHADER) {
		auto sub_shader_deleter = [](graph::SubShader* sub_shader) noexcept
			{ sub_shader->resource_creator()->delete_resource(sub_shader); };

		UniquePtr<graph::SubShader, decltype(sub_shader_deleter)>
			sub_shader(Core::get().active<graph::Renderer>()->new_resource<graph::SubShader>());
		if (auto err = this->import_sub_shader(sub_shader.get(), file_path); !err)
			return nullptr;

		return (Resource*)sub_shader.release();
	}

	DK_LOG_ERROR("Unsupported resource type");
	return nullptr;
}

Status SubShaderImporter::import(Resource* res, StringView file_path) noexcept /* override */
{
	switch (res->resource_type()) {
		case ResourceType::SUB_SHADER_DATA: return this->import_sub_shader_data((graph::SubShaderData*)res, file_path);
		case ResourceType::SUB_SHADER: return this->import_sub_shader((graph::SubShader*)res, file_path);
		default:
			DK_LOG_ERROR("Unsupported resource type");
			return Status::ERROR;
	}
}

void SubShaderImporter::delete_resource(Resource* res) noexcept /* override */
{
	res->destroy();
	dk_mem_delete(res);
}

}
