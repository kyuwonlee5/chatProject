#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mysql/jdbc.h>
#include <conio.h>
#include <Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;

#define MAX_SIZE 1024

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "1234";

sql::mysql::MySQL_Driver* driver;
sql::Connection* con;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;
sql::Statement* stmt;

SOCKET client_sock;
string nickName;

void beginning() {
	system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < ���� ȭ�� >                   *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1.�α���                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. ID ã��                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               3. PW ã��                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               4. ȸ������                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. ����                         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n"; 
}

void log_in() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < Log In >                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ID �Է�                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> PW �Է�                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void search_ID() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < ���̵� ã�� >                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �̸� �Է�                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ��ȣ �Է�                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �������(8�ڸ�) �Է�         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void search_PW() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < ��й�ȣ ã�� >               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ���̵� �Է�                  *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �̸� �Է�                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ��ȭ��ȣ �Է�                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �������(8�ڸ�) �Է�         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �Ϸ�� ����ȭ��              *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void sign_up() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               <  ȸ�� ����  >                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ���̵� �Է�                  *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ��й�ȣ �Է�                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �̸�, ��ȭ��ȣ �Է�          *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �������(8�ڸ�) �Է�         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> �Ϸ�� ����ȭ��              *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void mainMenu() {
    Sleep(500);
    system("color 06");
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              < ���� ���� : ���� �� >          *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                1. �� ����                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                2. ģ��                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                3. ��ȭ��                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                4. ����                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                0. ����                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void myMenu() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < �� ���� ���� >                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              1. �� ������                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              2. ��� ����/����                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              3. BGM ����/����                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              0. �ڷΰ���                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void friends() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < �� ģ�� ���� >                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. ģ�� ��� ����               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. ģ�� ���� �˻�               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> ���� ~ ���� �˻�             *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. �ڷΰ���                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void chatting() {
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*            < ��ȭ�� ���� / �˻� >             *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. ��ȭ�� ����                  *\n";
    cout << " "; cout << "*           >> /�Ӹ� �Է½� �Ӹ�����            *\n";
    cout << " "; cout << "*           >> /���� �Է½� �Ӹ�����            *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. ä�� ���� �˻�               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               3. ä�� �Ⱓ �˻�               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. �ڷΰ���                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void setting() { // �� ����
    system("cls");
    cout << "\n";
    cout << " "; cout << "*************************************************\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*       *****   *      *      **     *********  *\n";
    cout << " "; cout << "*      *        *      *     *  *        *      *\n";
    cout << " "; cout << "*      *        ********    ******       *      *\n";
    cout << " "; cout << "*      *        *      *   *      *      *      *\n";
    cout << " "; cout << "*       *****   *      *  *        *     *      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               < �� ���� >                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. ��й�ȣ ����                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. ȸ�� Ż��                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. �ڷΰ���                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void textColor(int foreground, int background) {
    int color = foreground + background * 16;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int msg_recv() {
    char buf[MAX_SIZE] = {};
    string msg;

    while (true)
    {
        ZeroMemory(&buf, MAX_SIZE);
        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            textColor(7, 0);
            msg = buf;
            std::stringstream ss(msg); // ���ڿ� ��Ʈ��
            string user;
            ss >> user;
            if (user != nickName) {
                cout << buf << endl;
            }
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

class SQL {
private: 
    string id, pw, name, phone, status, birth, song;
public :
    SQL() {
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }

        con->setSchema("chat");

        // DB �ѱ�����
        stmt = con->createStatement();
        stmt->execute("Set names euckr");
        if (stmt) {
            delete stmt;
            stmt = nullptr;
        }
    }

    int login() {
        cout << " �� �� �� : ";
        cin >> id;
        this->id = id;
        cout << " �� �� �� ȣ : ";
        char ch = ' ';
        while (ch != 13) { // Enter Ű�� ������ �Է�����
            ch = _getch();
            if (ch == 13) break; // Enter Ű�� ������ �Է�����
            else if (ch == 8) {
                if (!pw.empty()) { // �Է¹��ڰ� ������
                    pw.pop_back(); // ���������� ����
                    cout << "\b \b"; // Ŀ�� ��ġ�� �������� �̵����� ������ ����� ��,
                                     // �ٽ� Ŀ�� ��ġ�� ������� �̵���Ŵ
                }
            }
            else {
                pw.push_back(ch);
                cout << '*'; // * �� ��ü
            }
        }
        cout << endl;
        pstmt = con->prepareStatement("SELECT id, pw, name from user WHERE id =?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) { // ������ ����� �ִٸ�, ������� Ž��
            string db_id = result->getString(1); // DB���� ������ ID
            string db_pw = result->getString(2); // DB���� ������ PW

            if (db_id == id && db_pw == pw) {
                name = result->getString(3);
                this->name = name;
                cout << endl << "�� �α��� ���Դϴ�. ��ø� ��ٷ��ּ���." << endl << endl;
                cout << "�� " << name << "�� ȯ���մϴ�!" << endl;
                return 1;
            }
            else {
                cout << "�� �ش��ϴ� ������ �����ϴ�. " << endl;
            }
        }
        else {
            cout << "�� �ش��ϴ� ������ �����ϴ�." << endl;
        }
        pw.clear();
    }

    void searchID() {
        cout << " >> �̸� : ";
        cin >> name;
        cout << " >> ��ȭ��ȣ : ";
        cin >> phone;
        while (true)
        {
            cout << " >> ������� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "�� ��������� 8�ڸ��� �Է����ּ���!!" << endl;
                continue;
            }
            break;
        }
        
        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("SELECT id, name, phone, birth FROM user WHERE phone=?");
        pstmt->setString(1, phone);
        result = pstmt->executeQuery();

        if (result->next()) {
            string db_id = result->getString(1);
            string db_name = result->getString(2);
            string db_phone = result->getString(3);
            string db_birth = result->getString(4);

            if (db_name == name && db_phone == phone && db_birth == DATE) {
                cout << "�� " << name << "���� ���̵� : " << db_id << " �Դϴ�." << endl;
                Sleep(30000);
            }
            else {
                cout << "�� �ش��ϴ� ������ �����ϴ�.";
                Sleep(500);
            }
        }
        else {
            cout << " �� �ش��ϴ� ������ �����ϴ�." << endl;
            Sleep(500);
        }
    }

    void searchPW() {
        cout << " �� �� �� : ";
        cin >> id;
        cout << " �� �� : ";
        cin >> name;
        cout << " �� ȭ �� ȣ : ";
        cin >> phone;   
        while (true)
        {
            cout << " �� �� �� �� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "8�ڸ��� �Է����ּ���.. (- ����)" << endl;
                continue;
            }
            break;
        }

        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("SELECT id, name, phone, birth FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) {
            string db_id = result->getString(1);
            string db_name = result->getString(2);
            string db_phone = result->getString(3);
            string db_birth = result->getString(4);

            if (db_id == id && db_name == name && db_phone == phone && db_birth == DATE) {
                while (1)
                {
                    string new_pw = "";
                    cout << " ���ο� ��й�ȣ�� �Է��ϼ��� : ";
                    char ch = ' ';
                    while (ch != 13) {
                        ch = _getch();
                        if (ch == 13) break; // Enter Ű�� ������ ����
                        if (ch == 8) { // backspace ���
                            if (!new_pw.empty()) { // �Էµ� ���ڰ� �������
                                new_pw.pop_back(); // ������ ���ڸ� ����
                                cout << "\b \b"; // Ŀ�� ��ġ�� �������� �̵����� �������, Ŀ����ġ ������� �ϱ�����
                            }
                        }
                        else {
                            new_pw.push_back(ch);
                            cout << "*"; // ��ǥ�� ��ü
                        }
                    }

                    cout << endl;

                    string renew_pw = "";
                    cout << " �ٽ� �� �� �Է����ּ��� : ";
                    char reCh = ' ';
                    while (reCh != 13) 
                    {
                        reCh = _getch();
                        if (reCh == 13) break; // Enter Ű �Է½� ����
                        if (reCh == 8) {
                            if (!renew_pw.empty()) {
                                renew_pw.pop_back();
                                cout << "\b \b";
                            }
                        }
                        else {
                            renew_pw.push_back(reCh);
                            cout << "*";
                        }
                    }
                    cout << endl;

                    if (new_pw == renew_pw) {
                        pstmt = con->prepareStatement("UPDATE user SET pw = ? WHERE id = ?");
                        pstmt->setString(1, new_pw);
                        pstmt->setString(2, id);
                        pstmt->executeQuery();
                        cout << " �� ���ο� ��й�ȣ�� ����Ǿ����ϴ�." << endl;
                        Sleep(500);
                        break;
                    }
                    else {
                        cout << " �� ��й�ȣ�� �ٸ��ϴ�." << endl;
                        Sleep(500);
                    }

                }
            }
            else {
                cout << " �� �ش��ϴ� ������ �����ϴ�. " << endl;
                Sleep(500);
            }
        }
    }

    void createUser() {
        while (true)
        {
            cout << " �� �� �� : ";
            cin >> id;
            pstmt = con->prepareStatement("SELECT id FROM user WHERE id=?");
            pstmt->setString(1, id);
            result = pstmt->executeQuery();

            if (result->next()) {
                string db_id = result->getString(1);
                if (db_id == id) {
                    cout << " �� �ߺ��� ID�� �ֽ��ϴ�." << endl;
                    continue;
                }
            }
            else {
                cout << " �� �ߺ�üũ �Ϸ�!" << endl;
                break;
            }
        }

        while (true)
        {
            cout << " �� �� �� ȣ : ";
            char ch = ' ';
            while ( ch != 13) 
            {
                ch = _getch();
                if (ch != 13) break;
                if (ch == 8) {
                    if (!pw.empty()) {
                        pw.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    pw.push_back(ch);
                    cout << "*";
                }
            }
            cout << endl;
            string new_pw = "";
            cout << endl << " �� �� �� ȣ ���Է�: ";
            char reCh = ' ';
            while ( reCh != 13) 
            {
                reCh = _getch();
                if (reCh == 13) break;
                if (reCh == 8) {
                    if (!new_pw.empty()) {
                        new_pw.pop_back();
                        cout << "\b \b";
                    }
                }
                else {
                    new_pw.push_back(reCh);
                    cout << "*";
                }
            }
            cout << endl;

            if (pw == new_pw) {
                break;
            }
            else {
                cout << " �� ��й�ȣ�� �ٸ��ϴ�. �ٽ� Ȯ�� ��Ź�帳�ϴ�." << endl;
                pw.clear();
            }
        }

        cout << " �� �� : ";
        cin >> name;
        cout << " �� ȭ �� ȣ : ";
        cin >> phone;
        while (true)
        {
            cout << "�� �� �� �� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << " �� ��������� 8�ڸ��� �Է����ּ���." << endl;
                continue;
            }
            break;
        }

        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("INSERT INTO user(id, pw, name, phone, birth) VALUE(?,?,?,?,?)");
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        pstmt->setString(3, name);
        pstmt->setString(4, phone);
        pstmt->setString(5, DATE);
        pstmt->execute();
        cout << " ȸ���� �ǽŰ� ���ϵ帳�ϴ�!! :D" << endl;
        pw.clear();
        Sleep(500);
    }

    void myProfile() {
        pstmt = con->prepareStatement("SELECT name, status, song, birth, phone FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result->next())
        {
            cout << "************************************************" << endl;
            cout << "�� �� �� : " << result->getString("name") << endl;
            if (result -> getString("status") == "")
            {
                cout << " �� ���¸޼��� : ����" << endl;
            }
            else {
                cout << " �� ���¸޼��� : " << result->getString("status") << endl;
            }

            if (result->getString("song") == "") {
                cout << " �� �� �� : ����" << endl;
            }
            else {
                cout << " �� �� �� : " << result->getString("song") << endl;
            }
            cout << " �� �� �� : " << result->getString("birth") << endl;
            cout << " �� �޴��� ��ȣ : " << result->getString("phone") << endl;
            cout << "************************************************" << endl;
        }
    }

    void updateStatus() {
        cout << " �� ���¸޼��� �� �� : ";
        cin.ignore(); // ǥ���Է� ���ۿ� ���� ���๮�� ����, getline �Լ� �տ� ���
        getline(cin, status);
        pstmt = con->prepareStatement("UPDATE user SET status = ? WHERE id = ?");
        pstmt->setString(1, status);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        cout << " �� ������Ʈ �Ǿ����ϴ�." << endl;
    }

    void updateSong() {
        cout << " �� �� �� �� : ";
        cin.ignore();
        getline(cin, song);
        pstmt = con->prepareStatement("UPDATE user SET song=? WHERE id=?");
        pstmt->setString(1, song);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        cout << " �� ������Ʈ �Ǿ����ϴ�." << endl;
    }

    void friends() {
        pstmt = con->prepareStatement("SELECT name, status, song, birth, phone FROM user WHERE id != ?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result -> next())
        {
            cout << "************************************************" << endl;
            cout << " �� �� �� : " << result->getString("name") << endl;
            if (result->getString("status") == "") {
                cout << " �� ���¸޼��� : ����" << endl;
            }
            else {
                cout << " �� ���¸޼��� : " << result->getString("status") << endl;
            }

            if (result->getString("song") == "") {
                cout << " �� �뷡 : ����" << endl;
            }
            else {
                cout << " �� �뷡 : " << result->getString("song") << endl;
            }

            cout << " �� �� �� �� �� : " << result->getString("birth") << endl;
            cout << " �� �� �� �� �� ȣ : " << result->getString("phone") << endl;
        }
    }

    void searchBirth() {
        string startDay;
        string endDay;
        cout << " ���� || ���� 4�ڸ��� �Է����ּ���. ex) 0101, 0315 ";
        cin >> startDay;
        cout << " �� || ���� 4�ڸ��� �Է����ּ���. ex) 0101,0315 ";
        cin >> endDay;
        pstmt = con->prepareStatement("SELECT name, birth, phone FROM user WHERE DATE_FORMAT(birth, '%m%d') BETWEEN ? AND ? AND id != ?;");
        pstmt->setString(1, startDay);
        pstmt->setString(2, endDay);
        pstmt->setString(3, id);
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " �˻������ �����ϴ�." << endl;
        }
        else {
            while (true)
            {
                cout << "************************************************" << endl;
                cout << " �� �� �� :" << result->getString("name") << endl;
                cout << " �� �� �� �� �� : " << result->getString("birth") << endl;
                cout << " �� �� �� �� �� ȣ : " << result->getString("phone") << endl;
                if (!result->next()) break; // �� �̻� ����� ������ �ݺ��� ����
            }
        }

    }

    void search_content_msg() {
        string content;
        cout << " �������� ��ȭ �˻� : " << endl;
        cin >> content;
        pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting WHERE recv LIKE ?");
        pstmt->setString(1, "%" + content + "%");
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " �˻������ �����ϴ�.." << endl;
        }
        else {
            while (true)
            {
                string chatname = result->getString(1);
                string time = result->getString(2);
                string recv = result->getString(3);
                cout << "************************************************" << endl;
                cout << " �� ���� ��� : " << chatname << " || ���� �ð� : " << time << endl;
                cout << " �� �� �� : " << recv << endl;
                if (!result->next()) break;
            }
        }
    }

    void search_day_msg() {
        string startDay;
        string endDay;
        cout << " ���� || ���� 4�ڸ��� �Է����ּ���. ex) 0101, 0315 ";
        cin >> startDay;
        cout << " �� || ���� 4�ڸ��� �Է����ּ���. ex) 0101,0315 ";
        cin >> endDay;
        
        string startMonthDay = "2023" + startDay;
        string endMonthDay = "2023" + endDay;

        pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting WHERE time BETWEEN ? AND ?");
        pstmt->setString(1, startMonthDay);
        pstmt->setString(2, endMonthDay);
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " �˻������ �����ϴ�." << endl;
        }
        else {
            while (true)
            {
                string chatname = result->getString(1);
                string time = result->getString(2);
                string recv = result->getString(3);
                cout << "************************************************" << endl;
                cout << " �� ���� ��� : " << chatname << " || ���� �ð� : " << time << endl;
                cout << " �� �� �� : " << recv << endl;
                if (!result->next()) break;
            }
        }
    }

    void modifyPW() {
        cout << " ���� ��й�ȣ�� �Է��ϼ��� : ";
        string exist_pw = "";
        char ch = ' ';
        while ( ch != 13)
        {
            ch = _getch();
            if (ch == 13) break;
            if (ch == 8) {
                if (!exist_pw.empty()) {
                    exist_pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                exist_pw.push_back(ch);
                cout << "*";
            }
        }
        cout << endl;

        pstmt = con->prepareStatement("SELECT pw FROM user WHERE id =?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();
        if (result->next()) {
            while (true)
            {
                string new_pw = "";
                cout << " ���ο� ��й�ȣ�� �Է����ּ��� : ";
                char ch = ' ';
                while (ch != 13)
                {
                    ch = _getch();
                    if (ch != 13) break;
                    else if (ch == 8) {
                        if (!new_pw.empty()) {
                            new_pw.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else {
                        new_pw.push_back(ch);
                        cout << "*";
                    }
                }
                cout << endl;

                string renew_pw = "";
                cout << endl << " �ٽ� �ѹ� �Է����ּ��� : ";
                char reCh = ' ';
                while (reCh != 13) {
                    reCh = _getch();
                    if (reCh == 13) break;
                    else if (reCh == 8) {
                        if (!renew_pw.empty()) {
                            renew_pw.pop_back();
                            cout << "\b \b";
                        }
                    }
                    else {
                        renew_pw.push_back(reCh);
                        cout << "*";
                    }
                }

                cout << endl;

                if (new_pw == renew_pw) {
                    pstmt = con->prepareStatement("UPDATE user SET pw=? WHERE id =?");
                    pstmt->setString(1, new_pw);
                    pstmt->setString(2, id);
                    pstmt->executeQuery();
                    cout << " �� ��й�ȣ�� ����Ǿ����ϴ�." << endl;
                    break;
                }
                else {
                    cout << " �� ��й�ȣ�� �ٸ��ϴ�." << endl;
                }
            }
        }
        else {
            cout << " �� ��й�ȣ�� �ٸ��ϴ�." << endl;
        }
    }

    int deleteUser() {
        string exist_pw = "";
        char ch = ' ';
        cout << " ��й�ȣ�� �Է����ּ��� : ";
        while (ch != 13)
        {
            ch = _getch();
            if (ch == 13) break;
            if (ch == 8) {
                if (!exist_pw.empty()) {
                    exist_pw.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                exist_pw.push_back(ch);
                cout << "*";
            }
        }
        cout << endl;

        pstmt = con->prepareStatement("SELECT pw FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) {
            string db_pw = result->getString(1); // DB �� �ִ� pw
            if (db_pw == exist_pw) {
                cout << " ���� �����Ͻðڽ��ϱ�? 1.�� 2.�ƴϿ�"; 
                char check;
                cin >> check;
                if (check == '1') {
                    pstmt = con->prepareStatement("DELETE FROM user WHERE id=?");
                    pstmt->setString(1, id);
                    result = pstmt->executeQuery();
                    cout << " �����Ǿ����ϴ�. �����մϴ�." << endl;
                    return 1;
                }
                else if (check == '2') {
                    cout << "Ź���� �����̽ʴϴ�.!" << endl;
                    return 2;
                }
                else {
                    cout << "�ٽ� �Է����ּ���." << endl;
                }
            }
            else {
                cout << " ��й�ȣ�� �ٸ��ϴ�. �ٽ� �ѹ� Ȯ�����ּ���." << endl;
            }
        }
        else {
            cout << " ��й�ȣ�� �ٸ��ϴ�. �ٽ� �ѹ� Ȯ�����ּ���." << endl;
        }
    }

    string getName() {
        string getName = "";
        pstmt = con->prepareStatement("SELECT name FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) {
            getName = result->getString(1);
        }

        return getName;
    }

    void beforeChat() {
        pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting ORDER BY time DESC LIMIT 5");
        result = pstmt->executeQuery();

        string chatname[5];
        string time[5];
        string recv[5];
        string msg[5];
        int num = 0;
        while (result->next())
        {
            chatname[num] = result->getString(1);
            time[num] = result->getString(2);
            recv[num] = result->getString(3);
            num++;
        }
        for (int i = 4; i >= 0; i--) {
            msg[i] += "************************************************";
            msg[i] += "\n�� ���� ��� : " + chatname[i] + "|| ���� �ð� :  " + time[i] + "\n";
            msg[i] += "�� �� �� : " + recv[i] + "\n";
            msg[i] += "************************************************";
            cout << msg[i] << endl;
       
        }
    }
};

int main() {
    SQL sql;
    bool loginSuccess = false;

    // ����ȭ��
    while (!loginSuccess)
    {
        beginning(); // ����ȭ��
        char start = 0;
        cout << " ��";
        cin >> start;
        switch (start)
        {
            case '1': // �α���
                log_in();
                if (sql.login() == 1) {
                    loginSuccess = true;
                    break;
                }
                continue;

            case '2': // ID ã��
                search_ID();
                sql.searchID();
                continue;

            case '3': // PW ã��
                search_PW();
                sql.searchPW();
                continue;
            
            case '4': // ȸ������
                sign_up();
                sql.createUser();
                continue;

            case '0' : // ����
                return -1;

            default: // 0 ~ 4 �ܿ� �ٸ���ȣ �Է½�
                cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                continue;
        }
    }

    // ����ȭ�� ����
    while (true)
    {
        mainMenu();
        int mainIn = 0;
        cout << "�� ";
        cin >> mainIn;

        // �� ����
        if (mainIn == 1) {
            myMenu();
            bool backButton = false;
            while (!backButton) {
                char information = 0;
                cout << "�� ";
                cin >> information;
                switch (information)
                {
                    case '1':
                        sql.myProfile();
                        break;
                    
                    case '2':
                        sql.updateStatus();
                        continue;

                    case '3':
                        sql.updateSong();
                        continue;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << "�߸��� �Է��Դϴ� �ٽ� �Է����ּ���." << endl;
                        continue;
                }
            }
        }
        else  if (mainIn == 2) {    // ģ�����
            friends();
            bool backButton = false;
            while (!backButton)
            {
                char friendsIn = 0;
                cout << "�� ";
                cin >> friendsIn;
                switch (friendsIn)
                {
                    case '1' :
                        sql.friends(); // ģ�����
                        continue;

                    case '2' :
                        sql.searchBirth(); // ���ϰ˻�
                        continue;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                        continue;
                }
            }
        }
        else if (mainIn == 3) { // ä�ù�
            chatting(); // ģ��ȭ��
            bool backButton = false;
            int code = 0;
            while (!backButton)
            {
                char chattingIn = 0;
                cout << "�� ";
                cin >> chattingIn;
                switch (chattingIn)
                {
                    case '1':
                        sql.beforeChat();
                        WSADATA wsa;
                        code = WSAStartup(MAKEWORD(2, 2), &wsa);    
                        if (!code) {
                            cout << " [ ä�ù濡 �����մϴ�. ]" << endl;
                            nickName = sql.getName();
                            closesocket(client_sock);
                            client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

                            SOCKADDR_IN client_addr = {};
                            client_addr.sin_family = AF_INET;
                            client_addr.sin_port = htons(7777);
                            InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

                            while (1)
                            {
                                if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) {
                                    cout << " �����ǡ� ������ ��Ī�Ͽ� ������ �䱸�� �� ������ �ǽ� �ȴٸ� ��ȭ�� �ߴ����ֽñ� �ٶ��ϴ�." << endl;
                                    send(client_sock, nickName.c_str(), nickName.length(), 0);
                                    break;
                                }
                                cout << "Connecting..." << endl;
                            }
                            std::thread th2(msg_recv);
                            while (true)
                            {
                                string text;
                                getline(cin, text);
                                const char* buffer = text.c_str(); // string -> char *Ÿ������ ��ȯ
                                send(client_sock, buffer, strlen(buffer), 0);
                                if (text == "/����") {
                                    closesocket(client_sock);
                                    backButton = true;
                                    break;
                                }
                            }
                            th2.join();
                        }
                        WSACleanup();
                        break;

                    case '2': 
                        sql.search_content_msg();
                        continue;

                    case '3':
                        sql.search_day_msg();
                        continue;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                        continue;
                }
            }
            
            }
        else if (mainIn == 4) { // ����
            setting();
            bool backButton = false;
            while (!backButton)
            {
                char settinIn = 0;
                cout << "�� ";
                cin >> settingIn;
                switch (settingIn)
                {
                    case '1':   
                        sql.modifyPW(); // ��й�ȣ ����
                        continue;

                    case '2':
                        if (sql.deleteUser() == 1) return -1;
                        else backButton = true;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���. " << endl;
                }
            }
            }
        else if (mainIn == 0) { // ����
                cout << "���α׷��� �����մϴ�. Bye Bye~" << endl;
                return 0;
        }

        else {
            cout << " �߸��� �Է��Դϴ�. �ٽ� �Է����ּ���. " << endl;
        }

    }

    delete result;
    delete pstmt;
    delete stmt;
    delete con;
}