#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "http.h"
#include "db_manager.h"
#include "json.h"
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <windows.h>

int http_getPath(const char * const request, char * pathBuf, int maxPathBuf);
void server_homepage(socket_t * client);
void server_notFound(socket_t * client);
http_request_t http_request_parse(const char * const request);
void server_students(socket_t * client, http_request_t * req);
void server_file_parse(socket_t * client);
void parse_text(char *text);
char * info_to_xml(char * name, char * group, char * var);
int main() {
    lib_init();
    socket_t * server = socket_new();
    socket_bind(server, 5000);
    socket_listen(server);
	
   char buf[10000];
    char pathBuf[256];
    socket_t * client = NULL;

    while(1) {
		client = socket_accept(server);
        socket_read(client, buf, sizeof(buf));
		if (strlen(buf) == 0)
			continue;
        printf(">> Got request:\n%s\n", buf);

        http_getPath(buf, pathBuf, sizeof(pathBuf));

        http_request_t request = http_request_parse(buf);

        if (strcmp(request.uri, "/") == 0) {
            server_homepage(client);
        } else if (strcmp(request.uri, "/database") == 0) {
            server_students(client, &request);
        }  
        else if (strcmp(request.uri, "/info") == 0) {
            server_info(client);
        }
        else if (strcmp(request.uri, "/filename") == 0) {
            server_file_parse(client);
        }
        else {
            server_notFound(client);
        }
		socket_free(client);
    }
    socket_free(server);
    lib_free();
    return 0;
}

int http_getPath(const char * const request, char * pathBuf, int maxPathBuf) {
    // get method
    char method[8];
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(method, request, methodLen);
    method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(pathBuf, uriStartPtr, uriLen);
    pathBuf[uriLen] = '\0';
    return uriLen;
}

void server_homepage(socket_t * client) {
    const char pageText[1024] = "<!DOCTYPE html> <html> <head> <title>Page Title</title> </head> <body> <h1>My First Heading</h1> <p> <a href=\"http://127.0.0.1:5000/database\">Show persons</a></p> </body> </html>";
    char homeBuf[1024];
    sprintf(homeBuf,
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
        "\n%s", strlen(pageText), pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

void server_notFound(socket_t * client) {
    char homeBuf[1024];
	
    const char * pageText = "404 Page Not Found!";
    sprintf(homeBuf,
        "HTTP/1.1 404 \n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
        "\n%s", strlen(pageText), pageText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

http_request_t
http_request_parse(const char * const request) {
    http_request_t req;
    // get method
    ptrdiff_t methodLen = strstr(request, " ") - request;  // find first whitespace
    memcpy(req.method, request, methodLen);
    req.method[methodLen] = '\0';
    // get uri
    const char * uriStartPtr = request + strlen(req.method) + 1;
    const char * uriEndPtr = strstr(uriStartPtr, " ");  // find second whitespace
    ptrdiff_t uriLen = uriEndPtr - uriStartPtr;
    memcpy(req.uri, uriStartPtr, uriLen);
    req.uri[uriLen] = '\0';
    return req;
}

void server_students(socket_t * client, http_request_t * req) {
    char strbuf[10240];
    if (strcmp(req->method, "GET") == 0) {
		char allStudentsJson[10240] = "";
		char buf[1000];
        list_t persons = list_new();
		FILE * file = fopen("Untitled1.xml", "r");
		while(fgets(buf, 1000, file) != NULL)
		{
			strcat(allStudentsJson, buf);
			puts(buf);
		}
        db_t * db = db_new("worker.db");
        
        
        for(int i = 1; i < 6; i++){
            struct person * pers = malloc(sizeof(struct person));
            pers = db_getWorkerById(db, i);
            list_add(persons, pers, list_size(persons));
        }
        
        char xml_buf[10000];
        strcpy(xml_buf, list_to_xml_string(persons));
		//list_to_xml(persons);
        puts(xml_buf);
        sprintf(strbuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/xml\n"
            "Content-Length: %u\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(xml_buf), xml_buf);
		fclose(file);
	}
    socket_write_string(client, strbuf);
    socket_close(client);
}

void server_info(socket_t * client)
{
	char homeBuf[1024];
	const char * name = "Stas Samokhvalenko";
	const char * group = "KP-52";
	const char * variant = "26";
	char * text = info_to_xml(name, group, variant);
    sprintf(homeBuf,
        "HTTP/1.1 404 \n"
        "Content-Type: text/xml\n"
        "Content-Length: %u\n"
        "\n%s", strlen(text), text);
    socket_write_string(client, homeBuf);
    socket_close(client);
	free(text);
}

void server_file_parse(socket_t * client){
        char html_doc[15000];
    char * filename = {"C:\\Users\\User\\Desktop\\samokh-52\\courses\\prog_base_2\\tests\\test_2\\Server_kr_app\\files\\filename.txt"};
    if(file_exists(filename)){
    char text[10000];
    char buf[1000];
    char ContentToReceive[10000];
    memset(ContentToReceive, '\0', 10000);
    FILE *f = fopen(filename, "r");
    char *word;
    int i = 0, j = 0;
    char html_text[15000] ="<!DOCTYPE html> <html> <head>List</head> <body><ol type=\"1\">";
    while(fgets(buf, 1000, f) != NULL)
		{
			strcat(ContentToReceive, buf);
		}
    word = strtok(ContentToReceive, " ");
    while(word != NULL){
        /*j = 0;
        while(ContentToReceive[i] != ' '){
            word[j] = ContentToReceive[i];
            j++;
            i++;
        }*/
        
        strcat(html_text, "<li>");
        strcat(html_text, word);
        strcat(html_text, "</li>");
        puts(word);
        word = strtok(NULL, " ");
    }
    puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    strcat(html_text, "</ol>");
    strcat(html_text, "</body> </html>");
    sprintf(html_doc,
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
    "\n%s", strlen(html_text), html_text);
    
    }
    else if(!file_exists(filename)){
        char html_text[15000] ="<!DOCTYPE html> <html> <head>File does`not exist</head> <body><ol type=\"1\">";
        
        strcat(html_text, "</body> </html>");
        char html_doc[15000];
        sprintf(html_doc,
        "HTTP/1.1 200 OK\n"
        "Content-Type: text/html\n"
        "Content-Length: %u\n"
        "\n%s", strlen(html_text), html_text);
    }
    socket_write_string(client, html_doc);
    socket_close(client);
    
}