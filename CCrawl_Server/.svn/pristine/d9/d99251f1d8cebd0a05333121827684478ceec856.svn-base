/*
 * charsetEncode.h
 *
 *  Created on: Jul 25, 2016
 *      Author: root
 */

#ifndef COMMONSERVER_INCLUDE_CHARSETENCODE_H_
#define COMMONSERVER_INCLUDE_CHARSETENCODE_H_

#include <iostream>
#include <algorithm>
#include <string>
#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "ChtmlTag.h"
#include <locale>
#include <codecvt>
#include <assert.h>

using namespace std;
/*
 * useage:(http://www.qq.com/ convert faild: Invalid or incomplete multibyte or wide character)
 * 	CcharsetEncode cc = CcharsetEncode(charset.c_str(),"utf-8");
 *	string data;
 *	cc.charset(body, data, charset.c_str(),"utf-8");
 * */
class CcharsetEncode
{
public:

   int charset_convert(const char *from_charset, const char *to_charset,
       char *in_buf, size_t in_left, char *out_buf, size_t out_left);
   int charset(const string &desc, string &desk, const char *from_charset,const char *to_charset);

   //任意编码格式转utf8，返回转码后的字符串，待验证
   string encode_to_utf8(const string &source); //gb2312_to_utf8,gbk_to_utf8

   int unicode_to_utf8(string &source);//unicode to utf-8

   //字符串忽略大小写字串替换
   void ReplaceStr(string &strContent, const char *strSrc, const char *strDest, bool ignoreCase);

   void setHtmlTagToLower(string &body);
   static char tolower(char letter); //call_back function

private:

    int enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput, int outSize);
    int isUnicode(const string &src); //the src is unicode or not, total 6 char(0x5e3f).1,yes;2,no
    unsigned int xstrtoshortint(const char *str); //"0x1a3f"->1a3f

};

#endif /* COMMONSERVER_INCLUDE_CHARSETENCODE_H_ */
