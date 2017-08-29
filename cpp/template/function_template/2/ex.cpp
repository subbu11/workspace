#include <iostream>

using namespace std;

template <class T>
T average(T *arr, int length)
{
    T sum = 0;

    for(int count = 0; count < length; count++)
        sum += arr[count];

    sum /= length;

    return sum;
}

class Rupee
{
    private:
        int mRupee;
    public:
        Rupee(int r)     {  mRupee = r; }
        ~Rupee()    {}

        friend ostream& operator<< (ostream &out, const Rupee &r)
        {
            out << r.mRupee << " Rs." ;
        }

        void operator+= (Rupee rhs)
        {
            mRupee += rhs.mRupee;
        }

        void operator/= (Rupee rhs)
        {
            mRupee /= rhs.mRupee;
        }
};

int main()
{
    int a1[] = {2, 4, 6, 10, 12};
    cout << average(a1, 5) << endl;

    Rupee a2[] = {Rupee(2), Rupee(4), Rupee(6), Rupee(8), Rupee(10)};
    cout << average(a2, 5) << endl;
}
