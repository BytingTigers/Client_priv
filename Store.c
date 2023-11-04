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

#define MAX_EMOJI_LENGTH 10

redisContext *c = NULL;
redisReply *replyEmoji;
redisReply *replyMain;
redisReply *replyAddEmoji;
char *selectedEmoji;
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

char* listEmojis() {
    printf("Select your emoji choice: \n");
    replyEmoji = redisCommand(c, "LRANGE emojis 0 -1");
    for (int i = 0; i < replyEmoji->elements; i++) {
        printf("%d. %s\n", i+1, replyEmoji->element[i]->str);
    }
    printf("\nSelected emoji number: ");
    int emojiNum = 0;
    scanf("%d", &emojiNum);
    while (true) {
        if (emojiNum > replyEmoji->elements || emojiNum < 1) {
            printf("Invalid input. Please try again.\n\n\n");
            printf("Select your emoji choice: \n");
            replyEmoji = redisCommand(c, "LRANGE emojis 0 -1");
            for (int i = 0; i < replyEmoji->elements; i++) {
                printf("%d. %s\n", i+1, replyEmoji->element[i]->str);
            }
            printf("\nSelected emoji number: ");
            scanf("%d", &emojiNum);
        } else {
            selectedEmoji = replyEmoji->element[emojiNum-1]->str;
            break;
        }
    }
    return selectedEmoji;
}

void addEmoji() {
    char newEmoji[MAX_EMOJI_LENGTH];
    printf("Enter your new emoji: ");
    scanf("%s", newEmoji);
    replyAddEmoji = redisCommand(c, "RPUSH emojis %s", newEmoji);
    printf("New emoji added!\n");
}

int main() {
    connectRedis();
    while (true) {
        printf("Enter menu number: \n");
        printf("1. Get Existing Emoji\n");
        printf("2. Add New Emoji\n");
        printf("3. Exit\n");
        printf("\nSelected menu: ");
        scanf("%d", &menuNum);
        if (menuNum == 1) {
            char *result = listEmojis();
            if (result == "") {
                exit(1);
            } else {
                printf("Selected emoji: %s\n", result);
                break;
            }
        } else if (menuNum == 2) {
            addEmoji();
        } else if (menuNum == 3) {
            exit(1);
        } else {
            printf("Invalid input. Please try again.\n\n\n");
        }
    }
    
    return 0;
}