/*---------------------------------------------------------------------------
 * 
 * basics.c 
 *
 *     08/26/2014 - 
 *
 *     <esatrod@egi.ericsson.com>
 *
 *     Copyright (c) 2014 RedBack Networks, Inc.
 *     All rights reserved.
 *
 *---------------------------------------------------------------------------
 */

#include<GL/glut.h>

void main(int argc, char**argv) { 
    glutInit(&argc, argv);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow(Hello World);
    glutMainLoop();
}
