/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 12:28:21 by mbatty            #+#    #+#             */
/*   Updated: 2025/05/24 13:16:13 by mbatty           ###   ########.fr       */
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
		return vec2(x + op.x, y + op.y);
	}
    vec2 operator-(const vec2& op) const
	{
		return vec2(x - op.x, y - op.y);
	}
    vec2 operator*(float s) const
	{
		return vec2(x * s, y * s);
	}
    vec2 operator/(float s) const
	{
		return vec2(x / s, y / s);
	}

    float dot(const vec2& op) const
	{
		return x * op.x + y * op.y;
	}
    float length() const
	{
		return std::sqrt(x * x + y * y);
	}
    vec2 normalize() const
	{
        float len = length();
        return len > 0.0f ? *this / len : vec2(0, 0);
    }
    float cross(const vec2& v) const
    {
        return x * v.y - y * v.x;
    }
};

class vec4
{
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
		return x * v.x + y * v.y + z * v.z + w * v.w;
	}
    float length() const
	{
		return std::sqrt(x * x + y * y + z * z + w * w);
	}
    vec4 normalize() const
	{
        float len = length();
        return len > 0.0f ? *this / len : vec4(0, 0, 0, 0);
    }
};

class Mat4
{
	public:
    	float data[16]; // column-major
	
    	Mat4()
		{
    	    std::fill(data, data + 16, 0.0f);
    	}
	
    	static Mat4 identity()
		{
    	    Mat4 m;
    	    m.data[0] = m.data[5] = m.data[10] = m.data[15] = 1.0f;
    	    return m;
    	}
	
    	float& operator()(int col, int row)
		{
			return data[col * 4 + row];
		}
    	const float& operator()(int col, int row) const
		{
			return data[col * 4 + row];
		}
};

inline Mat4 operator*(const Mat4& a, const Mat4& b)
{
    Mat4 result;
    for (int col = 0; col < 4; ++col)
	{
        for (int row = 0; row < 4; ++row)
		{
            result(col, row) = 0.0f;
            for (int k = 0; k < 4; ++k)
                result(col, row) += a(k, row) * b(col, k);
        }
    }
    return result;
}

inline Mat4 perspective(float fovDeg, float aspect, float near, float far)
{
    float fovRad = fovDeg * 3.14159265f / 180.0f;
    float f = 1.0f / std::tan(fovRad / 2.0f);

    Mat4 m;
    m.data[0] = f / aspect;
    m.data[5] = f;
    m.data[10] = (far + near) / (near - far);
    m.data[11] = -1.0f;
    m.data[14] = (2.0f * far * near) / (near - far);
    return m;
}

inline Mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
{
    vec3 f = (center - eye).normalize();
    vec3 s = f.cross(up).normalize();
    vec3 u = s.cross(f);

    Mat4 m = Mat4::identity();
    m(0, 0) = s.x; m(1, 0) = s.y; m(2, 0) = s.z;
    m(0, 1) = u.x; m(1, 1) = u.y; m(2, 1) = u.z;
    m(0, 2) = -f.x; m(1, 2) = -f.y; m(2, 2) = -f.z;
    m(3, 0) = -s.dot(eye);
    m(3, 1) = -u.dot(eye);
    m(3, 2) = f.dot(eye);
    return m;
}

inline Mat4 translate(const vec3& t)
{
    Mat4 m = Mat4::identity();
    m(3, 0) = t.x;
    m(3, 1) = t.y;
    m(3, 2) = t.z;
    return m;
}

inline Mat4 scale(const vec3& s)
{
    Mat4 m = Mat4::identity();
    m(0, 0) = s.x;
    m(1, 1) = s.y;
    m(2, 2) = s.z;
    return m;
}

inline Mat4 rotate(float angleRad, const vec3& axis)
{
    vec3 a = axis.normalize();
    float c = std::cos(angleRad);
    float s = std::sin(angleRad);
    float oneMinusC = 1.0f - c;

    Mat4 m = Mat4::identity();
    m(0, 0) = c + a.x * a.x * oneMinusC;
    m(0, 1) = a.x * a.y * oneMinusC + a.z * s;
    m(0, 2) = a.x * a.z * oneMinusC - a.y * s;

    m(1, 0) = a.y * a.x * oneMinusC - a.z * s;
    m(1, 1) = c + a.y * a.y * oneMinusC;
    m(1, 2) = a.y * a.z * oneMinusC + a.x * s;

    m(2, 0) = a.z * a.x * oneMinusC + a.y * s;
    m(2, 1) = a.z * a.y * oneMinusC - a.x * s;
    m(2, 2) = c + a.z * a.z * oneMinusC;

    return m;
}

#endif