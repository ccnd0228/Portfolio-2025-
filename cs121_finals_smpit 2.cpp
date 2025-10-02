#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <cstdlib> 

using namespace std;


class InventoryException : public runtime_error {
public:
    InventoryException(const string& message) : runtime_error(message) {}
};


class Item {
public:
    virtual void display() const = 0;          
    virtual void save(ofstream& ofs) const = 0;
    virtual ~Item() {}
};


class Product : public Item {
public:
    string id;
    string name;
    string author;
    string category;
    int quantity;
    float price;

    Product() {
        quantity = 0;
        price = 0.0f;
    }

    void display() const {
        cout << left << setw(11) << id
             << setw(25) << name
             << setw(20) << author
             << setw(15) << category
             << setw(9)  << quantity
             << "?" << fixed << setprecision(2) << price << "\n";
    }

    void save(ofstream& ofs) const {
        ofs << id << "," << name << "," << author << ","
            << category << "," << quantity << "," << price << "\n";
    }


    friend ostream& operator<<(ostream& os, const Product& p) {
        p.display();
        return os;
    }

    bool operator==(const Product& other) const {
        return id == other.id;
    }
};


class Inventory {
private:
    vector<Item*> products;

public:
    ~Inventory() {
        for (size_t i = 0; i < products.size(); ++i) {
            delete products[i];
        }
    }

    void saveToFile(const string& filename) {
        ofstream ofs(filename.c_str());
        if (!ofs) throw InventoryException("Error saving to file.");
        for (size_t i = 0; i < products.size(); ++i) {
            products[i]->save(ofs);
        }
        ofs.close();
    }

