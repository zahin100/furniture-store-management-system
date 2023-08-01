/*
NAME: AKMAL ZAHIN BIN ZULKEPLI
MATRIC NUMBER: B032010175
PROGRAMME: BITS
*/

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <mysql.h>
using namespace std;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
int queryStatus;

string userID;

class database_connection {

	public:
		static void ConnectionFunction() {

			conn = mysql_init(0);
			if (conn) 
				cout << "Connected to Database" << endl;

			else
				cout << "Database connection failed!" << endl;

			conn = mysql_real_connect(conn, "localhost", "root", "", "furniture", 3306, NULL, 0);

			if (conn) {
				cout << "Connected to MySQL" << endl;
				cout << "Press any key to continue..." << endl;
				_getch();
				system("cls");
			}
			else
				cout << "MySQL connection failed!" << endl;
		}
};

bool check_number(string input);
void registration();
void registerCustomer();
void registerAdmin();
void login();
void customerLogin();
void adminLogin();
void customerMenu();
void adminMenu();
void order();
void viewFurniture();
void calculateCost(string, int);
void insertOrderDetails(string, string, string);
void displayReceipt(double, int, double, string);
void purchaseHistory();
void updateCustomerAccount();
void insertFurnitures();
void searchFurnitures();
void updateFurnitures();
void deleteFurnitures();
void viewInventory();
void viewSalesReport();
void updateAdminAccount();


int main() {

	system("cls");
	system("title Furniture Store");
	database_connection::ConnectionFunction();

	int mainMenuChoice;

	cout << "*===================================*" << endl;
	cout << "| FURNITURE STORE MANAGEMENT SYSTEM |" << endl;
	cout << "*===================================*" << "\n\n";

	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "3. Exit" << endl;
	cout << "Enter your choice : ";
	cin >> mainMenuChoice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> mainMenuChoice;
	}


	if (mainMenuChoice == 1) {
		registration();
	}

	else if (mainMenuChoice == 2) {
		login();
	}

	else if (mainMenuChoice == 3) {

		cout << "\nThank you for your visit." << endl;
		exit(0);
	}

	else {
		cout << "\nInvalid choice. Please enter number 1, 2 or 3 only. Press any key to continue..." << endl;
		_getch();
		system("cls");
		main();
	}

	return 0;
}

bool check_number(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (isdigit(input[i]) == false) {

			if (input[i] == '.')
				return true;
			else
				return false;
		}
	}
	return true;
}

void registration() {

	system("cls");
	int choice;

	cout << "Please choose if you want to register as customer or admin." << "\n\n";
	cout << "0. Go back to main menu" << endl;
	cout << "1. Customer" << endl;
	cout << "2. Admin" << endl;
	cout << "\nEnter your choice : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 0)
		main();

	else if (choice == 1)
		registerCustomer();

	else if (choice == 2)
		registerAdmin();

	else {
		cout << "Invalid choice. Please enter number 0, 1 or 2 only. Press any key to continue...";
		_getch();
		system("cls");
		registration();
	}
}

void registerCustomer() {

	system("cls");
	string name, phoneNum, address, username, password;
	int choice;
	cout << "*============================*" << endl;
	cout << "| Customer Registration Page |" << endl;
	cout << "*============================*" << "\n\n";

	cout << "Enter your name : ";
	cin.ignore(1, '\n');
	getline(cin, name);
	while (check_number(name) == true) {
		cout << "\nPlease enter letters only.\n";
		cout << "Enter your name : ";
		getline(cin, name);
	}

	cout << "Enter your phone number : ";
	getline(cin, phoneNum);
	while (check_number(phoneNum) == false || phoneNum.length() != 10) {

		if (check_number(phoneNum) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter your phone number : ";
			getline(cin, phoneNum);
		}

		else {
			cout << "\nYour phone number must be 10 digits.\n";
			cout << "Enter your phone number : ";
			getline(cin, phoneNum);
		}
	}

	cout << "Enter your home address : ";
	getline(cin, address);
	cout << "Enter your username : ";
	getline(cin, username);
	cout << "Enter your password : ";
	getline(cin, password);

	do {
		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> choice;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter your choice : ";
			cin >> choice;
		}

		if (choice == 0)
			registration();

		else if (choice == 1) {
			string check_username = "select * from Customer where customer_username = '" + username + "'";
			const char* checkUsername = check_username.c_str();
			queryStatus = mysql_query(conn, checkUsername);

			if (!queryStatus) {

				res = mysql_store_result(conn);

				if (res->row_count == 1) {

					cout << "\nUsername is already taken. Press any key to try again...";
					_getch();
					registerCustomer();
				}

				else {

					string insert_customer = "insert into Customer (customer_name, customer_phoneNum, customer_address, customer_username, customer_password) values ('" + name + "', '" + phoneNum + "', '" + address + "', '" + username + "', '" + password + "' )";
					const char* insertCustomer = insert_customer.c_str();
					queryStatus = mysql_query(conn, insertCustomer);

					if (!queryStatus) {

						cout << "\nYour registration is successful. Press any key to continue...";
						_getch();
						main();
					}

					else
						cout << "Query execution error!" << mysql_errno(conn) << endl;
				}
			}

			else
				cout << "Query execution error!" << mysql_errno(conn) << endl;
		}

		else
			cout << "Please enter number 0 or 1 only.\n";
	} while (choice != 0 && choice != 1);
}

