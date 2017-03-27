/** 
\file   mcfourcc.h
\brief  fourcc defines

\verbatim
File: mcfourcc.h
Desc: fourcc defines

 Copyright (c) 2016 MainConcept GmbH or its affiliates.  All rights reserved.
 
 MainConcept and its logos are registered trademarks of MainConcept GmbH or its affiliates.  
 This software is protected by copyright law and international treaties.  Unauthorized 
 reproduction or distribution of any portion is prohibited by law.
\endverbatim
**/

#if !defined (__MC_FOURCC_INCLUDED__)
#define __MC_FOURCC_INCLUDED__

#include "mctypes.h"

#ifndef MAKEFOURCC
  #define MAKEFOURCC(ch0, ch1, ch2, ch3)  \
    ((uint32_t)(int8_t)(ch0) | ((uint32_t)(int8_t)(ch1) << 8) | \
    ((uint32_t)(int8_t)(ch2) << 16) | ((uint32_t)(int8_t)(ch3) << 24 ))
#endif // MAKEFOURCC

/**
  * @addtogroup FourCC
  
 \section ColorSpaceBaseInfo_t Characteristics of the FourCC formats
<table>
<tr><th>FourCC</th>             <th>bit_depth</th>      <th>chroma_format</th>      <th>bits_per_pixel</th>     <th>pixels_per_macropixel</th>  </tr>
<tr><td>@ref FOURCC_AYUV</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_VUYA</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_YUY2</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_YUYV</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_YuYv</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_UYVY</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_UyVy</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_YVYU</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_VYUY</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y41P</td>   <td>8</td>              <td>CHROMA411</td>          <td>12</td>                 <td>8</td>                      </tr>
<tr><td>@ref FOURCC_Y211</td>   <td>8</td>              <td>CHROMA211</td>          <td>8</td>                  <td>4</td>                      </tr>
<tr><td>@ref FOURCC_CLJR</td>   <td>6</td>              <td>CHROMA411</td>          <td>8</td>                  <td>4</td>                      </tr>
<tr><td>@ref FOURCC_YVU9</td>   <td>8</td>              <td>CHROMA810</td>          <td>9</td>                  <td>4</td>                      </tr>
<tr><td>@ref FOURCC_YUV9</td>   <td>8</td>              <td>CHROMA810</td>          <td>9</td>                  <td>4</td>                      </tr>
<tr><td>@ref FOURCC_YV12</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_IYUV</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_I420</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_YV16</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_I422</td>   <td>8</td>              <td>CHROMA422</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_YV24</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_NV24</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_I444</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_BGRA32F</td><td>32</td>             <td>CHROMA444</td>          <td>128</td>                <td>1</td>                      </tr>
<tr><td>@ref FOURCC_VUYA32F</td><td>32</td>             <td>CHROMA444</td>          <td>128</td>                <td>1</td>                      </tr>
<tr><td>@ref FOURCC_NV12</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_NV21</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_IMC1</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_IMC2</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_IMC3</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_IMC4</td>   <td>8</td>              <td>CHROMA420</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_V210</td>   <td>10</td>             <td>CHROMA422</td>          <td>20</td>                 <td>6</td>                      </tr>
<tr><td>@ref FOURCC_V216</td>   <td>16</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y210</td>   <td>10</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y216</td>   <td>16</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y410</td>   <td>10</td>             <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_Y416</td>   <td>16</td>             <td>CHROMA444</td>          <td>64</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_P010</td>   <td>10</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_P016</td>   <td>16</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_P210</td>   <td>10</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_P216</td>   <td>16</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W009</td>   <td>9</td>              <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W010</td>   <td>10</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W011</td>   <td>11</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W012</td>   <td>12</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W013</td>   <td>13</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W014</td>   <td>14</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W015</td>   <td>15</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W016</td>   <td>16</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W209</td>   <td>9</td>              <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W210</td>   <td>10</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W211</td>   <td>11</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W212</td>   <td>12</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W213</td>   <td>13</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W214</td>   <td>14</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W215</td>   <td>15</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W216</td>   <td>16</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_W409</td>   <td>9</td>              <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W410</td>   <td>10</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W411</td>   <td>11</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W412</td>   <td>12</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W413</td>   <td>13</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W414</td>   <td>14</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W415</td>   <td>15</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_W416</td>   <td>16</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X009</td>   <td>9</td>              <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X010</td>   <td>10</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X011</td>   <td>11</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X012</td>   <td>12</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X013</td>   <td>13</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X014</td>   <td>14</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X015</td>   <td>15</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X016</td>   <td>16</td>             <td>CHROMA420</td>          <td>24</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X209</td>   <td>9</td>              <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X210</td>   <td>10</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X211</td>   <td>11</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X212</td>   <td>12</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X213</td>   <td>13</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X214</td>   <td>14</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X215</td>   <td>15</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X216</td>   <td>16</td>             <td>CHROMA422</td>          <td>32</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_X409</td>   <td>9</td>              <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X410</td>   <td>10</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X411</td>   <td>11</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X412</td>   <td>12</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X413</td>   <td>13</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X414</td>   <td>14</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X415</td>   <td>15</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_X416</td>   <td>16</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_GRAY</td>   <td>8</td>              <td>CHROMA400</td>          <td>8</td>                  <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y09</td>    <td>9</td>              <td>CHROMA400</td>          <td>9</td>                  <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y10</td>    <td>10</td>             <td>CHROMA400</td>          <td>10</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y11</td>    <td>11</td>             <td>CHROMA400</td>          <td>11</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y12</td>    <td>12</td>             <td>CHROMA400</td>          <td>12</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y13</td>    <td>13</td>             <td>CHROMA400</td>          <td>13</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y14</td>    <td>14</td>             <td>CHROMA400</td>          <td>14</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y15</td>    <td>15</td>             <td>CHROMA400</td>          <td>15</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_Y16</td>    <td>16</td>             <td>CHROMA400</td>          <td>16</td>                 <td>2</td>                      </tr>
<tr><td>@ref FOURCC_410P</td>   <td>8</td>              <td>CHROMA410</td>          <td>10</td>                 <td>4</td>                      </tr>
<tr><td>@ref FOURCC_411P</td>   <td>8</td>              <td>CHROMA411</td>          <td>12</td>                 <td>4</td>                      </tr>
<tr><td>@ref FOURCC_211P</td>   <td>8</td>              <td>CHROMA211</td>          <td>8</td>                  <td>4</td>                      </tr>
<tr><td>@ref FOURCC_ARGB</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_argb</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_BGRA</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_RGBA</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_BGR4</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_BGR3</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R565</td>   <td>6</td>              <td>CHROMA444</td>          <td>16</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R555</td>   <td>5</td>              <td>CHROMA444</td>          <td>16</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_RGB3</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R24C</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R32C</td>   <td>8</td>              <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_b64a</td>   <td>16</td>             <td>CHROMA444</td>          <td>64</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R24P</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R27P</td>   <td>9</td>              <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R30P</td>   <td>10</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R33P</td>   <td>11</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R36P</td>   <td>12</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R39P</td>   <td>13</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R42P</td>   <td>14</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R45P</td>   <td>15</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_R48P</td>   <td>16</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_AR10</td>   <td>10</td>             <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_AB10</td>   <td>10</td>             <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_DPX10</td>  <td>10</td>             <td>CHROMA444</td>          <td>32</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_XYZ8</td>   <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_XYZ12</td>  <td>12</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ8</td> <td>8</td>              <td>CHROMA444</td>          <td>24</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ9</td> <td>9</td>              <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ10</td><td>10</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ11</td><td>11</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ12</td><td>12</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ13</td><td>13</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ14</td><td>14</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ15</td><td>15</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
<tr><td>@ref FOURCC_PLXYZ16</td><td>16</td>             <td>CHROMA444</td>          <td>48</td>                 <td>1</td>                      </tr>
</table>
  * @{
**/

