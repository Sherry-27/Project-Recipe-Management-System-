#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct Recipe {
    string name;
    string ingredients;
    string instructions;
    Recipe* next;
};

Recipe* createRecipeNode(string name, string ingredients, string instructions) {
    Recipe* newNode = new Recipe;
    newNode->name = name;
    newNode->ingredients = ingredients;
    newNode->instructions = instructions;
    newNode->next = NULL;
    return newNode;
}

void insertRecipe(Recipe* &head, string name, string ingredients, string instructions) {
    Recipe* newNode = createRecipeNode(name, ingredients, instructions);
    if (head == NULL) {
        head = newNode;
    } else {
        Recipe* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

Recipe* searchRecipe(Recipe* head, string name) {
    Recipe* current = head;
    while (current != NULL) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteRecipe(Recipe* &head, string name, stack<Recipe*> &deletedRecipes) {
    Recipe* current = head;
    Recipe* prev = NULL;
    while (current != NULL && current->name != name) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return;
    }
    if (prev == NULL) {
        head = head->next;
    } else {
        prev->next = current->next;
    }
    deletedRecipes.push(current);
    cout << "Recipe deleted and added to undo stack.\n";
}

void undoDelete(Recipe* &head, stack<Recipe*> &deletedRecipes) {
    if (deletedRecipes.empty()) {
        cout << "No recipes to undo delete.\n";
        return;
    }
    Recipe* recipe = deletedRecipes.top();
    deletedRecipes.pop();
    recipe->next = head;
    head = recipe;
    cout << "Undo successful: " << recipe->name << " restored.\n";
}

void printRecipe(Recipe* recipe) {
    if (recipe != NULL) {
        cout << "Name: " << recipe->name << endl;
        cout << "Ingredients: " << recipe->ingredients << endl;
        cout << "Instructions: " << recipe->instructions << endl;
    } else {
        cout << "Recipe not found." << endl;
    }
}

void displayRecipes(Recipe* head) {
    Recipe* current = head;
    while (current != NULL) {
        cout << current->name << endl;
        current = current->next;
    }
}

void deleteAllRecipes(Recipe* &head) {
    Recipe* current = head;
    Recipe* next = NULL;
    while (current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }
    head = NULL;
}



void swap(Recipe* a, Recipe* b) {
    string tempName = a->name;
    string tempIngredients = a->ingredients;
    string tempInstructions = a->instructions;

    a->name = b->name;
    a->ingredients = b->ingredients;
    a->instructions = b->instructions;

    b->name = tempName;
    b->ingredients = tempIngredients;
    b->instructions = tempInstructions;
}

void sortRecipes(Recipe* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }
    bool swapped;
    Recipe* ptr1;
    Recipe* lptr = NULL;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->name > ptr1->next->name) {
                swap(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int main() {
    Recipe* head = NULL;
    stack<Recipe*> deletedRecipes;

    insertRecipe(head, "Pasta Carbonara", "Spaghetti, eggs, bacon, Parmesan cheese, black pepper", "Cook spaghetti; fry bacon; mix eggs, cheese, and pepper; combine all ingredients.");
    insertRecipe(head, "Chicken Curry", "Chicken, onions, tomatoes, curry powder, coconut milk", "Saute onions; add chicken and curry powder; pour coconut milk; simmer until chicken is cooked.");
    insertRecipe(head, "Chocolate Cake", "Flour, cocoa powder, baking powder, sugar, eggs, milk, butter", "Mix dry ingredients; add wet ingredients; bake at 350F for 30 minutes.");

    int choice;
    string name, ingredients, instructions;

    do {
        cout << "\nRecipe Management System\n";
        cout << "1. Add a Recipe\n";
        cout << "2. Search for a Recipe\n";
        cout << "3. Display All Recipe Names\n";
        cout << "4. Delete a Recipe\n";
        cout << "5. Delete All Recipes\n";
        cout << "6. Sort Recipes by Name\n";
        cout << "7. Undo Last Deletion\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter the name of the recipe: ";
                getline(cin, name);
                cout << "Enter the ingredients: ";
                getline(cin, ingredients);
                cout << "Enter the instructions: ";
                getline(cin, instructions);
                insertRecipe(head, name, ingredients, instructions);
                cout << "Recipe added successfully.\n";
                printRecipe(searchRecipe(head, name));
                break;
            case 2:
                cout << "Enter the name of the recipe to search: ";
                getline(cin, name);
                printRecipe(searchRecipe(head, name));
                break;
            case 3:
                cout << "List of Available Recipes:\n";
                displayRecipes(head);
                break;
            case 4:
                cout << "Enter the name of the recipe to delete: ";
                getline(cin, name);
                deleteRecipe(head, name, deletedRecipes);
                break;
            case 5:
                deleteAllRecipes(head);
                cout << "All recipes deleted successfully.\n";
                break;
            case 6:
                sortRecipes(head);
                cout << "Recipes sorted successfully.\n";
                break;
            case 7:
                undoDelete(head, deletedRecipes);
                break;
            case 8:
                
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
