#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct {
    float x, y, z, w;
} Vec4;

/**
 * @brief   Creates a new 4D vector.
 * @param   x   X-axis coordinate.
 * @param   y   Y-axis coordinate.
 * @param   z   Z-axis coordinate.
 * @param   w   W-axis coordinate.
 * @return  A pointer to the newly allocated 4D vector if 
 *          successful, or NULL if the allocation fails.
 */
Vec4* vec4(float x, float y, float z, float w);

/**
 * @brief   Adds two 4D vectors in a new 4D vector.
 * @param   v1 First vector pointer.
 * @param   v2 Second vector pointer.
 * @return  A pointer to a newly allocated 4D vector  
 *          representing the sum of v1 and v2.
 *          Returns NULL if the allocation fails.
 */
Vec4* vec4Add(Vec4* v1, Vec4* v2);

/**
 * @brief   Subtracts two 4D vectors in a new 4D 
 *          vector.
 * @param   v1 First vector pointer.
 * @param   v2 Second vector pointer.
 * @return  A pointer to a newly allocated 4D vector  
 *          representing the subtraction of v1 and v2. 
 *          Returns NULL if the allocation fails.
 */
Vec4* vec4Sub(Vec4* v1, Vec4* v2);

/**
 * @brief   Scales a 4D vector by a constant scalar in a 
 *          new 4D vector.
 * @param   v 4D vector pointer.
 * @param   scalar Constant.
 * @return  A pointer to a newly allocated 4D vector  
 *          representing the multiplication of v1 and a 
 *          scalar. Returns NULL if the allocation 
 *          fails.
 */
Vec4* vec4Scale(Vec4* v, float scalar);

/**
 * @brief   Computes the dot product of two 4D vectors
 * @param   a First vector pointer.
 * @param   b Second vector pointer.
 * @return  The dot product of a and b as a scalar value.
 *          - scalar value > 0.f: Both vectors have the same orientation 
 *            (the angle between them is acute).
 *          - scalar value = 0.f: Both vectors are orthogonal (the angle 
 *            between them is 90 degrees).
 *          - scalar value < 0.f: Both vectors have opposite orientations 
 *            (the angle between them is obtuse).
 *          Returns NAN if one of the input vectors are 
 *          NULL.
 */
float vec4Dot(Vec4* a, Vec4* b);

/**
 * @brief   Computes the Length (magnitude) of a 4D 
 *          vector
 * @param   v 4D vector pointer.
 * @return  The length (magnitude) of the vector v as 
 *          a scalar value. Returns NAN if input vector
 *          is NULL.
 */
float vec4Len(Vec4* v);

/**
 * @brief   Normalizes the 4D vector.
 * @param   v Pointer to the 4D vector.
 * @return  A pointer to a newly allocated 4D vector that 
 *          is normalized. Returns a zero vector (0, 0, 0) 
 *          if the input vector is a zero vector. Returns 
 *          NULL if the input pointer is invalid.
 */
Vec4* vec4Norm(Vec4* v);

/**
 * @brief   Performs linear interpolation between two 4D 
 *          vectors to determine a new 4D vector.
 * @param   a  Pointer to the first 4D vector (start vector).
 * @param   b  Pointer to the second 4D vector (end vector).
 * @param   t  Interpolation factor (0.0 to 1.0): 
 *             - t = 0 returns the vector a.
 *             - t = 1 returns the vector b.
 *             - t between 0 and 1 returns a point between 
 *             a and b.
 * @return  A pointer to a newly allocated 4D vector 
 *          representing the interpolated result between 
 *          a and b. Returns NULL if any of the input vectors 
 *          is NULL.
 */
Vec4* vec4Lerp(Vec4* a, Vec4* b, float t);

/**
 * @brief   Computes the angle between two 4D vectors.
 * @param   a Pointer to the first vector.
 * @param   b Pointer to the second vector.
 * @return  The angle between a and b in radians.
 */
float vec4Angle(Vec4* a, Vec4* b);

/**
 * @brief   Computes the projection of vector a onto vector b.
 * @param   a Pointer to the vector to be projected.
 * @param   b Pointer to the vector onto which a is projected.
 * @return  A pointer to a newly allocated 4D vector representing 
 *          the projection of a onto b.
 *          Returns NULL if b is a zero vector.
 */
Vec4* vec4Proj(Vec4* a, Vec4* b);

/**
 * @brief   Computes the reflection of a vector v against a normal.
 * @param   v Pointer to the incident vector.
 * @param   normal Pointer to the normal vector of the surface.
 * @return  A pointer to a newly allocated 4D vector representing 
 *          the reflection of v across normal.
 *          Returns NULL if normal is a zero vector.
 */
Vec4* vec4Refl(Vec4* v, Vec4* normal);

/**
 * @brief   Computes the Euclidean distance between two 4D vectors.
 * @param   a Pointer to the first vector.
 * @param   b Pointer to the second vector.
 * @return  The scalar distance between a and b.
 *          Returns NAN if either vector is NULL.
 */
float vec4Dist(Vec4* a, Vec4* b);

void vec4Free(Vec4* v);


#endif // VECTOR4_H