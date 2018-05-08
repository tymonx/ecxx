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

#ifndef ECXX_ALLOCATOR_STANDARD_HPP
#define ECXX_ALLOCATOR_STANDARD_HPP

#include "ecxx/allocator.hpp"

namespace ecxx {
namespace allocator {

class Standard final : public Allocator {
public:
    Standard() noexcept = default;

    Standard(Standard&& other) noexcept = default;

    Standard(const Standard& other) noexcept = default;

    Standard& operator=(Standard&& other) noexcept = default;

    Standard& operator=(const Standard& other) noexcept = default;

    auto allocate(std::size_t n) noexcept -> void* override;

    auto reallocate(void* ptr, std::size_t n) noexcept -> void* override;

    void deallocate(void* ptr) noexcept override;

    ~Standard() noexcept override;
};

Standard::~Standard() noexcept = default;

} /* namespace allocator */
} /* namespace ecxx */

#endif /* ECXX_ALLOCATOR_STANDARD_HPP */
