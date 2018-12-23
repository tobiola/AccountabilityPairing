#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

using namespace std;

typedef struct {
  int count;
  int id1;
  int id2;
} Edge;

void readMembers(string *members) {

  const string filename = "members.txt";
  ifstream file(filename);
  assert(file);
  cout << "Reading in File " << filename << endl;

  int count = 0;
  while (!file.eof()) {
    string line;
    getline(file, line);
    if (line != "") {
      members[count++] = line;
    }
  }
  cout << count << " members scanned in:" << endl;

  for (int i = 0; i < count; i++) {
    cout << members[i] << endl;
  }
  cout << endl;

}

int getMemberId(string member, string *members) {

  for (int i = 0; i < 14; i++) {
    if (members[i] == member) {
      return i;
    }
  }

  cout << "ERROR: member " << member << " not found!" << endl;
  return -1;

}

void swapEdge(Edge *x, Edge *y) {
  Edge temp = *x;
  *x = *y;
  *y = temp;
}

void sortGraph(Edge *graph, int edges) {

  cout << "Sorting graph" << endl;

  for (int i = 0; i < edges - 1; i++) {
    for (int j = 0; j < edges - 1; j++) {
      if (graph[j].count >= graph[j+1].count) {
        swapEdge(&graph[j], &graph[j+1]);
      }
    }
  }

}

void makeGraph(Edge *graph, string *members, int edges, int m_count) {

  cout << "Making graph" << endl;

  int count = 0;
  for (int i = 0; i < m_count; i++) {
    for (int j = i + 1; j < m_count; j++) {

      cout << i << " " << j << endl;
      graph[count].count = 0;
      graph[count].id1 = i;
      graph[count].id2 = j;
      count++;
    }
  }

  const string filename = "logs.txt";
  ifstream file(filename);
  assert(file);
  cout << "Reading in File " << filename << endl;

  while (!file.eof()) {
    string line;
    getline(file, line);

    if (line != "") {

      int split = line.find_first_of('-');
      if (split < 0) {
        continue;
      }

      int m1 = getMemberId(line.substr(0, split-1), members);
      int m2 = getMemberId(line.substr(split+2, line.length()), members);
      if (m1 > m2) {
        int temp = m1;
        m1 = m2;
        m2 = temp;
      }
      for (int i = 0; i < edges; i++) {
        if ((graph[i].id1 == m1) && (graph[i].id2 == m2)) {
          graph[i].count++;
        }
      }
    }
  }
}

void printEdges(Edge *graph, int edges, string *members) {

  cout << "Printing Edges" << endl;

  for (int i = 0; i < edges; i++) {

    cout << graph[i].count << " " << members[graph[i].id1] << " - " << members[graph[i].id2] << endl;

  }

}

void printPairs(Edge *graph, bool *paired, string *members, int edges) {

  cout << "Printing Pairs" << endl;

  for (int i = 0; i < edges; i++) {
    if ((paired[graph[i].id1] == false) &&
        (paired[graph[i].id2] == false)) {

      paired[graph[i].id1] = true;
      paired[graph[i].id2] = true;

      cout << members[graph[i].id1] << " - "
           << members[graph[i].id2] << endl;

    }

  }

}

int main() {

  const int MEMBER_COUNT = 14;
  const int EDGE_COUNT = (MEMBER_COUNT * (MEMBER_COUNT - 1))/2;
  string members[MEMBER_COUNT];
  Edge graph[EDGE_COUNT];
  bool paired[MEMBER_COUNT] = { false };

  readMembers(members);

  makeGraph(graph, members, EDGE_COUNT, MEMBER_COUNT);

  sortGraph(graph, EDGE_COUNT);

  printEdges(graph, EDGE_COUNT, members);

  printPairs(graph, paired, members, EDGE_COUNT);

}
