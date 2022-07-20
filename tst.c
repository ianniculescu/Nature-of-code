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
XDrawPoint(dis, win, gc, 500 + dot.x, 500 + dot.y); 
usleep(100);

dot.x += rand()%3-1;
dot.y += rand()%3-1;

printf("dot.x is %d key!\n", dot.x);
printf("dot.y is %d key!\n", dot.y);
XFlush(dis);
//XNextEvent(dis, &event);
if(event.type == Expose && event.xexpose.count == 0) {

draw();
}

if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
//XDrawLine(dis, win, gc, 500, 0, 500, 300);
if(text[0] == 'q') {
quit();
}
printf("you pressed the %c key!\n", text[0]);
}

}
}

void init() {
dot.x = 0;
dot.y = 0;

dis = XOpenDisplay(NULL);
scn_num = DefaultScreen(dis);
win_root = RootWindow(dis, scn_num);
win = XCreateSimpleWindow(dis, win_root, 0, 0, 1000, 1000, 1, 0xffffff, 0x0000ff);
XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
gc = XCreateGC(dis, win, 0, 0);
XMapWindow(dis,win);
}

void quit() {
XFreeGC(dis, gc);
XDestroyWindow(dis, win);
XCloseDisplay(dis);
exit(0);
}

void draw() {
XClearWindow(dis, win);
}


