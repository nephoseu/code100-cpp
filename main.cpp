#include <iostream>
#include <curl/curl.h>
#include <string>

using namespace std;

int main() 
{   
    std::string email = "totipu@nephos.eu";
    std::string password = "cibona2!";

    // Step 1: Login
    CURL *loginCurl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    loginCurl = curl_easy_init();

    if (loginCurl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");

        curl_easy_setopt(loginCurl, CURLOPT_HTTPHEADER, headers);

        std::string json_body = "{\"email\":\"" + email + "\", \"password\": \"" + password + "\"}";
        
        curl_easy_setopt(loginCurl, CURLOPT_URL, "https://challenger.code100.dev/login");
        curl_easy_setopt(loginCurl, CURLOPT_POST, 1);
        curl_easy_setopt(loginCurl, CURLOPT_POSTFIELDS, json_body.c_str());

        curl_easy_perform(loginCurl);
        curl_easy_cleanup(loginCurl);
    }

    // Extract the token from the login response and set it as a header for the next request

    // Step 2: Call Authenticated Endpoint
    CURL *authCurl;
    authCurl = curl_easy_init();

    if (authCurl) {
        cout << "\nCalling...\n";
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: Bearer <TOKEN>");

        curl_easy_setopt(authCurl, CURLOPT_URL, "http://challenger.code100.dev/testauthroute");
        curl_easy_setopt(authCurl, CURLOPT_HTTPHEADER, headers);

        curl_easy_perform(authCurl);
        curl_easy_cleanup(authCurl);
    }

    return 0;
}