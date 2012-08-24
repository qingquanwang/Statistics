#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
/*
 * For frequency sampling, please use with a memory allocation lib
 */
#ifndef USE_ZMALLOC
#define zmalloc malloc
#define zfree free
#endif

int weighted = 0; // uniform weighted
int shuffled = 0; // no need to shuffled
FILE* f; //fd of the datafile
char* datafile=NULL;
int k=0;
char buffer[1024];

#define LRU_CLOCK_RESOLUTION 10
#define LRU_CLOCK_MAX ((1<<21)-1)


unsigned seed(){
    return (time(NULL)/LRU_CLOCK_RESOLUTION) & LRU_CLOCK_MAX;
}
/*
 * If k > total item nums in the datafile
 * return all items in the datafile
 */
void parseOptions(int argc, char** argv){
	int i;
    int lastarg;
    for (i = 1; i < argc; i++) {
        lastarg = (i == (argc-1));
        if (!strcmp(argv[i],"-f")) {
            if (lastarg) goto invalid;
            datafile = strdup(argv[++i]);
        } else if (!strcmp(argv[i],"-k")) {
            if (lastarg) goto invalid;
			k = atoi(argv[++i]);
		} else {
			goto invalid;
		}
	}
	return;
invalid:
	printf("sample -f datafile -k sample_num\n");
	exit(1);
}
void reservoir(char** results,int k){
	int i,j,m;
	int finish=0;
	srandom(seed());
	for(i=1;i<=k;++i){
		if(fscanf(f,"%s\n",buffer)!=EOF){
			results[i]=strdup(buffer);
		}
		else{
			finish=1;
			break;
		}
	}
	if(finish){
		--i;
		for(j=1;j<=i;++j){
			printf("%s\n",results[j]);
			free(results[j]);
		}
		return;
	}
	while(fscanf(f,"%s\n",buffer)!=EOF){
		++i;
		m = rand()%i + 1;
		if ( m<=k ){
			free(results[m]);
			results[m] = strdup(buffer);
		}
	}
	for(j=1;j<=k;++j){
		printf("%s\n",results[j]);
		free(results[j]);
	}
	return;
}
int
main(int argc, char** argv){
	parseOptions(argc,argv);
	if(datafile==NULL)goto usage;
	if(k==0){
		free(datafile);
		goto usage;
	}
	f = fopen(datafile,"r");
	if(f==NULL)goto fileError;
	char** results = malloc(sizeof(char*)*(k+1));
	reservoir(results,k);
	free(results);
	fclose(f);
	return 0;
usage:
	printf("sample -f datafile -k sample_num \n");
	exit(1);
fileError:
	printf("%s not existed\n",datafile);
	exit(1);
}
