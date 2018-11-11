#ifndef __DK_SPAN_H__
#define __DK_SPAN_H__

#include <type_traits>
#include <iterator>
#include <cstddef>

namespace lao
{

inline constexpr std::ptrdiff_t dynamic_extent = -1;

template<typename T, std::ptrdiff_t Extent = dynamic_extent>
class Span
{
private:
	const T* m_data;
	size_t   m_size;

public:
	using element_type = const T;
	using value_type = std::remove_cv<T>;
	using index_type = std::ptrdiff_t;
	using difference_type = std::ptrdiff_t;
	using pointer = element_type*;
	using reference = element_type&;
	using iterator = element_type*;
	using const_iterator = iterator;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr Span() noexcept = default;
	constexpr Span(pointer data, index_type size) noexcept : m_data(data), m_size(size) {}
	constexpr Span(pointer data_beg, pointer data_end) noexcept : m_data(data_beg), m_size(std::distance(data_beg, data_end)) {}
	template<size_t N> constexpr Span(value_type (&data)[N]) noexcept : m_data(data), m_size(N) {}
	template<typename Container> constexpr Span(Container& cont) noexcept : m_data(std::data(cont)), m_size(std::size(cont)) {}
	template<typename Container> constexpr Span(const Container& cont) noexcept : m_data(std::data(cont)), m_size(std::size(cont)) {}

	constexpr Span& operator=(const Span& span) noexcept = default;

	constexpr iterator begin() const noexcept { return iterator(m_data); }
	constexpr const_iterator cbegin() const noexcept { return const_iterator(m_data); }

	constexpr iterator end() const noexcept { return iterator(m_data + m_size); }
	constexpr const_iterator cend() const noexcept { return const_iterator(m_data + m_size); }

	constexpr reverse_iterator rbegin() const noexcept { return reverse_iterator(m_data + m_size - 1); }
	constexpr const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_data + m_size - 1); }

	constexpr reverse_iterator rend() const noexcept { return reverse_iterator(m_data - 1); }
	constexpr const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_data - 1); }

	constexpr reference operator[](size_t idx) const noexcept { return m_data[idx]; }
	constexpr reference operator()(size_t idx) const noexcept { return m_data[idx]; }

	constexpr pointer data() const noexcept { return m_data; }
	constexpr size_t size() const noexcept { return m_size; }
	constexpr size_t size_bytes() const noexcept { return m_size * sizeof(element_type); }
	constexpr bool empty() const noexcept { return m_size == 0; }
};

}

#endif  //  !__DK_SPAN_H__
