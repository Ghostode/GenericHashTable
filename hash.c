#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"hash.h"

typedef struct hash_node{
    void* key;
    void* val;
    Entry* next;
}Entry;

struct hashtable{
    size_t key_size;
    size_t val_size;
    HashFunc hash_func;
    int (*equal)(void*, void*);
    unsigned int size;
    unsigned long capacity;
    int capIndex;
    Entry **bucket;
};

static Entry* entryCreate(HashTable* table, void* key, void* val){
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    if(NULL == entry){
        printf("Entry MALLOC FAILED!\n");
        return NULL;
    }
    entry->next = NULL;
    entry->key = malloc(table->key_size);
    memcpy(entry->key, key, table->key_size);
    entry->val = malloc(table->val_size);
    memcpy(entry->val, val, table->val_size);

    return entry;
}

static Entry** getBucket(HashTable* table, void* key){
    int index = table->hash_func(table->capacity, key);
    if(index >= table->capacity) {
        printf("INDEX ERROR\n");
        exit(0);
    }
    return &(table->bucket[index]);
}

HashTable* hashCreate(size_t key_size, size_t val_size, HashFunc hash_func, int (*equal)(void*, void*)){
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if(NULL == table){
        printf("TABLE MALLOC FAILED!\n");
        return NULL;
    }
    int i;
    table->key_size = key_size;
    table->val_size = val_size;
    table->hash_func = hash_func;
    table->equal = equal;
    table->size = 0;
    table->capIndex = 0;
    table->capacity = PrimeList[capIndex];
    table->bucket = (Entry**)malloc(sizeof(Entry*)*table->capacity);
    for(i = 0; i < table->capacity; i++)
        table->bucket[i] = NULL;

    return table;
}  //Create a Hash Table

void hashPut(HashTable* table, void* key, void* val){
    if(NULL == table){
        printf("NO TABLE TO PUT\n");
        return;
    }
    if(!hashContains(table, key)){
        Entry* entry = entryCreate(table, key, val);
        if(NULL == entry){
            printf("PUT FAILED\n");
            return;
        }
        Entry** bucket = getBucket(table, key);
        entry->next = *bucket;
        *bucket = entry;
        table->size++;
    }
    else{
        void* val_dest = hashGet(table, key);
        memcpy(val_dest, val, table->val_size);
    }
}   //Put an entry into Hash Table

void *hashGet(HashTable* table, void* key){
    if(NULL == table){
        printf("NO TABLE TO GET\n");
        return NULL;
    }
    if(hashIsEmpty(table)){
        printf("EMPTY TABLE\n");
        return NULL;
    }

    Entry** bucket = getBucket(table, key);
    Entry* tmp = *bucket;
    if(NULL == tmp){
        prinf("NO THIS ENTRY\n");
        return NULL;
    }
   while(tmp != NULL ){
        if(table->equal(tmp->key, key))
            return tmp->val;
        tmp = tmp->next;
    }
    return NULL;

}               //Get an entry by key

int hashContains(HashTable* table, void* key){
    if(NULL == table){
        printf("NO TABLE TO OPERATE\n");
        return 0;
    }
    if(hashIsEmpty(table)){
        printf("EMPTY TABLE\n");
        return 0;
    }
    Entry** bucket = getBucket(table, key);
    Entry* tmp = *bucket;
    if(NULL == tmp) return 0;
    while(tmp != NULL ){
        if(table->equal(tmp->key, key))
            return 1;
        tmp = tmp->next;
    }
    return 0;
}           //Dose the table contains an entry

void hashRemove(HashTable* table, void* key){
    if(NULL == table){
        printf("NO TABLE TO REMOVE\n");
        return ;
    }
    if(hashIsEmpty(table)){
        printf("EMPTY TABLE\n");
        return ;
    }
    if(!hashContains(table, key)){
        prinf("NO THIS ENTRY\n");
        return ;
    }
    Entry** bucket = getBucket(table, key);
    Entry* tmp = *bucket;
    Entry* prev = tmp;
    int count = 0;
    while(tmp != NULL ){
        if(table->equal(tmp->key, key)){
            prev->next = tmp->next;
            free(tmp->key);
            free(tmp->val);
            free(tmp);
            if(!count) *bucket = NULL;
            table->size--;
            return;
        }
        prev = tmp;
        tmp = tmp->next;
        count++;
    }
    prinf("NO THIS ENTRY\n");
}            //Remove an entry from the table

int hashIsEmpty(HashTable* table){
    if(NULL == table){
        printf("NO TABLE\n");
        return 0;
    }
    return 0 == table->size;
}                          //Is the table empty

int hashSize(HashTable* table){
    if(NULL == table){
        printf("NO TABLE\n");
        return 0;
    }
    return table->size;
}                              //Get the size of the table

void hashPrint(HashTable* table, void(*print)(void* )){
    if(NULL == table){
        printf("NO TABLE\n");
        return ;
    }
    if(hashIsEmpty(table)){
        printf("EMPTY TABLE\n");
        return;
    }
    for(i = 0; i<table->capacity; i++){
        Entry* tmp = table->bucket[i];
        while(tmp){
            print(tmp->val);
            tmp = tmp->next;
        }
    }
} //Print a table

void hashDestroy(HashTable* table){
    if(NULL == table){
        printf("NO TABLE\n");
        return ;
    }
    for(i = 0; i<table->capacity; i++){
        Entry* tmp = table->bucket[i];
        Entry* next;
        while(tmp){
            next = tmp->next;
            free(tmp->key);
            free(tmp->val);
            free(tmp->data);
            tmp = next;
        }
    }
    free(table);
    table = NULL;
}  //Destroy the table
