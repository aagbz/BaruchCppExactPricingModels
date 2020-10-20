//
//  File: Helpers.hpp
//  Project: ExactPricingModels
//  Objective: Helper functions
//
//  Created by Aldo Aguilar on 04/10/20.
//

#ifndef Helpers_hpp
#define Helpers_hpp

#include <stdio.h>
#include <vector>

std::vector<double> CreateMesh(double mesh_start, double mesh_end, double step) {
    /*
     Returns a mesh used for a monotonically increasing range of underlying values
     input:
        mesh_start: first element
        mesh_end: last element
        step: iteration step until last element is reached
     output:
        mesh: resulting array that goes from start to end
    */
    std::vector<double> mesh; // Output mesh
    
    for (double start = mesh_start; start < mesh_end + 1; start+=step) {
        mesh.push_back(start); // Populate mesh
    }
    
    return mesh;
    
}

#endif /* Helpers_hpp */
