#include <stdio.h>
#include <math.h>

double RoundTo(double num){
    return round(num * 100) / 100;
}

//task_1
//r2 = 2 * m1 / (m1 + m2)
float lift_a_car(const int stick_length, const int human_weight, const int car_weight){
    return RoundTo((float) stick_length * human_weight / (human_weight + car_weight));
}


//task_2
float unit_price(const float pack_price, const int rolls_count, const int pieces_count){
    float roll_price = pack_price / rolls_count;
    float piece_price = roll_price / pieces_count;
    float hundred_price = piece_price * 100;
    return RoundTo(hundred_price);
}

//task_3
int bank_notes(const int price){
    int curr_price = price;
    int banknote_count = 0;
    if(price %2 != 0) return -1;
    while(curr_price >= 200){
        banknote_count += 1;
        curr_price -= 200;
    }
    while(curr_price >= 100){
        banknote_count += 1;
        curr_price -= 100;
    }
    while(curr_price >= 50){
        banknote_count += 1;
        curr_price -= 50;
    }
    while(curr_price >= 20){
        banknote_count += 1;
        curr_price -= 20;
    }
    while(curr_price >= 10){
        banknote_count += 1;
        curr_price -= 10;
    }
    return banknote_count;
}

//Function for task_4
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
//

//task_4
int euler(const int n) {
    int res = 0;
    for (int k = 1; k < n; ++k) {
        if (gcd(k, n) == 1) {
            ++res;
        }
    }
    return res;
}

//Function for task_5, task_7
void sort_an_array(int array[], int array_size){
    int temp;
    for (int i = 0; i < array_size - 1; ++i){
        for (int j = 0; j < array_size - 1 - i; ++j){
            if (array[j] > array[j+1]){
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }
}
//


//task_5
int find_missing_number(const int n, const int arr[]){
    int find_num = 0;  
    int arr_of_num[n]; 
    for(int i = 0; i < n; i++){
        arr_of_num[i] = arr[i]; 
    }
    sort_an_array(arr_of_num, n);
    for(int i = 0; i < n; i++){
        if(arr_of_num[i+1] - arr_of_num[i] > 1){
            find_num = arr_of_num[i] + 1;
            break;
        }
    }
    return find_num;
}

//Functions for task_6
unsigned long long combination(int line, int i) {
    if (i == 0 || i == line) return 1;
    unsigned long long result = 1;
    for (int k = 1; k <= i; k++) {
        result = result * (line - k + 1) / k;
    }
    return result;
}
//


//task_6
unsigned long sum_squared(const int line) {
    unsigned long long summ = 0;
    for (int i = 0; i <= line; i++) {
        unsigned long long temp = combination(line, i);
        summ += temp * temp;
    }
    return summ;
}

//task_7
//task_7.1 MIN
int array_min(const int input_array[], const int array_size){
    if(input_array == NULL) return -1;
    int arr_of_num[array_size]; 
    for(int i = 0; i < array_size; i++){
        arr_of_num[i] = input_array[i]; 
    }
    sort_an_array(arr_of_num, array_size);
    return arr_of_num[0];
}
//task_7.2 MAX
int array_max(const int input_array[], const int array_size){
    if(input_array == NULL) return -1;
    int arr_of_num[array_size]; 
    for(int i = 0; i < array_size; i++){
        arr_of_num[i] = input_array[i]; 
    }
    sort_an_array(arr_of_num, array_size);
    return arr_of_num[array_size - 1];
}

//task_8
int factorize_count(const int n) {
    if (n == 1) return 0;
    int factors_count = 0;
    int curr_number = n;
    if (curr_number % 2 == 0) {
        factors_count++;
        for(;;){
            if (curr_number % 2 == 0) {
                curr_number /= 2;
            }
            else break;
        }
    }
    for (int i = 3; i <= sqrt(curr_number); i += 2) {
        if (curr_number % i == 0) {
            factors_count++;
            for(;;){
                if (curr_number % i == 0) {
                        curr_number /= i;
                }
                else break;
            }
        }
    }
    if (curr_number > 2) {
        factors_count++;
        return factors_count;
    }
    return factors_count;
}

//task_9
void podium(const int n, int arr[]) {

    int first = 1 + ((n + 2) / 3);
    int second = (first - 1);
    int third = (n - (first + second));
    
    arr[0] = second;
    arr[1] = first;
    arr[2] = third;
}


int main(){    
    // task_1
    printf("%.4f\n", lift_a_car(2, 80, 1400));

    // task_2
    printf("%.4f\n", unit_price(4.79, 16, 150));
    
    // task_3
    printf("%d\n", bank_notes(480));
    
    // task_4
    printf("%d\n", euler(283));
    
    // task_5
    int input_array[] = {3,0,1,2,5};
    printf("%d\n", find_missing_number(5, input_array));

    // task_6
    printf("%lu\n", sum_squared(21));

    // task_7
    int input_array_2[] = {1,2,3,4,5};
    printf("%d\n", array_min(input_array_2, 5));
    printf("%d\n", array_max(input_array_2, 5));
    printf("%d\n", array_min(NULL, 5));
    printf("%d\n", array_max(NULL, 5));

    // task_8
    printf("%d\n", factorize_count(456));

    // task_9
    int heights[3];
    int material = 9;
    podium(material, heights);
    for(int i = 0; i < 3; i++){
        printf("%d ", heights[i]);
    }
}

