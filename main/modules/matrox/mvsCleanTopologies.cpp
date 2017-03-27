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

#include "mvsCleanTopologies.h"
namespace caspar {
	namespace matrox {

		// ----------------------------------------------------------------------------
		CmvsCleanTopologies::CmvsCleanTopologies(TMvSmartPtr<IMvSystemConfiguration>in_pSystemConfiguration)
			: m_pISystemConfiguration(NULL)
			, m_pICardCfg(NULL)
		{
			m_pISystemConfiguration = in_pSystemConfiguration;
		}


		// ----------------------------------------------------------------------------
		CmvsCleanTopologies::~CmvsCleanTopologies()
		{

		}

		// ----------------------------------------------------------------------------
		HRESULT CmvsCleanTopologies::Clean(const char *in_szTopologyName)
		{
			CMvHResult oHr;

			IMvSystemTopologyEnumerator* pITopologiesEnumerator = NULL;

			oHr = m_pISystemConfiguration->CreateSystemTopologyEnumerator(&pITopologiesEnumerator);
			IMvSystemTopology*  pITopology = NULL;

			if (oHr.DidSucceed() && pITopologiesEnumerator)
			{
				pITopologiesEnumerator->Reset();
				do
				{
					pITopology = NULL;
					pITopologiesEnumerator->Next(&pITopology);

					if (pITopology)
					{
						char szTopologyName[128];
						pITopology->GetName(szTopologyName, 128);
						if ((strcmp(in_szTopologyName, "") == 0 || strcmp(in_szTopologyName, szTopologyName) == 0))
						{
							pITopology->AcquireControl();
							pITopology->DestroyAllComponents();
							pITopology->DestroyTopology();
							pITopology->Release();
						}
						else
						{
							pITopology->Release();
						}
					}

				} while (pITopology);

				pITopologiesEnumerator->Release();
			}

			return oHr;
		}
	}
}
