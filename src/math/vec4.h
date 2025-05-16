#ifndef VECTOR4_H
#define VECTOR4_H

typedef struct 
{
    float x, y, z, w;
} Vec4;

/**
 * @brief   Creates a new 4D vector.
 * @param   x   X-axis coordinate.
 * @param   y   Y-axis coordinate.
 * @param   z   Z-axis coordinate.
 * @param   w   W-axis coordinate.
 * @return  A 4D vector with the specified coordinates.
 */
Vec4 vec4(float x, float y, float z, float w);

/**
 * @brief   Adds two 4D vectors and returns a new 4D vector.
 * @param   v1 First vector.
 * @param   v2 Second vector.
 * @return  A 4D vector representing the sum of v1 and v2.
 */
Vec4 vec4_add(Vec4 v1, Vec4 v2);

/**
 * @brief   Subtracts two 4D vectors and returns a new 4D vector.
 * @param   v1 First vector.
 * @param   v2 Second vector.
 * @return  A 4D vector representing the result of v1 minus v2.
 */
Vec4 vec4_sub(Vec4 v1, Vec4 v2);

/**
 * @brief   Scales a 4D vector by a constant scalar and returns a new 4D vector.
 * @param   v      4D vector.
 * @param   scalar Scalar value.
 * @return  A 4D vector representing the multiplication of v by the scalar.
 */
Vec4 vec4_scale(Vec4 v, float scalar);

/**
 * @brief   Computes the dot product of two 4D vectors.
 * @param   a First vector.
 * @param   b Second vector.
 * @return  A scalar value representing the dot product of a and b.
 *          - scalar > 0: Both vectors have the same orientation (the angle between them is acute).
 *          - scalar = 0: Vectors are orthogonal (the angle between them is 90 degrees).
 *          - scalar < 0: Vectors have opposite orientations (the angle between them is obtuse).
 */
float vec4_dot(Vec4 a, Vec4 b);

/**
 * @brief   Computes the length (magnitude) of a 4D vector.
 * @param   v 4D vector.
 * @return  A scalar value representing the length (magnitude) of the vector v.
 */
float vec4_len(Vec4 v);

/**
 * @brief   Normalizes a 4D vector (scales it to unit length).
 * @param   v 4D vector.
 * @return  A 4D vector representing the normalized version of v.
 *          Returns a zero vector (0, 0, 0) if the input vector is a zero vector.
 */
Vec4 vec4_norm(Vec4 v);

/**
 * @brief   Performs linear interpolation between two 4D vectors.
 * @param   a Start vector.
 * @param   b End vector.
 * @param   t Interpolation factor (0.0 to 1.0).
 *             - t = 0 returns the vector a.
 *             - t = 1 returns the vector b.
 *             - t between 0 and 1 returns a point between a and b.
 * @return  A 4D vector representing the interpolated result between a and b.
 */
Vec4 vec4_lerp(Vec4 a, Vec4 b, float t);

/**
 * @brief   Computes the angle between two 4D vectors.
 * @param   a First vector.
 * @param   b Second vector.
 * @return  The angle between vectors a and b in radians.
 */
float vec4_angle(Vec4 a, Vec4 b);

/**
 * @brief   Computes the projection of vector a onto vector b.
 * @param   a The vector to be projected.
 * @param   b The vector onto which a is projected.
 * @return  A 4D vector representing the projection of a onto b.
 */
Vec4 vec4_proj(Vec4 a, Vec4 b);

/**
 * @brief   Computes the reflection of a vector v against a normal.
 * @param   v The incident vector.
 * @param   normal The normal vector of the surface.
 * @return  A 4D vector representing the reflection of v across normal.
 */
Vec4 vec4_refl(Vec4 v, Vec4 normal);

/**
 * @brief   Computes the Euclidean distance between two 4D vectors.
 * @param   a The first vector.
 * @param   b The second vector.
 * @return  The scalar distance between a and b.
 */
float vec4_dist(Vec4 a, Vec4 b);

#endif // VECTOR4_H