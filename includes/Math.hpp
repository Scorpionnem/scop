/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:28:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/24 15:22:40 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
# define MATH_HPP

#include "libs.hpp"

class	vec3
{
	public:
		float x;
		float y;
		float z;
		
		~vec3(){}
		vec3() : x(0), y(0), z(0)
		{}
		vec3(float xyz) : x(xyz), y(xyz), z(xyz)
		{}
		vec3(float x, float y, float z) : x(x), y(y), z(z)
		{}
		
		vec3 operator+(const vec3 &op) const
		{
			return (vec3(x + op.x, y + op.y, z + op.z));
		}
		vec3 operator-(const vec3 &op) const
		{
			return (vec3(x - op.x, y - op.y, z - op.z));
		}
		vec3 operator*(const vec3 &op) const
		{
			return (vec3(x * op.x, y * op.y, z * op.z));
		}
		vec3 operator/(const vec3 &op) const
		{
			return (vec3(x / op.x, y / op.y, z / op.z));
		}

		float	dot(const vec3 &op) const
		{
			return (x * op.x + y * op.y + z * op.z);
		}
		vec3	cross(const vec3 &op) const
		{
			return (vec3(
				y * op.z - z * op.y,
    	        z * op.x - x * op.z,
    	        x * op.y - y * op.x
			));
		}
		float	length() const
			{return (std::sqrt(x * x + y * y + z * z));}
		vec3	normalize() const
		{
			float len = this->length();
			return (len > 0.0f ? *this / len : vec3(0, 0, 0));
		}
};

class vec2
{
    public:
        float x, y;
    
	    ~vec2(){}
	    vec2(float xy) : x(xy), y(xy)
	    {}
        vec2() : x(0), y(0)
	    {}
        vec2(float x, float y) : x(x), y(y)
	    {}
    
        vec2 operator+(const vec2& op) const
	    {
	    	return (vec2(x + op.x, y + op.y));
	    }
        vec2 operator-(const vec2& op) const
	    {
	    	return (vec2(x - op.x, y - op.y));
	    }
        vec2 operator*(float s) const
	    {
	    	return (vec2(x * s, y * s));
	    }
        vec2 operator/(float s) const
	    {
	    	return (vec2(x / s, y / s));
	    }
    
        float dot(const vec2& op) const
	    {
	    	return (x * op.x + y * op.y);
	    }
        float length() const
	    {
	    	return (std::sqrt(x * x + y * y));
	    }
        vec2 normalize() const
	    {
            float len = length();
            return (len > 0.0f ? *this / len : vec2(0, 0));
        }
        float cross(const vec2& v) const
        {
            return (x * v.y - y * v.x);
        }
};

class vec4
{
    public:
        float x, y, z, w;

	    ~vec4(){}
        vec4(float xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw)
	    {}
        vec4() : x(0), y(0), z(0), w(0)
	    {}
        vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	    {}
    
        vec4 operator+(const vec4& v) const
	    {
	    	return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	    }
        vec4 operator-(const vec4& v) const
	    {
	    	return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	    }
        vec4 operator*(float s) const
	    {
	    	return vec4(x * s, y * s, z * s, w * s);
	    }
        vec4 operator/(float s) const
	    {
	    	return vec4(x / s, y / s, z / s, w / s);
	    }
    
        float dot(const vec4& v) const
	    {
	    	return (x * v.x + y * v.y + z * v.z + w * v.w);
	    }
        float length() const
	    {
	    	return (std::sqrt(x * x + y * y + z * z + w * w));
	    }
        vec4 normalize() const
	    {
            float len = length();
            return len > 0.0f ? *this / len : vec4(0, 0, 0, 0);
        }
};

class mat4
{
	public:
    	float data[16];
	
    	mat4()
		{
    	    std::fill(data, data + 16, 0.0f);
    	}
        mat4(float val)
		{
    	    std::fill(data, data + 16, 0.0f);
            this->data[0] = this->data[5] = this->data[10] = this->data[15] = val;
    	}
        mat4(const mat4 &cpy)
		{
            *this = cpy;
    	}
        mat4 &operator=(const mat4 &cpy)
        {
            for (int i = 0; i < 16; i++)
                this->data[i] = cpy.data[i];
            return (*this);
        }
	
    	static mat4 identity()
		{
    	    mat4 m;
    	    std::fill(m.data, m.data + 16, 0.0f);
    	    m.data[0] = m.data[5] = m.data[10] = m.data[15] = 1.0f;
    	    return (m);
    	}
    	float& operator()(int col, int row)
		{
			return (data[col * 4 + row]);
		}
    	const float& operator()(int col, int row) const
		{
			return (data[col * 4 + row]);
		}
};

inline mat4 operator*(const mat4& a, const mat4& b)
{
    mat4 result;
    for (int col = 0; col < 4; ++col)
	{
        for (int row = 0; row < 4; ++row)
		{
            result(col, row) = 0.0f;
            for (int k = 0; k < 4; ++k)
                result(col, row) += a(k, row) * b(col, k);
        }
    }
    return (result);
}

