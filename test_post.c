#include <stdio.h>
#include <curl/curl.h>

int postUrl(char *filename)
{
    CURL *curl;
    CURLcode res;
    FILE *fp;
    if ((fp = fopen(filename, "w")) == NULL)
        return 0;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "input1=123&input2=456&remember=False");
        //curl_easy_setopt(curl, CURLOPT_PROXY, "10.99.60.201:8080");
        curl_easy_setopt(curl, CURLOPT_URL, "http://passport.cnblogs.com/(X(1)S(eaccajjo3wecsnpojuhychid))/user/signin?AspxAutoDetectCookieSupport=1");   // 指定url
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    fclose(fp);
    return 1;
}
int main(void)
{
    postUrl("post.html");
}