    void loadFromFile(const string& filename) {
        for (size_t i = 0; i < products.size(); ++i)
            delete products[i];
        products.clear();

        ifstream ifs(filename.c_str());
        if (!ifs) return;

        string line;
        while (getline(ifs, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string token;

            Product* p = new Product();

            if (!getline(ss, token, ',')) { delete p; continue; }
            p->id = token;

            if (!getline(ss, token, ',')) { delete p; continue; }
            p->name = token;

            if (!getline(ss, token, ',')) { delete p; continue; }
            p->author = token;

            if (!getline(ss, token, ',')) { delete p; continue; }
            p->category = token;

            if (!getline(ss, token, ',')) { delete p; continue; }
            p->quantity = atoi(token.c_str());

            if (!getline(ss, token)) { delete p; continue; }
            p->price = (float)atof(token.c_str());

            products.push_back(p);
        }

        ifs.close();
    }

    void addProduct(Product* p, const string& filename) {
        products.push_back(p);
        saveToFile(filename);
    }

    Product* findProductById(const string& id) {
        for (size_t i = 0; i < products.size(); ++i) {
            Product* p = dynamic_cast<Product*>(products[i]);
            if (p != NULL && p->id == id) return p;
        }
        return NULL;
    }

    vector<Product*> findProductsByName(const string& name) {
        vector<Product*> matches;
        for (size_t i = 0; i < products.size(); ++i) {
            Product* p = dynamic_cast<Product*>(products[i]);
            if (p != NULL && p->name.find(name) != string::npos) {
                matches.push_back(p);
            }
        }
        return matches;
    }

    vector<Product*> findProductsByAuthor(const string& author) {
        vector<Product*> matches;
        for (size_t i = 0; i < products.size(); ++i) {
            Product* p = dynamic_cast<Product*>(products[i]);
            if (p != NULL && p->author.find(author) != string::npos) {
                matches.push_back(p);
            }
        }
        return matches;
    }

    const vector<Item*>& getAllProducts() const {
        return products;
    }

    bool deleteProductById(const string& id, const string& filename) {
        for (size_t i = 0; i < products.size(); ++i) {
            Product* p = dynamic_cast<Product*>(products[i]);
            if (p != NULL && p->id == id) {
                delete products[i];
                products.erase(products.begin() + i);
                saveToFile(filename);
                return true;
            }
        }
        return false;
    }

    float calculateTotalValue() const {
        float total = 0.0f;
        for (size_t i = 0; i < products.size(); ++i) {
            Product* p = dynamic_cast<Product*>(products[i]);
            if (p != NULL)
                total += p->quantity * p->price;
        }
        return total;
    }
};



void displayAllProducts(const vector<Item*>& inventory) {
    if (inventory.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\nProduct ID  Book Title               Author              Category       Quantity  Price\n";
    cout << "--------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < inventory.size(); ++i) {
        Product* p = dynamic_cast<Product*>(inventory[i]);
        if (p != NULL)
            p->display();
    }

    cout << "--------------------------------------------------------------------------------------------\n";
}


int countAvailableProducts(const vector<Item*>& products, int index = 0) {
    if (index >= (int)products.size()) return 0;
    Product* p = dynamic_cast<Product*>(products[index]);
    int countRest = countAvailableProducts(products, index + 1);
    if (p != NULL && p->quantity > 0) return 1 + countRest;
    else return countRest;
}

void addProduct(Inventory& inventory, const string& filename) {
    Product* p = new Product();
    try {
        cout << "\nAdd Product\n";

        cout << "Product ID: ";
        getline(cin, p->id);

        cout << "Book Title: ";
        getline(cin, p->name);

        cout << "Author Name: ";
        getline(cin, p->author);

        cout << "Category: ";
        getline(cin, p->category);

        cout << "Quantity: ";
        if (!(cin >> p->quantity) || p->quantity < 0) {
            throw InventoryException("Invalid quantity input.");
        }

        cout << "Price: ";
        if (!(cin >> p->price) || p->price < 0) {
            throw InventoryException("Invalid price input.");
        }
        cin.ignore(10000, '\n');

        inventory.addProduct(p, filename);
        cout << "Product added successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
        cin.clear();
        cin.ignore(10000, '\n');
        delete p;
    }
}

void searchProduct(Inventory& inventory) {
    int option;
    cout << "\nSearch Product\n1. By ID\n2. By Title\n3. By Author\nChoice: ";
    while (!(cin >> option) || option < 1 || option > 3) {
        cout << "Invalid choice. Enter 1-3: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    if (option == 1) {
        string id;
        cout << "Enter Product ID: ";
        getline(cin, id);

        Product* p = inventory.findProductById(id);
        if (p != NULL) {
            cout << "Found Product:\n";
            p->display();
        }
        else {
            cout << "Product not found.\n";
        }

    }
    else if (option == 2) {
        string name;
        cout << "Enter Product Title (or part): ";
        getline(cin, name);
        vector<Product*> results = inventory.findProductsByName(name);
        if (results.size() > 0) {
            cout << "\nMatching Products:\n";
            cout << "Product ID  Book Title               Author              Category       Quantity  Price\n";
            cout << "--------------------------------------------------------------------------------------------\n";
            for (size_t i = 0; i < results.size(); ++i) {
                results[i]->display();
            }
            cout << "--------------------------------------------------------------------------------------------\n";
        }
        else {
            cout << "No matching products found.\n";
        }
    }
    else if (option == 3) {
        string author;
        cout << "Enter Author Name (or part): ";
        getline(cin, author);
        vector<Product*> results = inventory.findProductsByAuthor(author);
        if (results.size() > 0) {
            cout << "\nMatching Products:\n";
            cout << "Product ID  Book Title               Author              Category       Quantity  Price\n";
            cout << "--------------------------------------------------------------------------------------------\n";
            for (size_t i = 0; i < results.size(); ++i) {
                results[i]->display();
            }
            cout << "--------------------------------------------------------------------------------------------\n";
        }
        else {
            cout << "No products found for that author.\n";
        }
    }
}

void deleteProduct(Inventory& inventory, const string& filename) {
    string id;
    cout << "\nDelete Product\nEnter Product ID: ";
    getline(cin, id);

    if (inventory.deleteProductById(id, filename)) {
        cout << "Product deleted.\n";
    }
    else {
        cout << "Product not found.\n";
    }
}

void showTotalInventoryValue(Inventory& inventory) {
    float total = inventory.calculateTotalValue();
    cout << "\nTotal Inventory Value: ?" << fixed << setprecision(2) << total << "\n";
}

void editProduct(Inventory& inventory, const string& filename) {
    string id;
    cout << "\nUpdate Stock / Price\nEnter Product ID: ";
    getline(cin, id);

    Product* p = inventory.findProductById(id);
    if (p == NULL) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Current Quantity: " << p->quantity << "\n";
    cout << "1. Add to Stock (Stock In)\n";
    cout << "2. Deduct from Stock (Stock Out)\n";
    cout << "3. Keep Quantity Unchanged\n";
    cout << "Choice: ";

    int stockChoice;
    while (!(cin >> stockChoice) || stockChoice < 1 || stockChoice > 3) {
        cout << "Invalid input. Enter 1-3: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    int amount = 0;
    if (stockChoice == 1) {
        cout << "Enter amount to add: ";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid input. Enter a positive number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        p->quantity += amount;
        cout << "Stock increased. New quantity: " << p->quantity << "\n";
    }
    else if (stockChoice == 2) {
        cout << "Enter amount to deduct: ";
        while (!(cin >> amount) || amount <= 0) {
            cout << "Invalid input. Enter a positive number: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (amount > p->quantity) {
            cout << "Cannot deduct more than available stock.\n";
        }
        else {
            p->quantity -= amount;
            cout << "Stock decreased. New quantity: " << p->quantity << "\n";
        }
    }
    cin.ignore(10000, '\n');

    cout << "Current Price: ?" << fixed << setprecision(2) << p->price << "\n";
    cout << "New Price (-1 to keep unchanged): ";
    float newPrice;
    while (!(cin >> newPrice) || newPrice < -1) {
        cout << "Invalid input. Enter -1 or a non-negative number: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore(10000, '\n');

    if (newPrice != -1) {
        p->price = newPrice;
        cout << "Price updated.\n";
    }

    try {
        inventory.saveToFile(filename);
        cout << "Product updated successfully.\n";
    }
    catch (const InventoryException& e) {
        cout << "Error saving changes: " << e.what() << "\n";
    }
}



int main() {
    Inventory inventory;
    string filename = "smbookstoreproducts.txt";

    inventory.loadFromFile(filename);

    while (true) {
        cout << "\n================ SM Bookstore Inventory System ================\n";
        cout << "1. Add Product\n"
			 << "2. Display All Products\n"
			 << "3. Search Product\n"
			 << "4. Delete Product\n"
			 << "5. Update Stock/Price\n"
			 << "6. Total Inventory Value\n"
			 << "7. Count Available Products\n"
			 << "8. Exit\n";
         cout << "================================================================\n";
		cout << "Enter your choice: ";

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        switch (choice) {
        case 1:
            addProduct(inventory, filename);
            break;
        case 2:
            displayAllProducts(inventory.getAllProducts());
            break;
        case 3:
            searchProduct(inventory);
            break;
        case 4:
            deleteProduct(inventory, filename);
            break;
        case 5:
            editProduct(inventory, filename);
            break;
        case 6:
            showTotalInventoryValue(inventory);
            break;
        case 7: {
            int count = countAvailableProducts(inventory.getAllProducts());
            cout << "\nNumber of available products (quantity > 0): " << count << "\n";
            break;
        }
        case 8:
            cout << "Exiting program...\n";
            return 0;
        default:
            cout << "Invalid choice! Please select 1-8.\n";
        }
    }
}

