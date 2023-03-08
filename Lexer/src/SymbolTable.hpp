#include <map>
#include <iostream>

template <class K, class V>
class SymbolTable {
  private:
    std::map<K, V> table;
    SymbolTable* father;

  public:
    SymbolTable(SymbolTable* father = NULL) {
      this->father = father;
      this->table = std::map<K, V>();
    };

    SymbolTable* createSubSope() {
      SymbolTable* subscope = new SymbolTable(this);
      return subscope;
    };

    bool symbolExists(K symbol) {
      if (this->father == NULL) {
        return table.find(symbol) != table.end();
      } else {
        return table.find(symbol) != table.end() || father->symbolExists(symbol);
      }
    };

    void addSymbol(K key, V value) {
      table[key] = value;
    };

    V get(K symbol) {
      if (table.find(symbol) != table.end())
        return table[symbol];
      else 
        return *new V;
    }

    SymbolTable<K, V>* superScope() {
      return father;
    }
};