//CSCI 1300 Spring 2023
//Author: Daralynn Rhode
//Recitation 107- Tanmay
//Project 3 Skeleton

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>
#include "Inventory.h"
#include "npc.h"
#include "Party.h"
#include "Map.h"
#include <fstream>
#include <ctime>
#include "riddles.h"

/**
 * Algorithm: Print inventory that the party has
 * 1. accept paramaters
 * 2. cout needed strings and insert given data from paramaters
 * 
 */
void merchantMenu(int gold, int ingredients, int cookware[3], int weapons[5], int armor, int treasures[5])
{ //just basic couting, calling from arrays when needed

    cout << "+-------------+" << endl
         << "| INVENTORY   |" << endl
         << "+-------------+" << endl
         << "| Gold        | " << gold << endl
         << "| Ingredients | " << ingredients << " kg" << endl
         << "| Cookware    | P: " << cookware[0] << " | F: " << cookware[1] << " | C: " << cookware[2] << endl
         << "| Weapons     | C: " << weapons[0] << " | S: " << weapons[1] << " | R: " << weapons[2] << " | B: " << weapons[3] << " | L: " << weapons[4] << endl
         << "| Armor       | " << armor << endl
         << "| Treasures   | R: " << treasures[0] << " | N: " << treasures[1] << " | B: " << treasures[2] << " | C: " << treasures[3] << " | G: " << treasures[4] << endl
         << "+-------------+" << endl
         << endl;
}

/**
 * Algorithm: print out the main menu optionfor the merchant and accept an input value to be returned
 * 1. accpets no parameters
 * 2. print out list of choices
 * 3. assign choice to tracker and ensure it is correct number or else ask again
 * 4. return tracker
 */
int merchantTracker()
{ //cout the menu
    int tracker1 = 0;
    cout << "Choose one of the following:" << endl
         << "1. Ingredients: To make food, you have to cook raw ingredients." << endl
         << "2. Cookware: You will need something to cook those ingredients." << endl
         << "3. Weapons: It's dangerous to go alone, take this!" << endl
         << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl
         << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl
         << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
    cin >> tracker1;                  //assign to tracker
    if (tracker1 < 0 || tracker1 > 6) //make sure it si 1-6
    {
        cout << "pick a correct number." << endl;
        cin >> tracker1;
    }
    return tracker1; //return tracker
}

/**
 * Algorithm: print out status menu for the dungeon
 * 1. accept parameters
 * 2. print out statements for status
 * 3. call on MerchantMenu to print inventory
 * 4. print party stats
 * 5. display map
 * 
 */
void status(int gold, int ingredients, int cookware[3], int weapons[5], int armor, int treasures[5], int rooms, int keys, Party Party, Map map, Character characters[5], int villian)
{ //basic couting

    cout << "+-------------+" << endl
         << "| STATUS      |" << endl
         << "| Rooms Cleared: " << rooms << " | Keys: " << keys << " | Anger Level: " << villian << endl;

    merchantMenu(gold, ingredients, cookware, weapons, armor, treasures); //call upon MerchantMenu for inventory
    cout << "| PARTY       |" << endl
         << "+-------------+" << endl
         << "| " << characters[0].getUsername() << " | Fullness: " << characters[0].getHealth() << endl //getting names and health
         << "| " << characters[1].getUsername() << " | Fullness: " << characters[1].getHealth() << endl
         << "| " << characters[2].getUsername() << " | Fullness: " << characters[2].getHealth() << endl
         << "| " << characters[3].getUsername() << " | Fullness: " << characters[3].getHealth() << endl
         << "| " << characters[4].getUsername() << " | Fullness: " << characters[4].getHealth() << endl
         << "+-------------+" << endl
         << endl;
    map.displayMap(); //display map
}

/**
 * Algorithm: generate a random number between 1 and 100\
 * 1. using srand generate a random number
 * 2. modulate that number by 100 to be within range
 * 3. return number
 */
int randomNum() //done
{
    srand(time(0));      //random number
    return rand() % 100; //making sure it is between 1 and 100
}

/**
 * Algorithm: generate a number based on stats for a fight outcome
 * 1. accept parameters
 * 2. update number of weapons
 * 3. update special weapons bonuses
 * 4. calculate w
 * 5. assign parameters to a, c, and d
 * 6. genreate random number until they fall between 1 and 6
 * 7. calculate outcome
 * 8. return outcome.
 */
int fight(int weapons[5], int armor, int characount, int rating) //done
{
    int numw;
    for (int k = 0; k < 5; k++) //making sure number of weapons is updated
    {
        if (weapons[k] != 0)
        {
            numw = numw + weapons[k];
        }
    }
    int ba = 0;
    if (weapons[3] > 0) //updating special weapons
    {
        ba = weapons[3];
    }
    int ls = 0;
    if (weapons[4] > 0) //updating speacial weapons
    {
        ls = weapons[4];
    }
    int w = (5 * numw) + weapons[2] + (2 * ba) + (3 * ls); //calculating weapons

    int d = characount;
    int a = armor;
    if (armor == 0)
    {
        a = 1;
    }
    int c = rating;
    int r1 = randomNum() % 10;
    while (r1 == 0 || r1 > 6) //random number must be between 1-6
    {
        r1 = randomNum() % 10;
    }
    int r2 = randomNum() % 10;
    while (r2 == 0 || r2 > 6) //must be between 1-6
    {
        r2 = randomNum() % 10;
    }
    int outcome;
    outcome = (r1 * w + d) - ((r2 * c) / a); //calculate outcome

    return outcome;
}