void registerAdmin() {

	system("cls");
	string name, phoneNum, address, username, password;
	int choice;
	cout << "*=========================*" << endl;
	cout << "| Admin Registration Page |" << endl;
	cout << "*=========================*" << "\n\n";

	cout << "Enter your name : ";
	cin.ignore(1, '\n');
	getline(cin, name);
	while (check_number(name) == true) {
		cout << "\nPlease enter letters only.\n";
		cout << "Enter your name : ";
		getline(cin, name);
	}

	cout << "Enter your phone number : ";
	getline(cin, phoneNum);
	while (check_number(phoneNum) == false || phoneNum.length() != 10) {

		if (check_number(phoneNum) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter your phone number : ";
			getline(cin, phoneNum);
		}

		else {
			cout << "\nYour phone number must be 10 digits.\n";
			cout << "Enter your phone number : ";
			getline(cin, phoneNum);
		}
	}

	cout << "Enter your home address : ";
	getline(cin, address);
	cout << "Enter your username : ";
	getline(cin, username);
	cout << "Enter your password : ";
	getline(cin, password);

	do {
		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> choice;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter your choice : ";
			cin >> choice;
		}

		if (choice == 0)
			registration();

		else if (choice == 1) {

			string check_username = "select * from Admin where admin_username = '" + username + "'";
			const char* checkUsername = check_username.c_str();
			queryStatus = mysql_query(conn, checkUsername);

			if (!queryStatus) {

				res = mysql_store_result(conn);

				if (res->row_count == 1) {

					cout << "\nUsername is already taken. Press any key to try again...";
					_getch();
					registerAdmin();
				}

				else {

					string insert_admin = "insert into Admin (admin_name, admin_phoneNum, admin_address, admin_username, admin_password) values ('" + name + "', '" + phoneNum + "', '" + address + "', '" + username + "', '" + password + "')";
					const char* insertAdmin = insert_admin.c_str();
					queryStatus = mysql_query(conn, insertAdmin);


					if (!queryStatus) {

						cout << "\nYour registration is successful. Press any key to continue...";
						_getch();
						main();
					}

					else
						cout << "Query execution error!" << mysql_errno(conn) << endl;
				}
			}

			else
				cout << "Query execution error!" << mysql_errno(conn) << endl;
		}

		else
			cout << "Please enter number 0 or 1 only.\n";
	} while (choice != 0 && choice != 1);
}

void login() {

	system("cls");
	int choice;

	cout << "Please choose if you want to log in as customer or admin." << "\n\n";
	cout << "0. Go back to main menu" << endl;
	cout << "1. Customer" << endl;
	cout << "2. Admin" << endl;
	cout << "\nEnter your choice : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 0)
		main();

	else if (choice == 1)
		customerLogin();

	else if (choice == 2)
		adminLogin();

	else {
		cout << "Invalid choice. Please enter number 0, 1 or 2 only. Press any key to continue...";
		_getch();
		system("cls");
		login();
	}
}

void customerLogin() {

	system("cls");
	string username, password;
	int choice;

	cout << "*=====================*" << endl;
	cout << "| Customer Login Page |" << endl;
	cout << "*=====================*" << "\n\n";

	cout << "Enter your username : ";
	cin.ignore(1, '\n');
	getline(cin, username);
	cout << "Password : ";
	getline(cin, password);

	string check_username = "select customer_id from Customer where customer_username = '" + username + "' and customer_password = '" + password + "'";
	const char* checkUsername = check_username.c_str();
	queryStatus = mysql_query(conn, checkUsername);

	if (!queryStatus) {

		res = mysql_store_result(conn);

		if (res->row_count == 1) {

			while (row = mysql_fetch_row(res))
				userID = row[0];
			customerMenu();
		}

		else {

			cout << "\n\nInvalid username or password. Enter 0 to go to previous page or 1 to try again." << endl;
			cout << "Enter your choice : ";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear(); // clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter your choice : ";
				cin >> choice;
			}

			if (choice == 0)
				login();

			else if (choice == 1)
				customerLogin();

			else {
				do {
				cout << "\nInvalid choice. Please enter number 0 or 1 only." << endl;
				cout << "Enter your choice : ";
				cin >> choice;
				while (cin.fail())
				{
					cin.clear(); // clear input buffer to restore cin to a usable state
					cin.ignore(INT_MAX, '\n'); // ignore last input
					cout << "\nPlease enter numbers only.\n";
					cout << "Enter your choice : ";
					cin >> choice;
				}

				if (choice == 0)
					login();

				else if (choice == 1)
					customerLogin();

				} while (choice != 0 && choice != 1);
			}
		}
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;
}

