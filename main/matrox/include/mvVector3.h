//==============================================================================
// (c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 
//
// This code and information is provided "as is" without warranty of any kind, 
// either expressed or implied, including but not limited to the implied 
// warranties of merchantability and/or fitness for a particular purpose.
//
// Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
// changes in specifications and code at any time and without notice. 
// No responsibility is assumed by Matrox Electronic Systems Ltd. for 
// its use; nor for any infringements of patents or other rights of 
// third parties resulting from its use. No license is granted under 
// any patents or patent rights of Matrox Electronic Systems Ltd.
//===============================================================================
#pragma once

#ifdef LINUX_PLATFORM
	#include "mvLinuxDefinitions.h"
#else
	#include <windows.h>
	#include <unknwn.h>
#endif

#include <math.h>
#include "mvFlex3DDeviceStructs.h"
#include "mvVector3.h"

//
// Summary:
//	3 components vector abstraction class.
//
class CMvVector3 : public SMvVector3
{
public:
   
   // Summary
   //    Default constructor.  Initializes the internal vector to (0,0,0).
   CMvVector3(void)
	{
		fx = 0.0f;
		fy = 0.0f;
		fz = 0.0f;
	}

   // Summary:
   //	   Constructor.  Initializes the internal vector to the given values.
   CMvVector3 (
					float in_fX,   // X value of the vector.
					float in_fY,   // Y value of the vector.
					float in_fZ    // Z value of the vector.
              )
	{
		fx = in_fX;
		fy = in_fY;
		fz = in_fZ;
	}

   // Summary:
   //	   Copy constructor. Initializes the internal vector to the given vector.
   CMvVector3 (
					const SMvVector3& in_rv  // Vector to copy in the internal vector.
              )
	{
		fx = in_rv.fx;
		fy = in_rv.fy;
		fz = in_rv.fz;
	}
   
   // Summary
   //    Destructor.
   virtual ~CMvVector3(void)
	{
	}

   // 
   // Public Members Functions
   //

   //------------------------------------------------
   // Lenght Related Functions
   //------------------------------------------------

   // Summary:
   //	   Computes and returns the square magnitude of the internal vector.
   // Return value:
   //	   - (x*x)+(y*y)+(z*z)
   float SquareMagnitude()
	{
		return ( (fx * fx) + (fy * fy) + (fz * fz) );
	}

   // Summary:
   //	   Computes and return the magnitude of the internal vector.
   // Return value:
   //	   - sqrt((x*x)+(y*y)+(z*z))
   float Magnitude()
	{
		return (float) sqrt(SquareMagnitude());
	}

   // Summary:
   //	   Normalizes the internal vector.
   void Normalize()
	{
		float fMagnitude;

		fMagnitude = Magnitude();

		if (fMagnitude == 0.0f)
			return;

		*this /= fMagnitude;
	}

   //------------------------------------------------
   //Return the Min/Max Component of input Vector
   //------------------------------------------------

   // Summary:
   //	   Returns the minimum component of the internal vector. 
   // Return value:
   //	   - min(x,y,z)
   float Min()
	{
		float ret = fx;
		if (fy < ret) ret = fy;
		if (fz < ret) ret = fz;
		return ret;
	}

   // Summary:
   //	   Returns the maximum component of the internal vector.
   // Return value:
   //	   - max(x,y,z)
   float Max()
	{
		float ret = fx;
		if (ret < fy) ret = fy;
		if (ret < fz) ret = fz;
		return ret;
	}

   //------------------------------------------------
   //Product Functions
   //------------------------------------------------

   // Summary:
   //	   Computes the dot product between the current vector and the vector received as a parameter.
   // Return value:
   //	   - Dot product.
   float DotProduct (
							const SMvVector3& in_rsOperand2  // Second vector.
                    )
	{
		return ( (fx * in_rsOperand2.fx) + (fy * in_rsOperand2.fy) + (fz * in_rsOperand2.fz) );
	}