#ifndef FOURCC_RGB3
/**@brief Packed RGB, 8 bits per component, components order: R->G->B, 24 bpp
* @hideinitializer */
#define FOURCC_RGB3 MAKEFOURCC('R', 'G', 'B', '3')
#endif

#ifndef FOURCC_BGR3
/**@brief RGB24, packed RGB, 24 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd407253(VS.85).aspx
* @hideinitializer */
#define FOURCC_BGR3 MAKEFOURCC('B', 'G', 'R', '3')
#endif

#ifndef FOURCC_BGRA
/**@brief BGRA32, packed RGB with alpha channel, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd407253(VS.85).aspx
* @hideinitializer */
#define FOURCC_BGRA MAKEFOURCC('B', 'G', 'R', 'A')
#endif

#ifndef FOURCC_RGBA
/**@brief RGBA32, packed RGB with alpha channel, components order: R->G->B->A, 32 bpp
* @hideinitializer */
#define FOURCC_RGBA MAKEFOURCC('R', 'G', 'B', 'A')
#endif

#ifndef FOURCC_BGRA32F
/**@brief BGRA, packed RGB, 32 bits per component (floating point), components order: B->G->R->A, 128 bpp
* @hideinitializer */
#define FOURCC_BGRA32F MAKEFOURCC('B', '3', '2', 'F')
#endif

#ifndef FOURCC_B32F
/**@brief BGRA, packed RGB, 32 bits per component (floating point), components order: B->G->R->A, 128 bpp
* @hideinitializer */
#define FOURCC_B32F MAKEFOURCC('B', '3', '2', 'F')
#endif

#ifndef FOURCC_ARGB
/**@brief ARGB32, packed RGB with alpha channel, components order: A->R->G->B, 32 bpp
* @n ARGB Colorspace as common used on Macintosh. May not be available on other platforms.
* @hideinitializer */
#define FOURCC_ARGB MAKEFOURCC('A', 'R', 'G', 'B')
#endif

