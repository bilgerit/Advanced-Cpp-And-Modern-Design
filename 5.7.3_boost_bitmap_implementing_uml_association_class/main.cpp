// UML Association Class
// 
// We use bimaps and multimaps to logically model associations between types.
// Exemplary, an Author can write multiple books, and books can be written by
// multiple authors.
// However, each book has only one abstract, and each abstract can be found
// in only one book (ideally).
// 
// Tobias Bilgeri, 28.1.2024
#include <iostream>
#include <tuple>
#include <map>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

// Define the author-to-book multimap type (1:N)
using AuthorToBook = std::multimap<std::string, std::string>;

// Define the book-to-attributes bimap type (1:1)
using BookSet = boost::bimaps::unordered_set_of<std::string>;
using Attributes = std::tuple<std::string, double>;
using BookAttributes = boost::bimaps::unordered_set_of<Attributes>;
using BookToAttributes = boost::bimap<BookSet, BookAttributes>;

int main() {
    // create author to book multimap
    AuthorToBook authorToBookMap;

    authorToBookMap.insert({ "Author1", "Book1" });
    authorToBookMap.insert({ "Author1", "Book2" });
    authorToBookMap.insert({ "Author2", "Book2" });
    authorToBookMap.insert({ "Author2", "Book3" });

    // print author and associated books
    std::cout << "Author-to-Book multimap: \n";
    for (const auto& [author, book] : authorToBookMap) {
        std::cout << "Author: " << author << ", \tBook: " << book << "\n";
    }

    // create book to attributes bimap
    BookToAttributes bookToAttributes;

    bookToAttributes.insert(BookToAttributes::value_type("Book1", std::make_tuple("Abstract for Book1", 19.99)));
    bookToAttributes.insert(BookToAttributes::value_type("Book2", std::make_tuple("Abstract for Book2", 29.99)));
    bookToAttributes.insert(BookToAttributes::value_type("Book3", std::make_tuple("Abstract for Book3", 39.99)));

    // print books and associated attriutes
    std::cout << "\nBook-to-Attributes bimap: \n";
    for (const auto& [book, attributes] : bookToAttributes) {
        std::cout << "Book: " << book << ", \tAbstract: " << std::get<0>(attributes) << ", \tPrice: " << std::get<1>(attributes) << "\n";
    }

    // print price of books from given author: Author1.
    std::cout << "\nPrices of books by Author1: \n";
    
    // find all keys in multimap w/ value Author1 
    // (due to sorting, they will be in a range ... hence use equal_range to query start and end iterators.
    auto [start, end] = authorToBookMap.equal_range("Author1"); 
    
    std::string book;
    Attributes attr;
    double price;

    for (auto i = start; i != end; i++) {
        book = i->second;
        attr = bookToAttributes.left.at(book);
        price = std::get<1>(attr);
        std::cout << "Book: " << book << ", \tPrice: " << price << "\n";
    }

    return 0;
}