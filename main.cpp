#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<iostream>
#include<bits/stdc++.h>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#define PI 3.14159265


using namespace std;

double Txval=0,Tyval=0,Tzval=0;
double tx=0,ty=0,tz=0;

double windowHeight=1080, windowWidth=720,car_run = 0, theta_pakha = 0.0,theta_fan = 0.0,ovAng = 0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLfloat upDown=3, leftRight = 10, farNear= 10;
GLfloat gscale=1,cdist=0,fdist=0; //zooming constant
GLfloat lpan=0,rpan=0;  //panning constant
GLboolean  bulb_switch = false, tube_switch=false, lamp_switch=false, bulb_ambient_light=true, bulb_diffusion_light=true, bulb_specular_light=true, tube_ambient_light=true, tube_diffusion_light=true, tube_specular_light=true, lamp_ambient_light=true, lamp_diffusion_light=true, lamp_specular_light=true;
GLboolean birds_eye =false;
GLfloat initialEyex= 130,initialEyey=55,initialEyez= 75,initialxaxis=0,initialyaxis=1,initialzaxis=0,initialx=40,initialy=40,initialz=0;
GLfloat x=80,y=40,z=0,eyex= 80,eyey=40,eyez=250,dx=0,dy=0,dz=0,xaxis=0,yaxis=1,zaxis=0; //for pitch , yaw, roll
GLboolean bRotate = false, uRotate = false, fan_rotate = true;
unsigned int ID;

float color1[] = {1,1,1};
float color2[] = {.8,.2,.2};
float color3[] = {.8,.2,.7};
float color4[] = {0,1,.7};


//colors
float red[] = {1.0,0.0,0.0};
float green[] = {0.0,1.0,0.0};
float blue[] = {0.0, 0.0,1.0};
float yellow[] = {1.0,1.0, 0.0};
float purple[] = {1.0,0.0,1.0};
float cyan[] = {0.0,1.0, 1.0};
float white[] = {1.0,1.0,1.0};
float orange[] = {1.0,0.5, 0.0};
float greenish_yellow[] = {0.5, 1.0,0.0};
float light_green[] = {0.5, 1.0,0.5};
float dark_green[] = {0.0, 0.5, 0.0};
float magenta[] = {1,0,1};
float violet[] = {0.5f, 0.5f, 0.5f};
float baby_blue[]= {0.0f, 0.5f, 1.0f};
float lilac[] = {2.0f, 0.5f, 1.0f};
float dark_grey[] = {0.1f, 0.1f, 0.1f};
float dark_purple[] = {0.1f, 0.0f, 0.1f};
float bronze[] = {0.1f, 0.1f, 0.0f};
float dark_blue[] = {0.0f, 0.1f, 0.1f};
float forest_green[] = {0.0f, 0.1f, 0.0f};
float brown[] = {0.1f, 0.0f, 0.0f};
float light_blue[] = {0.0f, 1.0f, 1.0f, 1.0f};
float chair_wood[] = {.20,.14,.14};
float table_wood[] = {.30,.14,.14};
float bed_wood[] = {.568,.318,.004};
float pillow_color[] = {0,1,.7};
float closet_wood[] = {1,.5,0};
float plastic_black[] = {.2,.2,.2};
float tiles_white[] = {.7,.7,.7};
float grey[] = {.4,.4,.4};
float wall_col[] = {0.9647, 0.8588, 0.16078};
float ceil_col[] = {0.776,0.6705,0.0};

using namespace std;

GLuint ID_[100];
int id=1;

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void LoadTexture2(const char*filename)
{
    glGenTextures(1, &ID_[id]);
    glBindTexture(GL_TEXTURE_2D, ID_[id]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID_[id++]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}


static void getNormal3p(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}


void drawCube(float x, float y, float z, float xheight, float yheight, float zheight, float color[],float shine=60)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { color[0]*.3, color[1]*.3, color[2]*.3,1.0 };
    GLfloat mat_diffuse[] = { color[0], color[1], color[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    static GLfloat v_cube[8][3] =
    {
        {0.0, 0.0, 0.0}, //0
        {0.0, 0.0, 1.0}, //1
        {1.0, 0.0, 1.0}, //2
        {1.0, 0.0, 0.0}, //3
        {0.0, 1.0, 0.0}, //4
        {0.0, 1.0, 1.0}, //5
        {1.0, 1.0, 1.0}, //6
        {1.0, 1.0, 0.0}  //7
    };

    static GLubyte quadIndices[6][4] =
    {
        {0, 1, 2, 3}, //bottom
        {4, 5, 6, 7}, //top
        {5, 1, 2, 6}, //front
        {0, 4, 7, 3}, // back is clockwise
        {2, 3, 7, 6}, //right
        {1, 5, 4, 0}  //left is clockwise
    };



    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);
        glTexCoord2f(0,1);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);
        glTexCoord2f(1,0);
    }
    glEnd();

}



void drawcube2(GLfloat r,GLfloat g,GLfloat b)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    static GLfloat v_pyramid[8][3] =
    {
        {0.0, 0.0, 0.0}, //0
        {4.0, 0.0, 0.0}, //1
        {4.0, 4.0, 0.0}, //2
        {0.0, 4.0, 0.0}, //3

        {0.0, 0.0, 4.0}, //4
        {4.0, 0.0, 4.0}, //5
        {4.0, 4.0, 4.0}, //6
        {0.0, 4.0, 4.0}, //7


    };
    static GLubyte quadIndices[6][4] =
    {
        //{4,5,6,7},
        {0,1,2,3},
        {1,5,6,2},
        {5,4,7,6},
        {4,0,3,7},
        {3,2,6,7},
        {4,5,1,0}
    };
    for (GLint i = 0; i <6; i++)
    {
        glBegin(GL_QUADS);
        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);
        glEnd();

    }
}


void outside(int basex, int basey, float px, float py, float pz)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(0,4.2,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(0,4.2,-3);
    glScalef(basex,basey,.5);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(0,4.2,-3);
    glScalef(.5,basey,basex);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(747.000000,4.2,-3);
    glScalef(.5,basey,basex);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 8);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(0,502.500000,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void road(int basex, int basey, float px, float py, float pz)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 9);
    glPushMatrix();
    glTranslatef(px,py,pz);
    glPushMatrix();
    glTranslatef(0,4.2,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,white,50);
    glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void materialProperty_car(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0, GLfloat ambY=0, GLfloat ambZ=0, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {70};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void drawTorus(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings, GLfloat shine=90)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glutSolidTorus(innerRadius, outerRadius, nsides, rings);

    //glutSolidTorus(0.5, 10.0, 16, 12);
}
void car(double pri_x, double pri_y, double pri_z, double sec_x, double sec_y, double sec_z)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    glRotatef(0, 1.0f, 0.0f, 0.0f);
    glRotatef(0, 0.0f, 1.0f, 0.0f);

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glEnd();


    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
