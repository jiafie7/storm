#pragma once

namespace storm
{
  namespace utility
  {
    template <typename T>
    class Singleton
    { 
      public:
        static T* getInstance()
        {
          static T instance;
          return &instance;
        }

      private:
        Singleton() = default;
        Singleton(const Singleton<T>&) = delete;
        Singleton<T>& operator=(const Singleton<T>&) = delete;
        ~Singleton() = default;
    };

#define SINGLETON(classname)                           \
  friend class Singleton<classname>;                   \
    private:                                           \
      classname() = default;                           \
      classname(const classname&) = delete;            \
      classname& operator=(const classname&) = delete; \
      ~classname() = default
  }
}
