#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <SOIL2.h>
#include <algorithm>
#include "dk/Assert.h"
#include "dk/Mem.h"
#include "dk/Log.h"
#include "ModelImporter.h"

namespace gl
{

Status import_texture_data(graph::TextureData* tex_data, const aiTexture* tex) noexcept
{
	int width;
	int height;
	int channels;
	tex_data->data = SOIL_load_image_from_memory((uint8_t*)tex->pcData, tex->mWidth * std::max(tex->mHeight, 1u),
		&width, &height, &channels, SOIL_LOAD_AUTO);
	if (tex_data->data == nullptr) {
		DK_LOG_ERROR("SOIL failed to import texture: ", SOIL_last_result());
		return Status::ERROR;
	}

	tex_data->width = width;
	tex_data->height = height;
	switch (channels) {
		case SOIL_LOAD_L:    tex_data->type = graph::TextureType::GRAY;       break;
		case SOIL_LOAD_LA:   tex_data->type = graph::TextureType::GRAY_ALPHA; break;
		case SOIL_LOAD_RGB:  tex_data->type = graph::TextureType::RGB;        break;
		case SOIL_LOAD_RGBA: tex_data->type = graph::TextureType::RGBA;       break;
		default:
			DK_LOG_ERROR("Unsupported SOIL texture type #", channels);
			return Status::ERROR;
	}

	return Status::OK;
}

Status import_material_texture(graph::SubModel& sub_model, const struct aiScene* ai_scene,
	const aiMaterial* ai_material, aiTextureType ai_type) noexcept
{
	for (uint32_t i = 0; i < ai_material->GetTextureCount(ai_type); ++i) {
		aiString ai_str;
		ai_material->GetTexture(ai_type, i, &ai_str);

		graph::Texture* tex;
		if (ai_str.data[0] != '*') {
			String tex_dir = "res/model/castle_fantasy_book/"; // TODO: I know, this is so ugly. Remove
			String tex_path = tex_dir + String(ai_str.data, ai_str.length);

			tex = Core::get().resource_manager().import<graph::Texture>(tex_path);
			if (tex == nullptr)
				return Status::ERROR;
		} else {
			graph::TextureData tex_data;
			int tex_id = std::atoi(ai_str.data + 1 /* skip first '*' symbol */);
			if (auto err = import_texture_data(&tex_data, ai_scene->mTextures[tex_id]); !err)
				return err;

			tex = Core::get().active<graph::Renderer>()->new_resource<graph::Texture>();
			if (auto err = tex->create_from_resource_data(&tex_data); !err)
				return err;
		}

		switch (ai_type) {
			case aiTextureType_DIFFUSE:  sub_model.material().set_shader_arg("DK_DIFFUSE_TEX", tex); break;
			case aiTextureType_SPECULAR: sub_model.material().set_shader_arg("DK_SPECULAR_TEX", tex); break;
			case aiTextureType_HEIGHT:   sub_model.material().set_shader_arg("DK_NORMAL_TEX", tex); break;
			default:
				DK_LOG_ERROR("Unsupported texture type #", ai_type);
				return Status::ERROR;
		}
	}

	// TODO:
	/*aiColor3D color;
	if (ai_material->Get(AI_MATKEY_COLOR_AMBIENT, color) == aiReturn_SUCCESS) {
		DK_LOG("Material ambient color: { ", color.r, ", ", color.g, ", ", color.b, " }");
	}

	if (ai_material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == aiReturn_SUCCESS) {
		DK_LOG("Material diffuse color: { ", color.r, ", ", color.g, ", ", color.b, " }");
		sub_model.material().set_shader_arg("material_color", math::Vec3f(color.r, color.g, color.b));
	}*/

	// TODO: remove
	//for (uint32_t i = 0; i < ai_material->mNumProperties; ++i) {
	//	DK_LOG("Property: '", StringView(ai_material->mProperties[i]->mKey.data, ai_material->mProperties[i]->mKey.length), '\'');
	//}

	return Status::OK;
}

Status ModelImporter::import_model_node_mesh(graph::SubModel& sub_model, const struct aiScene* scene, struct aiMesh* ai_mesh) noexcept
{
	/* if 'aiProcess_Triangulate' flag removed replace '3' by 'face.mNumIndices' */
	DK_ASSERT(ai_mesh->mNumFaces == 0 || ai_mesh->mFaces[0].mNumIndices == 3, "Replace '3' by 'face.mNumIndices'");
	auto mesh_data_ints = dk_mem_new(graph::MeshData);
	auto& mesh_data = *mesh_data_ints;
	mesh_data.vertices.reserve(ai_mesh->mNumVertices);
	mesh_data.indices.reserve(ai_mesh->mNumFaces * 3);

	const bool does_mesh_have_UVs = ai_mesh->HasTextureCoords(0);
	const bool does_mesh_have_tangent = ai_mesh->HasTangentsAndBitangents();
	for (uint32_t i = 0; i < ai_mesh->mNumVertices; ++i) {
		auto& vertex = mesh_data.vertices.emplace_back();
		vertex.position = math::Vec3f(ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z);
		vertex.normal = math::Vec3f(ai_mesh->mNormals[i].x, ai_mesh->mNormals[i].y, ai_mesh->mNormals[i].z);

		if (does_mesh_have_tangent) {
			vertex.tangent = math::Vec3f(ai_mesh->mTangents[i].x, ai_mesh->mTangents[i].y, ai_mesh->mTangents[i].z);
			vertex.bitangent = math::Vec3f(ai_mesh->mBitangents[i].x, ai_mesh->mBitangents[i].y, ai_mesh->mBitangents[i].z);
		}

		if (does_mesh_have_UVs)
			vertex.uv = math::Vec2f(ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y);
	}

	for (uint32_t i = 0; i < ai_mesh->mNumFaces; ++i) {
		auto face = ai_mesh->mFaces[i];
		mesh_data.indices.emplace_back(face.mIndices[0]);
		mesh_data.indices.emplace_back(face.mIndices[1]);
		mesh_data.indices.emplace_back(face.mIndices[2]);

		/* Uncomment if face does not triangle */
		/* for (uint32_t j = 0; j < face.mNumIndices; ++j)
				mesh_data.indices.emplace_back(face.mIndices[j]); */
	}

	auto mesh = Core::get().active<graph::Renderer>()->new_resource<graph::Mesh>();
	sub_model.set_mesh(mesh);
	mesh->set_resource_data(mesh_data_ints);
	if (auto err = mesh->create_from_resource_data(&mesh_data); !err)
		return err;

	// TODO: remove
	sub_model.material().set_shader(Core::get().active<graph::Renderer>()->default_shader());
	auto ai_material = scene->mMaterials[ai_mesh->mMaterialIndex];
	if (auto err = import_material_texture(sub_model, scene, ai_material, aiTextureType_DIFFUSE); !err)
		return err;

	if (auto err = import_material_texture(sub_model, scene, ai_material, aiTextureType_SPECULAR); !err)
		return err;

	if (auto err = import_material_texture(sub_model, scene, ai_material, aiTextureType_HEIGHT); !err)
		return err;

	return Status::OK;
}

Status ModelImporter::import_model_node(graph::Model* model, const struct aiScene* scene, struct aiNode* node) noexcept
{
	DK_LOG("Importing node '", StringView(node->mName.data, node->mName.length),
		"' with ", node->mNumMeshes, " meshes and ", node->mNumChildren, " childrens...");

	for (uint32_t i = 0; i < node->mNumMeshes; ++i) {
		auto ai_mesh = scene->mMeshes[node->mMeshes[i]];
		auto& sub_model = model->new_sub_model();
		//auto mesh = model->meshes.emplace_back(dk_mem_new(graph::MeshData));
		if (auto err = this->import_model_node_mesh(sub_model, scene, ai_mesh); !err)
			return err;

		//DK_LOG("Mesh with ", mesh->vertices.size(), " vertices and ", mesh->indices.size() / 3, " faces imported");
	}

	for (uint32_t i = 0; i < node->mNumChildren; ++i) {
		if (auto err = this->import_model_node(model, scene, node->mChildren[i]); !err)
			return err;
	}

	return Status::OK;
}

Status ModelImporter::import_model_data(graph::Model* data, StringView file_path) noexcept
{
	// TODO: remove PreTransformVertices
	Assimp::Importer importer;
	const auto scene = importer.ReadFile(file_path.data(), aiProcess_Triangulate
		| aiProcess_CalcTangentSpace /* | aiProcess_PreTransformVertices */);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
		DK_LOG_ERROR("Assimp failed to import model '", file_path, "': ", importer.GetErrorString());
		return Status::ERROR;
	}