//    glColor3f(1, 1.0, 1.0);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glEnd();

    materialProperty_car( sec_x, sec_y, sec_z, sec_x, sec_y, sec_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,0.0f,15.0f);
    glVertex3f(-40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,-15.0f);
    glVertex3f(40.0f,0.0f,15.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-40.0f,-15.0f,15.0f);
    glVertex3f(-40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,-15.0f);
    glVertex3f(40.0f,-15.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 13);
    materialProperty_car( pri_x, pri_y, pri_z, pri_x, pri_y, pri_z);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(20.0f,10.0f,15.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);


    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-10.0f,10.0f,15.0f);
    glVertex3f(-20.0f,0.0f,15.0f);
    glVertex3f(-20.0f,0.0f,-15.0f);
    glVertex3f(-10.0f,10.0f,-15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(20.0f,10.0f,15.0f);
    glVertex3f(20.0f,10.0f,-15.0f);
    glVertex3f(25.0f,0.0f,-15.0f);
    glVertex3f(25.0f,0.0f,15.0f);
    glEnd();

    materialProperty_car(0, 0, 0, 0, 0, 0);
    glBegin(GL_POLYGON);
//    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-30.0f,-15.0f,15.0f);
    glVertex3f(-30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,-15.0f);
    glVertex3f(30.0f,-15.0f,15.0f);
    glEnd();


    glBegin(GL_3D);
//    glColor3f(1, 0, 0);
    glTranslated(-20.0f,-15.0f,15.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);


//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,-30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(45.0f,0.0f,0.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
//    glColor3f(1, 0, 0);
    glTranslated(0.0f,0.0f,30.0f);
    drawTorus(0, 0, 0, 0, 0, 0, 2,5,5,100);
    glEnd();




    glPushMatrix();
    glColor3f(3.0,4.0,5.0);
    //glRotatef(45,0,0,1);
    glScalef(10,0.3,3);

//    glutWireCube(-20);


    glPopMatrix();


    glPopMatrix();
}


void interior(int basex, int basey, float px, float py, float pz )
{

    glPushMatrix();
    glTranslatef(px,py,pz);

    //base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(0,4.5,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);
    glPushMatrix();
    glTranslatef(0,4.5,-3);
    glScalef(basex,basey-20,1);
    drawCube(0,0,0,1,1,1,wall_col,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///banner
    //wall2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 7);
    //glBindTexture(GL_TEXTURE_2D, 1);
    glPushMatrix();
    glTranslatef(40.000000,103.000000,116.000000);
    glScalef(basex,40,1);
    drawCube(0,0,0,1,1,1,white,1000);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//    glDisable(GL_TEXTURE_2D);

    //wall2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);
    glPushMatrix();
    glTranslatef(0,4.5,-3);
    glScalef(1,basey-20,basey);
    drawCube(0,0,0,1,1,1,wall_col,100);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    //ceiling
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glTranslatef(0,103,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}



void kitchen(int basex, int basey, float px, float py, float pz )
{


    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 10);
    glPushMatrix();
    glTranslatef(0,4.5,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,110);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 11);
    glPushMatrix();
    glTranslatef(0,4.5,-3);
    glScalef(basex,basey-20,1);
    drawCube(0,0,0,1,1,1,wall_col,100);
    glPopMatrix();


    //wall2

    glPushMatrix();
    glTranslatef(0,4.5,40);
    glScalef(1,basey-20,basex*0.95);
    drawCube(0,0,0,1,1,1,tiles_white,100);
    glPopMatrix();

//
//    glPushMatrix();
//    glTranslatef(0,4.5,40);
//    glScalef(1,basey+10,basex*1.5);
//    drawCube(0,0,0,1,1,1,tiles_white,100);
//    glPopMatrix();

    //wall3
    glPushMatrix();
    glTranslatef(80,4.5,-3);
    glScalef(1,basey-20,basey);
    drawCube(0,0,0,1,1,1,wall_col,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //ceiling
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 12);
    glPushMatrix();
    glTranslatef(0,103,-3);
    glScalef(basex,.5,basey);
    drawCube(0,0,0,1,1,1,tiles_white,100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPopMatrix();


}




void table(int basex, int basey,float legsize, float px, float py, float pz )
{

    glPushMatrix();
    glTranslatef(px,py,pz);
    glBindTexture(GL_TEXTURE_2D, 7);

    //base
    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.55,0,-0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(3,-2,2);
    glScalef(.5,legsize,.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,-2,2);
    glScalef(.5,legsize,.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,-2,-2);
    glScalef(.5,legsize,.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3,-2,-2);
    glScalef(.5,legsize,.5);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();


    glPopMatrix();


}


void sofa(int basex, int basey,float basez, float px, float py, float pz )
{

    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
    glPushMatrix();
    glScalef(basex, basey*0.75, basez);
    glTranslatef(-0.55,-0.5,-0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();


    //top-back
    glPushMatrix();
    glTranslatef(0,3.5,1.5);
    glScalef(basex, basey, basez*0.30);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,table_wood);
    glPopMatrix();


    glPopMatrix();


}


void counter1(int basex, int basey,float basez, float px, float py, float pz )
{

    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);
    ///LoadTexture("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\counter_texture.bmp");
    glPushMatrix();
    glScalef(basex, basey, basez);
    //glTranslatef(-0.5,-0.5,-0.5);
    drawCube(0,0,0,1,1,1,white);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glPopMatrix();


}

void counter2(int basex, int basey,float basez, float px, float py, float pz )
{
    //top-back
    glPushMatrix();
    glTranslatef(px,py,pz);
    //glTranslatef(0,3.5,1.5);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 2);

    glPushMatrix();
    glScalef(basex, basey, basey);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,white);

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}


