#include "dk/ide/ShaderLink/NodeClass.h"
#include "dk/ide/ShaderLink/Node.h"
#include "dk/ide/ShaderLink/Core.h"

namespace ed = ax::NodeEditor;

namespace dk::ide::ShaderLink
{

/* virtual */ void Node::gen_pins_name(size_t node_id) noexcept
{
	m_pins_name.clear();
	m_pins_name.reserve(m_pins.size());

	const String node_id_str = std::to_string(node_id);
	for (const auto& io: m_node_class->io()) {
		auto& pin_name = m_pins_name.emplace_back();
		pin_name.reserve(this->name().size()
			+ !io.name.empty() /* '_' */ + io.name.size()
			+ 1 /* '_' */ + node_id_str.size());

		pin_name = this->name();
		if (!io.name.empty()) {
			pin_name += '_';
			pin_name += Core::convert_name(io.name); // TODO: pre-convert
		}

		pin_name += '_';
		pin_name += node_id_str;
	}
}

/* virtual */ Status Node::gen_code() noexcept
{
	m_code = "void ";
	m_code += m_name;
	m_code += "(";

	for (size_t node_pin_id = 0; node_pin_id < m_pins.size(); ++node_pin_id) {
		auto pin = m_pins[node_pin_id];
		if (NodeIO::is_dynamic_type(pin->type()))
			return Status::ERROR;

		const auto& io = m_node_class->io()[node_pin_id];
		if (node_pin_id != 0)
			m_code += ", ";

		if (node_pin_id >= m_node_class->inputs_count())
			m_code += "out ";

		m_code += NodeIO::get_type_name(pin->type());
		m_code += Core::convert_name(io.name);
	}

	m_code += ")\n";
	m_code += m_node_class->body_code();
	m_code += "\n";
	return Status::OK;
}

void Node::gen_hash() noexcept
{
	m_hash = std::hash<size_t> {}((size_t)m_node_class);
	for (auto pin: m_pins)
		m_hash += std::hash<uint32_t> {}((uint32_t)pin->type());
}

void Node::draw_begin() const noexcept
{
	ed::BeginNode(m_external_id);
}

void Node::draw_end() const noexcept
{
	ed::EndNode();
}

float Node::draw_header() const noexcept
{
	ImGui::Text("%s", m_node_class->name().data());
	const float header_bot_y = ImGui::GetItemRectMax().y;

	ImGui::Spacing();
	return header_bot_y;
}

void Node::draw_footer(float header_bot_y) const noexcept
{
	auto top_left = ImGui::GetItemRectMin();
	auto bot_righ = ImGui::GetItemRectMax();
	auto draw_list = ed::GetNodeBackgroundDrawList(m_external_id);

	const float border_width = (int)ed::GetStyle().NodeBorderWidth;
	const auto a = ImVec2 { top_left.x + border_width, top_left.y + border_width };
	const auto b = ImVec2 { bot_righ.x - border_width, header_bot_y };
	const auto color = ImColor { 100, 90, 140, 255 };
	draw_list->AddRectFilled(a, b, color, ed::GetStyle().NodeRounding, 3);
}

/* static */ void Node::draw_input(const Pin* pin, StringView name) noexcept
{
	auto pos = ImGui::GetCursorScreenPos();
	auto draw_list = ImGui::GetWindowDrawList();
	auto size = ImVec2 { 10.0f, 10.0f };
	ImGui::Dummy(ImVec2(size.x, size.y + 6.0f));

	pos.x += 3.0f;
	pos.y += 3.0f;
	auto a = ImVec2 { pos.x, pos.y };
	auto b = ImVec2 { pos.x + size.x, pos.y + size.y * 0.5f };
	auto c = ImVec2 { pos.x, pos.y + size.y };
	auto color = ImColor { ImVec4 { 0.35f, 0.45f, 0.65f, 1.0f } };
	draw_list->AddTriangle(a, b, c, color, 3.0f);
	if (pin->is_connected()) {
		a.x += 1.8f;
		a.y += 3.0f;

		b.x -= 3.0f;

		c.x += 1.8f;
		c.y -= 3.0f;

		color = ImColor { ImVec4 { 0.35f, 0.65f, 0.55f, 1.0f } };
		draw_list->AddTriangleFilled(a, b, c, color);
	}

	/* name */
	ImGui::SameLine();
	ImGui::Text("%s", name.data());

	/* type */
	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)ImColor(128, 128, 128, 255));
	ImGui::Text("(%s)", NodeIO::get_type_name_short(pin->type()).data());
	ImGui::PopStyleColor();
}

