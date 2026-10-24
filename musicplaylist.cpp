#include <iostream>
#include <string>
#include <limits>
using namespace std;

class Node {
public:
    string title;
    string artist;
    Node* prev;
    Node* next;
    Node(string t, string a) {
        title = t;
        artist = a;
        prev = nullptr;
        next = nullptr;
    }
};

class MusicPlaylist {
private:
    Node* head;
    Node*current ;
    bool sameTitle(const string& a, const string& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); i++)
            if (tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])) return false;
        return true;
    }
public:
    MusicPlaylist() {
        head = nullptr;
        current = nullptr;
    }
    ~MusicPlaylist() {
        Node* q = head;
        while (q != nullptr) {
            Node* p = q;
            q = q->next;
            delete p;
        }
    }

    void addSong(string title, string artist) {
        Node* p = new Node(title, artist);
        if (head == nullptr) {
            head = p;
            current = p;
        } else {
            Node* q = head;
            while (q->next != nullptr) {
                q = q->next;
            }
            q->next = p;
            p->prev = q;
        }
        cout << "Added: \"" << title << "\" by " << artist << "\n";
    }

    void deleteSong(string title) {
        if (head == nullptr) {
            cout << "Playlist is empty. Nothing to delete.\n";
            return;
        }
        Node* p;
        Node* q = head;
    
        while (q != nullptr && !sameTitle(q->title, title)) {
            q = q->next;
        }
        if (q == nullptr) {
            cout << "Song \"" << title << "\" not found in the playlist.\n";
            return;
        }
        p = q;

        if (current == p) {
            if (p->next != nullptr) current = p->next;
            else current = p->prev;
        }
        if (p->prev == nullptr) {
            head = p->next;
            if (head != nullptr) head->prev = nullptr;
        } else if (p->next == nullptr) {
            p->prev->next = nullptr;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
        cout << "Deleted: \"" << p->title << "\" by " << p->artist << "\n";
        delete p;
    }

    void displayPlaylist() {
        if (head == nullptr) { cout << "Playlist is empty.\n"; return; }
        Node* q = head;
        int i = 1;
        cout << "\n--- Playlist (Forward) ---\n";
        while (q != nullptr) {
            cout << i++ << ". " << q->title << " - " << q->artist;
            if (q == current) cout << "   <-- current";
            cout << "\n";
            q = q->next;
        }
    }

    void displayReverse() {
        if (head == nullptr) { cout << "Playlist is empty.\n"; return; }
        Node* q = head;
        int count = 1;
        while (q->next != nullptr) {
            q = q->next;
            count++;
        }
        cout << "\n--- Playlist (Reverse) ---\n";
        while (q != nullptr) {
            cout << count-- << ". " << q->title << " - " << q->artist;
            if (q == current) cout << "   <-- current";
            cout << "\n";
            q = q->prev;
        }
    }

    void playCurrent() {
        if (current == nullptr) { cout << "No song to play. Playlist is empty.\n"; return; }
        cout << "Now Playing: " << current->title << " - " << current->artist << "\n";
    }

    void playNext() {
        if (current == nullptr) { cout << "Playlist is empty.\n"; return; }
        if (current->next == nullptr) {
            cout << "This is the last song. No next song available.\n";
            return;
        }
        current = current->next;
        playCurrent();
    }

    void playPrevious() {
        if (current == nullptr) { cout << "Playlist is empty.\n"; return; }
        if (current->prev == nullptr) {
            cout << "This is the first song. No previous song available.\n";
            return;
        }
        current = current->prev;
        playCurrent();
    }
    void playComplete() {
        if (head == nullptr) { cout << "Playlist is empty.\n"; return; }
        Node* q = current;
        cout << "\n--- Playing playlist from current song ---\n";
        while (q != nullptr) {
            current = q;
            playCurrent();
            q = q->next;
        }
        cout << "End of playlist.\n";
    }

    void repeatAll(int times) {
        if (head == nullptr) { cout << "Playlist is empty.\n"; return; }
        for (int r = 1; r <= times; r++) {
            cout << "\n=== Repeat round " << r << " of " << times << " ===\n";
            Node* q = head;
            while (q != nullptr) {
                current = q;
                playCurrent();
                q = q->next;
            }
        }
    }

    void showCurrent() {
        if (current == nullptr) { cout << "No current song. Playlist is empty.\n"; return; }
        cout << "Current Song: " << current->title << " - " << current->artist << "\n";
        cout << "  Previous : " << (current->prev ? current->prev->title : "NULL (first song)") << "\n";
        cout << "  Next     : " << (current->next ? current->next->title : "NULL (last song)") << "\n";
    }
};
int main() {
    MusicPlaylist list;
    int choice = 0;
    do {
        cout << "\n===== MUSIC PLAYLIST MANAGER =====\n"
             << "1. Add Song\n2. Delete Song\n3. Display Playlist\n"
             << "4. Display Playlist in Reverse\n5. Play Current Song\n"
             << "6. Play Next Song\n7. Play Previous Song\n"
             << "8. Play Complete Playlist\n9. Repeat All\n"
             << "10. Show Current Song\n11. Exit\nEnter choice: ";
        if (!(cin >> choice)) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string title, artist;
        int n;
        switch (choice) {
        case 1:
            cout << "Song Title : "; getline(cin, title);
            cout << "Artist Name: "; getline(cin, artist);
            list.addSong(title, artist);
            break;
        case 2:
            cout << "Title to delete: "; getline(cin, title);
            list.deleteSong(title);
            break;
        case 3:  list.displayPlaylist(); break;
        case 4:  list.displayReverse();  break;
        case 5:  list.playCurrent();     break;
        case 6:  list.playNext();        break;
        case 7:  list.playPrevious();    break;
        case 8:  list.playComplete();    break;
        case 9:
            cout << "Number of repetitions: ";
            if (cin >> n && n > 0) list.repeatAll(n);
            else { cout << "Invalid number.\n"; cin.clear(); }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        case 10: list.showCurrent();     break;
        case 11: cout << "Exiting Music Playlist Manager. Goodbye!\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 11);
    return 0;
}
/*PS C:\Users\ADMIN\OneDrive\Documents\musicplaylist manager> cd "c:\Users\ADMIN\OneDrive\Documents\musicplaylist manager\" ; if ($?) { g++ musicplaylist.cpp -o musicplaylist } ; if ($?) { .\musicplaylist }

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 1
Song Title : Vijeta
Artist Name: vikram
Added: "Vijeta" by vikram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 1
Song Title : Vande matram
Artist Name: Bankiram
Added: "Vande matram" by Bankiram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 1
Song Title : Rashtravadi
Artist Name: Adarsh shinde
Added: "Rashtravadi" by Adarsh shinde

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 3

--- Playlist (Forward) ---
1. Vijeta - vikram   <-- current
2. Vande matram - Bankiram
3. Rashtravadi - Adarsh shinde

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 3

--- Playlist (Forward) ---
1. Vijeta - vikram   <-- current
2. Vande matram - Bankiram
3. Rashtravadi - Adarsh shinde

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 4

--- Playlist (Reverse) ---
3. Rashtravadi - Adarsh shinde
2. Vande matram - Bankiram
1. Vijeta - vikram   <-- current

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 5
Now Playing: Vijeta - vikram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 6
Now Playing: Vande matram - Bankiram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 7
Now Playing: Vijeta - vikram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 8

--- Playing playlist from current song ---
Now Playing: Vijeta - vikram
Now Playing: Vande matram - Bankiram
Now Playing: Rashtravadi - Adarsh shinde
End of playlist.

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 9
Number of repetitions: 3

=== Repeat round 1 of 3 ===
Now Playing: Vijeta - vikram
Now Playing: Vande matram - Bankiram
Now Playing: Rashtravadi - Adarsh shinde

=== Repeat round 2 of 3 ===
Now Playing: Vijeta - vikram
Now Playing: Vande matram - Bankiram
Now Playing: Rashtravadi - Adarsh shinde

=== Repeat round 3 of 3 ===
Now Playing: Vijeta - vikram
Now Playing: Vande matram - Bankiram
Now Playing: Rashtravadi - Adarsh shinde

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 2
Title to delete: Vande matram
Deleted: "Vande matram" by Bankiram

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice: 3

--- Playlist (Forward) ---
1. Vijeta - vikram
2. Rashtravadi - Adarsh shinde   <-- current

===== MUSIC PLAYLIST MANAGER =====
1. Add Song
2. Delete Song
3. Display Playlist
4. Display Playlist in Reverse
5. Play Current Song
6. Play Next Song
7. Play Previous Song
8. Play Complete Playlist
9. Repeat All
10. Show Current Song
11. Exit
Enter choice:*/