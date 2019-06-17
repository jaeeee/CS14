#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

void PrintMenu(string playlist) {
    cout << playlist << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl;
    cout << endl;
    cout << "Choose an option:" << endl;
}

int main () {
    string playlistName;
    PlaylistNode* head = NULL;
    PlaylistNode* tail = NULL;
    char option;
    
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistName);
    cout << endl;
    while (true) {
        PrintMenu(playlistName);
        cin >> option;
        if (option == 'a') {
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            string uid;
            cin >> uid;
            cin.ignore();
            cout << "Enter song's name:" << endl;
            string songname;
            getline(cin, songname);
            cout << "Enter artist's name:" << endl;
            string songartist;
            getline(cin, songartist);
            cout << "Enter song's length (in seconds):" << endl;
            int songlength;
            cin >> songlength;
            PlaylistNode* temp = new PlaylistNode(uid, songname, songartist, songlength);
            if (head == NULL) {
                head = temp;
                tail = temp;
            }
            else {
                tail->SetNext(temp);
                tail = temp;
            }
            cout << endl;
        }
        else if (option == 'd') {
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            string identry = "";
            cin >> identry;
            for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                if (i->GetNext()->GetID() == identry) {
                    PlaylistNode* temp = i->GetNext();
                    string tempsong;
                    tempsong = i->GetNext()->GetSongName();
                    i->SetNext(i->GetNext()->GetNext());
                    delete temp;
                    cout << "\"" << tempsong << "\"" << " removed." << endl;
                    break;
                }
                if (identry == i->GetID()) {
                    if (i == head) {
                        PlaylistNode* temp = head->GetNext();
                        delete head;
                        head = temp;
                        break;
                    }
                }
            }
            cout << endl;
        }
        else if (option == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            PlaylistNode* clone = NULL;
            int num;
            int songPos = 0;
            cin >> songPos; 
            cout << "Enter new position for song:" << endl;
            int newPos = 0;
            cin >> newPos;
            //Loop that counts amount of song
            int lastSong;
            for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                ++lastSong;
            }
            //Moving the headnode
            if (songPos == 1) {
                clone = head;
                head = head->GetNext();
            }
            //moving the tailnode;
            else if (songPos == lastSong) {
                clone = tail;
                //for loop that moves tail node;
                for (PlaylistNode* i = head; i->GetNext()->GetNext() != NULL; i = i->GetNext()) {
                    tail = i;
                }
                tail = tail->GetNext();
                tail->SetNext(NULL);
            }
            else {
                num = 1;
                for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                    if (num == songPos - 1) {
                        clone = i->GetNext();
                        i->SetNext(i->GetNext()->GetNext());
                    }
                    ++num;
                }
            }
            num = 1;
            if (newPos == 1) {
                PlaylistNode* temp = head;
                head = clone;
                clone->SetNext(temp);
            }
            else {
                for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                    if (num == newPos - 1) {
                        PlaylistNode* temp = i->GetNext();
                        i->SetNext(clone);
                        clone->SetNext(temp);
                    }
                    ++num;
                }
            }
            cout << "\"" << clone->GetSongName() << "\"" << " moved to position " << newPos << endl << endl;
        }
        
        else if (option == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl;
            cout << endl;
            string artistentry;
            cin.ignore();
            getline(cin, artistentry);
            int displayval = 1;
            for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                if (i->GetArtistName() == artistentry) {
                    cout << displayval << "." << endl;
                    i->PrintPlaylistNode();
                    cout << endl;
                }
                ++displayval;
            }
        }
        else if (option == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            if (head == NULL) {
                cout << "Total time: 0 seconds" << endl;
            }
            else {
                int totalplay = 0;
                for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                    totalplay += i->GetSongLength();
                }
                cout << "Total time: " << totalplay << " seconds" << endl;
            }
            cout << endl;
        }
        else if (option == 'o') {
            cout << playlistName << " - OUTPUT FULL PLAYLIST" << endl;
            if (head == NULL) {
                cout << "Playlist is empty" << endl;
            }
            else {
                int displaynum = 1;
                for (PlaylistNode* i = head; i != NULL; i = i->GetNext()) {
                    cout << displaynum << "." << endl;
                    i->PrintPlaylistNode();
                    if (i->GetNext() != NULL) {
                        cout << endl;
                    }
                    ++displaynum;
                }
            }
            cout << endl;
        }
        else if (option == 'q') {
            break;
        }
    }
    return 0;
}