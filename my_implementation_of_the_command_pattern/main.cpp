#include <iostream>

using namespace std;

/* ----------------------------------------------------------------------------------------
	
	���� ��������:
	
	������������� ������ �� ���������� ������-�� �������� � ��������� ������ (�������).
	
	��� ���� ������� ������������ ������� � ������� ����������� �� ���������� ���� ��
	�����.

	� ������ �������� ���������:

	Command - ��������� �������.
	ConcreteCommand - ���������� �������, ������� ��������� n-��� ��������.
	Receiver - ��������� ����������, ���������� ��������, ������� ����� ��������� �������.
	Invoker - ��������� �������, �� ����� �������� ������� ��� ���������� �������.
	Client - ������� ������� � ������������� � ����������.

---------------------------------------------------------------------------------------- */

class Receiver { // ��������� ����������, �� ��������� �������� ������
public:
	Receiver() = default;
	virtual void commandOn() = 0;
	virtual void commandOff() = 0;
};

class Command { // ��������� �������
protected:
	Receiver* rec;
public:
	Command(Receiver* rec = nullptr) : rec(rec) {}
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class Invoker { // ��������� ������
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

	����� ���������� ����������� ����������� � ��������� ���������� ������,
	���������� �� ��� ���������� �������� �� ������� ������� �������:
	��������� <- ����� <- ������������

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

class Pult : public Receiver {
public:
	Pult() = default;
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
	Pult* pult = new Pult;
	ButtonOn* bon = new ButtonOn(pult);
	ButtonOff* boff = new ButtonOff(pult);

	user.setCommand(bon);
	user.executeCommand();

	user.setCommand(boff);
	user.executeCommand();


	return 0;
}