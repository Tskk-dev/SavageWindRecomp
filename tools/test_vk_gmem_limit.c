// Compile twice with -DVK_GMEM_LIMIT_MB=0 and =2048.
#include <assert.h>
#include "../runtime/rt.h"
#include "../runtime/nvn/vulkan/vk.h"

int main(void) {
    uint64_t want = 3120ull << 20;
    if (want > VK_GMEM_IMPORT_LIMIT) want = VK_GMEM_IMPORT_LIMIT;
    if (VK_GMEM_LIMIT_MB == 2048) assert(want == (2048ull << 20));
    else assert(want == (3120ull << 20));
    assert(VK_GMEM_IMPORT_LIMIT <= HEAP_MAX);
    return 0;
}
