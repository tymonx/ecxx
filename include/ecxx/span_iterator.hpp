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

#ifndef ECXX_SPAN_ITERATOR_HPP
#define ECXX_SPAN_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace ecxx {

template<typename T>
class SpanIterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    constexpr SpanIterator() noexcept = default;

    constexpr SpanIterator(pointer ptr) noexcept;

    constexpr SpanIterator(const SpanIterator& other) noexcept = default;

    template<typename U = T, typename = std::enable_if_t<
        std::is_const<U>::value, int>>
    constexpr SpanIterator(
            const SpanIterator<std::remove_const_t<T>>& other) noexcept;

    constexpr SpanIterator(SpanIterator&& other) noexcept = default;

    constexpr auto operator=(
            const SpanIterator& other) noexcept -> SpanIterator& = default;

    constexpr auto operator=(
            SpanIterator&& other) noexcept -> SpanIterator& = default;

    constexpr auto operator++() noexcept -> SpanIterator&;

    constexpr auto operator++(int) noexcept -> SpanIterator;

    constexpr auto operator--() noexcept -> SpanIterator&;

    constexpr auto operator--(int) noexcept -> SpanIterator;

    constexpr auto operator+(difference_type n) const noexcept -> SpanIterator;

    constexpr auto operator+=(difference_type n) noexcept -> SpanIterator&;

    constexpr auto operator-(difference_type n) const noexcept -> SpanIterator;

    constexpr auto operator-=(difference_type n) noexcept -> SpanIterator&;

    constexpr auto operator[](difference_type n) noexcept -> reference;

    constexpr auto operator[](difference_type n) const noexcept -> reference;

    constexpr auto operator*() noexcept -> reference;

    constexpr auto operator*() const noexcept -> reference;

    constexpr auto operator->() noexcept -> pointer;

    constexpr auto operator->() const noexcept -> pointer;
private:
    pointer m_ptr{nullptr};
};

template<typename T>
template<typename U, typename> inline constexpr
SpanIterator<T>::SpanIterator(
        const SpanIterator<std::remove_const_t<T>>& other) noexcept :
    m_ptr{other.m_ptr}
{ }

template<typename T> inline constexpr
SpanIterator<T>::SpanIterator(pointer ptr) noexcept :
    m_ptr{ptr}
{ }

template<typename T> inline constexpr auto
SpanIterator<T>::operator++() noexcept -> SpanIterator& {
    ++m_ptr;
    return *this;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator++(int) noexcept -> SpanIterator {
    return SpanIterator<T>{m_ptr++};
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator--() noexcept -> SpanIterator& {
    --m_ptr;
    return *this;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator--(int) noexcept -> SpanIterator {
    return SpanIterator<T>{m_ptr--};
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator+(difference_type n) const noexcept ->
        SpanIterator {
    return m_ptr + n;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator+=(difference_type n) noexcept ->
        SpanIterator& {
    m_ptr += n;
    return *this;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator-(difference_type n) const noexcept ->
        SpanIterator {
    return m_ptr - n;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator-=(difference_type n) noexcept ->
        SpanIterator& {
    m_ptr -= n;
    return *this;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator[](
        difference_type n) noexcept -> reference {
    return *(m_ptr + n);
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator[](
        difference_type n) const noexcept -> reference {
    return *(m_ptr + n);
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator*() noexcept -> reference {
    return *m_ptr;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator*() const noexcept -> reference {
    return *m_ptr;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator->() noexcept -> pointer {
    return m_ptr;
}

template<typename T> inline constexpr auto
SpanIterator<T>::operator->() const noexcept -> pointer {
    return m_ptr;
}

template<typename T, typename U> static inline constexpr auto
operator-(const SpanIterator<T>& lhs, const SpanIterator<U>& rhs)
        noexcept -> decltype(&(*lhs) - &(*rhs)) {
    return &(*lhs) - &(*rhs);
}

template<typename T> static inline constexpr auto
operator+(typename SpanIterator<T>::difference_type n,
        const SpanIterator<T>& rhs) noexcept -> SpanIterator<T> {
    return n + &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator==(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) == &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator!=(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) != &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator<(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) < &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator>(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) > &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator>=(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) >= &(*rhs);
}

template<typename T, typename U> static inline constexpr auto
operator<=(const SpanIterator<T>& lhs,
        const SpanIterator<U>& rhs) noexcept -> bool {
    return &(*lhs) <= &(*rhs);
}

} /* namespace ecxx */

#endif /* ECXX_SPAN_ITERATOR_HPP */
