/*
 * Encode.cpp
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#include "Encode.h"

const string CEncode::base64_chars ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned char CEncode::toHex(const unsigned char &x)
{
	return x > 9 ? x -10 + 'A': x + '0';
}

unsigned char CEncode::fromHex(const unsigned char &x)
{
	return isdigit(x) ? x-'0' : x-'A'+10;
}

void CEncode::URLEncode(string &out, const string &sIn)
   {
	   string sOut;
	   for( size_t ix = 0; ix < sIn.size(); ix++ )
	   {
		   unsigned char buf[4];
		   memset( buf, 0, 4 );
		   if( isalnum( (unsigned char)sIn[ix] ) )
		   {
			   buf[0] = sIn[ix];
		   }
		   //else if ( isspace( (unsigned char)sIn[ix] ) ) //貌似把空格编码成%20或者+都可以
		   //{
		   //    buf[0] = '+';
		   //}
		   else
		   {
			   buf[0] = '%';
			   buf[1] = toHex( (unsigned char)sIn[ix] >> 4 );
			   buf[2] = toHex( (unsigned char)sIn[ix] % 16);
		   }
		   sOut += (char *)buf;
	   }
	   out = sOut;
   };

void CEncode::URLDecode(string &out, const string &sIn)
{
   string sOut;
   for( size_t ix = 0; ix < sIn.size(); ix++ )
   {
	   unsigned char ch = 0;
	   if(sIn[ix]=='%')
	   {
		   ch = (fromHex(sIn[ix+1])<<4);
		   ch |= fromHex(sIn[ix+2]);
		   ix += 2;
	   }
	   else if(sIn[ix] == '+')
	   {
		   ch = ' ';
	   }
	   else
	   {
		   ch = sIn[ix];
	   }
	   sOut += (char)ch;
   }
   out = sOut;
}

bool CEncode::is_base64(unsigned char c)
{
  return (isalnum(c) || (c == '+') || (c == '/'));
}

void CEncode::base64_encode(string &out, unsigned char const *bytes_to_encode, unsigned int in_len)
{
	string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++)
			{
				ret += base64_chars[char_array_4[i]];
			}
			i = 0;
		}
	}

	if (i)
	{
		for(j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			ret += base64_chars[char_array_4[j]];
		}

		while((i++ < 3))
		{
			ret += '=';
		}
	}
	out = ret;
}

void CEncode::base64_decode(string &out, string const &encoded_string)
{
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i ==4)
		{
			for (i = 0; i <4; i++)
			{
				char_array_4[i] = base64_chars.find(char_array_4[i]);
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				ret += char_array_3[i];
			}
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j <4; j++)
		{
			char_array_4[j] = 0;
		}

		for (j = 0; j <4; j++)
		{
			char_array_4[j] = base64_chars.find(char_array_4[j]);
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			ret += char_array_3[j];
		}
	}

	out = ret;
}

