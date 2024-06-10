#include <iostream>
#include <string>

using namespace std;

struct Recipe {
    string name;
    string ingredients;
    string instructions;
    Recipe* left;
    Recipe* right;
};

Recipe* createRecipeNode(string name, string ingredients, string instructions) {
    Recipe* newNode = new Recipe;
    newNode->name = name;
    newNode->ingredients = ingredients;
    newNode->instructions = instructions;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Recipe* insertRecipe(Recipe* root, string name, string ingredients, string instructions) {
    if (root == NULL) {
        return createRecipeNode(name, ingredients, instructions);
    }
    if (name < root->name) {
        root->left = insertRecipe(root->left, name, ingredients, instructions);
    } else if (name > root->name) {
        root->right = insertRecipe(root->right, name, ingredients, instructions);
    }
    return root;
}

Recipe* searchRecipe(Recipe* root, string name) {
    if (root == NULL || root->name == name) {
        return root;
    }
    if (name < root->name) {
        return searchRecipe(root->left, name);
    } else {
        return searchRecipe(root->right, name);
    }
}

Recipe* deleteRecipe(Recipe* root, string name) {
    if (root == NULL) {
        return root;
    }
    if (name < root->name) {
        root->left = deleteRecipe(root->left, name);
    } else if (name > root->name) {
        root->right = deleteRecipe(root->right, name);
    } else {
        if (root->left == NULL) {
            Recipe* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Recipe* temp = root->left;
            delete root;
            return temp;
        }
        Recipe* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        root->name = temp->name;
        root->ingredients = temp->ingredients;
        root->instructions = temp->instructions;
        root->right = deleteRecipe(root->right, temp->name);
    }
    return root;
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

void displayRecipes(Recipe* root) {
    if (root != NULL) {
        displayRecipes(root->left);
        cout << root->name << endl;
        displayRecipes(root->right);
    }
}

void deleteAllRecipes(Recipe* &root) {
    if (root != NULL) {
        deleteAllRecipes(root->left);
        deleteAllRecipes(root->right);
        delete root;
        root = NULL;
    }
}

void deleteTree(Recipe* node) {
    if (node != NULL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    Recipe* root = NULL;

    root = insertRecipe(root, "Pasta Carbonara", "Spaghetti, eggs, bacon, Parmesan cheese, black pepper", "Cook spaghetti; fry bacon; mix eggs, cheese, and pepper; combine all ingredients.");
    root = insertRecipe(root, "Chicken Curry", "Chicken, onions, tomatoes, curry powder, coconut milk", "Saute onions; add chicken and curry powder; pour coconut milk; simmer until chicken is cooked.");
    root = insertRecipe(root, "Chocolate Cake", "Flour, cocoa powder, baking powder, sugar, eggs, milk, butter", "Mix dry ingredients; add wet ingredients; bake at 350F for 30 minutes.");

    int choice;
    string name, ingredients, instructions;
    
    do {
        cout << "\nRecipe Management System\n";
        cout << "1. Add a Recipe\n";
        cout << "2. Search for a Recipe\n";
        cout << "3. Display All Recipe Names\n";
        cout << "4. Delete a Recipe\n";
        cout << "5. Delete All Recipes\n";
        cout << "6. Exit\n";
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
                root = insertRecipe(root, name, ingredients, instructions);
                cout << "Recipe added successfully.\n";
                printRecipe(searchRecipe(root, name)); 
                break;
            case 2:
                cout << "Enter the name of the recipe to search: ";
                getline(cin, name);
                printRecipe(searchRecipe(root, name));
                break;
            case 3:
                cout << "List of Available Recipes:\n";
                displayRecipes(root);
                break;
            case 4:
                cout << "Enter the name of the recipe to delete: ";
                getline(cin, name);
                root = deleteRecipe(root, name);
                cout << "Recipe deleted successfully.\n";
                break;
            case 5:
                deleteAllRecipes(root);
                root = NULL; 
                cout << "All recipes deleted successfully.\n";
                break;
            case 6:
                deleteTree(root);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
