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

#include "ecxx/allocator/pool.hpp"

#include <algorithm>

using ecxx::allocator::Pool;

struct Header {
    void* prev;
    void* next;
    std::size_t size;
};

static constexpr std::uintptr_t HEADER_ALIGN =
    std::max(alignof(Header), alignof(std::max_align_t));

static constexpr std::uintptr_t HEADER_SIZE = sizeof(Header);
static constexpr std::uintptr_t HEADER_OFFSET = HEADER_ALIGN - 1u;
static constexpr std::uintptr_t HEADER_MASK = ~HEADER_ALIGN;

static inline Header* header_cast(void* header) noexcept {
    return static_cast<Header*>(header);
}

static inline std::uintptr_t align(std::uintptr_t ptr) noexcept {
    return (ptr + HEADER_SIZE + HEADER_OFFSET) & HEADER_MASK;
}

Pool::Pool(void* memory, std::size_t size) noexcept :
    m_memory{memory},
    m_size{size}
{
     
}

auto Pool::allocate(std::size_t n) noexcept -> void* {
    void* ptr = nullptr;

    return ptr;
}

auto Pool::reallocate(void* ptr, std::size_t n) noexcept -> void* {
    return ((n != 0) || (ptr != nullptr)) ? std::realloc(ptr, n) : nullptr;
}

void Pool::deallocate(void* ptr) noexcept {
    return std::free(ptr);
}
