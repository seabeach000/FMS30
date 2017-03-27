/**
 @file	mccolorspace.h
 @brief Profile and Preset definitions for default codec settings

 @verbatim
 * File: mccolorspace.h
 *
 * Desc: static functions for getting color space information
 *
 * Copyright (c) 2015 MainConcept GmbH or its affiliates.  All rights reserved.
 *
 * MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.
 * This software is protected by copyright law and international treaties.  Unauthorized
 * reproduction or distribution of any portion is prohibited by law.
 *
 @endverbatim
 **/

#if !defined (__MC_COLORSPACE_INCLUDED__)
#define __MC_COLORSPACE_INCLUDED__

#include <string.h>
#include <stdlib.h>
#include "mcfourcc.h"
#include "mcdefs.h"

#define CS_FORMAT_UNKNOWN   0
#define CS_FORMAT_YUV       1
#define CS_FORMAT_RGB       2
#define CS_FORMAT_XYZ       3

typedef struct 
{
    uint32_t    fourcc;
    uint32_t    cs_type;
    uint32_t    bit_depth;
    int32_t     chroma_format;
    uint32_t    bits_per_pixel;
    uint32_t    pixels_per_macropixel;
    uint8_t     name[12];
    uint8_t     alternative_name[12];
} ColorSpaceBaseInfo_t;

