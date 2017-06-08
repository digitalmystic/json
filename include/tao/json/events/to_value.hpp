// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_EVENTS_TO_VALUE_HPP
#define TAOCPP_JSON_INCLUDE_EVENTS_TO_VALUE_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../byte.hpp"
#include "../value.hpp"

namespace tao
{
   namespace json
   {
      namespace events
      {
         // Events consumer to build a JSON Value.

         template< template< typename... > class Traits, template< typename... > class Allocator = std::allocator >
         class to_basic_value
         {
         private:
            using value_t = basic_value< Traits, Allocator >;
            using string_t = typename value_t::string_t;
            using binary_t = typename value_t::binary_t;

            std::vector< value_t > m_stack;
            std::vector< string_t > m_keys;
            Allocator< void > m_alloc;

         public:
            to_basic_value() = default;

            template< typename... Ts >
            to_basic_value( Ts&&... ts )
               : m_alloc( std::forward< Ts >( ts )... ),
                 value( allocator_tag(), m_alloc )
            {
            }

            value_t value;

            void null()
            {
               value.unsafe_assign_null();
            }

            void boolean( const bool v )
            {
               value.unsafe_assign_bool( v );
            }

            void number( const std::int64_t v )
            {
               value.unsafe_assign_signed( v );
            }

            void number( const std::uint64_t v )
            {
               value.unsafe_assign_unsigned( v );
            }

            void number( const double v )
            {
               value.unsafe_assign_double( v );
            }

            void string( const string_t& v )
            {
               value.unsafe_emplace_string( v );
            }

            void string( string_t&& v )
            {
               value.unsafe_emplace_string( std::move( v ) );
            }

            void binary( const binary_t& v )
            {
               value.unsafe_emplace_binary( v );
            }

            void binary( binary_t&& v )
            {
               value.unsafe_emplace_binary( std::move( v ) );
            }

            void begin_array()
            {
               m_stack.emplace_back( allocator_tag(), m_alloc );
               m_stack.back().unsafe_emplace_array();
            }

            void begin_array( const std::size_t size )
            {
               begin_array();
               m_stack.back().unsafe_get_array().reserve( size );
            }

            void element()
            {
               m_stack.back().unsafe_emplace_back( std::move( value ) );
               value.discard();
            }

            void end_array( const std::size_t = 0 )
            {
               value = std::move( m_stack.back() );
               m_stack.pop_back();
            }

            void begin_object( const std::size_t = 0 )
            {
               m_stack.emplace_back( allocator_tag(), m_alloc );
               m_stack.back().unsafe_emplace_object();
            }

            void key( const string_t& v )
            {
               m_keys.push_back( v );
            }

            void key( string_t&& v )
            {
               m_keys.push_back( std::move( v ) );
            }

            void member()
            {
               m_stack.back().unsafe_emplace( std::move( m_keys.back() ), std::move( value ) );
               value.discard();
               m_keys.pop_back();
            }

            void end_object( const std::size_t = 0 )
            {
               value = std::move( m_stack.back() );
               m_stack.pop_back();
            }
         };

         using to_value = to_basic_value< traits >;

      }  // namespace events

   }  // namespace json

}  // namespace tao

#endif
