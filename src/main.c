#include "err.h"
#include "vm.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		error("usage: %s <module>\n", argv[0]);

	vm_run_file(argv[0], argv[1]);
	return 0;
}

/*

0123
"asd"
$arg
&fnname
func(asd)

:int:add
:str:cat
:boo:and
:arr:arr
:set:set

integer::add()
integer::sub()
integer::mul()
integer::div()
integer::mod()
integer::pow()

string::concat()
string::split()
string::find()

array::array()
array::select()
array::insert()
array::length()
array::reduce()
array::map()

set::set()
set::pair()
set::select()
set::insert()
set::remove()
set::contains()

boolean::and()
boolean::or()
boolean::xor()

*/
