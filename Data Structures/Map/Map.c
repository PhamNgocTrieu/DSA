#include "Map.h"
#include <stdio.h>
#include <string.h>

/* define the pool for map entry statically (I don't want to use dynamic allocation :D) */
struct Map_Entry mTable[MAX_MAP_KEY_NUM];
struct Map_Entry mEntry_Pool[MAX_MAP_VALUE_NUM];
// const struct List *list[MAX_MAP_KEY_NUM];

/* Size of the map */
static size_t mSize = 0;

/**
 * __hash_func - hash function for map key
 * @key: key to be hashed
 * @return: hash value
*/
unsigned int __hash_func(const char *key) {
	unsigned int hash = 0;
	while (*key) {
		hash = hash + 99 + *key++;
	}
	return hash % MAX_MAP_KEY_NUM;
}

/**
 * Map_Init - Initialize the map
 * @return: MAP_OK if success, MAP_ERROR if fail
*/
static MSTATUS Map_Init(void) {
	int i, j;

	if (MAX_MAP_KEY_NUM > 0 || MAX_MAP_VALUE_NUM > 0) {

		for (i = 0; i < MAX_MAP_KEY_NUM; i++) {
			// printf("%p \n",&mTable[i].hlist);
			mTable[i].list.head = &(mTable[i].hlist);
			// printf("%p \n", mTable[i].list.head);
			List_Create(&(mTable[i].list));
		}
		return MAP_OK;
	}
	return MAP_ERROR;
}

/**
 * __key_exist - check if the key exist in the hash table.
*/
static struct Map_Entry *__key_exist(struct Map_Entry *pos, unsigned int hash_index, const char *key) {
	list_for_each_entry(pos, mTable[hash_index].list.head, hlist) {
		if (strcmp(pos->key, key) == 0) {
			return pos;
		}
	}
	return NULL;
}

/**
 * Map_Insert - Insert a new key-value pair into the map
 * @key: The key to insert
 * @value: The value to insert
 * @return: OK if successful, ERROR if not
 * 
 * This function inserts a new key-value pair into the map.
 * If the key already exists, the value is updated.
 * If the key does not exist, a new entry is created.
*/
static MSTATUS Map_Insert(const char *key, void *value) {
	int i, j;
	unsigned int hash_index = __hash_func(key);
	struct Map_Entry *p_mKey = NULL;
	struct Map_Entry *p_mNewEntry = NULL;

	p_mKey = __key_exist(p_mKey, hash_index, key);

	/* if the key does not exist */
	if (!p_mKey) {
		for (j = 0; j < MAX_MAP_VALUE_NUM; j++) {
			if (mEntry_Pool[j].used == 0) {
				p_mNewEntry = &mEntry_Pool[j];
				break;
			}
		}

		if (!p_mNewEntry) {
			fprintf(stderr, "Map_Insert: No available value entry pool\n");
			return MAP_FULL;
		}
	}
	else {
		p_mNewEntry = p_mKey;
	}
	// insert new entry
	p_mNewEntry->used = 1;
	strcpy(p_mNewEntry->key, key);
	p_mNewEntry->value = value;
	p_mNewEntry->used = 1;

	if (!p_mKey) {
		mTable[hash_index].list.push_back(&mTable[hash_index].list, &p_mNewEntry->hlist);
	}

	mSize += 1;

	return MAP_OK;
}

/**
 * Map_Find - Find the value of the key
 * @key: The key
 * @return: The value of the key
*/
static void *Map_Find(const char *key) {
	unsigned int hash_index = __hash_func(key);

	struct Map_Entry *p_mEntry = NULL;
	
	p_mEntry = __key_exist(p_mEntry, hash_index, key);

	return p_mEntry->value;
}

/**
 * Map_Erase - Erase the key and value from the map
 * @key: The key to be erased
*/
static void Map_Erase(const char *key) {
	unsigned int hash_index = __hash_func(key);

	struct Map_Entry *p_mEntry;

	list_for_each_entry(p_mEntry, mTable[hash_index].list.head, hlist) {
		if (strcmp(p_mEntry->key, key) == 0) {
			p_mEntry->used = 0;
			mTable[hash_index].list.erase(&p_mEntry->hlist);
			mSize--;
			break;
		}
	}
}

/**
 * Map_Empty - Check if the map is empty.
*/
static int Map_Empty(void) {
	return mSize == 0;
}

/**
 * Map_Size - Get the size of the map.
*/
static size_t Map_Size(void) {
	return mSize;
}

/**
 * struct Map - Map operations.
*/
const struct Map map_ops = {
	.init = Map_Init,
	.insert = Map_Insert,
	.find = Map_Find,
	.erase = Map_Erase,
	.empty = Map_Empty,
	.size = Map_Size,
};

/**
 * get_map_ops - Get the map operations.
*/
const struct Map *get_map_ops(void) {
	return &map_ops;
}