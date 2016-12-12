/*
 * using set with user-defined objects
 */
#include <iostream>
#include <set>

using namespace std;

class Message
{
    public:
    string msg;
    string sender;
    string receiver;

    Message(string aMsg, string aSender, string aReceiver):
        msg(aMsg), sender(aSender), receiver(aReceiver)
    {
    }

    /* To compare two Message objects */
    bool operator< (const Message &a) const
    {
        string l = a.sender + a.msg + a.receiver;
        string r = this->sender + this->msg + this->receiver;

        return (l > r);
    }
};

int main()
{
    set<Message> setOfMessages;
    set<Message>::iterator it;

    Message m1("user_1", "Hello", "user_2");
    setOfMessages.insert(m1);

    Message m2("user_2", "Hi", "user_1");
    setOfMessages.insert(m2);
    
    /* message m3 does not get inserted in the set because it is duplicate of m1*/
    Message m3("user_1", "Hello", "user_2");
    setOfMessages.insert(m3);
    
    Message m4("user_2", "Hey", "user_1");
    setOfMessages.insert(m4);

    for(it = setOfMessages.begin(); it != setOfMessages.end(); it++)
    {
        cout << (*it).sender << " " << (*it).msg << " " << (*it).receiver << endl;
    }

   
}
