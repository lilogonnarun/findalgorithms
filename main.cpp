/*顺序查找、二分查找、分块索引查找、二叉排序查找、二叉树的插入删除*/

#include <iostream>

using namespace std;
typedef struct BiTNode {
    int data;
    int bf;
    struct BiTNode *lchild, *rchild;

    BiTNode() : data(0), lchild(nullptr), rchild(nullptr) {}
} BiTNode, *BiTree;

/*静态查找：数组存取数据。0位置放哨兵,1~n存数据*/
int sequential_search(int *array, int len, int key) {
    int i;
    array[0] = key;
    i = len;
    while (array[i] != key) {
        i--;
    }
    return i;
}

int binary_search(int *array, int len, int key) {
    int low, high, mid;
    low = 1;
    high = len;
    while (low <= high) {
        mid = (high + low) / 2;
        if (key < array[mid]) {
            high = mid - 1;
        } else if (key > array[mid]) {
            low = mid + 1;
        } else return mid;
    }
    return 0;
}

void Index_search(int *index, int *index_loc, int index_length, int *elem, int len, int key) {
    int compare_time = 0;
    for (int i = 0; i < index_length; i++) {
        compare_time++;
        if (key <= index[i] || i == index_length - 1)    //先和索引表最大关键字比较
        {
            int start_loc = index_loc[i];
            int end_loc = i + 1 >= index_length ? len : index_loc[i + 1];
            for (int j = start_loc; j < end_loc; j++)      //再从索引表最大关键字对应的下标开始比较
            {
                compare_time++;
                if (elem[j] == key) {
                    cout << j + 1 << '-' << compare_time << endl;
                    return;
                }
            }
            cout << "error" << endl;
            return;
        }
    }
}

bool BST_search(BiTree T, int key, BiTree f, BiTree *p) {
    if (!T) {
        *p = f;
        return false;
    } else if (key == T->data) {
        *p = T;
        return true;
    } else if (key < T->data) {
        return BST_search(T->lchild, key, T, p);
    }
}

bool BST_insert(BiTree *T, int key) {
    BiTree p = nullptr, s;
    if (!BST_search(*T, key, nullptr, &p)) {
        s = new BiTNode;
        s->data = key;
        s->lchild = s->rchild = nullptr;
        if (!p) {
            *T = s;//empty tree
        } else if (key < p->data) {
            p->lchild = s;
        } else if (key > p->data) {
            p->rchild = s;
        }
        return true;
    } else return false;
}

bool BiTNode_delete(BiTree *T) {
    BiTree q, s;
    if ((*T)->rchild == nullptr) {
        q = *T;
        *T = (*T)->rchild;
        delete (q);
    } else if ((*T)->lchild == nullptr) {
        q = *T;
        *T = (*T)->lchild;
        delete (q);
    } else {
        q = *T;
        s = (*T)->lchild;

        while (s->rchild) {
            q = s;
            s = s->rchild;
        }
        (*T)->data = s->data;
        if (q != *T) {
            q->rchild = s->lchild;
        } else {
            q->lchild = s->rchild;
        }
        delete (s);
    }
    return true;
}

bool BST_delete(BiTree *T, int key) {
    if (!*T) {
        return false;
    } else {
        if (key == (*T)->data) {
            return BiTNode_delete(T);
        } else if (key < (*T)->data) {
            //the search function returns status
            return BST_delete(&(*T)->lchild, key);
        } else if (key > (*T)->data) {
            return BST_delete(&(*T)->rchild, key);
        }
    }
}

void midTraverse(BiTree *T) {
    if (!*T) {
        return;
    } else {
        midTraverse(&(*T)->lchild);
        cout << (*T)->data << ' ';
        midTraverse(&(*T)->rchild);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, e;
        cin >> n;
        BiTree *T = new BiTree;
        while (n--) {
            cin >> e;
            bool b = false;
        }
        midTraverse(T);
        cout << endl;
        cin >> n;
        while (n--) {
            cin >> e;
            bool b = false;
            midTraverse(T);
            cout << endl;
        }
    }

}