void adminLogin() {

	system("cls");
	string username, password;
	int choice;

	cout << "*==================*" << endl;
	cout << "| Admin Login Page |" << endl;
	cout << "*==================*" << "\n\n";

	cout << "Enter your username : ";
	cin.ignore(1, '\n');
	getline(cin, username);
	cout << "Enter your password : ";
	getline(cin, password);

	string check_username = "select admin_id from Admin where admin_username = '" + username + "' and admin_password = '" + password + "'";
	const char* checkUsername = check_username.c_str();
	queryStatus = mysql_query(conn, checkUsername);

	if (!queryStatus) {

		res = mysql_store_result(conn);

		if (res->row_count == 1) {

			while (row = mysql_fetch_row(res))
				userID = row[0];
			adminMenu();
		}

		else {

			cout << "\n\nInvalid username or password. Enter 0 to go to previous page or 1 to try again." << endl;
			cout << "Enter your choice : ";
			cin >> choice;
			while (cin.fail())
			{
				cin.clear(); // clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter your choice : ";
				cin >> choice;
			}

			if (choice == 0)
				login();

			else if (choice == 1)
				adminLogin();

			else {

				do {
					cout << "\nInvalid choice. Please enter number 0 or 1 only." << endl;
					cout << "Enter your choice : ";
					cin >> choice;
					while (cin.fail())
					{
						cin.clear(); // clear input buffer to restore cin to a usable state
						cin.ignore(INT_MAX, '\n'); // ignore last input
						cout << "\nPlease enter numbers only.\n";
						cout << "Enter your choice : ";
						cin >> choice;
					}

						if (choice == 0)
							login();

						else if (choice == 1)
							adminLogin();

				} while (choice != 0 && choice != 1);
			}
		}
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;
}

void customerMenu() {

	system("cls");
	int choice;

	cout << "*====================*" << endl;
	cout << "| Customer Menu Page |" << endl;
	cout << "*====================*" << "\n\n";

	cout << "1. Buy furnitures " << endl;
	cout << "2. View purchase history " << endl;
	cout << "3. Update account information " << endl;
	cout << "4. Log out " << "\n\n";
	cout << "Enter your choice : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 1)
		order();

	else if (choice == 2)
		purchaseHistory();

	else if (choice == 3)
		updateCustomerAccount();

	else if (choice == 4)
		main();

	else {
		cout << "Please enter number 1, 2, 3 or 4 only. Press any key to try again...";
		_getch();
		customerMenu();
	}
}

void order() {

	system("cls");
	int choice, quantity, confirmation;
	string furnitureID, stock;

	viewFurniture();
	cout << "\nEnter the ID of the furniture that you want to buy (enter 0 to go back to the previous page) : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter the ID of the furniture that you want to buy (enter 0 to go back to the previous page) : ";
		cin >> choice;
	}

	if (choice == 0)
		customerMenu();
	
	else {
		string input = to_string(choice);
		string checkFurniture_id = "select furniture_id from furniture_item where furniture_id = '" + input + "'";
		const char* checkFurnitureID = checkFurniture_id.c_str();
		queryStatus = mysql_query(conn, checkFurnitureID);

		if (!queryStatus) {

			res = mysql_store_result(conn);
			if (res->row_count != 1) {
				cout << "Invalid furniture ID. Press any key to try again...";
				_getch();
				order();
			}
		}

		else
			cout << "Query execution error!" << mysql_errno(conn) << endl;

		cout << "Enter the quantity (20% discount of the total cost for 3 or more quantity) : ";
		cin >> quantity;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter the quantity (20% discount of the total cost for 3 or more quantity) : ";
			cin >> quantity;
		}

		furnitureID = to_string(choice);
		string checkFurniture_stock = "select furniture_stock from furniture_item where furniture_id = '" + furnitureID + "'";
		const char* checkFurnitureStock = checkFurniture_stock.c_str();
		queryStatus = mysql_query(conn, checkFurnitureStock);

		if (!queryStatus) {

			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			stock = row[0];
			if (stoi(stock) == 0) {
				cout << "The item is out of stock. Press any key to try again...";
				_getch();
				order();
			}
			
			else if (quantity > stoi(stock)) {
				cout << "The quantity you entered is more than the stock available. Press any key to try again...";
				_getch();
				order();
			}

			else if (quantity <= 0) {
				cout << "Invalid quantity. Press any key to try again...";
				_getch();
				order();
			}
		}

		else
			cout << "Query execution error!" << mysql_errno(conn) << endl;

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			customerMenu();

		else if (confirmation == 1) {
			furnitureID = to_string(choice);
			calculateCost(furnitureID, quantity);
			customerMenu();
		}

		else {

			do {
				cout << "\nInvalid input. Please enter number 0 or 1 only." << endl;
				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
				while (cin.fail())
				{
					cin.clear(); // clear input buffer to restore cin to a usable state
					cin.ignore(INT_MAX, '\n'); // ignore last input
					cout << "\nPlease enter numbers only.\n";
					cout << "Enter 0 to cancel or 1 to proceed : ";
					cin >> confirmation;
				}

				if (confirmation == 0)
					customerMenu();

				else if (confirmation == 1) {
					furnitureID = to_string(choice);
					calculateCost(furnitureID, quantity);
					customerMenu();
				}

			} while (confirmation != 0 && confirmation != 1);
		}
	}
}

void viewFurniture() {

	system("cls");

	cout << "\t======================= List of all furnitures ========================" << endl;

	queryStatus = mysql_query(conn, "Select furniture_id, furniture_name, furniture_price, furniture_stock from furniture_item");

	if (!queryStatus) {

		cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(25) << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(15) << row[3] << endl;
		}	
		cout << "\t=======================================================================" << endl;
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;
}

