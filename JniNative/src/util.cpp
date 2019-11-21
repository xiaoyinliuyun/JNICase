#include "case.h"
#include "windows.h"

// ���ַ� -> ���ַ�
WCHAR* char2u(const char* str){
	int len = MultiByteToWideChar(CP_UTF8,0,str,-1,NULL,0);
	int size = sizeof(WCHAR)*(len+1);
	WCHAR * dBuf = (WCHAR*)malloc(size);
	memset(dBuf,0,size);
	int ret = MultiByteToWideChar(CP_UTF8,0,str,-1,dBuf,len);
	if(ret <= 0){
		free(dBuf);
		return NULL;
	}else{
	    return dBuf;
	}
}

// ���ַ� -> ���ַ�
const char * u2utf(WCHAR * buf){
	int len = WideCharToMultiByte(CP_UTF8,0,buf,-1,NULL,0,NULL,FALSE);
	char *dBuf = new char[len];
	memset(dBuf,0,len);
	int ret = WideCharToMultiByte(CP_UTF8,0,buf,-1,dBuf,len,NULL,FALSE);
	if(ret<=0){
		delete[] dBuf;
		return NULL;
	}else{
		return dBuf;
	}
}