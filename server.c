#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include <sys/wait.h>
#define PORT 5050
#define MAX_TRY 5

void play(int client, char *word, int id){
    int wordlen = strlen(word)+1;
    char clue[wordlen];
    int tries = MAX_TRY;
    char try[wordlen];
    memset(clue, '_', strlen(word));
    clue[strlen(word)] = '\0';
    printf("Server : send of the clue %s\n", clue);
    printf("Server : size of the clue sent \n");
    //we send the clue
    int lenClue = strlen(clue)+1;
    if(send(client, &lenClue, sizeof(int), 0)< 0){
        perror("Server : pb with the send of the lenclue");
        exit(EXIT_FAILURE);
    }
    if(send(client, clue, strlen(clue)+1,0) < 0){
        perror("Server : pb with the send of the clue");
        exit(EXIT_FAILURE);
    }
    printf("Server : clue sent \n");
    while(tries > 0){
        //Reception of the tries
        recv(client,try,wordlen,0);
        printf("Server : Client %d Try number %d : %s \n",id,MAX_TRY -(tries-1), try);
        int correct = 0;
        for(int i = 0; i < strlen(word); i++){
            if (word[i] == try[i] && clue[i] == '_'){
                clue[i] = word[i];
            }
        }
        if(strcmp(clue, word) == 0) {
            correct = 1;
            if(send(client,&correct, sizeof(int), 0) < 0){
                perror("Server : pb with the send of the end game : ");
            }
            break;
        }else{
            if(send(client,&correct, sizeof(int), 0) < 0){
                perror("Server : pb with the send of the end game : ");
            }
        }
        if(send(client,clue, wordlen, 0) < 0){
            perror("Server : pb with the send of the clue changed : ");
        }
        tries --;
    
        if(send(client,&tries, sizeof(int), 0) < 0){
            perror("Server : pb with the send of the number of tries");
        }
        printf("Server : Client %d has %d tries left \n", id, tries);
        
    }
    close(client);
}

int main(){
    int ds, player1_ds, player2_ds;
    ds = socket(PF_INET, SOCK_STREAM, 0);
    if (ds == -1){
        perror("Server : pb creation of the socket");
        exit(EXIT_FAILURE);
    }
    printf("Server : Socket created \n");
    struct sockaddr_in server_addr, client1_addr, client2_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons((short)PORT);

    socklen_t adrlen = sizeof(struct sockaddr_in);
    if(bind(ds, (struct sockaddr *) &server_addr,adrlen) < 0){
        perror("Server : error naming the socket ");
        exit(EXIT_FAILURE);
    }
    if(listen(ds,2) < 0){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting players ... \n");

    //Accept connections
    player1_ds = accept(ds, (struct sockaddr *)&client1_addr, &adrlen);
    printf("Server  : Player 1 connected \n");

    player2_ds = accept(ds, (struct sockaddr *)&client2_addr, &adrlen);
    printf("Server : Player 2 connected \n");

    int lenWord1;
    int lenWord2;
    if(recv(player1_ds, &lenWord1, sizeof(int),0) < 0){
        perror("Reception of lenght word of player 1");
        exit(EXIT_FAILURE);
    }
    printf("Server : Length word 1 : %d",lenWord1);
    if(recv(player2_ds, &lenWord2, sizeof(int),0) < 0){
        perror("Reception of lenght word of player 2");
        exit(EXIT_FAILURE);
    }
    printf("Server : Length word 2 : %d",lenWord2);

    char word1[lenWord1];
    char word2[lenWord2];
    if(recv(player1_ds,word1, lenWord1,0) < 0){
        perror("Reception of lenght word of player 1");
        exit(EXIT_FAILURE);
    }
    printf("Server : Player 1 word : %s\n",word1);
    if(recv(player2_ds, word2, lenWord2,0) < 0){
        perror("Reception of lenght word of player 1");
        exit(EXIT_FAILURE);
    }
    printf("Server : Player 2 word : %s\n",word2);

    pid_t pid = fork();
    if(pid == -1){
        perror("Server : error  in fork");
    }
    if(pid == 0){
        //Son process manages player 1
        play(player1_ds, word2, 1);
    }
    else{
        play(player2_ds,word1,2);
    }
    int status;
    waitpid(pid, &status, 0);  
    close(ds);
    return EXIT_SUCCESS;

}
