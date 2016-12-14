#include <iostream>
#include <map>
#include <iterator>

using namespace std;

class User
{
    public:
        int id;
        string name;

        User(int id, string s)
        {
            this->id    = id;
            this->name  = s;
        }

        ~User()
        {
        }

        bool operator<(const User& obj) const
        {
            if(this->id < obj.id)
            {
                return true;
            }
            return false;
        }
};

int main()
{
    map<User, int> m;
    map<User, int>::iterator it;

    pair<map<User, int>::iterator, bool> res;

    res = m.insert(pair<User, int>(User(1, "A"), 300));
    res = m.insert(pair<User, int>(User(1, "Z"), 400));
    if(res.second == false)
    {
        map<User, int>::iterator i = res.first;
        User u = i->first;
        cout << "Insertion Failed, element already present is " << i->second << "\t" << "id :" << u.id << "\t" << " name :" << u.name << endl;
    }

    res = m.insert(pair<User, int>(User(2, "B"), 100));
    res = m.insert(pair<User, int>(User(3, "C"), 1000));
    res = m.insert(pair<User, int>(User(4, "B"), 1001));

    cout << "MAP" << endl;
    for(it = m.begin(); it != m.end(); it++)
    {
        User u = it->first;
        cout << it->second << "\t" << "id :" << u.id << "\t" << " name :" << u.name << endl;
    }
}
