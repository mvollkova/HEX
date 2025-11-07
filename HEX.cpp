#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int BoardSize(vector<vector<char>>& board)
{
    return board.size() / 2 + 1;
}

int PawnNumber(vector<vector<char>>& board, int& r, int& b)
{
    b = 0;
    r = 0;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'b')
            {
                b++;
            }
            if (board[i][j] == 'r')
            {
                r++;
            }
        }
    }
    return r + b;
}

bool isBoardCorrect(int r, int b)
{
    return r - 1 == b || r == b;
}

bool isCanStep(char** board, bool** visited, int n, int start_i, int start_j, int coord_i, int coord_j, char pawn)
{
    if (start_i + coord_i >= n || start_i + coord_i < 0 ||
        start_j + coord_j >= n || start_j + coord_j < 0)
    {
        return false;
    }
    if (board[start_i + coord_i][start_j + coord_j] == ' ')
    {
        return false;
    }
    if (board[start_i + coord_i][start_j + coord_j] != pawn)
    {
        return false;
    }

    if (visited[start_i + coord_i][start_j + coord_j] == true)
    {
        return false;
    }
    return true;
}

bool isRedDfs(char** board, bool** visited, int n, int start_i, int start_j)
{
    int coordI[]{ -1, -1, 0, 1, 1, 0 };
    int coordJ[]{ 0, 1, 1, 0, -1, -1 };

    visited[start_i][start_j] = true;

    if (n - 1 == start_i)
    {
        return true;
    }
    for (int i = 0; i < 6; i++)
    {
        if (isCanStep(board, visited, n, start_i, start_j, coordI[i], coordJ[i], 'r'))
        {
            bool res = isRedDfs(board, visited, n, start_i + coordI[i], start_j + coordJ[i]);
            if (res == true)
            {
                return true;
            }
        }
    }
    return false;
}
void clear(bool** visited, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
}
bool isExistsRedPath(char** board, bool** visited, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (board[0][i] == 'r' && isRedDfs(board, visited, n, 0, i) == true)
        {
            return true;
        }
        clear(visited, n);
    }
    return false;
}

char** convertToMatrix(vector<vector<char>> board)
{
    int n = board.size() / 2 + 1;
    char** matrix = new char* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new char[n];
    }

    for (int i = 0; i < n; i++)
    {
        int t = board.size() / 2;
        for (int j = i; j < n; j++)
        {
            matrix[i][j] = board[t--][i];
        }
    }
    for (int i = 1; i < n; i++)
    {
        int t = 0;
        int i_ = board.size() / 2 + i;
        for (int j = 0; j < i; j++)
        {
            matrix[i][j] = board[i_--][t++];
        }
    }

    return matrix;
}

