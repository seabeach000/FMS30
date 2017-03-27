#ifndef MVIPCACKNOWLEDGEEVENTPOOLELEMENT_H_
#define MVIPCACKNOWLEDGEEVENTPOOLELEMENT_H_

#include "mvUtility.h"
#include "mvTypes.h" //For uint64_t

class CMvIPCAcknowledgeEventPoolElement
{
public:   

	//==========================================================================;
	// Public operations
	//==========================================================================;
	CMvIPCAcknowledgeEventPoolElement(uint64_t in_ui64UniqueID, unsigned long in_ulProcessID);
	virtual ~CMvIPCAcknowledgeEventPoolElement();

	CMvEvent * GetAcknowledgeEvent();
	uint64_t GetAcknowledgeEventID();

protected:
	CMvEvent * CreateEvent(const char * strName);

	uint64_t m_ui64AcknowledgeID;
	CMvEvent * m_poAcknowledgeEvent;
};
#endif

