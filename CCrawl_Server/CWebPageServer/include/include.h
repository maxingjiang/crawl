#pragma once

//#include <afx.h>
#include <stdexcept>
#include <stdlib.h>
#include <vector>
#include <string>
#include <pthread.h>
#include <iostream>
using namespace std;

/************************************************************************/
/* 异常代码                                                               */
/************************************************************************/


/************************************************************************/
/*collector working model                                               */
/************************************************************************/
#define COLLECT_WORK_MODE_MAINURL   0
#define COLLECT_WORK_MODE_URLS		1

/************************************************************************/
/*代码来源                                                                */
/************************************************************************/
#define SOURCECODE 0		//源代码
#define BROWSERCODE 1		//浏览器代码

/************************************************************************/
/*Extract Object   提取对象
0-提取正文 1-提取连接地址 2-提取图片地址
3-提取html代码 4-固定值 5-关键词之后 6-随机行 7-时间
8-提取ubb代码 9-提取map 10-验证码 11-文字识别*/
/************************************************************************/
#define EXTRACT_OBJECT_CONTENT          0
#define EXTRACT_OBJECT_URL              1
#define EXTRACT_OBJECT_PIC_URL          2
#define EXTRACT_OBJECT_HTML_CODE        3
#define EXTRACT_OBJECT_FIXED_VALUE      4
#define EXTRACT_OBJECT_AFTER_KEYWORD    5
#define EXTRACT_OBJECT_RANDOM_LINE      6
#define EXTRACT_OBJECT_TIME             7
#define EXTRACT_OBJECT_UBB_CODE         8
#define EXTRACT_OBJECT_MAP              9
#define EXTRACT_OBJECT_IDENTIFY_CODE    10
#define EXTRACT_OBJECT_OCR              11


/************************************************************************/
/* 网页代码类型                                                           */
/************************************************************************/
#define PAGE_TYPE_LIST		0	//列表页
#define PAGE_TYPE_CONTENT	1	//正文页
#define PAGE_TYPE_DOWNLOAD	2	//下载
#define PAGE_TYPE_JUMP		3	//跳转
#define PAGE_TYPE_NOVEL		4	//小说章节页
#define PAGE_TYPE_ACCOUNTS	5	//帐号
#define PAGE_TYPE_SKYDISK	6	//网盘
#define PAGE_TYPE_TRANSLATE	7	//翻译
#define PAGE_TYPE_MASK		8	//打码
