#ifndef __DK_ASSERT_H__
#define __DK_ASSERT_H__

#include <stdlib.h>
#include "dk/Log.h"

#define DK_ASSERT(expr, ...) \
	if (!(expr)) { \
		DK_LOG_TITLE(LIGHT_RED, "ASSERT!", __FILE__, __func__, __LINE__, \
			"Assertion failed: '", #expr, "'. ", ##__VA_ARGS__, '\n'); \
		std::terminate(); \
	}

#endif // !__DK_ASSERT_H__
