
/*
 *  hist.c
 *  Compute the histogram of the visitors.  
 *  This program illustrates the
 *  use of the glHistogram() function.
 */



 
 /* Create an array with nun_buckets that will store data from min to max */
//struct histogram* histogram_create(int min, int max, int num_buckets);

/* Increment the bucket for data_point */
//void histogram_inc(struct histogram* hist, int data_point);

/* Print out the histogram bucket counts */
//void histogram_print(struct histogram* hist);



#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <GLUT/glut.h>
#include <stdlib.h>




#define LIMIT 20.0      // limit
#define CENTER (LIMIT - LIMIT - 1)


// prototype
void setup();             // initialization of the program
void display();           // drawing method
void create_coordinate();  // certasian coordinate
void draw();              // draw the object
void create_box(float, float, float, float);
void create_histogram(int, float*);

void create_histogram(int len, float *data)
{
    float x, y = 1.0, width = 1.0;
    int i;
    for(i=0; i<len; i++){
        x = (i * width) + i + 1;
        create_box(x, y, width, data[i]);
    }
}




void setup()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(CENTER, LIMIT, CENTER, LIMIT); // gluOrtho2D(left, right, bottom, top)

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    
    draw();
    create_coordinate();
    
    glFlush();
}


void draw()
{
    float value[] = {10.0, 15.0, 13.0, 9.0, 7.0, 10.0, 1.0 , 2.0, 3.0 ,4.0 , 5.0, 6, 17.0};
    int len = sizeof(value);
    createHistogram(len, value);
    
    
}

void create_box(float x, float y, float width, float height)
{
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x, y+height);
    glVertex2f(x+width, y+height);
    glVertex2f(x+width, y);
    glEnd();
}

void create_coordinate()
{
    glBegin(GL_LINES);
    // horizontal lines
    glVertex2f(-LIMIT, 0.0);
    glVertex2f(LIMIT, 0.0);
    
    // vertical lines
    glVertex2f(0.0, -LIMIT);
    glVertex2f(0.0, LIMIT);
    glEnd();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Histogram for Network Analysis");
    
    //float value[] = {10.0, 15.0, 13.0, 9.0, 7.0, 10.};
    
    glutDisplayFunc(display);
    
    setup();
    glutMainLoop();
    
    
    
    return 0;
    
}