void calculateCost(string furnitureID, int quantity) {

	string price, stock;
	int newStock;
	double totalCost;

	string get_stock = "select furniture_stock from furniture_item where furniture_id = '" + furnitureID + "'";
	const char* getStock = get_stock.c_str();
	queryStatus = mysql_query(conn, getStock);

	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		stock = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	newStock = stoi(stock) - quantity;
	string update_stock = "update furniture_item set furniture_stock = '" + to_string(newStock) + "' where furniture_id = '" + furnitureID + "'";
	const char* updateStock = update_stock.c_str();
	queryStatus = mysql_query(conn, updateStock);

	string get_price = "select furniture_price from furniture_item where furniture_id = '" + furnitureID + "'";
	const char* getPrice = get_price.c_str();
	queryStatus = mysql_query(conn, getPrice);

	if (!queryStatus) {

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
			price = row[0];

		if (quantity >= 3) {
			totalCost = stod(price) * quantity;
			totalCost = totalCost * 0.8;
		}

		else
			totalCost = stod(price) * quantity;

		displayReceipt(totalCost, quantity, stod(price), furnitureID);
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;
}

void displayReceipt(double totalCost, int quantity, double price, string furnitureID) {

	system("cls");
	string date, buyerName, item;

	queryStatus = mysql_query(conn, "select date_format(curdate(), '%d/%m/%Y');");
	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		date = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	string customer_name = "select customer_name from customer where customer_id = '" + userID + "'";
	const char* customerName = customer_name.c_str();
	queryStatus = mysql_query(conn, customerName);

	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		buyerName = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	string item_name = "select furniture_name from furniture_item where furniture_id = '" + furnitureID + "'";
	const char* itemName = item_name.c_str();
	queryStatus = mysql_query(conn, itemName);

	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		item = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	insertOrderDetails(to_string(quantity), to_string(totalCost), furnitureID);

	cout << "================Receipt================" << endl;
	cout << "Order date      : " << date << endl;
	cout << "Customer's name : " << buyerName << endl;
	cout << "Item            : " << item << endl;
	cout << "Price           : RM " << price << endl;
	cout << "Quantity        : " << quantity << endl;
	cout << "Total cost      : RM " << totalCost << endl;
	cout << "=======================================" << endl;
	cout << "Press any key to continue...";
	_getch();
}

void insertOrderDetails(string quantity, string totalCost, string furnitureID) {

	string date, orderID;

	queryStatus = mysql_query(conn, "select curdate()");
	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		date = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	string insert_into_orders = "insert into orders (order_date, customer_id) values ('" + date + "', '" + userID + "')";
	const char* insertIntoOrders = insert_into_orders.c_str();
	queryStatus = mysql_query(conn, insertIntoOrders);

	if (!queryStatus) {

	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	queryStatus = mysql_query(conn, "select order_id from orders order by order_id desc limit 1");
	if (!queryStatus) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		orderID = row[0];
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

	string insert_into_order_furniture = "insert into order_furniture (of_quantity, of_totalCost, order_id, furniture_id) values ('" + quantity + "', '" + totalCost + "', '" + orderID + "', '" + furnitureID + "')";
	const char* insertIntoOrderFurniture = insert_into_order_furniture.c_str();
	queryStatus = mysql_query(conn, insertIntoOrderFurniture);

	if (!queryStatus) {

	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;

}

void purchaseHistory() {

	system("cls"); 
	int i = 0;
	int j = 0;
	string orderID[1000];
	string furnitureID[1000];
	string date[1000];
	string item[1000];
	string price[1000];
	string quantity[1000];
	string totalCost[1000];

	string check_data = "select order_id from orders where customer_id = '" + userID + "'";
	const char* checkData = check_data.c_str();
	queryStatus = mysql_query(conn, checkData);

	if (!queryStatus) {
		
		res = mysql_store_result(conn);
		if (res->row_count == 0) {
			cout << "You have not purchased anything yet. Press any key to continue...";
			_getch();
			customerMenu();
		}

		else {
			cout << "\t==================================== Purchase History =======================================" << endl;
			cout << setw(18) << "Order date" << setw(20) << "Item" << setw(20) << "Price" << setw(17) << "Quantity" << setw(24) << "Total cost" << setw(20) << endl;

			string get_order_id = "select order_id from orders where customer_id = '" + userID + "'";
			const char* getOrderID = get_order_id.c_str();
			queryStatus = mysql_query(conn, getOrderID);

			if (!queryStatus) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				do {
					orderID[i] = row[0];
					i++;
				} while (row = mysql_fetch_row(res));
			}

			else
				cout << "Query execution error!" << mysql_errno(conn) << endl;

			i = 0;
			do {
				string get_furniture_id = "select furniture_id from order_furniture where order_id = '" + orderID[i] + "'";
				const char* getFurnitureID = get_furniture_id.c_str();
				queryStatus = mysql_query(conn, getFurnitureID);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					furnitureID[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (orderID[i] != "\0");

			i = 0;
			j = 0;
			do { 
				string get_date = "select date_format(order_date, '%d/%m/%Y') from orders where order_id = '" + orderID[i] + "'";
				const char* getDate = get_date.c_str();
				queryStatus = mysql_query(conn, getDate);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					date[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (orderID[i] != "\0");

			i = 0;
			j = 0;
			do {
				string get_item_name = "select furniture_name from furniture_item where furniture_id = '" + furnitureID[i] + "'";
				const char* getItemName = get_item_name.c_str();
				queryStatus = mysql_query(conn, getItemName);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					item[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (furnitureID[i] != "\0");

			i = 0;
			j = 0;
			do {
				string get_price = "select furniture_price from furniture_item where furniture_id = '" + furnitureID[i] + "'";
				const char* getPrice = get_price.c_str();
				queryStatus = mysql_query(conn, getPrice);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					price[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (furnitureID[i] != "\0");

			i = 0;
			j = 0;
			do {
				string get_quantity = "select of_quantity from order_furniture where order_id = '" + orderID[i] + "'";
				const char* getQuantity = get_quantity.c_str();
				queryStatus = mysql_query(conn, getQuantity);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					quantity[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (orderID[i] != "\0");

			i = 0;
			j = 0;
			do {
				string get_total_cost = "select of_totalCost from order_furniture where order_id = '" + orderID[i] + "'";
				const char* getTotalCost = get_total_cost.c_str();
				queryStatus = mysql_query(conn, getTotalCost);

				if (!queryStatus) {
					res = mysql_store_result(conn);
					row = mysql_fetch_row(res);
					totalCost[j] = row[0];
					j++;
					i++;
				}

				else
					cout << "Query execution error!" << mysql_errno(conn) << endl;
			} while (orderID[i] != "\0");

			i = 0;
			do {
				cout << setw(18) << date[i] << setw(25) << item[i] << setw(11) << "RM " << price[i] << setw(11) << quantity[i] << setw(22) << "RM " << totalCost[i] << endl;
				i++;
			} while (orderID[i] != "\0");

			cout << "\t=============================================================================================" << endl;
			cout << "\nPress any key to continue...";
			_getch();
			customerMenu();
		}
	}

	else
		cout << "Query execution error!" << mysql_errno(conn) << endl;
}

void updateCustomerAccount() {

	system("cls");
	string newData, currentPassword;
	int choice, confirmation;

	cout << "======= Update Your Account Information =======" << endl;

	string get_data = "select customer_name, customer_phoneNum, customer_address from customer where customer_id = '" + userID + "'";
	const char* getData = get_data.c_str();
	queryStatus = mysql_query(conn, getData);
	
	cout << "\n-----------------------------------------------";
	res = mysql_store_result(conn);
	while(row = mysql_fetch_row(res)) {
		cout << "\nName         : " << row[0] << endl;
		cout << "Phone number : " << row[1] << endl;
		cout << "Address      : " << row[2] << endl;
	}
	cout << "-----------------------------------------------" << endl;

	cout << "\n0. Go back to the previous page" << endl;
	cout << "1. Name" << endl;
	cout << "2. Phone number" << endl;
	cout << "3. Address" << endl;
	cout << "4. Password" << endl;
	cout << "Enter your choice : ";
	cin >> choice;
	cin.ignore(1, '\n');
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 0)
		customerMenu();

	else if (choice == 1) {
		cout << "Enter the new name : ";
		getline(cin, newData);
		while (check_number(newData) == true) {
			cout << "\nPlease enter letters only.\n";
			cout << "Enter the new name : ";
			getline(cin, newData);
		}

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateCustomerAccount();

		else if (confirmation == 1) {
			string update_name = "update customer set customer_name = '" + newData + "' where customer_id = '" + userID + "'";
			const char* updateName = update_name.c_str();
			queryStatus = mysql_query(conn, updateName);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			customerMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateCustomerAccount();
		}

	}

	else if (choice == 2) {
		cout << "Enter the new phone number : ";
		getline(cin, newData);
		while (check_number(newData) == false || newData.length() != 10) {

			if (check_number(newData) == false) {
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter the new phone number : ";
				getline(cin, newData);
			}

			else {
				cout << "\nYour phone number must be 10 digits.\n";
				cout << "Enter the new phone number : ";
				getline(cin, newData);
			}
		}

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateCustomerAccount();

		else if (confirmation == 1) {
			string update_phoneNum = "update customer set customer_phoneNum = '" + newData + "' where customer_id = '" + userID + "'";
			const char* updatePhoneNum = update_phoneNum.c_str();
			queryStatus = mysql_query(conn, updatePhoneNum);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			customerMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateCustomerAccount();
		}
	}

	else if (choice == 3) {
		cout << "Enter the new address : ";
		getline(cin, newData);

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateCustomerAccount();

		else if (confirmation == 1) {
			string update_address = "update customer set customer_address = '" + newData + "' where customer_id = '" + userID + "'";
			const char* updateAddress = update_address.c_str();
			queryStatus = mysql_query(conn, updateAddress);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			customerMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateCustomerAccount();
		}
	}

	else if (choice == 4) {

		cout << "Enter the current password : ";
		getline(cin, currentPassword);

		string check_password = "select customer_password from customer where customer_id = '" + userID + "' and customer_password = '" + currentPassword + "'";
		const char* checkPassword = check_password.c_str();
		queryStatus = mysql_query(conn, checkPassword);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count == 1) {
				cout << "Enter the new password : ";
				getline(cin, newData);

				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
				while (cin.fail())
				{
					cin.clear(); // clear input buffer to restore cin to a usable state
					cin.ignore(INT_MAX, '\n'); // ignore last input
					cout << "\nPlease enter numbers only.\n";
					cout << "Enter 0 to cancel or 1 to proceed : ";
					cin >> confirmation;
				}

				if (confirmation == 0)
					updateCustomerAccount();

				else if (confirmation == 1) {
					string update_password = "update customer set customer_password = '" + newData + "' where customer_id = '" + userID + "'";
					const char* updatePassword = update_password.c_str();
					queryStatus = mysql_query(conn, updatePassword);
					cout << "The update is successful. Press any key to continue...";
					_getch();
					customerMenu();
				}

				else {
					cout << "Invalid choice. Press any key to try again...";
					_getch();
					updateCustomerAccount();
				}
			}

			else {
				cout << "Invalid password. Press any key to try again...";
				_getch();
				updateCustomerAccount();
			}
		}
	}

	else {
		cout << "Invalid choice. Please enter number 0, 1, 2, 3 or 4 only. Press any key to try again...";
		_getch();
		updateCustomerAccount();
	}
}

void adminMenu() {

	system("cls");
	int choice;

	cout << "*=================*" << endl;
	cout << "| Admin Menu Page |" << endl;
	cout << "*=================*" << "\n\n";

	cout << "1. Add new furnitures " << endl;
	cout << "2. Search furnitures " << endl;
	cout << "3. Update furnitures " << endl;
	cout << "4. Delete furnitures " << endl;
	cout << "5. View inventory " << endl;
	cout << "6. View monthly sales report" << endl;
	cout << "7. Update account information " << endl;
	cout << "8. Log out " << "\n\n";
	cout << "Enter your choice : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 1)
		insertFurnitures();

	else if (choice == 2)
		searchFurnitures();

	else if (choice == 3)
		updateFurnitures();

	else if (choice == 4)
		deleteFurnitures();

	else if (choice == 5)
		viewInventory();

	else if (choice == 6)
		viewSalesReport();

	else if (choice == 7)
		updateAdminAccount();

	else if (choice == 8)
		main();

	else {
		cout << "Please enter number 1 - 8 only. Press any key to try again...";
		_getch();
		adminMenu();
	}
}

void insertFurnitures() {

	system("cls");
	string furnitureName, furniturePrice, furnitureStock;
	int confirmation;

	cout << "=====Add New Furnitures=====" << "\n\n";
	cin.ignore(1, '\n');
	cout << "Furniture name : ";
	getline(cin, furnitureName);
	while (check_number(furnitureName) == true) {
		cout << "\nPlease enter letters only.\n";
		cout << "Furniture name : ";
		getline(cin, furnitureName);
	}

	cout << "Furniture price : ";
	getline(cin, furniturePrice);
	while (check_number(furniturePrice) == false) {
		cout << "\nPlease enter numbers only.\n";
		cout << "Furniture price : ";
		getline(cin, furniturePrice);
	}

	cout << "Furniture stock : ";
	getline(cin, furnitureStock);
	while (check_number(furnitureStock) == false) {
		cout << "\nPlease enter numbers only.\n";
		cout << "Furniture Stock : ";
		getline(cin, furnitureStock);
	}

	cout << "Enter 0 to cancel or 1 to proceed : ";
	cin >> confirmation;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
	}

	if (confirmation == 0)
		adminMenu();

	else if (confirmation == 1) {
		string add_furniture = "insert into furniture_item (furniture_name, furniture_price, furniture_stock, admin_id) values ('" + furnitureName + "', '" + furniturePrice + "', '" + furnitureStock + "', '" + userID + "')";
		const char* addFurniture = add_furniture.c_str();
		queryStatus = mysql_query(conn, addFurniture);

		if (!queryStatus) {
			cout << "The furniture has been successfully added. Press any key to continue...";
			_getch();
			adminMenu();
		}

		else
			cout << "Query execution error!" << mysql_errno(conn) << endl;
	}

	else {
		cout << "Invalid choice. Press any key to try again...";
		_getch();
		insertFurnitures();
	}
}

void searchFurnitures() {

	system("cls");
	string furnitureID, furnitureName, furniturePrice, furnitureStock, adminID;
	int choice;

	cout << "Search furniture by : " << endl;
	cout << "0. Go back to the previous page" << endl;
	cout << "1. ID" << endl;
	cout << "2. Name" << endl;
	cout << "3. Price" << endl;
	cout << "4. Stock" << endl;
	cout << "5. Admin ID" << endl;
	cout << "Enter your choice : ";
	cin >> choice;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 0)
		adminMenu();

	else if (choice == 1) {

		cin.ignore(1, '\n');
		cout << "Enter the furniture ID : ";
		getline(cin, furnitureID);
		while (check_number(furnitureID) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter the furniture ID : ";
			getline(cin, furnitureID);
		}

		string search_furniture_id = "select * from furniture_item where furniture_id = '" + furnitureID + "'";
		const char* searchFurnitureID = search_furniture_id.c_str();
		queryStatus = mysql_query(conn, searchFurnitureID);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count == 1) {
				system("cls");
				cout << "\t====================================== Search Results ====================================" << endl;
				cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
				while (row = mysql_fetch_row(res)) {
					cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
				}
				cout << "\t==========================================================================================\n";
				cout << "\nPress any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "\nNo data found. Press any key to try again...";
				_getch();
				searchFurnitures();
			}
		}
	}

	else if (choice == 2) {
		cin.ignore(1, '\n');
		cout << "Enter the furniture name : ";
		getline(cin, furnitureName);
		while (check_number(furnitureName) == true) {
			cout << "\nPlease enter letters only.\n";
			cout << "Enter the furniture name : ";
			getline(cin, furnitureName);
		}

		string search_name = "select * from furniture_item where furniture_name like '%" + furnitureName + "%'";
		const char* searchName = search_name.c_str();
		queryStatus = mysql_query(conn, searchName);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 0) {
				system("cls");
				cout << "\t====================================== Search Results ====================================" << endl;
				cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
				while (row = mysql_fetch_row(res)) {
					cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
				}
				cout << "\t==========================================================================================\n";
				cout << "\nPress any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "\nNo data found. Press any key to try again...";
				_getch();
				searchFurnitures();
			}
		}
	}

	else if (choice == 3) {
		cin.ignore(1, '\n');
		cout << "Enter the furniture price : ";
		getline(cin, furniturePrice);
		while (check_number(furniturePrice) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter the furniture price : ";
			getline(cin, furniturePrice);
		}

		string search_price = "select * from furniture_item where furniture_price = '" + furniturePrice + "'";
		const char* searchPrice = search_price.c_str();
		queryStatus = mysql_query(conn, searchPrice);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 0) {
				system("cls");
				cout << "\t====================================== Search Results ====================================" << endl;
				cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
				while (row = mysql_fetch_row(res)) {
					cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
				}
				cout << "\t==========================================================================================\n";
				cout << "\nPress any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "\nNo data found. Press any key to try again...";
				_getch();
				searchFurnitures();
			}
		}
	}

	else if (choice == 4) {
		cin.ignore(1, '\n');
		cout << "Enter the furniture stock : ";
		getline(cin, furnitureStock);
		while (check_number(furnitureStock) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter the furniture stock : ";
			getline(cin, furnitureStock);
		}

		string search_stock = "select * from furniture_item where furniture_stock = '" + furnitureStock + "'";
		const char* searchStock = search_stock.c_str();
		queryStatus = mysql_query(conn, searchStock);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 0) {
				system("cls");
				cout << "\t====================================== Search Results ====================================" << endl;
				cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
				while (row = mysql_fetch_row(res)) {
					cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
				}
				cout << "\t==========================================================================================\n";
				cout << "\nPress any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "\nNo data found. Press any key to try again...";
				_getch();
				searchFurnitures();
			}
		}
	}

	else if (choice == 5) {
		cin.ignore(1, '\n');
		cout << "Enter the admin ID : ";
		getline(cin, adminID);
		while (check_number(adminID) == false) {
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter the admin ID : ";
			getline(cin, adminID);
		}

		string search_admin_id = "select * from furniture_item where admin_id = '" + adminID + "'";
		const char* searchAdminID = search_admin_id.c_str();
		queryStatus = mysql_query(conn, searchAdminID);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 0) {
				system("cls");
				cout << "\t====================================== Search Results ====================================" << endl;
				cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
				while (row = mysql_fetch_row(res)) {
					cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
				}
				cout << "\t==========================================================================================\n";
				cout << "\nPress any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "\nNo data found. Press any key to try again...";
				_getch();
				searchFurnitures();
			}
		}
	}

	else {
		cout << "Invalid choice. Press any key to try again...";
		_getch();
		searchFurnitures();
	}
}

