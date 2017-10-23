# Exercise 1
The result's type is _int_. 0 corresponds to _false_ and 1 corresponds to _true_.

# Exercise 2
Their value and type is the same as the relational operator.

# Exercise 3
Short evaluation. They stop evaluating the expression as soon as the result can be determined for sure.

# Exercise 4
_switch_ statements execute sequentially. This means if the first case is true, and no _break_ is present, the other cases are executed as well. _break_ makes sure just one case is considered. When it is executed, then _break_ jumps at the end of the _switch_ statement.

# Exercise 5
_continue_ is used for loops and makes another iteraction start. This does not apply at _switch_ statements, since there are no iterations. 

# Exercise 6
It will jump immediately to the loop's guard, without modifying the values of some maybe useful variables.

# Exercise 7
It is not possible to use _goto_ for such jumps since the scope of a label does not extend beyond a function. In other words, labels are local.
