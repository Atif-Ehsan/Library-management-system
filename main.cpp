#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


//  Structures
struct Date{
    int day, month ,year;
};

struct Book{
    char isbn[100],bookName[100], authorName[100],publisherName[100];
    int copies;
    Date doi;
};

struct User{
    int userId;
    char firstName[100], lastName[100] , category[100];
    Date dob;
};

struct issueBooks{
    int userId;
    char isbn[100];
    Date issueDate,returnDate;
};



//Global variables

const int limit = 20;
const int studentLimit = 2;
const int employeeLimit = 3;
Book allBooks[limit];
User allUsers[limit];
issueBooks allIssuedBooks[limit];

int totalBooks = 0;
int totalUsers = 0;
int totalIssuedBooks = 0;

//Functions

void head();
void loadData();
void loadUsers();
void loadIssuedBooks();
void addBook();
void addUser();
bool uniqueISBN(char[]);
void mainmenu();
void searchBook(bool in = false,Book *b = NULL);
void searchUser(bool in = false, User *b = NULL);
void editBook();
void displayBooks(Book[] ,int, bool in = false , Book *b = NULL);
void displayUser(User [], int , bool in = false , User *b = NULL);
void deleteBook();
bool uniqueID(int);
void editUser();
void deleteUser();
void issueBook();
void deleteIssueBook();
bool isIssued(char[]);
bool userHasBook(int);
void saveData();
void saveUser();
void saveIssueBook();
void goBack();



int main()
{
    loadData();
    loadUsers();
    loadIssuedBooks();
    mainmenu();
    return 0;
}

void head(){
    system("cls");

    //system("color F1");
    system("color 5A");
    //system("color A4");
    //system("color B4");
    cout<<'\n'<<'\n'<<'\t'<<" University of Sargodha"<<'\n'<<'\n';
    cout<<'\t'<<" Library Managment System"<<'\n'<<'\n';
    cout<<"  ------------------------------------------------  "<<'\n'<<'\n';

}
void loadData(){
    ifstream file("Books.txt");
    int i = 0;

    while(file){
        file . getline(allBooks[i].isbn, 100,'-');
        file . getline(allBooks[i].bookName, 100,'-');
        file . getline(allBooks[i].authorName, 100,'-');
        file . getline(allBooks[i].publisherName, 100,'-');
        file >> allBooks[i] .copies;
        file >>allBooks[i].doi.day;
        file.ignore();
        file>>allBooks[i].doi.month;
        file.ignore();
        file>>allBooks[i].doi.year;
        file.ignore();
        i++;
    }
    if (i>0){
        totalBooks = i-1;
    }
    else{
        totalBooks = i;
    }
    file.close();
}

void loadUsers(){
    ifstream file("Users.txt");

    int i = 0;

    while(file){
        file>>allUsers[i].userId;
        file . ignore();
        file . getline(allUsers[i].firstName, 100,'-');
        file . getline(allUsers[i].lastName, 100,'-');
        file . getline(allUsers[i].category, 100,'-');
        file >>allUsers[i].dob.day>>allUsers[i].dob.month>>allUsers[i].dob.year;

        i++;
    }
    if(i>0)
        totalUsers = i-1;
    else
        totalUsers = i;

    file.close();
}

void loadIssuedBooks(){

    ifstream file("IssuedBooks.txt");

    int i = 0;

    while(file){
    file>>allIssuedBooks[i].userId;
    file.ignore();
    file.getline(allIssuedBooks[i].isbn,100,'-');
    file>>allIssuedBooks[i].issueDate.day>>allIssuedBooks[i].issueDate.month>>allIssuedBooks[i].issueDate.year;
    file>>allIssuedBooks[i].returnDate.day>>allIssuedBooks[i].returnDate.month>>allIssuedBooks[i].returnDate.year;
    file.ignore();

    i++;
    }
    if(i>0){
        totalIssuedBooks = i-1;
    }
    else{
        totalIssuedBooks=i;
    }

    file.close();
}


