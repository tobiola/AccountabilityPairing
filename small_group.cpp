#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

class Pair{
 public:
  int count;
  int member1;
  int member2;
  bool operator<(const Pair &rhs) const {
    return count < rhs.count;
  }
};

void swapPairs(Pair *x, Pair *y) {
  Pair temp = *x;
  *x = *y;
  *y = temp;
}

class SmallGroup {
 public:
  SmallGroup();
  int getMemberCount();
  void readMembers();
  void readPairs();
  void sortPairs();
  int getMemberId(string member);
  void printPairs();
  void choosePairs();

 private:
  string kMembersFilename;
  string kLogsFilename;
  vector <string> members;
  vector <Pair> pairs;
  vector <bool> paired;

};

SmallGroup::SmallGroup() {

  kMembersFilename = "members.txt";
  kLogsFilename = "logs.txt";

  readMembers();
  readPairs();

}

int SmallGroup::getMemberCount() {

  ifstream file(kMembersFilename);
  assert(file);
  cout << "Reading in File " << kMembersFilename << endl;

  int count = 0;
  while (!file.eof()) {
    string line;
    getline(file, line);
    if (line != "") {
      count++;
    }
  }
  cout << count << " members counted:" << endl;

  cout << endl;

  return count; 

}

void SmallGroup::readMembers() {

  ifstream file(kMembersFilename);
  assert(file);
  cout << "Reading in File " << kMembersFilename << endl;

  while (!file.eof()) {
    string line;
    getline(file, line);
    if (line != "") {
      members.push_back(line);
    }
  }
  cout << members.size() << " members scanned in:" << endl;

  for (int i = 0; i < members.size(); i++) {
    cout << members.at(i) << endl;
  }
  cout << endl;

}

int SmallGroup::getMemberId(string member) {

  for (int i = 0; i < members.size(); i++) {
    if (members.at(i) == member) {
      return i;
    }
  }

  cout << "ERROR: member " << member << " not found!" << endl;
  return -1;

}

void SmallGroup::sortPairs() {

  cout << "Sorting pairs" << endl;

  sort(pairs.begin(), pairs.end());

}

void SmallGroup::readPairs() {

  cout << "Making pairs" << endl;

  int count = 0;
  for (int i = 0; i < members.size(); i++) {
    for (int j = i + 1; j < members.size(); j++) {

      cout << i << " " << j << endl;
      Pair pair = { 0, i, j };

      pairs.push_back(pair);
    }
  }

  ifstream file(kLogsFilename);
  assert(file);
  cout << "Reading in File " << kLogsFilename << endl;

  while (!file.eof()) {
    string line;
    getline(file, line);

    if (line != "") {

      int split = line.find_first_of('-');
      if (split < 0) {
        continue;
      }

      int m1 = getMemberId(line.substr(0, split-1));
      int m2 = getMemberId(line.substr(split+2, line.length()));
      if (m1 > m2) {
        int temp = m1;
        m1 = m2;
        m2 = temp;
      }
      for (int i = 0; i < pairs.size(); i++) {
        if ((pairs.at(i).member1 == m1) && (pairs.at(i).member2 == m2)) {
          pairs.at(i).count++;
        }
      }
    }
  }
}

void SmallGroup::printPairs() {

  sortPairs();

  cout << "Printing Edges" << endl;

  for (int i = 0; i < pairs.size(); i++) {

    cout << pairs.at(i).count << " " << members[pairs.at(i).member1]
         << " - " << members[pairs.at(i).member2] << endl;

  }

}

void SmallGroup::choosePairs() {

  sortPairs();

  cout << "Printing Pairs" << endl;

  paired.clear();

  for (int i = 0; i < members.size(); i++) {
    paired.push_back(false);
  }

  for (int i = 0; i < pairs.size(); i++) {
    if ((paired.at(pairs.at(i).member1) == false) &&
        (paired.at(pairs.at(i).member2) == false)) {

      paired.at(pairs.at(i).member1) = true;
      paired.at(pairs.at(i).member2) = true;

      cout << members.at(pairs.at(i).member1) << " - "
           << members.at(pairs.at(i).member2) << endl;

    }

  }

}

int main() {

  SmallGroup sg;

  sg.printPairs();

  sg.choosePairs();

}