void updateFurnitures() {

	system("cls");
	int input, choice, confirmation;
	string furnitureID, furnitureName, furniturePrice, furnitureStock;

	queryStatus = mysql_query(conn, "select * from furniture_item");

	res = mysql_store_result(conn);
	cout << "\t====================================== List Of All Furnitures ===========================" << endl;
	cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
	}
	cout << "\t==========================================================================================\n";

	cout << "\nEnter the ID of the furniture that you want to update (enter 0 to go back to the previous page) : ";
	cin >> input;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter the ID of the furniture that you want to update (enter 0 to go back to the previous page) : ";
		cin >> input;
	}
	
	if (input == 0)
		adminMenu();

	else {
		furnitureID = to_string(input);
		string checkFurniture_id = "select furniture_id from furniture_item where furniture_id = '" + furnitureID + "'";
		const char* checkFurnitureID = checkFurniture_id.c_str();
		queryStatus = mysql_query(conn, checkFurnitureID);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 1) {
				cout << "Invalid furniture ID. Press any key to try again...";
				_getch();
				updateFurnitures();
			}
		}

		cout << "\nChoose which details of the furniture that you want to update : " << endl;
		cout << "1. Name" << endl;
		cout << "2. Price" << endl;
		cout << "3. Stock" << endl;
		cout << "Enter your choice : ";
		cin >> choice;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter your choice : ";
			cin >> choice;
		}

		cin.ignore(1, '\n');
		if (choice == 1) {
			cout << "Enter the new furniture name : ";
			getline(cin, furnitureName);
			while (check_number(furnitureName) == true) {
				cout << "\nPlease enter letters only.\n";
				cout << "Enter the new furniture name : ";
				getline(cin, furnitureName);
			}

			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
			while (cin.fail())
			{
				cin.clear(); // clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
			}

			if (confirmation == 0)
				adminMenu();

			else if (confirmation == 1) {
				string update_name = "update furniture_item set furniture_name = '" + furnitureName + "' where furniture_id = '" + furnitureID + "'";
				const char* updateName = update_name.c_str();
				queryStatus = mysql_query(conn, updateName);
				cout << "The update is successful. Press any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "Invalid input. Press any key to try again...";
				_getch();
				updateFurnitures();
			}
		}

		else if (choice == 2) {
			cout << "Enter the new furniture price : ";
			getline(cin, furniturePrice);
			while (check_number(furniturePrice) == false) {
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter the new furniture price : ";
				getline(cin, furniturePrice);
			}

			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
			while (cin.fail())
			{
				cin.clear(); // clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
			}

			if (confirmation == 0)
				adminMenu();

			else if (confirmation == 1) {
				string update_price = "update furniture_item set furniture_price = '" + furniturePrice + "' where furniture_id = '" + furnitureID + "'";
				const char* updatePrice = update_price.c_str();
				queryStatus = mysql_query(conn, updatePrice);
				cout << "The update is successful. Press any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "Invalid input. Press any key to try again...";
				_getch();
				updateFurnitures();
			}
		}

		else if (choice == 3) {
			cout << "Enter the new furniture stock : ";
			getline(cin, furnitureStock);
			while (check_number(furnitureStock) == false) {
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter the new furniture stock : ";
				getline(cin, furnitureStock);
			}

			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
			while (cin.fail())
			{
				cin.clear(); // clear input buffer to restore cin to a usable state
				cin.ignore(INT_MAX, '\n'); // ignore last input
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
			}

			if (confirmation == 0)
				adminMenu();

			else if (confirmation == 1) {
				string update_stock = "update furniture_item set furniture_stock = '" + furnitureStock + "' where furniture_id = '" + furnitureID + "'";
				const char* updateStock = update_stock.c_str();
				queryStatus = mysql_query(conn, updateStock);
				cout << "The update is successful. Press any key to continue...";
				_getch();
				adminMenu();
			}

			else {
				cout << "Invalid input. Press any key to try again...";
				_getch();
				updateFurnitures();
			}
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateFurnitures();
		}
	}
}

