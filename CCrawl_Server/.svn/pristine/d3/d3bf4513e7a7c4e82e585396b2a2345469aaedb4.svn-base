/*
 * main.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: root
 */

#include "callpy.h"
#include "charsetEncode.h"
#include "readFile.h"
#include "Encode.h"

void testcallpy()
{
	int num = 100;
	while(num--)
	{
		CallPy call;
		CcharsetEncode encode;
		string desk;
		const char * s = "\uff0c";
		string src = s;
		//call.unicode2uft8(src, desk);
		//encode.charset(src, desk, "utf-8", "utf-8");
		cout<<src.size()<<endl;
		encode.unicode_to_utf8(src);
		cout<<num<<" unicode: "<<src<<endl;
	}

}

void testGBKencode()
{
	CcharsetEncode encode;
	string desk;
	const char * s = "我的";
	string src = s;
	encode.charset(src, desk, "utf-8", "GBK");
	cout<<src<<endl;
	cout<<desk<<endl;
	cout<<s<<endl;
	char xx[]="我";
	    printf( "%x%x" , (unsigned char)xx[0] , (unsigned char)xx[1] );
}

void testEncode()
{
	CEncode encode;
	//string test_str1 = "http://www.douguo.com/ingredients/主食";
	string test_str1 = "我的";
	cout << "test_str1=" << test_str1 <<endl;
	string test_str2;
	encode.URLEncode(test_str2, test_str1);
	cout << "test_str2=" << test_str2 <<endl;
	string test_str3;
	encode.URLDecode(test_str3, test_str2);
	cout << "test_str3=" << test_str3 <<endl;
}

void testbase64code()
{
	CEncode encode;
	const string s = "abc" ;

	string encoded;
	encode.base64_encode(encoded, reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
	string decoded;
	encode.base64_decode(decoded, encoded);

	cout << "encoded: " << encoded << endl;
	cout << "decoded: " << decoded << endl;
}

int main()
{
	testGBKencode();
	return 0;
	int i = 5;
	while(i--)
	{
		//testcallpy();
		testEncode();
		testbase64code();
	}
	return 0;
}


