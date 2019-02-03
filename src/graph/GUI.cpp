#include "sys/Keyboard.h"
#include "sys/EventManager.h"
#include "graph/imgui/imgui.h"
#include "graph/imgui/imgui_impl_opengl3.h"
#include "graph/GUI.h"
#include "Log.h"

namespace dk::graph
{

/* static */ GUI GUI::s_this;

/* static */ int GUI::convert_mouse_btn(sys::MouseBtn btn) noexcept
{
	switch (btn) {
		case sys::MouseBtn::LEFT: return 0;
		case sys::MouseBtn::RIGHT: return 1;
		case sys::MouseBtn::MIDDLE: return 2;
		default: return -1;
	}
}

/* static */ void GUI::update() noexcept
{
	ImGui_ImplOpenGL3_NewFrame();  //  TODO: rewrite
	ImGui::NewFrame();
}

/* static */ void GUI::render() noexcept
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::handle(const sys::MouseMoveEvent& e) noexcept /* override */
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)e.x(), (float)e.y());
}

void GUI::handle(const sys::MousePressEvent& e) noexcept /* override */
{
	if (e.btn() == sys::MouseBtn::SCROLL_UP) {
		ImGui::GetIO().MouseWheel += 1.0f;
	} else if (e.btn() == sys::MouseBtn::SCROLL_DOWN) {
		ImGui::GetIO().MouseWheel -= 1.0f;
	} else {
		int btn = convert_mouse_btn(e.btn());
		if (btn != -1)
			ImGui::GetIO().MouseDown[btn] = true;
	}
}

void GUI::handle(const sys::MouseReleaseEvent& e) noexcept /* override */
{
	int btn = convert_mouse_btn(e.btn());
	if (btn != -1)
		ImGui::GetIO().MouseDown[btn] = false;
}

void GUI::handle(const sys::KeyPressEvent& e) noexcept /* override */
{
	auto& io = ImGui::GetIO();
	if (sys::Keyboard::is_printable(e.btn())) {
		char c = sys::Keyboard::to_ASCII(e.btn());
		auto caps_enabled = sys::Keyboard::caps_lock_state();
		auto shift_enabled = sys::Keyboard::state(sys::KeyboardBtn::LEFT_SHIFT) || sys::Keyboard::state(sys::KeyboardBtn::RIGHT_SHIFT);
		if ((caps_enabled && !shift_enabled) || (!caps_enabled && shift_enabled))
			c = sys::Keyboard::to_upper_ASCII(c);

		io.AddInputCharacter(c);
	}

	io.KeysDown[(int)e.btn()] = true;
}

void GUI::handle(const sys::KeyReleaseEvent& e) noexcept /* override */
{
	ImGui::GetIO().KeysDown[(int)e.btn()] = false;
}

/* static */ Status GUI::create() noexcept
{

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/fonts/ProggyVector Regular.ttf", 16.0f);

	ImGui::StyleColorsDark();
	io.DisplaySize = ImVec2((float)800, (float)600);
	io.BackendPlatformName ="DK";

	io.KeyMap[ImGuiKey_Tab]        = (int)sys::KeyboardBtn::TAB;
	io.KeyMap[ImGuiKey_LeftArrow]  = (int)sys::KeyboardBtn::LEFT_ARROW;
	io.KeyMap[ImGuiKey_RightArrow] = (int)sys::KeyboardBtn::RIGHT_ARROW;
	io.KeyMap[ImGuiKey_UpArrow]    = (int)sys::KeyboardBtn::UP_ARROW;
	io.KeyMap[ImGuiKey_DownArrow]  = (int)sys::KeyboardBtn::DOWN_ARROW;
	//io.KeyMap[ImGuiKey_PageUp]     = (int)sys::KeyboardBtn::;
	//io.KeyMap[ImGuiKey_PageDown]   = (int)sys::KeyboardBtn::;
	//io.KeyMap[ImGuiKey_Home]       = (int)sys::KeyboardBtn::;
	//io.KeyMap[ImGuiKey_End]        = (int)sys::KeyboardBtn::;
	//io.KeyMap[ImGuiKey_Insert]     = (int)sys::KeyboardBtn::;
	io.KeyMap[ImGuiKey_Delete]     = (int)sys::KeyboardBtn::DELETE;
	//io.KeyMap[ImGuiKey_Backspace]  = (int)sys::KeyboardBtn::;
	io.KeyMap[ImGuiKey_Space]      = (int)sys::KeyboardBtn::SPACE;
	io.KeyMap[ImGuiKey_Enter]      = (int)sys::KeyboardBtn::ENTER;
	io.KeyMap[ImGuiKey_Escape]     = (int)sys::KeyboardBtn::ESCAPE;
	io.KeyMap[ImGuiKey_A]          = (int)sys::KeyboardBtn::A;
	io.KeyMap[ImGuiKey_C]          = (int)sys::KeyboardBtn::C;
	io.KeyMap[ImGuiKey_V]          = (int)sys::KeyboardBtn::V;
	io.KeyMap[ImGuiKey_X]          = (int)sys::KeyboardBtn::X;
	io.KeyMap[ImGuiKey_Y]          = (int)sys::KeyboardBtn::Y;
	io.KeyMap[ImGuiKey_Z]          = (int)sys::KeyboardBtn::Z;

	sys::EventManager<sys::MouseMoveEvent>::get().subscribe(&s_this);
	sys::EventManager<sys::MousePressEvent>::get().subscribe(&s_this);
	sys::EventManager<sys::MouseReleaseEvent>::get().subscribe(&s_this);
	sys::EventManager<sys::KeyPressEvent>::get().subscribe(&s_this);
	sys::EventManager<sys::KeyReleaseEvent>::get().subscribe(&s_this);

	ImGui_ImplOpenGL3_Init();
	DK_LOG_OK("GUI created");
	return Status::OK;
}

}
