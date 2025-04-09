#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

void log_msg(int priority, const char *message) {
	openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
	syslog(priority, "%s", message);
	closelog();
}

int main(int argc, char *argv[]){

	if (argc != 3) {
		fprintf(stderr, "ERROR! Please include file path and text pattern.\n");
		log_msg(LOG_ERR, "ERROR! Please include file path and text pattern.");
		return 1;
	}
	
	char *writefile = argv[1];
	char *writestr = argv[2];
	
	FILE *file = fopen(writefile,"w");
	if(file == NULL) {
		fprintf(stderr, "ERROR! Unable to open file %s.\n", writefile);
		char err_message[1024];
		sprintf(err_message, "ERROR! Unable to open file %s", writefile);
		log_msg(LOG_ERR, err_message);
		fclose(file);
		return 1;
	}
	
	if (fprintf(file, "%s", writestr) < 0) {
		fprintf(stderr, "ERROR! Could not write to file %s\n", writefile);
		char err_message[1024];
		sprintf(err_message, "ERROR! Could not write to file %s", writefile);
				log_msg(LOG_ERR, err_message);
		fclose(file);
		return 1;
	}
	
	char log_msg_str[1024];
	sprintf(log_msg_str, "Writing \"%s\" to %s", writestr, writefile);
	log_msg(LOG_DEBUG, log_msg_str);
	
	fclose(file);
	
	fprintf("File %s created successfully with inputted string.\n", writefile);
	return 0;
}
	

