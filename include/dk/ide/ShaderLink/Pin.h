#ifndef __DK_IDE_SHADER_LINK_PIN_H__
#define __DK_IDE_SHADER_LINK_PIN_H__

#include "dk/containers/Vector.h"
#include "dk/ide/ShaderLink/NodeIO.h"

namespace dk::ide::ShaderLink
{

class Pin
{
private:
	size_t              m_external_id;
	class Node*         m_node;
	size_t              m_node_pin_id;
	NodeIOType          m_type;
	Vector<class Link*> m_links;

public:
	Pin(size_t external_id, class Node* node, size_t node_pin_id, NodeIOType type) noexcept
		: m_external_id(external_id)
		, m_node(node)
		, m_node_pin_id(node_pin_id)
		, m_type(type)
	{}

	bool is_connected() const noexcept { return !m_links.empty(); }
	bool is_input() const noexcept;

	size_t external_id() const noexcept { return m_external_id; }
	class Node* node() const noexcept { return m_node; }
	size_t node_pin_id() const noexcept { return m_node_pin_id; }

	NodeIOType type() const noexcept { return m_type; }
	void set_type(NodeIOType type) noexcept { m_type = type; }

	const auto& links() const noexcept { return m_links; }
	void add_link(class Link* link) noexcept { m_links.emplace_back(link); }
	void remove_link(class Link* link) noexcept { std::erase(m_links, link); }
};

}

#endif // !__DK_IDE_SHADER_LINK_PIN_H__