void chair(int basex, int basey,float legsize, float topsize, float px, float py, float pz )
{


    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
    glPushMatrix();
    glScalef(basex, 1, basey);
    glTranslatef(-0.5,0,-0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();


    //legs
    glPushMatrix();
    glTranslatef(2.5,-2,1.5);
    glScalef(1,legsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,-2,1.5);
    glScalef(1,legsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-2,-2);
    glScalef(1,legsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,-2,-2);
    glScalef(1,legsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();

    //leg top

    glPushMatrix();
    glTranslatef(2,2,-2);
    glScalef(1,topsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,2,-2);
    glScalef(1,topsize,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();


    //top leg connector
    glPushMatrix();
    glTranslatef(0,3.5,-2);
    glScalef(3,2.3,1);
    glTranslatef(-0.5, -0.5, -0.5);
    drawCube(0,0,0,1,1,1,chair_wood);
    glPopMatrix();


    glPopMatrix();


}


//
//void fan_handle()
//{
//    glPushMatrix();
//    glTranslatef(20.0, 17.0, -20.0);
//    glScalef(0.2,1.0,0.2);
//    drawCube(0,0,0,1,1,1,red,60);
//    glPopMatrix();
//}
//
//void fan()
//{
//    glPushMatrix();
//    glTranslatef(20.0, 17.0, -20.0);
//    glRotatef(theta_pakha, 0.0, 1.0, 0.0);
//    glScalef(0.4,0.4,0.4);
//
//    for(int i = 0; i < 180; i++)
//    {
//        glPushMatrix();
//        glScalef(2.0,0.5,1.0);
//        glRotatef(theta_fan+=2, 0.0, 1.0, 0.0);
//        drawCube(0,0,0,1,1,1,red,60);
//        glPopMatrix();
//    }
//
//    glPushMatrix();
//    glScalef(7.0,0.3,2.0);
//    drawCube(0,0,0,1,1,1,red,60);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(120, 0.0, 1.0, 0.0);
//    glScalef(7.0,0.3,2.0);
//   drawCube(0,0,0,1,1,1,red,60);
//    glPopMatrix();
//
//    glPushMatrix();
//    glRotatef(240, 0.0, 1.0, 0.0);
//    glScalef(7.0,0.3,1.5);
//  drawCube(0,0,0,1,1,1,red,60);
//    glPopMatrix();
//
//
//    glPopMatrix();
//}
////

void fan( float px, float py, float pz)
{


    float shine = 60;

    glPushMatrix();
    glTranslatef(px,py,pz);

    //fan base
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { orange[0]*.3, orange[1]*.3, orange[2]*.3,1.0 };
    GLfloat mat_diffuse1[] = { orange[0], orange[1], orange[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glScalef(1,1,1);
    gluCylinder(gluNewQuadric(), 5, 5, 2,100, 100);


    glPopMatrix();

    //back

    glPushMatrix();


    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    gluDisk(gluNewQuadric(),1,5,32,32);
    glPopMatrix();



    //front

    glPushMatrix();
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,0,2);
    gluDisk(gluNewQuadric(),0,5,32,32);
    glPopMatrix();

    //cone1

    glPushMatrix();

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,0,-3);
    gluCylinder(gluNewQuadric(),1,4,3,32,32);

    glPopMatrix();


    //rod
    glPushMatrix();


    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,0,-12);
    gluCylinder(gluNewQuadric(),1,1,10,32,32);
    glPopMatrix();


    //cone2
    glPushMatrix();

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,0,-15);
    gluCylinder(gluNewQuadric(),2.5,1,3,32,32);
    glPopMatrix();


    //connector1
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(-1,5,0.5);
    glScalef(2,4,.7);
    drawCube(0,0,0,1,1,1,tiles_white);

    glPopMatrix();

    //connector2
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(5,-5,0.5);
    glRotatef(45,0,0,1);

    glScalef(2,4,.7);
    drawCube(0,0,0,1,1,1,tiles_white);
    glPopMatrix();

    //connector3
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(-6,-4,0.5);
    glRotatef(-45,0,0,1);

    glScalef(2,4,.7);
    drawCube(0,0,0,1,1,1,tiles_white);
    glPopMatrix();



    //blade 1
    glPushMatrix();
    glRotatef(theta_fan,0,0,1);
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(-1.8,6,0.5);
    glScalef(3.5,25,.5);
    drawCube(0,0,0,1,1,1,orange);
    glPopMatrix();

    //blade2
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(20,-21,0.5);
    glRotatef(45,0,0,1);
    glScalef(3.5,25,.5);
    drawCube(0,0,0,1,1,1,orange);
    glPopMatrix();

    //blade3
    glPushMatrix();
    glRotatef(5,0,1,0);
    glTranslatef(-23,-20,0.5);
    glRotatef(-45,0,0,1);

    glScalef(3.5,25,.5);
    drawCube(0,0,0,1,1,1,orange);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

}





void lamp(float px, float py, float pz,float lamp_bulb_color[],float angle)
{


    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
//    glPushMatrix();
//    glTranslatef(0,4.5,-3);
//    glScalef(6,3,2);
//    drawCube(0,0,0,1,1,1,cyan);
//    glPopMatrix();
//
//    //base decorator
//
//    glPushMatrix();
//    glTranslatef(0,5,-3.1);
//    glScalef(6.2,2,2.2);
//    drawCube(0,0,0,1,1,1,dark_blue);
//    glPopMatrix();

    //first arm
//
//    glPushMatrix();
//    glTranslatef(0,5,-3);
//    glScalef(.5,15,.5);
//    drawCube(0,0,0,1,1,1,grey);
//    glPopMatrix();
//
//
//    //second arm
//
//    glPushMatrix();
//
//    glTranslatef(0,5,-1.5);
//    glScalef(.5,15,.5);
//    drawCube(0,0,0,1,1,1,grey);
//    glPopMatrix();
//

    //lamp site

    glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(5,19,-3);
    glScalef(7,1,2);
    drawCube(0,0,0,1,1,1,cyan);
    glPopMatrix();


    //light area

    glPushMatrix();

    glRotatef(angle,0,0,1);
    glTranslatef(5.5,18.7,-2.8);
    glScalef(6.5,.5,1.5);
    drawCube(0,0,0,1,1,1,lamp_bulb_color);

    glPopMatrix();




    glPopMatrix();
}

void bulb(float px, float py, float pz,float bulb_color[])
{


    glPushMatrix();
    glTranslatef(px,py,pz);

    //base cone

    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { orange[0]*.3, orange[1]*.3, orange[2]*.3, 1.0 };
    GLfloat mat_diffuse1[] = { orange[0], orange[1], orange[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,0,-15);
    gluCylinder(gluNewQuadric(),2.5,1,1,32,32);
    glPopMatrix();

    //extension

    glPushMatrix();
    GLfloat mat_ambient2[] = { orange[0]*.3, orange[1]*.3, orange[2]*.3, 1.0 };
    GLfloat mat_diffuse2[] = { orange[0], orange[1],orange[2], 1.0 };
    GLfloat mat_shininess2[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);
    glTranslatef(0,0,-14);
    gluCylinder(gluNewQuadric(),1,1,1,32,32);
    glPopMatrix();


    //bulb head

    glPushMatrix();
    GLfloat mat_ambient3[] = { bulb_color[0]*.3, bulb_color[1]*.3, bulb_color[2]*.3, 1.0 };
    GLfloat mat_diffuse3[] = { bulb_color[0], bulb_color[1], bulb_color[2], 1.0 };
    GLfloat mat_shininess3[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess3);
    glTranslatef(0,0,-12);
    gluSphere(gluNewQuadric(),2,32,32);

    glPopMatrix();



    glPopMatrix();
}

void tubelight(float px, float py, float pz,float tubelight_bulb_color[])
{


    glPushMatrix();
    glTranslatef(px,py,pz);


    //base
    glPushMatrix();
    glScalef(6.5,.5,.7);
    drawCube(0,0,0,1,1,1,orange);
    glPopMatrix();

    //left connector
    glPushMatrix();
    glTranslatef(0,0,0);
    glScalef(.5,1.5,.7);
    drawCube(0,0,0,1,1,1,orange);

    glPopMatrix();

    //right connector
    glPushMatrix();
    glTranslatef(6,0,0);
    glScalef(.5,1.5,.7);
    drawCube(0,0,0,1,1,1,orange);

    glPopMatrix();

    //tube
    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient1[] = { tubelight_bulb_color[0]*.3, tubelight_bulb_color[1]*.3,tubelight_bulb_color[2]*.3, 1.0 };
    GLfloat mat_diffuse1[] = { tubelight_bulb_color[0], tubelight_bulb_color[1], tubelight_bulb_color[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess1[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
    glTranslatef(0,1,.3);
    glRotatef(90,0,1,0);
    gluCylinder(gluNewQuadric(),.3,.3,6,32,32);
    glPopMatrix();



    glPopMatrix();
}
//
//void clock(float px, float py, float pz)
//{
//
//
//    glPushMatrix();
//    glTranslatef(px,py,pz);
//
//    //base circle
//    glPushMatrix();
//    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient[] = { red[0]*.3, red[1]*.3, red[2]*.3, 1.0 };
//    GLfloat mat_diffuse[] = { red[0], red[1], red[2], 1.0 };
//    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess[] = {60};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
//
//    gluDisk(gluNewQuadric(),.5,5,32,32);
//    glPopMatrix();
//
//    //surround circle
//
//    glPushMatrix();
//    GLfloat no_mat1[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient1[] = { green[0]*.3, green[1]*.3, green[2]*.3, 1.0 };
//    GLfloat mat_diffuse1[] = { green[0], green[1], green[2], 1.0 };
//    GLfloat mat_specular1[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess1[] = {60};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient1);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse1);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular1);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess1);
//
//    gluCylinder(gluNewQuadric(), 5, 6, 2,100, 100);
//    glPopMatrix();
//
//    //outer circle
//    glPushMatrix();
//    GLfloat no_mat2[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_ambient2[] = { green[0]*.3, green[1]*.3, green[2]*.3, 1.0 };
//    GLfloat mat_diffuse2[] = { green[0], green[1], green[2], 1.0 };
//    GLfloat mat_specular2[] = { 1.0, 1.0, 1.0, 1.0 };
//    GLfloat mat_shininess2[] = {60};
//
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2);
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2);
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2);
//    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess2);
//    glTranslatef(0,0,2);
//    gluDisk(gluNewQuadric(),4,6,32,32);
//    glPopMatrix();
//
//
//    //hour dial
//    glPushMatrix();
//
//
//    glRotatef(5,0,1,0);
//    glTranslatef(0,0,0.5);
//    glRotatef(-45,0,0,1);
//    glScalef(2,.5,.1);
//    drawCube(0,0,0,1,1,1,white);
//    glPopMatrix();
//
//    //minute dial
//
//    glPushMatrix();
//
//
//    glRotatef(5,0,1,0);
//    glTranslatef(0,0,0.5);
//    glRotatef(80,0,0,1);
//    glScalef(4,.5,.1);
//    drawCube(0,0,0,1,1,1,white);
//    glPopMatrix();
//
//
//
//
//
//    glPopMatrix();
//}



double fAng =0.0,ang=0;


void drawcylinder(GLfloat r=.3,
                  GLfloat g=.4,
                  GLfloat b=.5,
                  GLboolean emission = false, GLfloat base=2, GLfloat top=2, GLfloat height=5)
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
//    gluCylinder(qobj,2,2,5,20,10);
    gluCylinder(qobj,base,top,height,20,10);
//    gluCylinder();
}


void drawdisk(GLfloat r=0.3,
              GLfloat g=0.4,
              GLfloat b=0.5,
              GLboolean emission = false,GLfloat inner=0.0002,GLfloat outer=2 )
{

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { r, g, b, 1.0 };
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    GLfloat mat_em[] = {1.0,1.0,1.0,1.0};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    if(emission) glMaterialfv( GL_FRONT, GL_EMISSION, mat_em);
    else glMaterialfv( GL_FRONT, GL_EMISSION, no_mat);

    GLUquadric* qobj;
    qobj = gluNewQuadric();
//    gluDisk(qobj,2,2,5,20,10);
    gluDisk(qobj,inner,outer,20,10);
}

void drawjug(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1,1,4);
    glPopMatrix();

}
void drawbottle(GLfloat r, GLfloat g, GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1,1,4);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, -2.200000);
    drawcylinder(r,g,b,false,.3,.3,3);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawdisk(r,g,b,false,.0002,1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 3.999998);
    drawdisk(r,g,b,false,.0002,1);
    glPopMatrix();
}


