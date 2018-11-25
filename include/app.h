#ifndef __DK_APPLICATION_H__
#define __DK_APPLICATION_H__

#include "status.h"

namespace dk
{

class application
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual status create() = 0;
};

}

#endif  //  !__DK_APPLICATION_H__
