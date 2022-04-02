#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <string>

#include <stdio.h>
extern "C"{
    #include "eqsolver.h"
}



#define MAX_INPUT_LEN 80
#define MARGIN_OFFSET 12
#define BUTTON_NUMBER 27


/*****************************************************************************
 *                                  Graphics                                 *
 * **************************************************************************/

// Values inside a button.
struct button_data {
	char value[5];
	int color;
};

// An array of all the predefined values for buttons
struct button_data BUTTON_DATA[BUTTON_NUMBER+2]= {
	{"Back", BROWN},
	{"CE", BROWN},
	{"C", BROWN},
	{"MC", RED},
	{"MR", RED},
	{"MS", RED},
	{"M+", RED},
	{"7", BLUE},{"8", BLUE},{"9", BLUE},{"/", RED},{"(", BLUE},
	{"4", BLUE},{"5", BLUE},{"6", BLUE},{"*", RED},{")", BLUE},
	{"1", BLUE},{"2", BLUE},{"3", BLUE},{"-", RED},{"1/x", BLUE},
	{"0", BLUE},{"+/-", BLUE},{".", BLUE},{"+", RED},{"=", RED},
};
int button_counter = 0;


// A Button
struct button {
	int x;
	int y;
	int width;
	int height;
	char *value;
	int txtcolor;
	int color;
	bool inset;
	bool pressed;
};

// a list of pointers for all the buttons.
struct button button_list[BUTTON_NUMBER];

struct button screen = {
	MARGIN_OFFSET, MARGIN_OFFSET, 
	260-MARGIN_OFFSET, 27, 
	"\0", BLACK, WHITE, 
	true, false
};


// Draws a button, with no text for now
void add_button(int x, int y, int width, int height, int color, bool inset, bool text){
	char *buttontext= (char *)"\0";
	int txtcolor;
	if (text == true) {
		txtcolor = BUTTON_DATA[button_counter].color;
		buttontext = BUTTON_DATA[button_counter].value;
		button_counter++;
	};
	struct button new_button = {
		x,
		y,
		width,
		height,
		buttontext,
		txtcolor,
		color,
		inset,
		false
	};
	button_list[button_counter] = new_button;
	
}

// Draws multiple buttons
void add_buttons(int xoff, int yoff, int xcount, int ycount, int width, int height, int xspacing, int yspacing){
	int xpos;
	int ypos;
	for (int y = 0; y<ycount; y++){
		for	(int x = 0; x<xcount; x++){	
			xpos = (x*width)+xoff+xspacing*x;
			ypos = (y*height)+yoff+yspacing*y;
			add_button(
				xpos,
				ypos,
				width,
				height,
				LIGHTGRAY,
				false,
				true
			);
		}
	}
}

void draw_button_text(int x, int y, int width, int height, int color, char *text){
	setbkcolor(LIGHTGRAY); //textBG
	setcolor(color);
	outtextxy(x+6,y+6, text);
}

void draw_button(struct button *b){
	
//	 draw before the rectangle a white and a black square
//	 to give an illusion of depth
	int x = b->x;
	int y = b->y;
	int width = b->width;
	int height = b->height;
	int color = b->color;
	
//	printf("x:%d, y:%d", x,y);
//	printf("c:%d,\n", b->color);
	if (b->inset == false) {
		setcolor(WHITE);
		rectangle(x,y,x+width,y+1);
		rectangle(x,y,x+1,y+height);
		setcolor(DARKGRAY);
		line(x+width-1,y+1,x+width-1,y+height);
		line(x,y+height-1,x+width,y+height-1);
		setcolor(BLACK);
		line(x+width,y,x+width,y+height);
		line(x,y+height,x+width,y+height);
	} else {
		setcolor(WHITE);
		rectangle(x+width-1,y,x+width,y+height);
		rectangle(x,y+height-1,x+width,y+height);
		setcolor(BLACK);
		line(x,y,x+width,y);
		line(x,y,x,y+height);
		setcolor(DARKGRAY);
		line(x+1,y+1,x+width-1,y+1);
		line(x+1,y+1,x+1,y+height-1);
	
	}
//	printf("%s", color);
	setcolor(b->color);
	
	rectangle(x+2,y+2,x+width-2,y+height-2);
	setfillstyle(SOLID_FILL, b->color);
	floodfill(x+3,y+3,b->color);
	
	// Now the text
	draw_button_text(x,y,width,height, b->txtcolor, b->value);
}

// Fills the background with a color
void background(int color){
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	floodfill(1,1,color);
}

// Our main drawing funcion, called every update to fill the screen with things
void init(int x, int y){
	
	background(LIGHTGRAY);
	int offset=MARGIN_OFFSET;
	int yoffset=8;
	int xoffset=5;
	int height=27;
	int width=35;
	add_button(offset, offset, x-offset*2, height, WHITE, true, false); // Screen
	add_button(offset, offset*2+height, width, height, LIGHTGRAY, true, false); // Weird void square.
	
	add_buttons( //Back buttons
		offset*3+xoffset+width*2,
		offset*2+height,
		3,1,
		48, height,
		xoffset,
		yoffset
	);
	
	add_buttons( //Left buttons
		offset, 
		offset*3+height*2, 
		1, 4,
		width, height, 
		xoffset,
		yoffset
	); 
	add_buttons( //Main keyboard
		offset*3+width,
		offset*3+height*2, 
		5,4,
		width,height,
		xoffset,
		yoffset
	);
	
}

//void clean_screen(){
//	setcolor(RED);
//	int x, y, right, bottom;
//	x=MARGIN_OFFSET+2;
//	y=MARGIN_OFFSET+2;
//	right=260-MARGIN_OFFSET-2;
//	bottom= y +25;
//	rectangle(x,y,right,bottom);
//	setfillstyle(SOLID_FILL, WHITE);
//	floodfill(x+3,y+3,WHITE);
//}

void print_eq(char* equation, int color){
	if (color != WHITE){
		print_eq((char*)"------------", WHITE);
	}
	setcolor(color);
	setbkcolor(WHITE);
	outtextxy(MARGIN_OFFSET+6,MARGIN_OFFSET+6, equation);
}

void draw(){
	// Draw screen:
	
	draw_button(&screen);
	
	for (int i = 0; i <= BUTTON_NUMBER; i++) {
//		printf("%d", button_list[i].x);
		draw_button(&button_list[i]);
	}
}

int main()
{
	initwindow(276,236);
	printf("Window initialized...  ");
	init(276,236);
	printf("Buttons initialized...\n");
	setbkcolor(WHITE);
	draw();
	char *equation =(char *) malloc(MAX_INPUT_LEN);
	char *result =(char *) malloc(MAX_INPUT_LEN);
	do {
		printf("Write your desired equation to be solved\n");
		gets(equation);
	//	char* equation = "10+8/(2)+25*5";
		print_eq(equation, BLACK);
		result = solve(equation); // Magic
        delay(1000);// Suspence
		print_eq(result, BLACK);
	} while (equation!= "\0");

	getch();
	closegraph();
	return 0;
}





