# Standard library

## The `:nil` module

- `:nil:nil`: The nil constant

## The `:bool` module

- `:bool:if`: Requires exactly 3 arguments of arbitrary type. If $0 is a truthy value, evaluate and return $1. If $0 is a falsy value, evaluate and return $2. Values considered as falsy are: `:bool:false` and `:nil:nil`. Everything else is considered truey.

- `:bool:and`: Accepts an arbitrary number of arguments of arbitrary type, but at least one. Returns `:bool:true` if all of the arguments are considered truthy.

- `:bool:or`: Accepts an arbitrary number of arguments of arbitrary type, but at least one. Returns `:bool:true` if at least one of the arguments is considered truthy.

- `:bool:equal`: Accepts an arbitrary number of arguments of arbitrary type, but at least 2. Returns `bool:true` if either all of the arguments are considered truthy or all of the arguments are considered falsy.

- `:bool:not`: Accepts exactly one argument of arbitrary type. Returns `:bool:true` if the $0 is considered falsy, returns `:bool:false` if $0 is considered truthy.

- `:bool:true`: The true constant

- `:bool:false`: The false constant

- `:bool:is`: Accepts an arbitrary number of arguments of arbitrary type, but at least one. Returns `:bool:true` if all arguments are booleans (`:nil:nil` is NOT considered a boolean).

## The `:int` module

- `:int:add`: Accepts an arbitrary number of integer arguments (or none at all) and returns the sum of all arguments, or `0` if none were given.

- `:int:sub`: Accepts exactly 2 integer arguments and returns their difference.

- `:int:mul`: Accepts an arbitrary number of integer arguments (or none at all) and returns the product of all arguments, or `1` if none were given.

- `:int:div`: Accepts exactly 2 integer arguments and returns their quotient (rounded towards 0).

- `:int:mod`: Accepts exactly 2 integer arguments and returns the reminder of their division.

- `:int:smaller`: Accepts exactly 2 integer arguments and returns `:bool:true` if $0 is smaller than $1, `:boool:false` else.

- `:int:greater`: Accepts exactly 2 integer arguments and returns `:bool:true` if $0 is greater than $1, `:bool:false` else.

- `:int:equal`: Accepts an arbitrary number of integer arguments, but at least 2. Returns `bool:true` if all the arguments are equal.

- `:int:is`: Accepts an arbitrary number of arguments of arbitrary type, but at least one. Returns `:bool:true` if all arguments are integers.

## The `:str` module

- `:str:cat`: Accepts an arbitrary number of arguments of arbitrary type and returns the concatenation of their string representations.

### String representations

- Integers: decimal notation
- Strings: themself
- Function references: `[Function referece: %p]`, where %p is the memory address of the UwUVMFunction in memory.
- Nil: an empty string
- Booleans: `true` or `false`
