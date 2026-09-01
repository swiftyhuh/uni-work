class Complex {
private:
    double real;
    double imaginary;
public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    Complex(const Complex& other) : real(other.real),   imaginary(other.imaginary) {}
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }
    Complex operator/(double d) const {
        if (d == 0)
            throw runtime_error("Division by zero!");
        return Complex(real / d, imaginary / d);
    }
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << c.real << "+" << c.imaginary << "i";
        return os;
    }
};



template <typename T>
class Vector {
private:
    vector<T> elems;
public:
    Vector(vector<T> v) : elems(v) {}
    void printAll(ostream& os) const {
        for (const auto& e : elems)
            os << e << ", ";
        os << endl;
    }
};

