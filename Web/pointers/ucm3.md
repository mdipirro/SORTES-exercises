# System Architecture UCM3

These exercises are taken from [here](http://www.it.uc3m.es/pbasanta/asng/course_notes/pointer_problems_en.html).

## Exercise 1
100 + 4 + 4 + 4 = 112

## Exercise 2
The former since its size is 112 bytes, while the latter occupies only 4 bytes (it is a pointer).

## Exercise 3
They all have the same size, which is a pointer's size: 4 bytes.

## Exercise 4
- `name` -> 100
- `identifier` -> 200
- `signal_quality` -> 204
- `carrier_ptr` -> 208

## Exercise 5
The same as **Exercise 4**.

## Exercise 6
`struct cell_information **c_ptr;` becomes `struct cell_information *c_ptr;`.

## Exercise 7
Yes, they can.

## Exercise 8
No, it's not. The two declarations are correct, but the assignment should be `c_ptr = &c;`.

## Exercise 9
Since `carrier_ptr` has type `struct information_carrier*`, the type of `&c.carrier_ptr` is `struct information_carrier**`.

## Exercise 10
1. `data1.c` **30**
2. `data_ptr->c` **30**
3. `data_ptr.c`	**Incorrect**, `data_ptr` is a pointer
4. `data1.next->b` **20**
5. `data_ptr->next->b` **20**
6. `data_ptr.next.b` **Incorrect**, `data_ptr` is a pointer
7. `data_ptr->next.b` **Incorrect**, `data_ptr -> next` is a pointer
8. `(*(data_ptr->next)).b` **20**
9. `data1.next->next->a` **10**
10. `data_ptr->next->next.a` **Incorrect**, `data_ptr -> next -> next` is a pointer
11. `data_ptr->next->next->a` **10**
12. `data_ptr->next->a` **Incorrect**, field `a` is not present in `struct pack2`
13. `data_ptr->next->next->b`**Incorrect**, field `b` is not present in `struct pack1`

## Exercise 11
1. `c.ctr_pointer = &carrier`
2. `c_ptr -> ctr_pointer = &carrier`
3. `c.ctr_pointer = car_ptr`
4. `c_ptr -> ctr_pointer = car_ptr`

## Exercise 12
```c
#define CELLS 10

struct exercise12 {
    struct cell_information cells[CELLS]; // to store cells' info
    int used_cells; // size of the cells array
};
```

## Exercise 13
```c
struct exercise12 cells_info;
for (int i = 0; i < CELLS; i++) {
    cells_info.cells[i].carrier_ptr = NULL;
}
cells_info.used_cells = CELLS;
```

## Exercise 14
Either a pointer to the cell or the position in the `cells` array.

## Exercise 15
Its size is 112 bytes as before. A pointer occupies the same space, no matter if it points to NUll or to a concrete memotu locaton.

## Exercise 16
```c
void fill_in(cell_information* data, unsigned int id, float sq, info_carrier_ptr carr_ptr) {
    data -> id = id;
    data -> signal_quality = sq;
    data -> carrier_ptr = carr_ptr;
}
```
Since the function takes as a parameter a pointer there is no need to return the modified value. The functions writes over te memory location pointed to by `data`.

## Exercise 17
Because the second uses a pointer to the data structure and modifies the value pointed to by that argument, while the first takes a copy of the data structure. In both cases pass-by-value is applied, but in the former a struct copy is made (no pointers involved), while in the latter the struct's address is copied.

## Exercise 18
112000 for the former, 400 for the latter. The difference is the following: the former is an array of 100 elements occupying 112 bytes, the latter is an array of 100 pointers.

## Exercise 19
`picture_info`'s size is 104 bytes, supposing `SIZE_NAME` to be equal to 100.

## Exercise 20
A possible solution would be memorizing the two sorted tables (by longitude and latitude) and return them when needed.