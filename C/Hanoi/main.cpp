//  This is a graphic implementation of the hanoi tower problem
//  using the graphics library provided by the course.

#include <graphics.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

using namespace std;

/******************************************************************************/
/*************************  CONSTANTS AND GLOBALS  ****************************/
#define MAX_DISKS 12
#define DEBUG 1

#define WIN_WIDTH 1000
#define WIN_HEIGHT 480

#define ANIMATION_DELAY 35
#define ANIMATION_STEPS 10

int num_disks;
int *pegs;
int top[3];

int base_disk_width = 30;
int border_offset = 10;
int peg_x_pos[3] = {WIN_WIDTH/5, WIN_WIDTH/2, WIN_WIDTH*4/5};

/******************************************************************************/
/*************************  FUNCTION PROTOTYPES  ******************************/

// Initializes the peg values
void init_pegs();

// Moves a disk from one peg to another
void pop_disk(int from, int to);

// Prints the current state of the pegs
void print_pegs();

// Solves the hanoi tower
void move(int n, int from, int aux, int to);

// For some reason getch() doesn't work correctly
// This function is a replacement
int stall();

// Shuffle the color palette of graphics.h
int pretty_color(int color);

// Draws the disk according to the peg it is on
void draw_disk(int n, int x, int y);

// Draws a peg
void draw_peg(int n);

// Call the other draw functions
void draw();

// Moves the disk from one peg to another *GRAPHICALLY*
void animate(int from, int to);

/******************************************************************************/
/**************************  FUNCTION DEFINITIONS  ****************************/

int main() {
	int gd = DETECT, gm;
	int done = 0;

	// clrscr();
	// initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
	initwindow(WIN_WIDTH, WIN_HEIGHT);

	do {
		// Choose the number of disks
		printf("Enter the number of disks:\n");
		if (DEBUG) {
			num_disks = 8;
			printf("DEBUG: Using Default Number of Disks\n");
		} else {
			scanf("%d", &num_disks);
		}

		if (num_disks > MAX_DISKS) {
			printf("Too many disks.\n");
			printf("Defaulting to %d disks.\n", MAX_DISKS);
			num_disks = MAX_DISKS;
		}

		// Initialize the pegs and draw.
		init_pegs();
		draw();
		// stall();

		// Move the disks
		move(num_disks, 0, 1, 2);

		// Wait for the user to choose an option
		printf("\n\nChoose an option: \n  0 to exit\n  1: to continue: \n");
		scanf("%d", &done);
	} while (done);

	// Close the graphics window
	free(pegs);
	getchar();
	closegraph();

	return 0;
}

/*********************************/
/************* LOGIC *************/

void init_pegs() {
	int i, j;
	// Allocate memory for the pegs
	pegs = (int *)calloc(num_disks, sizeof(int));

	// Fill the first peg with the disks, the other pegs with 0
	for (i = 0; i < num_disks; i++) {
		pegs[i] = num_disks - i;
	}
	// Fill the rest with -1
	for (i = num_disks; i < num_disks * 3; i++) {
		pegs[i] = -1;
	}

	// Initialize the top of the pegs
	top[0] = num_disks - 1;
	top[1] = -1;
	top[2] = -1;

	if (DEBUG) {
		print_pegs();
	}
}

void pop_disk(int from, int to) {
	if (DEBUG) {
		printf(
			"Popping disk %d from peg %d to peg %d\n",
			pegs[from * num_disks + top[from]], from, to
		);
		printf("to index: %d\n", (to * num_disks + top[to] + 1));
	}
	top[from]--; // Remove the disk from the top of the peg
	animate(from, to); // Animate the disk moving

	top[to]++; // Add it back in the new peg
	pegs[to * num_disks + top[to]] = pegs[(from * num_disks) + top[from] + 1];

	if (DEBUG) {
		print_pegs();
	}
}

void print_pegs() {
	int i, j;
	printf("\n");
	for (i = 0; i < 3; i++) {
		printf("Peg %d: ", i);
		for (j = 0; j <= top[i]; j++) {
			printf("%d ", pegs[i * num_disks + j]);
		}
		printf(".\n");
	}
	printf("\n");
}

void move(int n, int from, int aux, int to) {
	if (n == 1) {
		pop_disk(from, to);
		draw();
		stall();
	} else {
		// Recursive call
		// Move the top n-1 disks from peg 'from' to peg 'aux'
		move(n - 1, from, to, aux);

		pop_disk(from, to);
		draw();
		stall();

		// Move the top n-1 disks from peg 'aux' to peg 'to'
		move(n - 1, aux, from, to);
	}
}

int stall() {
	if (DEBUG) {
		Sleep(200);
	} else {
		Sleep(100);
		// printf("Press enter to continue.\n");
		// getchar();
		// Clear terminal
		system("cls");
	}
	return 0;
}

/*********************************/
/*********** Graphics ************/

