#ifndef MATH_H
#define MATH_H

#pragma once
#include <cmath>
#include <cstring>
namespace Source
{
#define PI			3.14159265358979323846
#define RAD2DEG(x)	(x * (180.0 / PI))
#define DEG2RAD(x)	(x * (PI / 180.0))

	class Vector2
	{
	public:
		float x, y;

		inline Vector2()
			: x(0),
			y(0)
		{
		}

		inline Vector2(float X, float Y)
			: x(X),
			y(Y)
		{
		}

		inline Vector2(float XY)
			: x(XY),
			y(XY)
		{
		}

		inline void Init(float X = 0.0f, float Y = 0.0f)
		{
			x = X;
			y = Y;
		}

		inline float operator [] (int i) const
		{
			return ((float*)this)[i];
		}

		inline float& operator [] (int i)
		{
			return ((float*)this)[i];
		}

		inline Vector2& operator += (const Vector2& v)
		{
			x += v.x;
			y += v.y;

			return *this;
		}

		inline Vector2& operator -= (const Vector2& v)
		{
			x -= v.x;
			y -= v.y;

			return *this;
		}

		inline Vector2& operator *= (const Vector2& v)
		{
			x *= v.x;
			y *= v.y;

			return *this;
		}

		inline Vector2& operator /= (const Vector2& v)
		{
			x /= v.x;
			y /= v.y;

			return *this;
		}

		inline Vector2& operator += (float v)
		{
			x += v;
			y += v;

			return *this;
		}

		inline Vector2& operator -= (float v)
		{
			x -= v;
			y -= v;

			return *this;
		}

		inline Vector2& operator *= (float v)
		{
			x *= v;
			y *= v;

			return *this;
		}

		inline Vector2& operator /= (float v)
		{
			x /= v;
			y /= v;

			return *this;
		}

