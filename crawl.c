#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, struct MemoryStruct *userp) {
    size_t realsize = size * nmemb;
    userp->memory = realloc(userp->memory, userp->size + realsize + 1);
    if (userp->memory == NULL) {
        printf("Not enough memory!\n");
        return 0;
    }
    memcpy(&(userp->memory[userp->size]), contents, realsize);
    userp->size += realsize;
    userp->memory[userp->size] = '\0';  // Null-terminate the string
    return realsize;
}

void parseHTML(const char *html) {
    xmlDoc *doc = xmlReadMemory(html, strlen(html), NULL, NULL, 0);
    if (doc == NULL) {
        printf("Failed to parse HTML\n");
        return;
    }

    // Example: Find the title
    xmlNode *root_element = xmlDocGetRootElement(doc);
    for (xmlNode *node = root_element; node; node = node->next) {
        if (node->type == XML_ELEMENT_NODE && strcmp((const char *)node->name, "title") == 0) {
            printf("Title: %s\n", xmlNodeGetContent(node));
        }
    }
    xmlFreeDoc(doc);
}

int main(void) {
    CURL *curl;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);  // initial allocation
    chunk.size = 0;            // no data at this point

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://muhammad-wasay.vercel.app"); // Replace with the URL you want to scrape
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0"); // Some websites require a user agent

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("HTML retrieved:\n%s\n", chunk.memory);
            parseHTML(chunk.memory); // Call your HTML parser
        }

        curl_easy_cleanup(curl);
    }

    // Save HTML to a file
    FILE *file = fopen("output.html", "w");
    if (file) {
        fputs(chunk.memory, file);
        fclose(file);
    }

    free(chunk.memory);
    curl_global_cleanup();
    return 0;
}
