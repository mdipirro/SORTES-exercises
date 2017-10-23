# Exercise 1
```c
struct {
    int a, b;
};
```

# Exercise 2
It is of limited use because it cannot be referred to in the source code (it is untagged, so it has no name).

# Exercise 3
```c
struct int_struc {
    int a, b;
} x, y;
```

# Exercise 4
```c
struct int_struct z;
```

# Exercise 5
```c
p = &z;
p -> a = 0; // Or *p.a = 0;
```

# Exercise 6
Explicitly, such as ```struct x``` or implicitly, such as ```struct x *p;```.