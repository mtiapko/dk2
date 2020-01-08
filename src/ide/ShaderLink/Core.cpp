#include <set> // TODO: remove
#include <unordered_set> // TODO: remove
#include "dk/ide/ShaderLink/Core.h"
#include "dk/Assert.h"
#include "dk/Core.h"

namespace ed = ax::NodeEditor;

namespace dk::ide::ShaderLink
{

void Core::new_node(size_t node_class_id) noexcept
{
	const size_t pin_base_id = m_pins.size();
	const auto& node_class = s_node_classes[node_class_id];

	const size_t node_id = m_nodes.size();
	const size_t node_external_id = ++m_external_id;
	auto node = m_nodes.emplace_back(node_class->new_node()).get();
	m_node_map.emplace(node_external_id, node);

	const auto& io = node_class->io();
	for (size_t i = 0; i < io.size(); ++i) {
		auto pin = m_pins.emplace_back(dk_mem_new(Pin, ++m_external_id, node, i, io[i].type)).get();
		m_pin_map.emplace(m_external_id, pin);
	}

	node->create(this, node_class, node_external_id, node_id, pin_base_id);
	ed::SetNodePosition(node_external_id, m_next_node_pos);

	if (node_class->is_output_node())
		m_output_node= node;

	DK_LOG_OK("Node '", s_node_classes[node_class_id]->name(), "' added");
	if (m_new_link_beg_pin != nullptr) {
		size_t from_node_pin_id;
		size_t to_node_pin_id;
		if (m_new_link_beg_pin->is_input()) {
			from_node_pin_id = node_class->inputs_count();
			to_node_pin_id = node_class->io().size();
		} else {
			from_node_pin_id = 0;
			to_node_pin_id = node_class->inputs_count();
		}

		for (size_t node_pin_id = from_node_pin_id; node_pin_id != to_node_pin_id; ++node_pin_id) {
			auto pin = node->pins()[node_pin_id];
			if (this->is_valid_link(m_new_link_beg_pin, pin)) {
				this->new_link(m_new_link_beg_pin, pin);
				break;
			}
		}

		m_new_link_beg_pin = nullptr;
	}

	m_is_running = (this->generate() == Status::OK); // TODO: remove or rewrite
}

void Core::new_link(Pin* beg_pin, Pin* end_pin) noexcept
{
	// TODO: rewrite as double call to function
	if ((NodeIO::is_dynamic_type(beg_pin->type()) && !NodeIO::is_dynamic_type(end_pin->type())) ||
			(beg_pin->type() == NodeIOType::DYNAMIC && end_pin->type() != NodeIOType::DYNAMIC)) {
		this->apply_type(beg_pin, end_pin->type());
	} else if ((NodeIO::is_dynamic_type(end_pin->type()) && !NodeIO::is_dynamic_type(beg_pin->type())) ||
			(end_pin->type() == NodeIOType::DYNAMIC && beg_pin->type() != NodeIOType::DYNAMIC)) {
		this->apply_type(end_pin, beg_pin->type());
	}

	const size_t link_external_id = ++m_link_external_id;
	auto link = m_links.emplace_back(dk_mem_new(Link, link_external_id, beg_pin, end_pin)).get();
	m_link_map.emplace(link_external_id, link);

	auto input_pin = (beg_pin->is_input() ? beg_pin : end_pin);
	if (input_pin->is_connected())
		this->delete_link(input_pin->links()[0]); /* input can have only 1 link  */

	beg_pin->add_link(link);
	end_pin->add_link(link);

	DK_LOG_OK("New link added");
	m_is_running = (this->generate() == Status::OK); // TODO: remove or rewrite
}

void Core::delete_node(Node* node) noexcept
{
	/* all links will be automatically deleted by ed::QueryDeletedLink() */
	if (node->node_class()->is_output_node())
		m_output_node = nullptr;

	auto pin = std::find_if(m_pins.cbegin(), m_pins.cend(), [pin = node->pins()[0]](const auto& p) noexcept
		{ return (pin == p.get()); });
	DK_ASSERT(pin != m_pins.cend());

	m_pins.erase(pin, pin + node->pins().size());
	std::erase_if(m_nodes, [node](const auto& n) noexcept { return (node == n.get()); });

	DK_LOG_OK("Node deleted, pins count: ", m_pins.size());
}

void Core::delete_link(Link* link) noexcept
{
	auto beg_pin = link->beg_pin();
	beg_pin->remove_link(link);

	auto end_pin = link->end_pin();
	end_pin->remove_link(link);

	std::erase_if(m_links, [link](const auto& l) noexcept { return (link == l.get()); });

	DK_LOG_OK("Link deleted: ", m_links.size(), " && ", beg_pin->links().size(), " || ", end_pin->links().size());
}

void Core::draw_nodes_palette() noexcept
{
	ImGui::PushItemWidth(-1);

	decltype(ImGuiTextFilter::InputBuf) tmp = {};
	bool is_search_active = ImGui::InputTextWithHint("##search", "Search", tmp, IM_ARRAYSIZE(tmp));
	ImGui::Dummy(ImVec2(100, 0)); /* to prevent small window */

	// TODO: make class member
	static ImGuiTextFilter search;
	if (is_search_active) {
		strcpy(search.InputBuf, tmp);
		search.Build();
	}

	ImGui::PopItemWidth();
	size_t search_res_count = 0;
	for (size_t node_class_id = 0; node_class_id < s_node_classes.size(); ++node_class_id) {
		const auto op = s_node_classes[node_class_id];
		if (!search.PassFilter(op->name().data()))
			continue;

		++search_res_count;
		if (ImGui::Selectable(op->name().data())) {
			this->new_node(node_class_id);
		} else {
			if (ImGui::BeginDragDropSource()) {
				ImGui::Text("%s", op->name().data());
				ImGui::SetDragDropPayload("node_class_id", &node_class_id, sizeof(node_class_id));
				ImGui::EndDragDropSource();
			}
		}
	}

	if (search_res_count == 0) {
		ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)ImColor(128, 128, 128, 255));
		ImGui::Text("Node not found");
		ImGui::PopStyleColor();
	}

	if (!is_search_active && !ImGui::IsMouseDown(0))
		search.Clear();
}

