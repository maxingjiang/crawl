/*
 * readFile.cpp
 *
 *  Created on: Jul 14, 2016
 *      Author: root
 */

#include "readFile.h"

vector<string> CreadFile::split(const string& source, const string& s)
{
    vector<string> elems;
    size_t pos = 0;
    size_t len = source.length();
    size_t s_len = s.length();
    if (len == 0 || s_len == 0)
        return elems;
    while (pos < len)
    {
        int find_pos = source.find(s, pos);
        if (find_pos < 0)
        {
            elems.push_back(source.substr(pos, len - pos));
            break;
        }
        elems.push_back(source.substr(pos, find_pos - pos));
        pos = find_pos + s_len;
    }
    return elems;
}

vector<string> CreadFile::getFileString(const string &filename)
{
	vector<string> FileStrings;
	const int LINE_LENGTH = 2048;
	char src[LINE_LENGTH+1];
    string str;
    FILE *fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", filename.c_str());
        return FileStrings;
    }
    while(1)
    {
    	// 加锁以判断文件是否已经被加锁了
    	if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
        {
    		//printf("file %s is unlock status \n", filename.c_str());
        	while ((fgets (src, LINE_LENGTH, fp)) != NULL)
            {
            	str = src;
            	size_t n = str.find_last_not_of(" \r\n\t");
                //std::cout << "src: "<< str << std::endl;
                if( n != string::npos )
                {
                	str.erase( n + 1 , str.size() - n );
                }
                FileStrings.push_back(str);
            }
            fclose(fp);
            flock(fileno(fp), LOCK_UN);
            break;
        }
        else
        {
        	printf("file %s is locked, please wait \n", filename.c_str());
        	sleep(1);
        }
    }
    return FileStrings;
}

void CreadFile::buildCPPCode(const string &filename)
{
	vector<string> FileStrings;
	const int LINE_LENGTH = 1024;
	char src[LINE_LENGTH+1];
    string str;
    FILE *fp = fopen(filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", filename.c_str());
    }
    while(1)
    {
    	// 加锁以判断文件是否已经被加锁了
    	if(flock(fileno(fp), LOCK_EX | LOCK_NB) == 0)
        {
    		//printf("file %s is unlock status \n", filename.c_str());
        	while ((fgets (src, LINE_LENGTH, fp)) != NULL)
            {
            	str = src;
            	size_t n = str.find_last_not_of(" \r\n\t");
                //std::cout << "src: "<< str << std::endl;
                if( n != string::npos )
                {
                	str.erase( n + 1 , str.size() - n );
                }
                FileStrings.push_back(str);
                string cmd = string("echo \"else if(strtag == \\\"")+str+"\\\")\n    tag = "+str+";\" >> ./url.hpp";
                cout<<"str: "<<cmd<<endl;
                system(cmd.c_str());
            }
            fclose(fp);
            flock(fileno(fp), LOCK_UN);
            break;
        }
        else
        {
        	printf("file %s is locked, please wait \n", filename.c_str());
        	sleep(1);
        }
    }
}

