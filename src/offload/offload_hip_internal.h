/*----------------------------------------------------------------------------*/
/*  CP2K: A general program to perform molecular dynamics simulations         */
/*  Copyright 2000-2022 CP2K developers group <https://cp2k.org>              */
/*                                                                            */
/*  SPDX-License-Identifier: BSD-3-Clause                                     */
/*----------------------------------------------------------------------------*/

#ifndef OFFLOAD_HIP_INTERNAL_H
#define OFFLOAD_HIP_INTERNAL_H
#include <hip/hip_runtime_api.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef hipStream_t offloadStream_t;
typedef hipEvent_t offloadEvent_t;

/*******************************************************************************
 * \brief Check given Hip status and upon failure abort with a nice message.
 * \author Ole Schuett
 ******************************************************************************/
#define OFFLOAD_CHECK(status)                                                  \
  if (status != hipSuccess) {                                                  \
    fprintf(stderr, "ERROR: %s %s %d\n", hipGetErrorString(status), __FILE__,  \
            __LINE__);                                                         \
    abort();                                                                   \
  }

static inline void offloadMemsetAsync(void *ptr_device__, int val__,
                                      size_t size__, offloadStream_t stream__) {
  OFFLOAD_CHECK(hipMemsetAsync(ptr_device__, val__, size__, stream__));
}

static inline void offloadMemcpyAsyncHtoD(void *ptr_device__,
                                          const void *ptr_host__,
                                          const size_t size__,
                                          offloadStream_t stream__) {
  OFFLOAD_CHECK(hipMemcpyAsync(ptr_device__, ptr_host__, size__,
                               hipMemcpyHostToDevice, stream__));
}

static inline void offloadMemcpyAsyncDtoH(void *ptr_host__,
                                          const void *ptr_device__,
                                          const size_t size__,
                                          offloadStream_t stream__) {
  OFFLOAD_CHECK(hipMemcpyAsync(ptr_host__, ptr_device__, size__,
                               hipMemcpyDeviceToHost, stream__));
}

static inline void offloadMemcpyHtoD(void *ptr_device__, const void *ptr_host__,
                                     const size_t size__) {
  OFFLOAD_CHECK(
      hipMemcpy(ptr_device__, ptr_host__, size__, hipMemcpyHostToDevice));
}

static inline void offloadMemcpyDtoH(void *ptr_host__, const void *ptr_device__,
                                     const size_t size__) {
  OFFLOAD_CHECK(
      hipMemcpy(ptr_host__, ptr_device__, size__, hipMemcpyDeviceToHost));
}

static inline void offloadEventCreate(offloadEvent_t *event__) {
  OFFLOAD_CHECK(hipEventCreate(event__));
}

static inline void offloadEventDestroy(offloadEvent_t event__) {
  OFFLOAD_CHECK(hipEventDestroy(event__));
}

static inline void offloadStreamCreate(offloadStream_t *stream__) {
  OFFLOAD_CHECK(hipStreamCreate(stream__));
}

static inline void offloadStreamDestroy(offloadStream_t stream__) {
  OFFLOAD_CHECK(hipStreamDestroy(stream__));
}

static inline void offloadEventSynchronize(offloadEvent_t event__) {
  OFFLOAD_CHECK(hipEventSynchronize(event__));
}

static inline void offloadStreamSynchronize(offloadStream_t stream__) {
  OFFLOAD_CHECK(hipStreamSynchronize(stream__));
}

static inline void offloadEventRecord(offloadEvent_t event__,
                                      offloadStream_t stream__) {
  OFFLOAD_CHECK(hipEventRecord(event__, stream__));
}

static inline void offloadMalloc(void **ptr__, size_t size__) {
  OFFLOAD_CHECK(hipMalloc(ptr__, size__));
}

static inline void offloadFree(void *ptr__) { OFFLOAD_CHECK(hipFree(ptr__)); }

static inline void offloadStreamWaitEvent(offloadStream_t stream__,
                                          offloadEvent_t event__,
                                          const int val__) {
  OFFLOAD_CHECK(hipStreamWaitEvent(stream__, event__, val__));
}

static inline void offloadDeviceSynchronize() {
  OFFLOAD_CHECK(hipDeviceSynchronize());
}

static inline void offloadMemset(void *ptr__, const int val__, size_t size__) {
  OFFLOAD_CHECK(hipMemset(ptr__, val__, size__));
}

static inline void offloadMallocHost(void **ptr__, size_t size__) {
  OFFLOAD_CHECK(hipHostMalloc(ptr__, size__, hipHostMallocDefault));
}
static inline void offloadFreeHost(void *ptr__) {
  OFFLOAD_CHECK(hipHostFree(ptr__));
}

#ifdef __cplusplus
}
#endif

#endif
