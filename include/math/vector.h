#ifndef VECTOR_H
#define VECTOR_H

#include "math/vector3.h"
#include "math/vector4.h"

/**
 * @brief   Converts a 4D vector to a 3D vector.
 * @param   v Pointer to the 4D vector.
 * @return  A pointer to a newly allocated 3D vector representing 
 *          the first three components of the 4D vector (x, y, z).
 *          Returns NULL if the input vector is NULL or allocation fails.
 */
Vec3 Vec4ToVec3(Vec4 v);

/**
 * @brief   Converts a 3D vector to a 4D vector.
 * @param   v Pointer to the 3D vector.
 * @return  A pointer to a newly allocated 4D vector with the 
 *          same x, y, and z components as the 3D vector and 
 *          a default w component (1.0 for position, 0.0 for direction).
 *          Returns NULL if the input vector is NULL or allocation fails.
 */
Vec4 Vec3ToVec4(Vec3 v);

#endif // VECTOR_H