	if (auto err = this->import_model_node(data, scene, scene->mRootNode); !err)
		return err;

	uint32_t indx = 0;
	uint32_t vert = 0;
	for (const auto& sub_model: data->sub_models()) {
		const auto mesh_data = sub_model.mesh()->resource_data();
		if (mesh_data != nullptr) {
			indx += mesh_data->indices.size();
			vert += mesh_data->vertices.size();
		}
	}

	DK_LOG_OK("Model '", file_path, "' contains ", data->sub_models().size(), " sub models, ",
		vert, " vertices and ", indx / 3, " faces");
	return Status::OK;
}

Status ModelImporter::import_model(graph::Model* model, StringView file_path) noexcept
{
	/*graph::ModelData data; // TODO: set resource owner?
	if (auto err = this->import_model_data(&data, file_path); !err)
		return err;

	uint32_t vert_count = 0;
	uint32_t face_count = 0;
	for (const auto mesh: data.meshes) {
		vert_count += mesh->vertices.size();
		face_count += mesh->indices.size();
	}

	DK_LOG_OK("Model with ", data.meshes.size(), " meshes ",
		vert_count, " vertices and ", face_count / 3, " faces imported");

	if (vert_count == face_count)
		DK_LOG_WARNING("Model has same count of vertices and indices, use 'glDrawArrys()'?");*/

	//return model->create(&data);
	return this->import_model_data(model, file_path);
}

