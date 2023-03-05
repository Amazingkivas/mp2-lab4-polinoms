#include <iostream>
#include "list.h"

using std::exception;

class Polynom
{
private:

    struct Monom
    {
        double coefficient;
        size_t degree;

        bool operator==(const Monom& other); // comparison of monomials
        bool operator!=(const Monom& other); // comparison of monomials
    };

    List<Monom> polynom;

    void add_monom(const Monom& monom); // adding monomials

public:

    void add_monom(double coef, size_t deg); // adding monomials by parameters

    size_t psize() const; // get polynomial size (number of monomials)

    Polynom operator+(const Polynom& other); // addition of polynomials

    Polynom operator*(const Polynom& other); // multiplication of polynomials

    Polynom operator*(const double& coef) const; // multiplication polynomial by a number

    Polynom operator-(const Polynom& other); // subtraction of polynomials

    bool operator==(const Polynom& other) const; // comparison of polynomials for tests

    bool operator!=(const Polynom& other) const; // comparison of polynomials for tests

    void show(); // polynomial output
};
