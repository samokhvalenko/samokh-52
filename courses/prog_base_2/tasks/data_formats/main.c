#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

struct work{
    char shop_name[15];
};

struct person{
    char name[15];
    char surname[15];
    char birthdate[11];
    unsigned age;
    float experience_age;
    struct work work;
};

int main() {
    struct person persons[3];
	char line[100];
	char text[10000] = "";
	FILE * fr = fopen("Untitled1.xml", "r");
	while(fgets(line, 100, fr)){
        strcat(text, line);
	}

	xmlDoc * xDoc;
	xDoc = xmlReadMemory(text, strlen(text), NULL, NULL, 0);
    if(NULL == xDoc){
        printf("error");
        return 0;
    }

    xmlNode * xRootEl;
    int i = 0;
    xRootEl = xmlDocGetRootElement(xDoc);
    for(xmlNode * xCur = xRootEl->children; NULL != xCur ;xCur = xCur->next){
        for(xmlNode * xJ = xCur->children; NULL != xJ ;xJ = xJ->next){
            if(XML_ELEMENT_NODE == xJ->type){
                const char * content = xmlNodeGetContent(xJ);
                if(strcmp(xJ->name, "name") == 0){
                    strcpy(persons[i].name, content);
                }
                if(strcmp(xJ->name, "surname") == 0){
                    strcpy(persons[i].surname, content);
                }
                if(strcmp(xJ->name, "birthdate") == 0){
                    strcpy(persons[i].birthdate, content);
                }
                if(strcmp(xJ->name, "age") == 0){
                    persons[i].age = atoi(content);
                }
                if(strcmp(xJ->name, "experience_age") == 0){
                    persons[i].experience_age = atof(content);
                }
                if(strcmp(xJ->name, "work") == 0){
                    xmlNode * xWork = xJ;
                    xmlNode * xShopname = xWork->children->next;
                    char * shop = xmlNodeGetContent(xShopname);
                    strcpy(persons[i].work.shop_name, shop);
                    i++;
                }
            }
        }
    }
    for(i = 0; i < 3; i++){
        printf("Name: %s\nSurname: %s\nBirthdate: %s\nAge: %i\nExperience age: %.1f\n   Work: %s\n\n",
                persons[i].name, persons[i].surname, persons[i].birthdate, persons[i].age, persons[i].experience_age,  persons[i].work.shop_name);
    }
}
