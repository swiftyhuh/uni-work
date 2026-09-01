// using namespace std;
// #include <vector>
//
// template <typename T> class SmartPointer {
// private:
//   T *ptr;
//
// public:
//   SmartPointer(T *p = nullptr) : ptr(p) {} // Constructor
//   SmartPointer &operator=(SmartPointer &other) {
//     if (this != &other) {
//       delete ptr;
//       ptr = (other.ptr ? new T(*other.ptr) : nullptr);
//     }
//     return *this;
//   }
// };
//
// template <typename T> class Vector {
// private:
//   std::vector<T> elems;
// };

// SmartPointer + Set

// #include <iostream>
// #include <stdexcept>
// #include <string>
// #include <vector>
// using namespace std;
//
// template <typename T> class SmartPointer {
// private:
//   T *ptr;
//
// public:
//   // we use = nullptr because the cunstructor can be called with no arguments
//   SmartPointer(T *p = nullptr) : ptr(p) {}
//
//   // rule of three, destructor
//   ~SmartPointer() { delete ptr; }
//   // copy cunstructor
//   SmartPointer(const SmartPointer &other) {
//     ptr = (other.ptr ? new T(*other.ptr) : nullptr);
//   }
//   // assignment operator
//   SmartPointer &operator=(const SmartPointer &other) {
//     if (this != &other) {
//       delete ptr;
//       ptr = (other.ptr ? new T(*other.ptr) : nullptr);
//     }
//     return *this;
//   }
//
//   T &operator*() const { return *ptr; }
//
//   bool operator==(const SmartPointer &other) const {
//     if (!ptr || !other.ptr)
//       return false;
//     return *ptr == *other.ptr;
//   }
// };
//
// template <typename T> class Set {
// private:
//   vector<T> elems;
//
// public:
//   Set operator+(const T &elem) {
//     for (const auto &e : elems) {
//       if (e == elem)
//         throw std::runtime_error("Element already exists!");
//     }
//     Set result = *this;
//     result.elems.push_back(elem);
//     return result;
//   }
//   Set &remove(const T &elem) {
//     for (auto it = elems.begin(); it != elems.end(); it++) {
//       if (*it == elem) {
//         elems.erase(it);
//         return *this;
//       }
//     }
//     throw std::runtime_error("Element does not exist");
//   }
//
//   auto begin() { return elems.begin(); }
//   auto end() { return elems.end(); }
// };

// MyObjectList
// #include <iostream>
// #include <string>
// #include <vector>
//
// using namespace std;
// class Object {
// public:
//   virtual void print() = 0;
//   virtual ~Object() {}
// };
//
// class String : public Object {
// private:
//   string value;
//
// public:
//   String(string v) : value(v) {}
//   void print() override { cout << value << " "; }
//   string operator*() const { return value; }
//   bool operator==(const string &other) const { return value == other; }
// };
//
// class Integer : public Object {
// private:
//   int value;
//
// public:
//   Integer(int v) : value(v) {}
//   void print() override { cout << value << " "; }
// };
//
// class MyObjectList {
// private:
//   vector<Object *> elems;
//
// public:
//   MyObjectList() {}
//
//   MyObjectList &add(Object *obj) {
//     elems.push_back(obj);
//     return *this;
//   }
//   int length() const { return elems.size(); }
//
//   auto begin() { return elems.begin(); }
//   auto end() { return elems.end(); }
//   ~MyObjectList() {
//     for (auto o : elems)
//       delete o;
//   }
// };

// InfixExpression
// #include <stdexcept>
// #include <vector>
// using namespace std;
// template <typename T> class InfixEpression {
// private:
//   vector<T> history;
//
// public:
//   InfixEpression(T initial) { history.push_back(initial); }
//   InfixEpression &operator+(T val) const {
//     InfixEpression result = *this;
//     T newVal = result.history.back() + val;
//     return result;
//   }
//   InfixEpression operator-(T val) const {
//     InfixEpression result = *this;
//     T newVal = result.history.back() - val;
//   }
//
//   InfixEpression &undo() {
//     if (history.size() <= 1) {
//       throw std::runtime_error("Cannot do!");
//     }
//     history.pop_back();
//     return *this;
//   }
//
//   T value() const { return history.back(); }
// };

template <typename T>
class InfixEpression{
    private:
        vector<T> history;
    public:
        InfixExpression(T initial){
            history.push_back(initial);
        }
        InfixExpression &operator+(T val) const{
            InfixExpression result = *this;
            T newVal = result.history.back() + val;
            return result;
        }
        InfixExpression operator-(T val) const{
            InfixExpression result =*this;
            T newVal = result.history.back() - val;
        }



