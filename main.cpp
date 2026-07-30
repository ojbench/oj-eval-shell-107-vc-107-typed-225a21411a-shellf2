#include <algorithm>
#include <iostream>

using namespace std;

namespace LIST {
    struct NODE {
        int val;
        NODE* next;
        NODE(int v = 0, NODE* n = nullptr) : val(v), next(n) {}
    };

    NODE* head = nullptr;
    int len = 0;

    void init() {
        head = nullptr;
        len = 0;
    }

    NODE* at(int i) {
        if (i < 0 || i >= len || head == nullptr) {
            return nullptr;
        }
        NODE* cur = head;
        for (int step = 0; step < i; ++step) {
            cur = cur->next;
        }
        return cur;
    }

    NODE* tail() {
        if (len == 0 || head == nullptr) {
            return nullptr;
        }
        NODE* cur = head;
        for (int step = 1; step < len; ++step) {
            cur = cur->next;
        }
        return cur;
    }

    void insert(int i, int x) {
        NODE* node = new NODE(x);
        if (len == 0) {
            node->next = node;
            head = node;
            ++len;
            return;
        }

        if (i <= 0) {
            NODE* last = tail();
            if (last == nullptr) return;
            node->next = head;
            last->next = node;
            head = node;
            ++len;
            return;
        }

        NODE* prev = at(i - 1);
        if (prev == nullptr) return;
        node->next = prev->next;
        prev->next = node;
        ++len;
    }

    void remove(int i) {
        if (len == 0) {
            return;
        }

        if (len == 1) {
            delete head;
            head = nullptr;
            len = 0;
            return;
        }

        if (i <= 0) {
            NODE* last = tail();
            if (last == nullptr) return;
            NODE* doomed = head;
            head = head->next;
            last->next = head;
            delete doomed;
            --len;
            return;
        }

        NODE* prev = at(i - 1);
        if (prev == nullptr || prev->next == nullptr) return;
        NODE* doomed = prev->next;
        prev->next = doomed->next;
        delete doomed;
        --len;
    }

    void remove_insert(int i) {
        if (len <= 1 || i < 0 || i >= len - 1) {
            return;
        }

        NODE* last = tail();
        if (last == nullptr) return;
        if (i == 0) {
            NODE* moved = head;
            head = head->next;
            last->next = moved;
            moved->next = head;
            return;
        }

        NODE* prev = at(i - 1);
        if (prev == nullptr || prev->next == nullptr) return;
        NODE* moved = prev->next;
        prev->next = moved->next;
        last->next = moved;
        moved->next = head;
    }

    void get_length() {
        cout << len << '\n';
    }

    void query(int i) {
        NODE* cur = at(i);
        if (cur == nullptr) {
            cout << -1 << '\n';
            return;
        }
        cout << cur->val << '\n';
    }

    void get_max() {
        if (len == 0 || head == nullptr) {
            cout << -1 << '\n';
            return;
        }

        int mx = head->val;
        NODE* cur = head->next;
        while (cur != head) {
            mx = max(mx, cur->val);
            cur = cur->next;
        }
        cout << mx << '\n';
    }

    void clear() {
        if (head == nullptr) {
            len = 0;
            return;
        }

        NODE* cur = head->next;
        while (cur != head) {
            NODE* next = cur->next;
            delete cur;
            cur = next;
        }
        delete head;
        head = nullptr;
        len = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        return 0;
    }

    LIST::init();
    for (int idx = 0; idx < n; ++idx) {
        int op;
        cin >> op;
        if (op == 0) {
            LIST::get_length();
        } else if (op == 1) {
            int p, x;
            cin >> p >> x;
            LIST::insert(p, x);
        } else if (op == 2) {
            int p;
            cin >> p;
            LIST::query(p);
        } else if (op == 3) {
            int p;
            cin >> p;
            LIST::remove(p);
        } else if (op == 4) {
            int p;
            cin >> p;
            LIST::remove_insert(p);
        } else if (op == 5) {
            LIST::get_max();
        }
    }

    LIST::clear();
    return 0;
}
