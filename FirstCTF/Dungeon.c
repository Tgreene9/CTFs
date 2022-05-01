#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define BOLDRED "\033[1m\033[31m"      /* Bold Red */
#define RESET   "\033[0m"
int lives = 0;
int bossHealth = 10;
int userClass = 0;

void introduction();
int getUserChoice();
int getUserClass();
int getRandoms(int lower, int upper);
int calculateCorrectMove(int first, int second, int third);
void changeLives();
int monsterLanguage();
void roundGame();
int gameplayLoop();

int main() {
    srand(time(NULL));
    gameplayLoop();
    printf("\n");

}

void introduction(){
    printf("Pick your Class: ");
    userClass = getUserClass();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("The Dungeon\n");
    printf("--------------------------------------------------------------\n");
    printf("You have all cleared all of the dungeon, but this last room\n");
    printf("You realize this must be the boss room, and enter the room prepared to face whatever faces you\n");
    printf(BOLDRED "Gary the Giant\n" RESET);
    //Here is where gif/image integration would be cool
    printf("Successfully beat the boss and you may leave this dungeon\n");
    printf("\n");

}

int getUserChoice() {
    int userNum;
    int dexClass;
    printf("\nWhat action do you take?\n");
    printf("0. Melee Attack\n");
    printf("1. Ranged Attack\n");
    printf("2. Defend\n");
    printf("3. Dodge\n");
    printf("4. Drink Potion(+ 1 Life)\n");

    scanf("%d", &userNum);
    return userNum;
}

int getUserClass() {
    int userNum;
    printf("\nClasses:\n");
    printf("0. STRENGTH-BUILD(Double Damage)\n");
    printf("1. DEXTERITY-BUILD(Two Actions)\n");
    printf("2. CONSTITUTION-BUILD(Double Health)\n");


    scanf("%d", &userNum);
    if(userNum > 2 || userNum < 0) {
        printf("Unable to select a class, you are unaware of the skeleton that has lurked behind you until it is too late\n");
        printf("Game Over!\n");
        exit(0);
    }
    return userNum;
}

int getRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

int calculateCorrectMove(int first, int second, int third) {
    switch (second) {
        case 0:
            return first + third;
        case 1:
            return first - third;
        case 2:
            return first * third;
        case 3:
            return first / third;

    }

    return -1;
}

void changeLives() {
    if(userClass == 2) {
        lives = 2;
    } else {
        lives = 1;
    }
}

int monsterLanguage() {
    printf("The Boss steps forwards and chants: ");
    char firstSign[3][10] = {"Nialas", "Jeden", "Kaksi"}; //0,1,2
    char secondSign[4][12] = {"Toevoeging", "Tnaqqis", "Biderketa", "Ferdieling"}; //Addition, Subtraction, Multiplication, Division
    char thirdSign[4][12] = {"placeholder","Vienas", "Tnejn"}; //1,2
    char randomWords[11][15] = {"Arvuti", "Wetenskap", "Erfaassen", "Bendera", "Rawhiti", "Egyetemi" , //Computer, Science, Capture, Flag, Eastern, University
                                "Fiarovana","Eheys","Riservatezza","Dostupnost"}; //Security, Integrity, Confidentiality, Availability

    int firstSignLocation = getRandoms(1, 6);
    int secondSignLocation = getRandoms(7, 12);
    int thirdSignLocation = getRandoms(13, 17);

    int i = 1;
    int first = 0;
    int second = 0;
    int third = 0;
    int random = 0;
    while(i != 18) {

        if (i == firstSignLocation) {
            first = getRandoms(0, 2);
            printf("%s ", firstSign[first]);
            i++;

        } else if (i == secondSignLocation) {
            second = getRandoms(0, 3);
            printf("%s ", secondSign[second]);
            i++;

        } else if (i == thirdSignLocation) {
            third = getRandoms(1, 2);
            printf("%s ", thirdSign[third]);
            i++;
        } else {
            random = getRandoms(0,9);
            printf("%s ", randomWords[random]);
            i++;
        }
    }
    printf("\n");
    return abs(calculateCorrectMove(first, second, third));
}

void roundGame() {
    int monsterMove = monsterLanguage();
    int userChoice = getUserChoice();

    if(monsterMove == userChoice) {
        if (userClass == 0) {
            bossHealth = bossHealth - 2;
        } else {
            bossHealth--;
        }

        switch(userChoice) {
            case 0:
                printf("MAS"); //Melee Attack Success
                break;
            case 1:
                printf("RAS"); //Ranged Attack Success
                break;
            case 2:
                printf("DAS"); //Defend Attack Success
                break;
            case 3:
                printf("DDAS"); //Dodge Attack Success
                break;
            case 4:
                printf("You grab a health potion from your bag. You quickly consume it and gain +1 Life"); //Drink Potion Success
                lives++;
                if (userClass == 0) {
                    bossHealth = bossHealth + 2;
                }
                break;
        }
    }
    else {
        lives--;
        switch(userChoice) {
            case 0:
                printf("You decide a decisive quick strike should end this battle. You attempt hand to hand combat with the Giant, but he quickly overwhelms you, defeating you.\n"); //Melee Attack Failure
                break;
            case 1:
                printf("Knowing you must keep your range from the behemoth, you pulled out your bow. You take aim and fire, but you have missed. The consequences are dire as the Giant throws a boulder that crushes you.\n"); //Ranged Attack Failure
                break;
            case 2:
                printf("Confident, you stand your ground as the Giant charges. In a blink of the eye the giant is upon you and has squashed you under his foot.\n"); //Defend Attack Failure
                break;
            case 3:
                printf("You attempt to dodge, but the attempt is futile. The Giant quickly brings his club down onto you.\n"); //Dodge Attack Failure
                break;
            case 4:
                printf("You frantically search your bag for a potion. You grab the first vial you find and hastily drink it. You suddenly feel lightheaded. Did I accidentally grab the poison?\n"); //Drink Potion Failure
                break;
        }
    }
}

int gameplayLoop() {
    introduction();
    changeLives();

    while(bossHealth > 0) {
        roundGame();
        if (lives > 0 && bossHealth != 0) {
            printf("\nBoss Health: %d/10\n", bossHealth);
            printf("You have %d remaining lives\n", lives);
        } else if (lives <= 0) {
            printf("\nBoss Health: %d/10\n", bossHealth);
            printf("Failed: Fate has no forgiveness for those who dare stand against it...");
            return 0;
        } else {
            continue;
        }

    }

    // Print the flag, after the completion condition
    printf("\nCongrats, you have slain the boss and conquered the dungeon\n");
    printf("You open the the bosse's chest and find: %s\n", "CTF{m0nst3r_s1AyeR}");
    return 1;
}