#include "dk/ide/ShaderLink/nodes/FloatNode.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

void FloatNode::draw() noexcept /* override */
{
	this->draw_begin();

	ImGui::PushItemWidth(50.0f);
	ImGui::PushID((void*)this);

	ImGui::DragFloat("", &m_float, 0.1f);

	ImGui::PopID();
	ImGui::PopItemWidth();

	ImGui::SameLine();
	this->draw_outputs();
	this->draw_end();
}

void FloatNode::update_shader_args(const Core* core) const noexcept /* override */
{
	core->shader()->set_arg(this->pins_param_id()[0], m_float);
}

}
