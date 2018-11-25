#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cstring>
#include "log.h"
#include "graphic/mesh.h"

namespace dk
{

status mesh::load(string_view file_path)
{
	auto beg = std::chrono::high_resolution_clock::now();
	FILE* file = fopen(file_path.data(), "rb");
	if (file == nullptr) {
		return status::ERROR;
	}

	struct stat file_stat;
	fstat(fileno(file), &file_stat);
	char* file_data = (char*)malloc(file_stat.st_size + 1);
	if (fread(file_data, sizeof(char), file_stat.st_size, file) != (size_t)file_stat.st_size) {
		return status::ERROR;
	}

	fclose(file);
	file_data[file_stat.st_size] = '\0';

	vector<vec3f> normals(4096);
	vector<vec3f> uvs(4096);

	size_t i = 0;
	while (file_data[i] != '\0') {
		char c = file_data[i++];
		if (c == 'v') {
			c = file_data[i++];
			if (c == ' ') {
				size_t len;
				auto& v = m_vertices.emplace_back();
				if (sscanf(&file_data[i], " %f %f %f %zn", &v.x, &v.y, &v.z, &len) != 3) {
					return status::ERROR;
				}

				i += len;
			} else if (c == 'n') {
				size_t len;
				auto& vn = normals.emplace_back();
				if (sscanf(&file_data[i], " %f %f %f %zn", &vn.x, &vn.y, &vn.z, &len) != 3) {
					return status::ERROR;
				}

				i += len;
			} else if (c == 't') {
				size_t len;
				auto& vt = uvs.emplace_back();
				if (sscanf(&file_data[i], " %f %f %zn", &vt.x, &vt.y, &len) != 2) {
					return status::ERROR;
				}

				i += len;
			} else {
				DK_LOG_ERROR("Unknown 'v' param: ", file_path);
				return status::ERROR;
			}
		} else if (c == 'f') {
			m_indices.reserve(3);
			auto& i1 = m_indices.emplace_back();
			auto& i2 = m_indices.emplace_back();
			auto& i3 = m_indices.emplace_back();

			m_normals.reserve(3);
			auto& vn1 = m_normals.emplace_back();
			auto& vn2 = m_normals.emplace_back();
			auto& vn3 = m_normals.emplace_back();

			m_uvs.reserve(3);
			auto& uv1 = m_uvs.emplace_back();
			auto& uv2 = m_uvs.emplace_back();
			auto& uv3 = m_uvs.emplace_back();

			uint32_t n[3];
			uint32_t u[3];
			size_t len;
			if (sscanf(&file_data[i], " %u/%u/%u %u/%u/%u %u/%u/%u %zn", &i1, &n[0], &u[0],
					&i2, &n[1], &u[1], &i3, &n[2], &u[2], &len) != 9) {
				return status::ERROR;
			}

			--i1;
			--i2;
			--i3;

			vn1 = normals[n[0] - 1];
			vn2 = normals[n[1] - 1];
			vn3 = normals[n[2] - 1];

			uv1 = uvs[u[0] - 1];
			uv2 = uvs[u[1] - 1];
			uv3 = uvs[u[2] - 1];
			i += len;
		} else {
			auto nl = strchr(&file_data[--i], '\n');
			if (nl == nullptr)
				break;

			i = std::distance(file_data, nl) + 1;
		}
	}

	free(file_data);
	auto end = std::chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);
	DK_LOG_OK("Mesh loaded: ", file_path, " (", dur.count() / 1000.0f, " ms)");
	DK_LOG("v: ", m_vertices.size(), ", vn: ", m_normals.size(), ", vt: ", m_uvs.size(), ", i: ", m_indices.size());
	return status::OK;
}

}
