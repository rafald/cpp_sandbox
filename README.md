
<a href="http://www.boost.org/LICENSE_1_0.txt" target="_blank">![Boost Licence](http://img.shields.io/badge/license-boost-blue.svg)</a>


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/rafald/cpp_sandbox/trend.png)](https://bitdeli.com/free "Bitdeli Badge")



[![Travis Status](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)](https://api.travis-ci.org/rafald/cpp_sandbox.svg?branch=master)
<!--
<a href="https://travis-ci.org/rafald/cpp_sandbox" target="_blank">![Build Status](https://img.shields.io/travis/rafald/cpp_sandbox/master.svg?label=linux/osx)</a>
-->

<a href="https://https://ci.appveyor.com/project/rafald/cpp-sandbox" target="_blank">![Build Status](https://img.shields.io/appveyor/ci/rafald/cpp-sandbox/master.svg?label=windows)</a>


[![Coverage Status](https://coveralls.io/repos/github/rafald/cpp_sandbox/badge.svg?branch=master)](https://coveralls.io/github/rafald/cpp_sandbox?branch=master)
<!--
<a href="https://coveralls.io/r/rafald/cpp_sandbox?branch=master" target="_blank">![Coveralls](http://img.shields.io/coveralls/rafald/cpp_sandbox/master.svg)</a>
-->

<a href="https://github.com/rafald/cpp_sandbox/releases" target="_blank">![Version](https://badge.fury.io/gh/rafald%2Fcpp_sandbox.svg)</a>

<a href="http://github.com/rafald/cpp_sandbox/issues" target="_blank">![Github Issues](https://img.shields.io/github/issues/rafald/cpp_sandbox.svg)</a>


[![Codeship Status for rafald/cpp_sandbox](https://codeship.com/projects/1532d940-fdc5-0133-0c34-226b7b8bc1bd/status?branch=master)](https://codeship.com/projects/152293)

# cpp_sandbox

Sandbox to experiment with:
* travis and coveralls integration
* bjam / Boost.Testing build tool
* modern C++ features


C++ tips:
* reverse_iterators refer/dereference to the position right before the one they’re initialized with:
  * so for range it is ok to specify range:  std::reverse_iterator(end_it), std::reverse_iterator(begin_it) 
  * for translation of single iterator:  std::reverse_iterator( std::next(iter) ) ) so iter can not be end()
* more stuff goes here ...

Gurus:
* Sean Parent
  * Write all code as if it where a library you intend to submit for standardization. 
  * Focus on the interface. 
  * Borrow, don’t invent. 
  * Write complete and efficient types. 
  * Use algorithms instead of loops. 
  * Avoid inheritance and owning pointers in your interface. 
  * Make your data structures explicit. 
  * Use a task system, message queues, futures with continuations, and parallel algorithms, instead of threads, mutexes, semaphores, and condition variables. It is important to be able to scale down to a single thread as well as up to many.
  * Embrace nothingness.
 
  * Finally, don’t worry about how much space there is around parentheses, what line the curly brace goes, or if you use spaces or tabs. These are bike-shed arguments.
