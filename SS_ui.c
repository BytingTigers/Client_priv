#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char userID[20] = "";
char password[20] = "";
bool exit_flag = false;
char message[BUFFER_SIZE];

void init_scr(){
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    curs_set(1);
    noecho();
    keypad(stdscr, TRUE);

    int windowHeight = 30;
    int windowWidth = 80;
    if(LINES < windowHeight || COLS < windowWidth){
	    endwin();
	    printf("Screen is too small. Minimum size required: %d x %d\n", windowHeight, windowWidth);
	    exit(1);
    }

    WINDOW *mainwin = newwin(windowHeight, windowWidth, 0, 0);

    if(mainwin == NULL){
    	endwin();
	printf("Error creting the main window.\n");
	exit(1);
    }

    refresh();

}

void regis(){
    memset(userID, 0, 20);
    memset(password, 0, 20);
    int key;
    int userIDCursorPosition = 12;
    int userPWCursorPosition = 12;

    WINDOW *regis_window = newwin(10, 35, 13, 28);
    wbkgd(regis_window, COLOR_PAIR(2));
    wrefresh(regis_window);
    mvwprintw(regis_window, 3, 2, "user ID :\n");
    mvwprintw(regis_window, 6, 2, "password :\n");
    mvwprintw(regis_window, 1, 13, "register");
    wrefresh(regis_window);
    refresh();

    while(1){
        key = getch();

	if(key == KEY_F(1)){
		exit_flag = true;
		break;
	}
	if(key == '\n')
		break;
	if(key == KEY_BACKSPACE || key == 127 || key == '\b'){
	    if(userIDCursorPosition > 12){
	        userIDCursorPosition--;
		mvwprintw(regis_window, 3, userIDCursorPosition, " ");
		wrefresh(regis_window);
	    }
	}
	if(key >= 32 && key <= 126){
	    if(userIDCursorPosition < 30){
	        mvwaddch(regis_window, 3, userIDCursorPosition, key);
		wrefresh(regis_window);
		userIDCursorPosition++;
	    }
	}
    }
    if(exit_flag)
	    return;
    
    while(1){
	key = getch();

        if(key == KEY_F(1)){
		exit_flag = true;
		break;
	}
	if(key == '\n')
		break;
	if(key == KEY_BACKSPACE || key == 127 || key == '\b'){
	    if(userPWCursorPosition > 12){
	        userPWCursorPosition--;
		mvwprintw(regis_window, 6, userPWCursorPosition, " ");
		wrefresh(regis_window);
	    }
	}
	if(key >= 32 && key <= 126){
	    if(userPWCursorPosition < 30){
	        mvwaddch(regis_window, 6, userPWCursorPosition, key);
		wrefresh(regis_window);
		userPWCursorPosition++;
	    }
	}
    }
    if(exit_flag)
	    return;
    wclear(regis_window);
    mvwprintw(regis_window, 3, 10, "registered!");
    mvwprintw(regis_window, 4, 8, "Press Enter to login");
    wrefresh(regis_window);

    while(1){
    	key = getch();

	if(key == KEY_F(1)){
		exit_flag = true;
		break;
	}
	if(key == '\n'){
		delwin(regis_window);		
		break;
	}
    }
    if(exit_flag)
	    return;
}

