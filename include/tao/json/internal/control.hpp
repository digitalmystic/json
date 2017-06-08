// Copyright (c) 2016-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_INTERNAL_CONTROL_HPP
#define TAOCPP_JSON_INCLUDE_INTERNAL_CONTROL_HPP

#include "../external/pegtl/contrib/changes.hpp"

#include "errors.hpp"

#include "unescape_action.hpp"

#include "key_state.hpp"
#include "number_state.hpp"
#include "string_state.hpp"

namespace tao
{
   namespace json
   {
      namespace internal
      {
         template< typename Rule, typename String = std::string >
         struct control
            : public errors< Rule >
         {
         };

         template< typename String>
         struct control< rules::number, String >
            : public json_pegtl::change_state< rules::number, number_state, errors >
         {
         };

         template< typename Rule, typename State >
         struct string_state_and_action
            : public errors< Rule >
         {
            template< json_pegtl::apply_mode A,
                      json_pegtl::rewind_mode M,
                      template< typename... > class,
                      template< typename... > class Control,
                      typename Input,
                      typename Consumer >
            static bool match( Input& in, Consumer& st )
            {
               State s;
               if( errors< Rule >::template match< A, M, unescape_action, Control >( in, s ) ) {
                  s.success( st );
                  return true;
               }
               return false;
            }

            template< json_pegtl::apply_mode A,
                      json_pegtl::rewind_mode M,
                      template< typename... > class,
                      template< typename... > class Control,
                      typename Input,
                      typename Consumer,
                      typename Allocator >
            static bool match( Input& in, Consumer& st, Allocator& alloc )
            {
               State s( alloc );
               if( errors< Rule >::template match< A, M, unescape_action, Control >( in, s ) ) {
                  s.success( st );
                  return true;
               }
               return false;
            }
         };

         template< typename String >
         struct control< rules::string::content, String >
            : public string_state_and_action< rules::string::content, string_state< String > >
         {
         };

         template< typename String >
         struct control< rules::key::content, String >
            : public string_state_and_action< rules::key::content, key_state< String > >
         {
         };

      }  // namespace internal

   }  // namespace json

}  // namespace tao

#endif
