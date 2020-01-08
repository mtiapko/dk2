#ifndef __DK_IDE_SHADER_LINK_NODE_CLASS_H__
#define __DK_IDE_SHADER_LINK_NODE_CLASS_H__

#include <type_traits>
#include "dk/containers/String.h"
#include "dk/containers/Vector.h"
#include "dk/ide/ShaderLink/NodeIO.h"

namespace dk::ide::ShaderLink
{

class NodeClass
{
private:
	String         m_name;
	String         m_body_code;
	Vector<NodeIO> m_io;
	size_t         m_inputs_count = 0;

	template<typename T>
	void process_io() noexcept
	{
		auto type = std::remove_reference_t<T>::type;
		auto name = std::remove_reference_t<T>::name;

		if constexpr (std::is_reference_v<T>) m_io.emplace_back(type, name);
		else m_io.emplace(m_io.begin() + m_inputs_count++, type, name);
	}

public:
	template<typename... IO>
	NodeClass(StringView name, StringView (*get_body_code)(IO...) noexcept) noexcept
	{
		// TODO: if input -> no dynamic
		m_name = name;
		m_body_code = ((StringView (*)())(void*)get_body_code)();//get_body_code(IO {}...); // TODO: if not input
		m_io.reserve(sizeof... (IO));
		(process_io<IO>(), ...);
	}

	virtual class Node* new_node() const noexcept = 0;

	virtual bool is_input_node() const noexcept = 0;
	virtual bool is_unique_input_node() const noexcept = 0;
	virtual bool is_output_node() const noexcept = 0;

	StringView name() const noexcept { return m_name; }
	String body_code() const noexcept { return m_body_code; }
	const auto& io() const noexcept { return m_io; }
	size_t inputs_count() const noexcept { return m_inputs_count; }
};

}

#endif // !__DK_IDE_SHADER_LINK_NODE_CLASS_H__