void Core::draw_nodes() noexcept
{
	for (size_t node_id = 0; node_id < m_nodes.size(); ++node_id) {
		const auto& node = m_nodes[node_id];
		node->draw();
	}
}

void Core::draw_links() noexcept
{
	for (size_t link_id = 0; link_id < m_links.size(); ++link_id) {
		auto link = m_links[link_id].get();
		size_t beg_pin_external_id = link->beg_pin()->external_id();
		size_t end_pin_external_id = link->end_pin()->external_id();
		ed::Link(link->external_id(), beg_pin_external_id, end_pin_external_id);
	}
}

/* static */ bool Core::validate_link(const Pin* beg_pin, const Pin* end_pin) noexcept
{
	// TODO: rewrite
	if ((NodeIO::is_vec_type(beg_pin->type()) || NodeIO::is_mat_type(beg_pin->type()))
			&& (NodeIO::is_vec_type(end_pin->type()) || NodeIO::is_mat_type(end_pin->type())))
		return true;

	return
		(beg_pin->type() == NodeIOType::DYNAMIC     && end_pin->type() != NodeIOType::TEX_2D) ||
		(beg_pin->type() == NodeIOType::DYNAMIC_VEC && NodeIO::is_vec_type(end_pin->type()))  ||
		(beg_pin->type() == NodeIOType::DYNAMIC_MAT && NodeIO::is_mat_type(end_pin->type()));
}

bool Core::is_valid_link(const Pin* beg_pin, const Pin* end_pin) const noexcept
{
	// TODO: if input -> only 1 link
	// TODO: if already not linked
	// TODO: if input and output (not input x2 or output x2)
	if (beg_pin->type() == end_pin->type())
		return true;

	if (validate_link(beg_pin, end_pin))
		return true;

	return validate_link(end_pin, beg_pin);
}

