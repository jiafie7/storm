#pragma once

#include <map>
#include <string>
#include <typeinfo>

namespace storm
{
  namespace engine
  {
    class Object
    {
    public:
      Object() {}
      virtual ~Object() {}
    };
    class Context
    {
    public:
      Context() {}
      ~Context() { clear(); }
      
      template <typename T>
      void set(const std::string& key, T value);
      
      void set(const std::string& key, const char* value);
      void set(const std::string& key, const std::string& value);
      void set(const std::string& key, Object* value);

      template <typename T>
      T get(const std::string& key);

      void clear();

    private:
      std::map<std::string, bool> m_bool;
      std::map<std::string, char> m_char;
      std::map<std::string, int> m_int;
      std::map<std::string, double> m_double;
      std::map<std::string, std::string> m_str;
      std::map<std::string, Object*> m_obj;
    };

    template <typename T>
    void Context::set(const std::string& key, T value)
    {
      if (typeid(T) == typeid(bool))
        m_bool[key] = value;
      else if (typeid(T) == typeid(char))
        m_char[key] = value;
      else if (typeid(T) == typeid(int))
        m_int[key] = value;
      else if (typeid(T) == typeid(double))
        m_double[key] = value;
    }

    inline void Context::set(const std::string& key, const char* value)
    {
      m_str[key] = value;
    }
    inline void Context::set(const std::string& key, const std::string& value)
    {
      m_str[key] = value;
    }
    inline void Context::set(const std::string& key, Object* value)
    {
      m_obj[key] = value;
    }

    template <typename T>
    inline T Context::get(const std::string& key)
    {
      if (typeid(T) == typeid(bool))
      {
        auto it = m_bool.find(key);
        if (it == m_bool.end())
          return false;
        return it->second;
      }
      else if (typeid(T) == typeid(char))
      {
        auto it = m_char.find(key);
        if (it == m_char.end())
          return 0;
        return it->second;
      }
      else if (typeid(T) == typeid(int))
      {
        auto it = m_int.find(key);
        if (it == m_int.end())
          return 0;
        return it->second;
      }
      else if (typeid(T) == typeid(double))
      {
        auto it = m_double.find(key);
        if (it == m_double.end())
          return 0;
        return it->second;
      }
      return 0;
    }

    template <>
    inline std::string Context::get<std::string>(const std::string& key)
    {
      auto it = m_str.find(key);
      if (it == m_str.end())
          return "";
      return it->second;
    }

    template <>
    inline Object* Context::get<Object*>(const std::string& key)
    {
      auto it = m_obj.find(key);
      if (it == m_obj.end())
          return nullptr;
      return it->second;
    }
         
    inline void Context::clear()
    {
      m_bool.clear();
      m_char.clear();
      m_int.clear();
      m_double.clear();
      m_str.clear();
      for (auto it = m_obj.begin(); it != m_obj.end(); ++ it)
      {
        delete it->second;
        it->second = nullptr;
      }
      m_obj.clear();
    }
  }
}
