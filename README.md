[![Travis Status](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)

[![Coverage Status](https://coveralls.io/repos/github/rafald/cpp_sandbox/badge.svg?branch=master)](https://coveralls.io/github/rafald/cpp_sandbox?branch=master)

# cpp_sandbox

<a href="http://www.boost.org/LICENSE_1_0.txt" target="_blank">![Boost Licence](http://img.shields.io/badge/license-boost-blue.svg)</a>
<a href="https://github.com/rafald/cpp_sandbox/releases" target="_blank">![Version](https://badge.fury.io/gh/rafald%2Fcpp_sandbox.svg)</a>
<a href="https://travis-ci.org/rafald/cpp_sandbox" target="_blank">![Build Status](https://img.shields.io/travis/rafald/cpp_sandbox/master.svg?label=linux/osx)</a>
<a href="https://ci.appveyor.com/project/rafald/cpp_sandbox" target="_blank">![Build Status](https://img.shields.io/appveyor/ci/rafald/cpp_sandbox/master.svg?label=windows)</a>
<a href="https://coveralls.io/r/rafald/cpp_sandbox?branch=master" target="_blank">![Coveralls](http://img.shields.io/coveralls/rafald/cpp_sandbox/master.svg)</a>
<a href="http://github.com/rafald/cpp_sandbox/issues" target="_blank">![Github Issues](https://img.shields.io/github/issues/rafald/cpp_sandbox.svg)</a>


Sandbox to experiment with:
* travis and coveralls integration
* bjam / Boost.Testing build tool
* modern C++ features


C++ tips:
* reverse_iterators refer/dereference to the position right before the one they’re initialized with:
  * so for range it is ok to specify range:  std::reverse_iterator(end_it), std::reverse_iterator(begin_it) 
  * for translation of single iterator:  std::reverse_iterator( std::next(iter) ) ) so iter can not be end()
* more stuff goes here ...
