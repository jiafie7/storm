#include "xml/xml.h"
#include "xml/xml_parser.h"

using namespace storm::xml; 

Xml::Xml(const char* name)
  : m_name(name)
{
}

Xml::Xml(const std::string& name)
  : m_name(name)
{
}

Xml::Xml(const Xml& other)
{
  copy(other);
}

Xml::Xml(Xml&& other)
{
  swap(other);
}

    
Xml::~Xml()
{
  clear();
}

Xml& Xml::operator=(const Xml& other)
{
  if (this == &other)
    return *this;
  copy(other);
  return *this;
}

Xml& Xml::operator=(Xml&& other) noexcept
{
  if (this == &other)
    return *this;
  swap(other);
  return *this;
}

std::string Xml::getName() const
{
  return m_name;
}

void Xml::setName(const std::string& name)
{
  m_name = name;
}
 
std::string Xml::getText() const
{
  return m_text;
}

void Xml::setText(const std::string& text)
{
  m_text = text;
}

Value& Xml::getAttribute(const std::string& key)
{
  return m_attributes[key]; 
}

void Xml::setAttribute(const std::string& key, const Value& value)
{
  m_attributes[key] = value;
}

void Xml::append(const Xml& child)
{
  m_child.push_back(child);
}

void Xml::append(Xml&& child)
{
  m_child.push_back(std::move(child));
}

void Xml::remove(int index)
{
  if (m_child.empty())
    return;
  
  int size = (int)(m_child.size());
  if (index < 0 || index >= size)
    return;

  m_child.erase(m_child.begin() + index);
}

void Xml::remove(const char* name)
{
  for (auto it = m_child.begin(); it != m_child.end();)
  {
    if (it->getName() == name)
      it = m_child.erase(it);
    else
      ++ it; 
  }
}

void Xml::remove(const std::string& name)
{
  return remove(name.c_str());
}

Xml& Xml::operator[](int index)
{
  return m_child.at(index);
}

Xml& Xml::operator[](const char* name)
{
  for (auto it = m_child.begin(); it != m_child.end(); ++ it)
    if (it->getName() == name)
      return *it;

  m_child.push_back(Xml(name));
  return m_child.back();
}

Xml& Xml::operator[](const std::string& name)
{
  return (*this)[name.c_str()];
}

int Xml::size() const
{
  return m_child.size();
}

bool Xml::empty() const
{
  return m_child.empty();
}

void Xml::clear()
{
  m_name.clear();
  m_text.clear();
  m_attributes.clear();
  m_child.clear();
}

std::string Xml::toString() const
{
  if (m_name.empty())
    return "";

  std::ostringstream oss;
  oss << "<";
  oss << m_name;

  for (auto it = m_attributes.begin(); it != m_attributes.end(); ++ it)
    oss << " " << it->first << "=\"" << it->second << "\"";
  oss << ">";
  
  for (auto it = m_child.begin(); it != m_child.end(); ++ it)
    oss << it->toString();

  oss << trimText(m_text);

  oss << "</" << m_name << ">";
  return oss.str();
}

std::string Xml::toString(int depth) const 
{
  if (m_name.empty())
    return "";

  std::ostringstream oss;

  std::string indent(depth * 2, ' ');
  oss << indent << "<" << m_name;

  for (const auto& attr : m_attributes)
    oss << " " << attr.first << "=\"" << attr.second << "\"";

  if (m_child.empty() && trimText(m_text).empty()) 
  {
    oss << "/>\n";
  } 
  else 
  {
    oss << ">";

    if (!m_child.empty()) 
    {
      oss << "\n";
      for (const auto& child : m_child)
        oss << child.toString(depth + 1);
      if (!trimText(m_text).empty())
        oss << std::string((depth + 1) * 2, ' ') << trimText(m_text) << "\n";
      oss << indent;
        
    } 
    else if (!trimText(m_text).empty()) 
    {
      oss << trimText(m_text);
    }

    oss << "</" << m_name << ">\n";
  }

  return oss.str();
}

void Xml::copy(const Xml& other)
{
  clear();
  m_name = other.m_name;
  m_text = other.m_text;
  m_attributes = other.m_attributes;
  m_child = other.m_child;
}

        
bool Xml::load(const std::string& filename)
{
  XmlParser parser;
  if (!parser.load(filename))
    return false;
  
  *this = parser.parse();
  return true;
}

bool Xml::load(const char* buf, int len)
{
  XmlParser parser;
  if (!parser.load(buf, len))
    return false;
  
  *this = parser.parse();
  return true;
}

bool Xml::save(const std::string& filename)
{
  std::ofstream ofs(filename);
  if (ofs.fail())
    return false;
  ofs << toString(0);
  ofs.close();

  return true;
}

void Xml::swap(Xml& other)
{
  clear();
  m_name.swap(other.m_name);
  m_text.swap(other.m_text);
  m_attributes.swap(other.m_attributes);
  m_child.swap(other.m_child);
}

std::string Xml::trimText(const std::string& text) 
{
  auto start = text.begin();
  auto end = text.end();

  while (start != end && std::isspace(*start)) {
    ++start;
  }

  do {
    --end;
  } while (std::distance(start, end) > 0 && std::isspace(*end));

  return std::string(start, end + 1);
}

std::string Xml::trimText(const std::string& text) const
{
  auto start = text.begin();
  auto end = text.end();

  while (start != end && std::isspace(*start)) {
    ++start;
  }

  do {
    --end;
  } while (std::distance(start, end) > 0 && std::isspace(*end));

  return std::string(start, end + 1);
}
