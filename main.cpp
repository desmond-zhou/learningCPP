//
// Created by Desmond on 3/7/2022.
//

#include <iostream>
#include <cstring>

class DesmondHashTable {
public:
    struct Item {
        char *key;
        char *value;
    };

    struct HashTable {
        Item **items;
        int size;
        int count;
    };


    static unsigned long hash(const char *input) {
        unsigned long accumulator = 0;
        for (int index = 0; input[index] != 0; index++) accumulator += input[index];
        return accumulator % CAPACITY;
    }

    static Item *create_item(char *key, char *value) {
        Item *item = (Item *) malloc(sizeof(Item));
        item->key = (char *) malloc(strlen(key) + 1);
        item->value = (char *) malloc(strlen(value) + 1);

        strcpy(item->key, key);
        strcpy(item->value, value);

        return item;
    }

    static HashTable *create_table(int size) {
        auto *table = (HashTable *) malloc(sizeof(HashTable));
        table->size = size;
        table->count = 0;
        table->items = (Item **) calloc(table->size, sizeof(Item *));
        for (int i = 0; i < table->size; i++) table->items[i] = nullptr;
        return table;
    }

    static void free_item(Item *item) {
        free(item->key);
        free(item->value);
        free(item);
    }

    static void free_table(HashTable *table) {
        for (int i = 0; i < table->size; i++) {
            Item *item = table->items[i];
            if (item != nullptr) free_item(item);
        }
        free(table->items);
        free(table);
    }

    static void handle_collision(HashTable *table, Item *item) {

    }

    static void insert(HashTable *table, char *key, char *value) {
        Item *new_item = create_item(key, value);
        unsigned long index = hash(key);
        Item *existing_item = table->items[index];

        if (existing_item == nullptr) {
            if (table->count == table->size) {
                printf("Insert error, table is full. \n");
                return;
            }

            table->items[index] = new_item;
            table->count++;
        } else {
            char *existing_key = existing_item->key;
            if (strcmp(existing_key, key) == 0) {
                strcpy(existing_item->value, value);
                return;
            } else {
                handle_collision(table, new_item);
                return;
            }
        }
    }

    static char *search(HashTable *table, char *key) {
        unsigned int index = hash(key);
        Item *item = table->items[index];
        if (item != nullptr) {
            if (strcmp(item->key, key) == 0) return item->value;
        }
        return nullptr;
    }

    static const int CAPACITY = 50000;
};

int main() {
    auto table = DesmondHashTable::create_table(DesmondHashTable::CAPACITY);
    DesmondHashTable::insert(table, "key1", "value1");
    char *result = DesmondHashTable::search(table, "key1");
    printf(result);
    return 0;
}
