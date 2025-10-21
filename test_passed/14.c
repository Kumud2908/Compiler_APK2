int main() {
    int choice = 2;
    int result = 0;
    
    switch (choice) {
        case 1: {
            int temp = 100;
            result = temp;
            break;
        }
        case 2: {
            int temp = 200;
            result = temp;
            break;
        }
        default: {
            int temp = 300;
            result = temp;
        }
    }
    return 0;
}