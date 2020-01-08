#ifndef __DK_IDE_SHADER_LINK_NODE_H__
#define __DK_IDE_SHADER_LINK_NODE_H__

#include "dk/containers/String.h"
#include "dk/containers/Vector.h"
#include "dk/ide/ShaderLink/NodeIO.h"
#include "dk/Status.h"

namespace dk::ide::ShaderLink
{

class Node
{
protected:
	size_t                 m_external_id;
	const class NodeClass* m_node_class;
	Vector<class Pin*>     m_pins;

	String m_name;
	Vector<String> m_pins_name;

	String         m_code;
	size_t         m_hash = 0;

	virtual void gen_pins_name(size_t node_id) noexcept;

	virtual Status gen_code() noexcept;
	void gen_hash() noexcept;

	void draw_begin() const noexcept;
	void draw_end() const noexcept;

	float draw_header() const noexcept;
	void draw_footer(float header_bot_y) const noexcept;

	static void draw_input(const class Pin* pin, StringView name) noexcept;
	void draw_inputs() const noexcept;

	static void draw_output(const class Pin* pin, StringView name) noexcept;
	void draw_outputs() const noexcept;

public:
	virtual void draw() noexcept;
	virtual void update_shader_args(const class Core* /* core */) const noexcept {};

	bool cmp(const Node* that) const noexcept;
	Status generate() noexcept;

	size_t external_id() const noexcept { return m_external_id; }
	const class NodeClass* node_class() const noexcept { return m_node_class; }
	const auto& pins() const noexcept { return m_pins; }

	/* XXX: const ref to use 'Shader::set_arg()' w/o casting and mem allocs */
	const String& name() const noexcept { return m_name; }
	const auto& pins_name() const noexcept { return m_pins_name; }

	StringView code() const noexcept { return m_code; }
	size_t hash() const noexcept { return m_hash; }

	virtual void create(class Core* core, const class NodeClass* node_class, size_t external_id, size_t node_id, size_t base_pin_id) noexcept;
};

}

#endif // !__DK_IDE_SHADER_LINK_NODE_H__