void Core::apply_type(Pin* pin, NodeIOType type) noexcept
{
	pin->set_type(type);

	auto node = pin->node();
	for (auto node_pin: node->pins()) {
		if (NodeIO::is_dynamic_type(node_pin->type()))
			this->apply_type(node_pin, type);
	}

	for (auto link: pin->links()) {
		auto end_pin = (link->beg_pin() != pin ? link->beg_pin() : link->end_pin());
		if (end_pin->type() != type && NodeIO::is_dynamic_type(end_pin->type()))
			this->apply_type(end_pin, type);
	}
}

// TODO: remove
namespace
{
	auto hash_lamb = [](auto node) noexcept { return node->hash(); };
	auto cmp_lamb = [](auto lnode, auto rnode) noexcept { return lnode->cmp(rnode); };
	std::unordered_set<
		const Node*,
		decltype(hash_lamb),
		decltype(cmp_lamb)
	> generated_nodes(16, hash_lamb, cmp_lamb);

	std::set<const Node*> visited_nodes;
}

// TODO: rewrite
void convert_pin(String& args, StringView arg_name, const Pin* in_pin, const Pin* out_pin) noexcept
{
	if (in_pin->type() < out_pin->type()) {
		args += arg_name;
		switch (in_pin->type()) {
			case NodeIOType::VEC1: args += ".x";   break;
			case NodeIOType::VEC2: args += ".xy";  break;
			case NodeIOType::VEC3: args += ".xyz"; break;
			default: DK_ASSERT(false, "Unsupported type");
		}
	} else {
		switch (in_pin->type()) {
			case NodeIOType::VEC2: args += "vec2("; break;
			case NodeIOType::VEC3: args += "vec3("; break;
			case NodeIOType::VEC4: args += "vec4("; break;
			default: DK_ASSERT(false, "Unsupported type");
		}

		args += arg_name;
		if (out_pin->type() != NodeIOType::VEC1) {
			for (int diff = (int)in_pin->type() - (int)out_pin->type(); diff --> 0;) {
				if (in_pin->type() == NodeIOType::VEC4 && diff == 0) args += ", 1.0";
				else args += ", 0.0";
			}
		}

		args += ')';
	}
}

Status Core::parse(Node* node, String& uniforms, String& funcs, String& main_func) const noexcept
{
	auto [it, is_inserted] = visited_nodes.emplace(node);
	if (!is_inserted)
		return Status::OK;

	// TODO: generate only if dirty!!!
	DK_LOG_OK("Parse: ", node->name());
	if (auto err = node->generate(); !err)
		return err;

	const auto& node_class = node->node_class();
	if (node_class->is_input_node() && !node_class->is_unique_input_node()) {
		uniforms += node->code();
	} else {
		if (node_class->is_output_node()) {
			uniforms += "out ";
			uniforms += NodeIO::get_type_name(node->pins()[node_class->inputs_count()]->type());
			uniforms += node->pins_name()[node_class->inputs_count()];
			uniforms += ";\n";
		}

		auto [it, is_inserted] = generated_nodes.emplace(node);
		if (is_inserted) {
			if (node_class->is_unique_input_node()) uniforms += node->code();
			else funcs += node->code();
		}
	}

	if (node_class->is_input_node())
		return Status::OK;

	String args;
	for (size_t node_pin_id = 0; node_pin_id < node_class->inputs_count(); ++node_pin_id) {
		auto beg_pin = node->pins()[node_pin_id];
		if (!beg_pin->is_connected()) {
			DK_LOG_ERROR("Pin does not connected");
			return Status::ERROR;
		}

		auto link = beg_pin->links()[0]; /* input can have only 1 link */
		auto end_pin = (link->beg_pin() != beg_pin ? link->beg_pin() : link->end_pin());
		auto end_node = end_pin->node();
		if (auto err = this->parse(end_node, uniforms, funcs, main_func); !err)
			return err;

		if (node_pin_id != 0)
			args += ", ";

		const auto& arg_name = end_node->pins_name()[end_pin->node_pin_id()];
		if (beg_pin->type() == end_pin->type()) args += arg_name;
		else convert_pin(args, arg_name, beg_pin, end_pin);
	}


	String call;
	call = '\t';
	call += node->name();
	call += '(';
	call += args;

	String decl;
	for (size_t io_id = node_class->inputs_count(); io_id < node_class->io().size(); ++io_id) {
		if (!node_class->is_output_node()) {
			decl += '\t';
			decl += NodeIO::get_type_name(node->pins()[io_id]->type());
			decl += node->pins_name()[io_id];
			decl += ";\n";
		}

		if (io_id != 0)
			call += ", ";

		call += node->pins_name()[io_id];
	}

	call += ");\n";
	if (!decl.empty()) {
		main_func += '\n';
		main_func += decl;
	}

	main_func += call;
	return Status::OK;
}