		inline Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		inline Vector2 operator - (const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

		inline Vector2 operator + (const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		inline Vector2 operator * (const Vector2& v) const
		{
			return Vector2(x * v.x, y * v.y);
		}

		inline Vector2 operator / (const Vector2& v) const
		{
			return Vector2(x / v.x, y / v.y);
		}

		inline float Length() const
		{
			return sqrtf(x * x + y * y);
		}

		inline float LengthSqr() const
		{
			return (x * x + y * y);
		}

		inline bool IsZero() const
		{
			return (x > -0.01f && x < 0.01f
				&& y > -0.01f && y < 0.01f);
		}

		inline float DistTo(const Vector2& v) const
		{
			return (*this - v).Length();
		}

		inline float DistToSqr(const Vector2& v) const
		{
			return (*this - v).LengthSqr();
		}

		inline float Dot(const Vector2& v) const
		{
			return (x * v.x + y * v.y);
		}
	};

	inline Vector2 operator * (float f, const Vector2& v)
	{
		return v * f;
	}

	class Vector3
	{
	public:
		float x, y, z;

		inline Vector3()
			: x(0),
			y(0),
			z(0)
		{
		}

		inline Vector3(float X, float Y, float Z)
			: x(X),
			y(Y),
			z(Z)
		{
		}

		inline Vector3(float XYZ)
			: x(XYZ),
			y(XYZ),
			z(XYZ)
		{
		}

		inline Vector3(float* v)
			: x(v[0]),
			y(v[1]),
			z(v[2])
		{
		}

		inline Vector3(const float* v)
			: x(v[0]),
			y(v[1]),
			z(v[2])
		{
		}

		inline void Init(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
		{
			x = X;
			y = Y;
			z = Z;
		}

		inline float operator [] (int i) const
		{
			return ((float*)this)[i];
		}

		inline float& operator [] (int i)
		{
			return ((float*)this)[i];
		}

		inline Vector3& operator += (const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		inline Vector3& operator -= (const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		inline Vector3& operator *= (const Vector3& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		inline Vector3& operator /= (const Vector3& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		inline Vector3& operator += (float v)
		{
			x += v;
			y += v;
			z += v;

			return *this;
		}

		inline Vector3& operator -= (float v)
		{
			x -= v;
			y -= v;
			z -= v;

			return *this;
		}

		inline Vector3& operator *= (float v)
		{
			x *= v;
			y *= v;
			z *= v;

			return *this;
		}

		inline Vector3& operator /= (float v)
		{
			x /= v;
			y /= v;
			z /= v;

			return *this;
		}

		inline Vector3 operator - () const
		{
			return Vector3(-x, -y, -z);
		}

		inline Vector3 operator - (const Vector3& v) const
		{
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		inline Vector3 operator + (const Vector3& v) const
		{
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		inline Vector3 operator * (const Vector3& v) const
		{
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		inline Vector3 operator / (const Vector3& v) const
		{
			return Vector3(x / v.x, y / v.y, z / v.z);
		}

		inline float Length() const
		{
			return sqrtf(x * x + y * y + z * z);
		}

		inline float LengthSqr() const
		{
			return (x * x + y * y + z * z);
		}

		inline float LengthXY() const
		{
			return sqrtf(x * x + y * y);
		}

		inline float LengthXZ() const
		{
			return sqrtf(x * x + z * z);
		}

		inline bool IsZero() const
		{
			return (x > -0.01f && x < 0.01f
				&& y > -0.01f && y < 0.01f
				&& z > -0.01f && z < 0.01f);
		}

		inline float DistTo(const Vector3& v) const
		{
			return (*this - v).Length();
		}

		inline float DistToSqr(const Vector3& v) const
		{
			return (*this - v).LengthSqr();
		}

		inline float Dot(const Vector3& v) const
		{
			return (x * v.x + y * v.y + z * v.z);
		}

		inline Vector3 Cross(const Vector3& v) const
		{
			return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}
	};

	inline Vector3 operator * (float f, const Vector3& v)
	{
		return v * f;
	}

	class Vector4
	{
	public:
		float x, y, z, w;

		inline Vector4()
			: x(0),
			y(0),
			z(0),
			w(0)
		{
		}

		inline Vector4(const Vector3& v)
			: x(v.x),
			y(v.y),
			z(v.z),
			w(0)
		{
		}

		inline Vector4(float X, float Y, float Z, float W)
			: x(X),
			y(Y),
			z(Z),
			w(w)
		{
		}

		inline Vector4(float XYZW)
			: x(XYZW),
			y(XYZW),
			z(XYZW),
			w(XYZW)
		{
		}

		inline void Init(float X = 0.0f, float Y = 0.0f, float Z = 0.0f, float W = 0.0f)
		{
			x = X;
			y = Y;
			z = Z;
			w = W;
		}

		inline float operator [] (int i) const
		{
			return ((float*)this)[i];
		}

		inline float& operator [] (int i)
		{
			return ((float*)this)[i];
		}

		inline Vector4& operator += (const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		inline Vector4& operator -= (const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			return *this;
		}

		inline Vector4& operator *= (const Vector4& v)
		{
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;

			return *this;
		}

		inline Vector4& operator /= (const Vector4& v)
		{
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;

			return *this;
		}

		inline Vector4& operator += (float v)
		{
			x += v;
			y += v;
			z += v;
			w += v;

			return *this;
		}

		inline Vector4& operator -= (float v)
		{
			x -= v;
			y -= v;
			z -= v;
			w -= v;

			return *this;
		}

		inline Vector4& operator *= (float v)
		{
			x *= v;
			y *= v;
			z *= v;
			w *= w;

			return *this;
		}

		inline Vector4& operator /= (float v)
		{
			x /= v;
			y /= v;
			z /= v;
			w /= v;

			return *this;
		}

		inline Vector4 operator - () const
		{
			return Vector4(-x, -y, -z, -w);
		}

		inline Vector4 operator - (const Vector4& v) const
		{
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		inline Vector4 operator + (const Vector4& v) const
		{
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		inline Vector4 operator * (const Vector4& v) const
		{
			return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		inline Vector4 operator / (const Vector4& v) const
		{
			return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
		}

		inline float Length() const
		{
			return sqrtf(x * x + y * y + z * z + w * w);
		}

		inline float LengthSqr() const
		{
			return (x * x + y * y + z * z + w * w);
		}

		inline float LengthXY() const
		{
			return sqrtf(x * x + y * y);
		}

		inline float LengthXZ() const
		{
			return sqrtf(x * x + z * z);
		}

		inline bool IsZero() const
		{
			return (x > -0.01f && x < 0.01f
				&& y > -0.01f && y < 0.01f
				&& z > -0.01f && z < 0.01f
				&& w > -0.01f && w < 0.01f);
		}

		inline float DistTo(const Vector4& v) const
		{
			return (*this - v).Length();
		}

		inline float DistToSqr(const Vector4& v) const
		{
			return (*this - v).LengthSqr();
		}

		inline float Dot(const Vector4& v) const
		{
			return (x * v.x + y * v.y + z * v.z + w * v.w);
		}
	};

	inline Vector4 operator * (float f, const Vector4& v)
	{
		return v * f;
	}

	inline float Vector3Normalize(Vector3& v)
	{
		float fLength = v.Length();

		if (fLength != 0.0f)
			v /= fLength;
		else
			v.Init();

		return fLength;
	}

	class matrix3x4_t
	{
	public:
		float m[3][4];

		inline matrix3x4_t()
		{
			memset(this, 0, sizeof(matrix3x4_t));
		}

		inline float* operator [] (int i)
		{
			return m[i];
		}

		inline const float* operator [] (int i) const
		{
			return m[i];
		}
	};

	class VMatrix
	{
	public:
		float m[4][4];

		inline VMatrix()
		{
			memset(this, 0, sizeof(VMatrix));
		}

		inline float* operator [] (int i)
		{
			return m[i];
		}

		inline const float* operator [] (int i) const
		{
			return m[i];
		}
	};

	inline void SinCos(float r, float* s, float* c)
	{
		__asm
		{
			fld dword ptr[r]
			fsincos
			mov edx, dword ptr[c]
			mov eax, dword ptr[s]
			fstp dword ptr[edx]
			fstp dword ptr[eax]
		}
	}

	inline float SSE_sqrt(float x)
	{
		float root = 0.0f;

		__asm
		{
			sqrtss xmm0, x
			movss root, xmm0
		}

		return root;
	}

	inline float SSE_rsqrt(float x)
	{
		float rroot = 0.0f;

		__asm
		{
			rsqrtss xmm0, x
			movss rroot, xmm0
		}

		return ((0.5f * rroot) * (3.0f - (x * rroot) * rroot));
	}

	inline void Vector3Angles(const Vector3& forward, Vector3& angles)
	{
		float tmp, yaw, pitch;

		if (forward.x == 0 && forward.y == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else
		{
			yaw = RAD2DEG(atan2(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.LengthXY();

			pitch = RAD2DEG(atan2(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}

		angles.x = pitch;
		angles.y = yaw;
		angles.z = 0;
	}

	inline void Vector3Angles(const Vector3& forward, const Vector3& pseudoup, Vector3& angles)
	{
		Vector3 left = pseudoup.Cross(forward);

		Vector3Normalize(left);

		float dist = forward.LengthXY();

		if (dist > 0.001f)
		{
			angles.x = RAD2DEG(atan2(-forward.z, dist));
			angles.y = RAD2DEG(atan2(forward.y, forward.x));

			float up_z = (left.y * forward.x) - (left.x * forward.y);

			angles.z = RAD2DEG(atan2(left.z, up_z));
		}
		else
		{
			angles.x = RAD2DEG(atan2(-forward.z, dist));
			angles.y = RAD2DEG(atan2(-left.x, left.y));
			angles.z = 0;
		}
	}

	inline void AngleVector(const Vector3& angles, Vector3& forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;
	}

	inline void AngleVector(const Vector3& angles, Vector3& forward, Vector3& right, Vector3& up)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;

		right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right.y = (-1 * sr * sp * sy + -1 * cr * cy);
		right.z = -1 * sr * cp;

		up.x = (cr * sp * cy + -sr * -sy);
		up.y = (cr * sp * sy + -sr * cy);
		up.z = cr * cp;
	}

	inline void VectorTransform(const Vector3& in1, const matrix3x4_t& in2, Vector3& out)
	{
		out.x = in1.x * in2[0][0] + in1.y * in2[0][1] + in1.z * in2[0][2] + in2[0][3];
		out.y = in1.x * in2[1][0] + in1.y * in2[1][1] + in1.z * in2[1][2] + in2[1][3];
		out.z = in1.x * in2[2][0] + in1.y * in2[2][1] + in1.z * in2[2][2] + in2[2][3];
	}

	inline void LimitAngles(Vector3& angles)
	{
		if (angles.x < -89.0f)
			angles.x = -89.0f;

		if (angles.x > 89.0f)
			angles.x = 89.0f;

		if (angles.y < -180.0f)
			angles.y += 360.0f;

		if (angles.y > 180.0f)
			angles.y -= 360.0f;
	}

	inline float LimitAngle(float angle)
	{
		float ret = angle;

		while (ret < -180) ret += 360;
		while (ret > 180) ret -= 360;

		return ret;
	}

	inline void CrossProduct(const float* a, const float* b, float* r)
	{
		r[0] = a[1] * b[2] - a[2] * b[1];
		r[1] = a[2] * b[0] - a[0] * b[2];
		r[2] = a[0] * b[1] - a[1] * b[0];
	}

	inline float Vector3Normalize(float* v)
	{
		return Vector3Normalize(*(Vector3*)v);
	}

	inline void Vector3Rotate(const Vector3& in1, const matrix3x4_t& in2, Vector3& out)
	{
		out.x = in1.Dot(Vector3(in2[0]));
		out.y = in1.Dot(Vector3(in2[1]));
		out.z = in1.Dot(Vector3(in2[2]));
	}

	inline void AngleMatrix(const Vector3& angles, matrix3x4_t& matrix)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;

		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = (sp * crcy + srsy);
		matrix[1][2] = (sp * crsy - srcy);
		matrix[2][2] = cr * cp;
	}

	inline void Vector3Copy(const Vector3& src, Vector3& dst)
	{
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}

	inline void Vector3Rotate(const Vector3& in1, const Vector3& in2, Vector3& out)
	{
		matrix3x4_t mat;

		AngleMatrix(in2, mat);

		Vector3Rotate(in1, mat, out);
	}

	inline void ClampAngles(Vector3& angles)
	{
		if (angles.y < -180.0f)
			angles.y += 360.0f;
		if (angles.y > 180.0f)
			angles.y -= 360.0f;

		if (angles.x < -89.0f)
			angles.x = -89.0f;
		if (angles.x > 89.0f)
			angles.x = 89.0f;
	}

	const Vector2 vec2_zero(0, 0);
	const Vector3 vec3_zero(0, 0, 0);
	const Vector4 vec4_zero(0, 0, 0, 0);
}

#endif // MATH_H