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

#ifndef ECXX_SPAN_HPP
#define ECXX_SPAN_HPP

#include "span_iterator.hpp"

#include <cstddef>
#include <limits>
#include <algorithm>
#include <type_traits>

namespace ecxx {

template<typename T>
class Span {
public:
    using value_type = T;

    using pointer = T*;

    using const_pointer = const T*;

    using reference = T&;

    using const_reference = const T&;

    using size_type = std::size_t;

    using difference_type = std::ptrdiff_t;

    using iterator = SpanIterator<T>;

    using const_iterator = SpanIterator<const T>;

    using reverse_iterator = std::reverse_iterator<iterator>;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    static constexpr size_type npos{std::numeric_limits<size_type>::max()};

    constexpr Span() noexcept = default;

    constexpr Span(std::nullptr_t) noexcept;

    template<typename U = T, typename std::enable_if<
        std::is_const<U>::value>::type>
    constexpr Span(const Span<typename std::remove_const_t<U>>& other) noexcept;

    template<typename U, typename = typename std::enable_if<std::is_convertible<
        typename U::pointer, pointer>::value>::type>
    constexpr Span(U& other) noexcept;

    template<typename U, typename = typename std::enable_if<std::is_convertible<
        typename U::pointer, pointer>::value>::type>
    constexpr Span(const U& other) noexcept;

    constexpr Span(pointer ptr, size_type n) noexcept;

    template<typename InputIt>
    constexpr Span(InputIt input_first, InputIt input_last) noexcept;

    template<size_type N>
    constexpr Span(value_type (&arr)[N]) noexcept;

    constexpr Span(const Span& other) noexcept = default;

    constexpr Span(Span&& other) noexcept = default;

    constexpr Span& operator=(const Span& other) noexcept = default;

    constexpr Span& operator=(Span&& other) noexcept = default;

    constexpr size_type size() const noexcept;

    constexpr size_type length() const noexcept;

    constexpr size_type size_bytes() const noexcept;

    constexpr bool empty() const noexcept;

    constexpr bool operator!() const noexcept;

    constexpr explicit operator bool() const noexcept;

    constexpr pointer data() noexcept;

    constexpr const_pointer data() const noexcept;

    constexpr reference front() noexcept;

    constexpr const_reference front() const noexcept;

    constexpr reference back() noexcept;

    constexpr const_reference back() const noexcept;

    constexpr reference operator[](size_type pos) noexcept;

    constexpr const_reference operator[](size_type pos) const noexcept;

    constexpr Span first(size_type count) const noexcept;

    constexpr Span last(size_type count) const noexcept;

    constexpr Span subspan(size_type offset,
            size_type count = npos) const noexcept;

    constexpr iterator begin() noexcept;

    constexpr const_iterator begin() const noexcept;

    constexpr const_iterator cbegin() const noexcept;

    constexpr iterator end() noexcept;

    constexpr const_iterator end() const noexcept;

    constexpr const_iterator cend() const noexcept;

    constexpr reverse_iterator rbegin() noexcept;

    constexpr const_reverse_iterator rbegin() const noexcept;

    constexpr const_reverse_iterator crbegin() const noexcept;

    constexpr reverse_iterator rend() noexcept;

    constexpr const_reverse_iterator rend() const noexcept;

