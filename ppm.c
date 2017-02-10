//Compile with scanner.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ppm.h"
#include "scanner.h"


//This function  returns a new (dynamically allocated) empty ppmPic structure
ppmPic *
newppmPic(void)
    {
    ppmPic *p = malloc(sizeof(ppmPic));
    p->rows = 0;
    p->cols = 0;
    p->colors = 0;
    p->pixels = 0;
    return p;
    }

//This function takes in a file pointer,
//reads in a ppmPic structure from the file
//and returns a ppmPic structure
ppmPic *
readppmPic(char *file)
    {
    ppmPic *a = malloc(sizeof(ppmPic));

    FILE *fp = fopen(file,"r");
    if (fp == 0)
        {
        fprintf(stderr,"file data could not be opened for reading\n");
        exit(1);
        }
    (void) readToken(fp);              //read and IGNORE P3
    a->cols = readInt(fp);
    a->rows = readInt(fp);
    a->colors = readInt(fp);

    a->pixels = malloc(sizeof(Pixel *) * a->rows);  //These four lines dynamically allocate
    int i;                                          //the 2-dimensional array of pixels
    for(i = 0; i < a->rows; i++)                    //called pixels
    a->pixels[i] = malloc(sizeof(Pixel) * a->cols); //
    
    //This for loop reads each row of pixels, one at a time
    int j;
    for (j = 0; j < a->rows; j++)
        {
        //reads one row (row number is j)
        i = 0;
        //i is the column number
        //this while loop reads a single row of pixels, one at a time.
        while(i < a->cols)
            {
            a->pixels[j][i].red = readInt(fp);
            a->pixels[j][i].green = readInt(fp);
            a->pixels[j][i].blue = readInt(fp);
            i++;
            }
        }
    return a;
    }


//This function takes in a ppmPic structure and a file pointer
//and prints the ppmPic represented by the structure
//to the file that corresponds to the file pointer.
void 
writeppmPic(ppmPic *a,FILE *fp)
    {
    if (fp == 0)
        {
        fprintf(stderr,"file data could not be opened for reading\n");
        exit(1);
        }
    fprintf(fp,"P3\n");
    fprintf(fp,"%d  ",a->cols);
    fprintf(fp,"%d\n",a->rows);
    fprintf(fp,"%d\n",a->colors);
    int j;                         //j is the row number
    for (j = 0; j < a->rows; j++)  //This for loop prints each row of pixels one at a time
        {
        int i = 0;                 //i is the column number
        while(i < a->cols)
            {
            fprintf(fp,"%d ",a->pixels[j][i].red);   //This while loop prints one row of pixels.
            fprintf(fp,"%d ",a->pixels[j][i].green);
            fprintf(fp,"%d",a->pixels[j][i].blue);
            fprintf(fp,"    ");
            i++;
            }
        
        fprintf(fp,"\n");
        }
    return;
    }



//This function takes in a ppmPic structure
//and returns a ppmPic structure representing an
//inverted version of the original picture (inverts the colors)
ppmPic *
invertppmPic(ppmPic *a)
    {
    int i;
    int j;                                  //j is the row number
    for (j = 0; j < a->rows; j++)
        {                                   //This for loop inverts each row one at a time
        i = 0;
                                            //i is the column number
        while(i < a->cols)
            {                               //This while loop inverts one row (row j)
            a->pixels[j][i].red = a->colors - a->pixels[j][i].red;
            a->pixels[j][i].green = a->colors - a->pixels[j][i].green;
            a->pixels[j][i].blue = a->colors - a->pixels[j][i].blue;
            i++;
            }
        }
    return a;
    }

//This function takes in a ppmPic structure
//and returns a ppmPic structure representing a
//horizontally flipped version of the original picture
ppmPic *
swapppmPic(ppmPic *a)
    {
    int i;                                  
    Pixel temp;
    int j;                          //j is the row number
    for (j = 0; j < a->rows; j++)
        {                           //This for loop swaps each row, one at a time
        i = 0;                      //i is the column number
        while(i < a->cols / 2)      //integer division is used, so the middle row is not 
            {                       //swapped with itself if there's an odd number of cols 
            temp = a->pixels[j][i]; //This while loop swaps one row (row j)
            a->pixels[j][i] = a->pixels[j][a->cols - i - 1];
            a->pixels[j][a->cols - i - 1] = temp;
            i++;
            }
        }
    return a;
    }

//This function takes in a ppmPic structure
//and returns a ppmPic structure representing an
//upside-down version of the original picture
ppmPic *
flipppmPic(ppmPic *a)
    {
    int i;                           // integer division is used, so the middle row
    Pixel temp;                      //is not swapped with itself if there is an
    int j;                           //odd number of rows. (in the for loop
    for (j = 0; j < a->rows / 2; j++)   //condition)
        {                           //This for loop switches the top half to the bottom half
        i = 0;                      //i is the column number
        while(i < a->cols)
            {                       //This while loop switches an upper half row with
            temp = a->pixels[j][i]; //a corresponding lower half row
            a->pixels[j][i] = a->pixels[a->rows - 1 - j][i];
            a->pixels[a->rows - 1 - j][i] = temp;
            i++;
            }
        }
    return a;
    }

//This function takes in a ppmPic structure and 
//returns a ppmPic structure representing a ppmPic rotated 90 degrees
//from the original pic (clockwise).
ppmPic *
rotateppmPic(ppmPic *a)
    {
    //The function first rotates the picture 90 degrees counter clockwise, and then
    //flips it horizontally using the swapppmPic function
    //to achieve a 90 degree clockwise rotation.
    
    ppmPic *b = newppmPic();
    b->cols = a->rows;                          //a new ppmPic structure is created
    b->rows = a->cols;                          //because the number of rows and cols
    b->colors = a->colors;                      //will be switched (here).

    b->pixels = malloc(sizeof(Pixel *) * b->rows);      //
    int i;                                              //These four lines dynamically
    for(i = 0; i < b->rows; i++)                        //allocate the 2-dimensional array,
    b->pixels[i] = malloc(sizeof(Pixel) * b->cols);     //pixels

    int j;                                      //j is the row number
    for (j = 0; j < a->rows; j++)               //This for loop copies each row of a
        {                                       //into a column of b
        i = 0;                                  //i is the column number
        while(i < a->cols)
            {                                   //This while loop copies a single row of a
            b->pixels[i][j] = a->pixels[j][i];  //into a column of b
            i++;
            }
        }
                                                //The picture is now rotated 90 degrees
    free(a->pixels);                                            //counter clockwise
    return swapppmPic(b);                       //swap flips the picture horizontally.
    }
