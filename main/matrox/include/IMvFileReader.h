
#ifndef __INTERFACE_FILE_READER_H__
#define __INTERFACE_FILE_READER_H__

#include "guiddef.h"
// {C8FE3757-E5BC-4b86-A8D0-FE68BDABB723}
DEFINE_GUID(IID_IMvFileReader, 
            0xc8fe3757, 0xe5bc, 0x4b86, 0xa8, 0xd0, 0xfe, 0x68, 0xbd, 0xab, 0xb7, 0x23);

#include "mvSmartPtr.h"
#include "mvFlexApi.h"
#include "mvFlexDefinitions.h"
#include "mvdDef.h"

typedef TMvSmartPtr <IMvSurface> TAPIMvSurface;
typedef TMvSmartPtr <IMvAudioSamples> TAPIMvAudioSamples;

interface IMvFileReader : public IUnknown
{
   public:
      static IMvFileReader * Create( IMvFlexEngine * in_pIFlexEngine );
      ~IMvFileReader() {};

      virtual bool __stdcall OpenFileW( wchar_t * in_pFilename ) = 0;
      virtual bool __stdcall OpenFile( char * in_pFilename ) = 0;
      virtual void __stdcall CloseFile() = 0;

      virtual bool __stdcall IsVideoValid() = 0;
      virtual bool __stdcall IsAudioValid() = 0;

      virtual bool __stdcall GetAVFileInfo( SMvAudioVideoFileInfo & in_rsInfo ) = 0;

      virtual bool __stdcall GetAudioSamplesDescription( SMvAudioSamplesDescription & io_rsDesc ) = 0;

      virtual bool __stdcall GetSurfaceDescription( SMvSurfaceDescription & io_rsDesc ) = 0;

      // Synchronous read of the file
      virtual bool __stdcall GetAudioSamples(   unsigned long in_ulFrameIndex,
                                                TAPIMvAudioSamples & io_rJIMvAudioSamples ) = 0;

      virtual bool __stdcall GetFrame( unsigned long in_ulFrameIndex,
                                       TAPIMvSurface & io_rJSurface ) = 0;
      virtual bool __stdcall GetFields( unsigned long   in_ulFrameIndex,
                                        TAPIMvSurface & io_rJSurfaceF0,
                                        TAPIMvSurface & io_rJSurfaceF1 ) = 0;

      virtual bool __stdcall GetFrameAndVBI( unsigned long in_ulFrameIndex,
                                             TAPIMvSurface & io_rJSurface,
                                             TAPIMvSurface & io_rJVBISurface) = 0;

      virtual bool __stdcall GetFieldsAndVBI( unsigned long   in_ulFrameIndex,
                                              TAPIMvSurface & io_rJSurfaceF0,
                                              TAPIMvSurface & io_rJSurfaceF1,
                                              TAPIMvSurface & io_rJVBISurfaceF0,
                                              TAPIMvSurface & io_rJVBISurfaceF1) = 0;

      virtual bool __stdcall GetHResult( HRESULT*   io_pHr) = 0;

};

typedef TMvSmartPtr <IMvFileReader> TAPIMvFileReader;

#endif //__INTERFACE_FILE_READER_H__