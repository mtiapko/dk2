#ifndef __DK_SINGLETON_H__
#define __DK_SINGLETON_H__

namespace dk
{

template<typename T>
class singleton : public T
{
private:
	T* m_t;


};

}

#endif  //  !__DK_SINGLETON_H__
