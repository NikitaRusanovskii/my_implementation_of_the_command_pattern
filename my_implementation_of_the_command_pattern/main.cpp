#include <iostream>

using namespace std;

/* ----------------------------------------------------------------------------------------
	
	Суть паттерна:
	
	Инкапсулируем запрос на выполнение какого-то действия в отдельный объект (команду).
	
	При этом объекты инициирующие запросы и объекты выполняющие их отделяются друг от
	друга.

	В данном паттерне участвуют:

	Command - интерфейс команды.
	ConcreteCommand - конкретная команда, которая выполняет n-ное действие.
	Receiver - интерфейс получателя, определяет действия, которые будет выполнять команда.
	Invoker - инициатор команды, он будет вызывать команду для выполнения запроса.
	Client - создает команду и устанавливает её получателя.

---------------------------------------------------------------------------------------- */

class Receiver { // интерфейс получателя, он определит действия команд
public:
	Receiver() = default;
	virtual void commandOn() = 0;
	virtual void commandOff() = 0;
};

class Command { // интерфейс команды
protected:
	Receiver* rec;
public:
	Command(Receiver* rec = nullptr) : rec(rec) {}
	virtual ~Command() = default;
	virtual void execute() = 0;
};

class Invoker { // инициатор команд
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

	После подготовки необходимых интерфейсов и написания инициатора команд,
	используем их для реализации паттерна на примере системы классов:
	Телевизор <- Пульт <- Пользователь

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