class Object {
public:
    virtual void print() = 0;
    virtual ~Object() {}
};
class Integer : public Object {
private:
    int value;
public:
    Integer(int v) : value(v) {}
    void print() override { cout << value << " "; }
    ~Integer() {}
};
class String : public Object {
private:
    string value;
public:
    String(string s) : value(s) {}
    string operator*() const { return value; }
    bool operator==(const string& s) const { return value == s; }
    void print() override { cout << value << " "; }
    ~String() {}
};
class MyObjectList {
private:
    vector<Object*> elems;
public:
    MyObjectList() {}

    // add cu method chaining
    MyObjectList& add(Object* obj) {
        elems.push_back(obj);
        return *this;
    }

    int length() const { return elems.size(); }

    auto begin() { return elems.begin(); }
    auto end()   { return elems.end(); }

    ~MyObjectList() {
        for (auto o : elems) delete o;
    }
};

