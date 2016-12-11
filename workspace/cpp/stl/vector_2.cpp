#include <iostream>
#include <vector>
using namespace std;

class Item
{
    int mI;
    public :
    static int mConstructor;
    static int mCopyConstructor;
    static int mDestructor;

    static int t;

    Item(int i)
    {
        this->mI = i;
        cout << "t = " << t++ << "constructor called for  " << this->mI << endl;
    }

    ~Item()
    {
        cout << "t = " << t++ << "destructor called for " <<  this->mI << endl;
    }

    Item(const Item& aI)
    {
        this->mI = aI.mI;
        cout << "t = " << t++ << "copy constructor called " << this->mI << endl;
    }
};

int Item::mConstructor = 0;
int Item::mCopyConstructor = 0;
int Item::mDestructor = 0;
int Item::t = 0;
class Factory
{
    public:
    static void create_vector_objects()
    {
        vector<Item> vecOfItems;
        //vecOfItems.push_back(Item());
    }

    static vector<Item> get_vector_objects()
    {
        vector<Item> vecOfItems;
        //vecOfItems.reserve(10);
        for(int i = 0; i < 2; i++)
        {
           cout << "--START--" << endl;
           cout << "-- i = " << i << endl;
           vecOfItems.push_back(Item(i));
           cout << "-- i = " << i << endl;
           cout << "--END--" << endl;
        }
        cout << "----" << endl;

        return vecOfItems;
    }
};

int main()
{
    //Item i1;
    //Item i2(i1);

    //Factory::create_vector_objects();

    /* 
     * TEST - 1 :: a copy of vector is returned
     * */
    vector<Item> v;
    v = Factory::get_vector_objects();

    /* 
     * TEST - 2 :: vector itself is returned
     * */
    //vector<Item> v2 = Factory::get_vector_objects();
    
    cout << "-- EXITING MAIN --" << endl;
}

