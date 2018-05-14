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

#ifndef ECXX_ALLOCATOR_HPP
#define ECXX_ALLOCATOR_HPP

#include <cstdint>

namespace ecxx {

class Allocator {
public:
    Allocator() noexcept = default;

    Allocator(Allocator&& other) noexcept = default;

    Allocator(const Allocator& other) noexcept = default;

    Allocator& operator=(Allocator&& other) noexcept = default;

    Allocator& operator=(const Allocator& other) noexcept = default;

    virtual auto allocate(std::size_t n) noexcept -> void* = 0;

    virtual auto reallocate(void* ptr, std::size_t n) noexcept -> void* = 0;

    virtual void deallocate(void* ptr) noexcept = 0;

    template<typename T = char>
    auto allocate(std::size_t n) noexcept -> T*;

    template<typename T = char>
    auto reallocate(void* ptr, std::size_t n) noexcept -> T*;

    virtual ~Allocator() noexcept;
};

inline
Allocator::~Allocator() noexcept = default;

template<typename T> inline auto
Allocator::allocate(std::size_t n) noexcept -> T* {
    return static_cast<T*>(allocate(n * sizeof(T)));
}

template<> inline auto
Allocator::allocate(std::size_t n) noexcept -> void* {
    return allocate(n);
}

template<typename T> inline auto
Allocator::reallocate(void*  ptr, std::size_t n) noexcept -> T* {
    return static_cast<T*>(reallocate(ptr, n * sizeof(T)));
}

template<> inline auto
Allocator::reallocate(void*  ptr, std::size_t n) noexcept -> void* {
    return reallocate(ptr, n);
}

} /* namespace ecxx */

#endif /* ECXX_ALLOCATOR_HPP */
