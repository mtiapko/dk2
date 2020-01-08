#ifndef __DK_IDE_SHADER_LINK_CORE_H__
#define __DK_IDE_SHADER_LINK_CORE_H__

#include "dk/ImGui/NodeEditor/imgui_node_editor.h"
#undef ImGui

#include <map> // TODO: use internal header
#include "dk/containers/UniquePtr.h"
#include "dk/graph/Shader.h"
#include "dk/ide/ShaderLink/NodeClass.h"
#include "dk/ide/ShaderLink/Node.h"
#include "dk/ide/ShaderLink/Link.h"
#include "dk/ide/ShaderLink/Pin.h"
#include "dk/sys/events/KeyPressEvent.h"
#include "dk/sys/EventManager.h"
#include "dk/sys/Keyboard.h"

namespace dk::ide::ShaderLink
{

class Core final : public sys::EventListener<sys::KeyPressEvent>
{
private:
	static inline Vector<NodeClass*> s_node_classes;

	ax::NodeEditor::EditorContext* m_context = nullptr;
	size_t                         m_external_id = 0; /* node + pin */
	size_t                         m_link_external_id = 0;
	ImVec2                         m_next_node_pos;

	Vector<UniquePtr<Node>> m_nodes;
	Vector<UniquePtr<Link>> m_links;
	Vector<UniquePtr<Pin>>  m_pins;

	bool m_is_running = false;
	Node* m_output_node = nullptr;
	Pin* m_new_link_beg_pin = nullptr;
	graph::Shader* m_shader;

	// TODO: rewrite to internal type
	/* search by EXTERNAL id */
	std::map<size_t, Node*> m_node_map;
	std::map<size_t, Link*> m_link_map;
	std::map<size_t, Pin*>  m_pin_map;

	void new_node(size_t node_class_id) noexcept;
	void new_link(Pin* beg_pin, Pin* end_pin) noexcept;

	void delete_node(Node* node) noexcept;
	void delete_link(Link* link) noexcept;

	void draw_nodes_palette() noexcept;
	void draw_nodes() noexcept;
	void draw_links() noexcept;

	// TODO: rename
	static bool validate_link(const Pin* beg_pin, const Pin* end_pin) noexcept;
	bool is_valid_link(const Pin* beg_pin, const Pin* end_pin) const noexcept;
	void apply_type(Pin* pin, NodeIOType type) noexcept;

	Status parse(Node* node, String& uniforms, String& funcs, String& main_func) const noexcept;
	Status generate() noexcept;

	void handle(const sys::KeyPressEvent& e) noexcept;

public:
	static const auto& get_node_classes() noexcept { return s_node_classes; }
	static void add_node_class(NodeClass* node_class) noexcept { s_node_classes.emplace_back(node_class); }

	static String convert_name(StringView name) noexcept;
	static String mangle_name(StringView name) noexcept;

	auto& nodes() noexcept { return m_nodes; }
	auto& pins() noexcept { return m_pins; }

	const auto& links() const noexcept { return m_links; }
	const auto& pins() const noexcept { return m_pins; }

	graph::Shader* shader() const noexcept { return m_shader; }

	void render() noexcept;

	Status create() noexcept;
};

}

#endif // !__DK_IDE_SHADER_LINK_CORE_H__
