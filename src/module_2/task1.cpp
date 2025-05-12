#include <iostream>
#include <vector>
#include <string>


const size_t INITIAL_SIZE = 8;
const double MAX_LOAD_FACTOR = 0.75;


class StringHasher {
public:
    StringHasher(size_t prime = 71) : prime(prime) {}
    
    size_t operator()(const std::string& str) const {
        size_t hash = 0;
        for (char c : str) {
            hash = hash * prime + c;
        }
        return hash;
    }

private:
    size_t prime;
};


template <typename T, typename Hasher>
class HashTable {
public:
    HashTable(size_t initial_size = INITIAL_SIZE) 
        : size(0), deleted_count(0), table(initial_size, State::EMPTY), keys(initial_size) 
    {
    }

    bool Add(const T& key) {
        if (size + deleted_count >= table.size() * MAX_LOAD_FACTOR) {
            Rehash();
        }

        size_t h1 = hasher(key) % table.size();
        size_t h2 = (hasher2(key) % (table.size() - 1)) + 1;
        
        size_t first_deleted = table.size();
        size_t i = h1;
        
        for (size_t j = 0; j < table.size(); ++j) {
            if (table[i] == State::EMPTY) {
                break;
            } else if (table[i] == State::DELETED) {
                if (first_deleted == table.size()) {
                    first_deleted = i;
                }
            } else if (keys[i] == key) {
                return false;
            }
            i = (i + h2) % table.size();
        }

        if (first_deleted != table.size()) {
            i = first_deleted;
            deleted_count--;
        }

        keys[i] = key;
        table[i] = State::OCCUPIED;
        size++;
        return true;
    }

    bool Has(const T& key) const {
        size_t h1 = hasher(key) % table.size();
        size_t h2 = (hasher2(key) % (table.size() - 1)) + 1;
        size_t i = h1;
        
        for (size_t j = 0; j < table.size(); ++j) {
            if (table[i] == State::EMPTY) {
                return false;
            } else if (table[i] == State::OCCUPIED && keys[i] == key) {
                return true;
            }
            i = (i + h2) % table.size();
        }
        return false;
    }

    bool Delete(const T& key) {
        size_t h1 = hasher(key) % table.size();
        size_t h2 = (hasher2(key) % (table.size() - 1)) + 1;
        size_t i = h1;
        
        for (size_t j = 0; j < table.size(); ++j) {
            if (table[i] == State::EMPTY) {
                return false;
            } else if (table[i] == State::OCCUPIED && keys[i] == key) {
                table[i] = State::DELETED;
                size--;
                deleted_count++;
                return true;
            }
            i = (i + h2) % table.size();
        }
        return false;
    }

private:
    enum class State {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    void Rehash() {
        std::vector<State> new_table(table.size() * 2, State::EMPTY);
        std::vector<T> new_keys(new_table.size());
        
        for (size_t i = 0; i < table.size(); ++i) {
            if (table[i] == State::OCCUPIED) {
                const T& key = keys[i];
                size_t h1 = hasher(key) % new_table.size();
                size_t h2 = (hasher2(key) % (new_table.size() - 1)) + 1;
                size_t j = h1;
                
                while (new_table[j] == State::OCCUPIED) {
                    j = (j + h2) % new_table.size();
                }
                
                new_keys[j] = key;
                new_table[j] = State::OCCUPIED;
            }
        }
        
        table = std::move(new_table);
        keys = std::move(new_keys);
        deleted_count = 0;
    }

    std::vector<State> table;
    std::vector<T> keys;
    size_t size;
    size_t deleted_count;
    Hasher hasher;
    StringHasher hasher2;
};


void solve(std::istream &in, std::ostream &out) {
    HashTable<std::string, StringHasher> table;
    
    char op;
    std::string key;

    while (in >> op >> key) {
        switch (op) {
            case '?':
                out << (table.Has(key) ? "OK" : "FAIL") << "\n";
                break;
            case '+':
                out << (table.Add(key) ? "OK" : "FAIL") << "\n";
                break;
            case '-':
                out << (table.Delete(key) ? "OK" : "FAIL") << "\n";
                break;
        }
    }
}


int main() {
    solve(std::cin, std::cout);
    
    return 0;
}
