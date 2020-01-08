#include "dk/ImGui/Manager.h"
#include "dk/ImGui/imgui_impl_opengl3.h"
#include "dk/sys/EventManager.h"
#include "dk/sys/Keyboard.h"
#include "dk/Log.h"

namespace dk::ImGui
{

/* static */ Manager Manager::s_this;

/* static */ int Manager::convert_mouse_btn(sys::MouseBtn btn) noexcept
{
	switch (btn) {
		case sys::MouseBtn::LEFT: return 0;
		case sys::MouseBtn::RIGHT: return 1;
		case sys::MouseBtn::MIDDLE: return 2;
		default:
			DK_LOG_ERROR("Unknown mouse button: #", (int)btn);
			return -1;
	}
}

void Manager::handle(const sys::MouseMoveEvent& e) noexcept /* override */
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2((float)e.x(), (float)e.y());
}

void Manager::handle(const sys::MousePressEvent& e) noexcept /* override */
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

void Manager::handle(const sys::KeyPressEvent& e) noexcept /* override */
{
	auto& io = ImGui::GetIO();
	auto alt_pressed = sys::Keyboard::state(sys::KeyboardBtn::LEFT_ALT) || sys::Keyboard::state(sys::KeyboardBtn::RIGHT_ALT);
	auto ctrl_pressed = sys::Keyboard::state(sys::KeyboardBtn::LEFT_CTRL) || sys::Keyboard::state(sys::KeyboardBtn::RIGHT_CTRL);
	auto shift_enabled = sys::Keyboard::is_shift_pressed();

	io.KeyShift = shift_enabled;
	io.KeyCtrl = ctrl_pressed;
	io.KeyAlt = alt_pressed;

	if (!alt_pressed && !ctrl_pressed && sys::Keyboard::is_printable(e.btn())) {
		char c = sys::Keyboard::to_ASCII(e.btn());
		auto caps_enabled = sys::Keyboard::caps_lock_state();
		if ((caps_enabled && !shift_enabled) || (!caps_enabled && shift_enabled))
			c = sys::Keyboard::to_upper_ASCII(c);

		io.AddInputCharacter(c);
	}

	io.KeysDown[(int)e.btn()] = true;
}

void Manager::handle(const sys::KeyReleaseEvent& e) noexcept /* override */
{
	auto& io = ImGui::GetIO();
	io.KeysDown[(int)e.btn()] = false;
	io.KeyShift = sys::Keyboard::is_shift_pressed();
}

/* static */ Status Manager::create() noexcept
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = "res/imgui.ini";
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.Fonts->AddFontFromFileTTF("res/font/Proggy/ProggyVector Regular.ttf", 14.0f);
	io.DisplaySize = ImVec2((float)1920, (float)1080);
	io.BackendPlatformName = "DK";

	io.KeyMap[ImGuiKey_Tab]        = (int)sys::KeyboardBtn::TAB;
	io.KeyMap[ImGuiKey_LeftArrow]  = (int)sys::KeyboardBtn::LEFT_ARROW;
	io.KeyMap[ImGuiKey_RightArrow] = (int)sys::KeyboardBtn::RIGHT_ARROW;
	io.KeyMap[ImGuiKey_UpArrow]    = (int)sys::KeyboardBtn::UP_ARROW;
	io.KeyMap[ImGuiKey_DownArrow]  = (int)sys::KeyboardBtn::DOWN_ARROW;
	io.KeyMap[ImGuiKey_PageUp]     = (int)sys::KeyboardBtn::PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown]   = (int)sys::KeyboardBtn::PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home]       = (int)sys::KeyboardBtn::HOME;
	io.KeyMap[ImGuiKey_End]        = (int)sys::KeyboardBtn::END;
	io.KeyMap[ImGuiKey_Delete]     = (int)sys::KeyboardBtn::DELETE;
	io.KeyMap[ImGuiKey_Backspace]  = (int)sys::KeyboardBtn::BACK_SPACE;
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
	sys::EventManager<sys::KeyPressEvent>::get().subscribe(&s_this);
	sys::EventManager<sys::KeyReleaseEvent>::get().subscribe(&s_this);

	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	DK_LOG_OK("ImGui created");
	return Status::OK;
}

/* static */ void Manager::update() noexcept
{
	ImGui_ImplOpenGL3_NewFrame();  //  TODO: rewrite
	ImGui::NewFrame();
}

/* static */ void Manager::render() noexcept
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	auto& io = ImGui::GetIO();
	io.MouseDown[convert_mouse_btn(sys::MouseBtn::LEFT)] = sys::Mouse::state(sys::MouseBtn::LEFT);
	io.MouseDown[convert_mouse_btn(sys::MouseBtn::MIDDLE)] = sys::Mouse::state(sys::MouseBtn::MIDDLE);
	io.MouseDown[convert_mouse_btn(sys::MouseBtn::RIGHT)] = sys::Mouse::state(sys::MouseBtn::RIGHT);
}

}
