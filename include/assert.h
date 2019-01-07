#ifndef __DK_ASSERT_H__
#define __DK_ASSERT_H__

#include <stdlib.h>
#include "log.h"

#define DK_ASSERT(expr, ...) \
	if (!(expr)) { \
		DK_LOG_PRINT(LIGHT_RED, "ASSERT!", __FILE__, __func__, __LINE__, \
			"Assertion failed: '", #expr, "'", ##__VA_ARGS__, '\n'); \
		std::exit(1); \
	}

#endif  //  !__DK_ASSERT_H__
