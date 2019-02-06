//#include <stdlib.h>
#include "sys/loaders/OBJ_Loader.h"
#include "fs/File.h"
#include "Log.h"
#include "Mem.h"

namespace dk::sys
{

bool is_space(char c)
{
	return c == ' ' || c == '\t';
}

void skip_spaces(const char*& str)
{
	while (is_space(*str))
		++str;
}

void skip_line(const char*& str)
{
	while (*str++ != '\n');
}

Status read(const char*& str, float& val)
{
	char* str_end;
	val = strtof(str, &str_end);
	if (str == str_end) {
		DK_LOG_ERROR("Failed to read float");
		return Status::ERROR;
	}

	str = str_end;
	return Status::OK;
}

Status read(const char*& str, uint32_t& val)
{
	char* str_end;
	val = strtoul(str, &str_end, 10);
	if (str == str_end) {
		DK_LOG_ERROR("Failed to read uint32");
		return Status::ERROR;
	}

	str = str_end;
	return Status::OK;
}

Status expect(const char*& str, char c)
{
	if (*str++ != c) {
		DK_LOG_ERROR("Expected '", c, '\'');
		return Status::ERROR;
	}

	return Status::OK;
}

Status OBJ_Loader::load(graph::ModelData& model_data, StringView file_path) noexcept
{
	String file_data_buff;
	if (auto ret = fs::File::read(file_path, file_data_buff); !ret)
		return ret;

	Vector<math::Vec3f> pos;
	Vector<math::Vec3f> norm;
	Vector<math::Vec2f> uv;

	Vector<uint32_t> norm_indx;
	Vector<uint32_t> uv_indx;

	size_t line = 1;
	const char* file_data = file_data_buff.data();
	while (*file_data != '\0') {
		skip_spaces(file_data);
		char statement = *file_data++;
		switch (statement) {
			case 'v':
				switch (*file_data) {
					case 'n': {
						auto& vn = norm.emplace_back();
						skip_spaces(++file_data);
						read(file_data, vn.x);

						skip_spaces(file_data);
						read(file_data, vn.y);

						skip_spaces(file_data);
						read(file_data, vn.z);

						skip_spaces(file_data);
						if (*file_data != '\n') {
							DK_LOG_ERROR("");
							return Status::ERROR;
						}

						++line;
						break;
					}
					case 't': {
						auto& vt = uv.emplace_back();
						skip_spaces(++file_data);
						read(file_data, vt.x);

						skip_spaces(file_data);
						read(file_data, vt.y);

						skip_spaces(file_data);
						if (*file_data != '\n') {
							DK_LOG_ERROR("");
							return Status::ERROR;
						}

						++line;
						break;
					}
					case ' ': {
						auto& v = pos.emplace_back();
						skip_spaces(++file_data);
						read(file_data, v.x);

						skip_spaces(file_data);
						read(file_data, v.y);

						skip_spaces(file_data);
						read(file_data, v.z);

						skip_spaces(file_data);
						if (*file_data != '\n') {
							DK_LOG_ERROR("");
							return Status::ERROR;
						}

						++line;
						break;
					}
				}
				break;
			case 'f':
				//  TODO: remove. super slow, let it grow exponentially
				//model_data.indx.reserve(model_data.indx.capacity() + 3);
				//norm_indx.reserve(norm_indx.capacity() + 3);
				//uv_indx.reserve(uv_indx.capacity() + 3);

				skip_spaces(++file_data);
				read(file_data, model_data.indx.emplace_back());
				expect(file_data, '/');
				read(file_data, uv_indx.emplace_back());
				expect(file_data, '/');
				read(file_data, norm_indx.emplace_back());

				skip_spaces(file_data);
				read(file_data, model_data.indx.emplace_back());
				expect(file_data, '/');
				read(file_data, uv_indx.emplace_back());
				expect(file_data, '/');
				read(file_data, norm_indx.emplace_back());

				skip_spaces(file_data);
				read(file_data, model_data.indx.emplace_back());
				expect(file_data, '/');
				read(file_data, uv_indx.emplace_back());
				expect(file_data, '/');
				read(file_data, norm_indx.emplace_back());

				skip_spaces(file_data);
				if (*file_data != '\n') {
					DK_LOG_ERROR("");
					return Status::ERROR;
				}

				++line;
				break;
			default:
				DK_LOG_WARNING("Unknown statement in the OBJ file '", file_path, "' on line #", line, ": ", '\'', statement, '\'');
				[[fallthrough]];
			case '#':
				skip_line(file_data);
				[[fallthrough]];
			case '\n':
				++line;
				break;
		}
	}

	if (model_data.indx.size() != norm_indx.size() || model_data.indx.size() != uv_indx.size()) {
		DK_LOG_ERROR("");
		return Status::ERROR;
	}

	DK_LOG_OK("Loaded. Compiling size: ", model_data.indx.size());
	if (model_data.indx.size() % 3 != 0)
		DK_LOG_WARNING("");  //  XXX: is this possible? no, is this legal???

	//  TODO: Dirty hach. Rewrite!!!
	/**/ model_data.vert.reserve(model_data.indx.size());
	/**/ for (size_t i = 0; i < model_data.indx.size(); ++i) {
	/**/ 	model_data.vert.emplace_back(pos[model_data.indx[i] - 1], norm[norm_indx[i] - 1], uv[uv_indx[i] - 1]);
	/**/ 	model_data.indx[i] = i;
	/**/ }

	DK_LOG_OK(
		"OBJ data created from file '", file_path, "':\n"
		"\tvertices: ", model_data.vert.size(), '\n',
		"\tindices:  ", model_data.indx.size(), '\n',
		"\tpolygons: ", model_data.indx.size() / 3
	);

	return Status::OK;
}

Status OBJ_Loader::load(graph::Model& model, StringView file_path) noexcept
{
	graph::ModelData model_data;
	if (auto ret = load(model_data, file_path); !ret)
		return ret;

	return model.create(model_data);
}

Resource* OBJ_Loader::load(StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::MODEL_DATA) {
		graph::ModelData* model_data = mem_create(graph::ModelData);
		if (!load(*model_data, file_path)) {
			mem_destroy(model_data);
			return nullptr;
		}

		return model_data;
	} else if (type == ResourceType::MODEL) {
		graph::Model* model = mem_create(graph::Model);
		if (!load(*model, file_path)) {
			mem_destroy(model);
			return nullptr;
		}

		return model;
	}

	DK_LOG_ERROR("OBJ loader does not support this resource type: #", (uint32_t)type);
	return nullptr;
}

Status OBJ_Loader::load(Resource& res, StringView file_path, ResourceType type) noexcept /* override */
{
	if (type == ResourceType::MODEL_DATA) return load(static_cast<graph::ModelData&>(res), file_path);
	else if (type == ResourceType::MODEL) return load(static_cast<graph::Model&>(res), file_path);

	DK_LOG_ERROR("OBJ loader does not support this resource type: #", (uint32_t)type);
	return Status::ERROR;
}

}
