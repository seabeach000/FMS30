
#ifndef __INTERFACE_FILE_INFO_H__
#define __INTERFACE_FILE_INFO_H__

#include "guiddef.h"
// {CAD3F5A8-572C-4448-BAFB-D35ABBED923B}
DEFINE_GUID(IID_IMvFileInfo, 
0xcad3f5a8, 0x572c, 0x4448, 0xba, 0xfb, 0xd3, 0x5a, 0xbb, 0xed, 0x92, 0x3b);

#include "mvSmartPtr.h"             // TMvSmartPtr
#include "mvFlexApiPublicSDK.h"
#include "mvFlexDefinitions.h"
#include "mvdDef.h"                 // SMvAudioVideoFileInfo

interface IMvFileInfo : public IUnknown
{
   public:
      static IMvFileInfo * Create();
      ~IMvFileInfo() {};

      virtual bool __stdcall GetAVFileInfo( char    * in_pFilename, SMvAudioVideoFileInfo & io_rsInfo ) = 0;
      virtual bool __stdcall GetAVFileInfoW( wchar_t * in_pFilename, SMvAudioVideoFileInfo & io_rsInfo ) = 0;
};

typedef TMvSmartPtr <IMvFileInfo> TAPIMvFileInfo;

#endif //__INTERFACE_FILE_INFO_H__