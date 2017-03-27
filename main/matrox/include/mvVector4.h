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
// Summary
//	4 components vector abstraction class.
//
class CMvVector4 :
   public SMvVector4
{
public:

   //
   // Default constructor.  Initializes to (0,0,0,0).
   //
   CMvVector4(void)
	{
		fx = 0.0f;
		fy = 0.0f;
		fz = 0.0f;
		fw = 0.0f;
	}

   //
   // Summary:
   //	   Constructor. 
   //
   CMvVector4(
				  float in_fX,   // X value of the vector.
				  float in_fY,   // Y value of the vector.
				  float in_fZ,   // Z value of the vector.
				  float in_fW    // W value of the vector.
             )
	{
		fx = in_fX;
		fy = in_fY;
		fz = in_fZ;
		fw = in_fW;
	}

   //
   // Summary:
   //	   Copy constructor. 
   //
   CMvVector4(
				  const SMvVector4& in_rv  // Vector to copy in the current vector.
             )
	{
		fx = in_rv.fx;
		fy = in_rv.fy;
		fz = in_rv.fz;
		fw = in_rv.fw;
	}

   //
   // Summary:
   //	   Destructor.
   //
   virtual ~CMvVector4(void)
	{
	}

   // 
   // Public Members Functions
   //
   //------------------------------------------------
   // Lenght Related Functions
   //------------------------------------------------

   //
   // Summary:
   //	Computes the square magnitude of the vector.
   // Return value:
   //	- (x*x)+(y*y)+(z*z)+(w*w)
   //
   float SquareMagnitude ()
	{
		return ((fx * fx) + (fy * fy) + (fz * fz) + (fw * fw));
	}

   //
   // Summary:
   //	Computes the magnitude of the vector.
   // Return value:
   //	- sqrt((x*x)+(y*y)+(z*z)+(w*w))
   //
   float Magnitude ()
	{
		return (float) sqrt(SquareMagnitude());
	}
   
   //
   // Summary:
   //	Normalizes the vector.
   //
   void Normalize ()
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
   
   //
   // Summary:
   //	Returns the minimum component of the vector. 
   // Return value
   //	- min(x,y,z,w)
   //
   float Min ()
	{
		float ret = fx;
		if(fy < ret) ret = fy;
		if(fz < ret) ret = fz;
		if(fw < ret) ret = fw; 
		return ret;
	}
   
   //
   // Summary:
   //	Returns the maximum component of the vector.
   // Return value:
   //	- max(x,y,z,w)
   //
   float Max ()
	{
		float ret = fx;
		if(ret < fy) ret = fy;
		if(ret < fz) ret = fz;
		if(ret < fw) ret = fw;
		return ret;
	}

   //------------------------------------------------
   //Product Functions
   //------------------------------------------------

   //
   // Summary:
   //	   Computes the dot product between the current vector and a vector received as parameter.
   // Return value:
   //	   - Dot product.
   //
   float DotProduct(
						  const SMvVector4& in_rsVector // Second vector.
                   )
	{
		return ((fx * in_rsVector.fx) + (fy * in_rsVector.fy) + (fz * in_rsVector.fz) + (fw * in_rsVector.fw));
	}

   //------------------------------------------------
   // Access Grant
   //------------------------------------------------

   //
   // Summary:
   //	   Gives accesses to each component of the vector.
   // Parameters:
   //	i - 
   // Return value:
   //	   - The selected component.
   //
   const float& operator[] (
									 int i    // The index of the component to return.
                           ) const
	{
		if(i == 0)
		{
			return (fx);
		}

		if(i == 1)
		{
			return (fy);
		}

		if(i == 2)
		{
			return (fz);
		}

		return (fw);
	}
   
   //
   // Summary:
   //	   Gives accesses to each component of the vector.
   // Return value:
   //	   - The selected component.
   //
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

		if(i == 2)
		{
			return (fz);
		}

		return (fw);
	}

   //------------------------------------------------
   //Assignemt Operators
   //------------------------------------------------
   CMvVector4&    operator+= (const SMvVector4& in_rsVector)
	{
		fx += in_rsVector.fx;   
		fy += in_rsVector.fy;   
		fz += in_rsVector.fz;
		fw += in_rsVector.fw;

		return *this;
	}

   CMvVector4&    operator-= (const SMvVector4& in_rsVector)
	{
		fx -= in_rsVector.fx;   
		fy -= in_rsVector.fy;   
		fz -= in_rsVector.fz;
		fw -= in_rsVector.fw;

		return *this;
	}

   CMvVector4&    operator*= (const SMvVector4& in_rsVector)
	{
		fx *= in_rsVector.fx;   
		fy *= in_rsVector.fy;  
		fz *= in_rsVector.fz;
		fw *= in_rsVector.fw;

		return *this;
	}

   CMvVector4&    operator/= (const SMvVector4& in_rsVector)
	{
		fx /= in_rsVector.fx;   
		fy /= in_rsVector.fy;   
		fz /= in_rsVector.fz;
		fw /= in_rsVector.fw;

		return *this;
	}

   CMvVector4&    operator*= (float in_fs)
	{
		fx *= in_fs;   
		fy *= in_fs;   
		fz *= in_fs;
		fw *= in_fs;

		return *this;
	}

   CMvVector4&    operator/= (float in_fs)
	{
		fx /= in_fs;   
		fy /= in_fs;   
		fz /= in_fs;
		fw /= in_fs;

		return *this;
	}

   CMvVector4&    operator*= (const SMvMatrix& in_rsMatrix)
	{
		CMvVector4 result;

		result.fx = in_rsMatrix.uMvMatrix.m[0][0]*fx + in_rsMatrix.uMvMatrix.m[1][0]*fy + in_rsMatrix.uMvMatrix.m[2][0]*fz + in_rsMatrix.uMvMatrix.m[3][0]*fw;
		result.fy = in_rsMatrix.uMvMatrix.m[0][1]*fx + in_rsMatrix.uMvMatrix.m[1][1]*fy + in_rsMatrix.uMvMatrix.m[2][1]*fz + in_rsMatrix.uMvMatrix.m[3][1]*fw;
		result.fz = in_rsMatrix.uMvMatrix.m[0][2]*fx + in_rsMatrix.uMvMatrix.m[1][2]*fy + in_rsMatrix.uMvMatrix.m[2][2]*fz + in_rsMatrix.uMvMatrix.m[3][2]*fw; 
		result.fw = in_rsMatrix.uMvMatrix.m[0][3]*fx + in_rsMatrix.uMvMatrix.m[1][3]*fy + in_rsMatrix.uMvMatrix.m[2][3]*fz + in_rsMatrix.uMvMatrix.m[3][3]*fw; 

		*this = result;
		return *this;
	}


   //------------------------------------------------
   //Binary Operators
   //------------------------------------------------
   CMvVector4    operator+ (const SMvVector4& in_rsVector)
	{
		CMvVector4 ret( (fx + in_rsVector.fx), 
			(fy + in_rsVector.fy), 
			(fz + in_rsVector.fz),
			(fw + in_rsVector.fw));
		return ret;
	}

   CMvVector4    operator- (const SMvVector4& in_rsVector)
	{
		CMvVector4 ret( (fx - in_rsVector.fx), 
			(fy - in_rsVector.fy), 
			(fz - in_rsVector.fz),
			(fw - in_rsVector.fw));
		return ret;
	}

   CMvVector4    operator* (const SMvVector4& in_rsVector)
	{
		CMvVector4 ret( (fx * in_rsVector.fx), 
			(fy * in_rsVector.fy), 
			(fz * in_rsVector.fz),
			(fw * in_rsVector.fw));
		return ret;
	} 

   CMvVector4    operator* (float in_fs)
	{
		CMvVector4 ret (in_fs*fx, in_fs*fy, in_fs*fz, in_fs*fw);
		return ret;
	}

   CMvVector4    operator/ (float in_fs)
	{
		CMvVector4 ret(fx/in_fs, fy/in_fs, fz/in_fs, fw/in_fs);
		return ret;
	}

   CMvVector4    operator/ (const SMvVector4& in_rsVector)
	{
		CMvVector4 ret( (fx / in_rsVector.fx), 
			(fy / in_rsVector.fy), 
			(fz / in_rsVector.fz),
			(fw / in_rsVector.fw));
		return ret;
	}

   CMvVector4    operator* (const SMvMatrix &in_rsMatrix)
	{
		CMvVector4 result;

		result.fx = in_rsMatrix.uMvMatrix.m[0][0]*fx + in_rsMatrix.uMvMatrix.m[1][0]*fy + in_rsMatrix.uMvMatrix.m[2][0]*fz + in_rsMatrix.uMvMatrix.m[3][0]*fw;
		result.fy = in_rsMatrix.uMvMatrix.m[0][1]*fx + in_rsMatrix.uMvMatrix.m[1][1]*fy + in_rsMatrix.uMvMatrix.m[2][1]*fz + in_rsMatrix.uMvMatrix.m[3][1]*fw;
		result.fz = in_rsMatrix.uMvMatrix.m[0][2]*fx + in_rsMatrix.uMvMatrix.m[1][2]*fy + in_rsMatrix.uMvMatrix.m[2][2]*fz + in_rsMatrix.uMvMatrix.m[3][2]*fw; 
		result.fw = in_rsMatrix.uMvMatrix.m[0][3]*fx + in_rsMatrix.uMvMatrix.m[1][3]*fy + in_rsMatrix.uMvMatrix.m[2][3]*fz + in_rsMatrix.uMvMatrix.m[3][3]*fw; 

		return result;
	}


   //------------------------------------------------
   // Comparasion Functions
   //------------------------------------------------
   int operator< (const SMvVector4& in_rsVector)
	{
		return fx < in_rsVector.fx && fy < in_rsVector.fy && fz < in_rsVector.fz && fw < in_rsVector.fw;
	}

   int operator<=(const SMvVector4& in_rsVector)
	{
		return fx <= in_rsVector.fx && fy <= in_rsVector.fy && fz <= in_rsVector.fz && fw <= in_rsVector.fw;
	}
	
   int operator==(const SMvVector4& in_rsVector)
	{
		return fx==in_rsVector.fx && fy==in_rsVector.fy && fz==in_rsVector.fz && fw==in_rsVector.fw;
	}

   int operator> (const SMvVector4& in_rsVector)
	{
		return fx > in_rsVector.fx && fy > in_rsVector.fy && fz > in_rsVector.fz && fw > in_rsVector.fw;
	}

   int operator>=(const SMvVector4& in_rsVector)
	{
		return fx >= in_rsVector.fx && fy >= in_rsVector.fy && fz >= in_rsVector.fz && fw >= in_rsVector.fw;
	}

};