void mainmenu(){

    int choice;

        head();

        cout<<'\t' << "(0)  Add new Book (Total # of books = "<<totalBooks<<")"<<'\n';
        cout<<'\t' << "(1)  Edit a Book " <<'\n';
        cout<<'\t' << "(2)  Delete a Book" <<'\n';
        cout<<'\t' << "(3)  Search Book " <<'\n';
        cout<<'\t' << "(4)  Add Library User (Total # of User = "<<totalUsers<<")" <<'\n';
        cout<<'\t' << "(5)  Edit Library User " <<'\n';
        cout<<'\t' << "(6)  Delete Library User " <<'\n';
        cout<<'\t' << "(7)  Search Library User " <<'\n';
        cout<<'\t' << "(8)  Issue Book (Total numbers of Issued Books = "<<totalIssuedBooks<<")" <<'\n';
        cout<<'\t' << "(9)  Delete Issued Books " <<'\n';
        cout<< "\tEnter -1 to exit"<<endl;
        cout<<endl<<endl;


        cout<< "What do you want to do"<<endl;
        cout<<'\n'<<"=";
        if (cin>>choice){
            switch(choice){
            case 0 :
                addBook();
                break;
            case 1 :
                editBook();
                break;
            case 2 :
                deleteBook();
                break;
            case 3 :
                searchBook();
                break;
            case 4 :
                addUser();
                break;
            case 5 :
                editUser();
                break;
            case 6 :
                deleteUser();
                break;
            case 7 :
                searchUser();
                break;
            case 8 :
                issueBook();
                break;
            case 9 :
                deleteIssueBook();
                break;
            }
        }
        else{
            saveData();
            saveUser();
            saveIssueBook();
        }
    saveData();
    saveUser();
    saveIssueBook();
}


void addBook(){
    head();
    if (totalBooks >= limit){
        cout<<"New Book can not be added because limit is already filled";
        goBack();
    }
    Book temp;
    cout<<"Enter ISBN : ";
    cin.ignore();
    cin.getline(temp.isbn,100,'\n');
    cout<<"Enter Book Name : ";
    cin.getline(temp.bookName, 100,'\n');
    cout<<"Enter Author Name : ";
    cin.getline(temp.authorName,100,'\n');
    cout<<"Enter publisher name : ";
    cin.getline(temp.publisherName,100, '\n');
    cout<<"Enter number of copies : ";
    cin>>(temp.copies);
    cout<<"Enter Date of Issue : ";
    cin>>temp.doi.day>>temp.doi.month>>temp.doi.year;
    //cin.ignore();
    //cin>>temp.doi.month;
    //cin.ignore();
    //cin>>temp.doi.year;
    cout<<'\n'<<'\n';

    char ch;

    cout<<"Enter y or Y to add New book or any other key to terminate : ";

    cin>>ch;

    cout<<'\n'<<'\n';
    head();

    if (ch != 'y' && ch != 'Y'){
        cout<<" The process is terminated "<<'\n';
        return;

    }

    if(uniqueISBN(temp.isbn)){
        allBooks[totalBooks] = temp;
        ++totalBooks;

        cout<<"The Book is added : "<<'\n';

    }
    else{
        cout<<" The ISBN number is not unique ";
    }
    saveData();
    goBack();
}

bool uniqueISBN(char str[]){
        bool is_unique = true;
        for (int i=0; i<totalBooks; i++){
            if (strcmp(str,allBooks[i].isbn)==0){
                is_unique = false;
                break;
            }
        }
        return is_unique;

}