#ifndef FOURCC_BGR4
/**@brief RGB32, packed RGB, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd407253(VS.85).aspx
* @hideinitializer */
#define FOURCC_BGR4 MAKEFOURCC('B', 'G', 'R', '4')
#endif

#ifndef FOURCC_R555
/**@brief RGB555, packed RGB, 16 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd407253(VS.85).aspx
* @hideinitializer */
#define FOURCC_R555 MAKEFOURCC('R', '5', '5', '5')
#endif

#ifndef FOURCC_R565
/**@brief RGB565, packed RGB, 16 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd407253(VS.85).aspx
* @hideinitializer */
#define FOURCC_R565 MAKEFOURCC('R', '5', '6', '5')
#endif

#ifndef FOURCC_AYUV
/**@brief AYUV, packed YUV, 4:4:4, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd206750(VS.85).aspx#ayuv
* @hideinitializer */
#define FOURCC_AYUV MAKEFOURCC('A', 'Y', 'U', 'V')
#endif

#ifndef FOURCC_VUYA
/**@brief VUYA, packed YUV, 4:4:4, 8 bits per component, components order: V->U->Y->A, 32 bpp
* @hideinitializer */
#define FOURCC_VUYA MAKEFOURCC('V', 'U', 'Y', 'A')
#endif

#ifndef FOURCC_VUYA32F
/**@brief VUYA, packed YUV, 4:4:4, 32 bits per component (floating point), components order: V->U->Y->A, 128 bpp
* @hideinitializer */
#define FOURCC_VUYA32F MAKEFOURCC('Y', '3', '2', 'F')
#endif

#ifndef FOURCC_Y32F
/**@brief VUYA, packed YUV, 4:4:4, 32 bits per component (floating point), components order: V->U->Y->A, 128 bpp
* @hideinitializer */
#define FOURCC_Y32F MAKEFOURCC('Y', '3', '2', 'F')
#endif

#ifndef FOURCC_UYVY
/**@brief UYVY, packed YUV, 4:2:2, 16 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd206750(VS.85).aspx#uyvy
* @hideinitializer */
#define FOURCC_UYVY MAKEFOURCC('U', 'Y', 'V', 'Y')
#endif

#ifndef FOURCC_YUY2
/**@brief YUYV, packed YUV, 4:2:2, 16 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd206750(VS.85).aspx#yuy2
* @hideinitializer */
#define FOURCC_YUY2 MAKEFOURCC('Y', 'U', 'Y', '2')
#endif

#ifndef FOURCC_YUYV
/**@brief YUYV, packed YUV, 4:2:2, 16 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd206750(VS.85).aspx#yuy2
* @hideinitializer */
#define FOURCC_YUYV MAKEFOURCC('Y', 'U', 'Y', 'V')
#endif

#ifndef FOURCC_YVYU
/**@brief YVYU, packed YUV, 4:2:2, 16 bpp
* @n Reference to the description is the same as @ref FOURCC_YUYV, but the U and V samples are swapped.
* @hideinitializer */
#define FOURCC_YVYU MAKEFOURCC('Y', 'V', 'Y', 'U')
#endif

#ifndef FOURCC_VYUY
/**@brief VYUY, packed YUV, 4:2:2, 16 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php
* @hideinitializer */
#define FOURCC_VYUY MAKEFOURCC('V', 'Y', 'U', 'Y')
#endif

#ifndef FOURCC_EXTP
/**@brief External, 3-plane colorspace-converter (requires a valid ext_cc_struct)
* @hideinitializer */
#define FOURCC_EXTP MAKEFOURCC('E', 'X', 'T', 'P')
#endif

#ifndef FOURCC_I420
/**@brief YV12, planar YUV, 4:2:0, 8 bits per component, planes order: Y->U->V, 12 bpp
* @hideinitializer */
#define FOURCC_I420 MAKEFOURCC('I', '4', '2', '0')
#endif

#ifndef FOURCC_I422
/**@brief YV16, planar YUV, 4:2:2, 8 bits per component, planes order: Y->U->V, 16 bpp
* @hideinitializer */
#define FOURCC_I422 MAKEFOURCC('I', '4', '2', '2')
#endif

#ifndef FOURCC_I444
/**@brief YV24, planar YUV, 4:4:4, 8 bits per component, planes order: Y->U->V, 24 bpp
* @hideinitializer */
#define FOURCC_I444 MAKEFOURCC('I', '4', '4', '4')
#endif

#ifndef FOURCC_YV12
/**@brief YV12, planar YUV, 4:2:0, 8 bits per component, planes order: Y->V->U, 12 bpp
* @hideinitializer */
#define FOURCC_YV12 MAKEFOURCC('Y', 'V', '1', '2')
#endif

