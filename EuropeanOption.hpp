//
//  File: EuropeanOption.hpp
//  Project: ExactPricingModels
//  Objective: European option, inherits Option
//
//  Created by Aldo Aguilar on 02/10/20.
//

#ifndef EuropeanOption_hpp
#define EuropeanOption_hpp

#include <stdio.h>
#include "Option.hpp"

class EuropeanOption : public Option {
    
public:
    /* CANONICAL HEADER START */
    EuropeanOption(){} // Default constructor
    
    EuropeanOption(const EuropeanOption& other_option); // Copy constructor
    
    EuropeanOption(double underlying_price,
                   double strike_price,
                   double time_to_maturity,
                   double riskfree_rate,
                   double constant_volatility,
                   enum CallOrPut call_or_put,
                   enum UnderlyingType underlying_type,
                   double dividend_yield = 0,
                   double foreign_rate = 0); // Parameter constructor
    
    virtual ~EuropeanOption(){} // Destructor
    
    EuropeanOption& operator = (const EuropeanOption& other_option); // Assignment operator overload
    /* CANONICAL HEADER END */
    
    double Price() const; // Price the option
    
    vector<double> Price(double price) const; // Price the option using put-call parity
    
    vector<double> Price(vector<double>& price_mesh, enum Parameter parameter) const; // Price the option using an array of parameters
    
    double Delta() const; // Compute delta
    
    double Gamma() const; // Compute gamma
    
    double DeltaApproximation(double h) const; // Compute delta using an approximation
    
    double GammaApproximation(double h) const; // Compute gamma using an approximation
    
    vector<double> Delta(vector<double>& parameter_mesh) const; // Price the option using an array of parameters
    
    vector<double> Gamma(vector<double>& parameter_mesh) const; // Price the option using an array of parameters
    
    // Helper functions
private:
    double PriceAsCall() const; // Price as a call option
    double PriceAsPut() const;  // Price as a put option
    
    double PriceAsCall(double S, double K, double T, double r, double s, double b) const; // Price as a call option. Used for mesh pricing
    double PriceAsPut(double S, double K, double T, double r, double s, double b) const; // Price as a put option. Used for mesh pricing
    
};

#endif /* EuropeanOption_hpp */
