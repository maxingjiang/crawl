/*
 * split.cpp
 *
 *  Created on: Jun 16, 2016
 *      Author: root
 */

#include "split.h"

vector<string> Csplit::split(const string& source, const string& s)
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


size_t namespace_split::write_data(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long sizes = size * nmemb;
    if (writerData == NULL)
    	return 0;
    writerData->append(data, sizes);
    return sizes;
}

size_t namespace_split::write_header(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long sizes = size * nmemb;
    if (writerData == NULL)
    	return 0;
    writerData->append(data, sizes);
    return sizes;
}

size_t namespace_split::fwrite_data(void *data, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out=(struct FtpFile *)stream;
  if(out && !out->stream)
  {
    out->stream=fopen(out->filename, "wb");//打开文件进行写入
    if(!out->stream)
      return -1;
  }
  return fwrite(data, size, nmemb, out->stream);
}



