#pragma once

#include<iostream>
#include<stdexcept>//异常库
//using namespace std;
namespace pjx {
namespace stl {

template <typename T>
class Vector
{
public:
    Vector();
    ~Vector();
    void push_back(const T & value);
    void pop_back();
    int size() const;
    int capacity() const;
    void reserve(int size);
    void resize(int size);
    T & at(int index);//at运算符返回index处值的引用;不符合条件还要抛出异常；
    T & operator [] (int index);//重载[]运算符
    T & front();
    T & back();
    bool empty() const;
    void clear();
    Vector<T> & operator = (const Vector<T> & other);//重载赋值运算符
    T * data();
    void swap(Vector<T> & other);
    void show() const;

    class Iterator
    {
    public:
        Iterator() : m_pointer(nullptr) {}
        Iterator(T * pointer) : m_pointer(pointer) {}
        ~Iterator() {}

        bool operator == (const Iterator & other)
        {
            return m_pointer == other.m_pointer;
        }

        bool operator != (const Iterator & other)
        {
            return m_pointer != other.m_pointer;
        }

        Iterator & operator = (const Iterator & other)
        {
            m_pointer = other.m_pointer;
            return * this;
        }

        Iterator & operator ++ ()
        {
            m_pointer += 1;
            return *this;
        }

        Iterator operator ++ (int)
        {
            Iterator it = *this;
            ++(*this);
            return it;
        }

        Iterator operator + (int i)
        {
            Iterator it = *this;
            it.m_pointer += i;
            return it;
        }

        Iterator & operator += (int i)
        {
            m_pointer += i;
            return *this;
        }

        Iterator operator - (int i)
        {
            Iterator it = *this;
            it.m_pointer -= i;
            return it;
        }

        Iterator & operator -= (int i)
        {
            m_pointer -= i;
            return *this;
        }

        int operator - (const Iterator & other) const//迭代器相减
        {
            return m_pointer - other.m_pointer;
        }

        T operator * ()//注意返回值的类型
        {
            return *m_pointer;
        }

        T * operator -> ()
        {
            return m_pointer;
        }

    private:
        T * m_pointer;
    };

    Iterator begin();
    Iterator end();
    Iterator find(const T & value);
    Iterator insert(Iterator it, const T & value);
    Iterator insert(Iterator it, int n, const T & value);
    Iterator erase(Iterator it);
    Iterator erase(Iterator first, Iterator last);
    
private:
    T * m_data;
    int m_size;
    int m_capacity;
};

template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{
}

template <typename T>
Vector<T>::~Vector()
{
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
void Vector<T>::push_back(const T & value)
{
    if (m_size < m_capacity)
    {
        m_data[m_size] = value;
        m_size++;
        return;
    }
    if (m_capacity == 0)
    {
        m_capacity = 1;
    }
    else
    {
        m_capacity *= 2;
    }
    T * data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        data[i] = m_data[i];
    }
    if (m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_data[m_size] = value;
    m_size++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (m_size > 0)
    {
        m_size--;
    }
}

template <typename T>
int Vector<T>::size() const
{
    return m_size;
}

template <typename T>
int Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void Vector<T>::reserve(int size)
{
    if(m_capacity >= size)
    {
        return;
    }
    while(m_capacity < size)
    {
        if(m_capacity == 0)
        {
        m_capacity = 1;
        }
        else
        {
        m_capacity *= 2;
        }
    }
    T * data = new T[m_capacity];
    for(int i = 0; i < m_size; i++)
    {
        data[i] = m_data[i];
    }
    if(m_data != nullptr)//释放m_data的内存
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
}

template <typename T>
void Vector<T>::resize(int size)
{
    if(size <= m_size)
    {
        m_size = size;
        return;
    }
    if(m_size <= m_capacity)
    {
        for(int i = m_size; i < size; i++)
        {
            m_data[i] = T();
        }
        m_size = size;
        return;
    }
    while(size > m_capacity)
    {
        if(m_capacity == 0)
        {
            m_capacity = 1;
        }
        else
        {
            m_capacity *= 2;
        }
    }
    T * data = new T[m_capacity];
    for(int i =0; i < m_size; i++)
    {
        data[i] = m_data[i];
    }
    for(int i = m_size; i < size; i++)
    {
        data[i] = T();
    }

    if(m_data != nullptr)
    {
        delete [] m_data;
        m_data = nullptr;
    }
    m_data = data;
    m_size = size;
}

template <typename T>
T & Vector<T>::at(int index)
{
    if(index < 0 || index >= m_size)
    {
        throw std::logic_error("out of range");
    }
    return m_data[index];
}

template <typename T>
T & Vector<T>::operator [] (int index)
{
    return at(index);
}

template <typename T>
T & Vector<T>::front()
{
    if(m_size <= 0)
    {
        throw std::logic_error("vector is empty");
    }
    return m_data[0];
}

template <typename T>
T & Vector<T>::back()
{
    if(m_size <= 0)
    {
        throw std::logic_error("vector is empty");
    }
    return m_data[m_size-1];
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
}

template <typename T>
T * Vector<T>::data()
{
    return m_data;
}

template <typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & other)
{
    if(m_capacity < other.m_size)//当前vector容量不足时，需要扩容；
    {
        if(m_data != nullptr)//释放原内存空间
        {
            delete [] m_data;
            m_data = nullptr;
            m_size = 0;
            m_capacity = 0;
        }
        while(m_capacity < other.m_size)//扩容
        {
            if(m_capacity == 0)
            {
                m_capacity = 1;
            }
            else
            {
                m_capacity *= 2;
            }
        }
        m_data = new T[m_capacity];
    }
    for(int i = 0; i < other.m_size; i++)//赋值容器中的值.第一次写的时候，写成了i < m_size，由于m_size已经设置为0，所以会产生错误；
    {
        m_data[i] = other.m_data[i];
    }
    m_size = other.m_size;
    return * this;
}

template <typename T>
void Vector<T>::swap(Vector<T> & other)//自己写的，和源码的有出入;
{
    T *data = this->m_data;
    int size =  this->m_size;
    int capacity = this->m_capacity;

    this->m_data = other.m_data;
    this->m_size = other.m_size;
    this->m_capacity = other.m_capacity;

    other.m_data = data;
    other.m_size = size;
    other.m_capacity = capacity;
    
}

template <typename T>
void Vector<T>::show() const
{
    std::cout << "size=" << size() << ", capacity=" << capacity() << std::endl;
    for (int i = 0; i < m_size; i++)
    {
        std::cout << m_data[i] << ",";
    }
    std::cout << std::endl;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()//不加typename会报错，加上typename说明是一个类型而不是变量，need 'typename' before 'pjx::stl::Vector<T>::Iterator' because 'pjx::stl::Vector<T>' is a dependent scope
{   
    Vector<T>::Iterator it(m_data);//Iterator的有参构造，传入数组的首地址进去；
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
    Vector<T>::Iterator it(m_data + m_size);
    return it;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::find(const T & value)
{
    for(Vector<T>::Iterator it = begin(); it != end(); it++)
    {
        if(*it == value)
        {
            return it;
        }
    }
    return end();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(Vector<T>::Iterator it, const T & value)//调用下面的insert
{

}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(Vector<T>::Iterator it, int n, const T & value)
{
    
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(Vector<T>::Iterator it)
{

}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(Vector<T>::Iterator first, Vector<T>::Iterator last)
{

}



}
}