    // Complex + vector
    // #include <ostream>
    // #include <stdexcept>
    // #include <vector>
    // using namespace std;
    // class Complex {
    // private:
    //   double real, imaginary;
    //
    // public:
    //   Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    //
    //   Complex(const Complex &other)
    //       : real(other.real), imaginary(other.imaginary) {}
    //
    //   double getReal() const { return real; }
    //   double getImaginary() const { return imaginary; }
    //
    //   bool operator==(const Complex &other) const {
    //     return real == other.real && imaginary == other.imaginary;
    //   }
    //
    //   Complex operator/(double value) const {
    //     if (value == 0)
    //       throw std::runtime_error("Divosopm by zero!");
    //     return Complex(real / value, imaginary / real);
    //   }
    //
    //   friend ostream &operator<<(ostream &os, const Complex &obj) {
    //     os << obj.real << "+" << obj.imaginary << "i";
    //     return os;
    //   }
    // };
    //
    // template <typename T> class Vector {
    // private:
    //   vector<T> elems;
    //
    // public:
    //   Vector(vector<T> v) : elems(v) {}
    //
    //   void printAll(ostream &os) const {
    //     for (const auto &e : elems) {
    //       os << e << ",";
    //     }
    //     os << "\n";
    //   }
    // };

    //

    // Person and multiDictionary

    // multiDictionary<int, string>
    // Person p1{23, "Mircea"}
    // multiDictionary<string, person>
    // that means we have a template

    // #include <iostream>
    // #include <map>
    // #include <stdexcept>
    // #include <string>
    // #include <vector>
    // using namespace std;
    // template <typename K, typename V> // key, value
    // class MultiDictionary {
    // private:
    //   map<K, vector<V>> data;
    //
    // public:
    //   MultiDictionary() {}
    //   MultiDictionary &add(K key, V value) {
    //     data[key].push_back(value);
    //     return *this;
    //   }
    //   MultiDictionary &erase(K key, V value) {
    //     if (data.find(key) == data.end())
    //       throw runtime_error("Key does not exist!");
    //     auto &vec = data[key];
    //     for (auto it = vec.begin(); it != vec.end(); ++it)
    //       if (*it == value) {
    //         vec.erase(it);
    //         if (vec.empty())
    //           data.erase(key);
    //         return *this;
    //       }
    //     throw runtime_error("Given value does not exist for given key");
    //   }
    //   void print(ostream &os) const {
    //     for (const auto &[key, values] : data)
    //       for (const auto &v : values)
    //         os << key << " " << v << ";";
    //     os << endl;
    //   }
    //
    //   int sizeForKey(K key) const {
    //     auto it = data.find(key);
    //     if (it == data.end())
    //       return 0;
    //     return it->second.size();
    //   }
    // };
    //
    // class Person {
    // private:
    //   int age;
    //   string name;
    //
    // public:
    //   Person(int a, string n) : age(a), name(n) {}
    //   friend ostream &operator<<(ostream &os, const Person &p) {
    //     os << p.name << " is " << p.age << " years old";
    //     return os;
    //   }
    //   bool operator==(const Person &other) const {
    //     return age == other.age && name = other.name;
    //   }
    // }
   
template <typename T>
class Stack{
private:
    int maxCap;
    vector<T> elems;
public:
    Stack(int c) : maxCap(c) {}
    int getMaxCapacity() {return maxCap;}
    Stack& operator+(T value){
        if(elems.size() == maxCap)
            throw rntime_error("Stack is full!");
        elems.push_back(value);
        return *this;
    }
    T pop(){
        T values = elems.back();
        elems.pop_back();
        return value;
    }
};
      

// operators si ce imi mai trebe coaie nu le pot tine minte

bool operator==(const Class& other) const{
    return field = other.field;
}

bool operator<(const Class& other) const{
    return field < other.field;
}

Class(name) operator+(const Class& other) const{
    Class result = *this;
    result.field += other.field;
    return result;
}

Classname operator+=(const Class& other){
    field+=other.field;
    return *this;
}

Classname operator-(const Class& other){
    Class result = *this;
    result.field += other.field;
    return result;
}

Classname& operator++(){
    field++;
    return *this;
}

Classname& oeprator++(int){
    Class old = *this;
    field++;
    return old;
}

Class& operator=(const Class& other){
    if(this != &other){
        field=other.field;
    }
    return *this;
}

T& operator*(){
    return *ptr;
}

friend ostream& operator<<(ostream& os, const CLass& obj){
    os<<obj.field;
    return os;
}

template <typename T>
class Pula{
    private:
        vector<T> elems;
}

void push(T value){
    elems.push_Bakc(value);
}

T pop(){
    T value = elems.back();
    elems.pop_back;
    return value;
}

int size(){
    return elems.size();
}

T& operator[](int index){
    return elemens[index];
}

auto begin(){
    return elems.begin();
}

auto end(){
    return elems.end();
}

chaining pattern
Class& add(T value){
    elems.push_back(value);
    return *this;
}

