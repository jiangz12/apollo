/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef CYBERTRON_CROUTINE_ROUTINE_CONTEXT_H_
#define CYBERTRON_CROUTINE_ROUTINE_CONTEXT_H_

#include <cstdlib>
#include <cstring>

#include "cybertron/common/log.h"

extern "C" {
extern void ctx_swap(void**, void**) asm("ctx_swap");
};

namespace apollo {
namespace cybertron {
namespace croutine {

static const int STACK_SIZE = 8 * 1024 * 1024;
static const int REGISTERS_SIZE = 56;

typedef void (*func)(void*);
struct RoutineContext {
  ~RoutineContext() { delete stack; }
  char* stack = nullptr;
  char* sp = nullptr;
};

void MakeContext(const func &f1, const void *arg, RoutineContext *ctx);

inline void SwapContext(RoutineContext* src_ctx, RoutineContext* dst_ctx) {
  ctx_swap(reinterpret_cast<void**>(&src_ctx->sp),
           reinterpret_cast<void**>(&dst_ctx->sp));
}

}  // namespace croutine
}  // namespace cybertron
}  // namespace apollo

#endif  // CYBERTRON_CROUTINE_ROUTINE_CONTEXT_H_
