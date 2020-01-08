#ifndef __DK_GL_MODEL_IMPORTER_H__
#define __DK_GL_MODEL_IMPORTER_H__

#include "dk/sys/ResourceImporter.h"
#include "dk/graph/Model.h"
#include "Common.h"

namespace gl
{

class ModelImporter : public sys::ResourceImporter
{
private:
	Status import_model_node_mesh(graph::SubModel& sub_model, const struct aiScene* scene, struct aiMesh* ai_mesh) noexcept;
	Status import_model_node(graph::Model* model, const struct aiScene* scene, struct aiNode* node) noexcept;

	Status import_model_data(graph::Model* model, StringView file_path) noexcept;
	Status import_model(graph::Model* model, StringView file_path) noexcept;

public:
	Resource* import(ResourceType type, StringView file_path) noexcept override;
	Status import(Resource* res, StringView file_path) noexcept override;

	void delete_resource(Resource* res) noexcept override;
};

}

#endif // !__DK_GL_MODEL_IMPORTER_H__
