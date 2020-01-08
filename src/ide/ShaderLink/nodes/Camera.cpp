#include "dk/ide/ShaderLink/UniqueInputNode.h"
#include "dk/ide/ShaderLink/NodeClassEntry.h"
#include "dk/Core.h"

namespace dk::ide::ShaderLink
{

class CameraNode final : public UniqueInputNode
{
private:
	static constexpr char Pos[] = "Pos";
	static constexpr char Dir[] = "Dir";

	static StringView Camera(Vec3<Pos>&, Vec3<Dir>&) noexcept { return {}; }

	static inline const NodeClassEntry<CameraNode> s_class_entry { "Camera", Camera };

public:
	void update_shader_args(const class Core* core) const noexcept override
	{
		auto camera = dk::Core::get().active<graph::Renderer>()->active_camera();
		core->shader()->set_arg(this->pins_param_id()[0], camera->position());
		core->shader()->set_arg(this->pins_param_id()[1], camera->direction());
	}
};

}
