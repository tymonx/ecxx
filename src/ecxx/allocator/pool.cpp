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

#include <cstddef>
#include <algorithm>

using ecxx::allocator::Pool;

struct Header {
    Header* next;
    std::size_t size;
};

static constexpr std::uintptr_t HEADER_ALIGN =
    std::max(alignof(Header), alignof(std::max_align_t));

static constexpr std::uintptr_t HEADER_OFFSET = HEADER_ALIGN - 1u;
static constexpr std::uintptr_t HEADER_MASK = ~HEADER_ALIGN;

static constexpr inline
auto align(std::uintptr_t address) noexcept -> std::uintptr_t {
    return (address + sizeof(Header) + HEADER_OFFSET) & HEADER_MASK;
}

auto Pool::allocate(std::size_t n) noexcept -> void* {
    void* ptr = nullptr;

    if (n != 0) {
        auto header = static_cast<Header*>(m_header_first);
        auto address_end = m_memory_end;
        auto address = m_memory_begin;

        do {
            address = align(address);

            if ((address + n) <= address_end) {
                ptr = reinterpret_cast<void*>(address);

                auto hdr = reinterpret_cast<Header*>(
                        address - sizeof(Header));

                hdr->size = n;

                if (header != nullptr) {
                    hdr->next = header->next;
                    header->next = hdr;
                }

                if (m_header_first == header) {
                    m_header_first = hdr;
                }
                else {
                    reinterpret_cast<Header*>(address_end)->next = hdr;
                }
            }
            else if (header != nullptr) {
                auto address = align((header != nullptr) ? (std::uintptr_t(header) +
                        sizeof(Header) + header->size) : m_memory_begin);



                address_end = std::uintptr_t(header);
                header = header->prev;
            }
        } while ((ptr == nullptr) && (header != nullptr));
    }

    return ptr;
}

auto Pool::reallocate(void* src, std::size_t n) noexcept -> void* {
    void* ptr = nullptr;

    if (n != 0) {
        if (ptr != nullptr) {

        }
        else {
            ptr = allocate(n);
        }
    }
    else {
        deallocate(ptr);
    }

    return ptr;
}

void Pool::deallocate(void* ptr) noexcept {
    return std::free(ptr);
}
