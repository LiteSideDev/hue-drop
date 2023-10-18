/*The goal is to create a program that will Use libcurl and OpenSSL to get and push info
to the hue bridge. For now just get info and turn lights on and off.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <curl/curl.h>
#include <json.h>

typedef struct
{
    char *id;
    uint8_t bri;
    uint8_t sat;
    uint16_t hue;

}light;

struct string
{
    char *ptr;
    size_t len;
};

void init_string(struct string *s)
{
    s->len = 0;
    s->ptr = malloc(s->len+1);
    if(s->ptr == NULL)
    {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
    size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if (s->ptr == NULL)
    {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;
}

int main(void)
{
    CURL *hue;
    CURLcode rv;

    hue = curl_easy_init();
    if(hue)
    {
        struct string s;
        init_string(&s);

        curl_easy_setopt(hue, CURLOPT_URL, "http://192.168.0.166/api/SX4s2BPf3QobZOjMAxME7T1Tdnk1qes9BofUQHYl/lights");
        curl_easy_setopt(hue, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(hue, CURLOPT_WRITEDATA, &s);
        rv = curl_easy_perform(hue);

        printf("%s\n", s.ptr);
        free(s.ptr);

        curl_easy_cleanup(hue);
    }
    return 0;
}