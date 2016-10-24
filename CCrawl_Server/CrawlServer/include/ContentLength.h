/*
 * ContentLength.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_ContentLength_H_
#define INCLUDE_ContentLength_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * example(post need)
 * Content-Length: 120
 *
*/

class CContentLength
{
public:
	CContentLength();
	~CContentLength();

    void setContentLength(const string &ContentLength);
    string getContentLength();
private:
	string m_ContentLength;
};

#endif /* INCLUDE_ContentLength_H_ */
