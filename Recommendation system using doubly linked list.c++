#include <iostream> 
#include <string> 
#include <limits> // For numeric limits 
#include <algorithm> // For std::transform 
struct Node { 
 std::string title; 
 std::string category; 
 std::string type; 
 float rating; 
 Node* next; 
 Node* prev; 
}; 
class DoublyLinkedList { 
public: 
 Node* head; 
 DoublyLinkedList() : head(nullptr) {} 
 ~DoublyLinkedList() { 
 while (head) { 
 Node* temp = head; 
 head = head->next; 
 delete temp; 
 } 
 } 
 void insertAtEnd(const std::string& title, const std::string& category, const std::string& type,  float rating) { 
 Node* newNode = new Node{ title, category, type, rating, nullptr, nullptr };  if (!head) { 
 head = newNode; 
 } 
 else { 
 Node* temp = head; 
 while (temp->next) { 
 temp = temp->next; 
 } 
 temp->next = newNode; 
 newNode->prev = temp;
 } 
 } 
 void insertAtStart(const std::string& title, const std::string& category, const std::string& type,  float rating) { 
 Node* newNode = new Node{ title, category, type, rating, head, nullptr };  if (head) { 
 head->prev = newNode; 
 } 
 head = newNode; 
 } 
 void insertAtPosition(const std::string& title, const std::string& category, const std::string&  type, float rating, int position) { 
 if (position <= 1 || !head) { 
 insertAtStart(title, category, type, rating); 
 return; 
 } 
 Node* temp = head; 
 int currentPosition = 1; 
 while (temp->next && currentPosition < position - 1) { 
 temp = temp->next; 
 currentPosition++; 
 } 
 Node* newNode = new Node{ title, category, type, rating, temp->next, temp };  if (temp->next) { 
 temp->next->prev = newNode; 
 } 
 temp->next = newNode; 
 } 
 void display(const std::string& type = "") const { 
 Node* temp = head; 
 bool found = false; 
 std::cout << "\nDisplaying items:\n"; 
 while (temp) { 
 if (type.empty() || temp->type == type) { 
 std::cout << "Title: " << temp->title 
 << ", Category: " << temp->category 
 << ", Type: " << temp->type 
 << ", Rating: " << temp->rating << "\n"; 
 found = true; 
 } 
 temp = temp->next; 
 } 
 if (!found) {
 std::cout << "No matching items found.\n"; 
 } 
 } 
 void recommendBasedOnPreferences() const { 
 std::string category, type; 
 float minRating; 
 std::cout << "Enter category (e.g., Fiction, Adventure): "; 
 std::getline(std::cin, category); 
 std::cout << "Enter type (Book/Movie/Travel Destination): "; 
 std::getline(std::cin, type); 
 std::cout << "Enter minimum rating: "; 
 std::cin >> minRating; 
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
 // Convert user inputs to lowercase 
 std::transform(category.begin(), category.end(), category.begin(), ::tolower);  std::transform(type.begin(), type.end(), type.begin(), ::tolower); 
 Node* temp = head; 
 bool found = false; 
 std::cout << "\nRecommended items matching your preferences:\n";  while (temp) { 
 std::string lowerCategory = temp->category; 
 std::string lowerType = temp->type; 
 // Convert node data to lowercase 
 std::transform(lowerCategory.begin(), lowerCategory.end(), lowerCategory.begin(),  ::tolower); 
 std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower); 
 if (lowerCategory == category && lowerType == type && temp->rating >= minRating)  { 
 std::cout << "Title: " << temp->title 
 << ", Rating: " << temp->rating << "\n"; 
 found = true; 
 } 
 temp = temp->next; 
 } 
 if (!found) { 
 std::cout << "No recommendations found for the given preferences.\n";  } 
 } 
 void searchByTitle(const std::string& searchTitle) const {
 Node* temp = head; 
 bool found = false; 
 std::string lowerSearchTitle = searchTitle; 
 // Convert searchTitle to lowercase 
 std::transform(lowerSearchTitle.begin(), lowerSearchTitle.end(), lowerSearchTitle.begin(),  ::tolower); 
 std::cout << "\nSearching for \"" << searchTitle << "\":\n"; 
 while (temp) { 
 std::string lowerTitle = temp->title; 
 // Convert title in the node to lowercase 
 std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower); 
 if (lowerTitle == lowerSearchTitle) { 
 std::cout << "Found!\n" 
 << "Title: " << temp->title 
 << ", Category: " << temp->category 
 << ", Type: " << temp->type 
 << ", Rating: " << temp->rating << "\n"; 
 found = true; 
 break; 
 } 
 temp = temp->next; 
 } 
 if (!found) { 
 std::cout << "No item with the title \"" << searchTitle << "\" was found.\n";  } 
 } 
 void deleteByTitle(const std::string& searchTitle) { 
 Node* temp = head; 
 std::string lowerSearchTitle = searchTitle; 
 // Convert searchTitle to lowercase 
 std::transform(lowerSearchTitle.begin(), lowerSearchTitle.end(), lowerSearchTitle.begin(),  ::tolower); 
 while (temp) { 
 std::string lowerTitle = temp->title; 
 // Convert title in the node to lowercase 
 std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower); 
 if (lowerTitle == lowerSearchTitle) { 
 if (temp->prev) temp->prev->next = temp->next;
 if (temp->next) temp->next->prev = temp->prev; 
 if (temp == head) head = temp->next; 
 delete temp; 
 std::cout << "Deleted item with title \"" << searchTitle << "\".\n";  return; 
 } 
 temp = temp->next; 
 } 
 std::cout << "No item with the title \"" << searchTitle << "\" was found.\n";  } 
 void deleteAtStart() { 
 if (!head) { 
 std::cout << "List is empty.\n"; 
 return; 
 } 
 Node* temp = head; 
 head = head->next; 
 if (head) { 
 head->prev = nullptr; 
 } 
 delete temp; 
 std::cout << "Deleted item at the start.\n"; 
 } 
 void deleteAtEnd() { 
 if (!head) { 
 std::cout << "List is empty.\n"; 
 return; 
 } 
 if (!head->next) { 
 deleteAtStart(); 
 return; 
 } 
 Node* temp = head; 
 while (temp->next) { 
 temp = temp->next; 
 } 
 temp->prev->next = nullptr; 
 delete temp; 
 std::cout << "Deleted item at the end.\n"; 
 } 
}; 
void addSampleData(DoublyLinkedList& list) {
 list.insertAtEnd("The Night Circus", "Fiction", "Book", 4.0); 
 list.insertAtEnd("Where the Crawdads Sing", "Fiction", "Book", 4.6);  list.insertAtEnd("The Shawshank Redemption", "Fiction", "Movie", 4.65);  list.insertAtEnd("Forrest Gump", "Fiction", "Movie", 4.4); 
 list.insertAtEnd("Kaghan Valley", "Adventure", "Travel Destination", 4.6);  list.insertAtEnd("Cappadocia", "Adventure", "Travel Destination", 4.8);  list.insertAtEnd("Gone Girl", "Mystery/Thriller", "Book", 4.0); 
 list.insertAtEnd("Big Little Lies", "Mystery/Thriller", "Book", 4.3); 
 list.insertAtEnd("Catch-22", "Comedy", "Book", 4.5); 
 list.insertAtEnd("Hyperbole and a Half", "Comedy", "Book", 4.6); 
 list.insertAtEnd("A Court of Thorns and Roses", "Fantasy", "Book", 4.3);  list.insertAtEnd("The Name of the Wind", "Fantasy", "Book", 4.5); 
 list.insertAtEnd("Shutter Island", "Mystery/Thriller", "Movie", 4.1); 
 list.insertAtEnd("Prisoners", "Mystery/Thriller", "Movie", 4.0); 
 list.insertAtEnd("The 40-Year-Old Virgin", "Comedy", "Movie", 3.4);  list.insertAtEnd("Dumb and Dumber", "Comedy", "Movie", 3.6); 
 list.insertAtEnd("Harry Potter and the Sorcerer's Stone", "Fantasy", "Movie", 3.9);  list.insertAtEnd("Avatar", "Fantasy", "Movie", 3.9); 
 list.insertAtEnd("Burj Al Arab (Dubai, UAE)", "Luxury", "Travel Destination", 5.0);  list.insertAtEnd("Lake Como (Italy)", "Luxury", "Travel Destination", 4.9);  list.insertAtEnd("Swat Valley (Pakistan)", "Nature", "Travel Destination", 4.7);  list.insertAtEnd("Olympos National Park (Turkey)", "Nature", "Travel Destination", 4.6);  list.insertAtEnd("Al Ain Oasis (UAE)", "Historic", "Travel Destination", 4.6);  list.insertAtEnd("Taxila (Pakistan)", "Historic", "Travel Destination", 4.5); 
} 
int main() { 
 DoublyLinkedList list; 
 addSampleData(list); 
 int choice; 
 do { 
 std::cout << "\nMenu:\n"; 
 std::cout << "1. Display All Items\n2. Display Books\n3. Display Movies\n4. Display  Travel Destinations\n"; 
 std::cout << "5. Recommend Based on Preferences\n6. Search by Title\n7. Insert Item\n8.  Delete Item by Title\n9. Exit\n"; 
 std::cout << "Enter your choice: "; 
 std::cin >> choice; 
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
 switch (choice) { 
 case 1: 
 list.display(); 
 break; 
 case 2: 
 list.display("Book");
 break; 
 case 3: 
 list.display("Movie"); 
 break; 
 case 4: 
 list.display("Travel Destination"); 
 break; 
 case 5: 
 list.recommendBasedOnPreferences(); 
 break; 
 case 6: { 
 std::string searchTitle; 
 std::cout << "Enter the title to search: "; 
 std::getline(std::cin, searchTitle); 
 list.searchByTitle(searchTitle); 
 break; 
 } 
 case 7: { 
 std::string title, category, type; 
 float rating; 
 int position; 
 std::cout << "Enter title: "; 
 std::getline(std::cin, title); 
 std::cout << "Enter category: "; 
 std::getline(std::cin, category); 
 std::cout << "Enter type (Book/Movie/Travel Destination): "; 
 std::getline(std::cin, type); 
 std::cout << "Enter rating: "; 
 std::cin >> rating; 
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  std::cout << "Enter position (1 for start, -1 for end, any other for specific position): ";  std::cin >> position; 
 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  if (position == 1) { 
 list.insertAtStart(title, category, type, rating); 
 } 
 else if (position == -1) { 
 list.insertAtEnd(title, category, type, rating); 
 } 
 else { 
 list.insertAtPosition(title, category, type, rating, position); 
 } 
 break; 
 } 
 case 8: { 
 std::string title;
 std::cout << "Enter the title to delete: "; 
 std::getline(std::cin, title); 
 list.deleteByTitle(title); 
 break; 
 } 
 case 9: 
 std::cout << "Exiting program...\n"; 
 break; 
 default: 
 std::cout << "Invalid choice. Try again.\n"; 
 } 
 } while (choice != 9); 
 return 0; 
} 
