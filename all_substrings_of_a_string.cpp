#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
void print_all_substrings(char *s){
    for(int i = 0; i < strlen(s); i++){
        for(int j = 1; j <= strlen(s) - i; j++) {
            printf("%.*s\n", j, s+i);
        }
    }
}
*/

/*
char** get_all_substrings(char *s){
    int len = strlen(s);
    
    char *all = malloc(len * (len * (len+1))/2);
    memset(all, 0, sizeof(all));
    int allIndex = 0;
    
    printf("Starting...\n");
    for(int i = 0; i < len; i++){
        for(int j = 1; j <= len - i; j++) {
            int substr_len = len - i;
            char *sub = all[allIndex++];
            printf("Substring = %s", sub);
            snprintf(sub, len, "%.*s\n", j, s+i);
        }
    }
}
*/

vector<string> get_all_substrings(string s){
    int len = s.length();
    int total_substr = (len*(len+1))/2;
    
    vector<string> all;
    int allIndex = 0;
    
    for(int i = 0; i <len; i++){
        for(int j = 1; j <= len - i; j++) {
            all.push_back(s.substr(i, j));
        }
    }
    
    for(int i = 0; i < total_substr; i++)
        cout << all[i] << endl;
    return all;
}

int main()
{
    string s = "abcd";
    vector<string> all = get_all_substrings(s);
    int len = s.length();
    
    for(int i =0; i < (len * (len+1)/2); i++)
        cout << all[i] << endl;
    
    return 0;
}