Resource* ModelImporter::import(ResourceType type, StringView file_path) noexcept /* override */
{
	/*if (type == ResourceType::MODEL_DATA) {
		UniquePtr<graph::ModelData> data(dk_mem_new(graph::ModelData));
		if (auto err = this->import_model_data(data.get(), file_path); !err)
			return nullptr;

		return (Resource*)data.release();
	} else */if (type == ResourceType::MODEL) {
		//auto model_deleter = [](graph::Model* model) noexcept
		//	{ model->resource_creator()->delete_resource(model); };

		//UniquePtr<graph::Model, decltype(model_deleter)>
		//	model(Core::get().active<graph::Renderer>()->new_resource<graph::Model>());
		graph::Model model;
		if (auto err = this->import_model(&model, file_path); !err)
			return nullptr;

		return (Resource*)dk_mem_new(graph::Model, model);
	}

	DK_LOG_ERROR("Unsupported resource type");
	return nullptr;
}

Status ModelImporter::import(Resource* res, StringView file_path) noexcept /* override */
{
	switch (res->resource_type()) {
		//case ResourceType::MODEL_DATA: return this->import_model_data((graph::ModelData*)res, file_path);
		case ResourceType::MODEL: return this->import_model((graph::Model*)res, file_path);
		default:
			DK_LOG_ERROR("Unsupported resource type");
			return Status::ERROR;
	}
}

void ModelImporter::delete_resource(Resource* res) noexcept /* override */
{
	res->destroy();
	dk_mem_delete(res);
}

}
