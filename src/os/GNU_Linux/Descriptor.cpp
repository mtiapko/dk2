#include "dk/os/Descriptor.h"
#include "dk/Assert.h"

namespace dk::os
{

/* static */ Status Descriptor::create() noexcept
{
	DK_ASSERT(s_display == nullptr, "Already created");

	s_display = XOpenDisplay(nullptr);
	if (s_display == nullptr) {
		DK_LOG_ERROR("Failed to connection to X server");
		return Status::ERROR;
	}

	return Status::OK;
}

}
