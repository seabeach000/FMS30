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

//////////////////////////////////////////////////////////////////////////
//
// Summary:
//	   Matrix abstraction class.
// Description:
//    This class is a matrix manipulation helper class.
//
//////////////////////////////////////////////////////////////////////////
class CMvMatrix : public SMvMatrix
{
public:

   // Summary:
   // Default constructor.  Initializes to the identity matrix.
   //
   CMvMatrix ()
	{
		Identity();
	}

   // Summary:
   //	   Copy constructor.  Initializes the internal matrix to the given one. 
   CMvMatrix (
				  const CMvMatrix& in_roMatrix  // Matrix to copy in the current matrix.
             )
	{
		memcpy(uMvMatrix.m, in_roMatrix.uMvMatrix.m, sizeof(float)*16);
	}
   
   // Summary:
   //	   Constructor. Initalizes the internal matrix with the given values.
   CMvMatrix (
				  float in_f11,  // Value for the cell[1][1] of the matrix.
				  float in_f12,  // Value for the cell[1][2] of the matrix.
				  float in_f13,  // Value for the cell[1][3] of the matrix.
				  float in_f14,  // Value for the cell[1][4] of the matrix.

               
				  float in_f21,  // Value for the cell[2][1] of the matrix.
			     float in_f22,  // Value for the cell[2][2] of the matrix.
			     float in_f23,  // Value for the cell[2][3] of the matrix.
			     float in_f24,  // Value for the cell[2][4] of the matrix.
         
			     float in_f31,  // Value for the cell[3][1] of the matrix.
				  float in_f32,  // Value for the cell[3][2] of the matrix.
				  float in_f33,  // Value for the cell[3][3] of the matrix.
				  float in_f34,  // Value for the cell[3][4] of the matrix.

				  float in_f41,  // Value for the cell[4][1] of the matrix.
				  float in_f42,  // Value for the cell[4][2] of the matrix.
				  float in_f43,  // Value for the cell[4][3] of the matrix.
				  float in_f44   // Value for the cell[4][4] of the matrix.
             )
	{
		uMvMatrix.sMvMatrixElement._11 = in_f11;
		uMvMatrix.sMvMatrixElement._12 = in_f12;
		uMvMatrix.sMvMatrixElement._13 = in_f13;
		uMvMatrix.sMvMatrixElement._14 = in_f14;

		uMvMatrix.sMvMatrixElement._21 = in_f21;
		uMvMatrix.sMvMatrixElement._22 = in_f22;
		uMvMatrix.sMvMatrixElement._23 = in_f23;
		uMvMatrix.sMvMatrixElement._24 = in_f24;

		uMvMatrix.sMvMatrixElement._31 = in_f31;
		uMvMatrix.sMvMatrixElement._32 = in_f32;
		uMvMatrix.sMvMatrixElement._33 = in_f33;
		uMvMatrix.sMvMatrixElement._34 = in_f34;

		uMvMatrix.sMvMatrixElement._41 = in_f41;
		uMvMatrix.sMvMatrixElement._42 = in_f42;
		uMvMatrix.sMvMatrixElement._43 = in_f43;
		uMvMatrix.sMvMatrixElement._44 = in_f44;

	}

   // Summary:
   //    Destructor.
   virtual ~CMvMatrix ()
	{
	}

   //
   // Public Member Functions
   //
   //-----------------------------------------------
   // Creation functions
   //-----------------------------------------------
   //
   
   // Summary:
   //	   Initializes the internal matrix to a rotation matrix from the given angles in radians.
   void CreateRotationMatrixXYZ (
										   float in_fAngleX,    // Rotation in radians around the x-axis.
											float in_fAngleY,    // Rotation in radians around the y-axis.
											float in_fAngleZ     // Rotation in radians around the z-axis.
                                )
	{
		//
		// This function is equivalent (and much faster!)
		// to MatrixRotZ*MatrixRotY*MatrixRotX
		//
		double dCosX = cos(in_fAngleX);
		double dCosY = cos(in_fAngleY);
		double dCosZ = cos(in_fAngleZ);
		double dSinX = sin(in_fAngleX);
		double dSinY = sin(in_fAngleY);
		double dSinZ = sin(in_fAngleZ);

		uMvMatrix.m[0][0] = (float)(dCosY*dCosZ);
		uMvMatrix.m[1][0] = (float)((dSinX*dSinY*dCosZ)-(dCosX*dSinZ));
		uMvMatrix.m[2][0] = (float)((dCosX*dSinY*dCosZ)+(dSinX*dSinZ));
		uMvMatrix.m[3][0] = 0.0f;

		uMvMatrix.m[0][1] = (float)(dCosY*dSinZ);
		uMvMatrix.m[1][1] = (float)((dSinX*dSinY*dSinZ)+(dCosX*dCosZ));
		uMvMatrix.m[2][1] = (float)((dCosX*dSinY*dSinZ)-(dSinX*dCosZ));
		uMvMatrix.m[3][1] = 0.0f;

		uMvMatrix.m[0][2] = (float)(-dSinY);
		uMvMatrix.m[1][2] = (float)(dSinX*dCosY);
		uMvMatrix.m[2][2] = (float)(dCosX*dCosY);
		uMvMatrix.m[3][2] = 0.0f;

		uMvMatrix.m[0][3] = 0.0f;
		uMvMatrix.m[1][3] = 0.0f;
		uMvMatrix.m[2][3] = 0.0f;
		uMvMatrix.m[3][3] = 1.0f;
	}