void searchBook(bool in , Book *b){
    head();
    cout<< "(0)  Search by ISBN " <<'\n';
    cout<< "(1)  Search by Book Name " <<'\n';
    cout<< "(2)  Search by Author Name " <<'\n';
    cout<< "(3)  Search by Publisher Name " <<'\n';
    cout<< "(4)  Search by Issue Date " <<'\n';

    int value;

    cout<< "=";
    cin>>value;

    int total =0;
    Book searchBook[limit];

    head();

    char input[100];

    if (value == 0){
        cout<<"Enter the ISBN of Book : ";
        cin>>input;

        for (int i=0 ; i<totalBooks ; i++){
            if (strcmp(allBooks[i].isbn, input)==0){
                searchBook[total] = allBooks[i];
                total++;
            }
        }
    }
    else if(value==1){
        cout<<"Enter the Name of Book : ";
        cin>>input;

        for (int i=0 ; i<totalBooks ; i++){
            if (strcmp(allBooks[i].bookName, input)==0){
                searchBook[total] = allBooks[i];
                total++;
            }
        }
    }
    else if(value==2){
        cout<<"Enter the Author Name of Book : ";
        cin>>input;

        for (int i=0 ; i<totalBooks ; i++){
            if (strcmp(allBooks[i].authorName, input)==0){
                searchBook[total] = allBooks[i];
                total++;
            }
        }
    }
    else if(value==3){
        cout<<"Enter the Publisher Name of Book : ";
        cin>>input;

        for (int i=0 ; i<totalBooks ; i++){
            if (strcmp(allBooks[i].publisherName, input)==0){
                searchBook[total] = allBooks[i];
                total++;
            }
        }
    }
    else if(value==4){
        int year;
        cout<<"Enter the Issue year of Book : ";

        cin>>year;

        for (int i=0 ; i<totalBooks ; i++){
            if (allBooks[i].doi.year == year){
                searchBook[total] = allBooks[i];
                total++;
            }
        }
    }
    displayBooks(searchBook,total,in,b );

}

void displayBooks(Book b[] , int t , bool in , Book *bk){
    head();


    for (int i = 0 ; i<t ; i++){

        cout<< "\t  Book No : "<<i+1<<endl;
        cout<< "Book Index : "<<i<<endl;
        cout<< "ISBN number is : \t "<<b[i].isbn<<endl;
        cout<< "Book Name is :\t\t"<<b[i].bookName<<endl;
        cout<< "Author Name is : \t"<<b[i].authorName<<endl;
        cout<< "Publisher Name is : \t"<<b[i].publisherName<<endl;
        cout<< "Date of Issue is : \t"<<b[i].doi.day<<"/"<<b[i].doi.month<<"/"<<b[i].doi.year<<endl;
        cout<<endl;
    }
    int inp;
    if (in){
        cout<<"Enter the index of the book : ";
        cin>>inp;
        //if(inp>=t ){
          //  strcpy(bk->isbn,"-1");
          //  return;
        //}
       // else
        *bk = b[inp];
    }
    else{
        goBack();
        //cout<<endl<<endl;
        //system("pause");
    }

}

void editBook(){

    Book temp;
    searchBook(true , &temp);
    system("cls");

    head();

    cout<< "\t Book's Old Details "<<endl<<endl;

    char oldisbn[100];

    strcpy(oldisbn,temp.isbn);

    cout<< "ISBN is : " << temp.isbn << endl;
    cout<< "Book Name is : " <<temp.bookName <<endl;
    cout<< "Author Name is : " <<temp.authorName<<endl;
    cout<< "Publisher Name is : " <<temp.publisherName<<endl;
    cout<< "Numbers of copies are : " <<temp.copies<<endl;
    cout<< "Date of Issue is : "<< temp.doi.day<< "/" <<temp.doi.month<< "/" <<temp.doi.year<<endl;

    if (isIssued(temp.isbn)){
        cout<< "The Book is issued so it can not be editid!!"<<endl;
        goBack();
        return;
    }
    cout<<endl<<endl;

    cout<< "\t Book's New Details are : " <<endl<<endl;

    cout<< "ISBN is : " ;
    cin>>temp.isbn;
    cout<< "Book Name is : ";
    cin>>temp.bookName;
    cout<< "Author Name is : " ;
    cin>>temp.authorName;
    cout<< "Publisher Name is : ";
    cin>>temp.publisherName;
    cout<< "Number of copies are : ";
    cin>>temp.copies;
    cout<< "Date of Issue is : ";
    cin>>temp.doi.day>>temp.doi.month>>temp.doi.year;

    cout<<endl<<endl;

    cout<< "Press y or Y to update the data and any other key to cancel : ";
    char choice;

    cin>>choice;

    head();

    if (choice == 'y' || choice == 'Y'){
        if(!(strcmp(oldisbn, temp.isbn)==0)){
            if(!uniqueISBN(temp.isbn)){
                cout<< " ISBN is not unique ";
                return;
            }
        }
        for (int i =0 ; i<totalBooks ; i++){
            if(strcmp(oldisbn,allBooks[i].isbn)==0){
               allBooks[i] = temp;
                cout<< " Book record Update ";
                break;
               }
            }
        }

        else{
            cout<< " Book Update Cancelled ";
        }
        goBack();
}

