//////////////////////////////////////////////////////////////////////////////////
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2001-2015. All rights reserved. 
//
//  This software code is subject to the terms and conditions outlined 
//  in the non-disclosure agreement between Matrox and your company. 
//  By accessing this code or using it in any way, you indicate your 
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind, 
//  either expressed or implied, including but not limited to the implied 
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
//  changes in specifications and code at any time and without notice. 
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for 
//  its use; nor for any infringements of patents or other rights of 
//  third parties resulting from its use. No license is granted under 
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//////////////////////////////////////////////////////////////////////////////////
#ifndef MVHARDWAREID_H
#define MVHARDWAREID_H


//// Child device's Hardware ID
#define kszVideoClockID            "MatroxVideoBus\\00000010"
#define kszVideoInputID            "MatroxVideoBus\\00000011"
#define kszVideoOutputID           "MatroxVideoBus\\00000012"
#define kszABobID                  "MatroxVideoBus\\00000013"
#define kszHDBobID                 "MatroxVideoBus\\00000014"
#define kszProxyID                 "MatroxVideoBus\\00000015"
#define kszMemoryManagerID0        "MatroxVideoBus\\00000016"
#define kszMemoryManagerID1        "MatroxVideoBus\\00000017"
#define kszMemoryManagerID2        "MatroxVideoBus\\00000018"
#define kszTransferID              "MatroxVideoBus\\00000019"
#define kszOnBoardComponentID      "MatroxVideoBus\\0000001A"
#define kszScalerID                "MatroxVideoBus\\0000001B"
#define kszMiscID                  "MatroxVideoBus\\0000001C"
#define kszAudioBusID              "MatroxVideoBus\\0000001D"

#define kszOnBoardIO               "MatroxVideoBus\\0000002A"
#define kszAudioInputID	           "MatroxVideoBus\\0000002B"
#define kszAudioOutputID           "MatroxVideoBus\\0000002C"
#define kszOnBoardIODSXLE          "MatroxVideoBus\\0000002D"
#define kszVideoCompositor         "MatroxVideoBus\\0000002E"
#define kszAudioWdmID              "MatroxVideoBus\\0000002F"
#define kszOnBoardXopen            "MatroxVideoBus\\00000030"
#define kszOnBoardMXO              "MatroxVideoBus\\00000032"
#define kszAVCCodec                "MatroxVideoBus\\00000033"
#define kszAVCio                   "MatroxVideoBus\\00000034"
#define kszAdvancedVideoCompositor "MatroxVideoBus\\00000035"
#define kszMxo2Codec               "MatroxVideoBus\\00000036"
#define kszDeInterlacer            "MatroxVideoBus\\00000037"
#define kszNodeTransferID          "MatroxVideoBus\\00000038"
#define kszTopologyID              "MatroxVideoBus\\00000039"
#define kszSerialPort              "MatroxVideoBus\\0000003A"
#define kszSerialOutput            "MatroxVideoBus\\0000003B"

#define kszAudioCapture            "MatroxAudioBus\\00000000"
#define kszAudioPlayback           "MatroxAudioBus\\00000001"
#define kszAudioCaptureRaw         "MatroxAudioBus\\00000002"
#define kszAudioPlaybackRaw        "MatroxAudioBus\\00000003"

// Registry key name
#define kszBoardName                "BoardName"
#define kszDeviceName               "DeviceName"
#define kszBoardNumber              "BoardNumber"
#define kszDeviceNumber             "DeviceNumber"
#define kszChangeBoardName          "ChangeBoardName"
#define kszNewBoardName             "NewBoardName"
#define kwszBoardName               L"BoardName"
#define kwszDeviceName              L"DeviceName"
#define kwszBoardNumber             L"BoardNumber"
#define kwszDeviceNumber            L"DeviceNumber"
#define kwszChangeBoardName         L"ChangeBoardName"
#define kwszNewBoardName            L"NewBoardName"

// For the board name
#define kszDSX1000                  "DSX1000"
#define kszDSX1000IO                kszDSX1000 "IO"
#define kszDSX1000FX                kszDSX1000 "FX"
#define kszDSX1000DX                kszDSX1000 "DX"
#define kszDSXio                    kszDSX1000IO
#define kszDSXfx                    kszDSX1000FX

#define kszDSXmio                   "DSXmio"
#define kszDSXmiofx                 kszDSXmio "FX"
#define kszDSXmioDX                 kszDSXmio "DX"
#define kszDSXmioDXwGPUPb           kszDSXmio "DX with GPU Playback"

#define kszDSXmio2                  "DSXmio2"
#define kszDSXmio2fx                kszDSXmio2 "FX"
#define kszDSXmio2DX                kszDSXmio2 "DX"

#define kszDXBoardOnly              "DX Board Only"

#define kszDSXLE                    "DSXLE"
#define kszDSXLEDX                  kszDSXLE "DX"
#define kszDSXLEFX                  kszDSXLE "FX"

#define kszDSXLE3                   "DSXLE3"
#define kszDSXLE3DX                 kszDSXLE3 "DX"