   // Summary:
   //    Computes a cross product between two vectors and assigns it
   //    to the current vector.
   void CrossProduct (
							 const SMvVector3& in_rsOperand1, // First vector.
							 const SMvVector3& in_rsOperand2  // Second vector.
                     )
	{
		fx = (in_rsOperand1.fy * in_rsOperand2.fz) - (in_rsOperand1.fz * in_rsOperand2.fy);
		fy = (in_rsOperand1.fz * in_rsOperand2.fx) - (in_rsOperand1.fx * in_rsOperand2.fz);
		fz = (in_rsOperand1.fx * in_rsOperand2.fy) - (in_rsOperand1.fy * in_rsOperand2.fx);
	}

   // Summary:
   //    Computes the cross product between the current vector and a
   //    vector received as a parameter.  Does not modify the internal vector.
   // Returns
   //   - The Cross product vector.                                           
   SMvVector3 CrossProduct (
									 const SMvVector3& in_rsOperand2  // Second vector.
                           )
	{
		SMvVector3 sOutVector;

		sOutVector.fx = (fy * in_rsOperand2.fz) - (fz * in_rsOperand2.fy);
		sOutVector.fy = (fz * in_rsOperand2.fx) - (fx * in_rsOperand2.fz);
		sOutVector.fz = (fx * in_rsOperand2.fy) - (fy * in_rsOperand2.fx);

		return (sOutVector);
	}

   //------------------------------------------------
   // Access Grant
   //------------------------------------------------
   
   // Summary:
   //	   Gives accesses to each component of the vector.
   // Return Value:
   //	   - The selected component.
   const float& operator[] (
									 int i    // The index of the component to return.
                           ) const
	{
		if (i == 0)
		{
			return (fx);
		}
		if (i == 1)
		{
			return (fy);
		}
		return (fz);
	}
   
   // Summary:
   //	   Gives accesses to each component of the vector.
   // Return value:
   //	   - The selected component.
   float& operator[] (
							 int i    // The index of the component to return.
                     )
	{
		if (i == 0)
		{
			return (fx);
		}

		if (i == 1)
		{
			return (fy);
		}

		return (fz);
	}

   //------------------------------------------------
   //Assignment Operators
   //------------------------------------------------

   // Summary:
   //    Adds the given vector to the internal vector, keeps the result in the internal vector and returns the result.
   CMvVector3& operator+= (const SMvVector3& in_rsVector)
	{
		fx += in_rsVector.fx;   fy += in_rsVector.fy;   fz += in_rsVector.fz;
		return *this;
	}

   // Summary:
   //    Substracts the given vector from the internal vector, keeps the result in the internal vector and returns the result.
   CMvVector3& operator-= (const SMvVector3& in_rsVector)
	{
		fx -= in_rsVector.fx;   fy -= in_rsVector.fy;   fz -= in_rsVector.fz;
		return *this;
	}

   // Summary:
   //    Multiplies the given vector to the internal vector, keeps the result in the internal vector and returns the result.
   CMvVector3& operator*= (const SMvVector3& in_rsVector)
	{
		fx *= in_rsVector.fx;   fy *= in_rsVector.fy;   fz *= in_rsVector.fz;
		return *this;
	}

   // Summary:
   //    Divides the given vector from the internal vector, keeps the result in the internal vector and returns the result.
   CMvVector3& operator/= (const SMvVector3& in_rsVector)
	{
		fx /= in_rsVector.fx;   fy /= in_rsVector.fy;   fz /= in_rsVector.fz;
		return *this;
	}

   // Summary:
   //    Multiplies the given matrix to the internal vector, keeps the result in the internal vector and returns the result.
   CMvVector3& operator*= (const SMvMatrix& in_rsMatrix)
	{
		CMvVector3 result;

		result.fx = in_rsMatrix.uMvMatrix.m[0][0]*fx + in_rsMatrix.uMvMatrix.m[1][0]*fy + in_rsMatrix.uMvMatrix.m[2][0]*fz + in_rsMatrix.uMvMatrix.m[3][0];
		result.fy = in_rsMatrix.uMvMatrix.m[0][1]*fx + in_rsMatrix.uMvMatrix.m[1][1]*fy + in_rsMatrix.uMvMatrix.m[2][1]*fz + in_rsMatrix.uMvMatrix.m[3][1];
		result.fz = in_rsMatrix.uMvMatrix.m[0][2]*fx + in_rsMatrix.uMvMatrix.m[1][2]*fy + in_rsMatrix.uMvMatrix.m[2][2]*fz + in_rsMatrix.uMvMatrix.m[3][2]; 

		*this = result;
		return *this;
	}

