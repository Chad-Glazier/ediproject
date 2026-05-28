# To-do

- Implement the interface.
- Figure out why the search is slow. The possible problems are listed below
  (checked items have already been investigated and found unproblematic).
  - [x] `kmindist`, the static evaluation function.
  - [x] `get_children`, the function that gets successor states.
  - [x] `out_of_time`, the frequent time-checking.
  - [ ] `alpha_beta`, the actual recursive search function.
  - try rewriting the search to avoid heap allocations, instead using a
    fixed-size array of child states. Make a `set_children` function that takes
    a pointer to a (stack-allocated) array of states and returns the number of
    states actually computed.

```c
uint16 set_children(State* dst) {
    // ...
}
```

Also, use 

```c
sizeof(MyStruct)
_Alignof(MyStruct)
offsetof(MyStruct, field)
```

to optimize the memory of the state object.