void deleteFurnitures() {

	system("cls");
	int input, confirmation;
	string furnitureID, furnitureName, furniturePrice, adminID_add, adminID_delete;

	queryStatus = mysql_query(conn, "select * from furniture_item");

	res = mysql_store_result(conn);
	cout << "\t====================================== List Of All Furnitures ===========================" << endl;
	cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
	}
	cout << "\t==========================================================================================\n";

	cout << "\nEnter the ID of the furniture that you want to delete (enter 0 to go back to the previous page) : ";
	cin >> input;
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter the ID of the furniture that you want to delete (enter 0 to go back to the previous page) : ";
		cin >> input;
	}

	if (input == 0)
		adminMenu();

	else {
		furnitureID = to_string(input);
		string checkFurniture_id = "select furniture_id from furniture_item where furniture_id = '" + furnitureID + "'";
		const char* checkFurnitureID = checkFurniture_id.c_str();
		queryStatus = mysql_query(conn, checkFurnitureID);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count != 1) {
				cout << "Invalid furniture ID. Press any key to try again...";
				_getch();
				updateFurnitures();
			}
		}

		cout << "\nEnter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			adminMenu();

		else if (confirmation == 1) {

			string get_data = "select * from furniture_item where furniture_id = '" + furnitureID + "'";
			const char* getData = get_data.c_str();
			queryStatus = mysql_query(conn, getData);

			if (!queryStatus) {
				res = mysql_store_result(conn);
				row = mysql_fetch_row(res);
				furnitureName = row[1];
				furniturePrice = row[2];
				adminID_add = row[4];
			}

			string insert_to_archive = "insert into Archive (furniture_name, furniture_price, adminID_add, adminID_delete) values ('" + furnitureName + "', '" + furniturePrice + "', '" + adminID_add + "', '" + userID + "')";
			const char* insertToArchive = insert_to_archive.c_str();
			queryStatus = mysql_query(conn, insertToArchive);

			string delete_furniture = "delete from furniture_item where furniture_id = '" + furnitureID + "'";
			const char* deleteFurniture = delete_furniture.c_str();
			queryStatus = mysql_query(conn, deleteFurniture);

			if (!queryStatus) {
				cout << "The furniture has been successfully deleted. Press any key to continue...";
				_getch();
				adminMenu();
			}
		}

		else {
			cout << "Invalid input. Press any key to try again...";
			_getch();
			deleteFurnitures();
		}
	}
}

