/*

(c) Copyright Matrox Electronic Systems Ltd., 2008. All rights reserved. 

This code and information is provided "as is" without warranty of any kind, 
either expressed or implied, including but not limited to the implied 
warranties of merchantability and/or fitness for a particular purpose.

Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
changes in specifications and code at any time and without notice. 
No responsibility is assumed by Matrox Electronic Systems Ltd. for 
its use; nor for any infringements of patents or other rights of 
third parties resulting from its use. No license is granted under 
any patents or patent rights of Matrox Electronic Systems Ltd.

*/

// mv64bitUtils.h
// Luc Bergeron
// March 2008

#ifndef MV64BITUTILS_H
#define MV64BITUTILS_H

#pragma warning(disable : 4311 4312)

template <class T>
__inline
T *
MvToPtr(const T* __ptr64 p)
{
   return(
      (T *)
#if !defined(MAC_PLATFORM) && !defined(LINUX_PLATFORM) && !defined(_WIN64) //Win32
      (uint32_t) 
      (uint64_t) 
#endif
      p);
}

template <class T>
__inline
T * __ptr64
MvToPtr64(const T *p)
{
   return(
      (T * __ptr64) 
#if !defined(MAC_PLATFORM) && !defined(LINUX_PLATFORM) && !defined(_WIN64) //Win32
      (uint64_t) 
      (uint32_t)
#endif
      p);
}

#pragma warning(default : 4311 4312)

#endif //MVUTILITY_H
