//
//  File: EuropeanOption.cpp
//  Project: ExactPricingModels
//  Objective: European option, inherits Option
//
//  Created by Aldo Aguilar on 02/10/20.
//

#include "EuropeanOption.hpp"
#include "cmath"

#include <boost/math/distributions/normal.hpp>


EuropeanOption::EuropeanOption(const EuropeanOption& other_option) :
Option(other_option) {
    /*
     Copy constructor
     */
}


EuropeanOption::EuropeanOption(double underlying_price,
                               double strike_price,
                               double time_to_maturity,
                               double riskfree_rate,
                               double constant_volatility,
                               enum CallOrPut call_or_put,
                               enum UnderlyingType underlying_type,
                               double dividend_yield,
                               double foreign_rate) :
Option(underlying_price,
       strike_price,
       time_to_maturity,
       riskfree_rate,
       constant_volatility,
       call_or_put,
       underlying_type,
       dividend_yield,
       foreign_rate) {
    /*
     Parameter constructor
     */
}

EuropeanOption& EuropeanOption::operator = (const EuropeanOption& other_option){
    /*
     Assignment operator overload
     */
    
    if(this == &other_option){
        return *this;
    }
    
    Option::operator=(other_option);
    
    return *this;
}

double EuropeanOption::Price() const {
    /*
     Price the option based on Call/Put attribute
     */
    return CallOrPut() == CALL ? PriceAsCall() : PriceAsPut() ;
}

double EuropeanOption::PriceAsCall() const {
    /*
     Price as a call option
     */
    
    double temp =  s() * sqrt(T());
    
    double d1 = ( log(S()/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
    
    double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), d1);
    
    double d2 = d1 - temp;
    
    double Nd2 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), d2);
    
    double SebrT = S() * exp( (b() - r()) * T() );
    
    double KerT = K() * exp( - r() * T() );
    
    return SebrT*Nd1 - KerT*Nd2;
}

double EuropeanOption::PriceAsPut() const {
    /*
     Price as a put option
     */
    
    double temp =  s() * sqrt(T());
    
    double d1 = ( log(S()/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
    
    double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), -d1);
    
    double d2 = d1 - temp;
    
    double Nd2 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), -d2);
    
    double SebrT = S() * exp( (b() - r()) * T() );
    
    double KerT = K() * exp( - r() * T() );
    
    return KerT*Nd2 - SebrT*Nd1;
    
}

vector<double> EuropeanOption::Price(double price) const {
    /*
     Price the option using put-call parity
     input:
        option price
     output:
        vector with option price and parity difference
     */
    
    double temp = K() * exp( - r() * T() );
    
    double parity_price = CallOrPut() == CALL ? ( price + temp - S() ) :
    ( price + S() - temp );
    
    double parity_difference = CallOrPut() == CALL ? ( price + temp - (parity_price + S()) ) :
    ( parity_price + temp - (price + S()) ) ;
    
    return {parity_price, parity_difference};
}

// Price the option using an array of parameters
vector<double> EuropeanOption::Price(vector<double>& parameter_mesh, enum Parameter parameter) const {
    /*
     Price the option using an array of parameters
     input:
        parameter mesh
        parameter type
     output:
        vector with prices
     */
    
    vector<double> prices;
    bool is_call = CallOrPut() == CALL;
    
    switch(parameter){
        case UNDERLYING:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(element, -1, -1, -1, -1, -1));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(element, -1, -1, -1, -1, -1));
            }
            
            break;
        case STRIKE:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(-1, element, -1, -1, -1, -1));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(-1, element, -1, -1, -1, -1));
            }
            
            break;
        case TIME:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(-1, -1, element, -1, -1, -1));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(-1, -1, element, -1, -1, -1));
            }
            
            break;
        case RATE:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(-1, -1, -1, element, -1, -1));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(-1, -1, -1, element, -1, -1));
            }
            
            break;
        case SIGMA:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(-1, -1, -1, -1, element, -1));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(-1, -1, -1, -1, element, -1));
            }
            
            break;
        case CARRY:
            
            if(is_call){
                for(double element: parameter_mesh) prices.push_back(PriceAsCall(-1, -1, -1, -1, -1, element));
            } else {
                for(double element: parameter_mesh) prices.push_back(PriceAsPut(-1, -1, -1, -1, -1, element));
            }
            
            break;
        default:
            break;
    }
    
    return prices;
}

double EuropeanOption::PriceAsCall(double i_S, double i_K, double i_T, double i_r, double i_s, double i_b) const {
    /*
     Price as a call option using a parameter
     input:
        desired parameter
     output:
        price
     */
    
    double S = i_S == -1 ? Option::S() : i_S;
    double K = i_K == -1 ? Option::K() : i_K;
    double T = i_T == -1 ? Option::T() : i_T;
    double r = i_r == -1 ? Option::r() : i_r;
    double s = i_s == -1 ? Option::s() : i_s;
    double b = i_b == -1 ? Option::b() : i_b;
    
    double temp =  s * sqrt(T);
    
    double d1 = ( log(S/K) + (b + (s*s / 2.0) ) * T ) / temp;
    
    double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), d1);
    
    double d2 = d1 - temp;
    
    double Nd2 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), d2);
    
    double SebrT = S * exp( (b - r) * T );
    
    double KerT = K * exp( - r * T );
    
    return SebrT*Nd1 - KerT*Nd2;
}

