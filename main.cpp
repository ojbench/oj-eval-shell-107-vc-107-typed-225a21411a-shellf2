#include <bits/stdc++.h>
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

    NODE* move(int i) {
        if (len == 0 || i < 0 || i >= len) return nullptr;
        NODE* p = head;
        for (int k = 0; k < i; ++k) p = p->next;
        return p;
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
            // insert before head
            NODE* tail = move(len - 1);
            node->next = head;
            tail->next = node;
            head = node;
            ++len;
            return;
        }
        // insert before index i, i in [1, len]
        NODE* prev = move(i - 1);
        node->next = prev->next;
        prev->next = node;
        ++len;
    }

    void remove(int i) {
        if (len == 0) return;
        if (len == 1) {
            delete head;
            head = nullptr;
            len = 0;
            return;
        }
        if (i <= 0) {
            NODE* tail = move(len - 1);
            NODE* del = head;
            head = head->next;
            tail->next = head;
            delete del;
            --len;
            return;
        }
        NODE* prev = move(i - 1);
        NODE* del = prev->next;
        prev->next = del->next;
        delete del;
        --len;
    }

    void remove_insert(int i) {
        if (len <= 1 || i >= len || i < 0) return; // nothing to do or invalid
        if (i == len - 1) return; // already at tail
        if (i == 0) {
            NODE* tail = move(len - 1);
            NODE* x = head;
            head = head->next;
            tail->next = x;
            x->next = head;
            return;
        }
        NODE* prev = move(i - 1);
        NODE* x = prev->next;
        prev->next = x->next;
        NODE* tail = move(len - 1);
        tail->next = x;
        x->next = head;
    }

    void get_length() {
        cout << len << '\n';
    }

    void query(int i) {
        if (i < 0 || i >= len || len == 0) {
            cout << -1 << '\n';
            return;
        }
        NODE* p = move(i);
        cout << p->val << '\n';
    }

    void get_max() {
        if (len == 0) {
            cout << -1 << '\n';
            return;
        }
        int mx = head->val;
        for (NODE* p = head->next; p != head; p = p->next) mx = max(mx, p->val);
        cout << mx << '\n';
    }

    void clear() {
        if (len == 0 || head == nullptr) return;
        NODE* p = head->next;
        while (p != head) {
            NODE* tmp = p;
            p = p->next;
            delete tmp;
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
    if (!(cin >> n)) return 0;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}
