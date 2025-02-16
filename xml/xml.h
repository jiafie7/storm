#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "utility/value.h"
using namespace storm::utility;

namespace storm
{
  namespace xml
  {
    class Xml
    {
      public:
        Xml() = default;
        Xml(const char* name);
        Xml(const std::string& name);
        Xml(const Xml& other);
        Xml(Xml&& other);
        ~Xml();

        Xml& operator=(const Xml& other);
        Xml& operator=(Xml&& other) noexcept;

        std::string getName() const;
        void setName(const std::string& name);
        
        std::string getText() const;
        void setText(const std::string& text);

        Value& getAttribute(const std::string& key);
        void setAttribute(const std::string& key, const Value& value);

        void append(const Xml& child);
        void append(Xml&& child);
        void remove(int index);
        void remove(const char* name);
        void remove(const std::string& name);

        Xml& operator[](int index);
        Xml& operator[](const char* name);
        Xml& operator[](const std::string& name);

        int size() const;
        bool empty() const;
        void clear();

        typedef std::vector<Xml>::iterator iterator;
        iterator begin()
        {
          return m_child.begin();
        }

        iterator end()
        {
          return m_child.end();
        }

        iterator erase(iterator it)
        {
          it->clear();
          return m_child.erase(it);
        }

        std::string toString() const;
        std::string toString(int depth) const;
        friend std::ostream& operator<<(std::ostream& os, const Xml& xml)
        {
          os << xml.toString(0);
          return os;
        }

        bool load(const std::string& filename);
        bool load(const char* buf, int len);
        bool save(const std::string& filename);

      private:
        void copy(const Xml& other);
        void swap(Xml& other);
        std::string trimText(const std::string& text);
        std::string trimText(const std::string& text) const;

      private:
        std::string m_name; 
        std::string m_text; 
        std::map<std::string, Value> m_attributes;
        std::vector<Xml> m_child;
    };
  }
}

