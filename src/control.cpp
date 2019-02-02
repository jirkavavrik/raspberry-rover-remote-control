#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>//pton

#include <SDL2/SDL.h>

//size of window in pixels
int windowXSize = 640;
int windowYSize = 480;

SDL_Renderer* renderer;
SDL_Color color = {0,0,255,SDL_ALPHA_OPAQUE}; //default color blue
enum colors {colorRed, colorGreen, colorBlue, colorOrange, colorTurqoise, colorMagenta, colorBlack};
char currentColorCode = 2;




int main(int argc, char *argv[]) {	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* mainWindow = SDL_CreateWindow("Conway's game of life by Jiři Vavřík v3.2.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowXSize, windowYSize, SDL_WINDOW_RESIZABLE); //create window
	// Check that the window was successfully created
    if (mainWindow == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
	renderer = SDL_CreateRenderer(mainWindow,-1,SDL_RENDERER_ACCELERATED);//create renderer
	// Check that the renderer was successfully created
	if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }
	
	bool End = false;
	
	SDL_Event* event = new SDL_Event;//structure for handling events
	
	
	

	
	
	
	
	
	
	
	
	/*
	
	while (!End) {//main loop
		while (SDL_PollEvent(event)) {//read events from queue
			if (event->type == SDL_QUIT)
				End = true;	
			else if (event->type == SDL_KEYDOWN) { //if key is pressed
				switch (event->key.keysym.sym){ //choose the key
					case SDLK_UP: //if up arrow is pressed, we decrease delay by 10ms, but protect it from overfowing and getting stuck
									break;
					case SDLK_DOWN:						break;
					case SDLK_F1:		break;
					case SDLK_q:		End = true; break;

					}
			}

		}//end of reading event queue
		
	}//end of while loop
	
	
	
	*/
	
	
	int client_socket = 0;
	struct sockaddr_in server_address;
	char message;
	
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(client_socket < 0) {
		printf("\n Error : Could not create socket \n");
        return 1;
	}
	
	server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000);
	
	if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr)<=0) //assign address from argv
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

	if( connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
	
	while(true) {//network loop
	
		if(recv(client_socket, &message, sizeof(message),MSG_DONTWAIT) != -1) {	
		
		
		}
	}
	SDL_Delay(1000);
	return 0;
}