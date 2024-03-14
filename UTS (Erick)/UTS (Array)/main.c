#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[50];
    char plays[20];
    char artist[50];
    char duration[5];
} Song;

typedef struct {
    Song data[50];
    int front, rear;
} Queue;

typedef struct {
    char username[24];
    char password[24];
} Profile;


void enqueued_Playlist(Queue *queue, Song song) {
    int MAX_SONGS = 50;
    if (queue->rear == MAX_SONGS - 1) {
        printf("Queue is full\n");
        return;
    }
    queue->rear++;
    queue->data[queue->rear] = song;
}

void dequeued_Playlist(Queue *queue) {
    if (queue->front == queue->rear) {
        printf("Playlist is empty\n");
        return;
    }

    printf("\nFirst song has been played\n");
    printf("Dequeueing song....,:\n\n");
    printf("Dequed song:\n");
    printf("Title: %s\n", queue->data[queue->front + 1].title);
    printf("Plays: %s\n", queue->data[queue->front + 1].plays);
    printf("Artist: %s\n", queue->data[queue->front + 1].artist);
    printf("Duration: %s\n\n", queue->data[queue->front + 1].duration);

    queue->front++;
    printf("Song dequeued from playlist.\n");
}

void print_Queue(Queue *queue) {
    printf("\n-----------------------------------------------------------------------------------------------------\n");
    printf("| Title                          | Plays               | Artist                        | Duration   |\n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    for (int i = queue->front + 1; i <= queue->rear; i++) {
        printf("| %-31s| %-20s| %-30s| %-10s |\n", queue->data[i].title, queue->data[i].plays, queue->data[i].artist, queue->data[i].duration);
    }
    printf("-----------------------------------------------------------------------------------------------------\n");

}

void read_Playlist(const char *filename, Queue *queue) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Playlist File not found!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char title[50], plays[20], artist[50], duration[5];
        sscanf(line, " %[^#]#%[^#]#%[^#]#%s", title, plays, artist, duration);
        Song song;
        strcpy(song.title, title);
        strcpy(song.plays, plays);
        strcpy(song.artist, artist);
        strcpy(song.duration, duration);
        enqueued_Playlist(queue, song);
    }

    fclose(file);

}

void add_Playlist(Queue *queue) {
    int MAX_SONGS = 50;
    if (queue->rear == MAX_SONGS - 1) {
        printf("Playlist is full\n");
        return;
    }

    Song newSong;
    printf("Enter song details:\n");
    printf("Title: ");
    scanf(" %[^\n]", newSong.title);
    printf("Artist: ");
    scanf(" %[^\n]", newSong.artist);
    printf("Plays: ");
    scanf(" %[^\n]", newSong.plays);
    printf("Duration: ");
    scanf(" %[^\n]", newSong.duration);
    enqueued_Playlist(queue, newSong);
    printf("Song added to playlist.\n");

    FILE *file = fopen("playlist.txt", "a");
    if (!file) {
        printf("Error: Unable to open file for appending\n");
        return;
    }

    fprintf(file, "%s#%s#%s#%s\n", newSong.title, newSong.plays, newSong.artist, newSong.duration);
    fclose(file);
}
void read_Profile(const char *filename, Profile *profile) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Profile file not found!\n");
        return;
    }
    fscanf(file, "%[^#]#%s", profile->username, profile->password);
    fclose(file);
}

void change_Profile(Profile *profile) {
    printf("Enter new username: ");
    scanf("%s", profile->username);
    printf("Enter new password: ");
    scanf("%s", profile->password);

    FILE *file = fopen("profile.txt", "w");
    if (!file) {
        printf("Error: Unable to open file for writing\n");
        return;
    }

    fprintf(file, "%s#%s\n", profile->username, profile->password);
    fclose(file);
}


int main() {
    Profile profile;
    int choice;
    int sub_Choice1;
    int sub_Choice2;
    int language_Choice;
    char input_Password[24];
    Queue songQueue = { .front = -1, .rear = -1 };
    read_Playlist("playlist.txt", &songQueue);
    read_Profile("profile.txt", &profile);

    printf("//NOTES: The Initial Password is Password\n");
    printf("//NOTES: Password awal adalah Password\n");

    do {
        printf("Password:");
        scanf("%s", input_Password);

        if (strcmp(input_Password, profile.password) != 0) {
            printf("try again.\n\n");
        }
    } while (strcmp(input_Password, profile.password) != 0);

        do {
            printf("\nLanguage:\n");
            printf("1. English\n");
            printf("2. Indonesian\n");
            printf("Choice: ");
            scanf("%d", &language_Choice);

            switch (language_Choice) {
                case 1:
                    do {
                        printf("\nWelcome, %s\n", profile.username);
                        printf("Menu:\n");
                        printf("1. Show Songs\n");
                        printf("2. Add to Playlist\n");
                        printf("3. Remove from Playlist\n");
                        printf("4. Favorites\n");
                        printf("5. Search by Artist\n");
                        printf("6. Profile\n");
                        printf("7. Exit\n");
                        printf("Choice: ");
                        scanf("%d", &choice);

                        switch(choice) {
                            case 1:
                                printf("\n1. Default\n");
                                printf("2. Sort Alphabetically\n");
                                printf("Choice:");
                                scanf("%d", &sub_Choice1);
                                switch(sub_Choice1){
                                    case 1:
                                        print_Queue(&songQueue);
                                    break;
                                    case 2:
                                    break;
                                }
                                break;
                            case 2:
                                add_Playlist(&songQueue);
                                break;
                            case 3:
                                dequeued_Playlist(&songQueue);
                                break;
                            case 4:
                                break;
                            case 5:
                                break;
                            case 6:
                                printf("\nYour current Username is %s\n", profile.username);
                                printf("Your current Password is %s\n", profile.password);
                                printf("1. Change Username and Password\n");
                                printf("2. Cencel\n");
                                printf("Choice:");
                                scanf("%d", &sub_Choice2);
                                switch(sub_Choice2){
                                    case 1:
                                        change_Profile(&profile);
                                        printf("Profile updated successfully.\n");
                                        break;
                                    case 2:
                                    break;
                                }
                                break;
                            case 7:
                                return 0;
                            default:
                                printf("Invalid choice!!!\n");
                        }
                    } while(choice != 9);
                case 2:
                    break;
            }
        } while (language_Choice < 1 || language_Choice > 2);

    return 0;
}
