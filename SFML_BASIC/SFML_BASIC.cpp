//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#include "GL/glu.h"
  
 
 
  
////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 
void Draw_Cuboid(float,float,float);


int main() 
{ 
    // Create the main window 
	int width = 1024, height = 1024;
    sf::RenderWindow App(sf::VideoMode(width,height, 32), "SFML OpenGL"); 

    // Create a clock for measuring time elapsed     
    sf::Clock Clock; 
      
    //prepare OpenGL surface for HSR 
    glClearDepth(1.f); 
    glClearColor(0.3f, 0.3f, 0.3f, 0.f); //background colour
    glEnable(GL_DEPTH_TEST); 
    glDepthMask(GL_TRUE); 
	
 



    // Start game loop 
    while (App.isOpen()) 
    { 
        // Process events 
        sf::Event Event; 
        while (App.pollEvent(Event)) 
        { 
            // Close window : exit 
            if (Event.type == sf::Event::Closed) 
                App.close(); 
   
            // Escape key : exit 
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape)) 
                App.close(); 
             
    
        } 
           
        //Prepare for drawing 
        // Clear color and depth buffer 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//// Setup a perspective projection & Camera position 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//set up a 3D Perspective View volume
		//gluPerspective(90.f, (float)width/height, 1.f, 300.0f);//fov, aspect, zNear, zFar 
        // Apply some transformations 
		//set up a  orthographic projection same size as window
		//this means the vertex coordinates are in pixel space
		//glOrtho(-2,2,-2,2,0,10); // use pixel coordinates




		//glMatrixMode(GL_PROJECTION); // reset projection matrix
		//glLoadIdentity();

		//calculate new prespective and aspect ratio
		gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,1.f,1000.0f);

        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); 
         
		glTranslatef(0,0,-2); //push back 10 units from camera
		//gluLookAt(	0,0,100,// camera position
		//			0,0,0, //look at this point
		//			0,1,0); //camera up

		static float ang=0.0;
		glRotatef(ang,1,0,0); //spin about x-axis
		glRotatef(ang*2,0,1,0);//spin about y-axis
		

		ang+=0.01f;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glEnable(GL_CULL_FACE);

		Draw_Cuboid(1,1,1);
		glDisable(GL_CULL_FACE);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Draw_Cuboid(1, 1, 1);

		glTranslatef(0,40,0);//move everyting after this line by 40 units along y-axis
		glRotatef(ang*5,0,0,1); //spin about z-axis

		Draw_Cuboid(10,10,10);

		   
        // Finally, display rendered frame on screen 
        App.display(); 
    } 
   
    return EXIT_SUCCESS; 
}

//Draw a cube at the origin
void Draw_Cuboid(float width,float height,float depth){
		// points of a cube
	static GLfloat points[][3]={	{1.0f,1.0f,1.0f},
									{1.0f,1.0f,0.0f},
									{0.0f,1.0f,0.0f},
									{0.0f,1.0f,1.0f},
									{1.0f,0.0f,1.0f},
									{1.0f,0.0f,0.0f},
									{0.0f,0.0f,0.0f},
									{0.0f,0.0f,1.0f}};

		//GLfloat normal[3];
		glPushMatrix();	
		glScalef(width,height,depth);
		glTranslatef(-0.5,-0.5,-0.5);
		glBegin(GL_QUADS);
		//top 
		
		//NormalVector(points[0],points[1],points[2],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,1.0,1.0);
		glVertex3fv(points[0]); glVertex3fv(points[1]); glVertex3fv(points[2]); glVertex3fv(points[3]);
		
		//front
		//NormalVector(points[0],points[3],points[7],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,0.0,1.0);
		glVertex3fv(points[0]); glVertex3fv(points[3]); glVertex3fv(points[7]); glVertex3fv(points[4]);
		
		//back
		//NormalVector(points[1],points[5],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,1.0,0.0);
		glVertex3fv(points[1]); glVertex3fv(points[5]); glVertex3fv(points[6]); glVertex3fv(points[2]);
		
		//left
		//NormalVector(points[3],points[2],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(0.0,1.0,0.0);
		glVertex3fv(points[6]); glVertex3fv(points[7]); glVertex3fv(points[3]); glVertex3fv(points[2]);
		
		//right
		//NormalVector(points[1],points[0],points[4],normal);
		//glNormal3fv(normal);
		glColor3d(0.0,0.0,1.0);
		glVertex3fv(points[4]); glVertex3fv(points[5]); glVertex3fv(points[1]); glVertex3fv(points[0]);

		//bottom
		//NormalVector(points[4],points[7],points[6],normal);
		//glNormal3fv(normal);
		glColor3d(1.0,0.0,0.0);
		glVertex3fv(points[4]); glVertex3fv(points[7]); glVertex3fv(points[6]); glVertex3fv(points[5]);
		
		
	glEnd();
	glPopMatrix();
}