void deleteBook() {
	Book temp;
	searchBook(true,&temp);
	head();

	cout << " Book Details " << endl << endl;

	cout << " ISBN : ";
	cout << temp.isbn << endl;
	cout << " Name : ";
	cout << temp.bookName << endl;
	cout << " Author : ";
	cout << temp.authorName << endl;
	cout << " Publisher : ";
	cout << temp.publisherName << endl;
	cout << " Copies : ";
	cout << temp.copies << endl;
	cout << " DOI : ";
	cout << temp.doi.day << '/' << temp.doi.month << '/' << temp.doi.year << endl;

	cout << endl << endl;
     if (isIssued(temp.isbn)){
        cout<< "The Book is issued so it can not be deleted"<<endl;
        goBack();
        return;
    }
	cout << " Do You want To Delete Book ( y Or Y for yes any other key to cancel) ";

	char choice;

	cin >> choice;

	head();

	if (choice == 'y' || choice == 'Y') {
		for (int i = 0; i < totalBooks; ++i) {
			if (strcmp(temp.isbn,allBooks[i].isbn)==0) {
				strcpy(allBooks[i].isbn,"-1");
				saveData();
				loadData();
				cout << "The Book is Removed.";
				break;
			}
		}
	}
	else {
		cout << " Book Delete Cancelled ";
	}
	goBack();
}


void addUser(){
    head();


    if (totalUsers >= limit){
        cout<<"New User can not be added because limit is already filled";
        goBack();
    }
    User temp;

    cout<<"Enter User ID : ";
    cin>>temp.userId;
    cout<<"Enter First Name : ";
    cin.ignore();
    cin.getline(temp.firstName, 100,'\n');
    cout<<"Enter Last Name : ";
    cin.getline(temp.lastName,100,'\n');
    cout<<"Enter category : ";
    cin.getline(temp.category,100, '\n');
    cout<<"Enter Date of Birth : ";
    cin>>temp.dob.day>>temp.dob.month>>temp.dob.year;
    cout<<'\n'<<'\n';

    char ch;

    cout<<"Enter y or Y to add User or any other key to terminate : ";

    cin>>ch;

    cout<<'\n'<<'\n'<<'\n';
    head();

    if (ch != 'y' && ch != 'Y'){
        cout<<" The process is terminated "<<'\n';
        return;

    }

    if(uniqueID(temp.userId)){
        allUsers[totalUsers] = temp;
        totalUsers++;

        cout<<"The User is added : ";

    }
    else{
        cout<<" The User ID is not unique ";
    }
    saveUser();
    goBack();
}


bool uniqueID(int id){
    bool is_unique = true;
        for (int i=0; i<totalUsers; i++){
            if (allUsers[i].userId==id){
                is_unique = false;
                break;
            }
        }
        return is_unique;

}

void searchUser(bool in , User *b){

    head();

    cout<< "(0)  Search by ID " <<'\n';
    cout<< "(1)  Search by first Name " <<'\n';
    cout<< "(2)  Search by Last Name " <<'\n';
    cout<< "(3)  Search by category " <<'\n';

    int choice;

    cout<<endl;
    cout<<" = ";

    cin>>choice;

    int total = 0;

    User searchUsers[limit];

    head();

    char input[100];

    if (choice == 0){
        int inp;
        cout<<" Enter ID : ";
        cin>>inp;
        for(int i =0 ; i<totalUsers ; i++){
            if(allUsers[i].userId==inp){
                searchUsers[total]=allUsers[i];
                total++;
            }
        }
    }
    else if(choice == 1){
        cout<< "Enter First Name : ";
        cin>>input;
        for(int i = 0 ; i<totalUsers ; i++){
            if(strcmp(allUsers[i].firstName,input)==0){
                searchUsers[total] = allUsers[i];
                total++;
            }
        }
    }
     else if(choice == 2){
        cout<< "Enter Last Name : ";
        cin>>input;
        for(int i = 0 ; i<totalUsers ; i++){
            if(strcmp(allUsers[i].lastName,input)==0){
                searchUsers[total] = allUsers[i];
                total++;
            }
        }
    }
     else if(choice == 3){
        cout<< "Enter category : ";
        cin>>input;
        for(int i = 0 ; i<totalUsers ; i++){
            if(strcmp(allUsers[i].category,input)==0){
                searchUsers[total] = allUsers[i];
                total++;
            }
        }
    }
    displayUser(searchUsers , total , in , b);

}