static const ColorSpaceBaseInfo_t  g_ColorSpaceBaseInfoMap[] =
{
    //fourcc,           cs_type,    bit_depth, chroma_format, bits_per_pixel, pixels_per_macropixel, name,  alternative name
    // YUV
    {FOURCC_AYUV,	    CS_FORMAT_YUV,  8,	    CHROMA444,	        32,	            1,              "AYUV"          ,"" },
    {FOURCC_VUYA,	    CS_FORMAT_YUV,  8,	    CHROMA444,	        32,	            1,              "VUYA"	        ,"" },
    {FOURCC_YUY2,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "YUY2"	        ,"" },
    {FOURCC_YUYV,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "YUYV"	        ,"" },
    {FOURCC_YuYv,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "YuYv"	        ,"YUYVC" },
    {FOURCC_UYVY,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "UYVY"	        ,"" },
    {FOURCC_UyVy,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "UyVy"	        ,"UYVYC" },
    {FOURCC_YVYU,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "YVYU"	        ,"" },
    {FOURCC_VYUY,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "VYUY"	        ,"" },
    {FOURCC_Y41P,	    CS_FORMAT_YUV,  8,	    CHROMA411,	        12,	            8,              "Y41P"	        ,"" },
    {FOURCC_Y411,	    CS_FORMAT_YUV,  8,	    CHROMA411,	        12,	            8,              "Y411"          ,"" },
    {FOURCC_Y211,	    CS_FORMAT_YUV,  8,	    CHROMA211,	        8,	            4,              "Y211"	        ,"" },
    {FOURCC_CLJR,	    CS_FORMAT_YUV,  6,	    CHROMA411,	        8,	            4,              "CLJR"	        ,"" },
    {FOURCC_YVU9,	    CS_FORMAT_YUV,  8,	    CHROMA810,	        9,	            4,              "YVU9"	        ,"" },
    {FOURCC_YUV9,	    CS_FORMAT_YUV,  8,	    CHROMA810,	        9,	            4,              "YUV9"	        ,"" },
    {FOURCC_YV12,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "YV12"	        ,"" },
    {FOURCC_IYUV,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "IYUV"	        ,"" },
    {FOURCC_I420,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "I420"	        ,"" },
    {FOURCC_YV16,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "YV16"	        ,"" },
    {FOURCC_I422,	    CS_FORMAT_YUV,  8,	    CHROMA422,	        16,	            2,              "I422"	        ,"" },
    {FOURCC_YV24,	    CS_FORMAT_YUV,  8,	    CHROMA444,	        24,	            1,              "YV24"	        ,"" },
    {FOURCC_NV24,	    CS_FORMAT_YUV,  8,	    CHROMA444,	        24,	            1,              "NV24"	        ,"" },
    {FOURCC_I444,	    CS_FORMAT_YUV,  8,	    CHROMA444,	        24,	            1,              "I444"	        ,"" },
    {FOURCC_BGRA32F,	CS_FORMAT_YUV,  32,	    CHROMA444,	        128,	        1,              "BGRA32F"       ,"BGRAFP" },
    {FOURCC_VUYA32F,	CS_FORMAT_YUV,  32,	    CHROMA444,	        128,	        1,              "VUYA32F"       ,"VUYAFP" },
    {FOURCC_NV12,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "NV12"	        ,"" },
    {FOURCC_NV21,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "NV21"	        ,"" },
    {FOURCC_IMC1,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "IMC1"	        ,"" },
    {FOURCC_IMC2,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "IMC2"	        ,"" },
    {FOURCC_IMC3,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "IMC3"	        ,"" },
    {FOURCC_IMC4,	    CS_FORMAT_YUV,  8,	    CHROMA420,	        12,	            2,              "IMC4"	        ,"" },
    {FOURCC_v210,	    CS_FORMAT_YUV,  10,	    CHROMA422,	        20,	            6,              "v210"	        ,"V210" },
    {FOURCC_v216,	    CS_FORMAT_YUV,  16,	    CHROMA422,	        32,	            2,              "v216"	        ,"V216" },
    {FOURCC_Y210,	    CS_FORMAT_YUV,  10,	    CHROMA422,	        32,	            2,              "Y210"	        ,"" },
    {FOURCC_Y216,	    CS_FORMAT_YUV,  16,	    CHROMA422,	        32,	            2,              "Y216"	        ,"" },
    {FOURCC_Y410,	    CS_FORMAT_YUV,  10,	    CHROMA444,	        32,	            1,              "Y410"	        ,"" },
    {FOURCC_Y416,	    CS_FORMAT_YUV,  16,	    CHROMA444,	        64,	            1,              "Y416"	        ,"" },
    {FOURCC_P010,	    CS_FORMAT_YUV,  10,	    CHROMA420,	        24,	            2,              "P010"	        ,"" },
    {FOURCC_P016,	    CS_FORMAT_YUV,  16,	    CHROMA420,	        24,	            2,              "P016"	        ,"" },
    {FOURCC_P210,	    CS_FORMAT_YUV,  10,	    CHROMA422,	        32,	            2,              "P210"	        ,"" },
    {FOURCC_P216,	    CS_FORMAT_YUV,  16,	    CHROMA422,	        32,	            2,              "P216"	        ,"" },
    {FOURCC_W009,	    CS_FORMAT_YUV,  9,	    CHROMA420,	        24,	            2,              "W009"	        ,"" },
    {FOURCC_W010,	    CS_FORMAT_YUV,  10,	    CHROMA420,	        24,	            2,              "W010"	        ,"" },
    {FOURCC_W011,	    CS_FORMAT_YUV,  11,	    CHROMA420,	        24,	            2,              "W011"	        ,"" },
    {FOURCC_W012,	    CS_FORMAT_YUV,  12,	    CHROMA420,	        24,	            2,              "W012"	        ,"" },
    {FOURCC_W013,	    CS_FORMAT_YUV,  13,	    CHROMA420,	        24,	            2,              "W013"	        ,"" },
    {FOURCC_W014,	    CS_FORMAT_YUV,  14,	    CHROMA420,	        24,	            2,              "W014"	        ,"" },
    {FOURCC_W015,	    CS_FORMAT_YUV,  15,	    CHROMA420,	        24,	            2,              "W015"	        ,"" },
    {FOURCC_W016,	    CS_FORMAT_YUV,  16,	    CHROMA420,	        24,	            2,              "W016"	        ,"" },
    {FOURCC_W209,	    CS_FORMAT_YUV,  9,	    CHROMA422,	        32,	            2,              "W209"	        ,"" },
    {FOURCC_W210,	    CS_FORMAT_YUV,  10,	    CHROMA422,	        32,	            2,              "W210"	        ,"" },
    {FOURCC_W211,	    CS_FORMAT_YUV,  11,	    CHROMA422,	        32,	            2,              "W211"	        ,"" },
    {FOURCC_W212,	    CS_FORMAT_YUV,  12,	    CHROMA422,	        32,	            2,              "W212"	        ,"" },
    {FOURCC_W213,	    CS_FORMAT_YUV,  13,	    CHROMA422,	        32,	            2,              "W213"	        ,"" },
    {FOURCC_W214,	    CS_FORMAT_YUV,  14,	    CHROMA422,	        32,	            2,              "W214"	        ,"" },
    {FOURCC_W215,       CS_FORMAT_YUV,  15,     CHROMA422,          32,             2,              "W215"          ,"" },
    {FOURCC_W216,	    CS_FORMAT_YUV,  16,	    CHROMA422,	        32,	            2,              "W216"	        ,"" },
    {FOURCC_W409,	    CS_FORMAT_YUV,  9,	    CHROMA444,	        48,	            1,              "W409"	        ,"" },
    {FOURCC_W410,	    CS_FORMAT_YUV,  10,	    CHROMA444,	        48,	            1,              "W410"	        ,"" },
    {FOURCC_W411,	    CS_FORMAT_YUV,  11,	    CHROMA444,	        48,	            1,              "W411"	        ,"" },
    {FOURCC_W412,	    CS_FORMAT_YUV,  12,	    CHROMA444,	        48,	            1,              "W412"	        ,"" },
    {FOURCC_W413,	    CS_FORMAT_YUV,  13,	    CHROMA444,	        48,	            1,              "W413"	        ,"" },
    {FOURCC_W414,	    CS_FORMAT_YUV,  14,	    CHROMA444,	        48,	            1,              "W414"	        ,"" },
    {FOURCC_W415,	    CS_FORMAT_YUV,  15,	    CHROMA444,	        48,	            1,              "W415"	        ,"" },
    {FOURCC_W416,	    CS_FORMAT_YUV,  16,	    CHROMA444,	        48,	            1,              "W416"	        ,"" },
    {FOURCC_X009,	    CS_FORMAT_YUV,  9,	    CHROMA420,	        24,	            2,              "X009"	        ,"" },
    {FOURCC_X010,	    CS_FORMAT_YUV,  10,	    CHROMA420,	        24,	            2,              "X010"	        ,"" },
    {FOURCC_X011,	    CS_FORMAT_YUV,  11,	    CHROMA420,	        24,	            2,              "X011"	        ,"" },
    {FOURCC_X012,	    CS_FORMAT_YUV,  12,	    CHROMA420,	        24,	            2,              "X012"	        ,"" },
    {FOURCC_X013,	    CS_FORMAT_YUV,  13,	    CHROMA420,	        24,	            2,              "X013"	        ,"" },
    {FOURCC_X014,	    CS_FORMAT_YUV,  14,	    CHROMA420,	        24,	            2,              "X014"	        ,"" },
    {FOURCC_X015,	    CS_FORMAT_YUV,  15,	    CHROMA420,	        24,	            2,              "X015"	        ,"" },
    {FOURCC_X016,	    CS_FORMAT_YUV,  16,	    CHROMA420,	        24,	            2,              "X016"	        ,"" },
    {FOURCC_X209,	    CS_FORMAT_YUV,  9,	    CHROMA422,	        32,	            2,              "X209"	        ,"" },
    {FOURCC_X210,	    CS_FORMAT_YUV,  10,	    CHROMA422,	        32,	            2,              "X210"	        ,"" },
    {FOURCC_X211,	    CS_FORMAT_YUV,  11,	    CHROMA422,	        32,	            2,              "X211"	        ,"" },
    {FOURCC_X212,	    CS_FORMAT_YUV,  12,	    CHROMA422,	        32,	            2,              "X212"	        ,"" },
    {FOURCC_X213,	    CS_FORMAT_YUV,  13,	    CHROMA422,	        32,	            2,              "X213"	        ,"" },
    {FOURCC_X214,	    CS_FORMAT_YUV,  14,	    CHROMA422,	        32,	            2,              "X214"	        ,"" },
    {FOURCC_X215,	    CS_FORMAT_YUV,  15,	    CHROMA422,	        32,	            2,              "X215"	        ,"" },
    {FOURCC_X216,	    CS_FORMAT_YUV,  16,	    CHROMA422,	        32,	            2,              "X216"	        ,"" },
    {FOURCC_X409,	    CS_FORMAT_YUV,  9,	    CHROMA444,	        48,	            1,              "X409"	        ,"" },
    {FOURCC_X410,	    CS_FORMAT_YUV,  10,	    CHROMA444,	        48,	            1,              "X410"	        ,"" },
    {FOURCC_X411,	    CS_FORMAT_YUV,  11,	    CHROMA444,	        48,	            1,              "X411"	        ,"" },
    {FOURCC_X412,	    CS_FORMAT_YUV,  12,	    CHROMA444,	        48,	            1,              "X412"	        ,"" },
    {FOURCC_X413,	    CS_FORMAT_YUV,  13,	    CHROMA444,	        48,	            1,              "X413"	        ,"" },
    {FOURCC_X414,	    CS_FORMAT_YUV,  14,	    CHROMA444,	        48,	            1,              "X414"	        ,"" },
    {FOURCC_X415,	    CS_FORMAT_YUV,  15,	    CHROMA444,	        48,	            1,              "X415"	        ,"" },
    {FOURCC_X416,	    CS_FORMAT_YUV,  16,	    CHROMA444,	        48,	            1,              "X416"	        ,"" },
    {FOURCC_GRAY,	    CS_FORMAT_YUV,  8,	    CHROMA400,	        8,	            2,              "GRAY"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y09,	    CS_FORMAT_YUV,  9,	    CHROMA400,	        9,	            2,              "Y09"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y10,	    CS_FORMAT_YUV,  10,	    CHROMA400,	        10,	            2,              "Y10"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y11,	    CS_FORMAT_YUV,  11,	    CHROMA400,	        11,	            2,              "Y11"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y12,	    CS_FORMAT_YUV,  12,	    CHROMA400,	        12,	            2,              "Y12"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y13,	    CS_FORMAT_YUV,  13,	    CHROMA400,	        13,	            2,              "Y13"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y14,	    CS_FORMAT_YUV,  14,	    CHROMA400,	        14,	            2,              "Y14"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y15,	    CS_FORMAT_YUV,  15,	    CHROMA400,	        15,	            2,              "Y15"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_Y16,	    CS_FORMAT_YUV,  16,	    CHROMA400,	        16,	            2,              "Y16"	        ,"" },  // UCC doesn't support odd value of width for gray color spaces
    {FOURCC_410P,	    CS_FORMAT_YUV,  8,	    CHROMA410,	        10,	            4,              "410P"	        ,"yvu410" },
    {FOURCC_411P,	    CS_FORMAT_YUV,  8,	    CHROMA411,	        12,	            4,              "411P"	        ,"yvu411" },
    {FOURCC_211P,	    CS_FORMAT_YUV,  8,	    CHROMA211,	        8,	            4,              "211P"  	    ,"yvu211" },

    // RGB
    {FOURCC_ARGB,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "ARGB"	        ,"" },
    {FOURCC_argb,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "argb"	        ,"" },
    {FOURCC_BGRA,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "BGRA"	        ,"ARGB32" },
    {FOURCC_RGBA,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "RGBA"	        ,"" },
    {FOURCC_BGR4,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "BGR4"	        ,"RGB32" },
    {FOURCC_BGR3,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        24,	            1,              "BGR3"	        ,"RGB24" },
    {FOURCC_R565,	    CS_FORMAT_RGB,  6,	    CHROMA444,	        16,	            1,              "R565"	        ,"RGB565" },
    {FOURCC_R555,	    CS_FORMAT_RGB,  5,	    CHROMA444,	        16,	            1,              "R555"	        ,"RGB555" },
    {FOURCC_RGB3,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        24,	            1,              "RGB3"	        ,"" },
    {FOURCC_R24C,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        24,	            1,              "R24C"	        ,"" },
    {FOURCC_R32C,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        32,	            1,              "R32C"	        ,"" },
    {FOURCC_b64a,	    CS_FORMAT_RGB,  16,	    CHROMA444,	        64,	            1,              "b64a"	        ,"" },
    {FOURCC_R24P,	    CS_FORMAT_RGB,  8,	    CHROMA444,	        24,	            1,              "R24P"	        ,"rgb444" },
    {FOURCC_R27P,	    CS_FORMAT_RGB,  9,	    CHROMA444,	        48,	            1,              "R27P"	        ,"" },
    {FOURCC_R30P,	    CS_FORMAT_RGB,  10,	    CHROMA444,	        48,	            1,              "R30P"	        ,"" },
    {FOURCC_R33P,	    CS_FORMAT_RGB,  11,	    CHROMA444,	        48,	            1,              "R33P"	        ,"" },
    {FOURCC_R36P,	    CS_FORMAT_RGB,  12,	    CHROMA444,	        48,	            1,              "R36P"	        ,"" },
    {FOURCC_R39P,	    CS_FORMAT_RGB,  13,	    CHROMA444,	        48,	            1,              "R39P"	        ,"" },
    {FOURCC_R42P,	    CS_FORMAT_RGB,  14,	    CHROMA444,	        48,	            1,              "R42P"	        ,"" },
    {FOURCC_R45P,	    CS_FORMAT_RGB,  15,	    CHROMA444,	        48,	            1,              "R45P"	        ,"" },
    {FOURCC_R48P,	    CS_FORMAT_RGB,  16,	    CHROMA444,	        48,	            1,              "R48P"	        ,"R16G16B16P" },
    {FOURCC_AR10,	    CS_FORMAT_RGB,  10,	    CHROMA444,	        32,	            1,              "AR10"	        ,"A2R10G10B10" },
    {FOURCC_AB10,	    CS_FORMAT_RGB,  10,	    CHROMA444,	        32,	            1,              "AB10"	        ,"A2B10G10R10" },
    {FOURCC_DPX10,	    CS_FORMAT_RGB,  10,	    CHROMA444,	        32,	            1,              "DPX10"	        ,"DPXA" },

    // XYZ
    {FOURCC_XYZ8,	    CS_FORMAT_XYZ,  8,	    CHROMA444,	        24,	            1,              "XYZ8"	        ,"" },
    {FOURCC_XYZ12,	    CS_FORMAT_XYZ,  12,	    CHROMA444,	        48,	            1,              "XYZ12"         ,"XYZC" },
    {FOURCC_PLXYZ8,	    CS_FORMAT_XYZ,  8,	    CHROMA444,	        24,	            1,              "PLXYZ8"        ,"PL_XYZ8" },
    {FOURCC_PLXYZ9,	    CS_FORMAT_XYZ,  9,	    CHROMA444,	        48,	            1,              "PLXYZ9"        ,"PL_XYZ9" },
    {FOURCC_PLXYZ10,	CS_FORMAT_XYZ,  10,	    CHROMA444,	        48,	            1,              "PLXYZ10"       ,"PL_XYZ10" },
    {FOURCC_PLXYZ11,	CS_FORMAT_XYZ,  11,	    CHROMA444,	        48,	            1,              "PLXYZ11"       ,"PL_XYZ11" },
    {FOURCC_PLXYZ12,	CS_FORMAT_XYZ,  12,	    CHROMA444,	        48,	            1,              "PLXYZ12"       ,"PL_XYZ12" },
    {FOURCC_PLXYZ13,	CS_FORMAT_XYZ,  13,	    CHROMA444,	        48,	            1,              "PLXYZ13"       ,"PL_XYZ13" },
    {FOURCC_PLXYZ14,	CS_FORMAT_XYZ,  14,	    CHROMA444,	        48,	            1,              "PLXYZ14"       ,"PL_XYZ14" },
    {FOURCC_PLXYZ15,	CS_FORMAT_XYZ,  15,	    CHROMA444,	        48,	            1,              "PLXYZ15"       ,"PL_XYZ15" },
    {FOURCC_PLXYZ16,	CS_FORMAT_XYZ,  16,	    CHROMA444,	        48,	            1,              "PLXYZ16"       ,"PL_XYZ16" },
};
static const int32_t g_ColorSpaceBaseInfoMapSize = sizeof(g_ColorSpaceBaseInfoMap) / sizeof(ColorSpaceBaseInfo_t);

