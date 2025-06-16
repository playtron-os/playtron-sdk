#include <playtron/sdk/os.hxx>
#include <playtron/sdk/pact.hxx>

#include <iostream>
#include <format>

#include <nlohmann/json.hpp>
#include <curl/curl.h>

size_t curl_write_cb(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t contentsLength = size * nmemb;
    try
    {
        s->append((char*)contents, contentsLength);
    }
    catch(std::bad_alloc &e)
    {
        return 0;
    }

    return contentsLength;
}

int main()
{
    try {
        std::cout << "Checking if on a Playtron device..." << std::endl;
        if (playtron::sdk::os::is_playtron())
        {
            std::cout << "Running on Playtron!" << std::endl;
        }
        else
        {
            std::cout << "Not running on Playtron!" << std::endl;
            return 0;
        }

        std::cout << "Creating attestation client..." << std::endl;
        auto attestationClient = playtron::sdk::pact::AttestationClient();

        std::cout << "Creating attestation session..." << std::endl;
        playtron::sdk::pact::SessionInfo sessionInfo = attestationClient.create_session();

        std::cout << "Session ID: " << sessionInfo.sessionId << std::endl;
        std::cout << "Nonce: " << sessionInfo.nonce << std::endl;

        std::cout << "Getting quote from TPM..." << std::endl;
        std::string quote = attestationClient.get_quote(sessionInfo.nonce);
        std::cout << "Quote: " << quote << std::endl;

        std::cout << "Sending attestation request..." << std::endl;

        // Construct the attestation request
        curl_global_init(CURL_GLOBAL_ALL);
        CURL* client = curl_easy_init();

        const char* baseUrl = std::getenv("PACT_ATTESTATION_URL");
        std::string url = std::format("{}/{}", baseUrl, "api/v1/session/attest");

        curl_easy_setopt(client, CURLOPT_URL, url.c_str());
        curl_easy_setopt(client, CURLOPT_POSTFIELDS, quote.c_str());

        struct curl_slist *headers=NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string sessionIdHeader = std::format("X-Session-Id: {}", sessionInfo.sessionId);
        headers = curl_slist_append(headers, sessionIdHeader.c_str());
        curl_easy_setopt(client, CURLOPT_HTTPHEADER, headers);

        std::string responseBody;
        curl_easy_setopt(client, CURLOPT_WRITEFUNCTION, curl_write_cb);
        curl_easy_setopt(client, CURLOPT_WRITEDATA, &responseBody);
        curl_easy_setopt(client, CURLOPT_SSL_OPTIONS, (long)CURLSSLOPT_NATIVE_CA);

        // Send the attestation request
        CURLcode res = curl_easy_perform(client);
        curl_slist_free_all(headers);
        if (res != CURLE_OK)
        {
            long status_code = 0;
            curl_easy_getinfo (client, CURLINFO_RESPONSE_CODE, &status_code);
            std::cout << "Attestation request failed with status code: " << status_code << std::endl;
        }

        std::cout << "Response: " << responseBody << std::endl;

        curl_easy_cleanup(client);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }

    return 0;
}