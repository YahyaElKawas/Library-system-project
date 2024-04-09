#include <iostream>
#include <algorithm>
using namespace std;

struct book
{
    int id;
    string name;
    int quantity;
    int total_borrowed = 0;
};

book books[100];
int cnt_books = 0;

struct user
{
    string name;
    int id;
    book borrowed_books[100];
    int cnt_borrowed_books = 0;
};

user users[100];
int cnt_users = 0;


bool wether_exist(string book)
{
    for (int i = 0; i < cnt_books; i++)
    {
        if (books[i].name == book) return true;
    }
    return false;
}


void add_book()
{
    cout << "Enter book info: id & name & quantity: ";
    cin >> books[cnt_books].id;
    cin >> books[cnt_books].name;
    cin >> books[cnt_books].quantity;

    cnt_books++;
}



void print_by_prefix()
{
    cout << "Enter prefix: ";
    string prefix;
    cin >> prefix;
    bool wether_prefix_valid = false;

    for (int i = 0; i < cnt_books; i++)
    {
        bool search = true;
        for (int y = 0; y < prefix.size(); y++)
        {
            if (prefix[y] != books[i].name[y])
            {
                search = false;
                break;
            }
        }

        if (search)
        {
            cout << books[i].name << endl;
            wether_prefix_valid = true;
        }
    }

    if (!wether_prefix_valid)
    {
        cout << "There are no books with this prefix" << endl;
    }
}


bool sort_by_id(book first, book second)
{
    if (first.id < second.id) return true;
    else return false;
}

void print_library_by_id()
{
    sort(books, books + cnt_books, sort_by_id);

    for (int i = 0; i < cnt_books; i++)
    {
        cout << "id = " << books[i].id << " name = " << books[i].name << " quantity = " << books[i].quantity << " total borrowed = " << books[i].total_borrowed << endl;
    }
}



bool sort_by_name(book first, book second)
{
    if (first.name < second.name) return true;
    else return false;
}



void print_library_by_name()
{
    sort(books, books + cnt_books, sort_by_name);

    for (int i = 0; i < cnt_books; i++)
    {
        cout << "id = " << books[i].id << " name = " << books[i].name << " quantity = " << books[i].quantity << " total borrowed = " << books[i].total_borrowed << endl;
    }
}



void add_user()
{
    cout << "Enter user name & national id: ";
    cin >> users[cnt_users].name;
    cin >> users[cnt_users].id;

    cnt_users++;
}

bool user_exist(string name)
{
    for (int i = 0; i < cnt_users; i++)
    {
        if (users[i].name == name) return true;
    }

    return false;
}

void borrow_book()
{
    cout << "Enter user & book name: ";
    string user;
    string book;
    cin >> user;
    cin >> book;

    if (!wether_exist(book))
    {
        cout << "Sorry, we don't have this book" << endl;
        return;
    }

    if (!user_exist(user))
    {
        cout << "User not found, please register first" << endl;
        return;
    }


    for (int i = 0; i < cnt_books; i++)
    {
        if (book == books[i].name)
        {
            if (books[i].quantity == 0)
            {
                cout << "Sorry, this book is out of stock" << endl;
                return;
            }

            else
            {
                books[i].quantity--;
                books[i].total_borrowed++;
            }
        }
    }

    for (int x = 0; x < cnt_users; x++)
    {
        if (user == users[x].name)
        {
            users[x].borrowed_books[users[x].cnt_borrowed_books].name = book;
            // Getting the book borrowed id:
            for (int i = 0; i < cnt_books; i++)
            {
                if (book == books[i].name)
                {
                    users[x].borrowed_books[users[x].cnt_borrowed_books].id = books[i].id;
                    break;
                }
            }
            users[x].cnt_borrowed_books++;
        }
    }
}

void remove_book(int user_index, string book)
{
    int book_index;

    for (int i = 0; i < users[user_index].cnt_borrowed_books; i++)
    {
        if (users[user_index].borrowed_books[i].name == book)
        {
            book_index = i;
            break;
        }
    }

    for (int x = book_index; x < users[user_index].cnt_borrowed_books - 1; x++)
    {
        users[user_index].borrowed_books[x] = users[user_index].borrowed_books[x + 1];  
    }
    users[user_index].cnt_borrowed_books--;
}

void return_book()
{
    cout << "Enter user & book name: ";
    string user, book;
    cin >> user >> book;

    if (!wether_exist(book))
    {
        cout << "Sorry, we don't have this book" << endl;
        return;
    }

    if (!user_exist(user))
    {
        cout << "User not found, please register first" << endl;
        return;
    }

    for (int i = 0; i < cnt_users; i++)
    {
        if (users[i].name == user)
        {
            remove_book(i, book);
            break;
        }
    }

    for (int x = 0; x < cnt_books; x++)
    {
        if (books[x].name == book)
        {
            books[x].quantity++;
            books[x].total_borrowed--;
            break;
        }
    }
}


void print_who_borrowed_book()
{
    cout << "Enter book name: ";
    string name;
    cin >> name;

    if (!wether_exist(name))
    {
        cout << "This book doesn't exist in our library" << endl;
        return;
    }
    
    bool wether_its_borrowed = false;

    for (int i = 0; i < cnt_users; i++)
    {
        for (int y = 0; y < users[i].cnt_borrowed_books; y++)
        {
            if (users[i].borrowed_books[y].name == name)
            {
                cout << users[i].name << endl;
                wether_its_borrowed = true;
                break;
            }
        }
    }

    if (!wether_its_borrowed) cout << "Book isn't borrowed by someone" << endl;
}

int get_book_id(string book)
{
    for (int i = 0; i < cnt_books; i++)
    {
        if (book == books[i].name)
        {
            return books[i].id;
            break;
        }
    }
}

void print_users()
{
    for (int i = 0; i < cnt_users; i++)
    {
        cout << "User " << users[i].name << " national id " << users[i].id;

        if (users[i].cnt_borrowed_books == 0) cout << " No borrowed books.";
        else
        {
            cout << " Borrowed books ids: ";
            for (int x = 0; x < users[i].cnt_borrowed_books; x++)
            {
                cout << users[i].borrowed_books[x].id << " ";
            }
        }
    }
    cout << endl;
}

int main()
{
    cout << "Library Menu:" << endl;
    cout << "1) Add a book" << endl;
    cout << "2) Print books by prefix" << endl;
    cout << "3) Print who borrowed a book" << endl;
    cout << "4) Print library by id" << endl;
    cout << "5) Print library by name" << endl;
    cout << "6) Add user" << endl;
    cout << "7) User borrow a book" << endl;
    cout << "8) User return a book" << endl;
    cout << "9) Print Users" << endl;
    cout << "10) Exit" << endl;

    while (true)
    {   
        cout << "Enter your menu choice [1-10]: ";

        int choice;
        cin >> choice;

        if (!(1 <= choice && choice <= 10))
        {
            cout << "Invalid input, please try again." << endl;
            continue;
        }

        if (choice == 1)
        {
            add_book();
        }

        else if (choice == 2)
        {
            print_by_prefix();
        }

        else if (choice == 3)
        {
            print_who_borrowed_book();
        }

        else if (choice == 4)
        {
            print_library_by_id();
        }

        else if (choice == 5)
        {
            print_library_by_name();
        }

        else if (choice == 6)
        {
            add_user();
        }

        else if (choice == 7)
        {
            borrow_book();
        }

        else if (choice == 8)
        {
            return_book();
        }

        else if (choice == 9)
        {
            print_users();
        }

        else if (choice == 10) break;
    }
}
