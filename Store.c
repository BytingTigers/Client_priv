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

redisContext *c = NULL;

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

// Root name is emoji_store

// Types of emojis:
// 1. Happy
// 2. Sad
// 3. Angry
// 4. Custom

void listMenus() {
    redisReply *reply;

    reply = redisCommand(c, "KEYS *");
    printf("Available menus:\n");
    if (reply->elements == 0) {
        printf("No menus available\n");
        return;
    }
    for (int i = 0; i < reply->elements; i++) {
        printf("%s\n", reply->element[i]->str);
    }

    // reply = redisCommand(c, "LRANGE menus 0 4");
    // printf("Available menus:\n");
    // if (reply->elements == 0) {
    //     printf("No menus available\n");
    //     return;
    // }
    // for (int i = 0; i < reply->elements; i++) {
    //     printf("%s\n", reply->element[i]->str);
    // }
}

// void listEmojis(int menutNum) {
//     redisReply *reply;
//     reply = redisCommand(c, "LRANGE %d 0 -1", menuNum);
//     printf("Available emojis:\n");
//     for (int i = 0; i < reply->elements; i++) {
//         printf("%s\n", reply->element[i]->str);
//     }

int main() {
    connectRedis();
    listMenus();
    return 0;
}