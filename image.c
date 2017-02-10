//compile with scanner.c and ppm.c
//Code for manipulating ppm images and writing them to files or standard output
//Authored by Hank King
//for CS100
//      4/3/2015
//After compiling, type ./image followed by any combination of these commands:
//
//-i or --invert to invert the colors
//-s or --swap to flip horizontally
//-f or --to flip vertically
//-r or --rotate to rotate 90 degrees clockwise
//-o or --output followed by an output file name (ending in .ppm) if you want
//to write to a file instead of stdout 
//
// ***all output goes to stdout if an output file is not specified***
//
//The last argument in your command should be the name of the ppm file you 
//want to manipulate.
//
//if the only command line arguments are "image" and the ppm file to be manipulated,
//the text found in the ppm file will be printed to stdout.
//
//simply type image or ./image to display instructions on using a file.


//The method used to accomplish this:
//1) store the data in a ppm picture file in a data structure called a ppPic
//2) store the output file name if there is one
//3) change the ppmPic structure to reflect the manipulations specified by
//   the commands given, in order
//4) write the data in the modified ppmPic structure to stdout or the specified 
//   output file.

#include "image.h"


int main(int argc,char **argv)
    {
    if (userInstructions(argc) == 1)  //calls the user instructions function, wich prints instructions
        return 0;                   //if only one command line argument is entered.
                                    //ends the program if only one command line argument was
    char *outputFileName;           //entered
    int i;
    int hasOutputFile = 0;
    
    for (i = 1; i < argc; i++)  //This loop walks the command line arguments looking for
        {                       // -o or --output. If it finds them, it assigns
                                //the next argument to outputFileName.
        if (strcmp(argv[i],"-o") == 0 || strcmp(argv[i],"--output") == 0)
            {
            outputFileName = argv[i + 1];
            hasOutputFile = 1;
            }
        }

    ppmPic *a = newppmPic();                              //a will be the ppmPic structure we manipulate.
    a = readppmPic(argv[argc - 1]);         //reads in a ppm picture to a
    printf("picture was successfully read\n");
   
    a = handleppmPic(a,argc,argv,outputFileName);    //applies manipulations to picture

    printf("picture was successfully handled\n");
    
    if (hasOutputFile == 0)             //write to stdout if no output file was specified
        writeppmPic(a,stdout);
    else                                //write to specified file if one was specified
        {
        FILE *fp = fopen(outputFileName,"w");
        writeppmPic(a,fp);
        fclose(fp);    
        }
    free(a);                            
    return 0;
    }







//This function takes in a ppmPic structure, the command line arguments, the number
//of command line arguments, and the outputFileName. It then;
//1) applies the manipulations specified by each command line argument to the picture
//   (in order) by modifying the ppmPic structure
//2) prints error messages for all unexpected command line arguments
//3) returns the modified ppmPic structure.
ppmPic *
handleppmPic(ppmPic *a,int argc,char **argv,char *outputFileName)
    {
    int i;
    for (i = 1; i < argc - 1; i++)          //This for loop walks the command line arguments
        {                                   //looking for commands and manipulates
                                            //the picture accordingly (doesn't print)
        //invert
        if (strcmp(argv[i],"-i") == 0 || strcmp(argv[i],"--invert") == 0)
            a = invertppmPic(a);
        //flip
        else if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--flip") == 0)
            a = flipppmPic(a);
        //swap
        else if (strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--swap") == 0)
            a = swapppmPic(a);
        //rotate
        else if (strcmp(argv[i],"-r") == 0 || strcmp(argv[i],"--rotate") == 0)
            a = rotateppmPic(a);
        //This else if statement handles erroneous input
        else if (strcmp(argv[i],"-o") != 0 && strcmp(argv[i],"--output") != 0 && strcmp(argv[i],outputFileName) != 0)
            {
            //Once the program reaches this point, argv[i] is NOT one of
            //the expected commands.
            fprintf(stderr,"Error: Invalid command line argument: %s\n",argv[i]);
            }
        }
    return a;
    }

//This function takes in an integer representing the number of command
//line arguments and prints a short message on how to use the program
//if the user simply enters "image" or "./image" (if argc is equal to 1)
//it returns 1 if argc is equal to 1
int
userInstructions(int argc)
    {
    if (argc == 1)
        {
        printf("-----------------------------------------------------------\n");
        printf("This program is used to manipulate ppm pictures and write their contents to files or standard output.\n");
        printf("Type ./image followed by any combination of these commands:\n");
        printf("-i or --invert to invert\n");
        printf("-s or --swap to flip horizontally\n");
        printf("-f or --flip to flip vertically\n");
        printf("-r or --rotate to rotate 90 degrees clockwise\n");
        printf("-o or --output followed by an output file name (ending in .ppm) if you want to write to a file instead of stdout\n");
        printf("The last argument in your command should be the name of the ppm file you want to manipulate.\n");
        }
    return argc;
    }
