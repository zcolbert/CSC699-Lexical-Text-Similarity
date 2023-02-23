/******************************************************************************
 * Filename: FloatVector.cpp
 * Author: Zachary Colbert
 * Contact: zcolbert@sfsu.edu
 *
 * Description: Implementation of the FloatVector class which represents
 *              an N-dimensional vector of floating point values, and provides
 *              the operations needed to inspect and manipulate such a vector.
 *****************************************************************************/

#include <cmath>  // sqrt
#include <iostream>

#include "FloatVector.h"


FloatVector::FloatVector(const std::vector<float>& elements)
    :   elements_(elements),
        magnitude_(0),
        magnitude_is_valid_(false),
        is_normalized_(false)
{}

// Copy is trivial - Use default copy constructor
FloatVector::FloatVector(const FloatVector& other) = default;

FloatVector::~FloatVector() = default;

size_t FloatVector::dimension() const
{
    return elements_.size();
}

float FloatVector::magnitude()
{
    // Avoid recomputing the magnitude
    if (magnitude_is_valid_) return magnitude_;

    std::cout << "Recomputing magnitude" << std::endl;
    // Compute magnitude as square root of sum of squares
    // m = sqrt((e_0*e_0) + (e_1*e_1) + ... + (e_n*e_n))
    float sum = 0.0f;
    for (const float& elem: elements_) {
        sum += elem * elem;
    }
    magnitude_ = std::sqrt(sum);
    // Validate the cached magnitude value
    magnitude_is_valid_ = true;

    return magnitude_;
}

void FloatVector::normalize()
{
    if (!is_normalized_)
    {
        float magnitude = this->magnitude();

        if (magnitude == 0) {
            throw std::runtime_error("Cannot normalize zero vector");
        }

        // Divide each element by the vector's magnitude
        for (float &elem: elements_) {
            elem = elem / magnitude;
        }

        magnitude_ = 1.0f;  // by definition
        magnitude_is_valid_ = true;
        is_normalized_ = true;
    }
}

bool FloatVector::is_normalized() const
{
    return is_normalized_;
}

void FloatVector::print() const
{
    for (const auto& elem: elements_) {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;
}