#ifndef FOURCC_IYUV
/**@brief YV12, planar YUV, 4:2:0, 8 bits per component, planes order: Y->U->V, 12 bpp
* @hideinitializer */
#define FOURCC_IYUV MAKEFOURCC('I', 'Y', 'U', 'V')
#endif

#ifndef FOURCC_YV16
/**@brief YV16, planar YUV, 4:2:2, 8 bits per component, planes order: Y->V->U, 16 bpp
* @hideinitializer */
#define FOURCC_YV16 MAKEFOURCC('Y', 'V', '1', '6')
#endif

#ifndef FOURCC_YV24
/**@brief YV24, planar YUV, 4:4:4, 8 bits per component, planes order: Y->V->U, 24 bpp
* @hideinitializer */
#define FOURCC_YV24 MAKEFOURCC('Y', 'V', '2', '4')
#endif

#ifndef FOURCC_Y41P
/**@brief Y41P, packed YUV, 4:1:1, 12 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#Y41P
* @hideinitializer */
#define FOURCC_Y41P MAKEFOURCC('Y', '4', '1', 'P')
#endif

#ifndef FOURCC_Y411
/**@brief Y411 (the same as Y41P), packed YUV, 4:1:1, 12 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#Y41P
* @hideinitializer */
#define FOURCC_Y411 MAKEFOURCC('Y', '4', '1', '1')
#endif

#ifndef FOURCC_NV12
/**@brief NV12, planar YUV, 4:2:0, planes order Y->UV, UV interleaved, 12 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/dd206750(VS.85).aspx#nv12
* @hideinitializer */
#define FOURCC_NV12 MAKEFOURCC('N', 'V', '1', '2')
#endif

#ifndef FOURCC_NV21
/**@brief NV21, planar YUV, 4:2:0, planes order Y->UV, UV interleaved, 12 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#NV21
* @hideinitializer */
#define FOURCC_NV21 MAKEFOURCC('N', 'V', '2', '1')
#endif

#ifndef FOURCC_NV24
/**@brief NV24, planar YUV, 4:4:4, 8 bits per component, planes order Y->UV, UV interleaved, 24 bpp
* @hideinitializer */
#define FOURCC_NV24 MAKEFOURCC('N', 'V', '2', '4')
#endif

#ifndef FOURCC_IMC1
/**@brief YV12, planar YUV, 4:2:0, planes order: Y->V->U, 12 bpp
* @n Reference to the description https://msdn.microsoft.com/en-us/library/ff538197%28VS.85%29.aspx
* @hideinitializer */
#define FOURCC_IMC1 MAKEFOURCC('I', 'M', 'C', '1')
#endif

#ifndef FOURCC_IMC2
/**@brief YV12, planar YUV, 4:2:0, planes order: Y->V->U, UV interleaved, 12 bpp
* @n Reference to the description https://msdn.microsoft.com/en-us/library/ff538197%28VS.85%29.aspx
* @hideinitializer */
#define FOURCC_IMC2 MAKEFOURCC('I', 'M', 'C', '2')
#endif

#ifndef FOURCC_IMC3
/**@brief YV12, planar YUV, 4:2:0, planes order: Y->U->V, 12 bpp
* @n Reference to the description https://msdn.microsoft.com/en-us/library/ff538197%28VS.85%29.aspx
* @hideinitializer */
#define FOURCC_IMC3 MAKEFOURCC('I', 'M', 'C', '3')
#endif

#ifndef FOURCC_IMC4
/**@brief YV12, planar YUV, 4:2:0, planes order: Y->U->V, UV interleaved, 12 bpp
* @n Reference to the description https://msdn.microsoft.com/en-us/library/ff538197%28VS.85%29.aspx
* @hideinitializer */
#define FOURCC_IMC4 MAKEFOURCC('I', 'M', 'C', '4')
#endif

#ifndef FOURCC_YVU9
/**@brief YVU9, planar YUV, planes order Y->V->U, 9 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#YVU9
* @hideinitializer */
#define FOURCC_YVU9 MAKEFOURCC('Y', 'V', 'U', '9')
#endif

#ifndef FOURCC_YUV9
/**@brief YUV9, planar YUV, planes order Y->U->V, 9 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#YUV9
* @hideinitializer */
#define FOURCC_YUV9 MAKEFOURCC('Y', 'U', 'V', '9')
#endif

#ifndef FOURCC_Y211
/**@brief Y211, packed YUV, 2:1:1, 8 bits per component, 8 bpp
* @n Reference to the description http://www.fourcc.org/yuv.php#Y211
* @hideinitializer */
#define FOURCC_Y211 MAKEFOURCC('Y', '2', '1', '1')
#endif

#ifndef FOURCC_CLJR
/**@brief CLJR, packed YUV, 4:1:1, 8 bpp
* @n Reference to the description http://fourcc.org/yuv.php#CLJR
* @hideinitializer */
#define FOURCC_CLJR MAKEFOURCC('C', 'L', 'J', 'R')
#endif

