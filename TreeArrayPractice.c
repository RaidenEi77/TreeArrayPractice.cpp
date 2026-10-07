#include <stdio.h>
#include <string.h>

#define MAX 100
#define EMPTY 0

typedef struct {
    int id;                 // ma nut
    char content[120];      // cau hoi hoac ket luan
    int left;               // chi so nut con trai
    int right;              // chi so nut con phai
    int isLeaf;             // 1: nut la, 0: nut quyet dinh
} Node;

Node Tree[MAX];
int root = 1;
int n = 0;                  // so nut hien co (n = 0: cay chua khoi tao)

 //Ham tien ich 

// Xoa het du lieu: cac nut chua dung co left = right = 0
void initTree() {
    int i;
    for (i = 0; i < MAX; i++) {
        Tree[i].id = 0;
        Tree[i].content[0] = '\0';
        Tree[i].left = EMPTY;
        Tree[i].right = EMPTY;
        Tree[i].isLeaf = 0;
    }
    root = 1;
    n = 0;
}

// Chi so hop le khi nam trong khoang 1..n
int isValidIndex(int i) {
    return (i >= 1 && i <= n);
}

// Kiem tra cay da co du lieu chua, neu chua thi bao loi
int checkTree() {
    if (n == 0) {
        printf("Loi: Cay chua duoc khoi tao! Hay chon chuc nang 1 hoac 2 truoc.\n");
        return 0;
    }
    return 1;
}

Khoi tao / nhap du lieu 

void loadSampleTree() {
    initTree();
    n = 7;
    root = 1;

    Tree[1] = (Node){1, "DTB < 2.0?", 2, 3, 0};
    Tree[2] = (Node){2, "No >= 12 tin chi?", 4, 5, 0};
    Tree[3] = (Node){3, "DTB >= 3.2?", 6, 7, 0};
    Tree[4] = (Node){4, "Canh bao hoc vu muc 2", 0, 0, 1};
    Tree[5] = (Node){5, "Canh bao hoc vu muc 1", 0, 0, 1};
    Tree[6] = (Node){6, "De xuat khen thuong", 0, 0, 1};
    Tree[7] = (Node){7, "Theo doi binh thuong", 0, 0, 1};

    printf("Da nap cay mau gom %d nut (root = %d).\n", n, root);
}

void inputTree() {
    int i, count;

    printf("Nhap so nut (7 den %d): ", MAX - 1);
    if (scanf("%d", &count) != 1) {
        while (getchar() != '\n');
        printf("Loi: Ban phai nhap mot so nguyen!\n");
        return;
    }
    if (count < 7 || count > MAX - 1) {
        printf("Loi: So nut phai tu 7 den %d!\n", MAX - 1);
        return;
    }

    initTree();
    n = count;

    for (i = 1; i <= n; i++) {
        printf("\n--- Nhap nut o vi tri mang %d ---\n", i);

        printf("id: ");
        scanf("%d", &Tree[i].id);

        printf("Noi dung (cau hoi hoac ket luan): ");
        scanf(" %119[^\n]", Tree[i].content);

        printf("left (0 = khong co): ");
        scanf("%d", &Tree[i].left);

        printf("right (0 = khong co): ");
        scanf("%d", &Tree[i].right);

        printf("isLeaf (1 = nut la, 0 = nut quyet dinh): ");
        scanf("%d", &Tree[i].isLeaf);

        // Kiem tra du lieu: left/right khong duoc tro ra ngoai mang
        if (Tree[i].left < 0 || Tree[i].left > n ||
            Tree[i].right < 0 || Tree[i].right > n) {
            printf("Loi: left/right phai nam trong khoang 0..%d. Hay chay lai chuc nang nhap!\n", n);
            initTree();
            return;
        }
        if (Tree[i].isLeaf != 0 && Tree[i].isLeaf != 1) {
            printf("Loi: isLeaf chi duoc la 0 hoac 1. Hay chay lai chuc nang nhap!\n");
            initTree();
            return;
        }
    }
    printf("\nNhap cay thanh cong (%d nut).\n", n);
}

 //Hien thi bang mang 

void showTable() {
    int i;
    if (!checkTree()) return;

    printf("\n===== BANG BIEU DIEN CAY BANG MANG (root = %d, n = %d) =====\n", root, n);
    printf("%-6s %-5s %-25s %-6s %-6s %-7s\n",
           "Index", "id", "Noi dung", "left", "right", "isLeaf");
    printf("---------------------------------------------------------------\n");
    for (i = 1; i <= n; i++) {
        printf("%-6d %-5d %-25s %-6d %-6d %-7d\n",
               i, Tree[i].id, Tree[i].content,
               Tree[i].left, Tree[i].right, Tree[i].isLeaf);
    }
}

// Duyet cay 

void preorder(int i) {
    if (i == EMPTY) return;
    printf("%d - %s\n", Tree[i].id, Tree[i].content);
    preorder(Tree[i].left);
    preorder(Tree[i].right);
}

void inorder(int i) {
    if (i == EMPTY) return;
    inorder(Tree[i].left);
    printf("%d - %s\n", Tree[i].id, Tree[i].content);
    inorder(Tree[i].right);
}

void postorder(int i) {
    if (i == EMPTY) return;
    postorder(Tree[i].left);
    postorder(Tree[i].right);
    printf("%d - %s\n", Tree[i].id, Tree[i].content);
}

