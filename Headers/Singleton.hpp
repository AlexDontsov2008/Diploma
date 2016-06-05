#ifndef _SINGLETON_HPP_
#define _SINGLETON_HPP_

#include <memory>
#include <iostream>

#include "Uncopyable.hpp"

template <typename T>
class Singleton : private Uncopyable
{
    public:
        static T& Instance()
        {
            if (!m_pInstance)
            {
                if (m_destroyed)
                {
                    OnDeadReference();
                }
                else
                {
                    Create();
                }
            }
            return *m_pInstance;
        }

    protected:
        Singleton() {}

        virtual ~Singleton()
        {
            m_pInstance = nullptr;
            m_destroyed = true;
        }

    private:
        static void Create()
        {
            static T theInstance;
            m_pInstance = &theInstance;
        }

        static void OnDeadReference()
        {
            throw std::runtime_error("Dead Reference Detected");
        }

    private:
        static T* m_pInstance;
        static bool m_destroyed;
};

template <typename T>
T* Singleton<T>::m_pInstance = nullptr;

template <typename T>
bool Singleton<T>::m_destroyed = false;

#endif // _SINGLETON_HPP_
