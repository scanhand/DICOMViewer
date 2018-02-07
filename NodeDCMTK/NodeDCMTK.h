#pragma once

#define DllExport   __declspec( dllexport )  

extern "C" {

	DllExport int test_sum(int a, int b);

	DllExport void test_parameter_string(char* param);

	DllExport char* test_return_string(double data);

	DllExport void test_loaddcm(char* fileName);

	DllExport void* test_get_DcmFileFormat(char* fileName);

	DllExport void test_voidptr_paramter(void* dcmPtr);

	DllExport int OpenDcmFileFormat(char* fileName, void** dcmptr);

	DllExport int DumpDcmTag(void* dcmPtr);
}