#ifndef __DK_SINGLETON_H__
#define __DK_SINGLETON_H__

namespace dk
{

template<typename T>
class singleton
{
private:
	T* m_t;

protected:
	singleton() : m_t(static_cast<T*>(this)) {}

public:
	T&       get()       { return *m_t; }
	const T& get() const { return *m_t; }

	T*       get_ptr()       { return m_t; }
	const T* get_ptr() const { return m_t; }
};

}

#endif  //  !__DK_SINGLETON_H__