void drawoven()
{

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(ovAng,1,0,0);
    glScalef(3,4,.3);
    glBindTexture(GL_TEXTURE_2D,16);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.3,4,1.5);
    glTranslatef(0.000000, 0.000000, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(.3,4,1.5);
    glTranslatef(35.700027, 0.000000, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
//    glRotatef(ovAng,1,0,0);
    glScalef(3,4,.3);
    glTranslatef(0,0,-16.800028);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glScalef(3,.3,1.5);
    glTranslatef(0,50.199806, -3.399999);
    glBindTexture(GL_TEXTURE_2D,12);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glScalef(3,.3,1.5);
    glTranslatef(0,0, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glEnable(GL_TEXTURE_2D);
    glPushMatrix();

    glScalef(3,.3,1.5);
    glTranslatef(0,25, -3.399999);
    glBindTexture(GL_TEXTURE_2D,15);
    drawcube2(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//    //panin
//    glPushMatrix();
////    glRotatef(-90,0,1,0);
//    glScalef(.4,.4,.4);
//    glTranslatef(px,py,pz);
//    drawkorai(.5,.5,.5);
//    glPopMatrix();

}


void drawbowl(GLfloat r,GLfloat g,GLfloat b)
{

    glPushMatrix();
    glRotatef(90,1,0,0);
    drawcylinder(r,g,b,false,1.8,0.8,1.2);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(0.000000, 0.000000, 1.200000);
    drawdisk(r,g,b,false,.002,.8);

    glPopMatrix();
}

void drawfridge(GLfloat r,GLfloat g,GLfloat b)
{

    glPushMatrix();

    glTranslatef(0,13.500015,0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,4);
    //glPushMatrix();
    //sides
    glPushMatrix();
    glScalef(.3,12,2);
//    glTranslatef(tx,ty,tz);
    drawcube2(r,g,b);
    glPopMatrix();

    glPushMatrix();
    glScalef(.3,12,2);
    glTranslatef(-74.599434, 0.000000, 0.000000);
    drawcube2(r,g,b);
    glPopMatrix();


    //sides

    //top bottom

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,0,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,31.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,62.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,92.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,122.200083,0);
    drawcube2(1,1,1);
    glPopMatrix();


    glPushMatrix();
    glScalef(5.5,.3,2);
    glTranslatef(-3.899998,156.100327,0);
    drawcube2(1,1,1);
    glPopMatrix();


    //top bottom


    //back

    glPushMatrix();
    glScalef(5.5,12,.3);
    glTranslatef(-3.899998, 0.000000, 0.000000);
    drawcube2(.5,.5,.5);
    glPopMatrix();

    //glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    //back


    //front
    ///GT;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
//    glRotatef( falpha, axis_x, axis_y, axis_z );

//    glRotatef( 90, 0, 1, 0 );
    glTranslatef(2.2,0,-0.600000);
    glTranslatef(-2.5,0,2);
    glRotatef( fAng, 0, 1, 0 );
    glScalef(5.5,12,.3);
    glTranslatef(-3.899998, 0, 23.400053);
//    glRotatef( -45, 0, 1, 0 );
    ///glBindTexture(GL_TEXTURE_2D,28);

    drawcube2(.5,.5,.5);
    glPopMatrix();
    ///GD;
    glDisable(GL_TEXTURE_2D);
    //front


    //objects inside


    glPushMatrix();
    glTranslatef(-2.400000, 21.100044, 3.199999);
    drawbowl(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.400000, 21.100044, 6.599996);
    drawbowl(.5,.3,.4);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 21.100044, 3.199999);
    drawbowl(.6,.8,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.099997, 21.100044, 6.599996);
    drawbowl(.9,.8,.1);
    glPopMatrix();


    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-2.999999, 5.999997, -2.200000);
    drawbottle(.6,.8,1);
    glPopMatrix();

//    glPushMatrix();
//    glRotatef(90,1,0,0);
//    glTranslatef(btx,bty,btz);
//    drawbottle(.5,.3,.4);
//    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-10.999996, 5.999997, -2.200000);
    drawbottle(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-14.999996, 5.999997, -2.200000);
    drawbottle(.8,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-18.999996, 5.999997, -2.200000);
    drawbottle(.9,.9,.5);
    glPopMatrix();



    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-10.999996, 5.999997, -29.800077);
    drawbottle(.3,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-14.999996, 5.999997, -29.800077);
    drawbottle(.8,.4,.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glTranslatef(-18.999996, 5.999997, -29.800077);
    drawbottle(.9,.9,.5);
    glPopMatrix();










    glPopMatrix();
}



