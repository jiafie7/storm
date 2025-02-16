#pragma once

#include <cctype>  // std::isalpha()
#include <stdexcept>
#include "xml/xml.h"

namespace storm
{
  namespace xml
  {
    class XmlParser
    {
      public:
        XmlParser() = default;
        ~XmlParser() = default;

        bool load(const std::string& filename);
        bool load(const char* buf, int len);
        Xml parse();
        
      private:
        void skipWhiteSpace();
        bool parseDeclaration();
        bool parseComment();
        Xml parseElement();
        std::string parseElementName();
        std::string parseElementText();
        std::string parseElementAttrKey();
        std::string parseElementAttrVal();


      private:
        std::string m_content;
        int m_index = 0;
    };
  }
}
