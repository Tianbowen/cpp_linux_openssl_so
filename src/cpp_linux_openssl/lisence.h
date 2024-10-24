#pragma once

#ifdef LISENCELIBRARY_EXPORTS
#define LISENCELIBRARY_EXPORTS __declspec(dllexport)
#else
#define LISENCELIBRARY_EXPORTS __declspec(dllimport)
#endif

//#ifndef LICENSEENTITY
//#define LICENSEENTITY
//#pragma pack(1) //LICENSE_ENTITY_STRUCT // typedef
struct LICENSE_ENTITY
{
	char BindHostNo[64];
	char Version[64];
	char ProjectType[64];
	char TerminalType[64];
	char TerminalNunber[64];
	char StartTime[64];
	char ExpireTime[64];
	char SN[64];
	char ProductNo[64];
};
//struct LICENSE_ENTITY
//{
//	string BindHostNo;
//	string Version;
//	string ProjectType;
//	string TerminalType;
//	string TerminalMNunber;
//	string StartTime;
//	string ExpireTime;
//	string SN;
//	string ProductNo;
//};
//#pragma pack()
//#endif

#ifdef __cplusplus
extern "C" {
#endif
	LISENCELIBRARY_EXPORTS int __stdcall vaild(const char* des_key, LICENSE_ENTITY* pentity);
#ifdef __cplusplus
}
#endif