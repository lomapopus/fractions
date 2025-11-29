#include <string>
#include <sstream>
#include <iostream>

using namespace std;
class Rational {
private:
    int64_t num_;
    uint64_t den_;

public:
    Rational() : num_(0), den_(1) {}


    Rational(int64_t value) : num_(value), den_(1) {}

    Rational(int64_t n, int64_t d) {
        if (d < 0) {
            n = -n;
            d = -d;
        }
        num_ = n;
        den_ = d;
    }
    
    int64_t numerator() const     { return num_; }
    uint64_t denominator() const  { return den_; }
    
    explicit operator double() const {
        return static_cast<double>(num_) / static_cast<double>(den_);
    }
    
    string str() const {
        ostringstream os;
        os << num_;
        if (den_ != 1) os << "/" << den_;
        return os.str();
    }

    Rational operator+(const Rational &r) const {
        return Rational(
            num_ * r.den_+ r.num_ * den_,
            den_ * r.den_
        );
    }

    Rational& operator+=(const Rational &r) {
        *this = *this + r;
        return *this;
    }

    Rational operator-(const Rational &r) const {
        return Rational(
            num_ * int64_t(r.den_) - r.num_ * int64_t(den_),
            int64_t(den_) * int64_t(r.den_)
        );
    }

    Rational& operator-=(const Rational &r) {
        *this = *this - r;
        return *this;
    }

    Rational operator*(const Rational &r) const {
        return Rational(
            num_ * r.num_,
            int64_t(den_) * int64_t(r.den_)
        );
    }

    Rational& operator*=(const Rational &r) {
        *this = *this * r;
        return *this;
    }

    Rational operator/(const Rational &r) const {
        if (r.num_ == 0) {
            throw domain_error("Division by zero");
        }
        return Rational(
            num_ * int64_t(r.den_),
            int64_t(den_) * r.num_
        );
    }

    Rational& operator/=(const Rational &r) {
        *this = *this / r;
        return *this;
    }


    Rational operator-() const {
        return Rational(-num_, den_);
    }

    bool operator==(const Rational &r) const {
        return num_ == r.num_ && den_ == r.den_;
    }

    bool operator!=(const Rational &r) const { return !(*this == r); }

    bool operator<(const Rational &r) const {

        return num_/den_ < r.num_/r.den_;
    }

    bool operator>(const Rational &r) const { return r < *this; }
    bool operator<=(const Rational &r) const { return !(*this > r); }
    bool operator>=(const Rational &r) const { return !(*this < r); }
};

int main() {
    auto r1 = Rational(7, -3);
    auto r2 = Rational(7, 5);
    auto answer = r1 +r2;
    cout<<answer.str()<<endl;
    return 0;
}