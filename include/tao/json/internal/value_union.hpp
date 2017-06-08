// Copyright (c) 2015-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_VALUE_UNION_HPP
#define TAOCPP_JSON_INCLUDE_INTERNAL_VALUE_UNION_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../byte.hpp"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         template< typename Value, template< typename ... > class Allocator = std::allocator >
         union value_union
         {
            using string_t = std::basic_string< char, std::char_traits< char >, Allocator< char > >;
            using binary_t = std::vector< byte, Allocator< byte > >;
            using array_t = std::vector< Value, Allocator< Value > >;
            using object_t = std::map< string_t, Value, std::less< string_t >, Allocator< std::pair< const string_t, Value > > >;

            value_union()
            {
            }

            value_union( const value_union& ) = delete;
            void operator=( const value_union& ) = delete;

            ~value_union()
            {
            }

            bool b;
            std::int64_t i;
            std::uint64_t u;
            double d;

            string_t s;
            binary_t x;
            array_t a;
            object_t o;

            const Value* p;
         };

      }  // namespace internal

   }  // namespace json

}  // namespace tao

#endif