void bulbLight() //light for bulb
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 70,80,-40,1.0};

    if(bulb_ambient_light == true)
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
    }

    if(bulb_diffusion_light == true)
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
    }

    if(bulb_specular_light == true)
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void tubeLight()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 0.9, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 60,90,30, 1};

    if(tube_ambient_light == true)
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_AMBIENT, no_light);
    }

    if(tube_diffusion_light == true)
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_DIFFUSE, no_light);
    }

    if(tube_specular_light == true)
    {
        glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT1, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    glPopMatrix();
}

void lampLight()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1, 1, 1, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {10-5+40, 20+113+65, -43+33+27};
    //glEnable( GL_LIGHT2);

    if(lamp_ambient_light == true)
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
    }

    if(lamp_diffusion_light == true)
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
    }

    if(lamp_specular_light == true)
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat spot_direction[] = {40+10-5, 0, -43+33+27+100 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 40.0);
    glPopMatrix();
}

void lampLight2()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1, 1, 1, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {-2+5+10-5+40, 0+20+113+65, 1-43+33+27};
    //glEnable( GL_LIGHT2);

    if(lamp_ambient_light == true)
    {
        glLightfv( GL_LIGHT3, GL_AMBIENT, light_ambient);
    }
    else
    {
        glLightfv( GL_LIGHT3, GL_AMBIENT, no_light);
    }

    if(lamp_diffusion_light == true)
    {
        glLightfv( GL_LIGHT3, GL_DIFFUSE, light_diffuse);
    }
    else
    {
        glLightfv( GL_LIGHT3, GL_DIFFUSE, no_light);
    }

    if(lamp_specular_light == true)
    {
        glLightfv( GL_LIGHT3, GL_SPECULAR, light_specular);
    }
    else
    {
        glLightfv( GL_LIGHT3, GL_SPECULAR, no_light);
    }

    glLightfv( GL_LIGHT3, GL_POSITION, light_position);
    GLfloat spot_direction[] = {-2+40+5+10-5, 0, 1-43+33+27+100 };
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT3, GL_SPOT_CUTOFF, 40.0);
    glPopMatrix();
}


