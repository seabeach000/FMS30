/*

(c) Copyright Matrox Electronic Systems Ltd., 2003. All rights reserved. 

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



#ifndef MVSYSTEMCPUDETECTION_H
#define MVSYSTEMCPUDETECTION_H

#include "mvSharedMemory.h"
#include <vector>

#ifndef	LINUX_PLATFORM
        #include <intrin.h>
        typedef	unsigned int	cpu_set_t;
#else
	#include "mvLinuxDefinitions.h"
#endif
//////////////////////////////////////////////////////////////////////////
//
// Summary:
//    This class is used to get the number of physical and logical processors in the system.
//
// Remarks:
//    - They can also be used to get the features supported by the processors.
//////////////////////////////////////////////////////////////////////////
class CMvSystemCpuDetection
{
public:
   //
   // Summary:
   //    Detection of the CPU is done.
   // Description:
   //    Most of the work is done in this method. The calling thread is made to run on each 
   //    processor in the system in order to associate and logical and physical index to a Win32
   //    affinity mask. The features supported by the processors are also detected at this time.
   //    You should not create and destroy objects of this type too often.
   //
   CMvSystemCpuDetection();
   ~CMvSystemCpuDetection();

   //
   // Summary:
   //    Returns true if the processors are from Intel.
   //
   bool IsIntel() const { return m_sProcDescription.m_bIntel; }

   //
   // Summary:
   //    Returns true if the processors are from AMD.
   //
   bool IsAMD() const { return m_sProcDescription.m_bAMD; }

   //
   // Summary:
   //    Returns true if MMX instructions are supported.
   //
   bool IsMMXSupported() const { return m_sProcDescription.m_bMMX; }

   //
   // Summary:
   //    Returns true if SSE instructions are supported.
   //
   bool IsSSESupported() const { return m_sProcDescription.m_bSSE; }

   //
   // Summary:
   //    Returns true if SSE2 instructions are supported.
   //
   bool IsSSE2Supported() const { return m_sProcDescription.m_bSSE2; }

   //
   // Summary:
   //    Returns true if SSE3 instructions are supported.
   //
   bool IsSSE3Supported() const { return m_sProcDescription.m_bSSE3; }

   //
   // Summary:
   //    Returns true if Hyper-Threading is enabled.
   //
   bool IsHyperThreadingSupported() const { return m_sProcDescription.m_bHyperthreading; }

   //
   // Summary:
   //    Returns the number of logical processors in the system.
   //
   unsigned int GetLogicalProcessorCount() const { return m_sProcDescription.m_uiLogicalProcessorCount; }

   //
   // Summary:
   //    Returns the number of physical processors in the system.
   //
   unsigned int GetPhysicalProcessorCount() const { return m_sProcDescription.m_uiPhysicalProcessorCount; }

   //
   // Summary:
   //    Returns the number of logical processors per physical processor.
   //
   unsigned int GetLogicalPerPhysical() const { return m_sProcDescription.m_uiLogicalPerPhysical; }

   //
   // Summary:
   //    Returns the number of core processors in the system.
   //
   unsigned int GetCoreCount() const { return m_sProcDescription.m_uiCoreCount; }   

   //
   // Summary:
   //    Returns the number of core processors per physical processor.
   //
   unsigned int GetCorePerPhysical() const { return m_sProcDescription.m_uiCorePerPhysical; }   

   //
   // Summary:
   //    Returns the Level 2 cache size.
   //
   unsigned int GetLevel2CacheSize() const { return m_sProcDescription.m_uiLevel2CacheSize; }

   //
   // Summary:
   //    Returns the associatively of the level 2 cache.
   //
   unsigned int GetLevel2CacheAssociativity() const { return m_sProcDescription.m_uiLevel2CacheAssociativity; }

   //
   // Summary:
   //    Returns the level 2 cache line size.
   //
   unsigned int GetLevel2CacheLineSize() const { return m_sProcDescription.m_uiLevel2CacheLineSize; }

   unsigned int GetNbOfCoresPerPhysical();

   //
   // Summary:
   //    Returns the physical processor index according to the logical number defined by the
   //    affinity mask.
   //
   unsigned int GetPhysicalProcessorIndex(const cpu_set_t in_kuiAffinityMask);

   //
   // Summary:
   //    Returns true if the in_uiPhysicalProcessorIndex and in_uiLogicalProcessorSubIndex are 
   //    valid indexes, and also returns the corresponding affinity mask for the specified indexes
   //    via out_puiProcessorAffinity.
   //
   bool GetProcessorAffinityMask(unsigned int in_uiPhysicalProcessorIndex, unsigned int in_uiLogicalProcessorSubIndex, cpu_set_t* out_puiProcessorAffinity) const;

   //
   // Summary:
   //    Uses the Win32::SetThreadAffinityMask() function so that the calling thread executes on 
   //    the specified logical processor of a physical processor.
   //
   bool SetThreadProcessorAffinity(unsigned int in_uiPhysicalProcessorIndex, unsigned int in_uiLogicalProcessorSubIndex) const;

private:
   // Internal method
   void DetectProcessorFeatures();

   // Internal method
   void CollectLogicalProcessorInfo();

   // Internal method
   void ParseIntelCacheInfo(unsigned int in_auiIntelCacheInfo[4]);

   // Internal method
   void ParseAMDCacheInfo();

   // Internal method
   void SetCPUDetectionInformation();

   // Internal method
   bool SaveInfoToSharedMemory();

   // Internal method
   void GetInfoFromSharedMemory();

   // Internal method
   unsigned int GetProcessorApicId() const;

   // Purposely not implemented.
   CMvSystemCpuDetection(const CMvSystemCpuDetection&);

   // Purposely not implemented.
   CMvSystemCpuDetection& operator=(const CMvSystemCpuDetection&);

   CMvEvent * m_poEventCpuDetect;
   CMvEvent * m_poEventCpuDetect2;


   // Description of a processor.
   struct SProcDescription
   {
      bool m_bCpuId;    // 
      bool m_bIntel;    // 
      bool m_bAMD;      // 
      bool m_bMMX;      // 
      bool m_bSSE;      // 
      bool m_bSSE2;     // 
      bool m_bSSE3;     // 
      bool m_bHyperthreading;                      // 
      unsigned int m_uiLogicalProcessorCount;      // 
      unsigned int m_uiLogicalPerPhysical;         // 
      unsigned int m_uiPhysicalProcessorCount;     // 
      unsigned int m_uiCoreCount;                  // 
      unsigned int m_uiCorePerPhysical;            // 
      unsigned int m_uiLevel2CacheSize;            // 
      unsigned int m_uiLevel2CacheAssociativity;   // 
      unsigned int m_uiLevel2CacheLineSize;        // 
      unsigned int m_uiNbOfLogicalProcessor;

   } m_sProcDescription;

   
   CMvSharedMemory   *  m_poSharedMemory;

   // Maximum number of processor supported by this class.
   //static const int gs_iMaxProcessorsSupported = 64;
   // Array of element identifying each processor in the system
   struct SLogicalProcessorInfo
   {
      unsigned int m_uiPhysicalProcessorId;        //  
      unsigned int m_uiLogicalProcessorId;         // 
      unsigned int m_uiPhysicalProcessorIndex;     // 
      unsigned int m_uiLogicalProcessorSubIndex;   // 
      cpu_set_t	   m_uiAffinityMask;               // 
   };

   std::vector<SLogicalProcessorInfo> m_vecsLogicalProcessorInfo;
   

   unsigned int m_uiHighestValue; //Maximum supported CPUID leaf/function information
   unsigned int m_uiHighestExtended; //Maximum meaningful value of InfoType for extended function CPUID information.
};


#endif //MVSYSTEMCPUDETECTION_H


