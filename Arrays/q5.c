#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* NUMBER_WORDS[]={
    "ZERO","ONE","TWO","THREE","FOUR","FIVE","SIX",
    "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "TWELVE"
};

int compare_chars(const void* a,const void* b){
    return (*(const char*)a-*(const char*)b);
}

int main(){
    char input_buffer[1000]={0};
    char letters[2000]={0};
    int letter_count=0;

    if (fgets(input_buffer,sizeof(input_buffer),stdin)==NULL){
        return 0;
    }

    size_t len=strlen(input_buffer);
    if (len>0 && input_buffer[len-1]=='\n'){
        input_buffer[len-1]='\0';
    }

    char tokensize_buffer[1000];
    strcpy(tokensize_buffer,input_buffer);

    char* token=strtok(tokensize_buffer," ");
    while (token!=NULL){
        int val=atoi(token);
        if (val==999){
            break;
        }

        if (val>=0 && val<=12){
            const char* word=NUMBER_WORDS[val];
            for (int i=0;word[i]!='\0';i++){
                letters[letter_count++]=word[i];
            }
        }
        token=strtok(NULL," ");
    }
    qsort(letters,letter_count,sizeof(char),compare_chars);
    letters[letter_count]='\0';
    printf("%s\n",letters);
    return 0;
}
