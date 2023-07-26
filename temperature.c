#include <stdio.h>
#include <errno.h>
#include <glob.h>
#include <string.h>
#include <stdlib.h>

char* concat(const char *s1, const char *s2);
void layout(int columns,int temps[columns]);

int main(void) {
    glob_t paths;
    FILE *thermal;
    int temperature;


    FILE* fp;
    char buffer[128];
    // Open the file for cpu name
    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL) {
        printf("Could not open /proc/cpuinfo\n");
        return 1;
    }
    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        // If the line starts with "model name", print it
        if (strncmp(buffer, "model name", 10) == 0) {
            printf("%s", buffer);
            break;
        }
    }
    // Close the file
    fclose(fp);


    //read temp of cpu
    glob("/sys/class/thermal/thermal_zone*",GLOB_TILDE,NULL,&paths);
    int temps[paths.gl_pathc];

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
        temps[i]=temperature;
    }
    fclose(thermal);
    
    layout(paths.gl_pathc,temps);
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

void layout(int columns,int temps[columns]){
	for(int i=0;i<columns;i++){
		printf("============");
	}
	printf("=\n");

    for(int b=0;b<columns;b++){
        printf("|temp zone %i",b);
    }
    printf("|\n");

	
	for(int b=0;b<columns;b++){
                printf("|    %iC    ",temps[b]/1000);
        }
        printf("|\n");


    for(int b=0;b<columns;b++){
        printf("|           ");
    }
    printf("|\n");

	


	for(int i=0;i<columns;i++){
        	printf("============");
        }
	printf("=\n");

}