void Node::draw_inputs() const noexcept
{
	ImGui::BeginGroup();
	for (size_t node_pin_id = 0; node_pin_id < m_node_class->inputs_count(); ++node_pin_id) {
		auto pin = m_pins[node_pin_id];
		const auto& io = m_node_class->io()[node_pin_id];

		ed::BeginPin(pin->external_id(), ed::PinKind::Input);
		this->draw_input(pin, io.name);
		ed::EndPin();
	}

	ImGui::EndGroup();
}

/* static */ void Node::draw_output(const Pin* pin, StringView name) noexcept
{
	/* name */
	if (!name.empty()) {
		ImGui::Text("%s", name.data());
		ImGui::SameLine();
	}

	/* type */
	ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)ImColor(128, 128, 128, 255));
	ImGui::Text("(%s)", NodeIO::get_type_name_short(pin->type()).data());
	ImGui::PopStyleColor();
	ImGui::SameLine();

	auto pos = ImGui::GetCursorScreenPos();
	const auto size = ImVec2 { 10.0f, 10.0f };
	ImGui::Dummy(ImVec2(size.x, size.y + 6.0f));

	pos.x -= 3.0f;
	pos.y += 3.0f;
	auto a = ImVec2 { pos.x, pos.y };
	auto b = ImVec2 { pos.x + size.x, pos.y + size.y * 0.5f };
	auto c = ImVec2 { pos.x, pos.y + size.y };
	auto color = ImColor { ImVec4 { 0.35f, 0.65f, 0.55f, 1.0f } };
	auto draw_list = ImGui::GetWindowDrawList();
	draw_list->AddTriangle(a, b, c, color, 3.0f);
	if (pin->is_connected()) {
		a.x += 1.8f;
		a.y += 3.0f;

		b.x -= 3.0f;

		c.x += 1.8f;
		c.y -= 3.0f;

		color = ImColor { ImVec4 { 0.35f, 0.45f, 0.65f, 1.0f } };
		draw_list->AddTriangleFilled(a, b, c, color);
	}
}

void Node::draw_outputs() const noexcept
{
	ImGui::BeginGroup();
	for (size_t node_pin_id = m_node_class->inputs_count(); node_pin_id < m_pins.size(); ++node_pin_id) {
		auto pin = m_pins[node_pin_id];
		const auto& io = m_node_class->io()[node_pin_id];

		ed::BeginPin(pin->external_id(), ed::PinKind::Output);
		this->draw_output(pin, io.name);
		ed::EndPin();
	}

	ImGui::EndGroup();
}

/* virtual */ void Node::draw() noexcept
{
	/* header */
	this->draw_begin();
	float header_bot_y = this->draw_header();

	/* inputs */
	this->draw_inputs();

	/* content */
	ImGui::SameLine();
	ImGui::Dummy(ImVec2 { 10.0f, 0.0f });
	ImGui::SameLine();

	/* outputs */
	if (!m_node_class->is_output_node()) // TODO: remove
		this->draw_outputs();

	/* footer */
	this->draw_end();
	this->draw_footer(header_bot_y);
}

bool Node::cmp(const Node* that) const noexcept
{
	if (this->m_node_class != that->m_node_class)
		return false;

	for (size_t node_pin_id = 0; node_pin_id < m_pins.size(); ++node_pin_id) {
		auto this_pin = this->m_pins[node_pin_id];
		auto that_pin = that->m_pins[node_pin_id];
		if (this_pin->type() != that_pin->type())
			return false;
	}

	return true;
}

Status Node::generate() noexcept
{
	// TODO: has dynamic io?
	m_code.clear();
	if (auto err = this->gen_code(); !err)
		return err;

	this->gen_hash();
	return Status::OK;
}

/* virtual */ void Node::create(Core* core, const NodeClass* node_class, size_t external_id, size_t node_id, size_t base_pin_id) noexcept
{
	m_external_id = external_id;
	m_node_class = node_class;

	m_pins.reserve(node_class->io().size());
	for (size_t i = 0; i < node_class->io().size(); ++i)
		m_pins.emplace_back(core->pins()[base_pin_id + i].get());

	m_name = Core::mangle_name(node_class->name());
	this->gen_pins_name(node_id);
}

}