/**
 * Algorithm: take a text string and break it into pieces based on a split character and assign each piece to an array value
 * 1. take in input_string, seperator, array, and array size 
 * 2. if string length is zero return 0
 * 3. declare temp string that will be a place holder
 * 4. for loop, move through the string comparing each value to the seperator
 * 5. if not equal assign to temp string
 * 6. if they are equal, make temp the array for that index iteration of j
 * 7. clear the temp string, update j and update pieces
 * 8. once loop is done assign the latest temp string to array index, update pieces
 * 9. if pieces exceeds array size, return -1
 * 10. return pieces
 * 
*/
int split(string input_string, char seperator, string arr[], int arr_size) //int function
{
    int pieces = 0;                //pieces starts at zero
    if (input_string.length() < 1) //checking that there is a string
    {
        return 0;
    }
    string temp;                                    //declare temp string
    int j = 0;                                      //declare index counter for assigning
    for (int i = 0; i < input_string.length(); i++) //loop to move through the string
    {
        if (input_string[i] != seperator) //when it is not the seperator value
        {
            temp += input_string[i]; //add to temp string
        }
        else //when it is seperator value
        {
            if (j >= arr_size)
            {
                return -1;
            }
            arr[j] = temp; //assign string to array
            temp.clear();  //clear the string
            j++;           //update array index
            pieces++;      //update the number of pieces
        }
    }
    if (j >= arr_size)
    {
        return -1;
    }
    arr[j] = temp;         //must assign last temp string to array
    pieces++;              //update pieces
    if (pieces > arr_size) //is pieces is greater than array size
    {
        return -1;
    }

    return pieces; //return value
}
/**
 * Algorithm: function to call when final stats must be printed to results.txt
 * 1. accept parameters
 * 2. open file
 * 3. push all lines to file
 * 4. close file
 */
void printToFile(int rooms, int keys, int villian, int gold, int ingredients, int cookware[5], int weapons[5], int armor, int treasures[5], Character characters[5], int turns, int monsters, int explore)
{ //open stream
    ofstream file;
    file.open("results.txt");
    //push all to text file
    file << "Final STATS" << endl;
    file << "+-------------+" << endl
         << "| STATUS      |" << endl
         << "| Rooms Cleared: " << rooms << " | Keys: " << keys << " | Anger Level: " << villian << endl;
    file << "+-------------+" << endl
         << "| INVENTORY   |" << endl
         << "+-------------+" << endl
         << "| Gold        | " << gold << endl
         << "| Ingredients | " << ingredients << " kg" << endl
         << "| Cookware    | P: " << cookware[0] << " | F: " << cookware[1] << " | C: " << cookware[2] << endl
         << "| Weapons     | C: " << weapons[0] << " | S: " << weapons[1] << " | R: " << weapons[2] << " | B: " << weapons[3] << " | L: " << weapons[4] << endl
         << "| Armor       | " << armor << endl
         << "| Treasures   | R: " << treasures[0] << " | N: " << treasures[1] << " | B: " << treasures[2] << " | C: " << treasures[3] << " | G: " << treasures[4] << endl
         << "+-------------+" << endl;
    file << "| PARTY       |" << endl
         << "+-------------+" << endl
         << "| " << characters[0].getUsername() << " | Fullness: " << characters[0].getHealth() << endl //getting names and health
         << "| " << characters[1].getUsername() << " | Fullness: " << characters[1].getHealth() << endl
         << "| " << characters[2].getUsername() << " | Fullness: " << characters[2].getHealth() << endl
         << "| " << characters[3].getUsername() << " | Fullness: " << characters[3].getHealth() << endl
         << "| " << characters[4].getUsername() << " | Fullness: " << characters[4].getHealth() << endl
         << "+-------------+" << endl
         << endl;
    file << endl;
    file << "Turns Taken: " << turns << endl;
    file << "Monsters Defeated: " << monsters << endl;
    file << "Spaces Explored: " << explore << endl;
    //close file
    file.close();
}

