#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 2
#define MAX_MAPS 100
#define key_SIZE 100
#define hash_Size 10

typedef struct MAP
{
    char* key;
    int* val;
} MAP;


MAP* hashArr[hash_Size];
MAP* item;
MAP* deletedItem;

int hasher(char* key) {
    int hashtag = key[0];
    return hashtag % hash_Size;
}

MAP *search(int key) {
    int keyMan = key;

    while (hashArr[keyMan] != NULL) {
        if (hashArr[keyMan]->key != NULL && hasher(hashArr[keyMan]->key) == key) {
            return hashArr[keyMan];
        }
        ++keyMan;
        keyMan %= hash_Size;
    }

    return NULL;
}

void makeMap(char *key, int val, MAP *maps, int mapIndex) {

    maps[mapIndex].val = (int *)malloc(sizeof(int));
    maps[mapIndex].key = (char *)malloc(key_SIZE * sizeof(char));

    *(maps[mapIndex].val) = val;
    snprintf(maps[mapIndex].key, key_SIZE, "%s", key);

    printf("key: %s, value: %d\n", maps[mapIndex].key, *(maps[mapIndex].val));
}

void freeMap(MAP* map) {
    free(map->key);
    free(map->val);
    free(map);
}

/// @brief change main into another return type, vscode gets mad at me if i do so i wont
void main() {

    struct MAP maps[MAX_MAPS];

    makeMap("test", 2, maps, 0);
    makeMap("mamma", 3, maps, 1);

    char* keyToSearch = "test";
    int hello = hasher(keyToSearch);

    for (int i = 0; i < MAX_MAPS; i++) {
        int hash = hasher(maps[i].key);
        printf("Hash for key %s: %d\n", maps[i].key, hash);
    }

    MAP *foundMap = search(hello);

    if (foundMap != NULL)
    {
        printf("value for key %s: %d\n", foundMap->key, *(foundMap->val));
    } else {
        printf("key %s is not found\n", keyToSearch);
    }
    
    for (int i = 0; i < MAX_MAPS; i++) {
        freeMap(&maps[i]);
    }
}