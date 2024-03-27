#include <stdio.h>

int main() {
    FILE *file_ptr;
    char ch;

    // Mở tập tin để đọc
    file_ptr = fopen("F:\\EMBEDDED\\MCP\\Programming\\app2_A000.s19","r");

    // Kiểm tra xem tập tin có tồn tại không
    if (file_ptr == NULL) {
        printf("Không thể mở tập tin.\n");
        return 1;
    }

    // Đọc và in ra từng ký tự trong tập tin
    while ((ch = fgetc(file_ptr)) != EOF) {
        printf("%x ", ch);
    }

    // Đóng tập tin sau khi hoàn tất
    fclose(file_ptr);

    return 0;
}
