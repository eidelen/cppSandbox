
void doInheritanceTest();

class Person
{
public:
    Person( ){};
    ~Person(){};

    bool isAllowedToDrive() const { return true; }
};

class Child: public Person
{
public:
    Child(){};
    ~Child(){};

    bool isAllowedToDrive() const { return false; }

};
