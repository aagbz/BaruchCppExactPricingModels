//
//  File: Option.cpp
//  Project: ExactPricingModels
//  Objective: ABC for an option
//
//  Created by Aldo Aguilar on 02/10/20.
//

#include "Option.hpp"

Option::Option(const Option& other_option) :
m_S(other_option.m_S),
m_K(other_option.m_K),
m_T(other_option.m_T),
m_r(other_option.m_r),
m_s(other_option.m_s),
m_b(other_option.m_b),
call_or_put(other_option.call_or_put),
underlying_type(other_option.underlying_type),
m_q(other_option.m_q),
m_R(other_option.m_R) {
    /*
     Copy constructor
     */
}

Option::Option(double underlying_price,
               double strike_price,
               double time_to_maturity,
               double riskfree_rate,
               double constant_volatility,
               enum CallOrPut call_or_put,
               enum UnderlyingType underlying_type,
               double dividend_yield,
               double foreign_rate) :
m_S(underlying_price),
m_K(strike_price),
m_T(time_to_maturity),
m_r(riskfree_rate),
m_s(constant_volatility),
call_or_put(call_or_put),
underlying_type(underlying_type),
m_q(dividend_yield),
m_R(foreign_rate) {
    
    /*
     Parameter constructor. Carry cost (b) depends on the option's underlying asset class
     */
    
    switch (underlying_type) {
        case STOCK:
            m_b = m_r;
            break;
        case DIVIDEND:
            m_b = m_r - m_q;
            break;
        case FUTURES:
            m_b = 0;
            break;
        case CURRENCY:
            m_b = m_r - m_R;
            break;
        default:
            break;
    }
    
}

Option& Option::operator = (const Option& other_option){
    /*
     Assignment operator overload
     */
    
    if(this == &other_option){
        return *this;
    }
    
    m_S = other_option.m_S;
    m_K = other_option.m_K;
    m_T = other_option.m_T;
    m_r = other_option.m_r;
    m_s = other_option.m_s;
    m_b = other_option.m_b;
    call_or_put = other_option.call_or_put;
    underlying_type = other_option.underlying_type;
    m_q = other_option.m_q;
    m_R = other_option.m_R;
    
    return *this;
}
