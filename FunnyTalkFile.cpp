// 预编译
#include "stdafx.h"

// 文件处理
#include "FunnyTalkFile.h"

// 路径全局变量
TCHAR	ThePath[MAX_PATH];
TCHAR	TheFileName[MAX_PATH];

//************************************************************************************************
//*************************** 文件操作 ***********************************************************
//************************************************************************************************

// 获取程序当前目录
void FileGetPath(void)
{

	// 获取
	GetModuleFileName(NULL,ThePath,MAX_PATH);
	
	// 去掉文件名
	for(int i=MAX_PATH;i>0;i--){
		if(ThePath[i]=='\\'){
			break;
		}else{
			ThePath[i]='\0';
		}
	}

}

// 获取文件路径
void FileGetName(LPTSTR fileName)
{

	int j = 0;

	// 复制路径到文件名
	for(int i=0;i<MAX_PATH;i++){

		if(ThePath[i]=='\0'){

			TheFileName[i] = fileName[j];
			if(fileName[j]=='\0'){break;}	
			j++;
		
		}else{

			TheFileName[i] = ThePath[i];

		}

	}

}

// 读取文件数据
bool FileGetData(LPTSTR fileName, char* fileBuffer, int fileSize)
{

	// 获取文件名
	FileGetName(fileName);

	// 文件句柄
	HANDLE hFile = CreateFile(TheFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// 读取字节数
	DWORD dSize = 0;

	// 无法打开文件
	if(hFile==INVALID_HANDLE_VALUE){
		return false;
	}

	// 读取文件
	if(!ReadFile(hFile,fileBuffer,fileSize,&dSize,NULL)){
		return false;
	}

	// 关闭文件句柄
	CloseHandle(hFile);

	return true;

}