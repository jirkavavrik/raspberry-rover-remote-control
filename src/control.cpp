#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>//pton

#include <SDL2/SDL.h>

//size of window in pixels
int windowXSize = 300;
int windowYSize = 200;

SDL_Renderer* renderer;
SDL_Color color = {0,0,255,SDL_ALPHA_OPAQUE}; //default color blue

const char* infoMessage = "\ton the keyboard:\nW, A, S, D - driving\n\
F3 - camera on\n\
F4 - camera off\n\
arrows UP, DOWN - change speed\n\
spacebar - halt\n\n\
\tin the GUI:\n\
keypad: driving\n\
plus: increase speed\n\
minus: decrease speed\n\
rectangle: camera on\n\
cross: camera off\
";

int main(int argc, char *argv[]) {	
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* mainWindow = SDL_CreateWindow("RPi vehicle control", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowXSize, windowYSize, 0); //create window
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
	
	FILE *fp;
	char ip_address[255];
	//load IP from the file
	fp = fopen("ip.txt", "r");
	fgets(ip_address, 255, (FILE*)fp);
	printf("ip: %s\n", ip_address );
	fclose(fp);
	
	int client_socket = 0;
	struct sockaddr_in server_address;
	char message;
	
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(client_socket < 0) {
		printf("\n Error : Could not create socket \n");
        return 1;
	}
	
	server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
	
	if(inet_pton(AF_INET, ip_address, &server_address.sin_addr)<=0) //assign address from argv
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 
/*
	if( connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } */

	SDL_Color color = {0, 0, 255, SDL_ALPHA_OPAQUE};
	SDL_Rect rect = {0,0,0,0};
	SDL_SetRenderDrawColor(renderer, 127, 127, 127, SDL_ALPHA_OPAQUE);//background gray color
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	
	//keypad up
	rect.x = 127;
	rect.y = 10;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//keypad middle
	rect.x = 127;
	rect.y = 65;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//keypad down
	rect.x = 127;
	rect.y = 120;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//keypad left
	rect.x = 72;
	rect.y = 65;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//keypad right
	rect.x = 182;
	rect.y = 65;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//plus
	rect.x = 5;
	rect.y = 5;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//minus
	rect.x = 5;
	rect.y = 150;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//camera on
	rect.x = 250;
	rect.y = 5;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	//camera off
	rect.x = 250;
	rect.y = 150;
	rect.w = 45;
	rect.h = 45;
	SDL_RenderFillRect(renderer, &rect);
	
	color.r = 255;
	color.g = 255;
	color.b = 255;
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	//plus and minus
	SDL_RenderDrawLine(renderer, 27, 10, 27, 45);
	SDL_RenderDrawLine(renderer, 10, 27, 45, 27);
	SDL_RenderDrawLine(renderer, 10, 173, 45, 173);
	
	rect.x = 260;
	rect.y = 15;
	rect.w = 25;
	rect.h = 25;
	SDL_RenderDrawRect(renderer, &rect); //rectangle
	
	//cross
	SDL_RenderDrawLine(renderer, 260, 160, 285, 185);
	SDL_RenderDrawLine(renderer, 260, 185, 285, 160);
	
	//arrows
	SDL_RenderDrawLine(renderer, 137, 45, 150, 20);
	SDL_RenderDrawLine(renderer, 150, 20, 162, 45);
	
	SDL_RenderDrawLine(renderer, 137, 130, 150, 155);
	SDL_RenderDrawLine(renderer, 150, 155, 162, 130);
	
	SDL_RenderDrawLine(renderer, 107, 75, 82, 87);
	SDL_RenderDrawLine(renderer, 82, 87, 107, 100);
	
	SDL_RenderDrawLine(renderer, 192, 75, 217, 87);
	SDL_RenderDrawLine(renderer, 217, 87, 192, 100);
	
	SDL_RenderPresent(renderer); //update screen
	
	bool End = false;
	SDL_Event* event = new SDL_Event;//structure for handling events
	while (!End) {//main loop
		while (SDL_PollEvent(event)) {//read events from queue
			if (event->type == SDL_QUIT)
				End = true;	
			else if (event->type == SDL_KEYDOWN) { //if key is pressed
				switch (event->key.keysym.sym){ //choose the key
					case SDLK_F1:		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Help", infoMessage, mainWindow); break;
					case SDLK_F3:		send(client_socket, "X", 1, 0); break;
					case SDLK_F4:		send(client_socket, "x", 1, 0); break;
					case SDLK_q:		End = true; break;
					case SDLK_w:		send(client_socket, "F", 1, 0); break;
					case SDLK_a:		send(client_socket, "L", 1, 0); break;
					case SDLK_s:		send(client_socket, "B", 1, 0); break;
					case SDLK_d:		send(client_socket, "R", 1, 0); break;
					case SDLK_UP:		send(client_socket, "+", 1, 0); break;
					case SDLK_DOWN:		send(client_socket, "-", 1, 0); break;
					case SDLK_SPACE:	send(client_socket, "S", 1, 0); break;
					}
			} else if(event->type == SDL_KEYUP) {
				send(client_socket, "S", 1, 0); break;
			}  else if (event->type == SDL_MOUSEBUTTONDOWN) {
				int x, y = 0;
				SDL_GetMouseState(&x, &y);
				if (event->button.button == SDL_BUTTON_LEFT) {
					if(x >= 127 && x <= 127+45 && y >=10 && y <=  10+45) {
						send(client_socket, "F", 1, 0);
					} else if(x >= 127 && x <= 127+45 && y >=65 && y <=  65+45) {
						send(client_socket, "S", 1, 0);
					} else if(x >= 127 && x <= 127+45 && y >=120 && y <=  120+45) {
						send(client_socket, "B", 1, 0);
					} else if(x >= 72 && x <= 72+45 && y >=65 && y <=  65+45) {
						send(client_socket, "L", 1, 0);
					} else if(x >= 182 && x <= 182+45 && y >=65 && y <=  65+45) {
						send(client_socket, "R", 1, 0);
					} else if(x >= 5 && x <= 5+45 && y >=5 && y <=  5+45) {
						send(client_socket, "+", 1, 0);
					} else if(x >= 5 && x <= 5+45 && y >=150 && y <=  150+45) {
						send(client_socket, "-", 1, 0);
					} else if(x >= 250 && x <= 250+45 && y >=5 && y <=  5+45) {
						send(client_socket, "X", 1, 0);
					} else if(x >= 250 && x <= 250+45 && y >=150 && y <=  150+45) {
						send(client_socket, "x", 1, 0);
					}
				} else if (event->button.button == SDL_BUTTON_RIGHT) {
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Help", infoMessage, mainWindow); break;
				}
			} else if (event->type == SDL_MOUSEBUTTONUP) {
				send(client_socket, "S", 1, 0);
			}
		}//end of reading event queue
		if(recv(client_socket, &message, sizeof(message),MSG_DONTWAIT) != -1) {	
			
		}
	}//end of while loop		
	send(client_socket, "0", 1, 0);//send disconnect notice
	SDL_Delay(500);
	close(client_socket);
	SDL_Delay(500);
	return 0;
}