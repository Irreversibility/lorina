/* lorina: C++ parsing library
 * Copyright (C) 2018  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
  \file diagnostics.hpp
  \brief Implements diagnostics.

  \author Heinz Riener
*/

#pragma once

#include <lorina/colors.hpp>
#include <map>
#include <iostream>
#include <cassert>

namespace lorina
{

class diagnostic_builder;
class diagnostic_engine;

enum class diagnostic_level
{
  ignore = 0,
  note,
  remark,
  warning,
  error,
  fatal,
};

class diagnostic_builder
{
public:
  inline explicit diagnostic_builder( diagnostic_engine& diag, diagnostic_level level, const std::string& message );
  inline ~diagnostic_builder();

  diagnostic_engine& _diag;
  diagnostic_level _level;
  std::string _message;
}; /* diagnostic_builder */

class diagnostic_engine
{
public:
  virtual inline diagnostic_builder report( diagnostic_level level, const std::string& message );
  virtual inline void emit( diagnostic_level level, const std::string& message );

  mutable unsigned number_of_diagnostics = 0;
}; /* diagnostic_engine */

diagnostic_builder::diagnostic_builder( diagnostic_engine& diag, diagnostic_level level, const std::string& message )
    : _diag( diag ), _level( level ), _message( message )
{
}

diagnostic_builder::~diagnostic_builder()
{
  _diag.emit( _level, _message );
}

diagnostic_builder diagnostic_engine::report( diagnostic_level level, const std::string& message )
{
  ++number_of_diagnostics;
  return diagnostic_builder( *this, level, message );
}

void diagnostic_engine::emit( diagnostic_level level, const std::string& message )
{
  using color::modifier;

  switch ( level )
  {
  case diagnostic_level::ignore:
    break;
  case diagnostic_level::note:
    std::cout << modifier( color::FF_BOLD ) << modifier( color::FG_RED ) << "[i] " << modifier( color::FG_DEFAULT )
              << message << modifier( color::RESET ) << std::endl;
    break;
  case diagnostic_level::remark:
    std::cerr << modifier( color::FF_BOLD ) << modifier( color::FG_RED ) << "[i] " << modifier( color::FG_DEFAULT )
              << message << modifier( color::RESET ) << std::endl;
    break;
  case diagnostic_level::warning:
    std::cerr << modifier( color::FF_BOLD ) << modifier( color::FG_RED ) << "[w] " << modifier( color::FG_DEFAULT )
              << message << modifier( color::RESET ) << std::endl;
    break;
  case diagnostic_level::error:
    std::cerr << modifier( color::FF_BOLD ) << modifier( color::FG_RED ) << "[e] " << modifier( color::FG_DEFAULT )
              << message << modifier( color::RESET ) << std::endl;
    break;
  case diagnostic_level::fatal:
    std::cerr << modifier( color::FF_BOLD ) << modifier( color::FG_RED ) << "[E] " << modifier( color::FG_DEFAULT )
              << message << modifier( color::RESET ) << std::endl;
    break;
  default:
    assert( false );
  }
}

class silent_diagnostic_engine : public diagnostic_engine
{
public:
  virtual diagnostic_builder report( diagnostic_level level, const std::string& message )
  {
    (void)message;
    ++number_of_diagnostics;
    return diagnostic_builder( *this, level, std::string() );
  };

  virtual void emit( diagnostic_level level, const std::string& message )
  {
    (void)level;
    (void)message;
  }

  mutable unsigned number_of_diagnostics = 0;
}; /* silent_diagnostic_engine */

} // namespace lorina
