#ifndef __DK_GRAPH_RENDERER_H__
#define __DK_GRAPH_RENDERER_H__

#include "dk/containers/Array.h"
#include "dk/graph/RenderQueue.h"
#include "dk/graph/Camera.h"
#include "dk/sys/ResourceCreator.h"

namespace dk::graph
{

class Renderer : public sys::ResourceCreator
{
private:
	Array<RenderQueue, (int)RenderQueueType::RENDER_QUEUE_TYPE_SIZE> m_render_queues;
	Camera* m_active_camera = nullptr;

public:
	void begin_rendering(Camera* cam) noexcept { m_active_camera = cam; };
	void end_rendering() noexcept {};

	void render() noexcept
	{
		for (auto& queue: m_render_queues) {
			queue.sort();

			const graph::Material* curr_material = nullptr;
			const graph::Shader* curr_shader = nullptr;
			for (const auto& renderable: queue.queued_renderables()) {
				auto renderer = renderable.renderer();
				if (renderer->material != curr_material) {
					curr_material = renderer->material;
					if (curr_material->shader() != curr_shader) {
						curr_shader = curr_material->shader();
						curr_material->shader()->enable();
					}

					curr_material->enable();
					curr_material->shader()->set_arg("view_proj", m_active_camera->view_proj_matrix());
					curr_material->shader()->set_arg("camera_pos", m_active_camera->position());

					if (sys::Keyboard::state(sys::KeyboardBtn::TAB))
						curr_material->shader()->set_arg("kek", 1.0f);
					else
						curr_material->shader()->set_arg("kek", 0.0f);
				}

				renderer->mesh->render();
			}

			queue.clear();
		}
	}

	void add_renderable(const ecs::RendererComponent& renderer) noexcept
	{
		m_render_queues[(int)RenderQueueType::DEFAULT].add(0, &renderer);
	}

	virtual void clear() noexcept = 0;

	virtual Shader* default_shader() noexcept = 0; // TODO: make 'Shader::get_shader("Default")'
	Camera* active_camera() const noexcept { return m_active_camera; }

	virtual Resource* new_resource(ResourceType type) noexcept = 0;

	template<typename T> T* new_resource() noexcept
	{
		return (T*)this->new_resource(T::get_resource_type());
	}
};

}

#endif // !__DK_GRAPH_RENDERER_H__