void displayUser(User b[] , int t , bool in , User *bk){
    head();

    for(int i =0 ; i<t ; i++){
        cout<< "\t   User No : "<<i+1<<endl<<endl;
        cout<< " User Index : "<<i<<endl;
        cout<< " User ID is : " <<b[i].userId<<endl;
        cout<< " User's First Name is : " <<b[i].firstName<<endl;
        cout<< " User's Last Name is : " <<b[i].lastName<<endl;
        cout<< " User's category is : " <<b[i].category<<endl;
        cout<< " User's date of Birth is : "<<b[i].dob.day<<"/"
        <<b[i].dob.month<<"/"<<b[i].dob.year<<endl<<endl;

    }
    int inp;

    if(in){
        cout<< "Enter the Index number of the User :" ;
        cin>>inp;


        if(inp>=t){
            bk->userId = -1;
            return;
        }
        else
            *bk = b[inp];
    }
    else{
        goBack();
    }

}

void editUser(){
    User temp;
    searchUser(true , &temp);

    head();

    int oldId = temp.userId;

    cout<< " Enter Old details of users " <<endl<<endl;

    cout<< " ID is : " <<temp.userId<<endl;
    cout<< " User's First Name is : " <<temp.firstName<<endl;
    cout<< " User's Last Name is : " <<temp.lastName<<endl;
    cout<< " User's category is : " <<temp.category<<endl;
    cout<< " User's date of birth is : " <<temp.dob.day<<"/"<<temp.dob.month
    << "/" << temp.dob.year<<endl;

    if (userHasBook(temp.userId)){
        cout<< "User has a book issued so can not be edited!!";
        goBack();
        return;
    }
    cout<<endl<<endl;

    cout<< "Enter User's New details ";

    cout<<endl<<endl;

    cout<< "Enter ID : ";
    cin>>temp.userId;
    cout<< "Enter First Name : ";
    cin>>temp.firstName;
    cout<< "Enter Last Name : ";
    cin>>temp.lastName;
    cout<< "Enter Category : ";
    cin>>temp.category;
    cout<< "Enter Date of Birth : ";
    cin>>temp.dob.day>>temp.dob.month>>temp.dob.year;

    head();


    cout<< "Enter y or Y to update data and any other key to cancel : ";

    char choice;
    cin>>choice;
    head();

    if(choice == 'y' || choice == 'Y'){
        if(!(oldId==temp.userId)){
            if(!(uniqueID(temp.userId))){
                cout<< "User ID is not unique";
                return;
           }
        }
        for(int i = 0 ; i<totalUsers ; i++){
           if (oldId == allUsers[i].userId){
                allUsers[i] = temp;
                cout<< "Book record Updated";
                break;
           }
        }
    }
    else{
        cout<< "User update cancelled ";
    }
    goBack();

}

void deleteUser(){

    User temp;
    searchUser(true , &temp);
    head();

    cout<< "\t Book Details "<<endl<<endl;


    cout<< "User's ID Number is : " << temp.userId<< endl;
    cout<< "User's First Name is : " <<temp.firstName <<endl;
    cout<< "User's Last Name is : " <<temp.lastName<<endl;
    cout<< "User's category is : " <<temp.category<<endl;
    cout<< "User's Date of Birth is : "<< temp.dob.day<< "/" <<temp.dob.month<< "/" <<temp.dob.year<<endl;
    cout<<endl<<endl;

    if (userHasBook(temp.userId)){
        cout<< "The User has a book issued so cannot be deleted!!";
        goBack();
        return;
    }
    cout<< "Press y or Y to delete the User and any other key to cancel : ";
    char choice;

    cin>>choice;
    head();
    if (choice == 'y' || choice == 'Y'){
        for (int i = 0 ; i<totalBooks ; i++){
            if(allUsers[i].userId==temp.userId){
                allUsers[i].userId = -1;
                saveUser();
                loadUsers();
				cout << "The User is Removed.";
				break;
            }
        }
    }
    else{
        cout<< " User Delete cancelled ";
    }
    goBack();

}

