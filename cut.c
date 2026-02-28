#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    char delimeter = '\t';
    int fields[100];
    int num_fields = 0;
    int  count = argc;
    for (int i = 1; i < count; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--delimiter") == 0) {
            if (i  < count-1) {
		i++;
                delimeter = argv[i][0];
            } else {
                printf("Error:missing delimeter");
                return 1;
            }
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--fields") == 0) {
            if (i < count -1) {
		i++;
                char *p = argv[i];
		while (*p) {
        		int val = 0;
	       		while (*p >= '0' && *p <= '9') {
           			 val = (val * 10) + (*p - '0');
         			 p++; 
		        }
		        fields[num_fields] = val;
       		        num_fields++;
	        	if (*p == ',') {
        		    p++;
        	}
    		}


            } else {
                printf("Error:missing field");
                return 1;
            }
	}
    }

    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char *tokens[150];
        int toks = 0;
        tokens[toks] = line;
	toks++;

        for (int k = 0; line[k] != '\0'; k++) {
            if (line[k] == delimeter) {
                line[k] = '\0';
                tokens[toks] = &line[k + 1];
		toks++;
            }
        }

        bool first = true;
        for (int j = 0; j < num_fields; j++) {
            int idx = fields[j] - 1; 
            if (idx >= 0 && idx < toks) {
                if (!first) {
                    printf("%c", delimeter);
                }
                printf("%s", tokens[idx]);
                first = 0;
            }
        }
        printf("\n");
    }

    return 0;
}
