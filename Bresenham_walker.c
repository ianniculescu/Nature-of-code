#include<stdio.h>
#include<X11/Xlib.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<math.h>


struct coord{
signed int x, y;
}dot;

Display *dis;
Window win, win_root;
GC gc;
int scn_num;
int D;
int posx, posy, dx, dy, yi, xi;
char func;

void initHigh();
void initLow();
void drawHigh();
void drawLow();


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

usleep(10000);

XCheckWindowEvent(dis,win,PointerMotionMask | KeyPressMask,&event);
XFlush(dis);

if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
if(text[0] == 'q') {
quit();
}
printf("you pressed the %c key!\n", text[0]);
}
if(event.type == MotionNotify){

    //int posx = event.xbutton.x;
    //int posy = event.xbutton.y; 
    
    
    
    if(posx != event.xbutton.x || posy != event.xbutton.y){
    posx = event.xbutton.x;
    posy = event.xbutton.y;
    
    if(abs(posy - dot.y) < abs(posx - dot.x)){
    	if(dot.x > posx){
    	initLow(posx, posy, dot.x, dot.y);
    	func = 0;
    	}else{
    	initLow(dot.x, dot.y, posx, posy);
    	func = 1;
    	}
    	   
    }else{
    	if(dot.y > posy){
    	initHigh(posx, posy, dot.x, dot.y);
    	func = 2;
    	}else{
    	initHigh(dot.x, dot.y, posx, posy);
    	func = 3;
    	}
    	
    }
    
    printf("posx : %d, posy : %d, dot.x : %d, dot.y : %d, func : %d\n", posx, posy, dot.x, dot.y, func);   
    }
    
    
    switch(func){
    case 0 : drawLow(-1);
    break;
    case 1 : drawLow(1);
    break;
    case 2 : drawHigh(-1);
    break;
    case 3 : drawHigh(1);
    break;
    default : break;
    
    }
    
    

}

}

}

void init() {
dot.x = 0;
dot.y = 0;
posx = 0;
posy = 0;
dis = XOpenDisplay(NULL);
scn_num = DefaultScreen(dis);
win_root = RootWindow(dis, scn_num);
win = XCreateSimpleWindow(dis, win_root, 0, 0, 1000, 1000, 1, 0xffffff, 0x0000ff);
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



void initLow(int x0, int y0, int x1, int y1){
dx = x1 - x0;
dy = y1 - y0;
yi = 1;

if(dy < 0){
dy = -dy;
yi = -1;
} 
  
D = 2 * dy - dx;
    
}

void drawLow(int directon){

XDrawPoint(dis, win, gc, dot.x, dot.y);
    
if(D > 0) {
dot.y += yi * directon;
D += 2 * (dy - dx);
}else {
D += 2 * dy;
}
dot.x += directon;
}

void initHigh(int x0, int y0, int x1, int y1){
dx = x1 - x0;
dy = y1 - y0;
xi = 1;

if(dx < 0){
xi = -1;
dx = -dx;
}

D = 2 * dx - dy;

}

void drawHigh(int direction){

XDrawPoint(dis, win, gc, dot.x, dot.y);

if(D > 0){
dot.x += xi * direction;
D += 2 * (dx - dy);
}else{
D += 2 * dx;
}
dot.y += direction;
}


