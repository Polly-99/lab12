#include <iostream>
#include <future>
#include <thread>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
	CURL * curl = curl_easy_init();
	std::string url;
	CURLcode res;

	if(argc < 2)
	{
		std::cout << "Enter url: ";
		std::getline(std::cin, url);
	}
	else
	{
		url = argv[1];
	}

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

		#ifdef SKIP_PEER_VERIFICATION
    			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		#endif

		#ifdef SKIP_HOSTNAME_VERIFICATION
   			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		#endif
		
		std::promise<CURLcode> promise;
		auto response = promise.get_future();

		std::thread thread([curl, &promise](){
			promise.set_value(curl_easy_perform(curl));
		});

		thread.join();
		long result = 0;

		
		if(res != CURLE_OK)
		{
			std::cout << "ERROR" <<  std::endl;
		}
		else
		{
   		 	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &result);
			std::cout << "Response - " << result << '\n';
		}
	}
 	curl_easy_cleanup(curl);
	return 0;
}
