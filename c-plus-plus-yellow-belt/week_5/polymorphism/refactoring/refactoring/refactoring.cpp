#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& occupation)
        : name_(name), occupation_(occupation)
    {}
    virtual string GetName() const { return name_; }
    virtual string GetOccupation() const { return occupation_; }
    virtual string Log() const {
        return GetOccupation() + ": " + GetName();
    }
    virtual void Walk(const string& destination) const {
        cout << Log() << " walks to: " << destination << endl;
    }
private:
    const string name_;
    const string occupation_;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong)
        : Person(name, "Student"), favourite_song_(favouriteSong)
    {}
    void Walk(const string& destination) const override {
        cout << Log() << " walks to: " << destination << endl;
        this->SingSong();
    }
    void Learn() const {
        cout << Log() << " learns" << endl;
    }
    void SingSong() const {
        cout << Log() << " sings a song: " << favourite_song_ << endl;
    }
    string GetFavouriteSong() const {
        return favourite_song_;
    }

private:
    const string favourite_song_;
};

class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
        : Person(name, "Teacher"), subject_(subject)
    {}
    void Teach() const {
        cout << Log() << " teaches: " << subject_ << endl;
    }
    string GetSubject() const { return subject_; }

private:
    const string subject_;
};

class Policeman : public Person {
public:
    Policeman(const string& name) : Person(name, "Policeman") {}
    void Check(const Person& p) const {
        const string person_occupation = p.GetOccupation();
        cout << Log() << " checks " << person_occupation << ". " << person_occupation << "'s name is: " << p.GetName() << endl;
    }
};

void VisitPlaces(Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });
    return 0;
}