#ifndef FOURCC_RAW
/**@brief Uncompressed data
* @hideinitializer */
#define FOURCC_RAW  MAKEFOURCC('R', 'A', 'W', ' ')
#endif

#ifndef FOURCC_R32C
/**@brief RGB32, packed RGB, 8 bits per component, components order: B->G->R->X, 32 bpp (16:black, 235-white)
* @hideinitializer */
#define FOURCC_R32C MAKEFOURCC('R', '3', '2', 'C')
#endif

#ifndef FOURCC_argb
/**@brief ARGB32, packed RGB with alpha channel, 8 bits per component, components order: A->R->G->B, 32 bpp (16:black, 235-white)
* @hideinitializer */
#define FOURCC_argb MAKEFOURCC('a', 'r', 'g', 'b')
#endif

#ifndef FOURCC_R24C
/**@brief RGB24, packed RGB, 8 bits per component, components order: B->G->R, 24 bpp (16:black, 235-white)
* @hideinitializer */
#define FOURCC_R24C MAKEFOURCC('R', '2', '4', 'C')
#endif

#ifndef FOURCC_YuYv
/**@brief YUYV, packed YUV, 4:2:2, clamped chroma component, 16 bpp (No clamping to ITU601 range)
* @hideinitializer */
#define FOURCC_YuYv MAKEFOURCC('Y', 'u', 'Y', 'v')
#endif

#ifndef FOURCC_UyVy
/**@brief UYVY, packed YUV, 4:2:2, clamped luma component, 16 bpp (No clamping to ITU601 range)
* @hideinitializer */
#define FOURCC_UyVy MAKEFOURCC('U', 'y', 'V', 'y')
#endif

#ifndef FOURCC_XYZ8
/**@brief D-cinema xyz colorspace, packed XYZ, 8 bits per component, 24 bpp
* @hideinitializer */
#define FOURCC_XYZ8 MAKEFOURCC('X', 'Y', 'Z', 0x08)
#endif

#ifndef FOURCC_XYZ12
/**@brief D-cinema xyz colorspace, packed XYZ, 16 bits per component but only low 12 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_XYZ12 MAKEFOURCC('X', 'Y', 'Z', 0x0C)
#endif

#ifndef FOURCC_PLXYZ8
/**@brief D-cinema xyz colorspace, planar XYZ, 8 bits per component, 24 bpp
* @hideinitializer */
#define FOURCC_PLXYZ8 MAKEFOURCC('P', 'X', 'Y', 0x08)
#endif

#ifndef FOURCC_PLXYZ9
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 9 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ9 MAKEFOURCC('P', 'X', 'Y', 0x09)
#endif

#ifndef FOURCC_PLXYZ10
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 10 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ10 MAKEFOURCC('P', 'X', 'Y', 0x0A)
#endif

#ifndef FOURCC_PLXYZ11
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 11 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ11 MAKEFOURCC('P', 'X', 'Y', 0x0B)
#endif

#ifndef FOURCC_PLXYZ12
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 12 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ12 MAKEFOURCC('P', 'X', 'Y', 0x0C)
#endif

#ifndef FOURCC_PLXYZ13
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 13 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ13 MAKEFOURCC('P', 'X', 'Y', 0x0D)
#endif

#ifndef FOURCC_PLXYZ14
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 14 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ14 MAKEFOURCC('P', 'X', 'Y', 0x0E)
#endif

#ifndef FOURCC_PLXYZ15
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 15 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ15 MAKEFOURCC('P', 'X', 'Y', 0x0F)
#endif

#ifndef FOURCC_PLXYZ16
/**@brief D-cinema xyz colorspace, planar XYZ, 16 bits per component but only low 16 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_PLXYZ16 MAKEFOURCC('P', 'X', 'Y', 0x10)
#endif

#ifndef FOURCC_DPX10
/**@brief 10bit DPX format SMPTE 268M, packed RGB, 10 bits per component, components order: B->G->R->X, 32 bpp
* @hideinitializer */
#define FOURCC_DPX10 MAKEFOURCC('D', 'P', 'X', 0x0A)
#endif

#ifndef FOURCC_V210
/**@brief Quicktime v210, packed YUV, 4:2:2, 10 bits per component, 20 bpp
* @n Reference to the description https://developer.apple.com/library/mac/technotes/tn2162/_index.html
* @hideinitializer */
#define FOURCC_V210  MAKEFOURCC('v', '2', '1', '0')
#endif

#ifndef FOURCC_v210
/**@brief Quicktime v210, packed YUV, 4:2:2, 10 bits per component, 20 bpp
* @n Reference to the description https://developer.apple.com/library/mac/technotes/tn2162/_index.html
* @hideinitializer */
#define FOURCC_v210  MAKEFOURCC('v', '2', '1', '0')
#endif

