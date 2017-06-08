// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_STRING_STATE_HPP
#define TAOCPP_JSON_INCLUDE_INTERNAL_STRING_STATE_HPP

#include <string>
#include <utility>

namespace tao
{
   namespace json
   {
      namespace internal
      {
         template< typename String = std::string >
         struct string_state
         {
            string_state() = default;
            string_state( const string_state& ) = delete;
            void operator=( const string_state& ) = delete;

            template< typename Allocator >
            explicit
            string_state( Allocator& alloc )
               : unescaped( typename String::allocator_type( alloc ) )
            {
            }

            template< typename Consumer >
            void success( Consumer& consumer )
            {
               consumer.string( std::move( unescaped ) );
            }

            String unescaped;
         };

      }  // namespace internal

   }  // namespace json

}  // namespace tao

#endif
