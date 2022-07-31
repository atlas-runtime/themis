#undef CONFIG_BIGNUM
#undef CONFIG_ATOMICS
#undef USE_WORKER
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

size_t mspace_usable_size(const void *mem) {
    return 0;
}

size_t malloc_usable_size(void *p) {
    return 0;
}
