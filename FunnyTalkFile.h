#pragma once

//************************************************************************************************
//*************************** 文件操作 ***********************************************************
//************************************************************************************************

// 获取程序当前目录
void FileGetPath(void);
// 获取文件路径
void FileGetName(LPTSTR);
// 读取文件数据
bool FileGetData(LPTSTR, char*, int);