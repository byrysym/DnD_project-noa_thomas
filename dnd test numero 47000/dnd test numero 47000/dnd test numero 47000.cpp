#include <iostream>
#include <string>
#include <random>
#include <conio.h>  // For _getch()

class Character {
private:
    std::string name;
    std::string race;
    std::string characterClass;
    std::string weapon;
    std::string specialAbility;
    std::string magicItem;
    int stats[6];  // Tableau pour les stats : 0 = Force, 1 = Dexterite, etc.
    bool locked[6];  // Tableau pour savoir si une stat est verrouillée
    std::string statNames[6] = { "Strength", "Dexterity", "Constitution", "Intelligence", "Wisdom", "Charisma" };
    int height;     // Taille du personnage
    int weight;     // Poids du personnage
    std::string personalityTraits[3];  // Tableau pour les traits de personnalité

public:
    Character() : stats{ 0 }, locked{ false }, height(0), weight(0) {}

    void createCharacter() {
        std::cout << "Enter the character's name: ";
        std::getline(std::cin, name);

        race = chooseRace();
        chooseHeightAndWeight();
        characterClass = chooseClass();

        allocateStats();
        choosePersonalityTraits();  // Appel de la fonction pour choisir les traits de personnalité
    }

    void displayCharacterSheet() const {
        system("cls");
        std::cout << "\n--- Character Sheet ---\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Race: " << race << "\n";
        std::cout << "Class: " << characterClass << "\n";
        std::cout << "Weapon: " << weapon << "\n";
        std::cout << "Special Ability: " << specialAbility << "\n";
        std::cout << "Magic Item: " << magicItem << "\n";
        std::cout << "Height: " << height << " cm\n";
        std::cout << "Weight: " << weight << " kg\n";
        for (int i = 0; i < 6; ++i) {
            std::cout << statNames[i] << ": " << stats[i] << "\n";
        }
        std::cout << "\n--- Personality Traits ---\n";
        for (const auto& trait : personalityTraits) {
            std::cout << trait << "\n";
        }
        std::cout << "---------------------------\n";
    }

private:
    // Choisir la race
    std::string chooseRace() {
        std::string chosenRace;
        int raceChoice = 0;
        bool validChoice = false;

        while (!validChoice) {
            system("cls");
            std::cout << "Choose a race (Human, Orc, Elf, Dwarf):\n";
            std::cout << "Use arrows to navigate, Enter to select.\n";

            displayRaceMenu(raceChoice);

            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72) {  // Up arrow
                    raceChoice = (raceChoice - 1 + 4) % 4;
                }
                else if (key == 80) {  // Down arrow
                    raceChoice = (raceChoice + 1) % 4;
                }
            }
            else if (key == 13) {  // Entrée
                validChoice = true;
            }
        }

        switch (raceChoice) {
        case 0: chosenRace = "Human"; break;
        case 1: chosenRace = "Orc"; break;
        case 2: chosenRace = "Elf"; break;
        case 3: chosenRace = "Dwarf"; break;
        }

        return chosenRace;
    }

    // Display Race Option
    void displayRaceMenu(int selectedOption) {
        std::string options[] = { "Human", "Orc", "Elf", "Dwarf" };
        for (int i = 0; i < 4; ++i) {
            if (i == selectedOption)
                std::cout << "> " << options[i] << " <\n";  // Option selected
            else
                std::cout << options[i] << "\n";
        }
    }

    // Customizable size and weight function with arrow navigation
    void chooseHeightAndWeight() {
        // Size and weight ranges by breed
        int minHeight, maxHeight, minWeight, maxWeight;
        if (race == "Human") {
            minHeight = 160; maxHeight = 190;
            minWeight = 60; maxWeight = 90;
        }
        else if (race == "Orc") {
            minHeight = 180; maxHeight = 220;
            minWeight = 80; maxWeight = 120;
        }
        else if (race == "Elf") {
            minHeight = 150; maxHeight = 180;
            minWeight = 50; maxWeight = 70;
        }
        else if (race == "Dwarf") {
            minHeight = 120; maxHeight = 150;
            minWeight = 70; maxWeight = 100;
        }

        // Height choice
        height = minHeight;
        weight = minWeight;
        bool validChoice = false;
        while (!validChoice) {
            system("cls");
            std::cout << "Adjust height and weight for your character using arrow keys.\n";
            std::cout << "Press Enter to confirm.\n";
            std::cout << "Height: " << height << " cm\n";
            std::cout << "Weight: " << weight << " kg\n";

            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72 && height < maxHeight) {  // Up arrow to increase size
                    height += 1;
                }
                else if (key == 80 && height > minHeight) {  // Down arrow to decrease size
                    height -= 1;
                }
                else if (key == 77 && weight < maxWeight) {  // Right arrow to increase weight
                    weight += 1;
                }
                else if (key == 75 && weight > minWeight) {  // Left arrow to decrease weight
                    weight -= 1;
                }
            }
            else if (key == 13) {
                validChoice = true;  // Confirmation with Enter
            }
        }
    }

    // Choosing the class
    std::string chooseClass() {
        std::string chosenClass;
        int classChoice = 0;
        bool validChoice = false;

        while (!validChoice) {
            system("cls");
            std::cout << "Choose a class (1: Mage, 2: Barbarian, 3: Thief, 4: Archer):\n";
            std::cout << "Use arrows to navigate, Enter to select.\n";

            displayClassMenu(classChoice);

            int key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72) {  // Up arrow
                    classChoice = (classChoice - 1 + 4) % 4;
                }
                else if (key == 80) {  // Down arrow
                    classChoice = (classChoice + 1) % 4;
                }
            }
            else if (key == 13) {  // Enter
                validChoice = true;
            }
        }

        switch (classChoice) {
        case 0:
            chosenClass = "Mage";
            weapon = "Magic Staff";
            specialAbility = "Spellcasting";
            magicItem = "Spellbook";
            break;
        case 1:
            chosenClass = "Barbarian";
            weapon = "War Axe";
            specialAbility = "Rage";
            magicItem = "Amulet of Strength";
            break;
        case 2:
            chosenClass = "Thief";
            weapon = "Daggers";
            specialAbility = "Stealth";
            magicItem = "Cloak of Invisibility";
            break;
        case 3:
            chosenClass = "Archer";
            weapon = "Bow";
            specialAbility = "Archery";
            magicItem = "Quiver of Endless Arrows";
            break;
        }

        return chosenClass;
    }

    // Display class options
    void displayClassMenu(int selectedOption) {
        std::string options[] = { "Mage", "Barbarian", "Thief", "Archer" };
        for (int i = 0; i < 4; ++i) {
            if (i == selectedOption)
                std::cout << "> " << options[i] << " <\n";  // Option Selected
            else
                std::cout << options[i] << "\n";
        }
    }

    // Allocate statistics (draw dice)
    void allocateStats() {
        std::cout << "\nRolling dice to assign stats...\n";

        int remainingStats = 6;  // Number of statistics to allocate
        while (remainingStats > 0) {
            int roll = rollDie(20);  // Roll a 20-sided die
            int chosenStat = selectStat(roll);  // Allows you to choose the stat where to allocate the die

            if (!locked[chosenStat]) {
                stats[chosenStat] = roll;  // Assign the die value to the chosen statistic
                locked[chosenStat] = true;  // Lock this statistic to prevent reuse
                remainingStats--;  // Reduce the number of statistics remaining to be allocated
            }
            else {
                std::cout << "This stat is already locked. Choose a different stat.\n";
            }
        }
    }

    // Roll an X-sided die
    int rollDie(int sides) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, sides);
        return dis(gen);
    }

    // Select a statistic to assign the die
    int selectStat(int roll) {
        int statChoice = 0;  // Index of selected statistic (starts at 0)
        bool chosen = false;  // Indicator of whether a statistic has been selected

        while (!chosen) {
            system("cls");  // Clear screen
            std::cout << "Select a stat to assign your roll. Press Enter to confirm.\n";
            displayStats(statChoice);  // Display statistics and the currently selected statistic

            std::cout << "\nYou rolled a " << roll << "!\n";// Display die result below statistics

            int key = _getch();  // Wait for user's entry
            if (key == 224) {
                key = _getch();  // Reading direction input (arrows)
                if (key == 72) {  // Up arrow
                    statChoice = (statChoice - 1 + 6) % 6;  // Move to previous statistic
                }
                else if (key == 80) {  // Down arrow
                    statChoice = (statChoice + 1) % 6;  // Move to next statistic
                }
            }
            else if (key == 13) {  // Enter button to confirm selection
                if (!locked[statChoice]) {
                    chosen = true;  // Validate selected statistic
                }
                else {
                    std::cout << "This stat is already locked. Choose a different stat.\n";
                }
            }
        }

        return statChoice;  // Return the index of the selected statistic
    }

    // display the stats
    void displayStats(int selectedOption) {
        for (int i = 0; i < 6; ++i) {
            if (i == selectedOption)
                std::cout << "> " << statNames[i] << ": " << stats[i] << " <\n";  // Option selected
            else
                std::cout << statNames[i] << ": " << stats[i] << "\n";
        }
    }

    // Choosing personality traits
    void choosePersonalityTraits() {
        std::string availableTraits[] = {
            "Brave", "Cunning", "Compassionate", "Honest", "Impulsive", "Curious",
            "Stoic", "Pessimistic", "Optimistic", "Friendly", "Loyal", "Adventurous"
        };
        int traitChoice[3] = { -1, -1, -1 }; // Index of selected features, -1 means not selected
        int currentChoice = 0;
        bool validChoice = false;

        while (!validChoice) {
            system("cls");
            std::cout << "Select 3 personality traits for your character:\n\n";

            // Display available features with arrow navigation
            for (int i = 0; i < 12; ++i) {
                if (i == currentChoice) {
                    std::cout << "> " << availableTraits[i] << " <\n";  // Option selected
                }
                else {
                    std::cout << availableTraits[i] << "\n";
                }
            }

            std::cout << "\nPress Enter to select a trait, Space to toggle selection, Esc to cancel.\n";
            std::cout << "\nSelected traits: ";
            for (int i = 0; i < 3; ++i) {
                if (traitChoice[i] != -1) {
                    std::cout << availableTraits[traitChoice[i]] << " ";
                }
            }

            int key = _getch();
            if (key == 224) {
                key = _getch();  // Reading directional keys
                if (key == 72) {  // Up arrow
                    currentChoice = (currentChoice - 1 + 12) % 12;
                }
                else if (key == 80) {  // Down arrow
                    currentChoice = (currentChoice + 1) % 12;
                }
            }
            else if (key == 13) {  // Enter
                // If the trait is not already selected, then select it
                bool alreadyChosen = false;
                for (int i = 0; i < 3; ++i) {
                    if (traitChoice[i] == currentChoice) {
                        alreadyChosen = true;
                        break;
                    }
                }
                if (!alreadyChosen) {
                    for (int i = 0; i < 3; ++i) {
                        if (traitChoice[i] == -1) {
                            traitChoice[i] = currentChoice;
                            break;
                        }
                    }
                }
            }
            else if (key == 32) {  // Space key to remove a selected stroke
                for (int i = 0; i < 3; ++i) {
                    if (traitChoice[i] == currentChoice) {
                        traitChoice[i] = -1;
                        break;
                    }
                }
            }
            else if (key == 27) {  // Escape key to cancel
                std::cout << "Trait selection canceled.\n";
                return;
            }

            // Check that 3 features have been selected
            int selectedCount = 0;
            for (int i = 0; i < 3; ++i) {
                if (traitChoice[i] != -1) selectedCount++;
            }
            if (selectedCount == 3) validChoice = true;
        }

        // Save selected features
        for (int i = 0; i < 3; ++i) {
            personalityTraits[i] = availableTraits[traitChoice[i]];
        }
    }
};

int main() {
    Character myCharacter;
    myCharacter.createCharacter();
    myCharacter.displayCharacterSheet();
    return 0;
}