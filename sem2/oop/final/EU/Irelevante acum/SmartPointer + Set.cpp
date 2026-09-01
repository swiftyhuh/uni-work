template <typename T>
class SmartPointer {
private:
    T* ptr;
public:
    SmartPointer(T* p = nullptr) : ptr(p) {}
    SmartPointer(const SmartPointer& other) {
        ptr = (other.ptr ? new T(*other.ptr) : nullptr);
    }
    SmartPointer& operator=(const SmartPointer& other) {
        if (this != &other) {
            delete ptr;
            ptr = (other.ptr ? new T(*other.ptr) : nullptr);
        }
        return *this;
    }
    ~SmartPointer() { delete ptr; }
    T& operator*() const { return *ptr; }
    T* get() const { return ptr; }
    bool operator==(const SmartPointer& other) const {
        if (!ptr || !other.ptr) return false;
        return *ptr == *other.ptr;
    }
};
template <typename T>
class Set {
private:
    vector<T> elems;
public:
    Set operator+(const T& elem) const {
        for (const auto& e : elems) {
            if (e == elem)
                throw std::runtime_error("Element already exists!");
        }
        Set result = *this;
        result.elems.push_back(elem);
        return result;
    }
    Set& remove(const T& elem) {
        for (auto it = elems.begin(); it != elems.end(); ++it) {
            if (*it == elem) {
                elems.erase(it);
                return *this;
            }
        }
        throw std::runtime_error("Element does not exist!");
        return *this;
    }
    auto begin() { return elems.begin(); }
    auto end()   { return elems.end(); }
};
