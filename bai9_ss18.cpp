#include <stdio.h>
#include <string.h>
#include <stdlib.h>
	
 typedef struct {
	    int id;
	    char ten[50];
	    float gia;
	} MonAn;
	
	MonAn menu[100] = {
	    {1, "pho bo", 30000},
	    {2, "pho ga", 30000},
	    {3, "bun cha", 20000},
	    {4, "bun bo", 30000},
	    {5, "chao long", 25000}
	};
	int kichThuocMenu = 5;
	
	void inMenu();
	void themMonCuoi(MonAn mon_moi);
	void suaMonCuoi(MonAn mon_sua);
	void xoaMon(int vi_tri);
	void sapXepMenu(char thu_tu);
	void timKiemTen(char *ten, char loai_tim_kiem);
 main() {
	    int lua_chon;
	    MonAn mon_temp;
	    char thu_tu, loai_tim_kiem;
	    char ten_tim[50];
	
	    while (1) {
	        printf("\nMENU\n");
	        printf("1. In menu\n");
	        printf("2. Them mon an vao cuoi menu\n");
	        printf("3. Sua mon an cuoi cung trong menu\n");
	        printf("4. Xoa mon an o vi tri\n");
	        printf("5. Sap xep menu\n");
	        printf("6. Tim kiem theo ten\n");
	        printf("7. Thoat\n");
	        printf("Nhap lua chon cua ban: ");
	        scanf("%d", &lua_chon);
	
	        switch (lua_chon) {
	            case 1:
	                inMenu();
	                break;
	            case 2:
	                printf("Nhap id, ten, va gia: ");
	                scanf("%d", &mon_temp.id);
	                getchar();
	                fgets(mon_temp.ten, sizeof(mon_temp.ten), stdin);
	                mon_temp.ten[strcspn(mon_temp.ten, "\n")] = '\0';
	                scanf("%f", &mon_temp.gia);
	                themMonCuoi(mon_temp);
	                break;
	            case 3:
	                printf("Nhap id moi, ten moi, va gia moi: ");
	                scanf("%d", &mon_temp.id);
	                getchar();
	                fgets(mon_temp.ten, sizeof(mon_temp.ten), stdin);
	                mon_temp.ten[strcspn(mon_temp.ten, "\n")] = '\0';
	                scanf("%f", &mon_temp.gia);
	                suaMonCuoi(mon_temp);
	                break;
	            case 4:
	                printf("Nhap vi tri can xoa: ");
	                scanf("%d", &lua_chon);
	                xoaMon(lua_chon - 1); 
	                break;
	            case 5:
	                printf("a. Sap xep gia tang dan\n");
	                printf("b. Sap xep gia giam dan\n");
	                printf("Nhap lua chon: ");
	                scanf(" %c", &thu_tu);
	                sapXepMenu(thu_tu);
	                break;
	            case 6:
	                printf("Nhap ten mon an can tim: ");
	                getchar();
	                fgets(ten_tim, sizeof(ten_tim), stdin);
	                ten_tim[strcspn(ten_tim, "\n")] = '\0';
	                printf("a. Tim kiem tuyen tinh\n");
	                printf("b. Tim kiem nhi phan\n");
	                printf("Nhap lua chon: ");
	                scanf(" %c", &loai_tim_kiem);
	                timKiemTen(ten_tim, loai_tim_kiem);
	                break;
	            case 7:
	                return 0;
	            default:
	                printf("Lua chon khong hop le!\n");
	        }
	    }
	}
	
	void inMenu() {
	    for (int i = 0; i < kichThuocMenu; i++) {
	        printf("%d. id: %d, ten: %s, gia: %.2f\n", i + 1, menu[i].id, menu[i].ten, menu[i].gia);
	    }
	}
	
	void themMonCuoi(MonAn mon_moi) {
	    if (kichThuocMenu >= 100) {
	        printf("Menu da day. Khong the them mon an moi.\n");
	        return;
	    }
	    menu[kichThuocMenu] = mon_moi;
	    kichThuocMenu++;
	}
	
	void suaMonCuoi(MonAn mon_sua) {
	    if (kichThuocMenu == 0) {
	        printf("Menu rong. Khong co mon an de sua.\n");
	        return;
	    }
	    menu[kichThuocMenu - 1] = mon_sua;
	}
	
	void xoaMon(int vi_tri) {
	    if (vi_tri < 0 || vi_tri >= kichThuocMenu) {
	        printf("Vi tri khong hop le.\n");
	        return;
	    }
	
	    for (int i = vi_tri; i < kichThuocMenu - 1; i++) {
	        menu[i] = menu[i + 1];
	    }
	    kichThuocMenu--;
	}
	
	int so_sanh_gia_tang(const void *a, const void *b) {
	    float giaA = ((MonAn *)a)->gia;
	    float giaB = ((MonAn *)b)->gia;
	    return (giaA > giaB) - (giaA < giaB);
	}
	
	int so_sanh_gia_giam(const void *a, const void *b) {
	    float giaA = ((MonAn *)a)->gia;
	    float giaB = ((MonAn *)b)->gia;
	    return (giaB > giaA) - (giaB < giaA);
	}
	
	void sapXepMenu(char thu_tu) {
	    if (thu_tu == 'a') {
	        qsort(menu, kichThuocMenu, sizeof(MonAn), so_sanh_gia_tang);
	    } else if (thu_tu == 'b') {
	        qsort(menu, kichThuocMenu, sizeof(MonAn), so_sanh_gia_giam);
	    }
	}
	
	void timKiemTen(char *ten, char loai_tim_kiem) {
	    if (loai_tim_kiem == 'a') {
	        for (int i = 0; i < kichThuocMenu; i++) {
	            if (strcmp(menu[i].ten, ten) == 0) {
	                printf("Mon an tim thay o vi tri %d: id: %d, ten: %s, gia: %.2f\n", i + 1, menu[i].id, menu[i].ten, menu[i].gia);
	                return;
	            }
	        }
	        printf("Khong tim thay mon an.\n");
	    } else if (loai_tim_kiem == 'b') {
	        
	        qsort(menu, kichThuocMenu, sizeof(MonAn), (int (*)(const void *, const void *))strcmp);
	        int low = 0, high = kichThuocMenu - 1, mid;
	        while (low <= high) {
	            mid = (low + high) / 2;
	            int cmp = strcmp(menu[mid].ten, ten);
	            if (cmp == 0) {
	                printf("Mon an tim thay o vi tri %d: id: %d, ten: %s, gia: %.2f\n", mid + 1, menu[mid].id, menu[mid].ten, menu[mid].gia);
	                return;
	            } else if (cmp < 0) {
	                low = mid + 1;
	            } else {
	                high = mid - 1;
	            }
	        }
	        printf("Khong tim thay mon an.\n");
	    }
	}