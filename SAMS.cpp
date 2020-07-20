#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;
class variable
{
    struct student
    {
        char usn[11], name[15], sem[10], dept[15], achie[20], place[10], level[10];
    };
public:
    void add();
    void unpack();
    void modify();
    void search();
    void delete1();
    void setup();
};

void variable::setup()
{
    ofstream out1, out2;
    out1.open("index6.txt", ios::in | ios::trunc);
    out2.open("student6.txt", ios::in | ios::trunc);
    out1.close();
    out2.close();
}

void variable::add()
{
    char buffer[100], temp[50], usn[11], temp1[50], name[15];
    int pos1, flag = 0; student s;
    ifstream out2;
    out2.open("index6.txt", ios::out);
    cout << "\nEnter usn, name, sem, dept: ";
    cin >> s.usn >> s.name >> s.sem >> s.dept;
    cout << "Enter the Student's Achievement Field from: \n=> Academics\n=> Sports\n=> Arts\n=> Writing\n=> Music\n=> Dance\n=> Leadership\n";
    cin >> s.achie;
    cout << "Enter the Place: ";
    cin >> s.place;
    cout << "Enter the Level of Achievement: =>Inter-College\n=>Intra-College\n=>District\n=>State\n=>National\n=>International\n";
    cin >> s.level;
    while (1)
    {
        out2.getline(temp, 50, '$');
        if (out2.eof())
            break;
        sscanf(temp, "%[^|]|%[^|]|%d|$", usn, name, &pos1);
        if (strcmp(s.usn, usn) == 0)
        {
            flag = 1;
            break;
        }
    }
    out2.close();
    if (flag == 1)
        cout << "\nPrimary Key Constraint violation, Record not inserted\n";
    else
    {
        ofstream out1, out2;
        out1.open("student6.txt", ios::app);
        out2.open("index6.txt", ios::app);
        out1.seekp(0, ios::end);
        long pos = out1.tellp();
        sprintf(buffer, "%s|%s|%s|%s|%s|%s|%s|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
        out1 << buffer;
        sprintf(temp1, "%s|%s|%ld|$", s.usn, s.name, pos);
        out2 << temp1;
        out1.close();
        out2.close();
    }
}

void variable::modify()
{
    char temp[100], b[100], usn[11];
    student s;
    ifstream out1, out2;
    out1.open("student6.txt", ios::out);
    out2.open("index6.txt", ios::out);
    int ch;
    cout << "\nEnter usn to be modified: ";
    cin >> usn;
    cout << "\nDatabase: \n";
    fstream of1, of2;
    of1.open("new1.txt",ios::out);
    of2.open("new2.txt",ios::out);
	while (true)
    {
        out1.getline(b, 100, '$');
        sscanf(b, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
        sprintf(b, "%s|%s|%s|%s|%s|%s|%s|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
		if (out1.eof())
		break;
		if (strcmp(s.usn, usn) == 0)
        {
            cout << "\nKey found\n1:Modify Name 2:Modify Sem 3:Modify Dept 4:Modify Achievement 5:Modify Place 6:Modify Level\nEnter your choice: ";
            cin >> ch;
            switch (ch)
            {
            case 1: cout << "\nEnter Name: "; cin >> s.name; break;
            case 2: cout << "\nEnter Sem: "; cin >> s.sem; break;
            case 3: cout << "\nEnter Department: "; cin >> s.dept; break;
            case 4: cout << "\nEnter Achievement: "; cin >> s.achie; break;
            case 5: cout << "\nEnter Place: "; cin >> s.place; break;
            case 6: cout << "\nEnter Level: "; cin >> s.level; break;
            default: break;
            }
            ofstream out1, out2;
            out1.open("student6.txt", ios::in);
            out2.open("index6.txt", ios::in);
            cout << endl << s.usn << " " << s.name << " " << s.sem << " " << s.dept << " " << s.achie << " " << s.place << " " << s.level << endl;
            sprintf(b, "%s|%s|%s|%s|%s|%s|%s|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
            //sprintf(b, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
			//strcat(b, "$");
            of1 << b;
			}
		else{
			of1 << b; 
			//of1.close();
			}
		char usn1[20],name1[20],temp1[20];
		long pos1;
		out2.getline(b, 100, '$');
		sscanf(temp, "%[^|]|%[^|]|%d|$", usn1, name1, pos1);
		sprintf(temp1, "%s|%s|%ld|$", s.usn, s.name, pos1);
		of2<< temp1; 
	}
    out1.close();
    out2.close();
    of1.close();
    of2.close(); 
    remove("index6.txt"); remove("student6.txt");
    rename("new1.txt", "student6.txt");
    rename("new2.txt", "index6.txt");
}

void variable::unpack()
{
    char b[200];
    student s;
    ifstream out1;
    out1.open("student6.txt", ios::out);
    cout << "\nDatabase: \n";
    while (true)
    {
        out1.getline(b, 200, '$');
        sscanf(b, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
        if (out1.eof()) break;
        cout << s.usn << " " << s.name << " " << s.sem << " " << s.dept << " " << s.achie << " " << s.place << " " << s.level << endl;
    } 
    out1.close();
}

void variable::search()
{
    char buffer[100], temp[50], name[15], usn1[11], name1[15];
    int pos, flag = 0; student s;
    cout << "\nEnter Name to be searched: ";
    cin >> name;
    ifstream out2, out1;
    out2.open("index6.txt", ios::out);
    out1.open("student6.txt", ios::out);
    while (1)
    {
        out2.getline(temp, 50, '$');
        if (out2.eof())
            break;
        sscanf(temp, "%[^|]|%[^|]|%d|$", usn1, name1, &pos);
        out1.getline(buffer, 100, '$');
        sscanf(buffer, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|$", s.usn, s.name, s.sem, s.dept, s.achie, s.place, s.level);
        if (strcmp(name, name1) == 0)
        {
            flag = 1;
            cout << s.usn << " " << s.name << " " << s.sem << " " << s.dept << " " << s.achie << " " << s.place << " " << s.level << endl;
        }
    }
    if (flag == 0)
        cout << "\nRecord does not exist";
    out1.close();
    out2.close();
}

void variable::delete1()
{
    char buffer[100], temp[50], name[15], usn1[11], name1[15];
    int pos, flag = 0; student s;
    cout << "\nEnter Name to be Deleted: ";
    cin >> name;
    ifstream in1, in2;
    fstream of1, of2;
    in1.open("index6.txt", ios::out);
    in2.open("student6.txt", ios::out);
    of1.open("index1.txt", ios::out);
    of2.open("stud61.txt", ios::out);
    int tempv = 0;
	while (1)
    { 
        in1.getline(temp, 50, '$');
        if (in1.eof())
            break;
        in2.getline(buffer, 100, '$');
        sscanf(temp, "%[^|]|%[^|]|%d|$", usn1, name1, &pos);
        strcat(buffer, "$");
        strcat(temp, "$");
        int len = strlen(buffer);
        if (strcmp(name, name1) != 0)
        {
            of1 << temp;
            of2 << buffer;
            flag++;
        }
//        if (in1.eof())
//		{
//			break; 
//	}
}
    if (flag!=0)
        cout << "\nRecord Deleted";
    else
        cout << "\nRecord does not exist";
    	in1.close(); in2.close(); of1.close(); of2.close();
   	remove("index6.txt"); remove("student6.txt");
    rename("index1.txt", "index6.txt");                                                                           
    rename("stud61.txt", "student6.txt");                                                                         
}                                                                                                    

int main()
{
    int ch;
    variable v;
    v.setup();
    cout << "\n\n\t       ********************      ";
    cout << "\n\t      *                    *     ";
    cout << "\n\t     *          1           *    ";
    cout << "\n\t    *        WINNER          *   ";
    cout << "\n\t    *                        *   ";
    cout << "\n\t     *                      *    ";
    cout << "\n\t      *                    *     ";
    cout << "\n\t       *                  *      ";
    cout << "\n\t        ******************       ";
    cout << "\n\t              *   *              ";
    cout << "\n\t             *     *             ";
    cout << "\n\t              *   *              ";
    cout << "\n\t              *   *              ";
    cout << "\n\t              *   *              ";
    cout << "\n\t             *     *             ";
    cout << "\n\t           |*********|           ";
    cout << "\n\t           |*********|           ";
    cout << "\n\t           |*********|           ";
    cout << "\n\t  EAST WEST INSTITUTE OF TECHNOLOGY";
    cout << "\n\n\tSTUDENT ACHIEVEMENT MANAGEMENT SYSTEM\t\n";
    for (;;)
    {
        cout << "\n======================================================";
		cout << "\n   1:Add 2:Show 3:Modify 4:Search 5:Delete 6:Exit : ";
		cout << "\n======================================================\n";
        cin >> ch;
        switch (ch)
        {
        case 1: v.add(); break;
        case 2: v.unpack(); break;
        case 3: v.modify(); break;
        case 4: v.search(); break;
        case 5: v.delete1(); break;
        default: exit(0);
        }
    }
}
