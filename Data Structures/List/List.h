#ifndef LISH_H
#define LISH_H

#include <stdio.h>
// #include <stddef.h> // for offsetof macro

typedef enum {
LIST_SUCCESS = 0,
LIST_ERROR,
LIST_EMTPY,
LIST_NOT_FOUND,
LIST_NULL_POINTER,
LIST_OUT_OF_MEMORY,
LIST_FULL
} LSTATUS;

typedef struct list_head {
struct list_head *next, *prev;
} list_head;

typedef struct List List;
struct List {
list_head *head;
LSTATUS (*insert)(list_head *new, list_head *prev, list_head *next);
LSTATUS (*push_back)(List *const me, list_head *new);
LSTATUS (*push_front)(List *const me, list_head *new);
LSTATUS (*pop_back)(List *const me);
LSTATUS (*pop_front)(List *const me);
int (*empty)(List *const me);
};

void List_Create(List *const me);

/**
 * list_is_head - tests whether @list is the list @head
 * @list: the entry to test
 * @head: the head of the list
 */
// static inline int list_is_head(const struct list_head *list, const struct list_head *head)
// {
// 	return list == head;
// }
#define list_is_head(list, head) \
    ((list) == (head))

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
// static inline int list_empty(struct list_head *head) {
//     return head->next == head;
// }
#define list_empty(head) \
    ((head)->next == (head))

/**
 * offsetof - get the offset of a member in a struct type
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define offsetof(type, member) ((size_t)&((type *)0)->member)

/**
 * container_of - get the container struct of the list_head member within the list struct
 * @ptr:    the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define container_of(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the struct.
 */
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_head within the struct.
 */
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; !list_is_head(pos, (head)); pos = pos->next)

/**
 * list_for_each_prev	-	iterate over a list backwards
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each_prev(pos, head) \
	for (pos = (head)->prev; !list_is_head(pos, (head)); pos = pos->prev)

/**
 * list_first_entry_or_null - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_head within the struct.
 *
 */
#define list_first_entry_or_null(ptr, type, member) \
    (!list_empty(ptr) ? list_first_entry(ptr, type, member) : NULL)

/**
 * list_entry_is_head - test if the entry points to the head of the list
 * @pos:	the type * to cursor
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_entry_is_head(pos, head, member)				\
	list_is_head(&pos->member, (head))

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_head within the struct.
 */
#define list_for_each_entry(pos, head, member)                  \
    for (pos = list_first_entry(head, typeof(*pos), member);   \
        !list_entry_is_head(pos, head, member);                 \
        pos = list_next_entry(pos, member))

#endif /* LISH_H */