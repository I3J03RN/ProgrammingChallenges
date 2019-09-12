#include <forward_list>
#include <iostream>
#include <utility>
#include <vector>

typedef unsigned int uint;

using namespace std;

enum direction { left, right, top, bottom };

ostream& operator<<(ostream& out, const pair<int, int>& p) {
    out << "<" << p.first << ", " << p.second << ">";
    return out;
}

ostream& operator<<(ostream& out, const direction& dir) {
    switch (dir) {
        case direction::left:
            out << "left";
            break;
        case direction::right:
            out << "right";
            break;
        case direction::top:
            out << "top";
            break;
        case direction::bottom:
            out << "bottom";
            break;
    }
    return out;
}

struct piece {
    piece(uint pieceHeight)
        : data(vector<string>(pieceHeight)),
          position(-1, -1),
          left(-10),
          right(-10),
          top(-10),
          bottom(-10) {}

    void setEdges(int left, int right, int top, int bottom) {
        this->left = left;
        this->right = right;
        this->top = top;
        this->bottom = bottom;

        leftV[5 + left].push_front(this);
        rightV[5 + right].push_front(this);
        topV[5 + top].push_front(this);
        bottomV[5 + bottom].push_front(this);
    }

    bool placed() { return position.first != -1 && position.second != -1; }

    static forward_list<piece*>& getEdgeList(direction direction, int value) {
        switch (direction) {
            case direction::left:
                return leftV[value + 5];
            case direction::right:
                return rightV[value + 5];
            case direction::top:
                return topV[value + 5];
            case direction::bottom:
                return bottomV[value + 5];
        }
    }

    static void clear() {
        for (auto& fl : leftV) {
            fl.clear();
        }
        for (auto& fl : rightV) {
            fl.clear();
        }
        for (auto& fl : topV) {
            fl.clear();
        }
        for (auto& fl : bottomV) {
            fl.clear();
        }
    }

    vector<string> data;

    pair<int, int> position;

    int left, right, top, bottom;

   private:
    static vector<forward_list<piece*>> leftV;
    static vector<forward_list<piece*>> rightV;
    static vector<forward_list<piece*>> topV;
    static vector<forward_list<piece*>> bottomV;
};

ostream& operator<<(ostream& out, const piece& p) {
    out << "pos: " << p.position << ", " << p.top << ", " << p.left << ", "
        << p.bottom << ", " << p.right << "\n";
    for (const string& s : p.data) out << s << "\n";
    return out;
}

vector<forward_list<piece*>> piece::leftV(11);
vector<forward_list<piece*>> piece::rightV(11);
vector<forward_list<piece*>> piece::topV(11);
vector<forward_list<piece*>> piece::bottomV(11);

struct puzzle {
    puzzle(size_t size) : data(size, vector<piece*>(size)) {}

    int getFitValue(pair<int, int> position, direction dir) {
        if (position.first < 0 || position.first >= data.size() ||
            position.second < 0 || position.second >= data.size())
            cerr << "getFItvalue parameter error\n";

        switch (dir) {
            case direction::left:
                if (position.second == 0) {
                    return 0;
                } else {
                    return -data[position.first][position.second - 1]->right;
                }
            case direction::right:
                if (position.second == data.size() - 1) {
                    return 0;
                } else {
                    return -data[position.first][position.second + 1]->left;
                }
            case direction::top:
                if (position.first == 0) {
                    return 0;
                } else {
                    return -data[position.first - 1][position.second]->bottom;
                }
            case direction::bottom:
                if (position.first == data.size() - 1) {
                    return 0;
                } else {
                    return -data[position.first + 1][position.second]->top;
                }
        }
    }

    void set(pair<int, int> position, piece* p) {
        data[position.first][position.second] = p;
    }

    piece* get(pair<int, int> position) {
        return data[position.first][position.second];
    }

    bool fits(pair<int, int> position, piece* p) {
        if (position.first < 0 || position.first >= data.size() ||
            position.second < 0 || position.second >= data.size() ||
            p == nullptr)
            cerr << "fits parameter error\n";

        if (position.first == 0) {
            if (p->top != 0) return false;
        } else {
            if (data[position.first - 1][position.second] != nullptr)
                if (data[position.first - 1][position.second]->bottom !=
                    -p->top)
                    return false;
        }
        if (position.first == data.size() - 1) {
            if (p->bottom != 0) return false;
        } else {
            if (data[position.first + 1][position.second] != nullptr)
                if (data[position.first + 1][position.second]->top !=
                    -p->bottom)
                    return false;
        }
        if (position.second == 0) {
            if (p->left != 0) return false;
        } else {
            if (data[position.first][position.second - 1] != nullptr)
                if (data[position.first][position.second - 1]->right !=
                    -p->left)
                    return false;
        }
        if (position.second == data.size() - 1) {
            if (p->right != 0) return false;
        } else {
            if (data[position.first][position.second + 1] != nullptr)
                if (data[position.first][position.second + 1]->left !=
                    -p->right)
                    return false;
        }

        return true;
    }