void viewInventory() {
	system("cls");

	queryStatus = mysql_query(conn, "select * from furniture_item");

	res = mysql_store_result(conn);
	cout << "\t====================================== List Of All Furnitures ===========================" << endl;
	cout << setw(11) << "ID" << setw(30) << "Furniture Name" << setw(20) << "Price" << setw(17) << "Stock" << setw(18) << "Admin ID" << endl;
	while (row = mysql_fetch_row(res)) {
		cout << setw(11) << row[0] << setw(30) << row[1] << setw(16) << "RM " << row[2] << setw(13) << row[3] << setw(17) << row[4] << endl;
	}
	cout << "\t=========================================================================================";

	cout << "\n\nPress any key to continue...";
	_getch();
	adminMenu();
}

void viewSalesReport() {
	
	system("cls");
	string orderDate[1000];
	string orderID[1000];
	string quantity[1000];
	string totalCost[1000];
	string furnitureID[1000];
	string furnitureName[1000];
	string furniturePrice[1000];

	int i = 0;
	double grandTotal = 0;
	int totalQuantity = 0;

	queryStatus = mysql_query(conn, "select order_id, date_format(order_date, '%d/%m/%Y') from orders where MONTH(order_date) = MONTH(CURRENT_DATE()) and YEAR(order_date) = YEAR(CURRENT_DATE())");

	if (!queryStatus) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			orderID[i] = row[0];
			orderDate[i] = row[1];
			i++;
		}
	}

	i = 0;
	do {
		string get_data = "select of_quantity, of_totalCost, furniture_id from order_furniture where order_id = '" + orderID[i] + "'";
		const char* getData = get_data.c_str();
		queryStatus = mysql_query(conn, getData);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			quantity[i] = row[0];
			totalCost[i] = row[1];
			furnitureID[i] = row[2];
			i++;
		}

	} while (orderID[i] != "\0");

	i = 0;
	do {
		string get_furnitureName = "select furniture_name, furniture_price from furniture_item where furniture_id = '" + furnitureID[i] + "'";
		const char* getFurnitureName = get_furnitureName.c_str();
		queryStatus = mysql_query(conn, getFurnitureName);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			furnitureName[i] = row[0];
			furniturePrice[i] = row[1];
			i++;
		}

	} while (furnitureID[i] != "\0");

	i = 0;
	do {
		grandTotal += stod(totalCost[i]);
		i++;
	} while (orderID[i] != "\0");

	i = 0;
	do {
		totalQuantity += stoi(quantity[i]);
		i++;
	} while (orderID[i] != "\0");

	cout << "\t======================================== Monthly Sales Report =======================================" << endl;
	cout << setw(15) << "Date" << setw(11) << "ID" << setw(20) << "Item" << setw(20) << "Price" << setw(17) << "Sold" << setw(23) << "Total cost" << setw(20) << endl;

	i = 0;
	do {
		cout << setw(18) << orderDate[i] << setw(8) << furnitureID[i] << setw(25) << furnitureName[i] << setw(11) << "RM " << furniturePrice[i] << setw(13) << quantity[i] << setw(18) << "RM " << totalCost[i] << endl;
		i++;
	} while (orderID[i] != "\0");

	cout << "\n\tThe total sales for this month is : RM " << grandTotal << endl;
	cout << "\tThe total number of furnitures sold in this month is : " << totalQuantity << endl;
	cout << "\t====================================================================================================\n";

	cout << "\nPress any key to continue...";
	_getch();
	adminMenu();
}