void issueBook(){

    Book btemp;
    User utemp;

    head();
    cout<< "\t Book Details "<<endl<<endl;

    cout<< " Search the book you want to issue "<<endl;

    system("pause");

    searchBook(true , &btemp);

    head();


    cout<< "Book Details" <<endl <<endl;

    cout<< "Book ISBN is : ";
    cout<<btemp.isbn<<endl;
    cout<< "Book Name is : ";
    cout<<btemp.bookName<<endl;
    cout<< "Book's Author Name is : ";
    cout<<btemp.authorName<<endl;
    cout<< "Book's Publisher Name is : ";
    cout<< btemp.publisherName<<endl;
    cout<< "Book's Date of Issue is : ";
    cout<<btemp.doi.day<<'/'<<btemp.doi.month<<'/'<<btemp.doi.year<<endl;

    cout<<endl<<endl;

    if (isIssued(btemp.isbn)){
        cout<< "The Book has already been issued to someone so can not be issued again ";
        goBack();
        return;
    }
    cout<< "Search the User you want to Issue the Book" <<endl;
    cout<< ' ';
    system("pause");

    searchUser(true ,&utemp);

    head();
    cout<< "Book Details" <<endl <<endl;

    cout<< "Book ISBN is : ";
    cout<<btemp.isbn<<endl;
    cout<< "Book Name is : ";
    cout<<btemp.bookName<<endl;
    cout<< "Book's Author Name is : ";
    cout<<btemp.authorName<<endl;
    cout<< "Book's Publisher Name is : ";
    cout<< btemp.publisherName<<endl;
    cout<< "Book's Date of Issue is : ";
    cout<<btemp.doi.day<<'/'<<btemp.doi.month<<'/'<<btemp.doi.year<<endl;

    cout<<endl<<endl;


    cout<< " User Details " <<endl<<endl;

    cout<< "User ID is : " ;
    cout<< utemp.userId<<endl;
    cout<< "User's First Name is : ";
    cout<< utemp.firstName<<endl;
    cout<< "User's Last Name is : ";
    cout<< utemp.lastName<<endl;
    cout<< "User's category is : ";
    cout<< utemp.category<<endl;
    cout<< "User's Date of Birth is : ";
    cout<< utemp.dob.day<<utemp.dob.month<<utemp.dob.year<<endl;

    issueBooks itemp;

    itemp.userId = utemp.userId;
    strcpy(itemp.isbn,btemp.isbn);

    cout<< "Do you want to issue the following book : ";
    char ch;

    cin>>ch;

    if(ch == 'y' || ch == 'Y'){
        Date dIssue, dReturn;
        cout<< "Enter Date of Issue : ";
        cin>>dIssue.day>>dIssue.month>>dIssue.year;
        cout<<endl;
        //cout<< "Enter Return Date : " ;
        //cin>>dReturn.day>>dReturn.month>>dReturn.year;
        if(strcmp(utemp.category , "student")==0){
            dReturn.month = dIssue.month + studentLimit;
        }
        else{
            dReturn.month = dIssue.month+employeeLimit;
        }
        dReturn.day= dIssue.day;
        dReturn.year = dIssue.year;
        if(dReturn.month > 12){
            ++dReturn.year;
            //dReturn.month = dIssue.month - 10;
            dReturn.month = dReturn.month - 12;
        }
        cout<< "Return Date is : " ;
        cout<<dReturn.day<<"/"<<dReturn.month<<"/"<<dReturn.year;
        cout<<endl<<endl;

        itemp.issueDate = dIssue;
        itemp.returnDate = dReturn;

        allIssuedBooks[totalIssuedBooks]=itemp;
        ++totalIssuedBooks;
        cout<< "The Book has been Issued "<<endl;

    }
    else{
        cout<< "The Book has not been Issued"<<endl;
    }
    saveIssueBook();
    goBack();

}