/** @brief Call this function to get human-readable name by fourcc.
*
* @param[in] fourcc format
* @return human-readable name\n
*         pointer to "unsupported cc" if FourCC format is unsupported
*/
const static inline uint8_t* get_name(uint32_t fourcc)
{
    int32_t i;
    for (i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if (g_ColorSpaceBaseInfoMap[i].fourcc == fourcc)
            return g_ColorSpaceBaseInfoMap[i].name;

    return (const uint8_t*)"unsupported color space";
}

/** @brief Call this function to get fourcc value by the human-readable name.
*
* @param[in] name the human-readable name
* @return fourcc value\n
*         0 if the human-readable name is unsupported or incorrect
*/
static inline uint32_t get_fourcc(const uint8_t* name)
{
    int32_t i;
    for (i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
    {
        uint8_t equal_names = !strcmp((const char*)name, (const char*)g_ColorSpaceBaseInfoMap[i].name);
        uint8_t equal_alternative_names = !!strcmp((const char*)"", (const char*)g_ColorSpaceBaseInfoMap[i].alternative_name) &&
            !strcmp((const char*)name, (const char*)g_ColorSpaceBaseInfoMap[i].alternative_name);
        if (equal_names	|| equal_alternative_names)
        {
            return g_ColorSpaceBaseInfoMap[i].fourcc;
        }
    }

    return 0;
}

/** @brief Call this function to get type of color space (RGB, YUV, XYZ) by fourcc.
	 *
	 * @param[in] fourcc format
     * @return color space type\n
     *         0 (CS_FORMAT_UNKNOWN) if FourCC format is unsupported
	 */
static inline int32_t get_cs_type(uint32_t fourcc)
{
    int32_t i;
    for(i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if(g_ColorSpaceBaseInfoMap[i].fourcc == fourcc)
            return g_ColorSpaceBaseInfoMap[i].cs_type;

    return CS_FORMAT_UNKNOWN;
}

/** @brief Call this function to get bit depth by fourcc.
	 *
	 * @param[in] fourcc format
     * @return bit depth\n
     *         0 if FourCC format is unsupported
	 */
static inline int32_t get_bit_depth(uint32_t fourcc)
{
    int32_t i;
    for(i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if(g_ColorSpaceBaseInfoMap[i].fourcc == fourcc)
            return g_ColorSpaceBaseInfoMap[i].bit_depth;

    return 0;
}

/** @brief Call this function to get chroma format by fourcc.
	 *
	 * @param[in] fourcc format
     * @return chroma format\n
     *         CHROMA_UNKNOWN if FourCC format is unsupported
	 */
static inline int32_t get_chroma_format(uint32_t fourcc)
{
    int32_t i;
    for(i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if(g_ColorSpaceBaseInfoMap[i].fourcc == fourcc)
            return g_ColorSpaceBaseInfoMap[i].chroma_format;

    return CHROMA_UNKNOWN;
}

/** @brief Call this function to count of bits per pixel by fourcc.
	 *
	 * @param[in] fourcc format
     * @return count of bits per pixel\n
     *         0 if FourCC format is unsupported
	 */
static inline uint32_t get_bits_per_pixel(int32_t fourcc)
{
    int32_t i;
    for(i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if(g_ColorSpaceBaseInfoMap[i].fourcc == (uint32_t) fourcc)
            return g_ColorSpaceBaseInfoMap[i].bits_per_pixel;

    return 0;
}

/** @brief Call this function to get number of pixels per macropixel.
	 *
	 * @param[in] fourcc FourCC format
	 * @return number of pixels per macropixel\n
     *         0 if FourCC format is unsupported
	 */
static inline uint32_t get_pixels_per_macropixel(int32_t fourcc)
{
    int32_t i;
    for(i = 0; i < g_ColorSpaceBaseInfoMapSize; i++)
        if(g_ColorSpaceBaseInfoMap[i].fourcc == (uint32_t) fourcc)
            return g_ColorSpaceBaseInfoMap[i].pixels_per_macropixel;

    return 0;
}

/** @brief Call this function to check color space frame parameters.
	 *
     * @param[in] width frame width
     * @param[in] height frame height
	 * @param[in] fourcc FourCC format
	 * @return 0 if the parameters are correct\n
     *         1 if not
	 */
static inline int32_t check_frame_colorspace_param(uint32_t width, uint32_t height, uint32_t fourcc)
{
    uint32_t pixels;
    int32_t chroma_format;

    if (width == 0 || height == 0)
        return 1;

    chroma_format = get_chroma_format(fourcc);
    if(((chroma_format == CHROMA420 || chroma_format == CHROMA410) && (height % 2)) ||
       (chroma_format == CHROMA810 && (height % 4)))
    {
        return 1;
    }

    // According to the specification: "As a special case that applies to the 'v210' compression type only, 
    // width may be a multiple of 2 that is not a multiple of horiz_align_pixels (48)..."
    if(FOURCC_V210 == fourcc)
    {
        // FOURCC_V210 has 4:2:2 chroma format therefore width should be multiplied 2
        if(width % 2)
            return 1;

        return 0;
    }
    pixels = get_pixels_per_macropixel(fourcc);

    if (pixels == 0 || width % pixels)
        return 1;

    return 0;
}

#define V210_LINE_ALIGN     (128 - 1)

/** @brief Call this function to get color space frame information.
	 *
     * @param[in] width frame width
     * @param[in] height frame height
	 * @param[in] fourcc FourCC format
     * @param[in] stride buffer line size in bytes, it should be 0 if stride is undefined
     * @param[out] cs_info pointer to @ref frame_colorspace_info_tt structure
	 * @return 0 if the parameters are correct\n
     *         1 if not
	 */
static inline int32_t get_frame_colorspace_info(frame_colorspace_info_tt *cs_info, uint32_t width, uint32_t height, uint32_t fourcc, int32_t stride)
{
    int32_t line_offset;
    if(!cs_info)
        return 1;

    memset(cs_info, 0, sizeof(frame_colorspace_info_tt));

    if (check_frame_colorspace_param(width, height, fourcc))
        return 1;

    cs_info->width = width;
    cs_info->height = height;
    cs_info->plane_height[0] = height;
    cs_info->fourcc = fourcc;    
    cs_info->planes = 1;

    switch (fourcc)
    {
    case FOURCC_YV12:
    case FOURCC_I420:
    case FOURCC_IYUV:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0]/2;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * (height/2);
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 3 / 2;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_I422:
    case FOURCC_YV16:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0]/2;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * height;
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 2;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_I444:
    case FOURCC_R24P:
    case FOURCC_PLXYZ8:
    case FOURCC_YV24:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->stride[2] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->stride[0] * height * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 3;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_YUYV:
    case FOURCC_YuYv:
    case FOURCC_YUY2:
    case FOURCC_UYVY:
    case FOURCC_UyVy:
    case FOURCC_VYUY:
    case FOURCC_YVYU:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;    

    case FOURCC_W009:
    case FOURCC_W010:
    case FOURCC_W011:
    case FOURCC_W012:
	case FOURCC_W013:
    case FOURCC_W014:
	case FOURCC_W015:
    case FOURCC_W016:
    case FOURCC_X009:
    case FOURCC_X010:
    case FOURCC_X011:
    case FOURCC_X012:
	case FOURCC_X013:
    case FOURCC_X014:
	case FOURCC_X015:
    case FOURCC_X016:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->stride[1] = cs_info->stride[0] / 2;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * (height/2);
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 3 / 2;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_W209:
    case FOURCC_W210:
    case FOURCC_W211:
    case FOURCC_W212:
    case FOURCC_W213:
    case FOURCC_W214:
    case FOURCC_W215:
    case FOURCC_W216:
    case FOURCC_X209:
    case FOURCC_X210:
    case FOURCC_X211:
    case FOURCC_X212:
    case FOURCC_X213:
    case FOURCC_X214:
    case FOURCC_X215:
    case FOURCC_X216:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->stride[1] = cs_info->stride[0] / 2;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * height;
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 2;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_W409:
    case FOURCC_W410:
    case FOURCC_W411:
    case FOURCC_W412:
    case FOURCC_W413:
    case FOURCC_W414:
    case FOURCC_W415:
    case FOURCC_W416:
    case FOURCC_X409:
    case FOURCC_X410:
    case FOURCC_X411:
    case FOURCC_X412:
    case FOURCC_X413:
    case FOURCC_X414:
    case FOURCC_X415:
    case FOURCC_X416:
    case FOURCC_R27P:
    case FOURCC_R30P:
    case FOURCC_R33P:
    case FOURCC_R36P:
    case FOURCC_R39P:
    case FOURCC_R42P:
    case FOURCC_R45P:
    case FOURCC_R48P:
    case FOURCC_PLXYZ9:
    case FOURCC_PLXYZ10:
    case FOURCC_PLXYZ11:
    case FOURCC_PLXYZ12:
    case FOURCC_PLXYZ13:
    case FOURCC_PLXYZ14:
    case FOURCC_PLXYZ15:
    case FOURCC_PLXYZ16:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->stride[2] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * height;
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 3;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_V210:
        cs_info->stride[0] = stride ? stride : (((width * 128 / 6) / 8 + V210_LINE_ALIGN) & (~V210_LINE_ALIGN));
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;   

        // RGB data is stored upside down
    case FOURCC_BGR3:
    case FOURCC_RGB3:
        cs_info->stride[0] = stride ? stride : width * 3;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_BGR4:
    case FOURCC_BGRA:
    case FOURCC_RGBA:
    case FOURCC_ARGB:
    case FOURCC_argb:
    case FOURCC_AR10:
    case FOURCC_AB10:
        cs_info->stride[0] = stride ? stride : width * 4;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_VUYA:
    case FOURCC_AYUV:
        cs_info->stride[0] = stride ? stride : width * 4;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_VUYA32F:
    case FOURCC_BGRA32F:
        cs_info->stride[0] = stride ? stride : width * 16;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_R32C:
        cs_info->stride[0] = stride ? stride : width * 4;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_R24C:
        cs_info->stride[0] = stride ? stride : width * 3;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_H264:
        cs_info->frame_size = 32 * 1024;
        cs_info->stride[0] = cs_info->frame_size;
        break;

    case FOURCC_XYZ8:
        cs_info->stride[0] = stride ? stride : width * 3;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_XYZ12:
        cs_info->stride[0] = stride ? stride : width * 3 * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;    

    case FOURCC_Y09:
    case FOURCC_Y10:
    case FOURCC_Y11:
    case FOURCC_Y12:
    case FOURCC_Y13:
    case FOURCC_Y14:
    case FOURCC_Y15:
    case FOURCC_Y16:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_V216:
    case FOURCC_Y216:
        cs_info->stride[0] = stride ? stride : width * 2 * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_Y416:
    case FOURCC_b64a:
        cs_info->stride[0] = stride ? stride : width * 4 * 2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_YVU9:
    case FOURCC_YUV9:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0] / 4;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * (height / 4);
        cs_info->frame_size = (9 * abs(cs_info->stride[0]) * height) / 8;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 4;
        break;

    case FOURCC_IMC1:
    case FOURCC_IMC3:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->stride[2] = cs_info->stride[0];
        line_offset = ((height + 15) & ~15);
        cs_info->plane_offset[1] = cs_info->stride[0] * line_offset;
        line_offset = (line_offset + height/2 + 15) & ~15;
        cs_info->plane_offset[2] = cs_info->stride[0] * line_offset;
        cs_info->frame_size = (line_offset + (height / 2)) * abs(cs_info->stride[0]);
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_IMC2:
    case FOURCC_IMC4:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->stride[2] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] / 2;
        cs_info->frame_size = (3 * abs(cs_info->stride[0]) * height) / 2;
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_NV12:
    case FOURCC_NV21:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->frame_size = (3 * abs(cs_info->stride[0]) * height) / 2;
        cs_info->planes = 2;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_NV24:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0]*2;
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->frame_size = 3 * abs(cs_info->stride[0]) * height;
        cs_info->planes = 2;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_R565:
    case FOURCC_R555:
        cs_info->stride[0] = stride ? stride : 2 * width;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;
    
    case FOURCC_Y210:
    case FOURCC_DPX10:
    case FOURCC_Y410:    
        cs_info->stride[0] = stride ? stride : 4 * width;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_P210:
    case FOURCC_P216:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->frame_size = abs(cs_info->stride[0]) * height * 2;
        cs_info->planes = 2;
        cs_info->plane_height[1] = height;
        break;

    case FOURCC_Y41P:
    case FOURCC_Y411:
        cs_info->stride[0] = stride ? stride : ((width+7)&~7)*3/2;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;

    case FOURCC_CLJR:
    case FOURCC_Y211:
    case FOURCC_GRAY:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->frame_size = abs(cs_info->stride[0]) * height;
        break;
    
    case FOURCC_P010:
    case FOURCC_P016:
        cs_info->stride[0] = stride ? stride : width * 2;
        cs_info->stride[1] = cs_info->stride[0];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->frame_size = 3 * (height * abs(cs_info->stride[0])) / 2;
        cs_info->planes = 2;
        cs_info->plane_height[1] = height / 2;
        break;

    case FOURCC_410P:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0] / 4;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * (height/2);
        cs_info->frame_size = abs(cs_info->stride[0] * (int32_t)height + cs_info->stride[1] * (int32_t)height);
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height / 2;
        break;

    case FOURCC_411P:
        cs_info->stride[0] = stride ? stride : width;
        cs_info->stride[1] = cs_info->stride[0] / 4;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * height;
        cs_info->frame_size = abs(cs_info->stride[0] * (int32_t)height + 2 * cs_info->stride[1] * (int32_t)height);
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    case FOURCC_211P:
        cs_info->stride[0] = stride ? stride : width / 2;
        cs_info->stride[1] = cs_info->stride[0] / 2;
        cs_info->stride[2] = cs_info->stride[1];
        cs_info->plane_offset[1] = cs_info->stride[0] * height;
        cs_info->plane_offset[2] = cs_info->plane_offset[1] + cs_info->stride[1] * height;
        cs_info->frame_size = abs(cs_info->stride[0] * (int32_t)height + 2 * cs_info->stride[1] * (int32_t)height);
        cs_info->planes = 3;
        cs_info->plane_height[1] = cs_info->plane_height[2] = height;
        break;

    default:
        return 1;
    }
    return 0;
}

