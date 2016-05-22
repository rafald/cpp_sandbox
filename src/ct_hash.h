#ifndef CT_HASH_H
#define CT_HASH_H

namespace foonathan {
namespace string_id {
namespace detail {
using hash_type = std::uint64_t;

constexpr hash_type fnv_basis = 14695981039346656037ull;
constexpr hash_type fnv_prime = 109951162821ull;

// FNV-1a 64 bit hash
constexpr hash_type sid_hash(const char *str,
                             hash_type hash = fnv_basis) noexcept {
  return *str ? sid_hash(str + 1, (hash ^ *str) * fnv_prime) : hash;
}
}
}
} // foonathan::string_id::detail

#endif
