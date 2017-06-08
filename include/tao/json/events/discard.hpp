// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_EVENTS_DISCARD_HPP
#define TAOCPP_JSON_INCLUDE_EVENTS_DISCARD_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "../byte.hpp"

namespace tao
{
   namespace json
   {
      namespace events
      {
         // Events consumer that discards events.

         struct discard
         {
            void null() noexcept
            {
            }

            void boolean( const bool ) noexcept
            {
            }

            void number( const std::int64_t ) noexcept
            {
            }

            void number( const std::uint64_t ) noexcept
            {
            }

            void number( const double ) noexcept
            {
            }

            template< typename String >
            void string( const String& ) noexcept
            {
            }

            template< typename Binary >
            void binary( const Binary& ) noexcept
            {
            }

            void begin_array( const std::size_t = 0 ) noexcept
            {
            }

            void element() noexcept
            {
            }

            void end_array( const std::size_t = 0 ) noexcept
            {
            }

            void begin_object( const std::size_t = 0 ) noexcept
            {
            }

            template< typename String >
            void key( const String& ) noexcept
            {
            }

            void member() noexcept
            {
            }

            void end_object( const std::size_t = 0 ) noexcept
            {
            }
         };

      }  // namespace events

   }  // namespace json

}  // namespace tao

#endif
