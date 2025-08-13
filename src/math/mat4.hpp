extern "C"
{
    #include "mat4.h"
}

namespace math 
{
    class Mat4f
    {
    private:
        Mat4f_t mat4;
    
    public:
        Mat4f() { mat4f_zero_r(&mat4); }
        explicit Mat4f(const Mat4f_t& m) : mat4(m) {}
        explicit Mat4f(const float arr[16]) { mat4f_from_array_r(&mat4, arr); }

        static Mat4f Identity() { Mat4f mat; mat4f_identity_r(&mat.mat4); return mat; }
        static Mat4f Zero() { Mat4f mat; mat4f_zero_r(&mat.mat4); return mat; }

        const Mat4f_t& data() const { return mat4; }
        Mat4f_t& data() { return mat4; }
    };
}