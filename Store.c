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
    c = redisConnect("localhost", 6739);
    if (c == NULL) {
        printf("Error: Failure when connecting to Redis server.\n");
        exit(1);
    }
    printf("Connected to Redis\n");
}

void store() {
    connectRedis();
}

int main() {
    store();
    return 0;
}