double EuropeanOption::PriceAsPut(double i_S, double i_K, double i_T, double i_r, double i_s, double i_b) const {
    /*
     Price as a put option using a parameter
     input:
        desired parameter
     output:
        price
     */
    
    double S = i_S == -1 ? Option::S() : i_S;
    double K = i_K == -1 ? Option::K() : i_K;
    double T = i_T == -1 ? Option::T() : i_T;
    double r = i_r == -1 ? Option::r() : i_r;
    double s = i_s == -1 ? Option::s() : i_s;
    double b = i_b == -1 ? Option::b() : i_b;
    
    double temp =  s * sqrt(T);
    
    double d1 = ( log(S/K) + (b + (s*s / 2.0) ) * T ) / temp;
    
    double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), -d1);
    
    double d2 = d1 - temp;
    
    double Nd2 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), -d2);
    
    double SebrT = S * exp( (b - r) * T );
    
    double KerT = K * exp( - r * T );
    
    return KerT*Nd2 - SebrT*Nd1;
    
}


// Compute delta
double EuropeanOption::Delta() const {
    /*
     Compute delta
     */

    bool is_call = CallOrPut() == CALL;
    
    double temp =  s() * sqrt(T());
    
    double d1 = ( log(S()/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
    
    double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), (is_call ? +1 : -1) * d1);
    
    double ebrT = exp( (b() - r()) * T() );
    
    return (is_call ? +1 : -1) * ebrT * Nd1;
    
}

// Compute gamma
double EuropeanOption::Gamma() const {
    /*
     Compute gamma
     */
    
    bool is_call = CallOrPut() == CALL;
    
    double temp =  s() * sqrt(T());
    
    double d1 = ( log(S()/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
    
    double nd1 = boost::math::pdf(boost::math::normal_distribution<double>(0.0, 1.0), (is_call ? +1 : -1) * d1);
    
    double ebrT = exp( (b() - r()) * T() );
    
    return (nd1 * ebrT) / (S() * temp);
    
}

// Compute delta using array of prices
vector<double> EuropeanOption::Delta(vector<double>& price_mesh) const {
    /*
     Compute delta
     input:
        price mesh
     output:
        delta
     */
    
    bool is_call = CallOrPut() == CALL;
    
    vector<double> deltas;
    
    for(double price: price_mesh){
        
        double temp =  s() * sqrt(T());
        
        double d1 = ( log(price/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
        
        double Nd1 = boost::math::cdf(boost::math::normal_distribution<double>(0.0, 1.0), (is_call ? +1 : -1) * d1);
        
        double ebrT = exp( (b() - r()) * T() );
        
        deltas.push_back((is_call ? +1 : -1) * ebrT * Nd1);
    }
    
    return deltas;
    
}

// Compute gamma using array of prices
vector<double> EuropeanOption::Gamma(vector<double>& price_mesh) const {
    /*
     Compute gamma
     input:
        price mesh
     output:
        gamma
     */
    
    bool is_call = CallOrPut() == CALL;
    
    vector<double> gammas;
    
    for(double price: price_mesh){
        
        double temp =  s() * sqrt(T());
        
        double d1 = ( log(price/K()) + (b() + (s()*s() / 2.0) ) * T() ) / temp;
        
        double nd1 = boost::math::pdf(boost::math::normal_distribution<double>(0.0, 1.0), (is_call ? +1 : -1) * d1);
        
        double ebrT = exp( (b() - r()) * T() );
        
        gammas.push_back((nd1 * ebrT) / (price * temp));
    }
    
    return gammas;
    
}

// Compute delta
double EuropeanOption::DeltaApproximation(double h) const {
    /*
     Compute delta using an approximation
     input:
        h
     output:
        delta
     */
    
    return CallOrPut() == CALL ? (PriceAsCall(S() + h, -1, -1, -1, -1, -1) - PriceAsCall(S() - h, -1, -1, -1, -1, -1)) / (2 * h) :
    (PriceAsPut(S() + h, -1, -1, -1, -1, -1) - PriceAsPut(S() - h, -1, -1, -1, -1, -1)) / (2 * h);
    
}

// Compute gamma
double EuropeanOption::GammaApproximation(double h) const {
    /*
     Compute gamma using an approximation
     input:
        h
     output:
        gamma
     */
    
    return CallOrPut() == CALL ? (PriceAsCall(S() + h, -1, -1, -1, -1, -1) - (2 * PriceAsCall(S(), -1, -1, -1, -1, -1)) + PriceAsCall(S() - h, -1, -1, -1, -1, -1)) / (h * h) :
    (PriceAsPut(S() + h, -1, -1, -1, -1, -1) - (2 * PriceAsPut(S(), -1, -1, -1, -1, -1)) + PriceAsPut(S() - h, -1, -1, -1, -1, -1)) / (h * h);
}