/** @brief Call this function to fill @ref frame_tt structure from @ref frame_colorspace_info_tt.
	 *
     * @param[in] cs_info pointer to @ref frame_colorspace_info_tt structure
     * @param[in] buffer pointer to @ref uint8_t buffer
     * @param[out] frame_tt_out pointer to @ref frame_tt structure
	 * @return 0 if the parameters are correct\n
     *         1 if not
	 */
static inline int32_t fill_frame_from_colorspace_info(const frame_colorspace_info_tt *cs_info, uint8_t *buffer, frame_tt *frame_tt_out)
{
    uint32_t i;
    if (!cs_info || !frame_tt_out)
        return 1;

    frame_tt_out->four_cc   = cs_info->fourcc;
    frame_tt_out->width     = cs_info->width;
    frame_tt_out->height    = cs_info->height;
    for(i = 0; i < cs_info->planes; i++)
    {
        frame_tt_out->stride[i] = cs_info->stride[i];
        frame_tt_out->plane[i]  = buffer + cs_info->plane_offset[i];
    }

    return 0;
}

/** @brief Call this function to get offsets to the position for each plane in bytes.
	 *
     * @param[in] x horizontal position in pixels
     * @param[in] y vertical position in lines
	 * @param[in] fourcc FourCC format
     * @param[in] stride buffer line size in bytes
     * @param[out] offset pointer to the offset's array, minimal size of the array should be 3
	 * @return 0 if fourcc if correct\n
     *         1 if not
	 */