   // Summary:
   //	   Initializes the internal matrix to a rotation matrix around the x-axis from the given angle in radians.
   void CreateRotationMatrixX (
										 float in_fAngleX  // Rotation in radians around the x-axis.
                              )
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);

		uMvMatrix.m[0][0] = uMvMatrix.m[3][3] = 1.0f;
		uMvMatrix.m[1][1] = uMvMatrix.m[2][2] = (float)(cos(in_fAngleX));
		uMvMatrix.m[2][1] = -(float)sin(in_fAngleX);
		uMvMatrix.m[1][2] = (float)sin(in_fAngleX);
	}
   
   // Summary:
   //	   Initializes the internal matrix to a rotation matrix around the y-axis from the given angle in radians.
   void CreateRotationMatrixY (
										 float in_fAngleY  // Rotation in radians around the y-axis.
                              )
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);

		uMvMatrix.m[1][1] = uMvMatrix.m[3][3] = 1.0f;
		uMvMatrix.m[0][0] = uMvMatrix.m[2][2] = (float)cos(in_fAngleY);
		uMvMatrix.m[0][2] = -(float)sin(in_fAngleY);
		uMvMatrix.m[2][0] = (float)sin(in_fAngleY);
	}
   
   // Summary:
   //	   Initializes the internal matrix to a rotation matrix around the z-axis from the given angle in radians.
   void CreateRotationMatrixZ (
										 float in_fAngleZ  // Rotation in radians around the z-axis.
                              )
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);

		uMvMatrix.m[2][2] = uMvMatrix.m[3][3] = 1.0f;
		uMvMatrix.m[0][0] = uMvMatrix.m[1][1] = (float)cos(in_fAngleZ);
		uMvMatrix.m[1][0] = -(float)sin(in_fAngleZ);
		uMvMatrix.m[0][1] = (float)sin(in_fAngleZ);
	}
   
   // Summary:
   //	   Initializes the internal matrix to a translation matrix from the given offset in pixels.
   void CreateTranslationMatrix (
											float in_fOffsetX,   // Translation along the x-axis.
											float in_fOffsetY,   // Translation along the y-axis.
											float in_fOffsetZ    // Translation along the z-axis.
                                )
	{
		Identity();

		uMvMatrix.m[3][0] = in_fOffsetX;
		uMvMatrix.m[3][1] = in_fOffsetY;
		uMvMatrix.m[3][2] = in_fOffsetZ;
	}										
   
   // Summary:
   //	   Initializes the internal matrix to a scale matrix from the given scale factors.
   void CreateScaleMatrix (
									float in_fScaleX,    // Scaling along the x-axis.
									float in_fScaleY,    // Scaling along the y-axis.
									float in_fScaleZ     // Scaling along the z-axis.
                          )
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);
		uMvMatrix.m[0][0] = in_fScaleX;
		uMvMatrix.m[1][1] = in_fScaleY;
		uMvMatrix.m[2][2] = in_fScaleZ;
		uMvMatrix.m[3][3] = 1.0f;
	}

   //------------------------------------------------
   // Assignation Functions
   //------------------------------------------------
  
   // Summary:
   //	   Sets all the components of the internal matrix to 0.
   void Zero()
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);
	}
   
   //
   // Summary:
   //	   Changes the internal matrix in an identity matrix.
   //
   void Identity()
	{
		memset(uMvMatrix.m, 0, sizeof(float)*16);
		uMvMatrix.m[0][0] = 
			uMvMatrix.m[1][1] = 
			uMvMatrix.m[2][2] = 
			uMvMatrix.m[3][3] = 1.0f;
	}

   // Summary:
   //	   Transposes the current matrix.
   void Transpose()
	{
		SMvMatrix sTemp;

		//
		// Copy the original matrix
		//
		memcpy(&sTemp.uMvMatrix.m, &uMvMatrix.m, sizeof(SMvMatrix));

		//
		// Write the transposed
		//
		for (int i=0; i<4; i++) 
		{
			for (int j=0; j<4; j++)	
			{
				uMvMatrix.m[i][j] = sTemp.uMvMatrix.m[j][i];
			}
		}
	}

   //------------------------------------------------
   // Analyze Functions
   //------------------------------------------------
   
   // Summary:
   // 	Checks if the matrix is the identity matrix.
   bool IsIdentity()
	{
		if(uMvMatrix.m[0][0] == 1 && uMvMatrix.m[0][1] == 0 && uMvMatrix.m[0][2] == 0 && uMvMatrix.m[0][3] == 0 && 
			uMvMatrix.m[1][0] == 0 && uMvMatrix.m[1][1] == 1 && uMvMatrix.m[1][2] == 0 && uMvMatrix.m[1][3] == 0 && 
			uMvMatrix.m[2][0] == 0 && uMvMatrix.m[2][1] == 0 && uMvMatrix.m[2][2] == 1 && uMvMatrix.m[2][3] == 0 && 
			uMvMatrix.m[3][0] == 0 && uMvMatrix.m[3][1] == 0 && uMvMatrix.m[3][2] == 0 && uMvMatrix.m[3][3] == 1)
		{
			return true;
		}

		return false;
	}

   //------------------------------------------------
   // Transformation Matrix Functions
   //------------------------------------------------  

   // Summary:
   //	   Translates the current internal matrix along the x-axis. (Multiplies the current matrix by a translation matrix). 
   void TranslateX (
						  float in_fdX   // Amount of translation along the x-axis.
                   )
	{
		uMvMatrix.sMvMatrixElement._41 += in_fdX;
	}

   // Summary:
   //	   Translates the current internal matrix along the y-axis. (Multiplies the current matrix by a translation matrix). 
   void TranslateY (
						  float in_fdY   // Amount of translation along the y-axis.
                   )
	{
		uMvMatrix.sMvMatrixElement._42 += in_fdY;
	}

   // Summary:
   //	   Translates the current internal matrix along the z-axis. (Multiplies the current matrix by a translation matrix). 
   void TranslateZ (
						  float in_fdZ   // Amount of translation along the z-axis.
                   )
	{
		uMvMatrix.sMvMatrixElement._43 += in_fdZ;
	}
   
   // Summary:
   //	   Translates the current internal matrix along the 3 axis. (Multiplies the current matrix by a translation matrix). 
   void Translate (
						 float in_fdX,  // Amount of translation along the x-axis.
						 float in_fdY,  // Amount of translation along the y-axis.
						 float in_fdZ   // Amount of translation along the z-axis.
                  )
	{
		uMvMatrix.sMvMatrixElement._41 += in_fdX;
		uMvMatrix.sMvMatrixElement._42 += in_fdY;
		uMvMatrix.sMvMatrixElement._43 += in_fdZ;
	}

   // Summary:
   //	   Rotates the current internal matrix around the x-axis. (Multiply the current matrix by a rotation matrix). 
   void RotateX (
					  float in_fAngleX  // Amount of rotation in radians around the x-axis.
                )
	{
		CMvMatrix oTemp;
		oTemp.CreateRotationMatrixX(in_fAngleX);

		*this = (*this)*oTemp;
	}
   
   // Summary:
   //	   Rotates the current internal matrix around the y-axis. (Multiply the current matrix by a rotation matrix). 
   void RotateY (
					  float in_fAngleY  // Amount of rotation in radians around the y-axis.
                )
	{
		CMvMatrix oTemp;
		oTemp.CreateRotationMatrixY(in_fAngleY);

		*this = (*this)*oTemp;
	}
   
   // Summary:
   //	   Rotates the current internal matrix around the z-axis. (Multiply the current matrix by a rotation matrix). 
   void RotateZ (
					  float in_fAngleZ  // Amount of rotation in radians around the z-axis.
                )
	{
		CMvMatrix oTemp;
		oTemp.CreateRotationMatrixZ(in_fAngleZ);

		*this = (*this)*oTemp;
	}
   
   // Summary:
   //	   Rotates the current internal matrix around the 3 axis. (Multiply the current matrix by a rotation matrix). 
   void Rotate (
					 float in_fAngleX,    // Amount of rotation in radians around the x-axis.
					 float in_fAngleY,    // Amount of rotation in radians around the y-axis.
					 float in_fAngleZ     // Amount of rotation in radians around the z-axis.
               )
	{
		CMvMatrix oTemp;
		oTemp.CreateRotationMatrixXYZ(in_fAngleX, in_fAngleY, in_fAngleZ);

		*this = (*this)*oTemp;
	}

   // Summary: 
   //		Scales the current internal matrix along the x-axis. (Multiply the current matrix by a scaling matrix). 
   void ScaleX (
					 float in_fsX   // Amount of scaling along the x-axis.
               )
	{
		uMvMatrix.sMvMatrixElement._11 *= in_fsX;
		uMvMatrix.sMvMatrixElement._21 *= in_fsX;
		uMvMatrix.sMvMatrixElement._31 *= in_fsX;
		uMvMatrix.sMvMatrixElement._41 *= in_fsX;
	}
   
   // Summary: 
   //		Scales the current internal matrix along the y-axis. (Multiply the current matrix by a scaling matrix). 
   void ScaleY (
					 float in_fsY   // Amount of scaling along the y-axis.
               )
	{
		uMvMatrix.sMvMatrixElement._12 *= in_fsY;
		uMvMatrix.sMvMatrixElement._22 *= in_fsY;
		uMvMatrix.sMvMatrixElement._32 *= in_fsY;
		uMvMatrix.sMvMatrixElement._42 *= in_fsY;
	}
   
   // Summary: 
   //		Scales the current internal matrix along the z-axis. (Multiply the current matrix by a scaling matrix). 
   void ScaleZ (
					 float in_fsZ   // Amount of scaling along the z-axis.
               )
	{
		uMvMatrix.sMvMatrixElement._13 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._23 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._33 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._43 *= in_fsZ;
	}
   
   // Summary: 
   //		Scales the current internal matrix along the 3 axis. (Multiply the current matrix by a scaling matrix). 
   void Scale (
					float in_fsX,  // Amount of scaling along the x-axis.
					float in_fsY,  // Amount of scaling along the y-axis.
					float in_fsZ   // Amount of scaling along the z-axis.
              )
	{
		uMvMatrix.sMvMatrixElement._11 *= in_fsX;
		uMvMatrix.sMvMatrixElement._21 *= in_fsX;
		uMvMatrix.sMvMatrixElement._31 *= in_fsX;
		uMvMatrix.sMvMatrixElement._41 *= in_fsX;

		uMvMatrix.sMvMatrixElement._12 *= in_fsY;
		uMvMatrix.sMvMatrixElement._22 *= in_fsY;
		uMvMatrix.sMvMatrixElement._32 *= in_fsY;
		uMvMatrix.sMvMatrixElement._42 *= in_fsY;

		uMvMatrix.sMvMatrixElement._13 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._23 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._33 *= in_fsZ;
		uMvMatrix.sMvMatrixElement._43 *= in_fsZ;
	}

   //------------------------------------------------
   // Operators
   //------------------------------------------------


   // Summary:
   //    Returns the float value in the internal matrix at the request row and column.
   float& operator() (
							 int in_iRow,   // Requested 0-based row of the matrix.
							 int in_iColumn // Requested 0-based column of the matrix.
                     )
	{
		return uMvMatrix.m[in_iRow][in_iColumn]; 
	}

   // Summary:
   //    Returns the float value in the internal matrix at the request row and column. (Constant version).
   const float& operator() (
									 int in_iRow,   // Requested 0-based row of the matrix.
									 int in_iColumn // Requested 0-based column of the matrix.
                           ) const
	{ 
		return uMvMatrix.m[in_iRow][in_iColumn]; 
	}

   // Summary:
   //    Assigns the given matrix to the internal matrix.
   CMvMatrix operator= (
								const SMvMatrix &in_rkoMatrix // Matrix to assign to the current matrix object.
                       )
	{
		memcpy(uMvMatrix.m, in_rkoMatrix.uMvMatrix.m, sizeof(float)*16);

		return (*this);
	}
   
   // Summary:
   //    Multiple the given matrix by the internal matrix and return the result matrix.  This doesn't modify the internal matrix.
   CMvMatrix operator* (
								const SMvMatrix &in_rkoMatrix // Matrix to multiply.
                       )
	{
		CMvMatrix oRet;

		oRet.Zero();

		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				for (int k=0; k<4; k++)
				{
					oRet.uMvMatrix.m[i][j] += this->uMvMatrix.m[i][k] * in_rkoMatrix.uMvMatrix.m[k][j];
				}
			}
		}

		return oRet;
	}

   // Summary:
   //    Multiple each component of the internal matrix by the given float and return the result matrix.  This doesn't modify the internal matrix.
   CMvMatrix operator* (
								const float      &in_rkfMult // Value to multiply to each component of the internal matrix.
                       )
	{
		CMvMatrix oRet;

		for (int i=0; i<4; i++)
		{
			for (int j=0; j<4; j++)
			{
				oRet.uMvMatrix.m[i][j] = uMvMatrix.m[i][j] * in_rkfMult;  
			}
		}

		return oRet;
	}

   // Summary:
   //    Return the internal matrix.
   SMvMatrix  GetMatrix()
	{
		return *(dynamic_cast<SMvMatrix*> (this));
	}

   //------------------------------------------------
   // Creation Methods
   //------------------------------------------------
   
   // Summary:
   //	   Copies the matrix received as parameter into the current matrix.
   void SetMatrix (
						 SMvMatrix *in_psMatrix  // Source matrix.
                  )
	{
		*(dynamic_cast<SMvMatrix*> (this)) = *in_psMatrix;
	}
   
   // Summary:
   //	   Creates a view matrix from a view description and assigns it to the internal matrix.
   void CreateView (
						  SMvViewDesc *in_psView  // View matrix properties structure.
                   )
	{  
		CMvVector3 sZAxis(in_psView->sViewerDirection.fx - in_psView->sViewerPosition.fx, 
			in_psView->sViewerDirection.fy - in_psView->sViewerPosition.fy, 
			in_psView->sViewerDirection.fz - in_psView->sViewerPosition.fz);

		sZAxis.Normalize();

		CMvVector3 sXAxis;
		sXAxis.CrossProduct(in_psView->sViewerUp, sZAxis);
		sXAxis.Normalize();

		CMvVector3 sYAxis;
		sYAxis.CrossProduct(sZAxis, sXAxis);

		uMvMatrix.sMvMatrixElement._11 = sXAxis.fx;
		uMvMatrix.sMvMatrixElement._12 = sYAxis.fx;
		uMvMatrix.sMvMatrixElement._13 = sZAxis.fx;
		uMvMatrix.sMvMatrixElement._14 = 0;

		uMvMatrix.sMvMatrixElement._21 = sXAxis.fy;
		uMvMatrix.sMvMatrixElement._22 = sYAxis.fy;
		uMvMatrix.sMvMatrixElement._23 = sZAxis.fy;
		uMvMatrix.sMvMatrixElement._24 = 0;

		uMvMatrix.sMvMatrixElement._31 = sXAxis.fz;
		uMvMatrix.sMvMatrixElement._32 = sYAxis.fz;
		uMvMatrix.sMvMatrixElement._33 = sZAxis.fz;
		uMvMatrix.sMvMatrixElement._34 = 0;

		uMvMatrix.sMvMatrixElement._41 = -sXAxis.DotProduct(in_psView->sViewerPosition);
		uMvMatrix.sMvMatrixElement._42 = -sYAxis.DotProduct(in_psView->sViewerPosition);
		uMvMatrix.sMvMatrixElement._43 = -sZAxis.DotProduct(in_psView->sViewerPosition);
		uMvMatrix.sMvMatrixElement._44 = 1;
	}

   //
   // Summary:
   //	   Creates a projection matrix from a projection description structure and assigns it to the internal matrix.
   //
   void CreateProjection (
								  SMvProjectionDesc *in_psProjection  // Projection matrix properties structure.
                         )
	{
		float h = 1.0f/tanf(in_psProjection->fFovY/2.0f);
		float w = h / in_psProjection->fAspect;

		uMvMatrix.sMvMatrixElement._11 = w;
		uMvMatrix.sMvMatrixElement._12 = 0;
		uMvMatrix.sMvMatrixElement._13 = 0;
		uMvMatrix.sMvMatrixElement._14 = 0;

		uMvMatrix.sMvMatrixElement._21 = 0;
		uMvMatrix.sMvMatrixElement._22 = h;
		uMvMatrix.sMvMatrixElement._23 = 0;
		uMvMatrix.sMvMatrixElement._24 = 0;

		uMvMatrix.sMvMatrixElement._31 = 0;
		uMvMatrix.sMvMatrixElement._32 = 0;
		uMvMatrix.sMvMatrixElement._33 = in_psProjection->fFarZ/(in_psProjection->fFarZ-in_psProjection->fNearZ); //zf/(zf-zn)
		uMvMatrix.sMvMatrixElement._34 = 1;

		uMvMatrix.sMvMatrixElement._41 = 0;
		uMvMatrix.sMvMatrixElement._42 = 0;
		uMvMatrix.sMvMatrixElement._43 = -in_psProjection->fNearZ * uMvMatrix.sMvMatrixElement._33; // -zn*zf/(zf-zn)
		uMvMatrix.sMvMatrixElement._44 = 0;
	}

};

