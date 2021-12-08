#include <stdio.h>
#include "ffftHeader.h"


static char *programName = "<unset>";

static void add(compNum *a, compNum *b, compNum *c){
    c -> imaginary = a.imaginary + b.imaginary;
    c -> real = a.real + b.real;
}

static void multiply (compNum *a, compNum *b, compNum *c){
    compNum res;
    c -> real = a.real * b.real - a.imaginary * b.imaginary;
    c -> imaginary = a.real * b.imaginary + a.imaginary * b.real;
    return res;
}


static void createChild(dependencies * dep){
    //pipe 1 parent -> child
    //pipe 2 child -> parent
    int pipe1[2],pipe2[2];
    if((pipe(pipe1)) == -1 || (pipe(pipe2)) == -1){
        fprintf(stderr, "failed at creating pipes in %s",programName);
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
        exit(EXIT_FAILURE);
    }
    dep -> pid = fork();
    switch (dep -> pid){
        case 0: //case child
            close(pipe1[1]);
            close(pipe2[0]);

            if((dup2(pipe1[0],STDIN_FILENO)) == -1){
                fprintf(stderr,"failed at dup %s",programName);
                close(pipe1[0]);
                close(pipe2[1]);
                exit(EXIT_FAILURE);
            }
            close(pipe1[0]);
            if((dup2(pipe2[1], STDOUT_FILENO)) == -1){
                fprintf(stderr,"failed at dup in %s",programName);
                close(pipe2[1]);
                exit(EXIT_FAILURE);
            }
            close(pipe2[1]);

            if(execlp(programName,programName,NULL) == -1){
                fprintf(stderr,"failed at excelp in %s",programName);
                exit(EXIT_FAILURE);
            }
            assert(0);
        case -1: //case error
            fprintf(stderr,"fork failed in %s",programName);
            exit(EXIT_FAILURE);
            break;
        default:
            close(pipe1[0]);
            close(pipe2[1]);
            dep -> write = pipe1[1]; //saving fd to dep.write
            dep -> read = pipe2[0]; //saving fd to dep.read

    }
}

static void butterfly(char input[], int size){
    compNum even;
    compNum odd;
    compNum res;
    compNum result[size];
    for(int i = 0; i < size/2; i += 2){
        convert(even,input[i]) * convert(odd,input[i+1]); //TODO: finish up here 
    }
}
//convert string to complex number.
static void convert(compNum *c, char *input){ //todo untested maybe wrong 
    char *tmp;
    c->real = strtof(input, &tmp);
    if(tmp == ' '){
        c->imaginary = strtof(input,&tmp);
    }
    else{
        c -> imaginary = 0;
    }
}

int main(int argc, char *argv[])
{
    argumentParsing(argc, argv);
    
    programName = argv[0];

    char *line1 = NULL;
    char *line2 = NULL;
    size_t n1 = 0;
    size_t n2 = 0;
    ssize_t length1 = 0;
    ssize_t length2 = 0;

    
    length1 = getline(&line1, &n1, stdin);
    if (length1 == -1) //No line was read, something went wrong in parent process.
    { 
        fprintf(stderr, "Failure in %s",programName);
        //free(line1);
        //free(line2);
        exit(EXIT_FAILURE);
    }


    length2 = getline(&line2, &n2, stdin);
    if (length2 == -1) //only one line was read
    { 
        fprintf(stdout, "%f", strtof(line1, NULL));
        free(line1);
        free(line2);
        exit(EXIT_SUCCESS);
    }


    dependencies e_dep,o_dep;
    createChild(&e_dep);
    createChild(&o_dep);
    

    FILE * fEwr = fdopen(e_dep.write,"w");
    FILE * fOwr = fdopen(o_dep.write,"w");

    
    fprintf(fEwr,"%s",line1);
    fprintf(fOwr,"%s",line2);

    int count = 2; // We want to know how many floats we are writing to our children.
    while(1){
        if((getline(&line1,&n1,stdin)) == EOF){
            break;
        }
        fprintf(fEwr,"%s",line1);

        if((getline(&line2, &n2,stdin)) == EOF){
            free(line1);
            free(line2);
            fclose(fOwr);
            fclose(fEwr);
            usage(programName);
        }
        fprintf(fOwr,"%s",line2);
        count += 2;
    }

    fflush(fEwr);
    fflush(fOwr);

    fclose(fEwr);
    fclose(fOwr);
    
    int status;
    waitpid(e_dep.pid,&status,0);
    waitpid(o_dep.pid,&status,0);


    FILE *fErd = fdopen(e_dep.read,"r");
    FILE *fOrd = fdopen(o_dep.read,"r");
    char readChars[count]; // we are reading the same number of chars we put into our children, therefore we can use count from before.
    for(int i = 0; i < count; i++){ //todo untested maybe wrong
        if(getline(&line1, &n1, fErd) == EOF){
            break;
        }
        line1 = realloc(line1,strlen(line1) + 1);
        line1[strlen(line1) -1 ] = '\n';
        readChars[i] = *line1;
    }



    free(line1);
    free(line2);
    fflush(fErd);
    fflush(fOrd);
    fflush(stdout);
    fflush(stdout);
    fclose(fErd);
    fclose(fOrd);

}