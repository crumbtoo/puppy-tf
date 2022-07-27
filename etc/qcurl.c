#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define MAX_CURL_RETURN (256 * 256)

char *qcurl(const char *url)
{
	const char *useragent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Edge/18.19582";

	char *buf = calloc(MAX_CURL_RETURN + 1, 1);
	if(buf == NULL) /* malloc fail */
		return NULL;

	FILE *fp = fmemopen(buf, MAX_CURL_RETURN, "w");
	CURL *ch;

	/* init the curl session */
	ch = curl_easy_init();
	curl_global_init(CURL_GLOBAL_ALL);
 
	/* specify URL to get */
	curl_easy_setopt(ch, CURLOPT_URL, url);

	/* fix error 77 */
	curl_easy_setopt(ch, CURLOPT_SSL_VERIFYPEER, 0);
 
	/* set useragent */
	curl_easy_setopt(ch, CURLOPT_USERAGENT, useragent);

	/* write to fp (chunk in heap) */
	curl_easy_setopt(ch, CURLOPT_WRITEDATA, fp);
 
	/* call cURL */
	if(curl_easy_perform(ch) != CURLE_OK)
		return NULL;

	/* cleanup curl stuff */
	curl_easy_cleanup(ch);
	curl_global_cleanup();

	fclose(fp);

	return buf;
}

