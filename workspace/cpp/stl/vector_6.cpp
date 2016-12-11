/*
 * how vector uses assignment operator
 */

#include <vector>
#include <iostream>
using namespace std;

struct Sample
{
    Sample(const Sample & obj)
    {
        std::cout<<"Sample copy constructor"<<std::endl;
    }
    Sample()
    {
        std::cout<<"Sample constructor"<<std::endl;
    }
    Sample & operator=(const Sample & obj)
    {
        std::cout<<"Sample assignment operator"<<std::endl;
    }
    ~Sample()
    {
        std::cout<<"Sample destructor"<<std::endl;
    }
};
int main()
{
    std::vector<Sample> vecOfInts;

    std::cout<<"Capacity :: "<<vecOfInts.capacity()<<std::endl;
    std::cout<<"Size :: "<<vecOfInts.size()<<std::endl;
    int capcity = vecOfInts.capacity();
    for(int i = 0; i < capcity + 1; i++)
        vecOfInts.push_back(Sample());

    std::cout<<"Capacity :: "<<vecOfInts.capacity()<<std::endl;
    std::cout<<"Size :: "<<vecOfInts.size()<<std::endl;

    Sample tmp;
    vecOfInts[capcity + 1] = tmp;

    return 0;
}
