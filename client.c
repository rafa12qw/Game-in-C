#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 5050

int main(int argc, char  *argv[]) {
    if(argc != 2){
        printf("Use : %s IP_SERVER\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //Creation of the socket
    int ds = socket(PF_INET, SOCK_STREAM, 0);

    if (ds == -1){
        perror("Client : pb socket creation");
        exit(EXIT_FAILURE);
    }
    printf("Client : Socket created \n");

    //Create server connection

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);
    server_addr.sin_port = htons((short) PORT);

    socklen_t lenA = sizeof(struct sockaddr_in);
    
    if(connect(ds, (struct sockaddr *)&server_addr, lenA) == -1){
        perror("Client : Connection failed : ");
        exit(EXIT_FAILURE);
    }
    char word[1024];
    int tries;
    printf("Client : give a word to guess : \n");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';
    int lenWord = strlen(word)+1;
    if(send(ds, &lenWord, sizeof(int),0) < 0){
        perror("Client : send of length of word failed : ");
        exit(EXIT_FAILURE);
    }
    if(send(ds, word, lenWord,0) < 0){
        perror("Client : send of word failed : ");
        exit(EXIT_FAILURE);
    }
    int lenClue; 
    if(recv(ds, &lenClue, sizeof(int),0) < 0){
        perror("Client : reception of clue : ");
        exit(EXIT_FAILURE);
    }
    char clue[lenClue];
    if(recv(ds, clue, lenClue,0) < 0){
        perror("Client : reception of clue : ");
        exit(EXIT_FAILURE);
    }
    printf("Client :Clue received \n");
    while(1){
        int isCorrect;
        char try[lenClue];
        printf("Client : Guess the word:\n %s \n",clue);
        fgets(try, lenClue, stdin);
        word[strcspn(word, "\n")] = '\0';
        if(send(ds, try, lenClue,0) < 0){
            perror("Client : send of try ");
            exit(EXIT_FAILURE);
        }
        if(recv(ds, &isCorrect, sizeof(int),0) < 0){
            perror("Client : error receiving the status of the game :");
            exit(EXIT_FAILURE);
        };
        printf("isCorrect %d \n", isCorrect);
        if(isCorrect == 1){
            printf("Congratulations, you have won \n");
            break;
        }
        if(recv(ds, clue, lenClue,0) < 0){
            perror("Client : error receiving the clue :");
            exit(EXIT_FAILURE);
        }
        if(recv(ds, &tries,sizeof(int),0) < 0){
            perror("Client : error receiving the number of tries : ");
            exit(EXIT_FAILURE);
        }
        if(tries == 0){
            printf("Sorry!! You have lost the game\n");
            break;
        }
    }
    close(ds);
    return EXIT_SUCCESS;
}