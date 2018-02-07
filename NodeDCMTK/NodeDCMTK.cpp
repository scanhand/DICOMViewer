// NodeDCMTK.cpp: DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "NodeDCMTK.h"
#include "dcmtk/dcmdata/dcfilefo.h"
#include "dcmtk/dcmdata/dctagkey.h"
#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

#define MAX_STRINGBUFFER_SIZE	1024

char g_string_buffer[MAX_STRINGBUFFER_SIZE] = { 0, };

int test_sum(int a, int b)
{
	return a + b;
}

void test_parameter_string(char* param)
{
	char buffer[256];
	sprintf(buffer, "test_parameter_string::param=%s", param);
	OutputDebugStringA(buffer);
}

char* test_return_string(double data)
{
	sprintf(g_string_buffer, "convert::%f", data);
	return g_string_buffer;
}

void test_loaddcm(char* fileName)
{
	DcmFileFormat dcmfileFormat;
	OFCondition status = dcmfileFormat.loadFile(fileName);
	if (!status.good())
		return;

	for (long i = 0; i < dcmfileFormat.getDataset()->card(); i++)
	{
		DcmElement* pElement = dcmfileFormat.getDataset()->getElement(i);
		if (pElement == NULL)
			continue;

		OFString value;
		status = pElement->getOFString(value, 0);
		if (!status.good())
			continue;

		char buffer[256];
		sprintf(buffer, "[%04X:%04X] %s : %s", pElement->getGTag(), pElement->getETag(), ((DcmTag&)pElement->getTag()).getTagName(), value);
		OutputDebugStringA(buffer);
	}
}

void* test_get_DcmFileFormat(char* fileName)
{
	DcmFileFormat *pDcmfileFormat = new DcmFileFormat();
	OFCondition status = pDcmfileFormat->loadFile(fileName);
	if (!status.good())
		return NULL;

	return pDcmfileFormat;
}

void test_voidptr_paramter(void* dcmPtr)
{
	DcmFileFormat* pDcmFileFormat = (DcmFileFormat*)dcmPtr;
	OFString patientName;
	if (pDcmFileFormat->getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
	{
		char buffer[256];
		sprintf(buffer, "PatientName=%s", patientName);
		OutputDebugStringA(buffer);
	}
}