Status Core::generate() noexcept
{
	if (m_output_node == nullptr) {
		DK_LOG_ERROR("No output node");
		return Status::ERROR;
	}

	String uniforms = R"(
#version 330 core

in vec3 norm;
in vec2 uv;
in vec3 world_space_pos;

const vec3 light_dir = normalize(vec3(0, 1, 5));

)";

	String funcs;
	String main_func("\nvoid main() {");

	// TODO: remove
	generated_nodes.clear();
	visited_nodes.clear();
	if (auto err = this->parse(m_output_node, uniforms, funcs, main_func); !err)
		return err;

	main_func += "}\n";

	String shader_src;
	shader_src.reserve(uniforms.size() + funcs.size() + main_func.size());
	shader_src += uniforms;
	shader_src += funcs;
	shader_src += main_func;

	DK_LOG_OK("Shader source:\n", shader_src);
	auto shader_data = m_shader->resource_data();
	shader_data->sub_shaders[1]->resource_data()->source = std::move(shader_src);
	if (auto err = shader_data->sub_shaders[1]->create(); !err)
		return err;

	if (auto err = m_shader->create(); !err)
		return err;

	return Status::OK;
}

// TODO: remove
void Core::handle(const sys::KeyPressEvent&e ) noexcept
{
	if (e.btn() == sys::KeyboardBtn::TAB) {
		if (this->generate()) {
			DK_LOG_OK("Shader generated");
			m_is_running = true;
		}
	}
}

/* static */ String Core::convert_name(StringView name) noexcept
{
	String res;
	for (auto c: name) {
		if (std::isalnum(c) || c == '_')
			res.push_back(c);
		// TODO: remove
		//if (std::isspace(c))
		//	res.push_back('_');
	}

	return res;
}

/* static */ String Core::mangle_name(StringView name) noexcept
{
	static constexpr StringView dk_prefix = "DK_";

	String res;
	res.reserve(dk_prefix.size() + name.size());
	res = dk_prefix;
	res += convert_name(name);
	return res;
}

