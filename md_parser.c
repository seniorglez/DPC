#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

bool parsingTable = false;
bool codeBlockOpen = false;

//UTILS

int isTokenEmpty(char *token) {
    size_t len = strlen(token);
    size_t i;
    for (i = 0; i < len; i++) {
        if (token[i] != ' ' && token[i] != '\t' && token[i] != '\n') {
            return 0;
        }
    }
    return 1;
}

//CORE

void parseHeader(char *line, FILE *outputFile) {
    int headerLevel = 0;
    while (*line == '#') {
        headerLevel++;
        line++;
    }

    fprintf(outputFile, "<h%d>%s</h%d>\n", headerLevel, line, headerLevel);
}

void parseParagraph(char *line, FILE *outputFile) {
    fprintf(outputFile, "<p>%s</p>\n", line);
}

void parseTableLine(char *line, FILE *outputFile) {
    fprintf(outputFile, "<tr>\n");
    char *token = strtok(line, "|");
    while (token != NULL) {
        if (strlen(token) > 0 && !isTokenEmpty(token)) {
            fprintf(outputFile, "  <td>%s</td>\n", token);
        }
        token = strtok(NULL, "|");
    }
    fprintf(outputFile, "</tr>\n");
}

void parseLine(char *line, FILE *outputFile) {
     if (parsingTable && strstr(line, "|") == NULL) {
        fprintf(outputFile, "</table>\n");
        parsingTable = false;
        return;
    }
    if (strncmp(line, "```", 3) == 0) {
        if(!codeBlockOpen) {
            codeBlockOpen = true;
            fprintf(outputFile, "<pre><code>\n");
        } else {
            codeBlockOpen = false;
            fprintf(outputFile, "</pre></code>\n");
        }
        return;
    }
    
    if (line[0] == '#') {
        parseHeader(line, outputFile);
        return;
    } 
    if (strstr(line, "|") != NULL) {
        if(!parsingTable) {
           fprintf(outputFile, "<table>\n");
           parsingTable = true;
        }
        parseTableLine(line, outputFile);
    } else {
        parseParagraph(line, outputFile);
    }
}

void parseMarkdown(FILE *inputFile, FILE *outputFile) {
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        parseLine(line, outputFile);
    }
}

int main() {
    FILE *inputFile = fopen("input.md", "r");
    FILE *outputFile = fopen("output.html", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char* style = "table {\n"
                  "  width: 100%;\n"
                  "  border-collapse: collapse;\n"
                  "  font-family: Arial, sans-serif;\n"
                  "}\n"
                  "table th,  td {\n"
                  "  border: 1px solid #dddddd;\n"
                  "  padding: 8px;\n"
                  "}\n";

    fprintf(outputFile, "%s", "<html>\n<head>\n<style>\n");
    fprintf(outputFile, "%s", style);
    fprintf(outputFile, "%s", "</style>\n</head>\n<body>\n");
    parseMarkdown(inputFile, outputFile);
    fprintf(outputFile, "</body>\n</html>\n");
    fclose(inputFile);
    fclose(outputFile);

    printf("Markdown to HTML conversion completed.\n");
    return 0;
}
