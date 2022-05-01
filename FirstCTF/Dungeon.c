#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define BOLDRED "\033[1m\033[31m"
#define RESET   "\033[0m"

//Globals
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

//Introduction to the game and class selection
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
    printf("Successfully beat the boss, claim the Absolutely Valuable treasure, and you may leave this dungeon\n");
    printf("\n");
}

// Get user choice from standard input
int getUserChoice() {
    int userNum;
    printf("\nWhat action do you take?\n");
    printf("0. Melee Attack\n");
    printf("1. Ranged Attack\n");
    printf("2. Defend\n");
    printf("3. Dodge\n");
    printf("4. Drink Potion(+ 1 Life)\n");

    scanf("%d", &userNum);

    return userNum;
}

//get user class from standard input
int getUserClass() {
    int userNum;
    printf("\nClasses:\n");
    printf("0. STRENGTH-BUILD(Double Damage)\n");
    printf("1. CONSTITUTION-BUILD(Double Health)\n");
    //printf("2. DEXTERITY-BUILD(Two Actions)\n");


    scanf("%d", &userNum);
    if(userNum > 1 || userNum < 0) {
        printf("Unable to select a class, you are unaware of the skeleton that has lurked behind you until it is too late\n");
        printf("Game Over!\n");
        exit(0);
    }
    return userNum;
}

//Calculate random number given range
int getRandoms(int lower, int upper)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}

//Calculates the move to counter the monster
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

//Changes user lives on cons. class
void changeLives() {
    if(userClass == 1) {
        lives = 2;
    } else {
        lives = 1;
    }
}

//Generates the monster statement
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

//One round of the game
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
            case 0: //Melee Attack Success
                if (bossHealth == 0) {
                    printf("The boss is exhausted, clearly your attacks have taken a toll. You push forward for the final blow, slaying the Giant.\n");
                } else {
                    printf("The Giant underestimates your speed, within the blink of an eye, you are upon the boss swinging your weapon wounding the Giant.\n");
                }
                break;
            case 1: //Ranged Attack Success
                if (bossHealth == 0) {
                    printf("The battle has raged on for what seems like forever, you are down to your last arrow. You take aim...Fire...The Giant staggers...You have slain the Giant.\n");
                } else {
                    printf("You swift bring your bow taut with an arrow and take aim. Before the Giant can react, you fire the arrow, striking the Giant and wounding it.\n");
                }
                break;
            case 2: //Defend Attack Success
                if (bossHealth == 0) {
                    printf("The Giant is clearly on his last leg, it recklessly charges at you. You parry the attack and strike quickly and without mercy, slaying the Giant.\n");
                } else {
                    printf("As the Giant attacks, you are able to defend yourself. The Giant has left an opening and you take it, wounding the Giant.\n");
                }
                break;
            case 3: //Dodge Attack Success
                if (bossHealth == 0) {
                    printf("The Giant, furious with the how long you have been fighting, charges at you. Just as he is about strike, you dodge, and the Giant collapses from exhaustion. You take this advantage and attack, slaying the Giant.\n");
                } else {
                    printf("The Giant closes the distance and begins to swing his club towards you. You effortlessly dodge and launch a quick counter-attack, wounding the Giant.\n");
                }
                break;
            case 4: //Drink Potion Success
                printf("You grab a health potion from your bag. You quickly consume it and gain +1 Life\n");
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
            case 0: //Melee Attack Failure
                if(lives == 0) {
                    printf("You decide a decisive quick strike should end this battle. You attempt hand to hand combat with the Giant, but he quickly overwhelms you, defeating you.\n");
                } else {
                    printf ("You charge at the Giant, confident it will take you only one blow. The Giant effortlessly slaps you away, wounding you.\n");
                }
                break;
            case 1: //Ranged Attack Failure
                if (lives == 0) {
                    printf("Knowing you must keep your range from the behemoth, you pulled out your bow. You take aim and fire, but you have missed. The consequences are dire as the Giant throws a boulder that crushes you.\n");
                } else {
                    printf ("The Giant anticipating a ranged attack, beats you to the punch. The Giant hurls his weapon at you landing a glancing blow, wounding you.\n");
                }
                break;
            case 2: //Defend Attack Failure
                if (lives == 0) {
                    printf("Confident, you stand your ground as the Giant charges. In a blink of the eye the giant is upon you and has squashed you under his foot.\n");

                } else {
                    printf("You attempt to defend yourself as the Giant releases a flurry of blows. It proves unsuccessful as the Giant finds a weak spot in your defense, wounding you.\n");
                }
                break;
            case 3: //Dodge Attack Failure
                if (lives == 0) {
                    printf("You attempt to dodge, but the attempt is futile. The Giant quickly brings his club down onto you.\n");
                } else {
                    printf("As the Giant swings wildly, you try to dodge. Unfortunately, while dodging the attack the giant clips your heel with his attack, wounding you.\n");
                }
                break;
            case 4: //Drink Potion Failure
                if (lives == 0) {
                    printf("You frantically search your bag for a potion. You grab the first vial you find and hastily drink it. You suddenly feel lightheaded. Did I accidentally grab the poison...\n");
                } else {
                    printf("You open your bag in search of a potion. Desperately, you grab the first vial you can and swiftly consume it. Unexpectedly, you feel a great pain from stomach, had you just drunk a potion of harm?\n");
                }
                break;
        }
    }
}

//Loop of the game
int gameplayLoop() {
    introduction();
    changeLives();

    while(bossHealth > 0) {
        roundGame();
        if (lives > 0 && bossHealth != 0) {
            printf("\nBoss Health: %d/10\n", bossHealth);
            printf("You have %d remaining lives\n\n", lives);
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