#define kszDSXSD                    "DSXSD"
#define kszDSXSDDX                  kszDSXSD "DX"

#define kszXopen                    "X.open"
#define kwszXopen                   L"X.open"
#define kszXopenfx                  kszXopen "FX"
#define kszXopenDX                  kszXopen "DX"

#define kszMXO                      "MXO"
#define kszMXOwGPUpb                kszMXO "with GPU Playback"
#define kszMXODXwGPUpb              kszMXO "DX with GPU Playback"

#define kszRTX2                     "RT.X2"
#define kszRTX2DX                   kszRTX2 "DX"

#define kszUSBDongle                "X.Key"
#define kszUSBDongleDX              kszUSBDongle "DX"

#define kszDSXAVCio                    "AVCio"
#define kszDSXAVCioDX                  kszDSXAVCio "DX"

#define kszMXO2                     "MXO2"
#define kszMXO2DX                   kszMXO2 "DX"

#define kszMAX	                    "X264"
#define kwszMAX                    L"X264"
#define kszMAXDX	                 kszMAX "DX"

#define kszX264io                    "X264io"
#define kszX264ioDX                  kszX264io "DX"
#define kszDSXmio2Plus              "DSXmio2 Plus"
#define kszDSXmio2PlusDX             kszDSXmio2Plus "DX"

#define kszDSXmio3                  "DSXmio3"
#define kszDSXmio3DX                 kszDSXmio3 "DX"

#define kszDSXle4                  "DSXle4"
#define kszDSXle4DX                 kszDSXle4 "DX"

#define kszDSXmio3fh                  "DSXmio3fh"
#define kszDSXmio3fhDX                 kszDSXmio3fh "DX"

#define kszDSXle4fh                  "DSXle4fh"
#define kszDSXle4fhDX                 kszDSXle4fh "DX"

// For Device information szInformationString
#define kszDeviceNameXLink             "X.linkSD"
#define kszDeviceNameXLinkHD           "X.linkHD"
#define kszDeviceNameXIOCard           "X.io Card"
#define kszDeviceNameXIScalerHDCard    "X.scalerHD Card"
#define kszDeviceNameDSXmio_04         "X.mio /04 Card"
#define kszDeviceNameDSXmio_12         "X.mio /12 Card"
#define kszDeviceNameDSXmio_13         "X.mio /13 Card"
#define kszDeviceNameDSXmio_20         "X.mio /20 Card"
#define kszDeviceNameDSXmio_24         "X.mio /24 Card"
#define kszDeviceNameDSXmio2_04        "X.mio2 /04 Card"
#define kszDeviceNameDSXmio2_12        "X.mio2 /12 Card"
#define kszDeviceNameDSXmio2_12_plus   "X.mio2 /12+ Card"
#define kszDeviceNameDSXmio2_13        "X.mio2 /13 Card"
#define kszDeviceNameDSXmio2_20        "X.mio2 /20 Card"
#define kszDeviceNameDSXmio2_21        "X.mio2 /21 Card"
#define kszDeviceNameDSXmio2_24        "X.mio2 /24 Card"
#define kszDeviceNameDSXmio2_40        "X.mio2 /40 Card"
#define kszDeviceNameDSXmio2_41        "X.mio2 /41 Card"
#define kszDeviceNameDSXmio2_44        "X.mio2 /44 Card"

#define kszDeviceNameDSXLE             "LE Card"
#define kszDeviceNameDSXSD             "SD Card"
#define kszDeviceNameRTX2              "RT.X2 Card"
#define kszDeviceNameXopen             "X.open Card"
#define kszDeviceNameMXO               "MXO"
#define kszDeviceNameCNVTDVI		   "Convert DVI"
#define kszDeviceNameCNVTDVIPLUS	   "Convert DVI Plus"
#define kszDeviceNameUSBDongle         "X.Key /100"
#define kszDeviceNameDSXAVCio          "AVCio Card"
#define kszDeviceNameMXO2              "MXO2"
#define kszDeviceNameMAX			   "CompressHD"
#define kszDeviceNameX264			   "X264 Coprocessor"
#define kszDeviceNameX264io		       "X264io Card"
#define kszDeviceNameMOJITO            "Mojito"
#define kszDeviceNameDSXmio2Plus       "X.mio2 Plus Card"
#define kszDeviceNameDSXLE3_22C   "LE3 /22C Card"
#define kszDeviceNameDSXLE3_22S   "LE3 /22S Card"
#define kszDeviceNameDSXLE3_12S   "LE3 /12S Card"
#define kszDeviceNameDSXLE3_04S   "LE3 /04S Card"
#define kszDeviceNameDSXLE3_40S   "LE3 /40S Card"
#define kszDeviceNameDSXLE3_VS4   "VS4 Card"
#define kszDeviceNameMOJITO_4K    "Mojito 4K"
#define kszDeviceNameDSXLE3_4KO   "LE3 /4KO Card"
#define kszDeviceNameDSXLE3_VS4_PRO   "VS4 Pro Card"
#define kszDeviceNameMOJITO2          "Mojito2"

#endif // MVHARDWAREID_H