    constexpr const_reverse_iterator crend() const noexcept;
private:
    pointer m_begin{nullptr};
    pointer m_end{nullptr};
};

template<typename T> inline constexpr
Span<T>::Span(std::nullptr_t) noexcept { }

template<typename T> template<typename U, typename std::enable_if<
    std::is_const<U>::value>::type> inline constexpr
Span<T>::Span(const Span<
        typename std::remove_const<U>::type>& other) noexcept :
    m_begin{&*other.begin()}, m_end{&*other.end()}
{ }

template<typename T> template<typename U, typename> inline constexpr
Span<T>::Span(const U& other) noexcept :
    m_begin{&*other.begin()}, m_end{&*other.end()}
{ }

template<typename T> template<typename U, typename> inline constexpr
Span<T>::Span(U& other) noexcept :
    m_begin{&*other.begin()}, m_end{&*other.end()}
{ }

template<typename T> inline constexpr
Span<T>::Span(pointer ptr, size_type n) noexcept :
    m_begin{ptr}, m_end{ptr + n}
{ }

template<typename T> template<typename InputIt> inline constexpr
Span<T>::Span(InputIt input_first, InputIt input_last) noexcept :
    m_begin{&*input_first}, m_end{&*input_last}
{ }

template<typename T> template<std::size_t N> inline constexpr
Span<T>::Span(value_type (&arr)[N]) noexcept :
    m_begin{arr}, m_end{arr + N}
{ }

template<typename T> inline constexpr auto
Span<T>::size() const noexcept -> size_type {
    return m_end - m_begin;
}

template<typename T> inline constexpr auto
Span<T>::size_bytes() const noexcept -> size_type {
    return sizeof(T) * size();
}

template<typename T> inline constexpr auto
Span<T>::length() const noexcept -> size_type {
    return size();
}

template<typename T> inline constexpr auto
Span<T>::empty() const noexcept -> bool {
    return m_begin == m_end;
}

template<typename T> inline constexpr auto
Span<T>::operator!() const noexcept -> bool {
    return m_begin == m_end;
}

template<typename T> inline constexpr
Span<T>::operator bool() const noexcept {
    return m_begin != m_end;
}

template<typename T> inline constexpr auto
Span<T>::data() noexcept -> pointer {
    return m_begin;
}

template<typename T> inline constexpr auto
Span<T>::data() const noexcept -> const_pointer {
    return m_begin;
}

template<typename T> inline constexpr auto
Span<T>::front() noexcept -> reference {
    return *m_begin;
}

template<typename T> inline constexpr auto
Span<T>::front() const noexcept -> const_reference {
    return *m_begin;
}

template<typename T> inline constexpr auto
Span<T>::back() noexcept -> reference {
    return *(m_end - 1);
}

template<typename T> inline constexpr auto
Span<T>::back() const noexcept -> const_reference {
    return *(m_end - 1);
}

template<typename T> inline constexpr auto
Span<T>::operator[](size_type pos) noexcept -> reference {
    return *(m_begin + pos);
}

template<typename T> inline constexpr auto
Span<T>::operator[](size_type pos) const noexcept -> const_reference {
    return *(m_begin + pos);
}

template<typename T> inline constexpr auto
Span<T>::first(size_type count) const noexcept -> Span {
    const auto total = size();
    return {m_begin, m_begin + (count < total) ? count : total};
}

template<typename T> inline constexpr auto
Span<T>::last(size_type count) const noexcept -> Span {
    const auto total = size();
    return {m_end - (count < total) ? count : total, m_end};
}

template<typename T> inline constexpr auto
Span<T>::subspan(size_type offset,
        size_type count) const noexcept -> Span {
    return last(size() - offset).first(count);
}

template<typename T> inline constexpr auto
Span<T>::begin() noexcept -> iterator {
    return iterator{m_begin};
}

template<typename T> inline constexpr auto
Span<T>::begin() const noexcept -> const_iterator {
    return const_iterator{m_begin};
}

template<typename T> inline constexpr auto
Span<T>::cbegin() const noexcept -> const_iterator {
    return const_iterator{m_begin};
}

template<typename T> inline constexpr auto
Span<T>::end() noexcept -> iterator {
    return iterator{m_end};
}

template<typename T> inline constexpr auto
Span<T>::end() const noexcept -> const_iterator {
    return const_iterator{m_end};
}

template<typename T> inline constexpr auto
Span<T>::cend() const noexcept -> const_iterator {
    return const_iterator{m_end};
}

template<typename T> inline constexpr auto
Span<T>::rbegin() noexcept -> reverse_iterator {
    return iterator{m_end - 1};
}

template<typename T> inline constexpr auto
Span<T>::rbegin() const noexcept -> const_reverse_iterator {
    return const_iterator{m_end - 1};
}

template<typename T> inline constexpr auto
Span<T>::crbegin() const noexcept -> const_reverse_iterator {
    return const_iterator{m_end - 1};
}

template<typename T> inline constexpr auto
Span<T>::rend() noexcept -> reverse_iterator {
    return iterator{m_begin - 1};
}

template<typename T> inline constexpr auto
Span<T>::rend() const noexcept -> const_reverse_iterator {
    return const_iterator{m_begin - 1};
}

template<typename T> inline constexpr auto
Span<T>::crend() const noexcept -> const_reverse_iterator {
    return const_iterator{m_begin - 1};
}

template<typename T1, typename T2 = T1> static inline constexpr bool
operator==(const Span<T1>& lhs, const Span<T2>& rhs) noexcept {
    return (lhs.size() == rhs.size())
        ? std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin()) : false;
}

template<typename T1, typename T2 = T1> static inline constexpr bool
operator!=(const Span<T1>& lhs, const Span<T2>& rhs) noexcept {
    return !(lhs == rhs);
}

} /* namespace ecxx */

#endif /* ECXX_SPAN_HPP */
