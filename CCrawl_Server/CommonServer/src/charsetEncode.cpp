/*
 * charsetEncode.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: root
 */

#include "charsetEncode.h"

int CcharsetEncode::charset_convert(const char *from_charset, const char *to_charset,
    char *in_buf, size_t in_left, char *out_buf, size_t out_left)
{
        iconv_t icd;
        char *pin = in_buf;
        char *pout = out_buf;
        size_t out_len = out_left;
        if ((iconv_t)-1 == (icd = iconv_open(to_charset,from_charset)))
        {
            return -1;
        }
        if ((size_t)-1 == iconv(icd, &pin, &in_left, &pout, &out_left))
        {
            iconv_close(icd);
            return -1;
        }
        out_buf[out_len - out_left] = 0;
        iconv_close(icd);
        return (int)out_len - out_left;
}

int CcharsetEncode::charset(const string &desc, string &desk, const char *from_charset,const char *to_charset)
{
	char *to_str_gbk = (char*)calloc(1, desc.size() + 1);
    char *to_str_utf8;
    int len = desc.size()+1;
    memcpy(to_str_gbk, desc.c_str(), len);
    //gbk => utf8
    to_str_utf8 = (char*)calloc(1, len * 3);
    if (-1 == (len = charset_convert(from_charset, to_charset, to_str_gbk,
        len, to_str_utf8, len * 3)))
    {
    	string charsetsrc = string(from_charset)+" => "+to_charset+" error";
        perror(charsetsrc.c_str());
    }
    //output
    //printf("to gbk     : %s\n", to_str_gbk);
    //printf("gbk to utf8: %s\n", to_str_utf8);
    desk = to_str_utf8;
    delete[] to_str_gbk;
    delete[] to_str_utf8;
    return 0;
}

string CcharsetEncode::encode_to_utf8(const string &source)
{
	vector<wchar_t> buff(source.size());
	#ifdef _MSC_VER
	locale loc("zh-CN");
	#else
	locale loc("zh_CN.GB18030");
	#endif
	wchar_t* pwszNext = nullptr;
	const char* pszNext = nullptr;
	mbstate_t state = {};
	int res = use_facet<codecvt<wchar_t, char, mbstate_t> >
	(loc).in(state, source.data(), source.data() + source.size(), pszNext,
	buff.data(), buff.data() + buff.size(), pwszNext);

	if (codecvt_base::ok == res)
	{
		wstring_convert<codecvt_utf8<wchar_t>> cutf8;
		return cutf8.to_bytes(wstring(buff.data(), pwszNext));
	}

	return source;
}

int CcharsetEncode::unicode_to_utf8(string &source)
{
	int sourcesize = source.size();
	string src;
	unsigned char pout[8];
	for(int index = 0; index < sourcesize - 6;)
	{
		memset(pout, 0, 8);
		src = source.substr(index, 6);
		if(isUnicode(src) == 1)
		{
			string hexsrc = source.substr(index + 2, 4);
			int num = enc_unicode_to_utf8_one(xstrtoshortint(hexsrc.c_str()), pout, 8);
			if(num != 0)
			{
				ReplaceStr(source, src.c_str(), (char *)pout, false);
				index += 3;
				sourcesize = source.size();
			}
		}
		else
		{
			index++;
		}
	}
	return 0;
}

