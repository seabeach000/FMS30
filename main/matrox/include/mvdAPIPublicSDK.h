//==========================================================================;
//
// (c) Copyright Matrox Electronic Systems Ltd., 2002. All rights reserved.
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
//--------------------------------------------------------------------------;


//----------------------------------------------------------------
//                    mvdAPIPublicSDK.h
//----------------------------------------------------------------
// @module  Matrox Video DirectShow public interfaces.
//
//----------------------------------------------------------------
//   Birth Date:       February 2005
//   Operating System: WinXP
//   Author:           DirectShow team
//----------------------------------------------------------------
//   Matrox Electronic Systems Ltd.
//   Dorval, Quebec, Canada
//----------------------------------------------------------------

#ifndef _MVDAPIPUBLICSDK_H_
#define _MVDAPIPUBLICSDK_H_

// Our defines
#include "mvdDef.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Interfaces definitions
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MGF Reader
#include "IMvMGFReader.h"
#include "IMvMGF2Reader.h"

// MGF Writer
#include "IMvMGFWriter.h"
#include "IMvMGF2Writer.h"

// MGF file info.
#include "IMvMGFFileInfo.h"

// GFX Reader
#include "IMvGFXReader.h"
// GFX Writer
#include "IMvGFXWriter.h"

// GFX file info.
#include "IMvGFXFileInfo.h"

// interfaces for Device Control.
#include "IMvExtTransport.h"
#include "IMvUnifiedDeviceControlInit.h"
#include "IMvUnifiedDeviceControl.h"
#include "IMvEnumExtDeviceControl.h"

#endif /* _MVDAPIPUBLICSDK_H_ */

