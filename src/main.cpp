#include "dk/ImGui/Manager.h"
#include "dk/graph/Window.h"
#include "dk/ide/ShaderLink/Core.h"
#include "dk/ecs/components/RendererComponent.h"
#include "dk/ecs/Entity.h"
#include "dk/sys/Input.h"
#include "dk/Core.h"
#include "dk/Log.h"

using namespace dk;

class Sandbox final : public Application
{
private:
	Core*                 m_core;
	graph::Renderer*      m_renderer;
	graph::Window*        m_wnd;
	graph::Camera         m_cam { 90.0f, 1920.0f / 1080.0f, 0.01f, 1000.0f };
	ecs::Entity           m_player;
	Vector<ecs::Entity>   m_game_objects;
	ImGui::TextEditor     m_text_editor;
	ide::ShaderLink::Core m_shader_link;
	bool                  m_render_frame = true;

public:
	void update() noexcept override
	{
	}

	void render() noexcept override
	{
		static bool ctrl;
		sys::Input::update();
		if (ctrl) {
			m_cam.update();
			m_cam.update_view_matrix();
			m_cam.update_view_proj_matrix();
		}

		// TODO: move to update(), but not to fixed_update()
		ImGui::Manager::update();
		m_shader_link.render();

		ImGui::Begin("Camera");
		if (ImGui::Checkbox("Control", &ctrl)) {
		}

		if (sys::Keyboard::state(sys::KeyboardBtn::F1))
			ctrl = !ctrl;

		ImGui::End();
		if (sys::Keyboard::state(sys::KeyboardBtn::F5)) {
			static graph::SubShaderData data;
			data.source = m_text_editor.GetText();
			data.type = graph::SubShaderType::FRAGMENT;

			static auto sub_shader = (graph::SubShader*)nullptr;
			if (sub_shader == nullptr) {
				sub_shader = m_renderer->new_resource<graph::SubShader>();
				sub_shader->set_resource_data(&data);
			}

			m_render_frame = (sub_shader->create() == Status::OK);
			if (m_render_frame) {
				auto def = m_renderer->default_shader();
				def->resource_data()->sub_shaders[1] = sub_shader;
				m_render_frame = (def->create() == Status::OK);
			}
		}

		m_renderer->clear();
		if (m_render_frame) {
			m_renderer->begin_rendering(&m_cam);
			for (const auto& renderer: ecs::ComponentManager<ecs::RendererComponent>::get_components()) {
				m_renderer->add_renderable(renderer);
			}

			m_renderer->end_rendering();
			m_renderer->render();
		}

		ImGui::Manager::render();
		m_wnd->render();
	}

	Status create() noexcept override
	{
		sys::Keyboard::record_input(true);
		sys::Mouse::record_input(true);
		m_cam.update_proj_matrix();

		m_core = &Core::get();
		m_renderer = m_core->active<graph::Renderer>();
		if (m_renderer == nullptr)
			return Status::ERROR;

		m_wnd = m_renderer->new_resource<graph::Window>();
		if (auto err = m_wnd->create(); !err)
			return err;

		auto model = m_core->resource_manager().import<graph::Model>("res/model/castle_fantasy_book/model.fbx");
		if (model == nullptr)
			return Status::ERROR;

		for (auto& sub_model: model->sub_models()) {
			auto& o = m_game_objects.emplace_back();
			o.add_component<ecs::TransformComponent>();
			o.add_component<ecs::RendererComponent>(
				&o, sub_model.mesh(), &sub_model.material()
			);
		}

		auto lang = ImGui::TextEditor::LanguageDefinition::CPlusPlus();
		m_text_editor.SetLanguageDefinition(lang);
		m_text_editor.SetText(m_renderer->default_shader()->resource_data()->sub_shaders[1]->resource_data()->source);

		if (auto err = m_shader_link.create(); !err)
			return err;

		return Status::OK;
	}

	void destroy() noexcept override
	{
	}
};

int main()
{
	auto& core = Core::get();
	if (auto err = core.create(); !err)
		return err;

	if (core.plugin_manager().load("plugins/gl.so") == nullptr)
		return Status::ERROR;

	Sandbox sandbox;
	if (auto err = core.run(&sandbox); !err)
		return err;

	core.destroy();
	return Status::OK;
}
