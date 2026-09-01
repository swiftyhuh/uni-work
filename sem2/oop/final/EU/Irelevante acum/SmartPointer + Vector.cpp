template <typename T> class SmartPointer {
private:
  T *ptr;

public:
  SmartPointer(T *p = nullptr) : ptr(p) {}
  SmartPointer(const SmartPointer &other) {
    ptr = (other.ptr ? new T(*other.ptr) : nullptr);
  }
  SmartPointer &operator=(const SmartPointer &other) {
    if (this != &other) {
      delete ptr;
      ptr = (other.ptr ? new T(*other.ptr) : nullptr);
    }
    return *this;
  }
  ~SmartPointer() { delete ptr; }
  T &operator*() const { return *ptr; }
  T *get() const { return ptr; }
  bool operator==(const SmartPointer &other) const {
    if (!ptr || !other.ptr)
      return false;
    return *ptr == *other.ptr;
  }
};
template <typename T> class Vector {
private:
  vector<T> elems;

public:
  Vector &add(const T &elem) {
    elems.push_back(elem);
    return *this;
  }
  Vector operator-(const T &elem) const {
    Vector result;
    bool found = false;
    for (const auto &e : elems) {
      if (!found && e == elem) {
        found = true;
      } else {
        result.elems.push_back(e);
      }
    }
    if (!found) {
      throw runtime_error("Element does not exist!");
    }
    return result;
  }
  auto begin() { return elems.begin(); }
  auto end() { return elems.end(); }
  auto begin() const { return elems.begin(); }
  auto end() const { return elems.end(); }
};