#ifndef FOURCC_V216
/**@brief Quicktime v216, packed YUV, 4:2:2, 16 bits per component, 32 bpp
* @n Reference to the description https://developer.apple.com/library/mac/technotes/tn2162/_index.html
* @hideinitializer */
#define FOURCC_V216  MAKEFOURCC('v', '2', '1', '6')
#endif

#ifndef FOURCC_v216
/**@brief Quicktime v216, packed YUV, 4:2:2, 16 bits per component, 32 bpp
* @n Reference to the description https://developer.apple.com/library/mac/technotes/tn2162/_index.html
* @hideinitializer */
#define FOURCC_v216  MAKEFOURCC('v', '2', '1', '6')
#endif

#ifndef FOURCC_W009
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 9 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W009 MAKEFOURCC('W', '0', '0', '9')
#endif

#ifndef FOURCC_W010
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 10 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W010 MAKEFOURCC('W', '0', '1', '0')
#endif

#ifndef FOURCC_W011
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 11 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W011 MAKEFOURCC('W', '0', '1', '1')
#endif

#ifndef FOURCC_W012
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 12 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W012 MAKEFOURCC('W', '0', '1', '2')
#endif

#ifndef FOURCC_W013
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 13 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W013 MAKEFOURCC('W', '0', '1', '3')
#endif

#ifndef FOURCC_W014
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 14 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W014 MAKEFOURCC('W', '0', '1', '4')
#endif

#ifndef FOURCC_W015
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component but only low 15 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_W015 MAKEFOURCC('W', '0', '1', '5')
#endif

#ifndef FOURCC_W016
/**@brief Planar YUV, 4:2:0, planes order: Y->V->U, 16 bits per component, 24 bpp
* @hideinitializer */
#define FOURCC_W016 MAKEFOURCC('W', '0', '1', '6')
#endif

#ifndef FOURCC_X009
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 9 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X009 MAKEFOURCC('X', '0', '0', '9')
#endif

#ifndef FOURCC_X010
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 10 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X010 MAKEFOURCC('X', '0', '1', '0')
#endif

#ifndef FOURCC_X011
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 11 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X011 MAKEFOURCC('X', '0', '1', '1')
#endif

#ifndef FOURCC_X012
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 12 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X012 MAKEFOURCC('X', '0', '1', '2')
#endif

#ifndef FOURCC_X013
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 13 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X013 MAKEFOURCC('X', '0', '1', '3')
#endif

#ifndef FOURCC_X014
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component but only low 14 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X014 MAKEFOURCC('X', '0', '1', '4')
#endif

#ifndef FOURCC_X015
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component, but only low 15 bits are significant, 24 bpp
* @hideinitializer */
#define FOURCC_X015 MAKEFOURCC('X', '0', '1', '5')
#endif

#ifndef FOURCC_X016
/**@brief Planar YUV, 4:2:0, planes order: Y->U->V, 16 bits per component, 24 bpp
* @hideinitializer */
#define FOURCC_X016 MAKEFOURCC('X', '0', '1', '6')
#endif

#ifndef FOURCC_W209
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 9 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W209 MAKEFOURCC('W', '2', '0', '9')
#endif

#ifndef FOURCC_W210
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 10 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W210 MAKEFOURCC('W', '2', '1', '0')
#endif

#ifndef FOURCC_W211
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 11 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W211 MAKEFOURCC('W', '2', '1', '1')
#endif

#ifndef FOURCC_W212
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 12 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W212 MAKEFOURCC('W', '2', '1', '2')
#endif

#ifndef FOURCC_W213
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 13 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W213 MAKEFOURCC('W', '2', '1', '3')
#endif

#ifndef FOURCC_W214
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 14 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W214 MAKEFOURCC('W', '2', '1', '4')
#endif

#ifndef FOURCC_W215
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component but only low 15 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_W215 MAKEFOURCC('W', '2', '1', '5')
#endif

#ifndef FOURCC_W216
/**@brief Planar YUV, 4:2:2, planes order: Y->V->U, 16 bits per component, 32 bpp
* @hideinitializer */
#define FOURCC_W216 MAKEFOURCC('W', '2', '1', '6')
#endif

#ifndef FOURCC_X209
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 9 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X209 MAKEFOURCC('X', '2', '0', '9')
#endif

#ifndef FOURCC_X210
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 10 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X210 MAKEFOURCC('X', '2', '1', '0')
#endif

#ifndef FOURCC_X211
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 11 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X211 MAKEFOURCC('X', '2', '1', '1')
#endif

#ifndef FOURCC_X212
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 12 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X212 MAKEFOURCC('X', '2', '1', '2')
#endif

#ifndef FOURCC_X213
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 13 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X213 MAKEFOURCC('X', '2', '1', '3')
#endif

#ifndef FOURCC_X214
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 14 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X214 MAKEFOURCC('X', '2', '1', '4')
#endif