void login(){
    memset(userID, 0, 20);
    memset(password, 0, 20);
    bool flag = false;
    int key;
    int userIDCursorPosition = 12;
    int userPWCursorPosition = 12;

    WINDOW *login_window = newwin(10, 35, 13, 28);
    wbkgd(login_window, COLOR_PAIR(2));
    wrefresh(login_window);

    mvwprintw(login_window, 3, 2, "user ID :\n");
    mvwprintw(login_window, 6, 2, "password :\n");
    wrefresh(login_window);

    while(1){
	flag = false;
        key = getch();

        if(key == KEY_F(1)){
            exit_flag = true;
	    break;
        }
	if(key == KEY_F(2)){
		regis();
		memset(userID, 0, 20);
		memset(password, 0 ,20);
		userIDCursorPosition = 12;
		userPWCursorPosition = 12;
		wclear(login_window);
		mvwprintw(login_window, 3, 2, "user ID :\n");
		mvwprintw(login_window, 6, 2, "password :\n");
		wrefresh(login_window);
		continue;
	}
	if(key == '\n'){
		while(1){
			key = getch();

			if(key == KEY_F(1)){
				exit_flag = true;
				break;
			}
			if(key == KEY_F(2)){
				regis();
				memset(userID, 0, 20);
				memset(password, 0, 20);
				userIDCursorPosition = 12;
				userPWCursorPosition = 12;
				wclear(login_window);
				mvwprintw(login_window, 3, 2, "user ID :\n");
				mvwprintw(login_window, 6, 2, "password :\n");
				wrefresh(login_window);
				flag = true;
				break;
			}
			if(key == '\n')
				break;
			if(key == KEY_BACKSPACE || key == 127 || key == '\b'){
				if(userPWCursorPosition > 12){
					userPWCursorPosition--;
					mvwprintw(login_window, 6, userPWCursorPosition, " ");
					wrefresh(login_window);
					password[userPWCursorPosition - 12] = '\0';
				}
			}
			if(key >= 32 && key <= 126){
				if(userPWCursorPosition < 30){
					mvwaddch(login_window, 6, userPWCursorPosition, '*');
					wrefresh(login_window);
					password[userPWCursorPosition - 12] = key;
					userPWCursorPosition++;
				}
			}

		}
		if(exit_flag)
			break;
		if(flag){
			continue;
		}
		else{
			break;
		}
	}
	if(exit_flag)
		break;
	if(key == KEY_BACKSPACE || key == 127 || key == '\b'){
		if(userIDCursorPosition > 12){
			userIDCursorPosition--;
			mvwprintw(login_window, 3, userIDCursorPosition, " ");
			wrefresh(login_window);
			userID[userIDCursorPosition - 12] = '\0';
		}
	}
	if(key >= 32 && key <= 126){
		if(userIDCursorPosition < 30){
			mvwaddch(login_window, 3, userIDCursorPosition, key);
			wrefresh(login_window);
			userID[userIDCursorPosition - 12] = key;
			userIDCursorPosition++;
		}
	}
    }
}

void menu_window(){

    attron(A_BOLD);
    mvprintw(2, 2, "1. chat");
    mvprintw(4, 2, "2. help");
    mvprintw(6, 2, "3. user info");
    mvprintw(8, 2, "4. exit");
    attroff(A_BOLD);
    refresh();
}

void chat_list(){
    clear();
    attron(A_BOLD);
    mvprintw(2, 2, "Room 1");
    mvprintw(4, 2, "Room 2");
    mvprintw(6, 2, "Room 3");
    mvprintw(8, 2, "Room 4");
    mvprintw(10, 2, "Room 5");
    attroff(A_BOLD);
    mvprintw(28, 70, "Press F1 to quit");
    refresh();
}

void room(int room_num){
    clear();
    attron(A_BOLD);
    move(1, 1);
    printw("Room %d", room_num);    
    refresh();
}

void show_bar(WINDOW *bar){
    wclear(bar);
    mvwprintw(bar, 0, 0, ">");
    wrefresh(bar);
}

void emoji(){
    WINDOW *emoj = newwin(15, 45, 2, 35);
    wbkgd(emoj, COLOR_PAIR(2));
    wrefresh(emoj);
    int key;
    while(1){
        key = getch();

	if(key == KEY_F(1)){
	    delwin(emoj);
	    touchwin(stdscr);
	    refresh();
	    break;
	}
    }
}

