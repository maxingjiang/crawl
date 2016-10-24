/*
 * Encode.h
 *
 *  Created on: Oct 17, 2016
 *      Author: root
 */

#ifndef COMMONSERVER_INCLUDE_ENCODE_H_
#define COMMONSERVER_INCLUDE_ENCODE_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

class CEncode
{
public:
	void base64_encode(string &out, unsigned char const *bytes_to_encode, unsigned int in_len);
	void base64_decode(string &out, string const &encoded_string);

	void URLEncode(string &out, const string &sIn);
	void URLDecode(string &out, const string &sIn);

private:
	unsigned char toHex(const unsigned char &x);
	unsigned char fromHex(const unsigned char &x);

	static const string base64_chars;
	bool is_base64(unsigned char c);
};

#endif /* COMMONSERVER_INCLUDE_ENCODE_H_ */
