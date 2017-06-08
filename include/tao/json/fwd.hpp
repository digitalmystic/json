// Copyright (c) 2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_FWD_HPP
#define TAOCPP_JSON_INCLUDE_FWD_HPP

#include <utility>

namespace tao
{
   namespace json
   {
      template< template< typename... > class Traits, template< typename... > class Allocator = std::allocator >
      class basic_value;

   } // json

} // tao

#endif