int CcharsetEncode::enc_unicode_to_utf8_one(unsigned long unic, unsigned char *pOutput, int outSize)
{
    assert(pOutput != NULL);
    assert(outSize >= 6);

    if ( unic <= 0x0000007F )
    {
        // * U-00000000 - U-0000007F:  0xxxxxxx
        *pOutput     = (unic & 0x7F);
        return 1;
    }
    else if ( unic >= 0x00000080 && unic <= 0x000007FF )
    {
        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
        *(pOutput+1) = (unic & 0x3F) | 0x80;
        *pOutput     = ((unic >> 6) & 0x1F) | 0xC0;
        return 2;
    }
    else if ( unic >= 0x00000800 && unic <= 0x0000FFFF )
    {
        // * U-00000800 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
        *(pOutput+2) = (unic & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >>  6) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 12) & 0x0F) | 0xE0;
        return 3;
    }
    else if ( unic >= 0x00010000 && unic <= 0x001FFFFF )
    {
        // * U-00010000 - U-001FFFFF:  11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+3) = (unic & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 12) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 18) & 0x07) | 0xF0;
        return 4;
    }
    else if ( unic >= 0x00200000 && unic <= 0x03FFFFFF )
    {
        // * U-00200000 - U-03FFFFFF:  111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+4) = (unic & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 18) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 24) & 0x03) | 0xF8;
        return 5;
    }
    else if ( unic >= 0x04000000 && unic <= 0x7FFFFFFF )
    {
        // * U-04000000 - U-7FFFFFFF:  1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
        *(pOutput+5) = (unic & 0x3F) | 0x80;
        *(pOutput+4) = ((unic >>  6) & 0x3F) | 0x80;
        *(pOutput+3) = ((unic >> 12) & 0x3F) | 0x80;
        *(pOutput+2) = ((unic >> 18) & 0x3F) | 0x80;
        *(pOutput+1) = ((unic >> 24) & 0x3F) | 0x80;
        *pOutput     = ((unic >> 30) & 0x01) | 0xFC;
        return 6;
    }
    return 0;
}

int CcharsetEncode::isUnicode(const string &src)
{
	if(src.size() != 6)
		return 0;
	if(src.find("\\u", 0) == 0)
	{
		for(int i = 2; i <= 5; i++)
		{
			if(!((src[i] >= 'a' && src[i] <= 'f')
					|| (src[i] >= 'A' && src[i] <= 'F')
					|| (src[i] >= '0' && src[i] <= '9')))
			{
				return 0;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned int CcharsetEncode::xstrtoshortint(const char *str)
{
    int len = strlen(str);
    unsigned int ivalue = 0;
    for (int i = 0; i < len; i++)
    {
        if ((str[i] <= '9' && str[i] >= '0'))
        {
            ivalue = ivalue * 16 + (str[i] - '0'); //16进制 可换其它进制
        }
        else if ((str[i] >= 'a' && str[i] <= 'f'))
        {
            ivalue = ivalue * 16 + (str[i] - 'a') + 10;
        }
        else if ((str[i] >= 'A' && str[i] <= 'F'))
        {
            ivalue = ivalue * 16 + (str[i] - 'A') + 10;
        }
    }
    return ivalue;
}

void CcharsetEncode::ReplaceStr(string &strContent, const char *strSrc, const char *strDest, bool ignoreCase)
{
    string strCopy(strContent);
    string strSrcCopy(strSrc);

    string::size_type pos = 0;
    string::size_type srclen = strlen(strSrc);
    string::size_type dstlen = strlen(strDest);
    //忽略大小写时，先都转换成小写，然后定位位置，再对源字符串进行替换
    if(ignoreCase)
    {
        //源字符串转化成小写
        transform(strCopy.begin(),strCopy.end(),strCopy.begin(),tolower);
        transform(strSrcCopy.begin(),strSrcCopy.end(),strSrcCopy.begin(),tolower);
    }
    while( (pos=strCopy.find(strSrcCopy, pos)) != string::npos)
    {
        strContent.replace(pos, srclen, strDest);
        pos += dstlen;
        break; //replace once
    }
}

char CcharsetEncode::tolower(char letter)
{
    if (isupper(letter))
	{
		return letter + 32;
	}
	return letter;
}

void CcharsetEncode::setHtmlTagToLower(string &body)
{
	ChtmlTag tag;
	vector<string> tags;
	tag.initHtmlBeginTag(tags);
	for(unsigned int tagindex = 0; tagindex < tags.size(); ++tagindex)
	{
		ReplaceStr(body, tags[tagindex].c_str(), tags[tagindex].c_str(), true);
	}

	tags.clear();
	tag.initHtmlEndTag(tags);
	for(unsigned int tagindex = 0; tagindex < tags.size(); ++tagindex)
	{
		ReplaceStr(body, tags[tagindex].c_str(), tags[tagindex].c_str(), true);
	}
}



