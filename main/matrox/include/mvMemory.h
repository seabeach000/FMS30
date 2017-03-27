//==========================================================================;
//
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
//
//==========================================================================;
//                    mvMemory.h
//==========================================================================;
// @module  Matrox Video
//==========================================================================;
//   Birth Date:             April 10 2008
//   Operating System:       Vista
//   Author:                 Christian Bechette
//==========================================================================;
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//==========================================================================;

#ifndef mvMemory_H
#define mvMemory_H

#include "_MvFlexAPI.h"
// this class is used as a silence buffer memory to send to the AAC codec
// this class is used to store the AVC configuration data
// it will be attached as a custom object to the flex samples/surfaces

class CMvMemory 
: public IMvAVCSetupData
, public CMvUnknown
{
public:
   CMvMemory( wchar_t* in_pwchName, uint32_t in_ui32Size )
      : CMvUnknown( in_pwchName, NULL )
   {
      // allocate the memory
      m_pui8Buffer = new uint8_t[in_ui32Size];
      
      if ( m_pui8Buffer )
         m_ui32SizeInBytes = in_ui32Size;
      else 
         m_ui32SizeInBytes = 0;

      // debug
      wcscpy_s( m_awchName, MAX_PATH, in_pwchName );

      ASSERT( m_pui8Buffer );
   }

   virtual ~CMvMemory()
   {
      if ( m_pui8Buffer != NULL )
         delete[] m_pui8Buffer;
      m_pui8Buffer = NULL;
   }

   // retrieve the setup data
   void __stdcall GetSetupData( uint8_t** out_ppui8Buffer, uint32_t* out_pui32BufferSize )
   {
      *out_ppui8Buffer     = m_pui8Buffer;
      *out_pui32BufferSize = m_ui32SizeInBytes;
   }

   MVDECLARE_IUNKNOWN;

   HRESULT __stdcall NonDelegatingQueryInterface( REFIID in_rIID, void** out_ppv )
   {
      if ( in_rIID == IID_IMvAVCSetupData )
      {
         return MvGetInterface( dynamic_cast<IMvAVCSetupData*>( this ), out_ppv );
      }
      else
      {
         return CMvUnknown::NonDelegatingQueryInterface( in_rIID, out_ppv );
      }
   }

   uint8_t* m_pui8Buffer;
   uint32_t m_ui32SizeInBytes;
   wchar_t  m_awchName[MAX_PATH];
};

#endif // mvMemory_H
