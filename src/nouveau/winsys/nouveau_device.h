#ifndef NOUVEAU_DEVICE
#define NOUVEAU_DEVICE 1

#include "nouveau_private.h"
#include "nv_device_info.h"
#include "util/simple_mtx.h"
#include "util/vma.h"

#include <stddef.h>

struct _drmDevice;
struct hash_table;

#ifdef __cplusplus
extern "C" {
#endif


enum nvk_debug {
   /* dumps all push buffers after submission */
   NVK_DEBUG_PUSH_DUMP = 1ull << 0,

   /* push buffer submissions wait on completion
    *
    * This is useful to find the submission killing the GPU context. For easier debugging it also
    * dumps the buffer leading to that.
    */
   NVK_DEBUG_PUSH_SYNC = 1ull << 1,

   /* Zero all client memory allocations
    */
   NVK_DEBUG_ZERO_MEMORY = 1ull << 2,

   /* Dump VM bind/unbinds
    */
   NVK_DEBUG_VM = 1ull << 3,
};

struct nouveau_ws_device {
   int fd;

   struct nv_device_info info;

   uint32_t local_mem_domain;

   enum nvk_debug debug_flags;

   simple_mtx_t bos_lock;
   struct hash_table *bos;

   bool has_vm_bind;
   struct util_vma_heap vma_heap;
   simple_mtx_t vma_mutex;
};

struct nouveau_ws_device *nouveau_ws_device_new(struct _drmDevice *drm_device);
void nouveau_ws_device_destroy(struct nouveau_ws_device *);

#ifdef __cplusplus
}
#endif

#endif
