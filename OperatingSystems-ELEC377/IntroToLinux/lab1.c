/*+
 * lab1.c - Print process information
-*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <strings.h>
#include <ctype.h>

int isProcessDir(const struct dirent*d){

	int j;
	for (j = 0; j< strlen(d->d_name); j++){
		if (!isdigit(d->d_name[j])) {
			return 0; 
		}
	}
	//printf(d->d_name);
	//printf("\n");	
	return 1;
}

char* delLast(char* string){
	int i = 0;
	while(string[i] != '\0'){
		i++;
	}
	string[i - 1] = '\0';
	return string;
}

char* firstChar(char* input){
	char* starting = input;
	while (*starting != '\t'){
		starting++;
	}
	starting++;
	return starting;
}

char* deleteAfter(char* input){
	int i = 0;
	while(input[i] != '\t') {
		i++;
	}
	input[i] = '\0';
	return input; 
}

int main(){
	FILE *outfile = fopen("output.txt" , "w");
	fprintf(outfile, "#   Name            Status        User  Group \n");
	struct dirent ** namelist;
	int n;

	n = scandir("/proc", &namelist, isProcessDir, NULL);
	int i;
	for(i = 0; i < n; i++){

		char str[NAME_MAX];
		char proc[] = "/proc/";
	 	char stat[] = "/status";
		sprintf(str, "%s%s%s" , proc, namelist[i]->d_name, stat);
		FILE *fp = fopen(str, "r");
		
		char trash[NAME_MAX];			
		char name[NAME_MAX];
		char status[NAME_MAX];
		char user[NAME_MAX];
		char group[NAME_MAX];
		fgets(name, NAME_MAX, (FILE*)fp);
		fgets(status, NAME_MAX, (FILE*)fp);
		fgets(trash, NAME_MAX, (FILE*)fp);
		fgets(trash, NAME_MAX, (FILE*)fp);
		fgets(trash, NAME_MAX, (FILE*)fp);
		fgets(trash, NAME_MAX, (FILE*)fp);
		fgets(user, NAME_MAX, (FILE*)fp);
		fgets(group, NAME_MAX, (FILE*)fp);
		delLast(name);
		delLast(status);
		firstChar(group);
		
		firstChar(user);		
		fprintf(outfile, "%-4d%-16s%-14s%-6.4s%-6.4s\n",i ,firstChar(name), firstChar(status), deleteAfter(firstChar(user)),  deleteAfter(firstChar(group)));
	}

	return 1;

}