void Core::render() noexcept
{
	ed::Begin("ShaderLink");
	bool open_popup = ed::ShowBackgroundContextMenu();

	if (ImGui::BeginDragDropTarget()) {
		auto payload = ImGui::AcceptDragDropPayload("node_class_id", ImGuiDragDropFlags_AcceptNoDrawDefaultRect);
		if (payload != nullptr) {
			auto node_class_id = (const size_t*)payload->Data;
			m_next_node_pos = ImGui::GetMousePos();
			this->new_node(*node_class_id);
		}

		ImGui::EndDragDropTarget();
	}

	this->draw_nodes();
	this->draw_links();

	if (ed::BeginCreate()) {
		ed::PinId new_pin_external_id = 0;
		if (ed::QueryNewNode(&new_pin_external_id)) {
			if (ed::AcceptNewItem()) {
				auto pin_it = m_pin_map.find(new_pin_external_id.Get());
				DK_ASSERT(pin_it != m_pin_map.end());

				m_new_link_beg_pin = pin_it->second;
				open_popup = true;
			} else {
				ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)ImColor(128, 225, 128, 255));
				ImGui::PushStyleColor(ImGuiCol_PopupBg, (ImU32)ImColor(16, 32, 16, 255));
				ImGui::BeginTooltip();
				ImGui::Text("+ Create node");
				ImGui::EndTooltip();
				ImGui::PopStyleColor(2);
			}
		}

		ed::PinId beg_pin_external_id = 0;
		ed::PinId end_pin_external_id = 0;
		if (ed::QueryNewLink(&beg_pin_external_id, &end_pin_external_id)) {
			auto beg_it = m_pin_map.find(beg_pin_external_id.Get());
			DK_ASSERT(beg_it != m_pin_map.end());

			auto end_it = m_pin_map.find(end_pin_external_id.Get());
			DK_ASSERT(end_it != m_pin_map.end());

			auto beg_pin = beg_it->second;
			auto end_pin = end_it->second;
			if (this->is_valid_link(beg_pin, end_pin)) {
				if (ed::AcceptNewItem(ImColor(128, 196, 128, 255), 3.0f)) {
					this->new_link(beg_pin, end_pin);
				}
			} else {
				ed::RejectNewItem(ImColor(196, 128, 128, 255), 2.0f);
				ImGui::PushStyleColor(ImGuiCol_Text, (ImU32)ImColor(225, 128, 128, 255));
				ImGui::PushStyleColor(ImGuiCol_PopupBg, (ImU32)ImColor(32, 16, 16, 255));
				ImGui::BeginTooltip();
				ImGui::Text("x Invalid link");
				ImGui::EndTooltip();
				ImGui::PopStyleColor(2);
			}
		}
	}

	ed::EndCreate();
	if (ed::BeginDelete()) {
		ed::NodeId del_node_external_id = 0;
		while (ed::QueryDeletedNode(&del_node_external_id)) {
			if (ed::AcceptDeletedItem()) {
				auto node_it = m_node_map.find(del_node_external_id.Get());
				DK_ASSERT(node_it != m_node_map.end());

				this->delete_node(node_it->second);
			} else {
				DK_ASSERT(false, "Is this now possible?");
			}
		}

		ed::LinkId del_link_external_id = 0;
		while (ed::QueryDeletedLink(&del_link_external_id)) {
			if (ed::AcceptDeletedItem()) {
				auto link_it = m_link_map.find(del_link_external_id.Get());
				DK_ASSERT(link_it != m_link_map.end());

				this->delete_link(link_it->second);
			} else {
				DK_ASSERT(false, "Is this now possible?");
			}
		}
	}

	ed::EndDelete();
	if (ed::BeginShortcut()) {
		if (ed::AcceptCreateNode())
			open_popup = true;
	}

	ed::EndShortcut();

	if (open_popup)
		m_next_node_pos = ImGui::GetMousePos();

	ed::End();
	if (open_popup)
		ImGui::OpenPopup("nodes palette");

	if (ImGui::BeginPopup("nodes palette")) {
		this->draw_nodes_palette();
		ImGui::EndPopup();
	}

	if (m_is_running) {
		m_shader->enable();
		for (size_t node_id = 0; node_id < m_nodes.size(); ++node_id) {
			auto& node = m_nodes[node_id];
			const auto& node_class = node->node_class();
			if (!node_class->is_input_node())
				continue;

			node->update_shader_args(this);
		}
	}
}

Status Core::create() noexcept
{
	ed::Config cfg;
	cfg.SettingsFile = nullptr; // TODO: "res/ShaderLink.json";
	m_context = ed::CreateEditor(&cfg);
	ed::SetCurrentEditor(m_context);

	m_shader = dk::Core::get().active<graph::Renderer>()->default_shader(); // TODO: new_resource<graph::Shader>();
	if (m_shader == nullptr)
		return Status::ERROR;

	sys::EventManager<sys::KeyPressEvent>::get().subscribe(this);
	return Status::OK;
}

}
