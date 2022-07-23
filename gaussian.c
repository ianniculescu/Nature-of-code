#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<X11/Xlib.h>

Display *dis;
Window win, win_root;
GC gc;

int scn_num;

double max = (double)RAND_MAX;
double max2 = (double)RAND_MAX/2;
double top, bottom = 0;
double z0, z1;
int arr[1000];

void gauss();
void init();
void quit();





int main(){

for(int i = 0; i < 1000; ++i){
arr[i] = 900;
}
srand(time(0));

init();
XEvent event;
KeySym key;
char text[255];


for(int i = 0; i < 100000; ++i){

gauss();
printf("z0 : %.4f, z1 : %.4f\n", z0, z1);
int a = z0 * 200 + 500;
int b = z1 * 200 + 500;
if(a < 1000 && a > 0){
--arr[a];
}
if(b < 1000 && b > 0){
--arr[b];
}


XDrawPoint(dis, win, gc,a ,arr[a] - 50);
XDrawPoint(dis, win, gc,b ,arr[b] - 50);


printf("a : %d\n",a);
printf("b : %d\n",b);

XCheckWindowEvent(dis,win,PointerMotionMask | KeyPressMask,&event);

if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
if(text[0] == 'q') {
quit();
}
printf("you pressed the %c key!\n", text[0]);
}

XFlush(dis);

usleep(10);
}



while(1){

XCheckWindowEvent(dis,win,PointerMotionMask | KeyPressMask,&event);

if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
if(text[0] == 'q') {
quit();
}
printf("you pressed the %c key!\n", text[0]);
}

if(event.type == MotionNotify){

}


XFlush(dis);
}

return 0;
}

void gauss() {

double s = 0;
double u = 0;
double v = 0;
do {
u = (rand() - max2)/max2;
v = (rand() - max2)/max2;
s = u * u + v * v;

}while (s >= 1 || s == 0);

z0 = u * sqrt(-2 * log(s)/s);
z1 = v * sqrt(-2 * log(s)/s);

}

void init() {

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


