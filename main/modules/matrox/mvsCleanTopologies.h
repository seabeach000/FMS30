/*

(c) Copyright Matrox Electronic Systems Ltd., 2013. All rights reserved. 

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


#pragma once

#include "MatroxDSXsdk.h" 
namespace caspar {
	namespace matrox {
class CmvsCleanTopologies 
{
public:
    CmvsCleanTopologies(TMvSmartPtr<IMvSystemConfiguration>in_pSystemConfiguration);
    virtual ~CmvsCleanTopologies();

    HRESULT Clean(const char *in_szTopologyName);
private:
 
private: 
	TMvSmartPtr<IMvSystemConfiguration>	m_pISystemConfiguration;
    IMvCardConfiguration      *m_pICardCfg;
 
};
}}