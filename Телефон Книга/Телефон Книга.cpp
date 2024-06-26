

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

class Person {
	int sz;
	char* FIO;
	string phone;
	string mob_phone;
	string work_phone;
	string email;
	bool inl = false;

	friend ostream& operator<<(ostream& out, const Person& obj);
public:

	Person() : sz{ 150 }, FIO{ new char[sz] {} } {}

	Person(const char* FIO) : sz{ 150 }, FIO{ new char[sz] {} } {
		strcpy_s(this->FIO, sz, FIO);
	}

	Person (Person && obj): Person (obj.FIO) {
		obj.FIO = nullptr;
		obj.sz = 0;
	}

	Person(  const char* FIO, string phone, string mob_phone, string work_phone, string email) :
		sz{ 150 }, FIO{ new char [sz] {} }, phone{ phone }, mob_phone{ mob_phone }, work_phone{ work_phone }, email{ email } {
		strcpy_s(this->FIO, sz, FIO);
	}

	Person(const Person& obj) : sz{ obj.sz }, phone{ obj.phone }, mob_phone{ obj.mob_phone }, work_phone{ obj.work_phone }, email{ email }, FIO {new char[sz]} {
		strcpy_s(FIO, sz, obj.FIO);

	}

	Person& operator=(const Person& obj) {
		if (this != &obj) {
			sz = obj.sz;
			phone = obj.phone;
			mob_phone = obj.mob_phone;
			work_phone = obj.work_phone;
			email = obj.email;
			char *new_FIO = new char[sz];
			strcpy_s(new_FIO, sz, obj.FIO);
			delete[] FIO;
			FIO = new_FIO;
		}
		return *this;
	}

	Person& operator=( Person&& obj) {
		delete[] FIO;
		sz = obj.sz;
		FIO = obj.FIO;
		obj.FIO = nullptr;
		obj.sz = 0;
		return *this;
	}

	~Person() { delete[] FIO; }

	void print() const  {
		cout << "+------------------------------------+" << endl;
		cout << "F.I.O - " << FIO << endl;
		cout << "phone - " << phone << endl;
		cout << "mob-phone - " << mob_phone << endl;
		cout << "work-phone - " << work_phone << endl;
		cout << "email - " << email << endl;
		cout << "+------------------------------------+" << endl;
	}
	
	void set_FIO(const char* FIO) {
		delete[] this->FIO;
		this->FIO = new char[strlen(FIO) + 1];
		for (int i{}; i < strlen(FIO) + 1; ++i) {
			this->FIO[i] = FIO[i];
		}
		this->FIO [strlen(FIO)]= '\0';
	}

	char* get_FIO() const {
		return FIO;
	}

	void set_phone(string phone) {
		this->phone = phone;
	}

	string get_phone() const {
		return phone;
	}

	void set_mob_phone(string mob_phone) {
		this->mob_phone = mob_phone;
	}

	string get_mob_phone() const {
		return mob_phone;
	}

	void set_work_phone(string work_phone) {
		this->work_phone = work_phone;
	}

	string get_work_phone() const {
		return work_phone;
	}

	void set_email(string email) {
		this->email = email;
	}
	string get_email() const {
		return email;
	}

	void set_inl(bool inl) {
		this->inl = inl;
	}

	bool get_inl() const {
		return inl;
	}
};

ostream& operator<< (ostream& out, const Person& obj) {
	out <<"F.I.O : " << obj.get_FIO() << endl<<"Mob-phone : " << obj.get_mob_phone() << endl<<"Phone : " << obj.get_phone() << endl << "Work-phone : " << obj.get_work_phone() << endl<<" Email : " << obj.get_email() << endl;

	return out;
}

Person PersonFactory() {
	Person temp;
	cout << "Введите Ф.И.О. контакта : " << endl;
	char FIO[200]{};
	cin.ignore();
	cin.getline(FIO, 200);
	temp.set_FIO(FIO);
	
	cout << "Введите моб-телефон или поставьте - : " << endl;
	string mob;

	cin >> mob;
	temp.set_mob_phone(mob);
	cout << "Введите раб-телефон или поставьте - : " << endl;
	string rab;

	cin >> rab;
	temp.set_work_phone(rab);
	cout << "Введите телефон или поставьте - : " << endl;
	string tel;
	cin >> tel;
	temp.set_phone(tel);
	cout << "Введите email или поставьте - : " << endl;
	string email;

	cin >> email;
	temp.set_email(email);

	return temp;
	
}

class Phone_book {
	int sz;
	Person* book;

public:
	Phone_book(int sz=10 ) : sz{ sz }, book{ new Person[sz] } {}

	Phone_book(const Phone_book& obj) = delete;

	~Phone_book() { delete[] book; }

	
	

	void plus_person(const Person& obj, int i) {
		
		if (i >= sz) {
			return;
		}
		book[i] = obj;
		book[i].set_inl(true);
	}

	void del_person(int i) {
		if (i < 0 || i >= true_sz()) {
			return;
		}
		if (i == true_sz() - 1) {
			book[i].set_inl(false);
		}
		else {
			for (; i < true_sz(); ++i)
			{
				book[i] = book[i + 1];
			}
			book[true_sz() - 1].set_inl(false);
		}
	}

	int  true_sz() const {
		int count{};
		for (int i{}; book[i].get_inl() != false && i < sz;++i)
		{
			++count;
		}
		return count;
	}

