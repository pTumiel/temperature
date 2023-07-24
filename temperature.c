#include <stdio.h>
#include <errno.h>
#include <glob.h>
#include <string.h>
#include <stdlib.h>

char* concat(const char *s1, const char *s2);

int main(void) {
    glob_t paths;
    FILE *thermal;
    int temperature;
    glob("/sys/class/thermal/thermal_zone*",GLOB_TILDE,NULL,&paths);
    for(unsigned int i=0;i<paths.gl_pathc;i++){
    	thermal=fopen(concat(paths.gl_pathv[i],"/temp"),"r");
        if(thermal==NULL){
		perror("Failed");
		return 1;
	}
	if(fscanf(thermal,"%d",&temperature) !=1){
		perror("Failed to get temp");
		fclose(thermal);
	}
    	printf("========\n");
	printf("|      |\n");

    	printf("| temp |\n");
	printf("|  %i  |\n",temperature/1000);
    	printf("|      |\n");
	printf("|      |\n");
    	printf("========\n");
    }
    fclose(thermal);
}

char* concat(const char *s1, const char *s2) {
    size_t len = strlen(s1) + strlen(s2) + 1;

    char *result = malloc(len * sizeof(char));

    if (result == NULL) {
        printf("Failed to allocate memory\n");
        exit(1); 
    }

    strcpy(result, s1);

    strcat(result, s2);

    return result;
}