int main()
{
    int phase = 0;
    int villian = 0;
    //Starting adventure by asking for names and player types
    //
    string mainName;
    string mainType;
    cout << "Welcome to the adventure!" << endl
    << "To get started enter your player name and archetype!"
    << endl;
    cin >> mainName;
    cin >> mainType;
    Character main = Character(mainName, 50, mainType, 1); //assign to a character class
    string name2;
    string name3;
    string name4;
    string name5;
    string type2;
    string type3;
    string type4;
    string type5;
    cout << "Now we need to create your party." << endl
         << "Enter 4 more names and archetypes." << endl;
    cin >> name2;
    cin >> type2;
    cin >> name3;
    cin >> type3;
    cin >> name4;
    cin >> type4;
    cin >> name5;
    cin >> type5;
    //assign all to character classes
    Character second = Character(name2, 50, type2, 2);
    Character third = Character(name3, 50, type3, 3);
    Character fourth = Character(name4, 50, type4, 4);
    Character fifth = Character(name5, 50, type5, 5);
    //assign those characters to array
    Character characters[5] = {main, second, third, fourth, fifth};
    string partyName;
    cout << "Finally, you need to choose a Party name!" << endl;
    cin >> partyName;
    Party party = Party();
    int characount = 5;
    cout << "Great! Now its time to start the game, but your party doesnt look all that prepared..." << endl;
    cout << "..." << endl
         << "..." << endl
         << "I know! Lets go visit the Merchant!" << endl;
    //meant to slow down the game and printing
    int enter2;
    cout << "Press any letter and then ENTER to continue" << endl;
    cin >> enter2;
    cin.clear();
    cin.ignore();
    phase = 1;

    //MERCHANT PHASE COMPLETE

    int gold = 100;
    //cout merchant start direction
    cout << "Welcome to the Merchant!" << endl;
    cout << "Between the 5 of you, you have 100 gold pieces." << endl
         << "You will need to spend the some of your money on the following items:" << endl
         << endl
         << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl
         << "- COOKWARE. If you want to cook, you have to have cookware first." << endl
         << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl
         << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl
         << endl
         << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;

    cout << "If you're looking to get supplies, you've come to the right place." << endl
         << "I would be happy to part with some of my wares...for the proper price!" << endl;
    //create inventory objects and arrays
    int ingredients = 0;
    int cookware[3] = {0, 0, 0};
    int weapons[5] = {0, 0, 0, 0, 0};
    int armor = 0;
    int treasure[5] = {0, 0, 0, 0, 0};
    merchantMenu(gold, ingredients, cookware, weapons, armor, treasure); //print menu
    int tracker = 0;
    while (tracker != 6) //loop for main merchant menu
    {
        tracker = merchantTracker();

        if (tracker == 1)
        {
            int kg;
            cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> kg;
            gold = gold - kg;               //update gold
            ingredients = ingredients + kg; //update ingredients
            cout << "Thank you for your patronage! What else can I get for you?" << endl
                 << "Gold: " << gold << endl;
        }
        if (tracker == 2)
        {

            int choice;
            while (choice != 4) //loop for cookware menu
            {
                cout << "I have a several types of cookware, which one would you like?" << endl
                     << endl
                     << "Choose one of the following:" << endl
                     << "1. Ceramic Pot [2 Gold]" << endl
                     << "2. Frying Pan [10 Gold]" << endl
                     << "3. ( 2%) Cauldron [20 Gold]" << endl
                     << "4. Cancel" << endl;
                cin >> choice;
                int numwanted;
                if (choice == 1) //option 1 submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 2;           //update gold
                    cookware[0] = cookware[0] + numwanted; //update in array
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 2) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 10;          //update gold
                    cookware[1] = cookware[1] + numwanted; //update in array
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 3) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 20;          //update gold
                    cookware[2] = cookware[2] + numwanted; //update in array
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
            }
        }
        if (tracker == 3)
        {
            int choice;
            while (choice != 6) //loop for weapons menu
            {
                cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl
                     << endl
                     << "Choose one of the following:" << endl
                     << "1. Stone Club [2 Gold]" << endl
                     << "2. Iron Spear [2 Gold]" << endl
                     << "3. Mythril Rapier [5 Gold]" << endl
                     << "4. Flaming Battle-Axe [15 Gold]" << endl
                     << "5. Vorpal Longsword [50 Gold]" << endl
                     << "6. Cancel" << endl;
                cin >> choice;
                int numwanted;
                if (choice == 1) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 2;         //update
                    weapons[0] = weapons[0] + numwanted; //update
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 2) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 2;         //update
                    weapons[1] = weapons[1] + numwanted; //update
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 3) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 5;         //update
                    weapons[2] = weapons[2] + numwanted; //update
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 4) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 15;        //update
                    weapons[3] = weapons[3] + numwanted; //update
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
                if (choice == 5) //submenu
                {
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> numwanted;
                    gold = gold - numwanted * 50;        //update
                    weapons[4] = weapons[4] + numwanted; //update
                    cout << "Thank you for your patronage! What else can I get for you?" << endl
                         << "Gold: " << gold << endl;
                }
            }
        }
        if (tracker == 4)
        {
            int amount;
            cout << "How many suits of armor can I get you? (25 gold/one) (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> amount;
            gold = gold - amount * 25; //update
            armor = armor + amount;    //update
        }
        if (tracker == 5)
        {
            int treas;
            //while (treas !=6)//loop
            //{
            int a;
            //treasuer menu
            cout << "What type of treasure do you want to sell?" << endl
                 << " 1. Silver ring (R) - 10 gold pieces each" << endl
                 << "2. Ruby necklace (N) - 20 gold pieces each" << endl
                 << "3. Emerald bracelet (B) - 30 gold pieces each" << endl
                 << "4. Diamond circlet (C) - 40 gold pieces each" << endl
                 << "5. Gem-encrusted goblet (G) - 50 gold pieces each" << endl
                 << "6. Leave" << endl;
            cout << endl
                 << "Your Treasure: " << endl
                 << "R: " << treasure[0] << endl
                 << "N: " << treasure[1] << endl
                 << "B: " << treasure[2] << endl
                 << "C: " << treasure[3] << endl
                 << "G: " << treasure[4] << endl;
            cin >> treas;

            if (treas == 1)
            {
                if (treasure[0] > 0) //making sure there is something to sell
                {

                    cout << "How many? " << endl;
                    cin >> a;
                    treasure[0] = treasure[0] - a; //update
                    gold = gold + 10 * a;          //update
                }
                else
                {
                    cout << "sorry you dont have enough." << endl;
                    break;
                }
            }
            if (treas == 2)
            {
                if (treasure[1] > 0) //making sure there is something to sell
                {

                    cout << "How many? " << endl;
                    cin >> a;
                    treasure[1] = treasure[1] - a; //update
                    gold = gold + 20 * a;          //update
                }
                else
                {
                    cout << "sorry you dont have enough." << endl;
                    break;
                }
            }
            if (treas == 3)
            {
                if (treasure[2] > 0) //making sure there is somethign to sell
                {

                    cout << "How many? " << endl;
                    cin >> a;
                    treasure[2] = treasure[2] - a; //update
                    gold = gold + 30 * a;          //update
                }
                else
                {
                    cout << "sorry you dont have enough." << endl;
                    break;
                }
            }
            if (treas == 4)
            {
                if (treasure[3] > 0) //making sure there is something to sell
                {

                    cout << "How many? " << endl;
                    cin >> a;
                    treasure[3] = treasure[3] - a; //update
                    gold = gold + 40 * a;          //update
                }
                else
                {
                    cout << "sorry you dont have enough." << endl;
                    break;
                }
            }
            if (treas == 5)
            {
                if (treasure[4] > 0) //making sure there is something to sell
                {

                    cout << "How many? " << endl;
                    cin >> a;
                    treasure[4] = treasure[4] - a; //update
                    gold = gold + 50 * a;          //update
                }
                else
                {
                    cout << "sorry you dont have enough." << endl;
                    break;
                }
            }
            //}
        }
        if (tracker == 6) //option to leave merchant phase
        {
            break;
        }
    }

    //COMPLETE: DUNGEON PHASE

    //cout some general statments.

    cout << "Now, time to enter the dungeon. Good Luck!" << endl;

    Map map = Map();
    //tracker values
    int keys = 0;
    int rooms = 0;
    int random = randomNum();
    int explored = 0;
    //random map generation based on random number given
    if (random <= 30)
    {
        map.setDungeonExit(11, 11);
        map.setPlayerPosition(0, 0);
        map.addRoom(6, 9);
        map.addRoom(2, 7);
        map.addRoom(10, 3);
        map.addRoom(10, 9);
        map.addRoom(2, 2);
        map.addNPC(0, 3);
        map.addNPC(11, 3);
        map.addNPC(5, 5);
    }
    if (random > 30 && random <= 60)
    {
        map.setDungeonExit(11, 6);
        map.setPlayerPosition(0, 0);
        map.addRoom(6, 9);
        map.addRoom(3, 7);
        map.addRoom(10, 3);
        map.addRoom(1, 9);
        map.addRoom(0, 2);
        map.addNPC(0, 3);
        map.addNPC(11, 3);
        map.addNPC(5, 5);
        map.addNPC(11, 0);
    }
    if (random > 60)
    {
        map.setDungeonExit(11, 1);
        map.setPlayerPosition(0, 0);
        map.addRoom(6, 0);
        map.addRoom(2, 0);
        map.addRoom(11, 3);
        map.addRoom(10, 9);
        map.addRoom(8, 4);
        map.addNPC(0, 3);
        map.addNPC(11, 4);
        map.addNPC(5, 5);
    }
    //loop to keep moving through the dungeon until rooms reach 5
    int turns = 0;
    int monsters = 0;
    while (rooms != 6)
    {
        
        turns++;
        if (villian > 100) //makins sure villian does not become greater than 100
        {
            cout << "Oh No! You pushed the evil sorceror too far." << endl
                 << "GAME OVER!" << endl;
            status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //final status
        }
        if (characount == 1) //if all other character die, game over
        {
            cout << "Oh No! You lost all of your party." << endl
                 << "GAME OVER!" << endl;
            status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //final status
        }
        if (characters[0].getHealth() <= 0) //if  main characters health becomes 0, game over
        {
            cout << "Oh No! Your Player is dead." << endl
                 << "GAME OVER!" << endl;
            status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //final status
        }
        char act;
        int action = 0;
        status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //print status each turn through dungeon
        if (map.isFreeSpace(map.getPlayerRow(), map.getPlayerCol()) == true)                                         //check to see if player is on free space
        {                                                                                                            //free space menu
            cout << "Select one:" << endl
                 << "1. Move" << endl
                 << "2. Investigate" << endl
                 << "3. Pick a Fight" << endl
                 << "4. Cook and Eat" << endl
                 << "5. Give up" << endl;
            cin >> action;
            if (action == 1) //move
            {
                cout << "Make a Move(w:up, a:left, s:down, or d:right): " << endl;
                cin >> act;
                map.move(act);           //make move
                villian++;               //update
                int ranny = randomNum(); //misfortune
                if (ranny <= 20)
                {
                    cout << "Oh No! Misfortune Occures. Everyone looses 1 fullness Point." << endl;
                    for (int i = 0; i < 5; i++) //loop for everyone in party to loose health
                    {
                        Character temmpy = characters[0];
                        temmpy.looseHealth(1);
                    }
                }
            }
            if (action == 2) //investigate
            {
                int rando = randomNum(); //chance
                if (rando <= 20)
                {
                    cout << "You found a key!" << endl;
                    keys++; //updates
                    villian++;
                    explored++;
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol()); //mark as explored
                }
                else
                {
                    cout << "You found nothing." << endl;
                    villian++; //updates
                    explored++;
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol()); //mark as explored
                }
            }
            if (action == 3) //fight
            {
                cout << "You are purposely looking for a fight..." << endl;
                cout << "YOu now must face a monster." << endl;
                if (rooms == 0) //monster based on rooms cleared, 0 rooms
                {
                    cout << "MONSTER : Minotaur" << endl;
                    double freturn = fight(weapons, armor, characount, 2); //fight function
                    if (freturn <= 0)                                      //loose
                    {
                        cout << "Oh NO! YOu loose. The villian number increases by 5." << endl;
                        villian = villian + 5; //update
                    }
                    else //win
                    {
                        cout << "Congrates! You won!. you get 5 gold pieces and key." << endl;
                        gold = gold + 5; //updates
                        keys++;
                        monsters++;
                    }
                }
                if (rooms == 1) //1 room cleared
                {
                    cout << "MONSTER : Troll" << endl;
                    double freturn = fight(weapons, armor, characount, 3); //fight function
                    if (freturn <= 0)                                      //loose
                    {
                        cout << "Oh NO! YOu loose. The villian number increases by 10." << endl;
                        villian = villian + 10; //update
                    }
                    else //win
                    {
                        cout << "Congrates! You won!. you get 10 gold pieces and a key." << endl;
                        gold = gold + 10; //updates
                        keys++;
                        monsters++;
                    }
                }
                if (rooms == 2) //2 rooms cleared
                {
                    cout << "MONSTER : Silver Dragon" << endl;
                    double freturn = fight(weapons, armor, characount, 5); //fight funciton
                    if (freturn <= 0)                                      //loose
                    {
                        cout << "Oh NO! YOu loose. The villian number increases by 15." << endl;
                        villian = villian + 15; //update
                    }
                    else //win
                    {
                        cout << "Congrates! You won!. you get 15 gold pieces and a key." << endl;
                        gold = gold + 15; //updates
                        keys++;
                        monsters++;
                    }
                }
                if (rooms == 3) //3 rooms cleared
                {
                    cout << "MONSTER : Vampire" << endl;
                    double freturn = fight(weapons, armor, characount, 5); //fight funciton
                    if (freturn <= 0)                                      //loose
                    {
                        cout << "Oh NO! YOu loose. The villian number increases by 20." << endl;
                        villian = villian + 20; //update
                    }
                    else //win
                    {
                        cout << "Congrates! You won!. you get 20 gold pieces and a key." << endl;
                        gold = gold + 20; //updates
                        keys++;
                        monsters++;
                    }
                }
            }
            if (action == 4) //option 4, cook
            {
                int cook;
                cout << "You have " << ingredients << " kgs of ingredients. How much do you want to cook?"
                     << endl;
                cin >> cook;
                if (cook == 0) //checking to make sure there are ingredients
                {
                    continue;
                }
                else
                {
                    cout << "Cooking successful! Everyone in your Party health has increased by 5." << endl;
                    for (int i = 0; i < 5; i++) //increae everyones health
                    {
                        Character temmpy = characters[0];
                        temmpy.gainHealth(5);
                    }
                }
            }
            if (action == 5) //give up option
            {
                char yn;
                cout << "Are you sure you want to give up? Once you leave all progress will be lost!" << endl;
                cin >> yn;
                if (yn == 'Y' || yn == 'y') //if confirmed
                {
                    cout << "Its sad to see you go!" << endl;
                    cout << "FINAL STATS:" << endl;
                    status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);                     //print final stats
                    printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored); //print final stats to file
                    return 0;                                                                                                                        //end game
                }
                else //not confiemed, continue game
                {
                    continue;
                }
            }
            continue; //
        }
        if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()) == true) // if player is on a room space
        {                                                                       //room menu
            cout << "Select one:" << endl
                 << "1. Move" << endl
                 << "2. Open the Door" << endl
                 << "3. Give up" << endl;
            cin >> action;
            if (action == 1) //option 1, move
            {
                cout << "Make a Move(w:up, a:left, s:down, or d:right): " << endl;
                cin >> act;
                map.move(act); //complete action
                villian++;     //update
                int ranny = randomNum();
                if (ranny <= 20) //misfortune occurance
                {
                    cout << "Oh No! Misfortune Occures. Everyone looses 1 fullness Point." << endl;
                    for (int i = 0; i < 5; i++) //everyone loose health
                    {
                        Character temmpy = characters[0];
                        temmpy.looseHealth(1);
                    }
                }
            }
            if (action == 2) //option 2, open door
            {
                cout << "Lets see if you have any keys... " << endl
                     << "Keys : " << keys << endl;
                if (keys > 0) //must have a key
                {
                    cout << "YOu are in luck. You have a key!" << endl;
                    keys--;
                    cout << "YOu now must face a monster in order to clear the room." << endl;
                    if (rooms == 0) //1 room cleared
                    {
                        cout << "MONSTER : Minotaur" << endl;
                        double freturn = fight(weapons, armor, characount, 2);
                        if (freturn <= 0) //loose
                        {
                            cout << "Oh NO! YOu loose. The villian number increases by 5." << endl;
                            villian = villian + 5; //update
                        }
                        else //win
                        {
                            cout << "Congrates! You won!. you get 5 gold pieces and clear the room." << endl;
                            gold = gold + 5; //updates
                            rooms = 1;
                            monsters++;
                        }
                    }
                    if (rooms == 1) //1 room clreaed
                    {
                        cout << "MONSTER : Troll" << endl;
                        double freturn = fight(weapons, armor, characount, 3); //fight funciton
                        if (freturn <= 0)                                      //loose
                        {
                            cout << "Oh NO! YOu loose. The villian number increases by 10." << endl;
                            villian = villian + 10; //update
                        }
                        else //win
                        {
                            cout << "Congrates! You won!. you get 10 gold pieces and clear the room." << endl;
                            gold = gold + 10; //updates
                            rooms = 2;
                            monsters++;
                        }
                    }
                    if (rooms == 2) //2 rooms cleared
                    {
                        cout << "MONSTER : Silver Dragon" << endl;
                        double freturn = fight(weapons, armor, characount, 5); //fight funciton
                        if (freturn <= 0)                                      //loose
                        {
                            cout << "Oh NO! YOu loose. The villian number increases by 15." << endl;
                            villian = villian + 15; //update
                        }
                        else //win
                        {
                            cout << "Congrates! You won!. you get 15 gold pieces and clear the room." << endl;
                            gold = gold + 15; //updates
                            rooms = 3;
                            monsters++;
                        }
                    }
                    if (rooms == 3) //3 rooms cleared
                    {
                        cout << "MONSTER : Vampire" << endl;
                        double freturn = fight(weapons, armor, characount, 5); //fight funciton
                        if (freturn <= 0)                                      //loose
                        {
                            cout << "Oh NO! YOu loose. The villian number increases by 20." << endl;
                            villian = villian + 20; //update
                        }
                        else //win
                        {
                            cout << "Congrates! You won!. you get 20 gold pieces and clear the room." << endl;
                            gold = gold + 20; //updates
                            rooms = 4;
                            monsters++;
                        }
                    }
                }
                else //do not have any keys, solve riddle
                {
                    cout << "Looks like you need to find some more keys." << endl
                         << "YOu fall into a trap and now must solve this riddle to open the door" << endl;
                    riddle riddles[20]; //riddles array
                    string line1;       //line from file
                    ifstream fin;
                    fin.open("riddles.txt"); //open text
                    string arr1[2];
                    int mn = 0;
                    while (!fin.eof()) //while open
                    {
                        getline(fin, line1);                          //get line
                        int split_count = split(line1, '~', arr1, 2); //split into 2
                        if (split_count == 2)
                        {
                            string temp_riddle = arr1[0];
                            string temp_ans = arr1[1];
                            riddles[mn] = riddle(temp_riddle, temp_ans); //assign to riddles array
                            mn++;
                        }
                    }
                    fin.close(); //close file

                    int g = randomNum() / 10; //to keep it between 0 and 10, random number
                    string answer;
                    if (g == 1)
                    {
                        riddles[0];
                        cout << riddles[0].getRiddle() << endl; //print riddle
                        cin >> answer;
                        if (answer == riddles[0].getAns()) //if answer is correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++; //update
                        }
                        else //incorrect
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5 and you loose a party member" << endl;
                            characters[characount - 1].playerDeath(); //loose a member
                            characount--; //update
                        }
                    }
                    if (g == 2)
                    {
                        riddles[1];
                        cout << riddles[1].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[1].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;//update
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                                characount--;//update
                        }
                    }
                    if (g == 3)
                    {
                        riddles[2];
                        cout << riddles[2].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[2].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;//update
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 4)
                    {
                        riddles[3];
                        cout << riddles[3].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[3].getAns())//if cporrect
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 5)
                    {
                        riddles[4];
                        cout << riddles[4].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[4].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 6)
                    {
                        riddles[5];
                        cout << riddles[5].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[5].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 7)
                    {
                        riddles[6];
                        cout << riddles[6].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[6].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 8)
                    {
                        riddles[7];
                        cout << riddles[7].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[7].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 9)
                    {
                        riddles[8];
                        cout << riddles[8].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[8].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                    if (g == 10)
                    {
                        riddles[9];
                        cout << riddles[9].getRiddle() << endl;//print riddle
                        cin >> answer;
                        if (answer == riddles[9].getAns())//if correct
                        {
                            cout << "Correct!" << endl
                                 << "You have cleared the room." << endl;
                            rooms++;
                        }
                        else
                        {
                            cout << "Incorrect!" << endl
                                 << "You do not clear the room. " << endl
                                 << "villians anger increases by 5." << endl;
                                 characters[characount - 1].playerDeath(); //loose a member
                            characount--;                             //update
                        }
                    }
                }
            }
            if (action == 3) //option 3, quit
            {
                char yn;
                cout << "Are you sure you want to give up? Once you leave all progress will be lost!" << endl;
                cin >> yn;
                if (yn == 'Y' || yn == 'y')//confirmation
                {
                    cout << "Its sad to see you go!" << endl;
                    cout << "FINAL STATS:" << endl;
                    status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);//print final stats
                    printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored);//save final stats to file
                    return 0;//end game
                }
                else//no confirmation, then continue game
                {
                    continue;
                }
            }
            continue; //
        }
        if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) == true) //dungeon exit space
        {
            if (rooms == 5)//if 5 rooms have been cleared, you can leave
            {
                cout << "You are almost there! Congrats at escaping the dungeon! Before you can"
                     << "complete your quest you must vanquesh the evil sorceror!!" << endl;
                rooms++;//update, so loop stops
                break;
            }
            else//update on what must be done in order to win
            {
                cout << "you must clear all rooms before you can exit the dungeon. " << endl
                     << "Rooms cleared: " << rooms << endl;
                cout << "Villian Anger: " << villian << endl;
                cout << "Make a Move(w:up, a:left, s:down, or d:right): " << endl;//make a move
                cin >> act;
                map.move(act);//move
                villian++;//update
                int ranny = randomNum();//misfortune generator
                if (ranny <= 20)
                {
                    cout << "Oh No! Misfortune Occures. Everyone looses 1 fullness Point." << endl;
                    for (int i = 0; i < 5; i++)//everyone loose health
                    {
                        Character temmpy = characters[0];
                        temmpy.looseHealth(1);
                    }
                }
            }
            continue; //
        }
        if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol()) == true) // npc map location
        {//npc menu print
            cout << "Select one:" << endl
                 << "1. Move" << endl
                 << "2. Speak to NPC" << endl
                 << "3. Give up" << endl;
            cin >> action;
            if (action == 1) //option1 
            {
                cout << "Make a Move(w:up, a:left, s:down, or d:right): " << endl;
                cin >> act;
                map.move(act);//make move
                villian++;//update
                int ranny = randomNum();//misfortune
                if (ranny <= 20)
                {
                    cout << "Oh No! Misfortune Occures. Everyone looses 1 fullness Point." << endl;
                    for (int i = 0; i < 5; i++)//loop for party to loose health
                    {
                        Character temmpy = characters[0];
                        temmpy.looseHealth(1);
                    }
                }
            }
            if (action == 2) //option 2, speak to npc
            {//populate npc array from final 
                npc NPC[2];
                string line; //line from file
                ifstream fin;
                fin.open("npc.txt");//open file
                string arr[2];
                int m = 0;
                while (!fin.eof())//while open
                {
                    getline(fin, line);//get line
                    int split_count = split(line, ',', arr, 2);//pas to split function
                    if (split_count == 2)
                    {
                        string temp_dialog = arr[0];
                        string temp_name = arr[1];
                        NPC[m] = npc(temp_dialog, temp_name);//assign to npc array
                        m++;
                    }
                }
                fin.close();//close file

               
                int ran = randomNum();//random npc generator, from 3 choices
                if (ran <= 33)
                {
                    NPC[0];
                    cout << "Hello, my name is " << NPC[0].getNPCname() << "." << endl;//print name
                    cout << NPC[0].getDialog() << endl;//print dialog
                }
                if (ran <= 66 && ran > 33)
                {
                    NPC[1];
                    cout << "Hello, my name is " << NPC[1].getNPCname() << "." << endl;//print name 
                    cout << NPC[1].getDialog() << endl;//print dialog
                }
                if (ran > 66)
                {
                    NPC[2];
                    cout << "Hello, my name is " << NPC[2].getNPCname() << "." << endl;//print name
                    cout << NPC[2].getDialog() << endl;//print dialog
                }
            }
            if (action == 3) //option 3, quit
            {
                char yn;
                cout << "Are you sure you want to give up? Once you leave all progress will be lost!" << endl;
                cin >> yn;
                if (yn == 'Y' || yn == 'y')//confirmation
                {
                    cout << "Its sad to see you go!" << endl;
                    cout << "FINAL STATS:" << endl;
                    status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);//print final stats
                    printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored);//save final stats to file
                    return 0;//end game
                }
                else
                {
                    continue;
                }
            }
            continue; //
        }
        if (map.isExplored(map.getPlayerRow(), map.getPlayerCol()) == true) //if space is explored
        {//explore space outpur
            cout << "Nothing left to do on this space. Try exploring other spaces nearby." << endl;
            cout << "Make a Move(w:up, a:left, s:down, or d:right): " << endl;//make a move
            cin >> act;
            map.move(act);//move action
            villian++;//update
            int ranny = randomNum();//misfortune
            if (ranny <= 20)
            {
                cout << "Oh No! Misfortune Occures. Everyone looses 1 fullness Point." << endl;
                for (int i = 0; i < 5; i++)//entire party loose health
                {
                    Character temmpy = characters[0];
                    temmpy.looseHealth(1);
                }
            }
            continue; //
        }
    }

    //COMPLETE: FIGHT PHASE
    //And Boss Fight Extra Credit
    char answer;
    cout << "FINAL FIGHT!" << endl << "Are you ready? (Y/N)" << endl;
    cin>> answer;
    if(answer == 'Y' || answer=='N' || answer == 'y' || answer == 'n')//you have no choice
    {
        cout << "First, you must solve 3 riddles to break into his protective chamber!" << endl;
        int chamber=0;
        cout << "You will have three chances to answer correctly for each riddle. If you fail, YOU LOOSE!" << endl;
        int enter21;
        cout << "Press any letter and then ENTER to continue" << endl;//slowing donw game play
        cin >> enter21;
        cin.clear();
        cin.ignore();
//populatinf riddles array 
        riddle riddles2[20]; //riddles array
                    string line12;       //line from file
                    ifstream fin2;
                    fin2.open("riddles.txt"); //open text
                    string arr12[2];
                    int mn2 = 0;
                    while (!fin2.eof()) //while open
                    {
                        getline(fin2, line12);                          //get line
                        int split_count = split(line12, '~', arr12, 2); //split into 2
                        if (split_count == 2)
                        {
                            string temp_riddle = arr12[0];
                            string temp_ans = arr12[1];
                            riddles2[mn2] = riddle(temp_riddle, temp_ans); //assign to riddles array
                            mn2++;
                        }
                    }
                    fin2.close(); //close file
                    string rid1;
                    for (int g = 0; g < 3; g++)//three chances for riddle 1
                    {

                        cout << riddles2[15].getRiddle() << endl;//print riddle
                        cin >> rid1;
                        if (rid1 == riddles2[15].getAns())//if correct leave loop
                        {
                            cout << "Correct." << endl;
                            break;
                        }
                        else//incorrect
                        {
                            
                                cout << "Incorrect. Try again." << endl;
                            
                        }
                    }
                    if (rid1 != riddles2[15].getAns())//if answer was never correct, game ends
                    {
                        cout << "YOu LOOSE! The sorceror wins." << endl;
                        status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);                     //final stats
                        printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored); //save final stats to file
                        return 0;  //game end                                                                                                                      //end game
                    }

        cout << "One sheild brocken. NOw onto riddle 2. Answer if you dare..." << endl;

                string rid12;
                    for (int g2 = 0; g2 < 3; g2++)//loop for riddle 2, 3 chances
                    {

                        cout << riddles2[16].getRiddle() << endl;//print riddle
                        cin >> rid12;
                        if (rid12 == riddles2[16].getAns())//if answer correct, leave loop
                        {
                            cout << "Correct. Now onto to riddle 2!" << endl;
                            break;
                        }
                        else//incorrect
                        {
                            
                                cout << "Incorrect. Try again." << endl;
                            
                        }
                    }
                    if (rid12 != riddles2[16].getAns())//if answer was never correct, game ends
                    {
                        cout << "YOu LOOSE! The sorceror wins." << endl;
                        status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);                     //final stats
                        printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored); //save final stats to file
                        return 0;   //end game                                                                                                                     //end game
                    }
        cout << "Second Sheild has been broken! Keep up the good work. One more riddle to go!" << endl;
                string rid13;
                    for (int g3 = 0; g3 < 3; g3++)//loop for 3rd riddle, 3 chances
                    {

                        cout << riddles2[17].getRiddle() << endl;//print riddle
                        cin >> rid13;
                        if (rid13 == riddles2[17].getAns())//if answer is correct, leave loop
                        {
                            cout << "Correct. Now onto to riddle 2!" << endl;
                            break;
                        }
                        else//incorrect
                        {
                           
                                cout << "Incorrect. Try again." << endl;
                            
                        }
                    }
                    if (rid13 != riddles2[17].getAns())//if answer was never correct, game over
                    {
                        cout << "YOu LOOSE! The sorceror wins." << endl;
                        status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian);                     //final stats
                        printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored); //save final stats to file
                        return 0;   //end game                                                                                                                     //end game
                    }
        cout << "All Sheilds have been broken, you can now fight the sorceror! Good luck!" << endl;

        int enter213;//slowing donw the game play
        cout << "Press any letter and then ENTER to continue" << endl;
        cin >> enter213;
        cin.clear();
        cin.ignore();

        int finNum = fight(weapons, armor, characount, 6); //calculate final fight outcome
        if (finNum > 0)                                    //if greater than 0, you win
        {
            cout << "YOU WON!! " << endl
                << "You have defeated the sorceror and survived the dungeon." << endl;
            cout << "FINAL STATS:" << endl;
            monsters++;//update
            status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //final stats
            printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored);//save final stats to file
            return 0; //end game
        }
        else //if not, you loose
        {
            cout << "OH NO! You Lost! Your adventure is over. " << endl;
            for (int i = 0; i < 5; i++) //all characters die
            {
                characters[i].playerDeath();
            }
            status(gold, ingredients, cookware, weapons, armor, treasure, rooms, keys, party, map, characters, villian); //final stats
            printToFile(rooms, keys, villian, gold, ingredients, cookware, weapons, armor, treasure, characters, turns, monsters, explored);//save final stats to file

            return 0;//end game
        }

    }
}