int pretty_color(int color) {
	// Based on the graphics library color pallete
	// Excluding 0,7,8,15; BLACK, LIGHTGRAY, DARKGRAY, WHITE, respectively.
	// The pegs are brown, so that's excluded too.
	// Leaving only 11 colors
	color = (color % 11);

	switch (color)
	{
	case 0:
		return BLUE;
	case 1:
		return LIGHTBLUE;
	case 2:
		return CYAN;
	case 3:
		return LIGHTCYAN;
	case 4:
		return GREEN;
	case 5:
		return LIGHTGREEN;
	case 6:
		return YELLOW;
	case 7:
		return LIGHTRED;
	case 8:
		return RED;
	case 9:
		return LIGHTMAGENTA;
	case 10:
		return MAGENTA;
	default:
		return BLACK;
	}
}

void draw_disk(int peg, int n, int y) {
	int width = base_disk_width * n;
	int x = peg_x_pos[peg] - (width / 2);
	y = WIN_HEIGHT - ((y * base_disk_width) + border_offset);
	// Color is determined by n
	setcolor(pretty_color(n));
	setfillstyle(SOLID_FILL, pretty_color(n));

	// printf("Drawing disk %d on peg %d at x: %d, y: %d\n", n, peg, x, y);
	bar(
		x,
		y,
		x + width,
		y - base_disk_width
	);
}

void draw_peg(int n) {
	// int x = (WIN_WIDTH / 3) - border_offset;
	// x = border_offset + (x * n) + (x / 2);

	setcolor(BROWN);
	setfillstyle(SOLID_FILL, BROWN);

	// Draws a bar
	bar(
		peg_x_pos[n] - (base_disk_width / 4),
		border_offset + (WIN_HEIGHT/4),
		peg_x_pos[n] + (base_disk_width / 4),
		WIN_HEIGHT - border_offset
	);
}

void draw() {
	int i, j;
	// Paint the background
	setcolor(LIGHTGRAY);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(0, 0, WIN_WIDTH, WIN_HEIGHT);

	// Draw the pegs
	for (i = 0; i < 3; i++) {
		draw_peg(i);
	}

	// Draw the disks
	for (i = 0; i < 3; i++) {
		for (j = 0; j <= top[i]; j++) {
			draw_disk(i, pegs[i * num_disks + j], j);
		}
	}
}

void animate(int from, int to) {
	int i, delta, color, checkpoint;
	// int steps = 10;
	// int speed = 40; // ms per step
	int width = base_disk_width * pegs[from * num_disks + top[from] + 1];

	int initial[2] = {
		peg_x_pos[from] - (width / 2),
		WIN_HEIGHT - (((top[from] + 1) * base_disk_width) + border_offset)
	};
	int current[2] = {initial[0], initial[1]};
	int final[2] = {
		peg_x_pos[to] - (width / 2),
		WIN_HEIGHT - (((top[to] + 1) * base_disk_width) + border_offset)
	};

	if (DEBUG) {
		printf("Initial: %d, %d\n", initial[0], initial[1]);
		printf("Final: %d, %d\n", final[0], final[1]);
	}

	color = pretty_color(pegs[from * num_disks + top[from] + 1]);

	// THIS IS JUST HORRIBLE CODE
	// I'm sorry, I should have made it into a function,
	// but I don't even know how to do that in this case.
	// I'm just trying to get this to work.
	// First move the disk to the top of the peg
	delta = ((WIN_HEIGHT/5 - initial[1])/ANIMATION_STEPS);
	while (current[1] > WIN_HEIGHT/5) {
		current[1] = current[1] + delta;
		draw();
		setcolor(color);
		setfillstyle(SOLID_FILL, color);
		bar(
			current[0],
			current[1],
			current[0] + width,
			current[1] - base_disk_width
		);
		Sleep(ANIMATION_DELAY);
	}

	// Then move side to side
	delta = ((final[0] - initial[0])/ANIMATION_STEPS);
	if (delta > 0) {
		while (current[0] < final[0]) {
			current[0] = current[0] + delta;
			draw();
			setcolor(color);
			setfillstyle(SOLID_FILL, color);
			bar(
				current[0],
				current[1],
				current[0] + width,
				current[1] - base_disk_width
			);
			Sleep(ANIMATION_DELAY);
		}
	} else {
		while (current[0] > final[0]) {
			current[0] = current[0] + delta;
			draw();
			setcolor(color);
			setfillstyle(SOLID_FILL, color);
			bar(
				current[0],
				current[1],
				current[0] + width,
				current[1] - base_disk_width
			);
			Sleep(ANIMATION_DELAY);
		}
	}

	// Then move down again
	delta = ((final[1] - (WIN_HEIGHT/5))/ANIMATION_STEPS);
	while (current[1] < final[1] - base_disk_width) {
		current[1] = current[1] + delta;
		draw();
		setcolor(color);
		setfillstyle(SOLID_FILL, color);
		bar(
			current[0],
			current[1],
			current[0] + width,
			current[1] - base_disk_width
		);
		Sleep(ANIMATION_DELAY);
	}

}