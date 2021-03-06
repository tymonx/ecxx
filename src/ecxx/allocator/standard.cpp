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

#include "ecxx/allocator/standard.hpp"

#include <cstdlib>

using ecxx::allocator::Standard;

auto Standard::allocate(std::size_t n) noexcept -> void* {
    return (n != 0) ? std::malloc(n) : nullptr;
}

auto Standard::reallocate(void* ptr, std::size_t n) noexcept -> void* {
    return ((n != 0) || (ptr != nullptr)) ? std::realloc(ptr, n) : nullptr;
}

void Standard::deallocate(void* ptr) noexcept {
    return std::free(ptr);
}