#ifndef FOURCC_X215
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component but only low 14 bits are significant, 32 bpp
* @hideinitializer */
#define FOURCC_X215 MAKEFOURCC('X', '2', '1', '5')
#endif

#ifndef FOURCC_X216
/**@brief Planar YUV, 4:2:2, planes order: Y->U->V, 16 bits per component, 32 bpp
* @hideinitializer */
#define FOURCC_X216 MAKEFOURCC('X', '2', '1', '6')
#endif

#ifndef FOURCC_W409
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 9 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W409 MAKEFOURCC('W', '4', '0', '9')
#endif

#ifndef FOURCC_W410
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 10 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W410 MAKEFOURCC('W', '4', '1', '0')
#endif

#ifndef FOURCC_W411
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 11 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W411 MAKEFOURCC('W', '4', '1', '1')
#endif

#ifndef FOURCC_W412
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 12 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W412 MAKEFOURCC('W', '4', '1', '2')
#endif

#ifndef FOURCC_W413
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 13 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W413 MAKEFOURCC('W', '4', '1', '3')
#endif

#ifndef FOURCC_W414
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 14 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W414 MAKEFOURCC('W', '4', '1', '4')
#endif

#ifndef FOURCC_W415
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component but only low 15 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_W415 MAKEFOURCC('W', '4', '1', '5')
#endif

#ifndef FOURCC_W416
/**@brief Planar YUV, 4:4:4, planes order: Y->V->U, 16 bits per component, 48 bpp
* @hideinitializer */
#define FOURCC_W416 MAKEFOURCC('W', '4', '1', '6')
#endif

#ifndef FOURCC_X409
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 9 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X409 MAKEFOURCC('X', '4', '0', '9')
#endif

#ifndef FOURCC_X410
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 10 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X410 MAKEFOURCC('X', '4', '1', '0')
#endif

#ifndef FOURCC_X411
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 11 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X411 MAKEFOURCC('X', '4', '1', '1')
#endif

#ifndef FOURCC_X412
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 12 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X412 MAKEFOURCC('X', '4', '1', '2')
#endif

#ifndef FOURCC_X413
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 13 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X413 MAKEFOURCC('X', '4', '1', '3')
#endif

#ifndef FOURCC_X414
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 14 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X414 MAKEFOURCC('X', '4', '1', '4')
#endif

#ifndef FOURCC_X415
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component but only low 15 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_X415 MAKEFOURCC('X', '4', '1', '5')
#endif

#ifndef FOURCC_X416
/**@brief Planar YUV, 4:4:4, planes order: Y->U->V, 16 bits per component, 48 bpp
* @hideinitializer */
#define FOURCC_X416 MAKEFOURCC('X', '4', '1', '6')
#endif

#ifndef FOURCC_P010
/**@brief P010, planar YUV, 4:2:0, 16 bits per component but only high 10 bits are significant, 24 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_420formats
* @hideinitializer */
#define FOURCC_P010 MAKEFOURCC('P', '0', '1', '0')
#endif

#ifndef FOURCC_P016
/**@brief P016, planar YUV, 4:2:0, 16 bits per component, 24 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx
* @hideinitializer */
#define FOURCC_P016 MAKEFOURCC('P', '0', '1', '6')
#endif

#ifndef FOURCC_P210
/**@brief P210, planar YUV, 4:2:2, 16 bits per component but only high 10 bits are significant, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_422formats
* @hideinitializer */
#define FOURCC_P210 MAKEFOURCC('P', '2', '1', '0')
#endif

#ifndef FOURCC_P216
/**@brief P216, planar YUV, 4:2:2, 16 bits per component, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_422formats
* @hideinitializer */
#define FOURCC_P216 MAKEFOURCC('P', '2', '1', '6')
#endif

#ifndef FOURCC_Y210
/**@brief Y210, packed YUV, 4:2:2, 16 bits per component but only high 10 bits are significant, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_422formats
* @hideinitializer */
#define FOURCC_Y210 MAKEFOURCC('Y', '2', '1', '0')
#endif

#ifndef FOURCC_Y216
/**@brief Y216, packed YUV, 4:2:2, 16 bits per component, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_422formats
* @hideinitializer */
#define FOURCC_Y216 MAKEFOURCC('Y', '2', '1', '6')
#endif

#ifndef FOURCC_Y410
/**@brief Y410, packed YUV, 4:4:4, 10 bits per component, 2 bits of alpha, 32 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_444formats
* @hideinitializer */
#define FOURCC_Y410 MAKEFOURCC('Y', '4', '1', '0')
#endif

#ifndef FOURCC_Y416
/**@brief Y416, packed YUV, 4:4:4, 16 bits per component, 64 bpp
* @n Reference to the description http://msdn.microsoft.com/en-us/library/bb970578(VS.85).aspx#_444formats
* @hideinitializer */
#define FOURCC_Y416 MAKEFOURCC('Y', '4', '1', '6')
#endif

