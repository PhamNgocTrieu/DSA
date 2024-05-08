#ifndef MAP_H
#define MAP_H

#include "../List/List.h"

#define MAX_MAP_KEY_LEN		(50)

// map capacity
#define MAX_MAP_KEY_NUM		(20)
#define MAX_MAP_VALUE_NUM	(20)

typedef enum {
	MAP_OK = 0,
	MAP_ERROR,
	MAP_FULL,
	MAP_EMPTY,
	MAP_KEY_NOT_FOUND,
	MAP_VALUE_NOT_FOUND,
	MAP_KEY_ALREADY_EXIST,
	MAP_VALUE_ALREADY_EXIST,
	MAP_KEY_NOT_EXIST,
	MAP_VALUE_NOT_EXIST,
}MSTATUS;

struct Map_Entry {
	char key[MAX_MAP_KEY_LEN];
	void *value;
	list_head hlist;
	int used;
	List list;
};

struct Map {
	MSTATUS (*init)(void);
	MSTATUS (*insert)(const char *key, void *value);
	void (*erase)(const char *key);
	int  (*empty)(void);
	size_t (*size)(void);
	void *(*find)(const char *key);
};

const struct Map *get_map_ops(void);

#endif /* MAP_H */