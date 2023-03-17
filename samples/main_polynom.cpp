#include "polynom.h"

using std::cin;
using std::cout;
using std::endl;

bool fill(Polynom& poly) // return false if the polynomial could not be filled in
{
	int num;
	cout << "\nEnter the number of monomials in the polynomial: " ;
	cin >> num;
	if (num < 1)
	{
		cout << "ERROR: Non-positive number of monomials" << endl;
		return false;
	}

	cout << "\nFilling the polynomial" << endl;
	double coefficient;
	int degree;

	for (int i = 0; i < num; i++)
	{
		cout << "\nEnter the coefficient: ";
		cin >> coefficient;
		cout << endl << "Enter the degree: ";
		cin >> degree;
		try
		{
			poly.add_monom(coefficient, degree);
		}
		catch (const exception& except)
		{
			cout << "\nERROR: " << except.what() << endl;
			return false;
		}
	}
	return true;
}

int main()
{
	cout << "Monomial representation: { coefficient , degree }" << endl;
	cout << "Degree representation: three-digit number ABC (x^Ay^Bz^C, 0 <= A,B,C <= 9)" << endl;
	cout << "For example: 5x^2y^3z^4 -> { 5 , 234 }" << endl;

	Polynom pol1;
	if(!fill(pol1)) return 1;
	cout << "\nPolynomial: ";
	pol1.show();

	enum operations {
		ADD_POLYNOMIALS = 1,
		SUBTRACT_POLYNOMIALS,
		MULTIPLY_POLYNOMIALS,
		MULTIPLY_POLYNOMIAL_BY_NUMBER
	};

	int select;
	cout << "\n\nSelect an operation:\n" << endl;
	cout << "1 - addition" << endl;
	cout << "2 - subtraction" << endl;
	cout << "3 - multiplication" << endl;
	cout << "4 - multiplication by a number" << endl;
	cout << "\nOperation number: ";
	cin >> select;

	if (select > 4 || select < 1)
	{
		cout << "\nERROR: Invalid operation number" << endl;
		return 1;
	}

	switch (select)
	{
	case ADD_POLYNOMIALS:
	{
		Polynom pol2;
		if(!fill(pol2)) return 1;
		cout << "\nPolynomial: ";
		pol2.show();
		cout << "\n\nResult: ";
		(pol1 + pol2).show();
		break;
	}
	case SUBTRACT_POLYNOMIALS:
	{
		Polynom pol2;
		if (!fill(pol2)) return 1;
		cout << "\nPolynomial: ";
		pol2.show();
		cout << "\n\nResult: ";
		(pol1 - pol2).show();
		break;
	}
	case MULTIPLY_POLYNOMIALS:
	{
		Polynom pol2;
		if (!fill(pol2)) return 1;
		cout << "\nPolynomial: ";
		pol2.show();
		try
		{
			cout << "\n\nResult: ";
			(pol1 * pol2).show();
		}
		catch (const exception& except)
		{
			cout << "\n\nERROR: " << except.what() << endl;
			return 1;
		}
		break;
	}
	case MULTIPLY_POLYNOMIAL_BY_NUMBER:
	{
		double number;
		cout << "\nEnter the number: ";
		cin >> number;
		cout << "\n\nResult: ";
		(pol1 * number).show();
		break;
	}
	}

	return 0;
}
