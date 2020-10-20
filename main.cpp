//
//  File: main.cpp
//  Project: ExactPricingModels
//  Objective: Test european option
//
//  Created by Aldo Aguilar on 02/10/20.
//

#include <iostream>

#include "EuropeanOption.hpp"
#include "Helpers.hpp"

using namespace std;

void Pricing(); // Pricing example
void PutCallParity(); // Pricing using put-call parity example
void MeshPricing(); // Pricing using mesh example
void GreeksApproximation(); // Greeks computation example

int main(int argc, const char * argv[]) {
    
    Pricing();
    PutCallParity();
    MeshPricing();
    GreeksApproximation();
    
    return  0;
}

void Pricing(){
    // Batch 1
    EuropeanOption c_b1 = EuropeanOption(60.0, 65.0, 0.25, 0.08, 0.30, CALL, STOCK);
    cout << "Call price: " << c_b1.Price() << endl;

    EuropeanOption p_b1 = EuropeanOption(60.0, 65.0, 0.25, 0.08, 0.3, PUT, STOCK);
    cout << "Put price: " << p_b1.Price() << endl;

    // Batch 2
    EuropeanOption c_b2 = EuropeanOption(100.0, 100.0, 1.0, 0.0, 0.2, CALL, STOCK);
    cout << "Call price: " << c_b2.Price() << endl;

    EuropeanOption p_b2 = EuropeanOption(100.0, 100.0, 1.0, 0.0, 0.2, PUT, STOCK);
    cout << "Put price: " << p_b2.Price() << endl;

    // Batch 3
    EuropeanOption c_b3 = EuropeanOption(5.0, 10.0, 1.0, 0.12, 0.5, CALL, STOCK);
    cout << "Call price: " << c_b3.Price() << endl;

    EuropeanOption p_b3 = EuropeanOption(5.0, 10.0, 1.0, 0.12, 0.5, PUT, STOCK);
    cout << "Put price: " << p_b3.Price() << endl;

    // Batch 4
    EuropeanOption c_b4 = EuropeanOption(100.0, 100.0, 30.0, 0.08, 0.30, CALL, STOCK);
    cout << "Call price: " << c_b4.Price() << endl;

    EuropeanOption p_b4 = EuropeanOption(100.0, 100.0, 30.0, 0.08, 0.30, PUT, STOCK);
    cout << "Put price: " << p_b4.Price() << endl;

}

void PutCallParity(){
    // Batch 1
    EuropeanOption c_b1 = EuropeanOption(60.0, 65.0, 0.25, 0.08, 0.30, CALL, STOCK);
    cout << "Call price: " << c_b1.Price() << endl;

    EuropeanOption p_b1 = EuropeanOption(60.0, 65.0, 0.25, 0.08, 0.3, PUT, STOCK);
    cout << "Put price: " << p_b1.Price() << endl;

    cout << "Call price using parity: " << p_b1.Price(p_b1.Price())[0] << ", parity difference: " << p_b1.Price(p_b1.Price())[1] << endl;

    // Batch 2
    EuropeanOption c_b2 = EuropeanOption(100.0, 100.0, 1.0, 0.0, 0.2, CALL, STOCK);
    cout << "Call price: " << c_b2.Price() << endl;

    EuropeanOption p_b2 = EuropeanOption(100.0, 100.0, 1.0, 0.0, 0.2, CALL, STOCK);
    cout << "Put price: " << p_b2.Price() << endl;

    cout << "Call price using parity: " << p_b2.Price(p_b2.Price())[0] << ", parity difference: " << p_b2.Price(p_b1.Price())[1] << endl;

    // Batch 3
    EuropeanOption c_b3 = EuropeanOption(5.0, 10.0, 1.0, 0.12, 0.5, CALL, STOCK);
    cout << "Call price: " << c_b3.Price() << endl;

    EuropeanOption p_b3 = EuropeanOption(5.0, 10.0, 1.0, 0.12, 0.5, CALL, STOCK);
    cout << "Put price: " << p_b3.Price() << endl;

    cout << "Call price using parity: " << p_b3.Price(p_b3.Price())[0] << ", parity difference: " << p_b3.Price(p_b1.Price())[1] << endl;

    // Batch 4
    EuropeanOption c_b4 = EuropeanOption(100.0, 100.0, 30.0, 0.08, 0.30, CALL, STOCK);
    cout << "Call price: " << c_b4.Price() << endl;

    EuropeanOption p_b4 = EuropeanOption(100.0, 100.0, 30.0, 0.08, 0.30, PUT, STOCK);
    cout << "Put price: " << p_b4.Price() << endl;

    cout << "Call price using parity: " << p_b4.Price(p_b4.Price())[0] << ", parity difference: " << p_b4.Price(p_b1.Price())[1] << endl;
}

void MeshPricing(){
    
    EuropeanOption put = EuropeanOption(100.0, 100.0, 30.0, 0.08, 0.30, PUT, STOCK);
    
    cout << "Put price: " << put.Price() << endl;
    
    // Create mesh
    vector<double> price_mesh = CreateMesh(99, 101, 1);
    
    vector<double> prices = put.Price(price_mesh, UNDERLYING);
    
    vector<double> deltas = put.Delta(price_mesh);
    
    // Compute price and mesh
    for (int index = 0; index < prices.size(); index++) {
        cout << "Price: " << prices[index] << endl;
        
        cout << "Delta: " <<deltas[index] << endl;
    }
    
}

void GreeksApproximation(){
    EuropeanOption call = EuropeanOption(105, 100, 0.5, 0.1, 0.36, CALL, FUTURES);
    
    // Compute delta
    cout << "Delta: " << call.Delta() << endl;
    
    // Compute delta approximation
    cout << "Delta approx.: " << call.DeltaApproximation(1) << endl;
    
}
