#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PLAYERS 10
#define MAX_NAME_LENGTH 50
#define MAX_QUESTIONS 10
#define QUESTION_TIME_LIMIT 30
#define LEADERBOARD_FILE "leaderboard.txt"

//Nama: Mochammad Syarif Triardiasya
//Kelas : LD75
//Kelas LAB: BH75
//Project Game Binus Bandung

typedef struct {
    char name[MAX_NAME_LENGTH];
    float score;
} Player;

typedef struct {
    char question[100];
    char options[4][50];
    char correctOption;
} Question;

Player players[MAX_PLAYERS];
int currentPlayerIndex = 0;

// Function declarations
void displayMenu();
void startQuizRecursive();
void displayLeaderboard();
void searchLeaderboard();
void resetLeaderboard();
void saveGame();
void saveLeaderboard();
void loadLeaderboard();
void bubbleSort(Player players[], int n);
void displayQuestions();
int askQuestion(Question question);

int main() {
    char choice;

    loadLeaderboard();

    do {
        displayMenu();
        printf("\nEnter your choice: ");
        scanf(" %c", &choice);
        printf("==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==");

        switch (toupper(choice)) {
            case 'A':
                startQuizRecursive();
                break;
            case 'B':
                displayLeaderboard();
                break;
            case 'S':
                searchLeaderboard();
                break;
            case 'C':
                resetLeaderboard();
                break;
            case 'D':
                saveLeaderboard();
                saveGame();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (toupper(choice) != 'D');

    return 0;
}

void displayMenu() {
    printf("\n**********************************************\n");
    printf("*          Welcome to Quiz Game              *\n");
    printf("**********************************************\n");
    printf("*                                            *\n");
    printf("*     > Press A to start the quiz            *\n");
    printf("*     > Press B to view the leaderboard      *\n");
    printf("*     > Press S to search the leaderboard    *\n");
    printf("*     > Press C to reset the leaderboard     *\n");
    printf("*     > Press D to quit and save the game    *\n");
    printf("*                                            *\n");
    printf("**********************************************\n");
}


void startQuizRecursive() {
    printf("\nEnter your name: ");
    scanf("%s", players[currentPlayerIndex].name);
    printf("==*==*==*==*==*==*==*==*==*==*==*==*==*==*==*==");

    players[currentPlayerIndex].score = 0.0;

    displayQuestions();

    currentPlayerIndex++;

    char playAgain;
    printf("\nDo you want to play again? (Y/N): ");
    scanf(" %c", &playAgain);

    if (toupper(playAgain) == 'Y') {
        startQuizRecursive();
    }
}

void displayLeaderboard() {
    printf("\n-=-=-=- Leaderboard -=-=-=-=-\n");
    bubbleSort(players, currentPlayerIndex);

    int numPlayersToShow = (currentPlayerIndex > MAX_PLAYERS) ? MAX_PLAYERS : currentPlayerIndex;

    for (int i = 0; i < numPlayersToShow; i++) {
        printf("%d. %s - Score: %.2f\n", i + 1, players[i].name, players[i].score);
    }
}

void searchLeaderboard() {
    char searchName[MAX_NAME_LENGTH];
    printf("\nEnter the name to search: ");
    scanf("%s", searchName);

    int foundIndex = -1;

    for (int i = 0; i < currentPlayerIndex; i++) {
        if (strcmp(searchName, players[i].name) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Player found: %s - Score: %.2f\n", players[foundIndex].name, players[foundIndex].score);
    } else {
        printf("Player not found.\n");
    }
}

void resetLeaderboard() {
    currentPlayerIndex = 0;
    printf("\nLeaderboard has been reset.\n");
}

void saveGame() {
    printf("\nGame saved.\n");
}

void saveLeaderboard() {
    FILE *file = fopen(LEADERBOARD_FILE, "w");

    if (file == NULL) {
        printf("Unable to save leaderboard data.\n");
        return;
    }

    for (int i = 0; i < currentPlayerIndex; i++) {
        fwrite(&players[i], sizeof(Player), 1, file);
    }

    fclose(file);
}

void loadLeaderboard() {
    FILE *file = fopen(LEADERBOARD_FILE, "r");

    if (file == NULL) {
        printf("No leaderboard data found.\n");
        return;
    }

    while (fread(&players[currentPlayerIndex], sizeof(Player), 1, file) == 1) {
        currentPlayerIndex++;
    }

    fclose(file);
}

void bubbleSort(Player players[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (players[j].score < players[j + 1].score ||
                (players[j].score == players[j + 1].score && strcmp(players[j].name, players[j + 1].name) > 0)) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}

void displayQuestions() {
    Question questions[MAX_QUESTIONS] = {
        {"1.Berapa jumlah provinsi di Indonesia?", {"A. 32", "B. 36", "C. 37", "D. 38"}, 'D'},
        {"2.Apa nama samudra terbesar di dunia?", {"A. Pasifik", "B. Atlantik", "C. Hindia", "D. Arktik"}, 'A'},
        {"3.Apa mamalia terbesar di dunia?", {"A. Gajah", "B. Hiu Paus", "C. Jerapah", "D. Paus Biru"}, 'D'},
        {"4.Siapa penulis buku 'Harry Potter'?", {"A. Charles Dickens", "B. J.K Rowling", "C. Jane Austen", "D. Mark Twain"}, 'B'},
        {"5.Apa nama planet terbesar di tata surya ", {"A. Mars", "B. Bumi", "C. Jupiter", "D. Saturnus"}, 'C'},
        {"6.Siapa penemu teori gravitasi?", {"A. Isaac Newton", "B. Albert Einstein", "C. Nikola Tesla", "D. Bill Gates"}, 'A'},
        {"7.Apa nama ibukota negara jepang?", {"A. Seoul", "B. Shanghai", "C. Tokyo", "D. Taipei"}, 'C'},
        {"8.Apa nama sungai terpanjang di dunia?", {"A. Nil", "B. Amazon", "C. Mississippi", "D. Yangtze"}, 'A'},
        {"9.Berapakah total warna pada pelangi?", {"A. 5", "B. 6", "C. 7", "D. 8"}, 'C'},
        {"10.Siapakah pelukis terkenal yang menciptakan lukisan 'Mona Lisa", {"A. Claude Monet", "B. Van Gogh", "C. Leonardo da Vinci", "D. Picasso"}, 'C'}
    };

    time_t quizStartTime = time(NULL);
    time_t currentQuizTime;

    for (int i = 0; i < MAX_QUESTIONS; i++) {
        printf("\n%s\n", questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%s\n", questions[i].options[j]);
        }

        time_t start = time(NULL);
        char answer;
        printf("Your answer (A/B/C/D): ");
        scanf(" %c", &answer);

        time_t end = time(NULL);
        int elapsed = difftime(end, start);

        currentQuizTime = difftime(end, quizStartTime);
        int remainingTime = QUESTION_TIME_LIMIT - currentQuizTime;

        if (toupper(answer) == questions[i].correctOption && remainingTime > 0) {
            players[currentPlayerIndex].score += 10.0;
            printf("Correct! You earned 10 points. Time remaining: %d seconds\n", remainingTime);
        } else {
            if (remainingTime <= 0) {
                printf("Time limit exceeded. Quiz stopped.\n");
                break;
            } else {
                printf("Wrong answer. Time remaining: %d seconds\n", remainingTime);
            }
        }
    }

    printf("\nQuiz completed. Your total score is: %.2f\n", players[currentPlayerIndex].score);
}

int askQuestion(Question question) {
    return 0;
}



