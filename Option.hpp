//
//  File: Option.hpp
//  Project: ExactPricingModels
//  Objective: ABC for an option
//
//  Created by Aldo Aguilar on 02/10/20.
//

#ifndef Option_hpp
#define Option_hpp

#include <stdio.h>
#include <vector>

using namespace std;

enum CallOrPut{ CALL, PUT }; // Call/Put enumeration

enum UnderlyingType{ STOCK, DIVIDEND, FUTURES, CURRENCY }; // Underlying asset enumeration

enum Parameter{ UNDERLYING, STRIKE, TIME, RATE, SIGMA, CARRY }; // Pricing parameter enumeration. Used for mesh pricing

class Option {
    
    // Attributes
    double m_S; // Underlying asset price
    double m_K; // Strike price
    double m_T; // Time to maturity
    double m_r; // Risk-free rate
    double m_s; // Constant volatility
    double m_b; // Cost of carry
    CallOrPut call_or_put; // Call or Put
    UnderlyingType underlying_type; // Underlying asset class
    double m_q; // Dividend
    double m_R; // Foreign risk-free rate
    
public:
    /* CANONICAL HEADER START */
    Option(){}// Default constructor
    
    Option(const Option& other_option); // Copy constructor
    
    Option(double m_S,
           double m_K,
           double m_T,
           double m_r,
           double m_s,
           CallOrPut call_or_put,
           UnderlyingType underlying_type,
           double m_q,
           double m_R); // Parameter constructor
    
    virtual ~Option(){} // Destructor
    
    Option& operator = (const Option& other_option); // Assignment operator overload
    /* CANONICAL HEADER END */
    
    /* GETTERS START */
    
    double S() const {
        return m_S;
    }
    
    double K() const {
        return m_K;
    }
    
    double T() const {
        return m_T;
    }
    
    double r() const {
        return m_r;
    }
    
    double s() const {
        return m_s;
    }
    
    double b() const {
        return m_b;
    }
    
    CallOrPut CallOrPut() const {
        return call_or_put;
    }
    
    UnderlyingType UnderlyingType() const {
        return underlying_type;
    }
    
    double q() const {
        return m_q;
    }
    
    double R() const {
        return m_R;
    }
    
    /* GETTERS END */
    
    /* SETTERS START */
    
    void S(double underlying_price) {
        this->m_S = underlying_price;
    }
    
    void K(double strike_price) {
        this->m_K = strike_price;
    }
    
    void T(double time_to_maturity) {
        this->m_T = time_to_maturity;
    }
    
    void r(double riskfree_rate) {
        this->m_r = riskfree_rate;
    }
    
    void s(double constant_volatility) {
        this->m_s = constant_volatility;
    }
    
    void b(double cost_of_carry) {
        this->m_b = cost_of_carry;
    }
    
    void CallOrPut(enum CallOrPut call_or_put) {
        this->call_or_put = call_or_put;
    }
    
    void UnderlyingType(enum UnderlyingType underlying_type) {
        this->underlying_type = underlying_type;
    }
    
    void q(double dividend_yield) {
        this->m_q = dividend_yield;
    }
    
    void R(double foreign_rate) {
        this->m_R = foreign_rate;
    }
    /* SETTERS END */
    
    virtual double Price() const = 0; // Price the option
    
    virtual vector<double> Price(double price) const = 0; // Price the option using put-call parity
    
    virtual vector<double> Price(vector<double>& parameter_mesh, enum Parameter parameter) const = 0; // Price the option using an array of parameters
    
    virtual double Delta() const = 0; // Compute delta
    
    virtual double Gamma() const = 0; // Compute gamma
    
    virtual vector<double> Delta(vector<double>& price_mesh) const = 0; // Compute delta using array of underlying prices
    
    virtual vector<double> Gamma(vector<double>& price_mesh) const = 0; // Compute gamma using array of underlying prices
    
};

#endif /* Option_hpp */