    bool free(pair<int, int> position) {
        if (position.first < 0 || position.first >= data.size() ||
            position.second < 0 || position.second >= data.size())
            return false;

        return get(position) == nullptr;
    }

    vector<vector<piece*>> data;
};

bool solve(pair<int, int> position, direction from, puzzle& puzzle) {
    //    cout << "solve: " << position << ", " << from
    //      << ", fit value: " << puzzle.getFitValue(position, from) << endl;
    switch (from) {
        case direction::left:
            for (piece* p :
                 piece::getEdgeList(from, puzzle.getFitValue(position, from))) {
                //            cout << "candite:\n" << *p << "\n";
                if (!p->placed() && puzzle.fits(position, p)) {
                    p->position = position;
                    //    cout << "placed:\n" << *p << "\n";
                    puzzle.set(position, p);
                    pair<int, int> nextPos = {position.first,
                                              position.second + 1};
                    if (puzzle.free(nextPos)) {
                        if (solve(nextPos, direction::left, puzzle)) {
                            return true;
                        }
                    } else {
                        nextPos = {position.first + 1, position.second};
                        if (puzzle.free(nextPos)) {
                            if (solve(nextPos, direction::top, puzzle)) {
                                return true;
                            }
                        } else
                            return true;
                    }

                    p->position = {-1, -1};
                    puzzle.set(position, nullptr);
                }
            }
            break;
        case direction::right:
            for (piece* p :
                 piece::getEdgeList(from, puzzle.getFitValue(position, from))) {
                if (!p->placed() && puzzle.fits(position, p)) {
                    p->position = position;
                    // cout << "placed:\n" << *p << "\n";
                    puzzle.set(position, p);
                    pair<int, int> nextPos = {position.first,
                                              position.second - 1};
                    if (puzzle.free(nextPos)) {
                        if (solve(nextPos, direction::right, puzzle)) {
                            return true;
                        }
                    } else {
                        nextPos = {position.first - 1, position.second};
                        if (puzzle.free(nextPos)) {
                            if (solve(nextPos, direction::bottom, puzzle)) {
                                return true;
                            }
                        } else
                            return true;
                    }

                    p->position = {-1, -1};
                    puzzle.set(position, nullptr);
                }
            }
            break;
        case direction::top:
            for (piece* p :
                 piece::getEdgeList(from, puzzle.getFitValue(position, from))) {
                // cout << "candite:\n" << *p << "\n";
                if (!p->placed() && puzzle.fits(position, p)) {
                    p->position = position;
                    // cout << "placed:\n" << *p << "\n";
                    puzzle.set(position, p);
                    pair<int, int> nextPos = {position.first + 1,
                                              position.second};
                    if (puzzle.free(nextPos)) {
                        if (solve(nextPos, direction::top, puzzle)) {
                            return true;
                        }
                    } else {
                        nextPos = {position.first, position.second - 1};
                        if (solve(nextPos, direction::right, puzzle)) {
                            return true;
                        }
                    }

                    p->position = {-1, -1};
                    puzzle.set(position, nullptr);
                }
            }
            break;
        case direction::bottom:
            for (piece* p :
                 piece::getEdgeList(from, puzzle.getFitValue(position, from))) {
                if (!p->placed() && puzzle.fits(position, p)) {
                    p->position = position;
                    //                    cout << "placed:\n" << *p << "\n";
                    puzzle.set(position, p);
                    pair<int, int> nextPos = {position.first - 1,
                                              position.second};
                    if (puzzle.free(nextPos)) {
                        if (solve(nextPos, direction::bottom, puzzle)) {
                            return true;
                        }
                    } else {
                        nextPos = {position.first, position.second + 1};
                        if (puzzle.free(nextPos)) {
                            if (solve(nextPos, direction::left, puzzle)) {
                                return true;
                            }
                        } else
                            return true;
                    }

                    p->position = {-1, -1};
                    puzzle.set(position, nullptr);
                }
            }
            break;
    }
    return false;
}

int main() {
    uint n;
    cin >> n;

    while (n--) {
        uint puzzleSize;
        uint pieceHeight;
        uint pieceWidth;

        cin >> puzzleSize >> pieceHeight >> pieceWidth;

        forward_list<piece> pieces;

        puzzle puzzle(puzzleSize);

        for (uint i = 0; i < puzzleSize * puzzleSize; ++i) {
            pieces.emplace_front(pieceHeight);
            while (cin.peek() < 32) cin.get();
            for (uint line = 0; line < pieceHeight; ++line) {
                getline(cin, pieces.front().data[line]);
            }

            int top, left, bottom, right;

            cin >> top >> left >> bottom >> right;
            pieces.front().setEdges(left, right, top, bottom);
            // cout << pieces.front() << "\n";
        }

        if (!solve({0, 0}, direction::left, puzzle)) cout << "Häää\n";

        for (auto& pieceLine : puzzle.data) {
            // for (piece* p : pieceLine) cout << p << "\n";
            for (uint line = 0; line < pieceHeight; ++line) {
                for (piece* p : pieceLine) {
                    cout << p->data[line];
                }
                cout << '\n';
            }
        }
        if (n != 0) cout << '\n';
        piece::clear();
    }

    return 0;
}
