// Internal replacements for Abseil types/macros used by vendored RE2.
#pragma once

#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <mutex>
#include <string>
#include <unordered_map>

namespace re2 {

inline void AppendFormat(std::string* out, const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  va_list ap_copy;
  va_copy(ap_copy, ap);
  const int needed = std::vsnprintf(nullptr, 0, fmt, ap_copy);
  va_end(ap_copy);
  if (needed <= 0) {
    va_end(ap);
    return;
  }
  const size_t start = out->size();
  out->resize(start + static_cast<size_t>(needed));
  std::vsnprintf(out->data() + start, static_cast<size_t>(needed) + 1, fmt, ap);
  va_end(ap);
}

}  // namespace re2

#define RE2_ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))

#ifndef NDEBUG
#define RE2_DCHECK(cond) assert(cond)
#define RE2_DCHECK_EQ(a, b) assert((a) == (b))
#define RE2_DCHECK_GE(a, b) assert((a) >= (b))
#define RE2_DCHECK_LE(a, b) assert((a) <= (b))
#else
#define RE2_DCHECK(cond) ((void)0)
#define RE2_DCHECK_EQ(a, b) ((void)0)
#define RE2_DCHECK_GE(a, b) ((void)0)
#define RE2_DCHECK_LE(a, b) ((void)0)
#endif
