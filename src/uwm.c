#include "hwm.h"

typedef struct Client {
    Window window;
    struct Client* next;
} Client;

typedef struct WM {
    Display* display;
    Window root;
    Client* clients;
} WM;

void handleEvent(WM* wm, XEvent* event) {
    switch( event -> type) {
        case KeyPress:
            if (event -> xkey.keycode == XKeysymToKeycode(wm->display, XK_c) &&
                event -> xkey.state & Mod4Mask && event -> xkey.state & ShiftMask) {
                system("xterm &");
            }
            break;
        case MapRequest:
            {
                Client* client = malloc(sizeof(Client));
                client->window = event->xmaprequest.window;
                client->next = wm->clients;
                wm->clients = client;
            }
            break;
        case UnmapNotify:
            {
                Client* client = wm->clients;
                Client* prev = NULL;
                while(client) {
                    if (client->window == event->xunmap.window) {
                        if (prev) {
                            prev->next = client->next;
                        } else {
                            wm->clients = client->next;
                        }
                        free(client);
                        break;
                    }
                    prev = client;
                    client = client -> next;
                }
            }
            break;
    }
}

int main() {
    WM wm;
    wm.display = XOpenDisplay(NULL);
    if (!wm.display) {
        fprintf(stderr, "Nevozmojno otkrit display\n");
        return 1;
    }
    wm.root = RootWindow(wm.display, DefaultScreen(wm.display));
    wm.clients = NULL;

    XSelectInput(wm.display, wm.root, KeyPressMask | StructureNotifyMask);
    
    XEvent event;
    while (1) {
        XNextEvent(wm.display, &event);
        handleEvent(&wm, &event);
    }

    XCloseDisplay(wm.display);
    return 0;
}
