/*
 * CPPregex.cpp
 *
 *  Created on: Aug 2, 2016
 *      Author: root
 */

#include "CPPregex.h"

int CPPregex::getCharset(const string &responseBody, string &charset, const string &charsetRegex)
{
    boost::regex expression(charsetRegex);
    boost::smatch what;

    if(boost::regex_search(responseBody, what, expression))
    {
        //cout << what.size() << endl;
    	if(what.size() >= 2)
    	{
    		//cout << what[1] << endl;
    		charset = what[1];
    		return 1;
    	}
    }
    charset = ""; //not match charset
	return 0;
}

void CPPregex::removeSpace(string &src)
{
	src.erase( remove( src.begin(), src.end(), '\n' ), src.end() );
	src.erase( remove( src.begin(), src.end(), '\r' ), src.end() );
	src.erase( remove( src.begin(), src.end(), '\t' ), src.end() );
}