void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0, 50.0, 0, 1.0 };  //pos

    glEnable( GL_LIGHT0);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}

void draw_sp()
{
    glTranslatef(150,-30,-10);
    glScalef(0.5,0.5,0.5);

    // cout<<" kn "<<endl;



    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.1, .1, 0.1, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {40};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, 3);

    glPushMatrix();
    glTranslatef(0, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, 3.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 1.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 11.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 20.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,5,10);

    glPushMatrix();
    glTranslatef(0, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(15, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(30, 0.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5, 10.0, 5.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(20, 20.0, 0.0);
    glutSolidSphere(10.0, 50, 50);
    glPopMatrix();

    glPopMatrix();


//    for(double i=60; i>=0; i-=2)
//    {
//        for(double j = 0; j<i; j+=5)
//        {
//
//            for(double k=0; k<j; k+=7)
//            {
//
//                glPushMatrix();
//                glTranslatef(i, -j, k);
//                glutSolidSphere(10.0, 50, 50);
//                glPopMatrix();
//            }
//        }
//    }

    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

}

void draw_tree(double x,double y,double z,double p,double q,double r)
{

    glTranslatef(10,-20,-80);
    glScalef(1.5,1.5,1.5);
    glScalef(2.5,3.5,2.5);

    glPushMatrix();
    glTranslatef(-100,50,0);
    draw_sp();
    glPopMatrix();

    glPushMatrix();

    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { .5, .5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {30};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glTranslatef(56,4,-4);
    glScalef(2, 10, 2);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 6);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(p, q, r);
    drawcube2(1,1,1);
    glPopMatrix();
    //draw_color_cube(0,1,1);
    glDisable(GL_TEXTURE_2D );
    glPopMatrix();
}



void scene( float px, float py, float pz )
{


    glPushMatrix();

    //scene placement
    glTranslatef(px,py,pz);

    glPushMatrix();
    outside(750,500,-200,0,-100);
    glPopMatrix();

    glPushMatrix();
    road(750,35,-5+-200,3,267+-100);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(-419.000000+350+car_run,31.500000+6+2,69.000000+300);
    car(01, 01, 01, 0.5, .5, .5);
    glPopMatrix();

    ///TREE
    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(-66.000000-273.000000,24.500000,165.000000+72.000000);
    draw_tree(-58.000000,0,32.000000,1,1,1);
    glPopMatrix();

    ///TREE
    glPushMatrix();
    glScalef(.5,.5,.5);
    glTranslatef(-102.000000+-66.000000-273.000000,24.500000,0+165.000000+72.000000);
    draw_tree(2,-0.5,0,0.4,.7,.4);
    glPopMatrix();

    glPushMatrix();
    interior(150,120,0,0,0);
    glPopMatrix();


    glPushMatrix();
    kitchen(80,120,150,0,0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    ///table1
    glPushMatrix();
    glRotatef(90,0,1,0);
    //glTranslatef(tx,ty,tz);
    glTranslatef(-60,20,10);
    glScalef(3,3,2);
    table(7,5,4,0,0,0);
    glPopMatrix();

//    ///jug1
//    glPushMatrix();
//    glRotatef(90,0,1,0);
//    glTranslatef(-116,29,18);
//
//    glScalef(1,1,1);
//    drawjug(1,1,1);
//    glPopMatrix();



    ///t1c1
    glPushMatrix();
    glTranslatef(8,15,75);
    glRotatef(180,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();
    ///t1c2
    glPushMatrix();
    glTranslatef(17,15,60);
    glRotatef(-90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();

    ///table2
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-60,20,10);
    glScalef(3,3,2);
    table(7,5,4,-15,0,0);
    glPopMatrix();
    ///t2c1
    glPushMatrix();
    glTranslatef(8,15,115);
    glRotatef(180,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();
    ///t2c2
    glPushMatrix();
    glTranslatef(17,15,103);
    glRotatef(-90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();

    ///table3
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-60,20,10);
    glScalef(3,3,2);
    table(7,5,4,0,0,25);
    glPopMatrix();
    ///t3c1
    glPushMatrix();
    glTranslatef(17+50,15,60);
    glRotatef(-90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();
    ///t3c2
    glPushMatrix();
    glTranslatef(17+38,15,60);
    glRotatef(90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();



    ///table4
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-60,20,10);
    glScalef(3,3,2);
    table(7,5,4,-15,0,25);
    glPopMatrix();
    ///t4c1
    glPushMatrix();
    glTranslatef(17+50,15,60+45);
    glRotatef(-90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();
    ///t4c2
    glPushMatrix();
    glTranslatef(17+38,15,60+45);
    glRotatef(90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();


    ///sofa2
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-50,25,10);
    glScalef(3,3,2);
    sofa(7,5,4,-2,-4,62);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    ///sofa2
//    glPushMatrix();
//    glRotatef(180,0,1,0);
//    glTranslatef(-60,20,10);
//    glScalef(3,3,2);
//    sofa(7,5,4,0,0,0);
//    glPopMatrix();
//
//
    ///counter
    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-40,25,-20);
    glScalef(5,5,2);
    //glRotatef(180,0,1,0);
    counter1(7,5,4,-15,-4,62);
    //sofa(7,5,4,-2,-4,62);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(-55,38,-185);
    glScalef(2,5,5);
    //glRotatef(180,0,1,0);
    counter2(7,5,4,-15,-4,62);
    //sofa(7,5,4,-2,-4,62);
    glPopMatrix();


    ///counterchair

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 14);
    glPushMatrix();
    glTranslatef(12+58+17+38,15,-35+45+60+45);
    glRotatef(-90,0,1,0);
    glScalef(1.5,2,1);
    chair(5,6,4.5,5.8,0,0,0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    ///FRIDGE
    glPushMatrix();
    glTranslatef(228,-8,8);
    glScalef(1,1,1);
    drawfridge(1,1,1);
    glPopMatrix();
    ///oven
    glPushMatrix();
    glTranslatef(-39.000000+220,13.000000+-8,-16.000000+28);
    glScalef(1.6,1.6,1.6);
    drawoven();
    glPopMatrix();


    ///fan1
    glPushMatrix();
    glTranslatef(45,91,38);
    glRotatef(90,1,0,0);
    glScalef(.6,.6,.6);
    fan(0,0,0);
    glPopMatrix();
//
///fan2
    glPushMatrix();
    glTranslatef(45,91,60+28);
    glRotatef(90,1,0,0);
    glScalef(.6,.6,.6);
    fan(0,0,0);
    glPopMatrix();
//
    //
///fan2
    glPushMatrix();
    glTranslatef(45+60,91,38);
    glRotatef(90,1,0,0);
    glScalef(.6,.6,.6);
    fan(0,0,0);
    glPopMatrix();
//
    //
///fan2
    glPushMatrix();
    glTranslatef(45+60,91,60+28);
    glRotatef(90,1,0,0);
    glScalef(.6,.6,.6);
    fan(0,0,0);
    glPopMatrix();
//


    glPushMatrix();
    glTranslatef(36.000000,126.500000, 112.000000);
    glRotatef(-45,0,1,0);
    glScalef(1,1,1);
    lamp(0,0,0,white,15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4+148.000000+36.000000,0+126.500000, 5+0+112.000000);
    glRotatef(45,0,1,0);
    glScalef(1,1,1);
    lamp(0,0,0,white,15);
    glPopMatrix();


//
//    glPushMatrix();
//    glTranslatef(50,79,0);
//    glRotatef(0,0,1,0);
//    glScalef(1,1,1);
//    clock(0,0,0);
//    glPopMatrix();



    glPushMatrix();
    glTranslatef(70,80,7);
    glRotatef(0,0,1,0);
    glScalef(.5,.5,.5);
    bulb(0,0,0,white);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1,90,70);
    glRotatef(-90,0,0,1);
    glRotatef(90,0,1,0);
    glScalef(3,1,3);
    tubelight(0,0,0,white);
    glPopMatrix();

    glPushMatrix();

    glPushMatrix();
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { red[0]*.3, red[1]*.3, red[2]*.3, 1.0 };
    GLfloat mat_diffuse[] = { red[0], red[1], red[2], 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

//    glTranslatef(90,10,70);
//    gluSphere(gluNewQuadric(),5,32,32);
    glPopMatrix();



    glPopMatrix();


}


float axis_z = 0;
void display(void)
{

    glClearColor(0.75,0.78,0.815,0.7);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5, 5, -5, 5, 4, 1000);

    //gluPerspective(60,1,5,100);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyex+cdist,eyey+cdist,eyez+cdist+70, x+dx,y+dy,z+dz, xaxis,yaxis,zaxis);

    //glViewport(0, 0, windowHeight, windowWidth);

    glRotatef(theta,axis_x,axis_y,axis_z);

    glEnable(GL_LIGHTING);
    bulbLight();
    tubeLight();
    lampLight();
    lampLight2();

    glPushMatrix();

    //glRotatef(Tzval,0,1,0);
    glRotatef(Tyval,1,0,0);

    glScalef(gscale,gscale,gscale);
    scene(0,0,0);
    //book(0,0,0);
    //fan(0,0,0);
    //lamp(0,0,0);
    //bulb(0,0,0);
    //tubelight(0,0,0);
    //clock(0,0,0,color2,color3,color1);
    //calender(0,0,0);
    //monitor(0,0,0);
    //keyboard(0,0,0);
    //matress(0,0,0);
    //drawCube(0,0,0,1,1,1,color2);
    //chair(7,7,6,8,0,0,0);
    //closet(18,7,26,0,0,0);
    //interior(100,90,0,0,0);
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glFlush();
    glutSwapBuffers();
}

double dd = 4,aY = 90,aP = 0, aR = 90,d_v=5, radius = 90;


void pitch() /// x axis , y er about
{
    dy = 0 ;
    dz = 0;
    y = eyey+radius*(cos(aP*3.1416/180.0));
    z = eyez+radius*(sin(aP*3.1416/180.0));
}

void yaw() /// y axis, x axis about
{
    //lookY = 50.0*(cos(aY*3.1416/180.0));
    printf("%lf\n", aY);

    dx = 0;
    dz = 0;
    x = eyex+radius*(cos(aY*3.1416/180.0));
    z = eyez+radius*(sin(aY*3.1416/180.0));
}


void roll() /// z axis
{
    xaxis = (cos(aR*3.1416/180.0));
    yaxis = (sin(aR*3.1416/180.0));
    printf("%lf %faR\n", aR,cos(aR*3.1416/180.0));
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    case 'q': //car run
        car_run+=3;
        break;
    case 'Q': //car back
        car_run-=2;
        break;


    case 'k': //zoom in
        eyez++;
        dz++;
        break;
    case 'i': //zoom out
        eyez--;
        dz--;
        break;
    case 'I': //zoom up
        eyey++;
        dy++;
        break;
    case 'K': //zoom down
        eyey--;
        dy--;
        break;

    case 'l':
        eyex++;
        dx++;
        break;
    case 'j':
        eyex--;
        dx--;
        break;




//g
//yaw
    case 'y':

        aY+=d_v;

        yaw();
        glutPostRedisplay();
        break;
    case 'Y':

        aY-=d_v;
        // aY += 360.0*floor(aY/360.0);
        yaw();
        glutPostRedisplay();
        break;


        //cout<<"x :"<<x <<"y:"<<y<<"z:"<<z<<endl;

        break;
//pitch

    case 't':

        aP+=d_v;
        pitch();
        glutPostRedisplay();
        break;
    case 'T':

        aP-=d_v;
//        if(aP<=-180)
//            break;
        pitch();
        glutPostRedisplay();
        break;

//roll
    case 'r':
        aR+=d_v;

        roll();
        glutPostRedisplay();
        break;

    case 'R':
        aR-=d_v;

        // aY += 360.0*floor(aY/360.0);
        roll();
        glutPostRedisplay();
        break;


//light switches


    case '7': //to turn on and off lamp
        if(lamp_switch == false)
        {
            lamp_switch = true;
            lamp_ambient_light=true;
            lamp_diffusion_light=true;
            lamp_specular_light=true;
            glEnable( GL_LIGHT2);
            glEnable( GL_LIGHT3);
            break;
        }
        else if(lamp_switch == true)
        {
            lamp_switch = false;
            lamp_ambient_light=false;
            lamp_diffusion_light=false;
            lamp_specular_light=false;
            glDisable( GL_LIGHT2);
            glEnable( GL_LIGHT3);
            break;
        }
        break;


    case '8': //to turn on and off bulb
        if(bulb_switch == false)
        {
            bulb_switch = true;
            bulb_ambient_light=true;
            bulb_diffusion_light=true;
            bulb_specular_light=true;
            glEnable( GL_LIGHT0);
            break;
        }
        else if(bulb_switch == true)
        {
            bulb_switch = false;
            bulb_ambient_light=false;
            bulb_diffusion_light=false;
            bulb_specular_light=false;
            glDisable( GL_LIGHT0);
            break;
        }
        break;


    case '9': //to turn on and off tubelight
        if(tube_switch == false)
        {
            tube_switch = true;
            tube_ambient_light=true;
            tube_diffusion_light=true;
            tube_specular_light=true;
            glEnable( GL_LIGHT1);
            break;
        }
        else if(tube_switch == true)
        {
            tube_switch = false;
            tube_ambient_light=false;
            tube_diffusion_light=false;
            tube_specular_light=false;
            glDisable( GL_LIGHT1);
            break;
        }
        break;

    case'!': //turn on/off ambient light 1
        if(bulb_ambient_light == false)
        {
            bulb_ambient_light=true;
            break;
        }
        else
        {
            bulb_ambient_light=false;
            break;
        }


    case'@':
        if(bulb_diffusion_light == false)
        {
            bulb_diffusion_light=true;
            break;
        }
        else
        {
            bulb_diffusion_light=false;
            break;
        }

    case'#':
        if(bulb_specular_light == false)
        {
            bulb_specular_light=true;
            break;
        }
        else
        {
            bulb_specular_light=false;
            break;
        }

    case'$': //turn on/off ambient light 2
        if(tube_ambient_light == false)
        {
            tube_ambient_light=true;
            break;
        }
        else
        {
            tube_ambient_light=false;
            break;
        }

    case'%':
        if(tube_diffusion_light == false)
        {
            tube_diffusion_light=true;
            break;
        }
        else
        {
            tube_diffusion_light=false;
            break;
        }

    case'^':
        if(tube_specular_light == false)
        {
            tube_specular_light=true;
            break;
        }
        else
        {
            tube_specular_light=false;
            break;
        }

    case'&': //turn on/off ambient lamp light
        if(lamp_ambient_light == false)
        {
            lamp_ambient_light=true;
            break;
        }
        else
        {
            lamp_ambient_light=false;
            break;
        }

    case'*':
        if(lamp_diffusion_light == false)
        {
            lamp_diffusion_light=true;
            break;
        }
        else
        {
            lamp_diffusion_light=false;
            break;
        }


    case'~':
        if(lamp_specular_light == false)
        {
            lamp_specular_light=true;
            break;
        }
        else
        {
            lamp_specular_light=false;
            break;
        }


//    fanswitch
    case 'e':
        fan_rotate = false;
        break;
    case 'E':
        fan_rotate = true;
        break;

    case 'W':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        axis_z=1.0;
        break;

    case 'b':

        swap(eyey, eyez);
        break;

    case 'Z':
        tx-=1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case 'X':
        tx+=1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case 'C':
        ty-=.5;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case 'V':
        ty+=.5;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case 'B':
        tz-=1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;
    case 'N':
        tz+=1;
        printf("%lf %lf %lf\n",tx,ty,tz);
        break;

    case '>':
        if(fAng>0)
            fAng-=1;
        break;
    case '.':
        if(fAng<40)
            fAng+=1;
        break;
    case '<':
        if(ovAng>0)
            ovAng-=1;
        break;
    case ',':
        if(ovAng<70)
            ovAng+=1;
        break;
    case '{':
        printf("%lf\n",ang);
        if(ang>0)
            ang-=1;
        break;
    case '}':
        printf("%lf\n",ang);
        if(ang<180)
            ang+=1;
        break;


    case 27:	// Escape key
        exit(1);
    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.5;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 10.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (fan_rotate == true)
    {
        theta_fan += 8.50;
        if(theta_fan > 360) theta_fan = 0.0;
    }

    glutPostRedisplay();

}




static void resize(int width, int height)
{
    const float ar = (float) height / (float) width;


    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -ar, ar, 4, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}

static void idle(void)
{
    glutPostRedisplay();
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

//    cout<<"Input Mappings"<<endl;
//    cout<<"---------------"<<endl;
//    cout<<"Object zooming: z(+) x(-)"<<endl;
//    cout<<"Viewer zooming: c(-) v(+)"<<endl;
//    cout<<"Window zooming: n(+) m(-)"<<endl;
//    cout<<"Panning : l(+) k(-)"<<endl;
//    cout<<"Yaw : y(+) t(-)"<<endl;
//    cout<<"Pitch: 1(-) 2(+)"<<endl;
//    cout<<endl<<endl;
//    cout<<"7: Lamp " <<endl;
//    cout<<"8: Bulb " <<endl;
//    cout<<"9: Tubelight " <<endl;
//    cout<<"!: bulb ambient " <<endl;
//    cout<<"@: bulb diffusion " <<endl;
//    cout<<"#: bulb specular" <<endl;
//    cout<<"$: tubelight ambient" <<endl;
//    cout<<"%: tubelight diffusion " <<endl;
//    cout<<"^: tubelight specular " <<endl;
//    cout<<"&: lamp ambient " <<endl;
//    cout<<"*: lamp diffusion " <<endl;
//    cout<<"~: lamp specular" <<endl;
//    cout<<"B: birds eye view " <<endl;
//    cout<<"+: birds eye view move forward " <<endl;
//    cout<<"-: birds eye view move backward " <<endl;
//    cout<<"s: toggle fan switch" <<endl;

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Project-1707036");
    printf("%lf %lf %lf\n",tx,ty,tz);
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\starbuck.bmp"); ///1
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\counter_texture.bmp");///2
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\grass.bmp");///3
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\fridge.bmp");///4
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\fridge_door.bmp");///5
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\tree_wood.bmp");///6
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\banner.bmp");///7
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\sky.bmp");///8
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\road.bmp");///9
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\floor.bmp");///10
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\wall.bmp");///11
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\ceiling.bmp");///12
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\car.bmp");///13
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\furni.bmp");///14
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\stl.bmp");///15
    LoadTexture2("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\ovn.bmp");///16
    //LoadTexture("G:\\Semesters\\CSE 4-2\\Graphics_Project\\Coffee_Shop\\counter_texture.bmp");


    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    //light();

    glutKeyboardFunc(myKeyboardFunc);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
