#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& name) : Name(name) {}

    virtual void Voice() const {
        cout << Name << " is silent" << endl;
    };
protected:
    const string Name;
};


class Dog : public Animal {
public:
    Dog(const string& name) : Animal(name) {}
    void Voice() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main()
{
    Dog d("Scooby");
    return 0;
}


/*
#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
    Animal(const string& name) : Name(name) {}

    const string Name;
};


class Dog : public Animal {
public:
    Dog(const string& name) : Animal(name) {}
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main()
{
    Dog d("Scooby");
    d.Bark();
    return 0;
}
 */