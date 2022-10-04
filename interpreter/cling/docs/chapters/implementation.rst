Used Technology
-----------------------------------

`LLVM <https://llvm.org/>`_ is a free, open-source compiler infrastructure under
the `Apache License 2.0 <https://www.apache.org/licenses/LICENSE-2.0>`_. It is
designed as a collection of tools including Front Ends parsers, Middle Ends
optimizers, and Back Ends to produce machine code out of those programs.

`Clang <https://clang.llvm.org/>`_ is a front-end that uses a LLVM
license. Clang works by taking the source language (e.g. C++) and translating it
into an intermediate representation that is then received by the compiler back
end (i.e., the LLVM backend). Its library-based architecture makes it relatively
easy to adapt Clang and build new tools based on it.  Cling inherits a number of
features from LLVM and Clang, such as: fast compiling and low memory use,
efficient C++ parsing, extremely clear and concise diagnostics, Just-In-Time
compilation, pluggable optimizers, and support for `GCC <https://gcc.gnu.org/>`_
extensions.

Interpreters allow for exploration of software development at the rate of human
thought. Nevertheless, interpreter code can be slower than compiled code due to
the fact that translating code at run time adds to the overhead and therefore
causes the execution speed to be slower. This issue is overcome by exploiting
the *Just-In-Time* (`JIT
<https://en.wikipedia.org/wiki/Just-in-time_compilation>`_) compilation
method. With the JIT approach, assembly is generated by the interpreter with a
pseudocode (an `intermediate language
<https://en.wikipedia.org/wiki/Common_Intermediate_Language>`_ that is not
understood by the computer). The intermediate code is then translated into
machine language when required for use.  By following the JIT approach, Cling is
able to evaluate whether a certain part of the source code is executed often,
and then compile this part, therefore reducing the overall execution time.