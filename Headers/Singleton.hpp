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
            if (!pInstance_)
            {
                if (destroyed_)
                {
                    OnDeadReference();
                }
                else
                {
                    Create();
                }
            }
            return *pInstance_;
        }

    protected:
        Singleton() {}

        virtual ~Singleton()
        {
            pInstance_ = nullptr;
            destroyed_ = true;
        }

    private:
        static void Create()
        {
            static T theInstance;
            pInstance_ = &theInstance;
        }

        static void OnDeadReference()
        {
            throw std::runtime_error("Dead Reference Detected");
        }

    private:
        static T* pInstance_;
        static bool destroyed_;
};

template <typename T>
T* Singleton<T>::pInstance_ = nullptr;

template <typename T>
bool Singleton<T>::destroyed_ = false;

#endif // _SINGLETON_HPP_
