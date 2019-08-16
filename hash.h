#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#ifdef _cplusplus
extern 'C'{
#endif
const int PrimeSize= 28;
static const unsigned long PrimeList[PrimeSize] = {
                                                //ul代表这个数是unsigned long
                                                53ul, 97ul, 193ul, 389ul, 769ul,
                                                1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
                                                49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
                                                1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
                                                50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
                                                1610612741ul, 3221225473ul, 4294967291ul};


typedef struct hashtable HashTable;
typedef unsigned int(*HashFunc)(unsigned long , void* );

HashTable *hashCreate(size_t key_size, size_t val_size, HashFunc hash_func, int (*equal)(void*, void*));  //Create a Hash Table
void hashDestroy(HashTable* table);  //Destroy the table
void hashPut(HashTable* table, void* key, void* val);   //Put an entry into Hash Table
void *hashGet(HashTable* table, void* key);               //Get an entry by key
int hashContains(HashTable* table, void* key);           //Dose the table contains an entry
void hashRemove(HashTable* table, void* key);            //Remove an entry from the table
int hashIsEmpty(HashTable* table);                          //Is the table empty
int hashSize(HashTable* table);                              //Get the size of the table
void hashPrint(HashTable* table, void(*print)(void* )); //Print a table

#ifdef _cplusplus
}
#endif
#endif // HASH_H_INCLUDED
