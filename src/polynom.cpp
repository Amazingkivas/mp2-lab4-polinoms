#include "polynom.h"

bool Polynom::Monom::operator==(const Monom& other) const
{
    return abs(coefficient - other.coefficient) < eps && degree == other.degree;
}
bool Polynom::Monom::operator!=(const Monom& other) const
{
    return !(*this == other);
}

void Polynom::add_monom(double coef, size_t deg)
{
    if (abs(coef) < eps) return; 
    if (deg < 0 || deg > 999) throw exception("Exceeding the permissible degree");
    
    Monom monom{ coef, deg };
    if (psize() == 0)
    {
        polynom.push_front(monom);
    }
    else
    {
        size_t i = 0;
        for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter, i++)
        {
            if (deg > (*iter).degree)
            {
                if (i == 0) polynom.push_front(monom);
                else polynom.insert_after(i - 1, monom);
                return;
            }
            else if (deg == (*iter).degree)
            {
                if (abs((*iter).coefficient + coef) < eps)
                {
                    if (i == 0) polynom.pop_front();
                    else polynom.erase_after(i - 1);
                }
                else
                {
                    (*iter).coefficient += coef;
                }
                return;
            }
        }
        polynom.push_back(monom);
    }
}

size_t Polynom::psize() const
{
    return polynom.get_size();
}

Polynom Polynom::operator+(const Polynom& other)
{
    Polynom result;
    List<Monom>::iterator iter1 = polynom.begin();
    List<Monom>::iterator iter2 = other.polynom.begin();
    while (iter1 != polynom.end() && iter2 != other.polynom.end())
    {
        if ((*iter1).degree > (*iter2).degree)
        {
            result.polynom.push_back(*iter1);
            ++iter1;
        }
        else if ((*iter1).degree < (*iter2).degree)
        {
            result.polynom.push_back(*iter2);
            ++iter2;
        }
        else
        {
            double total_coef = (*iter1).coefficient + (*iter2).coefficient;
            ++iter2;
            if (!(abs(total_coef) < eps))
            {
                result.polynom.push_back(Monom{ total_coef, (*iter1).degree });
            }
            ++iter1;
        }
    }
    for (; iter1 != polynom.end(); ++iter1)
    {
        result.polynom.push_back(*iter1);
    }
    for (; iter2 != other.polynom.end(); ++iter2)
    {
        result.polynom.push_back(*iter2);
    }
    return result;
}
Polynom Polynom::operator*(const Polynom& other)
{
    Polynom result;
    size_t deg1, deg2;
    for (List<Monom>::iterator iter1 = polynom.begin(); iter1 != polynom.end(); ++iter1)
    {
        for (List<Monom>::iterator iter2 = other.polynom.begin(); iter2 != other.polynom.end(); ++iter2)
        {
            deg1 = (*iter1).degree;
            deg2 = (*iter2).degree;

            if (((deg1 - deg1 % 100) / 100) + ((deg2 - deg2 % 100) / 100) > 9)
                throw exception("Exceeding the permissible degree");
            if (((deg1 % 100 - deg1 % 10) / 10) + ((deg2 % 100 - deg2 % 10) / 10) > 9)
                throw exception("Exceeding the permissible degree");
            if ((deg1 % 10) + (deg2 % 10) > 9)
                throw exception("Exceeding the permissible degree");

            result.add_monom((*iter1).coefficient * (*iter2).coefficient, deg1 + deg2);
        }
    }
    return result;
}
Polynom Polynom::operator*(const double& coef) const
{
    Polynom result;
    if (abs(coef) < eps) return result;
    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter)
    {
        result.polynom.push_back(Monom{ (*iter).coefficient * coef, (*iter).degree });
    }
    return result;
}
Polynom Polynom::operator-(const Polynom& other)
{
    return *this + other * -1.0;
}

bool Polynom::operator==(const Polynom& other) const
{
    return psize() == other.psize() && polynom == other.polynom;
}
bool Polynom::operator!=(const Polynom& other) const
{
    return !(*this == other);
}

void Polynom::show()
{
    if (psize() == 0)
    {
        std::cout << "null polynomial";
    }
    std::string zeros = "";
    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end();)
    {
        if ((*iter).degree <= 9) zeros = "00";
        else if ((*iter).degree <= 99) zeros = "0";

        std::cout << "{ " << (*iter).coefficient << " , " << zeros << (*iter).degree << " }";
        if (++iter != nullptr) std::cout << " + ";
    }
}
