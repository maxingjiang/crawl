/*
 * CacheControl.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_CacheControl_H_
#define INCLUDE_CacheControl_H_

#include <iostream>
#include <string>

using namespace std;

/*
 * example
 * Cache-Control: max-age=0
 *
*/

class CCacheControl
{
public:
	CCacheControl();
	~CCacheControl();

    void setCacheControl(const string &CacheControl);
    string getCacheControl();
private:
	string m_CacheControl;
};

#endif /* INCLUDE_CacheControl_H_ */