void traverseAll() {
    if (!checkTree()) return;

    printf("\n--- Duyet TIEN TU (goc - trai - phai) ---\n");
    preorder(root);
    printf("\n--- Duyet TRUNG TU (trai - goc - phai) ---\n");
    inorder(root);
    printf("\n--- Duyet HAU TU (trai - phai - goc) ---\n");
    postorder(root);
}

// Tim kiem va duong di 

// Tim nut theo id, tra ve chi so trong mang (0 neu khong thay)
int findById(int targetId) {
    int i;
    for (i = 1; i <= n; i++) {
        if (Tree[i].id == targetId) return i;
    }
    return EMPTY;
}

// Tim duong di tu current den nut co id = targetId
int findPath(int current, int targetId, int path[], int *len) {
    if (current == EMPTY) return 0;

    path[(*len)++] = current;

    if (Tree[current].id == targetId) return 1;

    if (findPath(Tree[current].left, targetId, path, len)) return 1;
    if (findPath(Tree[current].right, targetId, path, len)) return 1;

    (*len)--;       // quay lui khi nhanh hien tai khong chua nut can tim
    return 0;
}

void searchAndPrintPath() {
    int choice, value, idx, i;
    int path[MAX];
    int len = 0;

    if (!checkTree()) return;

    printf("Tim theo: 1. Chi so mang   2. id cua nut\nChon: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');
        printf("Loi: Lua chon khong hop le!\n");
        return;
    }
    if (choice != 1 && choice != 2) {
        printf("Loi: Chi duoc chon 1 hoac 2!\n");
        return;
    }

    printf("Nhap gia tri can tim: ");
    if (scanf("%d", &value) != 1) {
        while (getchar() != '\n');
        printf("Loi: Ban phai nhap mot so nguyen!\n");
        return;
    }

    if (choice == 1) {
        if (!isValidIndex(value)) {
            printf("Loi: Chi so phai nam trong khoang 1..%d!\n", n);
            return;
        }
        idx = value;
    } else {
        idx = findById(value);
        if (idx == EMPTY) {
            printf("Khong tim thay nut co id = %d.\n", value);
            return;
        }
    }

    printf("\nDa tim thay nut:\n");
    printf("  Index = %d, id = %d, noi dung = %s\n", idx, Tree[idx].id, Tree[idx].content);
    printf("  left = %d, right = %d, isLeaf = %d\n", Tree[idx].left, Tree[idx].right, Tree[idx].isLeaf);

    // In duong di tu goc den nut vua tim
    if (findPath(root, Tree[idx].id, path, &len)) {
        printf("Duong di tu goc: ");
        for (i = 0; i < len; i++) {
            printf("%d", path[i]);
            if (i < len - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("Nut nay khong nam tren cay tu goc (kiem tra lai lien ket left/right).\n");
    }
}

// Thong ke 

// Chieu cao tinh theo so muc (cay mau co chieu cao = 3)
int height(int i) {
    if (i == EMPTY) return 0;
    int hLeft = height(Tree[i].left);
    int hRight = height(Tree[i].right);
    return 1 + (hLeft > hRight ? hLeft : hRight);
}

int countLeaves(int i) {
    if (i == EMPTY) return 0;
    if (Tree[i].left == EMPTY && Tree[i].right == EMPTY) return 1;
    return countLeaves(Tree[i].left) + countLeaves(Tree[i].right);
}

void showStatistics() {
    if (!checkTree()) return;

    printf("\n===== THONG KE CAY =====\n");
    printf("Tong so nut     : %d\n", n);
    printf("Chieu cao (muc) : %d\n", height(root));
    printf("So nut la       : %d\n", countLeaves(root));
}

// Mo phong tu van hoc vu 

void runDecisionTree() {
    int current;
    char answer;

    if (!checkTree()) return;

    current = root;
    printf("\n===== MO PHONG TU VAN HOC VU =====\n");
    printf("(y = Co -> nhanh trai, n = Khong -> nhanh phai)\n\n");

    while (current != EMPTY && Tree[current].isLeaf == 0) {
        printf("%s (y/n): ", Tree[current].content);
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y')
            current = Tree[current].left;
        else if (answer == 'n' || answer == 'N')
            current = Tree[current].right;
        else
            printf("Chi nhap y hoac n!\n");     // giu nguyen nut, hoi lai
    }

    if (current != EMPTY)
        printf("\nKet luan: %s\n", Tree[current].content);
    else
        printf("\nDu lieu cay bi loi.\n");
}

// Menu 

void processChoice(int choice) {
    switch (choice) {
        case 1: loadSampleTree();        break;
        case 2: inputTree();             break;
        case 3: showTable();             break;
        case 4: traverseAll();           break;
        case 5: searchAndPrintPath();    break;
        case 6: showStatistics();        break;
        case 7: runDecisionTree();       break;
        case 0: printf("Tam biet!\n");   break;
        default: printf("Lua chon khong hop le, vui long chon lai!\n");
    }
}

int main() {
    int choice;
    initTree();

    do {
        printf("\n===== TREE ARRAY PRACTICE =====\n");
        printf("1. Khoi tao cay mau\n");
        printf("2. Nhap cay thu cong\n");
        printf("3. Hien thi bang mang\n");
        printf("4. Duyet tien tu / trung tu / hau tu\n");
        printf("5. Tim nut va in duong di\n");
        printf("6. Tinh chieu cao va dem nut la\n");
        printf("7. Mo phong tu van hoc vu\n");
        printf("0. Thoat\nChon: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');      // xoa du lieu sai trong bo dem
            choice = -1;
        }
        processChoice(choice);
    } while (choice != 0);

    return 0;
}
