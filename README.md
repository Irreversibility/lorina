[![Build Status](https://travis-ci.org/hriener/lorina.svg?branch=master)](https://travis-ci.org/hriener/lorina)
[![Documentation Status](https://readthedocs.org/projects/lorina/badge/?version=latest)](http://lorina.readthedocs.io/en/latest/?badge=latest)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# lorina

<img src="https://cdn.rawgit.com/hriener/lorina/master/lorina.svg" width="64" height="64" align="left" style="margin-right: 12pt" />
lorina is a C++ parsing library.  It provides implementations of parsers for various simple file formats used in logic synthesis and formal verification.

[Read the full documentation.](http://lorina.readthedocs.io/en/latest/?badge=latest)

## Example

The following code snipped parses the bench file `"network.bench"` and calls the methods `on_input` and `on_gate` for each input and gate declaration in the file, respectively.

```c++
#include <lorina/lorina.hpp>

class reader : public bench_reader
{
public:
  void on_input( const std::string& name ) const override
  {
    /* ... */
  }

  void on_gate( const std::vector<std::string>& inputs, const std::string& output,
                const std::string& type ) const override
  {
    /* ... */
  }
}; /* reader */

read_bench( "network.bench", reader() );
```

Besides parsing, the reader supports a mechanism to react on parse errors.

```c++
#include <lorina/diagnostics.hpp>

class diagnostics : public diagnostic_engine
{
public:
  void emit( diagnostic_level level, const std::string& message ) const override
  {
    /* ... */
  }
}; /* diagnostics */

diagnostics diag;
read_bench( "network.bench", reader(), &diag );
```
