#ifndef _UNCOPYABLE_HPP_
#define _UNCOPYABLE_HPP_


class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable& operator=(const Uncopyable& rhs)    = delete;
        Uncopyable(const Uncopyable& rhs)               = delete;
};

#endif // _UNCOPYABLE_HPP_
