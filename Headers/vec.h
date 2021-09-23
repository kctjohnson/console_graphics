#pragma once

/*
    Written entirely based on the source code from from the
    processing p5.js vector class found here:
    https://github.com/processing/p5.js/blob/v1.4.0/src/math/p5.Vector.js
*/

#include <string>

class vec2d {
private:
    vec2d calculateRemainder(double x, double y);
    double dot(double x, double y);

public:
    double x, y;

    vec2d(double x, double y);
    
    // Return the vector as a string in (x, y) format
    std::string toString();

    // Set the x and y values to the input parameters
    void set(double x, double y);
    // Sets the vector values to match the input vector
    void set(vec2d vec);

    // Return a new copy of this vector
    vec2d copy();

    // Add the x and y value to this vector
    void add(double x, double y);
    // Add the input vector to this vector
    void add(vec2d vec);

    // Sub the x and y value from this vector
    void sub(double x, double y);
    // Sub the input vector from this vector
    void sub(vec2d vec);

    // Multiply the vector by a scalar
    void mult(double scalar);
    // Multiply the vector by an input x and y
    void mult(double x, double y);
    // Multiply the vector by the input vector
    void mult(vec2d vec);

    // Divide the vector by a scalar
    void div(double scalar);
    // Divide the vector by an input x and y
    void div(double x, double y);
    // Divide the vector by the input vector
    void div(vec2d vec);

    // Returns the magnitude of this vector
    double mag();
    // Calculates the square magnitude of this vector and returns the result
    double magSq();
    // Sets the magnitude of this vector to the given value
    void setMag(double mag);

    // Calculates the dot product of this vector and the input vector
    double dot(vec2d vec);
    // Calculates the cross product of this vector and the input vector
    double cross(vec2d vec);

    // Returns the euclidean distance between this vector and the input vector
    double dist(vec2d vec);

    // Normalize this vector to unit 1 to make it a unit vector
    void normalize();
    // Limit the magnitude of this vector to the given value
    void limit(double max);

    // Returns the angle of rotation for this vector in radians
    double heading();
    // Rotate the vector to the specified angle, magnitude remains the same. Angle is in radians
    void setHeading(double angle);
    // Rotate the vector by the given angle, magnitude remains the same. Angle is in radians
    void rotate(double angle);
    // Returns the angle between this vector and the input vector. Returns in radians
    double angleBetween(vec2d vec);

    // Linear interpolate the vector to another vector. amount is between 0.0 and 1.0
    void lerp(vec2d vec, double amount);

    // Reflect this vector about a normal line
    void reflect(vec2d surfaceNormal);

    // Checks to see if the two vectors are equal
    bool equals(vec2d vec);
    // Checks to see if the input values match this vector
    bool equals(double x, double y);

    // Sets this vector to the remainder of division with the input x and y
    void rem(double x, double y);
    // Sets this vector to the remainder of division with the input vector
    void rem(vec2d vec);
};

// Return a new vec2d from the given angle and length. The angle parameter is in radians
vec2d vec2dFromAngle(double angle, double length);