static inline int32_t get_plane_offsets_in_bytes(int32_t *offset, uint32_t x, uint32_t y, uint32_t fourcc, int32_t stride)
{
    int32_t line_offset;
    if(!offset)
        return 1;

    offset[0] = 0;
    offset[1] = 0;
    offset[2] = 0;

    switch (fourcc)
    {
    case FOURCC_YV12:
    case FOURCC_I420:
    case FOURCC_IYUV:
        offset[0] = x + stride*y;
        offset[1] = x/2 + (stride/2) * (y/2);
        offset[2] = offset[1];
        break;

    case FOURCC_I422:
    case FOURCC_YV16:
        offset[0] = x + stride*y;
        offset[1] = x/2 + (stride/2) * y;
        offset[2] = offset[1];
        break;

    case FOURCC_I444:
    case FOURCC_PLXYZ8:
    case FOURCC_YV24:
    case FOURCC_R24P:
        offset[0] = x + stride*y;
        offset[1] = offset[0];
        offset[2] = offset[0];
        break;

    case FOURCC_YUYV:
    case FOURCC_YuYv:
    case FOURCC_YUY2:
    case FOURCC_UYVY:
    case FOURCC_UyVy:
    case FOURCC_VYUY:
    case FOURCC_YVYU:
    case FOURCC_Y09:
    case FOURCC_Y10:
    case FOURCC_Y11:
    case FOURCC_Y12:
    case FOURCC_Y13:
    case FOURCC_Y14:
    case FOURCC_Y15:
    case FOURCC_Y16:
    case FOURCC_R565:
    case FOURCC_R555:
        offset[0] = x*2 + stride*y;
        break;

    case FOURCC_W009:
    case FOURCC_W010:
    case FOURCC_W011:
    case FOURCC_W012:
	case FOURCC_W013:
    case FOURCC_W014:
	case FOURCC_W015:
    case FOURCC_W016:
    case FOURCC_X009:
    case FOURCC_X010:
    case FOURCC_X011:
    case FOURCC_X012:
	case FOURCC_X013:
    case FOURCC_X014:
	case FOURCC_X015:
    case FOURCC_X016:
        offset[0] = x*2 + stride*y;
        offset[1] = x + (stride/2) * (y/2);
        offset[2] = offset[1];
        break;

    case FOURCC_W209:
    case FOURCC_W210:
    case FOURCC_W211:
    case FOURCC_W212:
    case FOURCC_W213:
    case FOURCC_W214:
    case FOURCC_W215:
    case FOURCC_W216:
    case FOURCC_X209:
    case FOURCC_X210:
    case FOURCC_X211:
    case FOURCC_X212:
    case FOURCC_X213:
    case FOURCC_X214:
    case FOURCC_X215:
    case FOURCC_X216:
        offset[0] = x*2 + stride*y;
        offset[1] = x + (stride/2) * y;
        offset[2] = offset[1];
        break;

    case FOURCC_W409:
    case FOURCC_W410:
    case FOURCC_W411:
    case FOURCC_W412:
    case FOURCC_W413:
    case FOURCC_W414:
    case FOURCC_W415:
    case FOURCC_W416:
    case FOURCC_X409:
    case FOURCC_X410:
    case FOURCC_X411:
    case FOURCC_X412:
    case FOURCC_X413:
    case FOURCC_X414:
    case FOURCC_X415:
    case FOURCC_X416:
    case FOURCC_PLXYZ9:
    case FOURCC_PLXYZ10:
    case FOURCC_PLXYZ11:
    case FOURCC_PLXYZ12:
    case FOURCC_PLXYZ13:
    case FOURCC_PLXYZ14:
    case FOURCC_PLXYZ15:
    case FOURCC_PLXYZ16:
    case FOURCC_R27P:
    case FOURCC_R30P:
    case FOURCC_R33P:
    case FOURCC_R36P:
    case FOURCC_R39P:
    case FOURCC_R42P:
    case FOURCC_R45P:
    case FOURCC_R48P:
        offset[0] = x*2 + stride*y;
        offset[1] = offset[0];
        offset[2] = offset[0];
        break;

    case FOURCC_V210:
        offset[0] = (((x * 128 / 6) / 8 + V210_LINE_ALIGN) & (~V210_LINE_ALIGN)) + stride*y;
        break;

        // RGB data is stored upside down
    case FOURCC_BGR3:
    case FOURCC_RGB3:
    case FOURCC_R24C:
    case FOURCC_XYZ8:
        offset[0] = x*3 + stride*y;
        break;

    case FOURCC_BGR4:
    case FOURCC_BGRA:
    case FOURCC_RGBA:
    case FOURCC_ARGB:
    case FOURCC_argb:
    case FOURCC_AR10:
    case FOURCC_AB10:
    case FOURCC_VUYA:
    case FOURCC_AYUV:
    case FOURCC_R32C:
    case FOURCC_V216:
    case FOURCC_Y216:
    case FOURCC_Y210:
    case FOURCC_DPX10:
    case FOURCC_Y410:
        offset[0] = x*4 + stride*y;
        break;

    case FOURCC_VUYA32F:
    case FOURCC_BGRA32F:
        offset[0] = x*16 + stride*y;
        break;

    case FOURCC_XYZ12:
        offset[0] = x*6 + stride*y;
        break;
        
    case FOURCC_Y416:
    case FOURCC_b64a:
        offset[0] = x*8 + stride*y;
        break;

    case FOURCC_YVU9:
    case FOURCC_YUV9:
        offset[0] = x + stride*y;
        offset[1] = x/4 + (stride/4)*(y/4);
        offset[2] = offset[1];
        break;

    case FOURCC_IMC1:
    case FOURCC_IMC3:
        line_offset = ((y + 15) & ~15);
        offset[0] = x + stride*line_offset;
        line_offset = (y/2 + 15) & ~15;
        offset[1] = x + stride*line_offset;
        offset[2] = offset[1];
        break;

    case FOURCC_IMC2:
    case FOURCC_IMC4:
        offset[0] = x + stride*y;
        offset[1] = x/2 + (stride/2)*(y/2);
        offset[2] = offset[1];
        break;

    case FOURCC_NV12:
    case FOURCC_NV21:
        offset[0] = x + stride*y;
        offset[1] = offset[0];
        break;

    case FOURCC_NV24:
        offset[0] = x + stride*y;
        offset[1] = x*2 + 2*stride*y;
        break;

    case FOURCC_P210:
    case FOURCC_P216:
        offset[0] = x*2 + stride*y;
        offset[1] = offset[0];
        break;

    case FOURCC_Y41P:
    case FOURCC_Y411:
        offset[0] = ((x+7)&~7)*3/2 + stride*y;
        break;

    case FOURCC_CLJR:
    case FOURCC_Y211:
    case FOURCC_GRAY:
        offset[0] = x + stride*y;
        break;

    case FOURCC_P010:
    case FOURCC_P016:
        offset[0] = x*2 + stride*y;
        offset[1] = x*2 + stride*(y/2);
        break;

    case FOURCC_410P:
        offset[0] = x + stride*y;
        offset[1] = x/4 + (stride/4)*(y/2);
        offset[2] = offset[1];
        break;

    case FOURCC_411P:
        offset[0] = x + stride*y;
        offset[1] = x/4 + (stride/4)*y;
        offset[2] = offset[1];
        break;

    case FOURCC_211P:
        offset[0] = x/2 + stride*y;
        offset[1] = x/4 + (stride/2)*y;
        offset[2] = offset[1];
        break;

    default:
        return 1;
    }
    return 0;
}