   // Summary:
   //    Multiplies the given value to all the internal vector components, keeps the result in the internal vector and returns the result.
   CMvVector3& operator*= (float in_fs)
	{
		fx *= in_fs;   fy *= in_fs;   fz *= in_fs;
		return *this;
	}

   // Summary:
   //    Divides the given value from the all internal vector components, keeps the result in the internal vector and returns the result.
   CMvVector3& operator/= (float in_fs)
	{
		fx /= in_fs;   fy /= in_fs;   fz /= in_fs;
		return *this;
	}

   //------------------------------------------------
   //Binary Operators
   //------------------------------------------------

   // Summary:
   //    Adds the given vector to the internal vector and returns the result.
   CMvVector3 operator+ (const SMvVector3& in_rsVector)
	{
		CMvVector3 ret( (fx + in_rsVector.fx), (fy + in_rsVector.fy), (fz + in_rsVector.fz) );
		return ret;
	}

   // Summary:
   //    Substracts the given vector from the internal vector and returns the result.
   CMvVector3 operator- (const SMvVector3& in_rsVector)
	{
		CMvVector3 ret( (fx - in_rsVector.fx), (fy - in_rsVector.fy), (fz - in_rsVector.fz) );
		return ret;
	}

   // Summary:
   //    Multiplies the given vector to the internal vector and returns the result.
   CMvVector3 operator* (const SMvVector3& in_rsVector)
	{
		CMvVector3 ret( (fx * in_rsVector.fx), (fy * in_rsVector.fy), (fz * in_rsVector.fz) );
		return ret;
	} 

   CMvVector3 operator/ (const SMvVector3& in_rsVector)
	{
		CMvVector3 ret( (fx / in_rsVector.fx), (fy / in_rsVector.fy), (fz / in_rsVector.fz) );
		return ret;
	}

   // Summary:
   //    Multiplies the given matrix to the internal vector and returns the result.
   CMvVector3 operator* (const SMvMatrix &in_rsMatrix)
	{
		CMvVector3 result;

		result.fx = in_rsMatrix.uMvMatrix.m[0][0]*fx + in_rsMatrix.uMvMatrix.m[1][0]*fy + in_rsMatrix.uMvMatrix.m[2][0]*fz + in_rsMatrix.uMvMatrix.m[3][0];
		result.fy = in_rsMatrix.uMvMatrix.m[0][1]*fx + in_rsMatrix.uMvMatrix.m[1][1]*fy + in_rsMatrix.uMvMatrix.m[2][1]*fz + in_rsMatrix.uMvMatrix.m[3][1];
		result.fz = in_rsMatrix.uMvMatrix.m[0][2]*fx + in_rsMatrix.uMvMatrix.m[1][2]*fy + in_rsMatrix.uMvMatrix.m[2][2]*fz + in_rsMatrix.uMvMatrix.m[3][2]; 

		return result;
	}
	
   CMvVector3 operator* (float in_fs)
	{
		CMvVector3 ret (in_fs*fx, in_fs*fy, in_fs*fz);
		return ret;
	}
	
   CMvVector3 operator/ (float in_fs)
	{
		CMvVector3 ret(fx/in_fs, fy/in_fs, fz/in_fs);
		return ret;
	}

   //------------------------------------------------
   // Comparison Functions
   //------------------------------------------------
   int operator< (const SMvVector3& in_rsVector)
	{
		return fx < in_rsVector.fx && fy < in_rsVector.fy && fz < in_rsVector.fz;
	}

   int operator<=(const SMvVector3& in_rsVector)
	{
		return fx <= in_rsVector.fx && fy <= in_rsVector.fy && fz <= in_rsVector.fz;
	}

   int operator==(const SMvVector3& in_rsVector)
	{
		return fx==in_rsVector.fx && fy==in_rsVector.fy && fz==in_rsVector.fz;
	}

   int operator> (const SMvVector3& in_rsVector)
	{
		return fx > in_rsVector.fx && fy > in_rsVector.fy && fz > in_rsVector.fz;
	}

   int operator>=(const SMvVector3& in_rsVector)
	{
		return fx >= in_rsVector.fx && fy >= in_rsVector.fy && fz >= in_rsVector.fz;
	}

};

