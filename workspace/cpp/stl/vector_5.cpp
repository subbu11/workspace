/*
 * fix iterator invalidation
 */
#include <iostream>
#include <vector>
using namespace std;

class Sample
{
    public:
    int i;
    int j;

    Sample(int a, int b)
    {
        this->i = a;
        this->j = b;
    }
};

int main()
{
    vector <Sample> v;

    vector<Sample>::iterator it;

    for(int i = 0; i < 5; i++)
        v.push_back(Sample(i + 10, i + 15));

    it = v.begin();
    while(it != v.end())
    {
        cout << "Sample " << (*it).i << " " << (*it).j << endl;
        it++;
    }

    /*remove 12-17 object*/
    it = v.begin();
    while(it != v.end())
    {
        if((*it).i == 12 && (*it).j == 17)
        {
            cout << "Removing Sample " << (*it).i << " " << (*it).j << endl;
            //v.erase(it); // <-- iterator invalidation
            it = v.erase(it); // FIX 
        }
        it++;
    }

    it = v.begin();
    //v.insert(it, Sample(100, 10)); // <-- iterator invalidation
    it = v.insert(it, Sample(100, 10)); // <-- iterator invalidation
    while(it != v.end())
    {
        cout << "Sample " << (*it).i << " " << (*it).j << endl;
        it++;
    }
}
