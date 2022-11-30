#include <string>
using namespace std;

class CharacterCount {
private:
    string s;
    int array[];
public:
    int operator[](int index);
    string getS();
    int* getArr();
    void setS(string new_s);
    void setArr(int* new_arr);
};
