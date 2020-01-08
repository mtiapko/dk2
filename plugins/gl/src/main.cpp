#include "Plugin.h"

extern "C" sys::Plugin* dk_plugin_open()
{
	static gl::Plugin gl;
	return &gl;
}

extern "C" void dk_plugin_close()
{}
