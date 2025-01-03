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
                cout << "책의 이름 '" << title << "'을 검색하셨습니다.\n";
                cout << "작가: " << Books[i].getAuthor()
                    << ", 위치: " << Books[i].getSerial() << endl;
                return;
            }
        }
        cout << "책 '" << title << "'은 목록에 없습니다.\n";
    }

    void searchByAuthor(string author)
    {
        for (int i = 0; i < Books.size(); i++)
        {
            if (author == Books[i].getAuthor())
            {
                cout << "작가 '" << author << "'의 책을 검색하셨습니다.\n";
                cout << "책 이름: " << Books[i].getTitle()
                    << ", 위치: " << Books[i].getSerial() << endl;
                return;
            }
        }
        cout << "작가 '" << author << "'의 책은 목록에 없습니다.\n";
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
            cout << "책 '" << title << "'은 재고가 없습니다.\n";
            return;
        }

        if (borrowed[title] >= 3)
        {
            cout << "책 '" << title << "'은 이미 3권이 대여 중입니다.\n";
            return;
        }

        if (stock[title] > 0)
        {
            stock[title]--;
            borrowed[title]++;
            cout << "책 '" << title << "'을 성공적으로 대여했습니다.\n";
        }
        else
        {
            cout << "책 '" << title << "'의 재고가 부족합니다.\n";
        }
    }

    void returnBook(string title)
    {
        if (borrowed[title] > 0)
        {
            stock[title]++;
            borrowed[title]--;
            cout << "책 '" << title << "'을 성공적으로 반납했습니다.\n";
        }
        else
        {
            cout << "책 '" << title << "'은 대여 기록이 없습니다.\n";
        }
    }

    void displayStock()
    {
        cout << "=== 현재 재고 상태 ===\n";
        for (auto& entry : stock)
        {
            cout << "책 제목: " << entry.first
                << ", 재고: " << entry.second
                << ", 대여 중: " << borrowed[entry.first] << "\n";
        }
    }
};

int main()
{
    fastio();

    BookManager bookManager;
    BorrowManager borrowManager;

    // 책 추가
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
        borrowManager.initializeStock(get<0>(books[i]), 3); // 각 책 초기 재고는 3권
    }

    // 책 목록 출력
    cout << "=== 전체 책 목록 ===\n";
    bookManager.displayAllBooks();

    // 책 검색 테스트
    cout << "\n=== 검색 테스트 ===\n";
    bookManager.searchByTitle("1984");
    bookManager.searchByAuthor("Leo Tolstoy");
    bookManager.searchByTitle("Unknown Book");
    bookManager.searchByAuthor("Unknown Author");

    // 책 대여 테스트
    cout << "\n=== 대여 테스트 ===\n";
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984");
    borrowManager.borrowBook("1984"); // 4번째 대여 시도

    // 책 반납 테스트
    cout << "\n=== 반납 테스트 ===\n";
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984");
    borrowManager.returnBook("1984"); // 더 이상 반납할 책이 없음

    // 재고 상태 출력
    cout << "\n=== 재고 상태 ===\n";
    borrowManager.displayStock();

    return 0;
}
