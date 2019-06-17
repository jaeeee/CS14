#include "Playlist.h"

PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string id, string songname, string artist, int length) {
    uniqueID = id;
    songName = songname;
    artistName = artist;
    songLength = length;
    nextNodePtr = 0;
}

void PlaylistNode::InsertAfter(PlaylistNode* ptr) {
    this->SetNext(ptr->GetNext());
    ptr->SetNext(this);
}

void PlaylistNode::SetNext(PlaylistNode* ptr) {
    nextNodePtr = ptr;
}

PlaylistNode* PlaylistNode::GetNext() {
    return nextNodePtr;
}

string PlaylistNode::GetID() {
    return uniqueID;
}

string PlaylistNode::GetSongName() {
    return songName;
}

string PlaylistNode::GetArtistName() {
    return artistName;
}

int PlaylistNode::GetSongLength() {
    return songLength;
}

void PlaylistNode::PrintPlaylistNode() {
    cout << "Unique ID: " << uniqueID << endl;
    cout << "Song Name: " << songName << endl;
    cout << "Artist Name: " << artistName << endl;
    cout << "Song Length (in seconds): " << songLength << endl;
}

Playlist::Playlist() {
    head = tail = 0;
}

void Playlist::AddSong(string id, string songname, string artistname, int length) {
    PlaylistNode* blah = new PlaylistNode(id, songname, artistname, length);
    if (head == 0) {
        head = tail = blah;
    } else {
        blah->InsertAfter(tail);
        tail = blah;
    }
}

bool Playlist::RemoveSong(string id) {
    if (head == NULL) {
        cout << "Playlist is empty" << endl;
        return false;
    }
    PlaylistNode* curr = head;
    PlaylistNode* prev = NULL;
    while (curr != NULL) {
        if (curr->GetID() == id) {
            break;
        }
        prev = curr;
        curr = curr->GetNext();
    }
    if (curr == NULL) {
        cout << "\"" << curr->GetSongName() << "\" is not found" << endl;
    } else {
        if (prev != NULL)
            tail = prev;
        cout << "\"" << curr->GetSongName() << "\" removed" << endl;
        delete curr;
        return true;
    }
}

bool Playlist::ChangePosition(int oldPos, int newPos)
{
    if (head == NULL)
    {
        cout << "Playlist is empty" << endl;
        return false;
    }
    PlaylistNode* prev = NULL;
    PlaylistNode* curr = head;
    int pos;
    if (head == NULL || head == tail)
        return false;
    
    for (pos = 1; curr != NULL && pos < oldPos; pos++)
    {
        prev = curr;
        curr = curr->GetNext();
    }
    if (curr != NULL)
    {
        string currentSong = curr->GetSongName();
        if (prev == NULL)
            head = curr->GetNext();
        else
        {
            prev->SetNext(curr->GetNext());
        }
        
        if (curr == tail)
            tail = prev;
        
        PlaylistNode* curr1 = curr;
        prev = NULL;
        curr = head;
        for (pos = 1; curr != NULL && pos < newPos; pos++)
        {
            prev = curr;
            curr = curr->GetNext();
        }
        if (prev == NULL)
        {
            curr1->SetNext(head);
            head = curr1;
        }
        else
            curr1->InsertAfter(prev);
        
        if (curr == NULL)
            tail = curr1;
        cout << "\"" << currentSong << "\" moved to position " << newPos << endl;
        return true;
        }
    else
    {
        cout << "Song's current position is invalid" << endl;
        return false;
    }
}

void Playlist::SongsByArtist(string artist) {
    if (head == NULL) {
        cout << "Playlist is empty" << endl;
    } else {
        PlaylistNode* curr = head;
        int i = 1;
        while (curr != NULL) {
            if (curr->GetArtistName() == artist) {
                cout << i << "." << endl;
                curr->PrintPlaylistNode();
                cout << endl;
            }
            curr = curr->GetNext();
            i++;
        }
    }
    cout << endl;
}

int Playlist::TotalTime() {
    int tot = 0;
    PlaylistNode* curr = head;
    
    while (curr != NULL) {
        tot += curr->GetSongLength();
        curr = curr->GetNext();
    }
    return tot;
}

void Playlist::PrintList() {
    if (head == NULL) { //does it matter whether or not we use 0 or NULL?
        cout << "Playlist is empty";
    } else {
        PlaylistNode* curr = head;
        int i = 1;
        while (curr != NULL) {
            cout << i++ << "." << endl;
            curr->PrintPlaylistNode();
            cout << endl;
            curr = curr->GetNext();
        }
    }
    cout << endl;
}
