#include <iostream>
#include <climits>
using namespace std;

class OBST {
    int n;
    string a[10];    // Keys
    int p[11], q[11]; // Probabilities (Note: p[1..n], q[0..n])
    int w[11][11], c[11][11], r[11][11];

public:
    void get_data();
    void build_OBST();
    void build_tree(int, int);
};

void OBST::get_data() {
    cout << "Enter the number of nodes (max 9): ";
    cin >> n;

    if (n > 9) {
        cout << "Limit exceeded. Maximum allowed is 9.\n";
        exit(1);
    }

    cout << "Enter the keys:\n";
    for (int i = 1; i <= n; i++) {
        cout << "a[" << i << "]: ";
        cin >> a[i];
    }

    cout << "Enter the successful search probabilities:\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "Enter the unsuccessful search probabilities:\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }
}

void OBST::build_OBST() {
    int i, j, k, m, min;

    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;

        if (i < n) {
            w[i][i + 1] = q[i] + p[i + 1] + q[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }
    }

    for (m = 2; m <= n; m++) {
        for (i = 0; i <= n - m; i++) {
            j = i + m;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            min = INT_MAX;
            for (k = i + 1; k <= j; k++) {
                int temp = c[i][k - 1] + c[k][j];
                if (temp < min) {
                    min = temp;
                    r[i][j] = k;
                }
            }
            c[i][j] = min + w[i][j];
        }
    }

    cout << "\nThe Optimal Binary Search Tree for the given data is built.\n";
    cout << "Root of OBST: " << a[r[0][n]] << endl;
    cout << "Cost of OBST: " << c[0][n] << endl;
    cout << "\nNODE\tLEFT CHILD\tRIGHT CHILD\n";
    build_tree(0, n);
}

void OBST::build_tree(int i, int j) {
    int root = r[i][j];
    if (root == 0) return;

    cout << a[root] << "\t";

    if (r[i][root - 1] != 0)
        cout << a[r[i][root - 1]] << "\t\t";
    else
        cout << "-\t\t";

    if (r[root][j] != 0)
        cout << a[r[root][j]] << "\n";
    else
        cout << "-\n";

    build_tree(i, root - 1);
    build_tree(root, j);
}

int main() {
    OBST obj;
    obj.get_data();
    obj.build_OBST();
    return 0;
}