inline vec4 getCol(const mat4& m, int col)
{
    return vec4(m(col, 0), m(col, 1), m(col, 2), m(col, 3));
}

inline void setCol(mat4& m, int col, const vec4& v)
{
    m(col, 0) = v.x;
    m(col, 1) = v.y;
    m(col, 2) = v.z;
    m(col, 3) = v.w;
}

inline mat4 perspective(float fovDeg, float aspect, float near, float far)
{
    float fovRad = fovDeg * M_PI / 180.0f;
    float f = 1.0f / std::tan(fovRad / 2.0f);

    mat4 m;
    m.data[0] = f / aspect;
    m.data[5] = f;
    m.data[10] = (far + near) / (near - far);
    m.data[11] = -1.0f;
    m.data[14] = (2.0f * far * near) / (near - far);
    return (m);
}

inline mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 f = (center - eye).normalize();
    vec3 s = f.cross(up).normalize();
    vec3 u = s.cross(f);

    mat4 m = mat4::identity();
    m(0, 0) = s.x; m(1, 0) = s.y; m(2, 0) = s.z;
    m(0, 1) = u.x; m(1, 1) = u.y; m(2, 1) = u.z;
    m(0, 2) = -f.x; m(1, 2) = -f.y; m(2, 2) = -f.z;
    m(3, 0) = -s.dot(eye);
    m(3, 1) = -u.dot(eye);
    m(3, 2) = f.dot(eye);
    return (m);
}

inline mat4 translate(const vec3& t) {
    mat4 m = mat4::identity();
    m(0, 3) = t.x;
    m(1, 3) = t.y;
    m(2, 3) = t.z;
    return (m);
}

inline mat4 translate(const mat4& m, const vec3& v)
{
    mat4 result = m;

    vec4 col0 = getCol(m, 0);
    vec4 col1 = getCol(m, 1);
    vec4 col2 = getCol(m, 2);
    vec4 col3 = getCol(m, 3);

    vec4 translation = col0 * v.x + col1 * v.y + col2 * v.z + col3;

    setCol(result, 3, translation);

    return (result);
}

inline mat4 scale(const vec3& s)
{
    mat4 m = mat4::identity();
    m(0, 0) = s.x;
    m(1, 1) = s.y;
    m(2, 2) = s.z;
    return (m);
}

inline mat4 scale(mat4 &mat, const vec3& s)
{
    (void)mat;
    return (mat * scale(s));
}

inline mat4 ortho(float left, float right, float bottom, float top)
{
    const float near = -1.0f;
    const float far = 1.0f;

    mat4 m = mat4::identity();

    m(0, 0) = 2.0f / (right - left);
    m(1, 1) = 2.0f / (top - bottom);
    m(2, 2) = -2.0f / (far - near);

    m(3, 0) = -(right + left) / (right - left);
    m(3, 1) = -(top + bottom) / (top - bottom);
    m(3, 2) = -(far + near) / (far - near);

    return (m);
}

inline mat4 rotate(float angleRad, const vec3& axis)
{
    vec3 a = axis.normalize();
    float c = std::cos(angleRad);
    float s = std::sin(angleRad);
    float oneMinusC = 1.0f - c;

    mat4 m = mat4::identity();
    m(0, 0) = c + a.x * a.x * oneMinusC;
    m(0, 1) = a.x * a.y * oneMinusC + a.z * s;
    m(0, 2) = a.x * a.z * oneMinusC - a.y * s;

    m(1, 0) = a.y * a.x * oneMinusC - a.z * s;
    m(1, 1) = c + a.y * a.y * oneMinusC;
    m(1, 2) = a.y * a.z * oneMinusC + a.x * s;

    m(2, 0) = a.z * a.x * oneMinusC + a.y * s;
    m(2, 1) = a.z * a.y * oneMinusC - a.x * s;
    m(2, 2) = c + a.z * a.z * oneMinusC;

    return (m);
}

inline mat4 rotate(mat4 &mat, float angleRad, const vec3& axis)
{
    return (mat * rotate(angleRad, axis));
}

inline  float   toRadians(float deg)
{
    return(deg * M_PI / 180.0f);
}

inline  float   clamp(float val, float min, float max)
{
    float   res = val;
    if (res < min)
        res = min;
    else if (res > max)
        res = max;
    return (res);
}

inline vec3 minvec3(const vec3& a, const vec3& b)
{
    return vec3(
        (a.x < b.x) ? a.x : b.x,
        (a.y < b.y) ? a.y : b.y,
        (a.z < b.z) ? a.z : b.z
    );
}

inline vec3 maxvec3(const vec3& a, const vec3& b)
{
    return vec3(
        (a.x > b.x) ? a.x : b.x,
        (a.y > b.y) ? a.y : b.y,
        (a.z > b.z) ? a.z : b.z
    );
}

#endif