#ifndef FOURCC_H264
/**@brief AVC/H.264 format
* @hideinitializer */
#define FOURCC_H264 MAKEFOURCC('H', '2', '6', '4')
#endif

#ifndef FOURCC_GRAY
/**@brief Gray YUV (only Y plane), 8 bits per component, 8 bpp
* @hideinitializer */
#define FOURCC_GRAY MAKEFOURCC('G', 'R', 'A', 'Y')
#endif

#ifndef FOURCC_Y09
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 9 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y09 MAKEFOURCC(' ', 'Y', '0', '9')
#endif

#ifndef FOURCC_Y10
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 10 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y10 MAKEFOURCC(' ', 'Y', '1', '0')
#endif

#ifndef FOURCC_Y11
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 11 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y11 MAKEFOURCC(' ', 'Y', '1', '1')
#endif

#ifndef FOURCC_Y12
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 12 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y12 MAKEFOURCC(' ', 'Y', '1', '2')
#endif

#ifndef FOURCC_Y13
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 13 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y13 MAKEFOURCC(' ', 'Y', '1', '3')
#endif

#ifndef FOURCC_Y14
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 14 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y14 MAKEFOURCC(' ', 'Y', '1', '4')
#endif

#ifndef FOURCC_Y15
/**@brief Gray YUV (only Y plane), 16 bits per component but only low 15 bits are significant, 16 bpp
* @hideinitializer */
#define FOURCC_Y15 MAKEFOURCC(' ', 'Y', '1', '5')
#endif

#ifndef FOURCC_Y16
/**@brief Gray YUV (only Y plane), 16 bits per component, 16 bpp
* @hideinitializer */
#define FOURCC_Y16 MAKEFOURCC(' ', 'Y', '1', '6')
#endif

#ifndef FOURCC_AR10
/**@brief Packed RGB, 10 bits per component with 2 bit alpha channel, components order: A->R->G->B, 32 bpp
* @hideinitializer */
#define FOURCC_AR10 MAKEFOURCC('A', 'R', '1', '0')
#endif

#ifndef FOURCC_AB10
/**@brief Packed BGR, 10 bits per component with 2 bit alpha channel, components order: A->B->G->R, 32 bpp
* @hideinitializer */
#define FOURCC_AB10 MAKEFOURCC('A', 'B', '1', '0')
#endif

#ifndef FOURCC_R24P
/**@brief Planar RGB, planes order R->G->B, 8 bits per component, 24 bpp
* @hideinitializer */
#define FOURCC_R24P MAKEFOURCC('R', '2', '4', 'P')
#endif

#ifndef FOURCC_R27P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 9 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R27P MAKEFOURCC('R', '2', '7', 'P')
#endif

#ifndef FOURCC_R30P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 10 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R30P MAKEFOURCC('R', '3', '0', 'P')
#endif

#ifndef FOURCC_R33P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 11 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R33P MAKEFOURCC('R', '3', '3', 'P')
#endif

#ifndef FOURCC_R36P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 12 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R36P MAKEFOURCC('R', '3', '6', 'P')
#endif

#ifndef FOURCC_R39P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 13 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R39P MAKEFOURCC('R', '3', '9', 'P')
#endif

#ifndef FOURCC_R42P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 14 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R42P MAKEFOURCC('R', '4', '2', 'P')
#endif

#ifndef FOURCC_R45P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component but only low 15 bits are significant, 48 bpp
* @hideinitializer */
#define FOURCC_R45P MAKEFOURCC('R', '4', '5', 'P')
#endif

#ifndef FOURCC_R48P
/**@brief Planar RGB, planes order R->G->B, 16 bits per component, 48 bpp
* @hideinitializer */
#define FOURCC_R48P MAKEFOURCC('R', '4', '8', 'P')
#endif

#ifndef FOURCC_b64a
/**@brief Packed BGRA 16-bit, little endian, components order: B->G->R->A, 64 bpp
* @hideinitializer */
#define FOURCC_b64a MAKEFOURCC('b', '6', '4', 'a')
#endif

#ifndef FOURCC_410P
/**@brief Planar YUV, 4:1:0, 8 bits per component, planes order: Y->V->U, 10 bpp
* @hideinitializer */
#define FOURCC_410P MAKEFOURCC('4', '1', '0', 'P')
#endif

#ifndef FOURCC_411P
/**@brief Planar YUV, 4:1:1, 8 bits per component, planes order: Y->V->U, 12 bpp
* @hideinitializer */
#define FOURCC_411P MAKEFOURCC('4', '1', '1', 'P')
#endif

#ifndef FOURCC_211P
/**@brief Planar YUV, 2:1:1, 8 bits per component, planes order: Y->V->U, 8 bpp (yvu211)
* @hideinitializer */
#define FOURCC_211P MAKEFOURCC('2', '1', '1', 'P')
#endif

/** @} */

#endif // #if !defined (__MC_FOURCC_INCLUDED__)

