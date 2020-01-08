#include "dk/ide/ShaderLink/nodes/ColorNode.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

void ColorNode::draw() noexcept /* override */
{
	this->draw_begin();
	ImGui::Dummy(ImVec2(0, 0));
	ImGui::SameLine(45.0f);
	this->draw_outputs();

	ImGui::PushItemWidth(130.0f);
	ImGui::PushID((void*)this);

	ImGui::ColorPicker4("Color picker", m_color.data(),
		ImGuiColorEditFlags_NoOptions |
		ImGuiColorEditFlags_NoTooltip |
		ImGuiColorEditFlags_NoSidePreview |
		ImGuiColorEditFlags_NoSmallPreview |
		ImGuiColorEditFlags_DisplayRGB |
		ImGuiColorEditFlags_NoLabel);

	ImGui::PopID();
	ImGui::PopItemWidth();
	this->draw_end();
}

void ColorNode::update_shader_args(const Core* core) const noexcept /* override */
{
	core->shader()->set_arg(this->pins_param_id()[0], m_color.operator math::Vec3f());
	core->shader()->set_arg(this->pins_param_id()[1], m_color.a);
}

}
