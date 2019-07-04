#include <algorithm>
#include <forward_list>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int rows, columns;

const bool _debug_ = false;

struct node {
    int x, y;
    int height;
    bool visited;
};

ostream& operator<<(ostream& os, const node& node) {
    os << "x: " << node.x + 1 << ", y: " << node.y + 1
       << ", height: " << node.height << ", visited: " << node.visited;
    return os;
}

int** mountain = nullptr;
node** nodes = nullptr;

void heapify(vector<node*>& queue, int index) {
    while (true) {
        unsigned int left = 2 * index + 1;
        unsigned int right = 2 * index + 2;
        if (right < queue.size()) {
            if (queue[left]->height < queue[right]->height) {
                if (queue[left]->height < queue[index]->height) {
                    swap(queue[left], queue[index]);
                    index = left;
                } else
                    break;

            } else {
                if (queue[right]->height < queue[index]->height) {
                    swap(queue[right], queue[index]);
                    index = right;
                } else
                    break;
            }
        } else if (left < queue.size()) {
            if (queue[left]->height < queue[index]->height) {
                swap(queue[left], queue[index]);
                index = left;
            } else
                break;
        } else {
            break;
        }
    }
}

void rebuildHeap(vector<node*>& queue) {
    for (int i = queue.size() / 2 - 1; i >= 0; --i) {
        heapify(queue, i);
    }
}

node* removeMin(vector<node*>& queue) {
    node* result = queue[0];
    swap(queue[0], queue[queue.size() - 1]);

    queue.pop_back();
    heapify(queue, 0);

    return result;
}

void insert(vector<node*>& queue, node* n) {
    queue.push_back(n);
    int index = queue.size() - 1;
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (queue[parentIndex]->height > queue[index]->height) {
            swap(queue[parentIndex], queue[index]);
            index = parentIndex;
        } else
            break;
    }
}

int solve(int startx, int starty, int endx, int endy) {
    vector<node*> queue;
    forward_list<node*> visited;
    queue.push_back(&nodes[startx][starty]);

    nodes[startx][starty].visited = true;
    visited.push_front(&nodes[startx][starty]);
    while (queue[0]->x != endx || queue[0]->y != endy) {
        node* current = removeMin(queue);
        if (_debug_) cout << "visit: " << *current << "\n";
        if (current->x > 0) {
            node* n = &nodes[current->x - 1][current->y];
            if (n->visited) {
                if (current->height >= mountain[n->x][n->y] &&
                    current->height < n->height) {
                    n->height = current->height;
                    if (_debug_) cout << "updated: " << *n << "\n";
                }
            } else {
                n->visited = true;
                visited.push_front(n);
                n->height = max(n->height, current->height);

                queue.push_back(n);
                visited.push_front(n);
                if (_debug_) cout << "added: " << *n << "\n";
            }
        }
        if (current->x + 1 < rows) {
            node* n = &nodes[current->x + 1][current->y];
            if (n->visited) {
                if (current->height >= mountain[n->x][n->y] &&
                    current->height < n->height) {
                    n->height = current->height;
                    if (_debug_) cout << "updated: " << *n << "\n";
                }
            } else {
                n->visited = true;
                visited.push_front(n);
                n->height = max(n->height, current->height);

                queue.push_back(n);
                visited.push_front(n);
                if (_debug_) cout << "added: " << *n << "\n";
            }
        }
        if (current->y > 0) {
            node* n = &nodes[current->x][current->y - 1];
            if (n->visited) {
                if (current->height >= mountain[n->x][n->y] &&
                    current->height < n->height) {
                    n->height = current->height;
                    if (_debug_) cout << "updated: " << *n << "\n";
                }
            } else {
                n->visited = true;
                visited.push_front(n);
                n->height = max(n->height, current->height);

                queue.push_back(n);
                visited.push_front(n);
                if (_debug_) cout << "added: " << *n << "\n";
            }
        }
        if (current->y + 1 < columns) {
            node* n = &nodes[current->x][current->y + 1];
            if (n->visited) {
                if (current->height >= mountain[n->x][n->y] &&
                    current->height < n->height) {
                    n->height = current->height;
                    if (_debug_) cout << "updated: " << *n << "\n";
                }
            } else {
                n->visited = true;
                visited.push_front(n);
                n->height = max(n->height, current->height);

                queue.push_back(n);
                visited.push_front(n);
                if (_debug_) cout << "added: " << *n << "\n";
            }
        }
        rebuildHeap(queue);
    }

    int result = queue[0]->height;

    for (const node* n : visited) {
        nodes[n->x][n->y].height = mountain[n->x][n->y];
        nodes[n->x][n->y].visited = false;
    }

    return result;
}

int main() {
    int q;

    cin >> rows >> columns >> q;

    mountain = new int*[rows];
    nodes = new node*[rows];
    for (int i = 0; i < rows; ++i) {
        mountain[i] = new int[columns];
        nodes[i] = new node[columns];
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            int f;
            cin >> f;
            mountain[r][c] = f;
            nodes[r][c].x = r;
            nodes[r][c].y = c;
            nodes[r][c].height = f;
            nodes[r][c].visited = false;
        }
    }

    while (q--) {
        int startx, starty, endx, endy;
        cin >> startx >> starty >> endx >> endy;
        int result = solve(startx - 1, starty - 1, endx - 1, endy - 1);
        cout << "result: " << result << "\n";
    }

    for (int i = 0; i < rows; ++i) {
        delete[] mountain[i];
        delete[] nodes[i];
    }
    delete[] mountain;
    delete[] nodes;

    return 0;
}
