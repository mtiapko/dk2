#ifndef __DK_APPLICATION_H__
#define __DK_APPLICATION_H__

#include "Status.h"

namespace dk
{

class Application
{
public:
	virtual ~Application() noexcept = default;

	virtual void update(float dt) noexcept = 0;
	virtual void render() noexcept = 0;

	virtual Status create() noexcept = 0;
	virtual void destroy() noexcept = 0;
};

}

#endif  //  !__DK_APPLICATION_H__
