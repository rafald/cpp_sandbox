[![Travis Status](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)

[![Coverage Status](https://coveralls.io/repos/github/rafald/cpp_sandbox/badge.svg?branch=master)](https://coveralls.io/github/rafald/cpp_sandbox?branch=master)

# cpp_sandbox

Sandbox to experiment with:
*travis and coveralls integration
*bjam / Boost.Testing build tool
*modern C++ features

C++ tips:
* reverse_iterators refer/dereference to the position right before the one they’re initialized with:
  * so for range it is ok to specify range:  std::reverse_iterator(end_it), std::reverse_iterator(begin_it) 
  * for translation of single iterator:  std::reverse_iterator( std::next(iter) ) ) so iter can not be end()
* more stuff goes here ...
