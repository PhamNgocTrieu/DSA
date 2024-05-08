# Hash Map Implementation in C

This is a simple hash map implementation in C, utilizing the list library.

## Features

- Insert elements into the map
- Find elements in the map

## Files

- `Map.h`: Header file containing the map definitions and function prototypes.
- `Map.c`: Source file containing the map implementation.

## Map Operations

The following operations are supported:

- `Map_Init`: Initializes the map.
- `insert`: Inserts a new entry after a specified position.
- `find`: Finds an entry in the map.

## Usage

1. Include `Map.h` in your source file.
2. Initialize a map using `get_map_ops()`.
3. Perform list operations as needed using the provided functions.

## Example

```c
#include "Map.h"

struct my_struct {
	int a;
	int b;
	int c;
};

struct my_struct instances[10];

int main() {
	const struct Map *map = get_map_ops();

	for (int i = 0; i < 10; i++) {
		instances[i].a = i + 1;
		instances[i].b = i + 1;
		instances[i].c = i + 1;
	}

	int ret = 0;

	ret = map->init();
	if (ret == MAP_OK) {
		ret = map->insert("key1", (void *)&instances[0]);
		ret = map->insert("key2", (void *)&instances[1]);
	}

	struct my_struct *p = NULL;

	p =	map->find("key3");
	
	if (p) {
		printf("%d %d %d\n", p->a, p->b, p->c);
	}
	else
		fprintf(stderr, "key not found");

	return 0;
}