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
 * @param   v1 First vector.
 * @param   v2 Second vector.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the sum of v1 and v2. 
 */
Vec3* vec3Add(Vec3* v1, Vec3* v2);

/**
 * @brief   Subtracts two 3D vectors in a new 3D 
 *          vector.
 * @param   v1 First vector.
 * @param   v2 Second vector.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the subtraction of v1 and v2. 
 */
Vec3* vec3Sub(Vec3* v1, Vec3* v2);

/**
 * @brief   Scales a 3D vector by a constant scalar in a 
 *          new 3D vector.
 * @param   v 3D vector.
 * @param   scalar Constant.
 * @return  A pointer to a newly allocated 3D vector  
 *          representing the multiplication of v1 and a 
 *          scalar. 
 */
Vec3* vec3Scale(Vec3* v, float scalar);

/**
 * @brief   Computes the dot product of two 3D vectors
 * @param   a First vector.
 * @param   b Second vector.
 * @return  The dot product of a and b as a scalar value
 */
float vec3Dot(Vec3* a, Vec3* b);

/**
 * @brief   Computes the Length (magnitude) of a 3D 
 *          vector
 * @param   v The 3D vector.
 * @return  The length (magnitude) of the vector v as a 
 *          scalar value.
 */
float vec3Len(Vec3* v);

Vec3* vec3Norm(Vec3* v);
Vec3* vec3Lerp(Vec3* a, Vec3* b, float t);
Vec3* vec3Cross(Vec3* a, Vec3* b);
float vec3Angle(Vec3* a, Vec3* b);
Vec3* vec3Proj(Vec3* a, Vec3* b);
Vec3* vec3Refl(Vec3* v, Vec3* normal);
float vec3Dist(Vec3* a, Vec3* b);
Vec3* vec3Rotate(Vec3* v, Vec3* axis, float angle);

void vec3Free(Vec3* v);

#endif // VEC3_H