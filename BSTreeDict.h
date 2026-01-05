#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        // Puntero al ABB que gestiona las entradas
        BSTree<TableEntry<V>>* tree; 

    public:
        // Constructor: crea un ABB vacío con memoria dinámica
        BSTreeDict() {
            tree = new BSTree<TableEntry<V>>();
        }

        // Destructor: libera la memoria del ABB
        ~BSTreeDict() {
            delete tree;
        }

        // Implementación de métodos abstractos de Dict<V>

        void insert(std::string key, V value) override {
            TableEntry<V> entry(key, value);
            // El propio BSTree lanzará runtime_error si la clave ya existe
            tree->insert(entry);
        }

        V search(std::string key) override {
            TableEntry<V> entry(key);
            // Buscamos la entrada y devolvemos su valor
            return tree->search(entry).value;
        }

        V remove(std::string key) override {
            TableEntry<V> entry(key);
            // Primero obtenemos el valor para devolverlo y luego eliminamos
            V val = tree->search(entry).value; 
            tree->remove(entry);
            return val;
        }

        int entries() override {
            return tree->size(); // Devuelve el número de nodos del árbol
        }

        // Sobrecarga de operadores adicionales

        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bsd) {
            out << *(bsd.tree); // Imprime el árbol (recorrido inorden)
            return out;
        }
};

#endif
