#include "Camera.hpp"

Camera::Camera()
    : 
        yaw{0.0}, pitch{0.5}, 
        maxPitch{1.45}, minPitch{1.45}, 
        x{0.25}, y{1.0}, z{0.0}, 
        lookAtX{0.0}, lookAtY{0.0}, lookAtZ{0.0}, 
        viewMatrix{new GLfloat[16]}
{
    this->UpdateViewMatrix();
}

GLfloat* Camera::GetViewMatrix() const
{
    return this->viewMatrix;
}

void Camera::UpdateViewMatrix()
{
    //  todo
    //  will need to use look at function to update the view matrix.

}





//  from vector Utlis, i only wanted them for lookAt function
//  also modified them a bit to not use the vec3 and mat4 datatypes
// #pragma GCC diagnostic ignored "-Wuninitialized" IdentityMatrix();
// #pragma GCC diagnostic ignored "-Wuninitialized" Mult(a, b);

    #define mat4 GLfloat*
    #define vec3 GLfloat*

    #include <math.h>


    vec3 Normalize(vec3 a)
    {
        GLfloat norm;
        vec3 result = new GLfloat[3];

        norm = (GLfloat)sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
        result[0] = a[0] / norm;
        result[1] = a[1] / norm;
        result[2] = a[2] / norm;
        return result;
    }

    vec3 VectorSub(vec3 a, vec3 b)
    {
        vec3 result = new GLfloat[3];

        result[0] = a[0] - b[0];
        result[1] = a[1] - b[1];
        result[2] = a[2] - b[2];
        return result;
    }

    vec3 CrossProduct(vec3 a, vec3 b)
    {
        vec3 result = new GLfloat[3];

        result[0] = a[1]*b[2] - a[2]*b[1];
        result[1] = a[2]*b[0] - a[0]*b[2];
        result[2] = a[0]*b[1] - a[1]*b[0];

        return result;
    }

    mat4 Mult(mat4 a, mat4 b) // m = a * b
    {
        mat4 m = new GLfloat[16];

        int x, y;
        for (x = 0; x <= 3; x++)
            for (y = 0; y <= 3; y++)
                    // m.m[x*4 + y] =	a.m[y+4*0] * b.m[0+4*x] +
                    //             a.m[y+4*1] * b.m[1+4*x] +
                    //             a.m[y+4*2] * b.m[2+4*x] +
                    //             a.m[y+4*3] * b.m[3+4*x];
                m[y*4 + x] = 
                    m[y*4+0] * m[0*4+x] +
                    m[y*4+1] * m[1*4+x] +
                    m[y*4+2] * m[2*4+x] +
                    m[y*4+3] * m[3*4+x];

        return m;
    }
    
    
    mat4 IdentityMatrix()
    {
        mat4 m = new GLfloat[16];
        int i;

        for (i = 0; i <= 15; i++)
            m[i] = 0;
        for (i = 0; i <= 3; i++)
            m[i * 5] = 1; // 0,5,10,15
        return m;
    }

    mat4 T(GLfloat tx, GLfloat ty, GLfloat tz)
    {
        mat4 m = new GLfloat[16];
        m = IdentityMatrix();

        //     m.m[12] = tx;
        //     m.m[13] = ty;
        //     m.m[14] = tz;
            m[3] = tx;
            m[7] = ty;
            m[11] = tz;
        return m;
    }



    mat4 lookAtv(vec3 p, vec3 l, vec3 v)
    {
        // vec3 n, u;
        // mat4 rot, trans;

        //  todo, split up the code in order to retain a pointer to the output of
        //      Normalize, VectorSub, CrossProduct, Mult and T
        //  these functions allocate memory for their outputs, but they do not unallocate it
        //  this function will need to either free the memory, or make use of global-ish variables to reuse pointer(which would require edits in all five functions to send their outputs to a where a pointer in the arguments are pointing)

        GLfloat* n = Normalize(VectorSub(p, l));
        GLfloat* u = Normalize(CrossProduct(v, n));
        v = CrossProduct(n, u);


        // rot = SetMat4(u[0], v[0], n[0], 0,
        //               u[1], v[1], n[1], 0,
        //               u[2], v[2], n[2], 0,
        //               0,   0,   0,   1);
        GLfloat* rot = new GLfloat[16]{
            u[0], u[1], u[2], 0,
            v[0], v[1], v[2], 0,
            n[0], n[1], n[2], 0,
            0,   0,   0,   1};

        GLfloat* trans = T(-p[0], -p[1], -p[2]);
        GLfloat* m = Mult(rot, trans);
        return m;
    }

    