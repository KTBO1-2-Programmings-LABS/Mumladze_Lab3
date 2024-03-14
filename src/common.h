struct CarNode {
    char p_name[21];
    char p_birthday[11];
    char p_phone[15];
    char c_sign[11];
    char c_passport[11];
    char c_police_code[8];
};

struct CarsList {
    CarNode** list = nullptr;
    int len = 0; 
};

enum NodeField {
    NAME = 0,
    BIRTHDAY = 1,
    PHONE = 2,
    SIGN = 3,
    PASSPORT = 4,
    POLICE_NUM = 5,
};

enum UserTask {
    CLOSE_PROGRAM = 0,
    ADD_NODE = 1,
    FIND_NODE = 2,
    PRINT_LIST = 3,
    SORT_LIST = 4,
};

void clean_input();
int get_user_task();

void close_program(CarsList* all_cars);
void add_node(CarsList* all_cars);
void find_node(CarsList* all_cars);
void print_list(CarsList* all_cars);
void sort_list(CarsList* all_cars);