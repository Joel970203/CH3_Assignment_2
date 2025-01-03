#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#define fastio() ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

class Book
{
private:
    string title;
    string author;
    string serial;

public:
    Book(string title, string author, string serial)
    {
        this->title = title;
        this->author = author;
        this->serial = serial;
    }
    string getTitle() { return this->title; }
    string getAuthor() { return this->author; }
    string getSerial() { return this->serial; }
};

class BookManager
{
private:
    vector<Book> Books;

public:
    void addBook(string title, string author, string serial)
    {
        Books.push_back(Book(title, author, serial));
    }

    void displayAllBooks()
    {
        for (int i = 0; i < Books.size(); i++)
        {
            cout << i + 1 << ": " << Books[i].getTitle()
                << " By " << Books[i].getAuthor()
                << " Placed at " << Books[i].getSerial() << endl;
        }
    }

    void searchByTitle(string title)
    {
        for (int i = 0; i < Books.size(); i++)
        {
            if (title == Books[i].getTitle())
            {
                cout << "å�� �̸� '" << title << "'�� �˻��ϼ̽��ϴ�.\n";
                cout << "�۰�: " << Books[i].getAuthor()
                    << ", ��ġ: " << Books[i].getSerial() << endl;
                return;
            }
        }
        cout << "å '" << title << "'�� ��Ͽ� �����ϴ�.\n";
    }

    void searchByAuthor(string author)
    {
        for (int i = 0; i < Books.size(); i++)
        {
            if (author == Books[i].getAuthor())
            {
                cout << "�۰� '" << author << "'�� å�� �˻��ϼ̽��ϴ�.\n";
                cout << "å �̸�: " << Books[i].getTitle()
                    << ", ��ġ: " << Books[i].getSerial() << endl;
                return;
            }
        }
        cout << "�۰� '" << author << "'�� å�� ��Ͽ� �����ϴ�.\n";
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock;
    unordered_map<string, int> borrowed;

public:
    void initializeStock(string title, int quantity)
    {
        stock[title] = quantity;
    }

    void borrowBook(string title)
    {
        if (stock.find(title) == stock.end())
        {
            cout << "å '" << title << "'�� ��� �����ϴ�.\n";
            return;
        }

        if (borrowed[title] >= 3)
        {
            cout << "å '" << title << "'�� �̹� 3���� �뿩 ���Դϴ�.\n";
            return;
        }

        if (stock[title] > 0)
        {
            stock[title]--;
            borrowed[title]++;
            cout << "å '" << title << "'�� ���������� �뿩�߽��ϴ�.\n";
        }
        else
        {
            cout << "å '" << title << "'�� ��� �����մϴ�.\n";
        }
    }

    void returnBook(string title)
    {
        if (borrowed[title] > 0)
        {
            stock[title]++;
            borrowed[title]--;
            cout << "å '" << title << "'�� ���������� �ݳ��߽��ϴ�.\n";
        }
        else
        {
            cout << "å '" << title << "'�� �뿩 ����� �����ϴ�.\n";
        }
    }

    void displayStock()
    {
        cout << "=== ���� ��� ���� ===\n";
        for (auto& entry : stock)
        {
            cout << "å ����: " << entry.first
                << ", ���: " << entry.second
                << ", �뿩 ��: " << borrowed[entry.first] << "\n";
        }
    }
};

int main()
{
    fastio();

    BookManager bookManager;
    BorrowManager borrowManager;

    // å �߰�
    vector<tuple<string, string, string>> books = {
        {"The Great Gatsby", "F. Scott Fitzgerald", "Shelf A1"},
        {"Moby Dick", "Herman Melville", "Shelf A2"},
        {"1984", "George Orwell", "Shelf A3"},
        {"Pride and Prejudice", "Jane Austen", "Shelf A4"},
        {"To Kill a Mockingbird", "Harper Lee", "Shelf B1"},
        {"The Catcher in the Rye", "J.D. Salinger", "Shelf B2"},
        {"War and Peace", "Leo Tolstoy", "Shelf B3"},
        {"The Odyssey", "Homer", "Shelf C1"},
        {"Ulysses", "James Joyce", "Shelf C2"},
        {"Crime and Punishment", "Fyodor Dostoevsky", "Shelf C3"} };

    for (int i = 0; i < books.size(); i++)
    {
        bookManager.addBook(get<0>(books[i]), get<1>(books[i]), get<2>(books[i]));
        borrowManager.initializeStock(get<0>(books[i]), 3); // �� å �ʱ� ���� 3��
    }

    // å ��� ���
    cout << "=== ��ü å ��� ===\n";
    bookManager.displayAllBooks();

    // å �˻� �׽�Ʈ
    cout << "\n=== �˻� �׽�Ʈ ===\n";
    bookManager.searchByTitle("1984");
    bookManager.searchByAuthor("Leo Tolstoy");
    bookManager.searchByTitle("Unknown Book");
    bookManager.searchByAuthor("Unknown Author");

    // å �뿩 �׽�Ʈ
    cout << "\n=== �뿩 �׽�Ʈ ===\n";
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984"); // 4��° �뿩 �õ�

    // å �ݳ� �׽�Ʈ
    cout << "\n=== �ݳ� �׽�Ʈ ===\n";
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984"); // �� �̻� �ݳ��� å�� ����

    // ��� ���� ���
    cout << "\n=== ��� ���� ===\n";
    borrowManager.displayStock();

    return 0;
}
