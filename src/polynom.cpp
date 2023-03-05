#include "polynom.h"

bool Polynom::Monom::operator==(const Monom& other)
{
    return coefficient == other.coefficient && degree == other.degree;
}

bool Polynom::Monom::operator!=(const Monom& other)
{
    return !(*this == other);
}

void Polynom::add_monom(double coef, size_t deg)
{
    if (coef == 0) return; 
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
                if ((*iter).coefficient + coef != 0)
                {
                    (*iter).coefficient += coef;
                }
                else
                {
                    if (i == 0) polynom.pop_front();
                    else polynom.erase_after(i - 1);
                }
                return;
            }
        }
        polynom.insert_after(psize() - 1, monom);
    }
}

void Polynom::add_monom(const Monom& monom)
{
    add_monom(monom.coefficient, monom.degree);
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
            result.add_monom(*iter1);
            ++iter1;
        }
        else if ((*iter1).degree < (*iter2).degree)
        {
            result.add_monom(*iter2);
            ++iter2;
        }
        else
        {
            double total_coef = (*iter1).coefficient + (*iter2).coefficient;
            ++iter2;
            if (total_coef != 0)
            {
                result.add_monom(total_coef, (*iter1).degree);
            }
            ++iter1;
        }
    }
    for (; iter1 != polynom.end(); ++iter1)
    {
        result.add_monom(*iter1);
    }
    for (; iter2 != other.polynom.end(); ++iter2)
    {
        result.add_monom(*iter2);
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
    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter)
    {
        result.add_monom((*iter).coefficient * coef, (*iter).degree);
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
    size_t i = 0;
    std::string zeros = "";
    for (List<Monom>::iterator iter = polynom.begin(); iter != polynom.end(); ++iter, i++)
    {
        if ((*iter).degree <= 9) zeros = "00";
        else if ((*iter).degree <= 99) zeros = "0";

        std::cout << "{ " << ( *iter).coefficient << " , " << zeros << (*iter).degree << " }";
        if (i != psize() - 1) std::cout << " + ";
    }
}