	int size() const {
		return sz;
	}

	void print() const {
		for (int i{}; i < true_sz() ; ++i) {
			book[i].print();
		}
	}

	void del_back() {
		book[true_sz() - 1].set_inl(false);
	}

	void push_back(const Person& obj) {
		
		if (true_sz() < sz) {
			book[true_sz()] = obj;
			book[true_sz()].set_inl(true);
		}
	}
	
	void print_file() {
		ofstream out;
		out.open("base.txt");
		if (out.is_open()) {
			cout << "Файл открыт" << endl;
			for (int i{}; i < true_sz(); ++i) {
				out << book[i] << endl;
			}
		}
		out.close();
		cout << "Файл закрыт" << endl;
	}

	Person& operator[](int i) {
		return book[i];
	}

	void resaze() {
		
			sz *= 2;
			Person* new_book = new Person[sz];
			for (int i{}; i < true_sz(); ++i) {
				new_book[i] = book[i];
			}
			delete[] book;
			book = new_book;
		
	}

	void clear() {
		for (int i{}; i < true_sz(); ++i) {
			book[i].set_inl(false);
		}
	}

	void sort() {

		for (int i{}; i < true_sz(); ++i) {
			for (int j{}; j < true_sz(); ++j) {
				if (book[j].get_FIO() < book[j + 1].get_FIO()) {
					Person temp = book[j];
					book[j] = book[j + 1];
					book[j = 1] = temp;
				}
			}
		}

	}

};

int main()
{
	setlocale(LC_ALL, "rus");
	

	Phone_book a;

	

	int chose{};
	do {
		bool exit = false;
		cout << "Ваши дейсвия : " << endl;
		cout << "1. Добавить контакт : " << endl;
		cout << "2. Редактировать контакт : " << endl;
		cout << "3. Удалить контакт в конце списка :" << endl;
		cout << "4. Удалить контакт по индексу : " << endl;
		cout << "5. Записать базу в файл : " << endl;
		cout << "6. Увеличть размер базы: " << endl;
		cout << "7. Вывести базу на экран : " << endl;
		cout << "8. Очистка базы" << endl;
		cout << "9. Сортировка по имени" << endl;
		cout << "10. Выход " << endl;
		cin >> chose;
		switch (chose)
		{
		case 1:
		{
			a.push_back(PersonFactory());
			system("cls");

		} break;

		case 2:
		{
			int i{};
			cout << "Индекс для изменения : ";
			cin >> i;
			int choice{};
			do {
				
				cout << "1. Изменить Ф.И.О." << endl;
				cout << "2. Изменить телефон" << endl;
				cout << "3. Изменить моб-телефон" << endl;
				cout << "4. Изменить рабочий телефон " << endl;
				cout << "5. Изменень email" << endl;
				cout << "6. Выход" << endl;
				cin >> choice;
				switch (choice)
				{

				case 1:
				{
					cout << "Введите новое Ф.И.О" << endl;
					char FIO[200]{};
					cin.ignore();
					cin.getline(FIO, 200);
					a[i].set_FIO(FIO);
					system("cls");

				}break;

				case 2:
				{
					cout << "Введите новый телефон" << endl;
					string tel;
					cin >> tel;
					a[i].set_phone(tel);
					system("cls");
				}break;

				case 3:
				{
					cout << "Введите новый моб-телефон" << endl;
					string mob;
					cin >> mob;
					a[i].set_mob_phone(mob);
					system("cls");
				}break;

				case 4:
				{
					cout << "Введите новый рабочий телефон" << endl;
					string work;
					cin >> work;
					a[i].set_work_phone(work);
					system("cls");
				}break;

				case 5:
				{
					cout << "Введите новый email" << endl;
					string email;
					cin >> email;
					a[i].set_email(email);
					system("cls");
				}break;

				case 6:
				{
					exit = true;
				}break;
				
				default:
				{
					cout << "Ошибка !" << endl;
					system("cls");
				}break;

				}
				if (exit == true) // очеь хотелось сделать выход через goto))))
					break;
				

			} while (chose != 6);
		}break;

		case 3:
		{
			cout << "Контакт с индексом " << a.true_sz() - 1 << " удален" << endl;
			a.del_back();
			system("pause");
			system("cls");

		}break;

		case 4:
		{
			int i{};
			cout << "Введите индек для удаления : ";
			cin >> i;
			if (i >= a.true_sz())
				break;
			cout << "Контакт с индексом " << i << " удален" << endl;
			a.del_person(i);
			system("pause");
			system("cls");
		}break;

		case 5:
		{
			a.print_file();
			system("pause");
			system("cls");
		}break;

		case 6: 
		{
			a.resaze();

			cout << " Размер базы увеличен до " << a.size() << " элементов" << endl;
			system("pause");
			system("cls");
		}break;
		
		case 7:
		{
			a.print();
			system("pause");
			system("cls");
		} break;

		case 8:
		{
			cout << "База удалена" << endl;
			a.clear();
			system("pause");
			system("cls");

		}break;

		case 9:
		{
			a.sort();
			system("pause");
			system("cls");
		}break;

		case 10:
		{
			break;
		}break;

		default:
		{
			cout << "Ошибка неверный ввод" << endl;
			system("pause");
			system("cls");
		}break;

		}



	} while (chose != 10);
	
	
return 0;
}