/** @brief Call this function to flip color space frame.
	 *
     * @param[in] cs_info pointer to @ref frame_colorspace_info_tt structure
     * @param[out] cs_info pointer to @ref frame_colorspace_info_tt structure
	 * @return 0 if the pointer of frame_colorspace_info_tt are correct\n
     *         1 if not
	 */
static inline int32_t flip_colorspace(frame_colorspace_info_tt *cs_info)
{
    int8_t i;
    if(!cs_info)
        return 1;

    for(i = 0; i < 4 && (cs_info->stride[i] != 0); i++)
    {
        cs_info->plane_offset[i] += cs_info->stride[i] * (cs_info->plane_height[i] - 1);
        cs_info->stride[i] = -cs_info->stride[i];
    }
    return 0;
}

/** @brief Call this function to crop frame.
*
* @param[in] crop_cs_info pointer to @ref frame_colorspace_info_tt structure
* @param[in] pixels_number_left the pixels number for left offset
* @param[in] pixels_number_top the pixels number for top offset
* @param[in] pixels_number_right the pixels number for right offset
* @param[in] pixels_number_bottom the pixels number for bottom offset
* @param[out] crop_cs_info pointer to @ref frame_colorspace_info_tt structure
* @return 1 if the cropping is unacceptable for frame settings, described in @ref frame_colorspace_info_tt structure, with window for cropping\n
*         0 if the cropping is successful
*/
static inline int32_t crop_frame_colorspace_info(frame_colorspace_info_tt *crop_cs_info, uint32_t pixels_number_left, uint32_t pixels_number_top, uint32_t pixels_number_right, uint32_t pixels_number_bottom)
{
    int32_t offset[4];
    int32_t error;
    frame_colorspace_info_tt cs_info_crop;
    uint32_t crop_width;
    uint32_t crop_height;
    uint32_t i;

    if (!crop_cs_info ||
        pixels_number_left + pixels_number_right >= crop_cs_info->width ||
        pixels_number_top + pixels_number_bottom >= crop_cs_info->height)
    {
        return 1;
    }

    error = get_plane_offsets_in_bytes(&offset[0], pixels_number_left, pixels_number_top, crop_cs_info->fourcc, crop_cs_info->stride[0]);
    if(error)
        return error;

    crop_width = crop_cs_info->width - pixels_number_left - pixels_number_right;
    crop_height = crop_cs_info->height - pixels_number_top - pixels_number_bottom;
    error = get_frame_colorspace_info(&cs_info_crop, crop_width, crop_height, crop_cs_info->fourcc, crop_cs_info->stride[0]);
    if(error)
        return error;

    for(i = 0; i < crop_cs_info->planes; i++)
    {
        crop_cs_info->plane_offset[i] += offset[i];
        crop_cs_info->plane_height[i] = cs_info_crop.plane_height[i];
    }

    crop_cs_info->width = cs_info_crop.width;
    crop_cs_info->height = cs_info_crop.height;

    return 0;
}

#endif // __MC_COLORSPACE_INCLUDED__
