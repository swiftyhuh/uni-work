class Person {
private:
    int age;
    string name;
public:
    Person(int a, string n) : age(a), name(n) {}
    friend ostream& operator<<(ostream& os, const Person& p) {
        os << p.name << " is " << p.age << " years old";
        return os;
    }
    bool operator==(const Person& other) const {
        return age == other.age && name == other.name;
    }
};

template <typename K, typename V>
class MultiDictionary {
private:
    map<K, vector<V>> data;
public:
    MultiDictionary() {}
    MultiDictionary& add(K key, V value) {
        data[key].push_back(value);
        return *this;
    }
    MultiDictionary& erase(K key, V value) {
        if (data.find(key) == data.end())
            throw runtime_error("Key does not exist!");
        auto& vec = data[key];
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (*it == value) {
                vec.erase(it);
                if (vec.empty()) data.erase(key);
                return *this;
            }
        }
        throw runtime_error("Given value does not exist for given key!");
    }
    void print(ostream& os) const {
        for (const auto& [key, values] : data)
            for (const auto& v : values)
                os << key << " " << v << "; ";
        os << endl;
    }
    int sizeForKey(K key) const {
        auto it = data.find(key);
        if (it == data.end()) return 0;
        return it->second.size();
    }
};