void chat(int room_num){
    WINDOW *chat_bar = newwin(1, 60, 30, 0);    
    wrefresh(chat_bar);

    room(room_num);
    show_bar(chat_bar);

    int key;
    int inputCursor = 1;

    while(1){
        key = getch();
	
	if(key == KEY_F(1))
		break;
	if(key == KEY_F(2)){
		emoji();
		show_bar(chat_bar);
	}
	if(key == '\n'){
		mvprintw(11, 11, message);
		wclear(chat_bar);
		mvwprintw(chat_bar, 0, 0, ">");
		wrefresh(chat_bar);
		inputCursor = 1;
		memset(message, 0, BUFFER_SIZE);
	}
	if(key == KEY_BACKSPACE || key == 127 || key == '\b'){
		if(inputCursor > 1){
			inputCursor--;
			mvprintw(30, inputCursor, " ");
			refresh();
			message[inputCursor - 1] = '\0';
		}
	}
	if(key >= 32 && key <= 126){
		if(inputCursor < 70){
			mvaddch(30, inputCursor, key);
			refresh();
			message[inputCursor - 1] = key;
			inputCursor++;
		}
	}
    }
}

int main(){
    init_scr();
    int key;
    bkgd(COLOR_PAIR(1));

    move(10,40);
    attron(A_BOLD);
    printw("BytingTigers\n");
    attroff(A_BOLD);
    move(27, 70);
    printw("Press F1 to quit\n");
    move(28,70);
    printw("press F2 to register\n");
    refresh();


    while(1){
	login();
	if(exit_flag)
		break;
	if(strcmp(userID, "root") == 0 && strcmp(password, "pass") == 0){
		break;
	}
	else{
		WINDOW *login_fail = newwin(10,35,13,28);
		wbkgd(login_fail, COLOR_PAIR(2));
		wrefresh(login_fail);
		mvwprintw(login_fail, 4, 10, "Login failed!");
		mvwprintw(login_fail, 5, 6, "Press Enter to retry");
		wrefresh(login_fail);
		key = getch();
		if(key == '\n')
			continue;
	}
    }

    if(exit_flag){
    	endwin();
        return 0;
    }


    clear();
    menu_window();
   
   while(1){
   	key = getch();
	if(key == KEY_F(1)){
		exit_flag = true;
		break;
	}
	if(key == 49){
	    while(1){
	        chat_list();
		key = getch();
			
		if(key == KEY_F(1)){
		    clear();
		    menu_window();
		    break;
		}
		if(key == 49){
		    chat(1);
		}
		if(key == 50){
		    chat(2);
		}
		if(key == 51){
		    chat(3);
		}
		if(key == 52){
		    chat(4);
		}
		if(key == 53){
		    chat(5);
		}
	    }
	}
	if(key == 50){
	    WINDOW *des_window = newwin(15, 45, 2, 35);
	    wbkgd(des_window, COLOR_PAIR(2));
	    mvwprintw(des_window, 2, 2, "description");
	    mvwprintw(des_window, 13, 15, "Press F2 to close this window");
	    wrefresh(des_window);

	    while(1){
	        key = getch();

		if(key == KEY_F(2)){
		    delwin(des_window);
		    touchwin(stdscr);		    
		    refresh();
		    break;
		}			
	    }
	}
	if(key == 51){
	    WINDOW *info_window = newwin(15, 45, 2, 35);
	    wbkgd(info_window, COLOR_PAIR(2));
	    mvwprintw(info_window, 2, 2, "user info");
	    mvwprintw(info_window, 13, 15, "Press F2 to close this window");
	    mvwprintw(info_window, 4, 2, "user ID :");
	    mvwprintw(info_window, 6, 2, "password :");
	    mvwprintw(info_window, 4, 12, userID);
	    mvwprintw(info_window, 6, 12, password);
	    wrefresh(info_window);

	    while(1){
	        key = getch();

		if(key == KEY_F(2)){		    
		    delwin(info_window);
		    touchwin(stdscr);
		    refresh();
		    break;
		}
	    }
	}
	if(key == 52){
	    exit_flag = true;
	    break;
	}
   }
   if(exit_flag)
	   endwin();
   endwin();
}
