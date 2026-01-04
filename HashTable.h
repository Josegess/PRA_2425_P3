#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../../prg1/PRA_2526_P1/ListLinked.h" 

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>** table;

        int h(std::string key) {
            int sum = 0;
            for (size_t i = 0; i < key.length(); i++) {
                sum += int(key.at(i));
            }
            return sum % max;
        }

    public:
        HashTable(int size) {
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>*[max];
            for (int i = 0; i < max; i++) {
                table[i] = new ListLinked<TableEntry<V>>();
            }
        }

        ~HashTable() {
            for (int i = 0; i < max; i++) {
                delete table[i];
            }
            delete[] table;
        }

        int capacity() {
            return max;
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
            out << "================" << std::endl;
            for (int i = 0; i < th.max; i++) {
                out << "== Cubeta " << i << " ==" << std::endl;
                out << *(th.table[i]) << std::endl;
            }
            out << "================";
            return out;
        }

        V operator[](std::string key) {
            return search(key);
        }

        void insert(std::string key, V value) override {
            int pos = h(key);
            TableEntry<V> entry(key, value);
            
            if (table[pos]->search(entry) != -1) {
                throw std::runtime_error("Key '" + key + "' already exists in the dictionary.");
            }
            
            table[pos]->prepend(entry);
            n++;
        }

        V search(std::string key) override {
            int pos = h(key);
            TableEntry<V> entry(key);
            int idx = table[pos]->search(entry);
            
            if (idx == -1) {
                throw std::runtime_error("Key '" + key + "' not found.");
            }
            
            return table[pos]->get(idx).value;
        }

        V remove(std::string key) override {
            int pos = h(key);
            TableEntry<V> entry(key);
            int idx = table[pos]->search(entry);
            
            if (idx == -1) {
                throw std::runtime_error("Key '" + key + "' not found.");
            }
            
            V val = table[pos]->get(idx).value;
            table[pos]->remove(idx);
            n--;
            return val;
        }

        int entries() override {
            return n;
        }
};

#endif
