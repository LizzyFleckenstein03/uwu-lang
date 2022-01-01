# uwulang
UWU (**U**ltimate p**W**ogwamming lang**U**age) is a **functional**, **interpreted**, **weakly typed** programming language written in C.

```uwu
fibo
	bool.if(int.smaller($1, 0), 0,
	bool.if(int.equal($1, 0),   1,
	int.add(
		fibo(int.sub($1, 1)),
		fibo(int.sub($1, 2))
	)))
```

You can run the example using `./uwu example/test.uwu`

## What this language is

- Demonstration of dlopen - 35%
- Demonstration of lambda - 30%
- Fun exercise for myself - 20%
- A meme - 10%
- Meant for actual use - 5%

It's turing complete and somewhat useable.

## Invocation

Make sure the submodules are checked out:

```
git submodule update --init
```

To build:

```
make
make -C std
```

To run:

```
./uwu <module> <args>
```

`<module>` is a path relative to the current directory.
Several file names are tried, the first one that exists is used:

- `<module>`
- `<module>.uwu`
- `<module>.so`

If the file name ends with `.so`, it is treated as a native module.

## Features

Makes heavy use of a module system with relative paths.

There is support for native modules written in C (or a C ABI compatible language) that are loaded at runtime. The standard library relies on this feature.

Strictly follows lambda principle. Functions without arguments are constants. Functions can (by design) not interact with anything globally, the input is passed to the main function and the only output is the return value of the main function. _However_, global interaction (e.g. print() or read()) could theoretically be added by native modules and since the VM does not cache any results and always calls functions, even .

Arguments are always passed by value, there are no references (except references to functions). This way, all memory allocation is stack based and no garbage collector is needed.

The syntax is very minimal. Almost everything is solved via functions (no control structures, no operators). The are only integer and string literals, but complex data structures are possible with native modules and available in the standard library.

Currently there are no floating point values, but they might be added in the future (One could also add them using native modules).

Typing is weak and handled at runtime, native modules can easily add their own types. Handling of type errors is up to the functions, usually they will throw an error and exit the program if incorrect types were passed to them.

## Platform

Does not aim to run on a platform other than Linux. Only tested on x86_64 so far, but it should work on other architectures as well.

Uses shared object files for native modules, opens them with `dlopen`, which is POSIX.1-2001.

Requires a libc that implements asprintf (asprintf is not standard, glibc and musl implement it and there are drop-in replacements)

The current implementation of the VM does not take advantage of lambda (no caching of results), but such a feature might be added in the future. I might also add a compiler for LLVM or x86_64 NASM or a JIT in the future.

## Further Documentation

See `doc/syntax.md` for a syntax documentation.
See `doc/std.md` for standard library documentation.
