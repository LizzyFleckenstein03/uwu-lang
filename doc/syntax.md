## Syntax

A module is made out of functions. Each function is made out of a name and exactly one expression, seperated by arbitrary whitespace.

```
function_name expression

other_function_name
	other_expression


		weird_indent_function_name

	weird_indent_expression

```

An expression is either of these:

- Integer literal: `0`, `1`, `3245`
- String literal: `"hello, world"`, `""`,

```
"this is   
a multiline   
string literal    
"
```

- Argument number: `$0`, `$1`, `$5` 
- Function reference: `&function_name`
- Function call: `function_name(args)` or just `function_name`, where args is a comma-separated list of expressions.

**Important:** UwU is based on lazy evaluation. This means that when passing arguments to a function, these arguments are not passed directly as values, but rather as expressions. Each argument is evaulated as the called function accesses it. This means that you can have constructs that would cause infinite recursion in other languages - a good example for a usecase of that are conditions: `bool.if(condition, if_true, else)` is just a regular function from the standard library. `if_true` is only evaluated if condition is truey, meaning that if condition is falsey and `if_true` is a function call, that function will not be called.

Function name syntax:

- `function`: Call `function` in the current module.
- `.path.to.module.function`: Call `function` in the module located at `path/to/module`. That path is relative to the path of the module calling the function. See module paths section under invocation.
- `std_module.function`: Call `function` in the module `std_module` from the standard library. The location of the standard library is the directory `std` in the path of the `uwu` binary. The standard library can be overwritten; if the environment variable UWU_MODULE_PATH is set, it is used as the standard library path. UWU_MODULE_PATH can also be a list of paths, separated by `:`. In that case, whenever a module from the standard library is requested, the paths is tried in order and the first module found is selected.
