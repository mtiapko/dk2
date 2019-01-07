#ifndef __DK_APPLICATION_H__
#define __DK_APPLICATION_H__

#include "status.h"

namespace dk
{

class application
{
public:
	virtual ~application() noexcept = default;

	virtual void update(float dt) noexcept = 0;
	virtual void render() noexcept = 0;

	virtual status create() noexcept = 0;
	virtual void destroy() noexcept = 0;
};

}

#endif  //  !__DK_APPLICATION_H__
