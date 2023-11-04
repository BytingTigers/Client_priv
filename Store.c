// Function to:
// 1. Connect to redis database 
// 2. List all available emojis
// 3. Group the emojis
// 4. Send the emoji through the text/group chat
// 5. Add new emoji to the list (as a new menu called Custom)

#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

redisContext *c = NULL;
redisReply *replyEmoji;
redisReply *replyMenu;
redisReply *replyMain;
int menuNum = 0;

void connectRedis() {
    c = redisConnect("home.hokuma.pro", 6380);

    if (c == NULL) {
        printf("Error: Failure when connecting to Redis server.\n");
        exit(1);
    }
    // TODO: Delete after deployment and release
    redisCommand(c, "AUTH bytingtigers");
    printf("Connected to Redis...\n");
    redisCommand(c, "SELECT 3");
}

// Root name is emojis

void listMenus() {
    replyMenu = redisCommand(c, "KEYS *");
    printf("Available menus:\n");
    if (replyMenu->elements == 0) {
        printf("No menus available\n");
        return;
    }
    for (int i = 1; i < replyMenu->elements; i++) {
        printf("%d. %s\n", i, replyMenu->element[i]->str);
    }
    printf("0. Exit Emoji Store\n");
}

void listEmojis(char* menuName) {
    if (menuName != NULL) {
        printf("Menu name: %s\n", menuName);
        replyEmoji = redisCommand(c, "LRANGE a 0 -1");
        printf("Available emojis:\n");
        for (int i = 0; i < replyEmoji->elements; i++) {
            printf("%d. %s\n", i+1, replyEmoji->element[i]->str);
        }
    }
}

int main() {
    connectRedis();
    while (true) {
        listMenus();
        replyMain = redisCommand(c, "KEYS *");
        printf("Enter menu number: ");
        scanf("%d", &menuNum);
        if (menuNum == 0) {
            break;
        } else if (menuNum < 0) {
            printf("Invalid menu number\n");
            continue;
        } else if (menuNum > 0) {
            printf("Menu number: %d\n", menuNum);
            listEmojis(replyMain->element[menuNum]->str);
        }
    }
    
    return 0;
}