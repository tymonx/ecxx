/* Copyright 2018 Tymoteusz Blazejczyk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ECXX_ALLOCATOR_POOL_HPP
#define ECXX_ALLOCATOR_POOL_HPP

#include "ecxx/span.hpp"
#include "ecxx/allocator.hpp"

namespace ecxx {
namespace allocator {

class Pool final : public Allocator {
public:
    constexpr Pool() noexcept = default;

    Pool(void* memory, std::size_t size) noexcept;

    template<typename T>
    constexpr Pool(const Span<T>& memory) noexcept;

    Pool(Pool&& other) noexcept;

    Pool(const Pool& other) noexcept = delete;

    Pool& operator=(Pool&& other) noexcept;

    Pool& operator=(const Pool& other) noexcept = delete;

    auto allocate(std::size_t n) noexcept -> void* override;

    auto reallocate(void* ptr, std::size_t n) noexcept -> void* override;

    void deallocate(void* ptr) noexcept override;

    ~Pool() noexcept override;
private:
    void* m_header{nullptr};
    void* m_memory{nullptr};
    std::size_t m_size{0u};
};

inline
Pool::~Pool() noexcept = default;

template<typename T> inline constexpr
Pool::Pool(const Span<T>& memory) noexcept :
    Pool{memory.data(), memory.size_bytes()}
{ }

} /* namespace allocator */
} /* namespace ecxx */

#endif /* ECXX_ALLOCATOR_POOL_HPP */
