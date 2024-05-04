# Doubly Linked List Implementation in C

This is a simple doubly linked list implementation in C, inspired by the list functionality in the Linux kernel. It provides basic operations to manipulate and traverse a linked list.

## Features

- Insert elements into the list
- Push elements to the back of the list
- Push elements to the front of the list
- Pop elements from the back of the list
- Pop elements from the front of the list
- Check if the list is empty

## Files

- `list.h`: Header file containing the list definitions and function prototypes.
- `list.c`: Source file containing the list implementation.

## List Operations

The following operations are supported:

- `List_Create`: Initializes the list.
- `insert`: Inserts a new entry after a specified position.
- `push_back`: Adds a new entry to the end of the list.
- `push_front`: Adds a new entry to the beginning of the list.
- `pop_back`: Removes the last entry from the list.
- `pop_front`: Removes the first entry from the list.
- `empty`: Checks if the list is empty.

## Usage

1. Include `list.h` in your source file.
2. Simply add the `list_head` struct to your structure.
3. Initialize a list using `List_Create`.
4. Perform list operations as needed using the provided functions.

## Example

```c
#include "List.h"

typedef struct {
  int data;
  list_head list;
} my_data;

int main() {
    my_data eg[5] = {
        {0},
        {0},
        {0},
        {0},
        {0}
    };

    List my_list = {0};
    list_head hlist;
    List *p = &my_list;
    p->head = &hlist;

    List_Create(p);

    for (int i = 0; i < 5; i++) {
        eg[i].data = i;
        p->push_front(p, &eg[i].list);
    }

    my_data *pos = NULL;
    list_for_each_entry(pos, p->head, list) {
        printf("%d ", pos->data);
    }

    return 0;
}
