#ifndef __DK_APPLICATION_H__
#define __DK_APPLICATION_H__

#include "ret_code.h"

namespace dk
{

class application
{
public:
	virtual void update() = 0;
	virtual void render() = 0;

	virtual ret_code create() = 0;
};

}

#endif  //  !__DK_APPLICATION_H__
