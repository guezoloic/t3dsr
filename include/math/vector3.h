#ifndef VEC3_H
#define VEC3_H

typedef struct {
    float x, y, z;
} Vec3;

/**
 * @brief   Creates a new 3D vector.
 * @param   x   X-axis coordinate.
 * @param   y   Y-axis coordinate.
 * @param   z   Z-axis coordinate.
 * @return  A pointer to the newly allocated 3D vector if 
 *          successful, or NULL if the allocation fails.
 */
Vec3* vec3(float x, float y, float z);

/**
 * @brief   Adds two 3D vectors in a new 3D vector.
 * @param   v1 First vector pointer.
 * @param   v2 Second vector pointer.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the sum of v1 and v2.
 *          Returns NULL if the allocation fails.
 */
Vec3* vec3Add(Vec3* v1, Vec3* v2);

/**
 * @brief   Subtracts two 3D vectors in a new 3D 
 *          vector.
 * @param   v1 First vector pointer.
 * @param   v2 Second vector pointer.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the subtraction of v1 and v2. 
 *          Returns NULL if the allocation fails.
 */
Vec3* vec3Sub(Vec3* v1, Vec3* v2);

/**
 * @brief   Scales a 3D vector by a constant scalar in a 
 *          new 3D vector.
 * @param   v 3D vector pointer.
 * @param   scalar Constant.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the multiplication of v1 and a 
 *          scalar. Returns NULL if the allocation 
 *          fails.
 */
Vec3* vec3Scale(Vec3* v, float scalar);

/**
 * @brief   Computes the dot product of two 3D vectors
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
float vec3Dot(Vec3* a, Vec3* b);

/**
 * @brief   Computes the Length (magnitude) of a 3D 
 *          vector
 * @param   v 3D vector pointer.
 * @return  The length (magnitude) of the vector v as 
 *          a scalar value. Returns NAN if input vector
 *          is NULL.
 */
float vec3Len(Vec3* v);

/**
 * @brief   Normalizes the 3D vector.
 * @param   v Pointer to the 3D vector.
 * @return  A pointer to a newly allocated 3D vector that 
 *          is normalized. Returns a zero vector (0, 0, 0) 
 *          if the input vector is a zero vector. Returns 
 *          NULL if the input pointer is invalid.
 */
Vec3* vec3Norm(Vec3* v);

/**
 * @brief   Performs linear interpolation between two 3D 
 *          vectors to determine a new 3D vector.
 * @param   a  Pointer to the first 3D vector (start vector).
 * @param   b  Pointer to the second 3D vector (end vector).
 * @param   t  Interpolation factor (0.0 to 1.0): 
 *             - t = 0 returns the vector a.
 *             - t = 1 returns the vector b.
 *             - t between 0 and 1 returns a point between 
 *             a and b.
 * @return  A pointer to a newly allocated 3D vector 
 *          representing the interpolated result between 
 *          a and b. Returns NULL if any of the input vectors 
 *          is NULL.
 */
Vec3* vec3Lerp(Vec3* a, Vec3* b, float t);

/**
 * @brief   Computes the cross product of two 3D vectors.
 *          The cross product produces a new vector that is 
 *          orthogonal (perpendicular) to both input vectors.
 *          The direction of the resulting vector follows the 
 *          right-hand rule.
 * @param   a Pointer to the first vector.
 * @param   b Pointer to the second vector.
 * @return  A pointer to a newly allocated 3D vector representing 
 *          the cross product of vectors a and b.
 *          Returns NULL if the allocation fails.
 */
Vec3* vec3Cross(Vec3* a, Vec3* b);
float vec3Angle(Vec3* a, Vec3* b);
Vec3* vec3Proj(Vec3* a, Vec3* b);
Vec3* vec3Refl(Vec3* v, Vec3* normal);
float vec3Dist(Vec3* a, Vec3* b);
Vec3* vec3Rotate(Vec3* v, Vec3* axis, float angle);

void vec3Free(Vec3* v);

#endif // VEC3_H