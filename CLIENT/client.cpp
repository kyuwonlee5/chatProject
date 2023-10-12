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

int msg_rect() {
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

    }

};