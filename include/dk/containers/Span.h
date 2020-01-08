#ifndef __DK_CONTAINERS_SPAN_H__
#define __DK_CONTAINERS_SPAN_H__

#include <array>

namespace dk
{

inline constexpr std::size_t dynamic_extent = std::numeric_limits<std::size_t>::max();

template<typename T>
class SpanIter
{
private:
	T* m_t;

public:
	constexpr SpanIter(T* t) noexcept : m_t(t) {}

	constexpr T& operator*() noexcept { return *m_t; }
	constexpr const T& operator*() const noexcept { return *m_t; }

	constexpr SpanIter& operator++() noexcept { ++m_t; return *this; }
	constexpr SpanIter& operator++(int) noexcept { return m_t++; }

	constexpr SpanIter& operator--() noexcept { --m_t; return *this; }
	constexpr SpanIter& operator--(int) noexcept { return m_t--; }
};

template<typename T, std::size_t Extent = dynamic_extent>
class Span
{
private:
	T* m_beg;

public:
	/* member types */
	using element_type = T;
	using value_type = std::remove_cvref<T>;
	using index_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = SpanIter<T>;
	using const_iterator = SpanIter<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	/* member constant */
	static constexpr std::size_t extent = Extent;

	constexpr Span() noexcept : m_beg(nullptr) {}
	constexpr Span(pointer ptr, index_type /* count */) noexcept : m_beg(ptr) {}
	constexpr Span(pointer first, pointer /* second */) noexcept : m_beg(first) {}
	template<std::size_t N> constexpr Span(element_type (&arr)[Extent]) noexcept : Span(arr) {}
	template<std::size_t N> constexpr Span(std::array<value_type, Extent>& arr) noexcept : Span(arr.data()) {}
	template<std::size_t N> constexpr Span(const std::array<value_type, Extent>& arr) noexcept : Span(arr.data()) {}
	template<typename Container> constexpr Span(Container& cont) noexcept : Span(std::data(cont)) {}
	template<typename Container> constexpr Span(const Container& cont) noexcept : Span(std::data(cont)) {}
	template<typename U, std::size_t N> constexpr Span(const Span<U, Extent>& that) noexcept : Span(that.data()) {}
	constexpr Span(const Span& that) noexcept = default;

	/* iterators */
	constexpr iterator begin() const noexcept { return m_beg; }
	constexpr const_iterator cbegin() const noexcept { return m_beg; }
	constexpr reverse_iterator rbegin() const noexcept { return this->end(); }
	constexpr const_reverse_iterator crbegin() const noexcept { return this->cend(); }

	constexpr iterator end() const noexcept { return m_beg + Extent; }
	constexpr const_iterator cend() const noexcept { return m_beg + Extent; }
	constexpr reverse_iterator rend() const noexcept { return m_beg; }
	constexpr const_reverse_iterator crend() const noexcept { return m_beg; }

	/* element access */
	constexpr reference front() const noexcept { return *m_beg; }
	constexpr reference back() const noexcept { return *(this->end() - 1); }
	constexpr reference operator[](index_type idx) const noexcept { return m_beg[idx]; }
	constexpr pointer data() const noexcept { return m_beg; }

	/* observers */
	constexpr index_type size() const noexcept { return Extent; }
	constexpr index_type size_bytes() const noexcept { return (this->size() * sizeof(element_type)); }
	[[nodiscard]] constexpr bool empty() const noexcept { return (this->size() == 0); }
};

template<typename T>
class Span<T, dynamic_extent>
{
private:
	T* m_beg;
	T* m_end;

public:
	using element_type = T;
	using value_type = std::remove_cvref<T>;
	using index_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = SpanIter<T>;
	using const_iterator = SpanIter<const T>;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	constexpr Span() noexcept : m_beg(nullptr), m_end(nullptr) {}
	constexpr Span(pointer ptr, index_type count) noexcept : m_beg(ptr), m_end(ptr + count) {}
	constexpr Span(pointer first, pointer second) noexcept : m_beg(first), m_end(second) {}
	template<std::size_t N> constexpr Span(element_type (&arr)[N]) noexcept : Span(arr, N) {}
	template<std::size_t N> constexpr Span(std::array<value_type, N>& arr) noexcept : Span(arr.data(), N) {}
	template<std::size_t N> constexpr Span(const std::array<value_type, N>& arr) noexcept : Span(arr.data(), N) {}
	template<typename Container> constexpr Span(Container& cont) noexcept : Span(std::data(cont), std::size(cont)) {}
	template<typename Container> constexpr Span(const Container& cont) noexcept : Span(std::data(cont), std::size(cont)) {}
	template<typename U, std::size_t N> constexpr Span(const Span<U, N>& that) noexcept : Span(that.data(), that.size()) {}
	constexpr Span(const Span& that) noexcept = default;

	/* iterators */
	constexpr iterator begin() const noexcept { return m_beg; }
	constexpr const_iterator cbegin() const noexcept { return m_beg; }
	constexpr reverse_iterator rbegin() const noexcept { return m_end; }
	constexpr const_reverse_iterator crbegin() const noexcept { return m_end; }

	constexpr iterator end() const noexcept { return m_end; }
	constexpr const_iterator cend() const noexcept { return m_end; }
	constexpr reverse_iterator rend() const noexcept { return m_beg; }
	constexpr const_reverse_iterator crend() const noexcept { return m_beg; }

	/* element access */
	constexpr reference front() const noexcept { return *m_beg; }
	constexpr reference back() const noexcept { return *(m_end - 1); }
	constexpr reference operator[](index_type idx) const noexcept { return m_beg[idx]; }
	constexpr pointer data() const noexcept { return m_beg; }

	/* observers */
	constexpr index_type size() const noexcept { return m_end - m_beg; }
	constexpr index_type size_bytes() const noexcept { return (this->size() * sizeof(element_type)); }
	[[nodiscard]] constexpr bool empty() const noexcept { return (this->size() == 0); }
};

}

#endif // !__DK_CONTAINERS_SPAN_H__
