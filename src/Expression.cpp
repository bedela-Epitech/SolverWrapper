//
// Created by adrien_bedel on 09/09/19.
//

#include "../include/Expression.h"


template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x) : _varIndex(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x, const double &coeff) : _varIndex(0)
{
    _coeffs.push_back(coeff);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
}

template <class T>
SLRExpr<T>::SLRExpr(const SLRVar<T> &x, const SLRVar<T> &y) : _varIndex(0)
{
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    if (x < y)
        _vars.at(_varIndex).push_back(y);
    else
        _vars.at(_varIndex).insert(_vars.at(_varIndex).begin(), y);
}

template <typename T>
SLRExpr<T> operator*(const SLRVar<T> &x, const SLRVar<T> &y)
{
    return (SLRExpr<T>(x, y));
}

template <typename T>
SLRExpr<T> operator*(const double &coeff, const SLRVar<T> &x)
{
    return (SLRExpr<T>(x, coeff));
}

template <typename T>
SLRExpr<T> operator*(const SLRVar<T> &x, const double &coeff)
{
    return (SLRExpr<T>(x, coeff));
}

template <typename T>
SLRExpr<T> operator+(const double &constant, SLRExpr<T> expr)
{
    expr = expr + constant;
    return expr;
}

template <typename T>
SLRExpr<T> operator+(const SLRVar<T> &var, SLRExpr<T> expr)
{
    expr = expr + var;
    return (expr);
}

template <typename T>
SLRExpr<T> operator+(const SLRVar<T> &x, const SLRVar<T> &y)
{
    SLRExpr<T> expr(x);
    expr = expr + y;
    return (expr);
}


template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const double &coeff)
{
    _coeffs.at(_varIndex) *= coeff;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator*(const SLRVar<T> &x)
{
    int i;
    for (i = 0; i < _vars.at(_varIndex).size()
    && _vars.at(_varIndex)[i] < x; i++) {};
    _vars.at(_varIndex).insert(_vars.at(_varIndex).begin() + i, x);
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const double &constant)
{
    _constant = constant;
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRVar<T> &x)
{
    _varIndex++;
    _coeffs.push_back(1);
    _vars.push_back(std::vector<SLRVar<T>>());
    _vars.at(_varIndex).push_back(x);
    simplify();
    return *this;
}

template <typename T>
SLRExpr<T> SLRExpr<T>::operator+(const SLRExpr<T> &expr)
{
    _varIndex += expr._varIndex + 1;
    _coeffs.insert(_coeffs.end(), expr._coeffs.begin(), expr._coeffs.end());
    _vars.insert(_vars.end(), expr._vars.begin(), expr._vars.end());
    simplify();
    return *this;
}

template <typename T>
void    SLRExpr<T>::simplify()
{
    for (int i = 0; i < _varIndex; i++)
    {
        if (_vars[_varIndex].size() == _vars[i].size())
        {
            int tmp = 0;
            for (int j = 0; j < _vars[i].size() &&
            _vars[i][j] == _vars[_varIndex][j]; j++, tmp++);
            if (tmp == _vars[i].size())
            {
                _vars.erase(_vars.begin() + _varIndex);
                _coeffs[i] += _coeffs[_varIndex];
                _coeffs.erase(_coeffs.begin() + _varIndex);
                _varIndex--;
                return ;
            }
        }
    }
}

