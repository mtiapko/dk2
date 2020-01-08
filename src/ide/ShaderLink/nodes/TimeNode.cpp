#include <chrono>
#include "dk/ide/ShaderLink/nodes/TimeNode.h"
#include "dk/ide/ShaderLink/Core.h"

namespace dk::ide::ShaderLink
{

void TimeNode::update_shader_args(const Core* core) const noexcept /* override */
{
	auto now = std::chrono::steady_clock::now().time_since_epoch();
	float t = std::chrono::duration_cast<std::chrono::milliseconds>(now).count() * 0.001f;
	core->shader()->set_arg(this->pins_param_id()[0], graph::ShaderArg(t));
	core->shader()->set_arg(this->pins_param_id()[1], graph::ShaderArg(std::sin(t)));
	core->shader()->set_arg(this->pins_param_id()[2], graph::ShaderArg(std::sin(t * 2.0f)));
	core->shader()->set_arg(this->pins_param_id()[3], graph::ShaderArg(std::sin(t * 10.0f)));
}

}
