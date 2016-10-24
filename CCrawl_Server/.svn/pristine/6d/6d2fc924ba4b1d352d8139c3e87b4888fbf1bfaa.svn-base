/*
 * RequestPostdata.h
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#ifndef INCLUDE_requestMode_H_
#define INCLUDE_requestMode_H_

#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <curl/easy.h>
#include "CHttpRequest.h"
#include "common.h"

using namespace std;

/*
 * example
 * POST
 * app_token=2cc896fc49944baeb5bef1ed31d86737&cityId=279&id=6459b43f-b8a5-4a7b-8f25-d4205df2d315&userId=5745187f46424f3281225e6e6f3851e7
 *
*/

class CRequestPostdata
{
public:
	CRequestPostdata();
	~CRequestPostdata();

    void setPostdata(const string &postdata);
    string getPostdata();
    void sendPostdata(CHttpRequest * httpRequest);

private:
	string m_postdata;
};


#endif /* INCLUDE_REQUESTHEADERS_REQUESTMODE_H_ */
