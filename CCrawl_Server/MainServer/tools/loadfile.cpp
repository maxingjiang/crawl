#include "curl/curl.h"
#include <iostream>
#include <fstream>
#include <sys/file.h>
using namespace std;
 
struct FtpFile 
{
  const char *filename;
  FILE *stream;
};
 
size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out=(struct FtpFile *)stream;
  if(out && !out->stream) 
  {
    out->stream=fopen(out->filename, "wb");//打开文件进行写入
    if(!out->stream)
      return -1;
  }
  return fwrite(buffer, size, nmemb, out->stream);
}
 
int download(string &downloadurl)
{
     CURL *curl;
     CURLcode res;
     int pos = downloadurl.find_last_of('/');
     string loadfile = "./image_dir/"+downloadurl.substr(downloadurl.length() - pos, downloadurl.length());
     cout<<"addr: "<<loadfile<<endl;
     struct FtpFile ftpfile={loadfile.c_str(), NULL};
    
     curl_global_init(CURL_GLOBAL_DEFAULT);
 
     curl = curl_easy_init();  //初始化一个curl指针
 
     if(curl) 
     { //curl对象存在的情况下执行的操作
        
         //设置远端地址
         curl_easy_setopt(curl, CURLOPT_URL, downloadurl.c_str());
 
         //执行写入文件流操作
         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);//当有数据被写入，回调函数被调用，
         curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile); //设置结构体的指针传递给回调函数
 
         //启用时会汇报所有的信息，存放在STDERR或指定的CURLOPT_STDERR中
         curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
         //curl_easy_setopt(curl, CURLOPT_USERPWD, "SUREN:SUREN");
 
         //写入文件
         res = curl_easy_perform(curl);
 
         //释放curl对象
         curl_easy_cleanup(curl);
 
         if(res != CURLE_OK)
         {
              cout<<stderr<<res<<endl;
         }
     }
 
     if(ftpfile.stream)
     {
         //关闭文件流
         fclose(ftpfile.stream);
     }
  
      //释放全局curl对象
     curl_global_cleanup();
 
     return 0;
 
 }

void run(string &imageurl_filename)
{
    const int LINE_LENGTH = 1024;
    char src[LINE_LENGTH+1];
    string str;
    int urlnum = 0;
    FILE *fp = fopen(imageurl_filename.c_str(), "r");
    if(!fp)
    {
        printf("error file %s \n", imageurl_filename.c_str());
        return ;
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
                int n = str.find_last_not_of(" \r\n\t");
                //std::cout << "src: "<< str << std::endl;
                if( n != string::npos )
                {
                	str.erase( n + 1 , str.size() - n );
                }
                //requestHeaders.push_back(str);
                cout<<urlnum<<"==>url: "<<str<<endl;
				download(str);
        		urlnum++;
            }
            fclose(fp);
            flock(fileno(fp), LOCK_UN);
            break;
        }
        else
        {
        	printf("file %s is locked, please wait \n", imageurl_filename.c_str());
        }
    }
}
 
int main()
{
    //string url = "http://bj.bfbzx.com/uploads/shopface/5f9900d3fb76cd3c8b7117040fd2c160.png";
    //download(url);
    string imageurl_filename = "./image.log";   
    run(imageurl_filename);
}
