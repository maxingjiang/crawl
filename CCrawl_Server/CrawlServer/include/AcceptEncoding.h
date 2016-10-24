/*
 * AcceptEncoding.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_REQUESTHEADERS_ACCEPTENCODING_H_
#define INCLUDE_REQUESTHEADERS_ACCEPTENCODING_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * example
 * Accept-Encoding: gzip, deflate
 *
*/

class CAcceptEncoding
{
public:
	CAcceptEncoding();
	~CAcceptEncoding();

    void setAcceptEncoding(const string &acceptencoding);
    string getAcceptEncoding();
private:
	string m_acceptEncoding;
};

#endif /* INCLUDE_REQUESTHEADERS_ACCEPTENCODING_H_ */