void updateAdminAccount() {
	system("cls");
	string newData, currentPassword;
	int choice, confirmation;

	cout << "======= Update Your Account Information =======" << endl;

	string get_data = "select admin_name, admin_phoneNum, admin_address from admin where admin_id = '" + userID + "'";
	const char* getData = get_data.c_str();
	queryStatus = mysql_query(conn, getData);

	cout << "\n-----------------------------------------------";
	res = mysql_store_result(conn);
	while (row = mysql_fetch_row(res)) {
		cout << "\nName         : " << row[0] << endl;
		cout << "Phone number : " << row[1] << endl;
		cout << "Address      : " << row[2] << endl;
	}
	cout << "-----------------------------------------------" << endl;

	cout << "\n0. Go back to the previous page" << endl;
	cout << "1. Name" << endl;
	cout << "2. Phone number" << endl;
	cout << "3. Address" << endl;
	cout << "4. Password" << endl;
	cout << "Enter your choice : ";
	cin >> choice;
	cin.ignore(1, '\n');
	while (cin.fail())
	{
		cin.clear(); // clear input buffer to restore cin to a usable state
		cin.ignore(INT_MAX, '\n'); // ignore last input
		cout << "\nPlease enter numbers only.\n";
		cout << "Enter your choice : ";
		cin >> choice;
	}

	if (choice == 0)
		adminMenu();

	else if (choice == 1) {
		cin.ignore(1, '\n');
		cout << "Enter the new name : ";
		getline(cin, newData);
		while (check_number(newData) == true) {
			cout << "\nPlease enter letters only.\n";
			cout << "Enter the new name : ";
			getline(cin, newData);
		}

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateAdminAccount();

		else if (confirmation == 1) {
			string update_name = "update admin set admin_name = '" + newData + "' where admin_id = '" + userID + "'";
			const char* updateName = update_name.c_str();
			queryStatus = mysql_query(conn, updateName);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			adminMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateAdminAccount();
		}

	}

	else if (choice == 2) {
		cin.ignore(1, '\n');
		cout << "Enter the new phone number : ";
		getline(cin, newData);
		while (check_number(newData) == false || newData.length() != 10) {

			if (check_number(newData) == false) {
				cout << "\nPlease enter numbers only.\n";
				cout << "Enter the new phone number : ";
				getline(cin, newData);
			}

			else {
				cout << "\nYour phone number must be 10 digits.\n";
				cout << "Enter the new phone number : ";
				getline(cin, newData);
			}
		}

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateAdminAccount();

		else if (confirmation == 1) {
			string update_phoneNum = "update admin set admin_phoneNum = '" + newData + "' where admin_id = '" + userID + "'";
			const char* updatePhoneNum = update_phoneNum.c_str();
			queryStatus = mysql_query(conn, updatePhoneNum);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			adminMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateAdminAccount();
		}
	}

	else if (choice == 3) {
		cin.ignore(1, '\n');
		cout << "Enter the new address : ";
		getline(cin, newData);

		cout << "Enter 0 to cancel or 1 to proceed : ";
		cin >> confirmation;
		while (cin.fail())
		{
			cin.clear(); // clear input buffer to restore cin to a usable state
			cin.ignore(INT_MAX, '\n'); // ignore last input
			cout << "\nPlease enter numbers only.\n";
			cout << "Enter 0 to cancel or 1 to proceed : ";
			cin >> confirmation;
		}

		if (confirmation == 0)
			updateAdminAccount();

		else if (confirmation == 1) {
			string update_address = "update admin set admin_address = '" + newData + "' where admin_id = '" + userID + "'";
			const char* updateAddress = update_address.c_str();
			queryStatus = mysql_query(conn, updateAddress);
			cout << "The update is successful. Press any key to continue...";
			_getch();
			adminMenu();
		}

		else {
			cout << "Invalid choice. Press any key to try again...";
			_getch();
			updateAdminAccount();
		}
	}

	else if (choice == 4) {
		cin.ignore(1, '\n');
		cout << "Enter the current password : ";
		getline(cin, currentPassword);

		string check_password = "select admin_password from admin where admin_id = '" + userID + "' and admin_password = '" + currentPassword + "'";
		const char* checkPassword = check_password.c_str();
		queryStatus = mysql_query(conn, checkPassword);

		if (!queryStatus) {
			res = mysql_store_result(conn);
			if (res->row_count == 1) {
				cout << "Enter the new password : ";
				getline(cin, newData);

				cout << "Enter 0 to cancel or 1 to proceed : ";
				cin >> confirmation;
				while (cin.fail())
				{
					cin.clear(); // clear input buffer to restore cin to a usable state
					cin.ignore(INT_MAX, '\n'); // ignore last input
					cout << "\nPlease enter numbers only.\n";
					cout << "Enter 0 to cancel or 1 to proceed : ";
					cin >> confirmation;
				}

				if (confirmation == 0)
					updateAdminAccount();

				else if (confirmation == 1) {
					string update_password = "update admin set admin_password = '" + newData + "' where admin_id = '" + userID + "'";
					const char* updatePassword = update_password.c_str();
					queryStatus = mysql_query(conn, updatePassword);
					cout << "The update is successful. Press any key to continue...";
					_getch();
					adminMenu();
				}

				else {
					cout << "Invalid choice. Press any key to try again...";
					_getch();
					updateAdminAccount();
				}
			}

			else {
				cout << "Invalid password. Press any key to try again...";
				_getch();
				updateAdminAccount();
			}
		}
	}

	else {
		cout << "Invalid choice. Please enter number 0, 1, 2, 3 or 4 only. Press any key to try again...";
		_getch();
		updateAdminAccount();
	}
}