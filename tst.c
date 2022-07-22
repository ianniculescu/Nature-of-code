#include<stdio.h>
#include<X11/Xlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

struct coord{
signed int x, y;
}dot;

Display *dis;
Window win, win_root;
GC gc;
int scn_num;
int D;
int posx, posy, dx, dy, yi, xi;

void initHigh();
void initLow();
void init();
void quit();
void draw();

int main() {

init();
XEvent event;
KeySym key;
char text[255];

while(1) {

//XDrawLine(dis, win, gc, 500, 500, 300, 300);
//XDrawArc(dis, win, gc, 490 + dot.x, 490 + dot.y, 20, 20, 0, 23040);

usleep(100);




//printf("dot.x is %d key!\n", dot.x);
//printf("dot.y is %d key!\n", dot.y);

XCheckWindowEvent(dis,win,PointerMotionMask | KeyPressMask,&event);
XFlush(dis);

if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
if(text[0] == 'q') {
quit();
}
printf("you pressed the %c key!\n", text[0]);
}

if(event.type == MotionNotify){
    
    int random = rand() % 800;
    printf("random : %i\n", random);
    if(random < 35){
    posx = event.xbutton.x;
    posy = event.xbutton.y;
    
    if(abs(posy - dot.y) < abs(posx - dot.x)){
    	if(dot.x > posx){
    	initLow(posx, posy, dot.x, dot.y, -1);
    	
    	}else{
    	initLow(dot.x, dot.y, posx, posy, 1);
    	
    	}
    	   
    }else{
    	if(dot.y > posy){
    	initHigh(posx, posy, dot.x, dot.y, -1);
    	
    	}else{
    	initHigh(dot.x, dot.y, posx, posy, 1);
    	
    	}
    	}
    	
}else{
int counter = 0;
	for(int i = 1; i < 4; ++i){
		for(int j = 1; j < 4; ++j){
			if(random < (++counter * 85 + 35)){
			dot.x += i - 2;
			dot.y += j - 2;
			printf("random : %d, i : %d, j : %d\n",random,i,j);
			goto out;
			}
		}
	}
	out : XDrawPoint(dis, win, gc,dot.x,dot.y);
	
}


}
}
}

void init() {
dot.x = 500;
dot.y = 500;
posx = 0;
posy = 0;

dis = XOpenDisplay(NULL);
scn_num = DefaultScreen(dis);
win_root = RootWindow(dis, scn_num);
win = XCreateSimpleWindow(dis, win_root, 0, 0, 1000, 1000, 1, 0xffffff, 0xFF6C19);
XSelectInput(dis, win, PointerMotionMask | KeyPressMask);
gc = XCreateGC(dis, win, 0, 0);
XMapWindow(dis,win);
}

void quit() {
XFreeGC(dis, gc);
XDestroyWindow(dis, win);
XCloseDisplay(dis);
exit(0);
}

void initLow(int x0, int y0, int x1, int y1,int direction){
dx = x1 - x0;
dy = y1 - y0;
yi = 1;

if(dy < 0){
dy = -dy;
yi = -1;
} 
  
D = 2 * dy - dx;

if(D > 0) {
dot.y += yi * direction;

    }
    dot.x += direction;
    XDrawPoint(dis, win, gc,dot.x,dot.y);
}

void initHigh(int x0, int y0, int x1, int y1, int direction){
dx = x1 - x0;
dy = y1 - y0;
xi = 1;

if(dx < 0){
xi = -1;
dx = -dx;
}

D = 2 * dx - dy;

if(D > 0){
dot.x += xi * direction;

   }
   dot.y += direction;
   XDrawPoint(dis, win, gc,dot.x,dot.y); 
}