void deleteIssueBook(){
    head();
    int userId;
    cout<<"Enter User ID : ";
    cin>>userId;

    cout<< "Book issued to user with user ID : "<<userId<<endl<<endl;
    issueBooks *temp[limit];
    int total = 0;
    for (int i = 0 ; i<totalBooks ; i++){
        if(allIssuedBooks[i].userId!=userId) continue;
        cout<< "ISBN of book is : "<<allIssuedBooks[i].isbn<<endl;
        cout<< "Issue date of book is : " <<allIssuedBooks[i].issueDate.day<<'/'
        <<allIssuedBooks[i].issueDate.month<<'/'<<allIssuedBooks[i].issueDate.year<<endl;
        cout<< "Return date of book is : " <<allIssuedBooks[i].returnDate.day<< '/'
        <<allIssuedBooks[i].returnDate.month<<'/'<<allIssuedBooks[i].returnDate.year<<endl;
        cout<<endl<<endl;
        temp[total] = &allIssuedBooks[i];
        ++total;
    }
    cout<<endl<<endl;

    int index;
    cout<< "Enter the Index you want to delete : ";
    cin>>index;

    if(index<total){
        strcpy(temp[index]->isbn,"-1");
        saveIssueBook();
        loadIssuedBooks();
        cout<< "The Issued Book has been deleted";

    }
    else{
        cout<< "The Entered Index is not in range";
    }
    goBack();

}

bool isIssued(char isbn[]){
    for (int i= 0 ; i<totalBooks ; i++){
        if(strcmp(allIssuedBooks[i].isbn,isbn)==0)
            return true;
    }
    return false;
}

bool userHasBook(int id){
    for (int i= 0 ; i<totalUsers ; i++){
        if(allIssuedBooks[i].userId==id)
            return true;
    }
    return false;
}

void saveData(){
    ofstream file("Books.txt");

    for(int i = 0 ; i<totalBooks ; i++){
    if(strcmp(allBooks[i].isbn, "-1")==0) continue;
    file<<allBooks[i].isbn<< "-" <<allBooks[i].bookName<< "-" <<allBooks[i].authorName<< "-"
    <<allBooks[i].publisherName<< "-" <<allBooks[i].copies<< " " ;
    file<<allBooks[i].doi.day<<'/'<<allBooks[i].doi.month<<'/'<<allBooks[i].doi.year << endl;
    }
    file.close();
}

void saveUser() {
	ofstream file("Users.txt");

	for (int i = 0; i < totalUsers; ++i){
        if (allUsers[i].userId == -1) continue;
		file << allUsers[i].userId <<' '<< allUsers[i].firstName << "-"
		<< allUsers[i].lastName << "-" << allUsers[i].category << "-"
		<< allUsers[i].dob.day <<" "<< allUsers[i].dob.month << " " << allUsers[i].dob.year << endl;
	}

	file.close();
}

void saveIssueBook(){
    ofstream file("IssuedBooks.txt");

    for(int i= 0 ; i<totalIssuedBooks ; i++){
        if(strcmp(allIssuedBooks[i].isbn, "-1")==0) continue;
        file<<allIssuedBooks[i].userId<< ' ' <<allIssuedBooks[i].isbn<< '-'
        <<allIssuedBooks[i].issueDate.day<< ' ' <<allIssuedBooks[i].issueDate.month<< ' '
        <<allIssuedBooks[i].issueDate.year<< ' ' <<allIssuedBooks[i].returnDate.day<< ' '
        <<allIssuedBooks[i].returnDate.month << ' ' <<allIssuedBooks[i].returnDate.year<<endl;
    }
    file.close();
}

void goBack()
{
    char x;
    while(1)
    {
        cout<<"\nDo you want to go back to Main Menu \n";
        cout<<"\tPress y or Y to go back and any other key to cancel: ";
        cin>>x;
        x=toupper(x);
        //if (x=='Y' || x=='N')
        break;
        //cout<<"\n\t*{Invalid Input Only press Y or N}*\n";
    }
    if (x=='Y'||x=='y')
        mainmenu();
    else
        exit(0);
}
