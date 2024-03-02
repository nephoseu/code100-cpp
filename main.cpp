#include <iostream>
#include <curl/curl.h>

using namespace std;

int main() 
{   
    // Step 1: Login
    CURL *loginCurl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    loginCurl = curl_easy_init();

    if (loginCurl) {
        curl_easy_setopt(loginCurl, CURLOPT_URL, "https://challenger.code100.dev/login");
        curl_easy_setopt(loginCurl, CURLOPT_POSTFIELDS, "({\"email\": \"any\", \"password\": \"any\"})\")";

        curl_easy_perform(loginCurl);
        curl_easy_cleanup(loginCurl);
    }

    // Extract the token from the login response and set it as a header for the next request

    // Step 2: Call Authenticated Endpoint
    CURL *authCurl;
    authCurl = curl_easy_init();

    if (authCurl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: Bearer <TOKEN>");

        curl_easy_setopt(authCurl, CURLOPT_URL, "http://challenger.code100.dev/testauthroute");
        curl_easy_setopt(authCurl, CURLOPT_HTTPHEADER, headers);

        curl_easy_perform(authCurl);
        curl_easy_cleanup(authCurl);
    }

    return 0;
}