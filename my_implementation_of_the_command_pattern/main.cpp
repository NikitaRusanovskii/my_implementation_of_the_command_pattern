#include <iostream>

using namespace std;

/* ----------------------------------------------------------------------------------------

    Essence of the pattern:

    We encapsulate a request to perform some action in a separate object (command).

    At the same time, the objects initiating requests and the objects executing them
    are separated from each other.

    The following participants are involved in this pattern:

    Command - command interface.
    ConcreteCommand - a specific command that performs a certain action.
    Receiver - the recipient interface, defines the actions that the command will perform.
    Invoker - the command initiator, it will call the command to execute the request.
    Client - creates the command and assigns its receiver.

---------------------------------------------------------------------------------------- */

class Receiver { // receiver interface, defines command actions
public:
    Receiver() = default;
    virtual void commandOn() = 0;
    virtual void commandOff() = 0;
};

class Command { // command interface
protected:
    Receiver* rec;
public:
    Command(Receiver* rec = nullptr) : rec(rec) {}
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class Invoker { // command initiator
protected:
    Command* com = nullptr;
public:
    Invoker() = default;
    virtual ~Invoker() { delete com; }

    void executeCommand() {
        if (com != nullptr) {
            com->execute();
        }
    }

    void setCommand(Command* newCom) {
        if (com != newCom) {
            if (com != nullptr) {
                delete com;
            }
            com = newCom;
        }
    }
};

/*

    After preparing the necessary interfaces and writing the command initiator,
    we use them to implement the pattern using a class system example:
    TV <- Remote <- User

*/

class ButtonOn : public Command {
public:
    ButtonOn(Receiver* rec) : Command(rec) {}
    void execute() override {
        rec->commandOn();
    }
};

class ButtonOff : public Command {
public:
    ButtonOff(Receiver* rec) : Command(rec) {}
    void execute() override {
        rec->commandOff();
    }
};

class Remote : public Receiver {
public:
    Remote() = default;
    void commandOn() override {
        cout << "TV is on" << endl;
    }
    void commandOff() override {
        cout << "TV is off" << endl;
    }
};

class User : public Invoker {
public:
    User() = default;
};

int main() {

    User user;
    Remote* remote = new Remote;
    ButtonOn* bon = new ButtonOn(remote);
    ButtonOff* boff = new ButtonOff(remote);

    user.setCommand(bon);
    user.executeCommand();

    user.setCommand(boff);
    user.executeCommand();

    return 0;
}
