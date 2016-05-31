#include <fenv.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <time.h>
#include <sys/time.h>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <map>
#include <tuple>
#include <thread>
#include <chrono>
#include <mutex>
#include <functional>

inline std::size_t
unaligned_load(const char* p)
{
  std::size_t result;
  __builtin_memcpy(&result, p, sizeof(result));
  return result;
}
  
inline std::size_t
load_bytes(const char* p, int n)
{
  std::size_t result = 0;
  --n;
  do
    result = (result << 8) + static_cast<unsigned char>(p[n]);
  while (--n >= 0);
  return result;
}

inline std::size_t
shift_mix(std::size_t v)
{ return v ^ (v >> 47);}


/*  
size_t
just_hash(const void* ptr, size_t len, size_t seed)
{
  const char* const buf = static_cast<const char*>(ptr);
  static const size_t mul = (((size_t) 0xc6a4a793UL) << 32UL)
                + (size_t) 0x5bd1e995UL;

  // Remove the bytes not divisible by the sizeof(size_t).  This
  // allows the main loop to process the data as 64-bit integers.
  const int len_aligned = len & ~0x7;
  const char* const end = buf + len_aligned;
  size_t hash = seed ^ (len * mul);
  for (const char* p = buf; p != end; p += 8)
    {
  const size_t data = shift_mix(unaligned_load(p) * mul) * mul;
  hash ^= data;
  hash *= mul;
    }
  if ((len & 0x7) != 0)
    {
  const size_t data = load_bytes(end, len & 0x7);
  hash ^= data;
  hash *= mul;
    }
  hash = shift_mix(hash) * mul;
  hash = shift_mix(hash);
  return hash;
   }
*/

size_t
just_hash(const void* ptr, size_t len, size_t seed) {
  const char* const buf = static_cast<const char*>(ptr);
  static const size_t mul = (((size_t) 0xc6a4a793UL) << 32UL)
                + (size_t) 0x5bd1e995UL;

  // Remove the bytes not divisible by the sizeof(size_t).  This
  // allows the main loop to process the data as 64-bit integers.
  const int len_aligned = len & ~0x7;
  const char* const end = buf + len_aligned;
  size_t hash = seed ^ (len * mul);
  for (const char* p = buf; p != end; p += 8)
    {
  const size_t data = shift_mix(unaligned_load(p) * mul) * mul;
  hash ^= data;
  hash *= mul;
    }
  if ((len & 0x7) != 0)
    {
  const size_t data = load_bytes(end, len & 0x7);
  hash ^= data;
  hash *= mul;
    }
  hash = shift_mix(hash) * mul;
  hash = shift_mix(hash);
  return hash;
}

int main() {
    std::cout << ~0x7 << std::endl;
    std::cout << 0x7 << std::endl;
    
    // 1367886195309846576
    std::string str__ = "936583";
    
    std::cout << std::hash<std::string>()(str__) << std::endl;
    std::cout << std::hash<std::string>()("936583") << std::endl;
    
    std::cout << just_hash(&str__, str__.length(), static_cast<size_t>(0xc70f6907UL)) << std::endl;
    std::cout << just_hash(&str__, str__.length(), static_cast<size_t>(0xc70f6907UL)) << std::endl;
    
    //std::cout << _Hash_bytes(&str__, str__.length(), static_cast<size_t>(0xc70f6907UL)) << std::endl;
    
    //std::cout << _Hash_bytes(&str__, str__.length(), static_cast<size_t>(2166136261UL)) << std::endl;
    //std::cout << _Hash_bytes(&str__, str__.length(), 2166136261UL) << std::endl;
    
    
    
    
}