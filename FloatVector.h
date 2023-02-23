#pragma once

#include <vector>


/**
 * Represents an N-dimensional vector of floating point values.
 */
class FloatVector
{
    public:
        /**
         * Construct a FloatVector from an existing std::vector of
         * floating point values.
         * @param elements The initial values for this FloatVector.
         */
        explicit FloatVector(const std::vector<float>& elements);

        /** Copy constructor for FloatVector.
         * @param other The FloatVector to copy.
         */
        FloatVector(const FloatVector& other);

        /**
         * Destructor for FloatVector.
         */
        ~FloatVector();

        /** Return the magnitude of the vector. */
        float magnitude();

        /** Return the number of elements in this vector */
        size_t dimension() const;

        /** Normalize the vector in place. */
        void normalize();

        /** Return true if the vector has been normalized
          * This will not indicate whether a normalized vector was used
          * to initialize the values. If a normalized vector is required,
          * the normalize() method should be called for certainty.
          */
        bool is_normalized() const;

        // Display a formatted output of this vector's elements.
        void print() const;

    private:
        std::vector<float> elements_;
        float magnitude_;
        bool magnitude_is_valid_;
        bool is_normalized_;
};

