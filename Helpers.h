#ifndef HELPERS_H
#define HELPERS_H

#include <sstream>
#include <string>

template <typename T>
std::string to_string(T value)
{
  std::ostringstream os ;
  os << value ;
  return os.str() ;
}

#endif // HELPERS_H
