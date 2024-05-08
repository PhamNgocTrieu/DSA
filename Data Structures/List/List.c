#include <stdio.h>
#include "List.h"                                                                                                                                                                                                                                              

/* Constructor */
static LSTATUS List_Init(
    List *const me,
    LSTATUS (*insert_fnc)(list_head *new, list_head *prev, list_head *next),
    LSTATUS (*push_back_fnc)(List *const me, list_head *new),
    LSTATUS (*push_front_fnc)(List *const me, list_head *new),
    void (*pop_back_fnc)(List *const me),
    void (*pop_front_fnc)(List *const me),
	void (*erase_fnc)(list_head *const pos),
    int (*empty_fnc)(List *const me)) {
    if (!me) {
        fprintf(stderr, "Warning: NULL pointer\n");
        return LIST_NULL_POINTER;
    }
    me->head->next = me->head;
    me->head->prev = me->head;

    /* initialize function pointers */
    me->insert = insert_fnc;
    me->push_back = push_back_fnc;
    me->pop_back = pop_back_fnc;
    me->push_front = push_front_fnc;
	me->erase = erase_fnc;
    me->empty = empty_fnc;

    return LIST_SUCCESS;
}

static int __list_add_valid(list_head *new, list_head *prev, list_head *next) {
    if (next->prev == prev && prev->next == next && new != prev &&new != next)
        return 1;
    return 0;
}

static LSTATUS List_Insert(list_head *new, list_head *prev, list_head *next) {
    if (!__list_add_valid(new, prev, next)) {
        fprintf(stderr, "Error: Cannot Add the new node into the list\n");
        return LIST_ERROR;
    }

    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;

    return LIST_SUCCESS;
}
/* Add a new entry at the end of the list */
static LSTATUS List_Push_Back(List *const me, list_head *new) {
    return List_Insert(new, me->head->prev, me->head);
}

/* Add a new entry at the beginning of the list */
static LSTATUS List_Push_Front(List *const me, list_head *new) {
  return List_Insert(new, me->head, me->head->next);
}

static int List_Empty(List *const me) { 
    return (me->head->next == me->head);    
}

static inline int __list_del_entry_valid(list_head *entry) {
	return (entry->prev->next == entry && entry->next->prev == entry);
}

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 */
static inline void __list_del(list_head *prev, list_head *next) {
	next->prev = prev;
	prev->next = next;
}

static inline void __list_del_entry(list_head *entry) {
	if (!__list_del_entry_valid(entry))
		return;
	__list_del(entry->prev, entry->next);
}
/* Delete entry from the list */
static inline void List_Del(list_head *entry) {
	__list_del_entry(entry);
	entry->next = NULL;
	entry->prev = NULL;
}

/* Delete entry at the end the list */
static void List_Pop_Back(List *const me) { 
	List_Del(me->head->prev);
}

/* Delete entry at the beginning the list */
static void List_Pop_Front(List *const me) { 
	List_Del(me->head->next);
}

void List_Create(List *const me) {
  List_Init(me, List_Insert, List_Push_Back, List_Push_Front, List_Pop_Back,
            List_Pop_Front, List_Del, List_Empty);
}