bool** createVisited(int n)
{
    bool** visited = new bool* [n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = new bool[n];
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
    return visited;
}

bool isBlueDfs(char** board, bool** visited, int n, int start_i, int start_j)
{
    int coordI[]{ -1, -1, 0, 1, 1, 0 };
    int coordJ[]{ 0, 1, 1, 0, -1, -1 };

    visited[start_i][start_j] = true;
    if (start_j == n - 1)
    {
        return true;
    }
    for (int i = 0; i < 6; i++)
    {
        if (isCanStep(board, visited, n, start_i, start_j, coordI[i], coordJ[i], 'b'))
        {
            bool res = isBlueDfs(board, visited, n, start_i + coordI[i], start_j + coordJ[i]);
            if (res == true)
            {
                return true;
            }
        }
    }
    return false;
}
bool isExistsBluePath(char** board, bool** visited, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (board[i][0] == 'b' && isBlueDfs(board, visited, n, i, 0) == true)
        {
            return true;
        }
        clear(visited, n);
    }
    return false;
}
bool isBoardPossible(char** board, bool** visited, int n, char p)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] == 'r' && p == 'r')
            {
                char pawn = board[i][j];
                board[i][j] = ' ';
                bool** visitedsecond = createVisited(n);
                bool isStillWinning = isExistsRedPath(board, visitedsecond, n);
                for (int i = 0; i < n; i++)
                {
                    delete[] visitedsecond[i];
                }
                delete[] visitedsecond;
                board[i][j] = pawn;
                if (!isStillWinning)
                {
                    return false;
                }
            }
            if (board[i][j] == 'b' && p == 'b')
            {
                char pawn = board[i][j];
                board[i][j] = ' ';
                bool** newVisited = createVisited(n);
                bool isStillWinning = isExistsBluePath(board, newVisited, n);
                for (int i = 0; i < n; i++)
                {
                    delete[] newVisited[i];
                }
                delete[] newVisited;
                board[i][j] = pawn;
                if (!isStillWinning)
                {
                    return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    string command;
    vector<vector<char>> board;
    vector<char> row;
    while (getline(cin, command))
    {
        if (command.find("---") != -1)
        {
            row.clear();
            board.clear();
            while (true)
            {
                getline(cin, command);
                for (int i = 0; i < command.size(); i++)
                {
                    if (command[i] == '<')
                    {
                        row.push_back(command[i + 2]);
                    }
                }
                if (!row.empty())
                {
                    board.push_back(row);
                    row.clear();
                }
                if (command.find("---") != -1 && !board.empty())
                {
                    break;
                }
            }
            continue;
        }

        int b = 0, r = 0;
        int n = BoardSize(board);
        char** matrix = convertToMatrix(board);
        bool** visited = createVisited(n);
        if (command == "BOARD_SIZE")
        {
            cout << n << endl
                << endl;
        }
        if (command == "PAWNS_NUMBER")
        {
            cout << PawnNumber(board, r, b) << endl
                << endl;
        }
        if (command == "IS_BOARD_CORRECT")
        {
            PawnNumber(board, r, b);
            cout << (isBoardCorrect(r, b) ? "YES" : "NO") << endl
                << endl;
        }
        if (command == "IS_GAME_OVER")
        {
            PawnNumber(board, r, b);
            if (!isBoardCorrect(r, b))
            {
                cout << "NO" << endl
                    << endl;
            }
            else
            {
                bool isRed = isExistsRedPath(matrix, visited, n);
                clear(visited, n);
                bool isBlue = isExistsBluePath(matrix, visited, n);
                if (isRed)
                {
                    cout << "YES RED" << endl
                        << endl;
                }
                else if (isBlue)
                {
                    cout << "YES BLUE" << endl
                        << endl;
                }
                else
                {
                    cout << "NO" << endl
                        << endl;
                }
            }
        }
        if (command == "IS_BOARD_POSSIBLE")
        {
            PawnNumber(board, r, b);
            bool isRed = isExistsRedPath(matrix, visited, n);
            clear(visited, n);
            bool isBlue = isExistsBluePath(matrix, visited, n);
            if (!isBoardCorrect(r, b))
            {
                cout << "NO" << endl
                    << endl;
            }
            else if (!isBlue && !isRed)
            {
                cout << "YES" << endl
                    << endl;
            }
            else if (isRed)
            {
                if (r - 1 != b)
                {
                    cout << "NO" << endl
                        << endl;
                }
                else if (isBoardPossible(matrix, visited, n, 'r'))
                {
                    cout << "NO" << endl
                        << endl;
                }
                else
                {
                    cout << "YES" << endl
                        << endl;
                }
            }
            else if (isBlue)
            {
                if (r != b)
                {
                    cout << "NO" << endl
                        << endl;
                }
                else if (isBoardPossible(matrix, visited, n, 'b'))
                {
                    cout << "NO" << endl
                        << endl;
                }
                else
                {
                    cout << "YES" << endl
                        << endl;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            delete[] matrix[i];
            delete[] visited[i];
        }
        delete[] matrix;
        delete[] visited;
    }
    return 0;
}