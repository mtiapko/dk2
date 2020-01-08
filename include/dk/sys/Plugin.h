#ifndef __DK_SYS_PLUGIN_H__
#define __DK_SYS_PLUGIN_H__

#include "dk/containers/StringView.h"
#include "dk/Status.h"

namespace dk::sys
{

class Plugin
{
public:
	virtual ~Plugin() noexcept = default;

	virtual StringView name() const noexcept = 0;

	virtual Status create() noexcept = 0;
	virtual void destroy() noexcept = 0;
};

}

#endif // !__DK_SYS_PLUGIN_H__
