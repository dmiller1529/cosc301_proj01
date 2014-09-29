/*
 *
 * DAN MILLER ---- submitted by myself
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/time.h>
#include <sys/resource.h>

#include "list.h"


void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function


    	struct node *current = malloc(sizeof(struct node*));
	current = current->next;
    
    char filestream[2000000];

    if (input_file == stdin) { //user input
	printf("Input a list of numbers \n");
	while(fgets(filestream, 2000000, stdin)!= NULL) {
		filestream[strlen(filestream)-1] = '\0';

		char *token = strtok(filestream, " \t\n");
    		if(token!=NULL) {
			int match = 0; //does # of chars in input match # of valid int digits?
			for(int i=0; i<strlen(token); i++) { //checks validity of each character of the input
				if(i==0 && (isdigit(token[i]) || token[i]=='-')) {
					match++;
				}
				else if(isdigit(token[i])) {
					match++;
				}
			}
			if (match == strlen(token)) {
				int i = atoi(token);
				list_append(i, &current);
			}
    		}
    
    		while (token!=NULL) {
			token = strtok(NULL," \t\n");
			if (token!=NULL) {
				int match = 0; //does # of chars in input match # of valid int digits?
				for(int i=0; i<strlen(token); i++) { //checks validity of each character of the input
					if(i==0 && (isdigit(token[i]) || token[i]=='-')) {
						match++;
					}
					else if(isdigit(token[i])) {
						match++;
					}
				}
				if (match == strlen(token)) {
					int i = atoi(token);
				        list_append(i, &current);
				}
			}
    		}
	}

	fflush(stdout);
    }

    else { //file input
        while(fgets(filestream, 2000000, input_file)!=NULL) {
		filestream[strlen(filestream)-1] = '\0';	
	
		char *token = strtok(filestream," \t\n");
    		if(token!=NULL) {
			int match = 0; //does # of chars in input match # of valid int digits?
			for (int i=0; i<strlen(token); i++) { //checks validity of each character of the input
				if(i==0 && (isdigit(token[i]) || token[i]=='-')) {
					match++;
				}
				else if(isdigit(token[i])) {
					match++;
				}
			}
			if (match == strlen(token)) {
				int i = atoi(token);
				list_append(i, &current);
			}
			if (token[0] == '#') {
				token = strtok(NULL, "\n");
			}
    		}
    
    		while(token!=NULL) {
			token = strtok(NULL," \t\n");
			if (token!=NULL) {
				int match = 0; //does # of chars in input match # of valid int digits?
				for(int i=0; i<strlen(token); i++) { //checks validity of each character of the input
					if(i==0 && (isdigit(token[i]) || token[i]=='-')) {
						match++;
					}
					else if(isdigit(token[i])) {
						match++;
					}
				}
				if (match == strlen(token)) {
					int i = atoi(token);
				        list_append(i, &current);
				}
				if (token[0] == '#') {
					token = strtok(NULL, "\n");
				}
			   
			}
    		}
	}
    }
   	list_sort(&current);
   	list_print(current);

	struct rusage usage;
	int who = RUSAGE_SELF;

	getrusage(who, &usage);
	if (getrusage(who, &usage) == -1) {
		fprintf(stderr, "getrusage error");
		exit(1);
	}
	printf("User time: %ld.%08lds\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
	printf("System time: %ld.%08lds\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
	
	list_clear(current);
	free(current);	
}


void usage(char *program) {
	fprintf(stderr, "usage: %s [<datafile>]\n", program);
    	exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
