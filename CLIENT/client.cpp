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
    cout << " "; cout << "*               < 시작 화면 >                   *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1.로그인                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. ID 찾기                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               3. PW 찾기                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               4. 회원가입                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. 종료                         *\n";
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
    cout << " "; cout << "*               >> ID 입력                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> PW 입력                      *\n";
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
    cout << " "; cout << "*               < 아이디 찾기 >                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 이름 입력                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 번호 입력                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 생년월일(8자리) 입력         *\n";
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
    cout << " "; cout << "*               < 비밀번호 찾기 >               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 아이디 입력                  *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 이름 입력                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 전화번호 입력                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 생년월일(8자리) 입력         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 완료시 메인화면              *\n";
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
    cout << " "; cout << "*               <  회원 가입  >                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 아이디 입력                  *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 비밀번호 입력                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 이름, 전화번호 입력          *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 생년월일(8자리) 입력         *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 완료시 메인화면              *\n";
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
    cout << " "; cout << "*              < 현재 상태 : 접속 중 >          *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                1. 내 정보                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                2. 친구                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                3. 대화방                      *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                4. 설정                        *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                0. 종료                        *\n";
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
    cout << " "; cout << "*               < 내 정보 보기 >                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              1. 내 프로필                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              2. 상메 설정/수정                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              3. BGM 설정/수정                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*              0. 뒤로가기                      *\n";
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
    cout << " "; cout << "*               < 내 친구 정보 >                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. 친구 목록 보기               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. 친구 생일 검색               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               >> 월일 ~ 월일 검색             *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. 뒤로가기                     *\n";
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
    cout << " "; cout << "*            < 대화방 입장 / 검색 >             *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. 대화방 입장                  *\n";
    cout << " "; cout << "*           >> /귓말 입력시 귓말가능            *\n";
    cout << " "; cout << "*           >> /종료 입력시 귓말종료            *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. 채팅 내용 검색               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               3. 채팅 기간 검색               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. 뒤로가기                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void setting() { // 내 설정
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
    cout << " "; cout << "*               < 내 설정 >                     *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               1. 비밀번호 변경                *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               2. 회원 탈퇴                    *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*               0. 뒤로가기                     *\n";
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
            std::stringstream ss(msg); // 문자열 스트림
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

        // DB 한글저장
        stmt = con->createStatement();
        stmt->execute("Set names euckr");
        if (stmt) {
            delete stmt;
            stmt = nullptr;
        }
    }

    int login() {
        cout << " 아 이 디 : ";
        cin >> id;
        this->id = id;
        cout << " 비 밀 번 호 : ";
        char ch = ' ';
        while (ch != 13) { // Enter 키를 누르면 입력종료
            ch = _getch();
            if (ch == 13) break; // Enter 키를 누르면 입력종료
            else if (ch == 8) {
                if (!pw.empty()) { // 입력문자가 있으면
                    pw.pop_back(); // 마지막문자 삭제
                    cout << "\b \b"; // 커서 위치를 왼쪽으로 이동시켜 공백을 출력한 뒤,
                                     // 다시 커서 위치를 원래대로 이동시킴
                }
            }
            else {
                pw.push_back(ch);
                cout << '*'; // * 로 대체
            }
        }
        cout << endl;
        pstmt = con->prepareStatement("SELECT id, pw, name from user WHERE id =?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) { // 쿼리의 결과가 있다면, 질문결과 탐색
            string db_id = result->getString(1); // DB에서 가져온 ID
            string db_pw = result->getString(2); // DB에서 가져온 PW

            if (db_id == id && db_pw == pw) {
                name = result->getString(3);
                this->name = name;
                cout << endl << "▶ 로그인 중입니다. 잠시만 기다려주세요." << endl << endl;
                cout << "▶ " << name << "님 환영합니다!" << endl;
                return 1;
            }
            else {
                cout << "▶ 해당하는 정보가 없습니다. " << endl;
            }
        }
        else {
            cout << "▶ 해당하는 정보가 없습니다." << endl;
        }
        pw.clear();
    }

    void searchID() {
        cout << " >> 이름 : ";
        cin >> name;
        cout << " >> 전화번호 : ";
        cin >> phone;
        while (true)
        {
            cout << " >> 생년월일 : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "▶ 생년월일을 8자리로 입력해주세요!!" << endl;
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
                cout << "▶ " << name << "님의 아이디 : " << db_id << " 입니다." << endl;
                Sleep(30000);
            }
            else {
                cout << "▶ 해당하는 정보가 없습니다.";
                Sleep(500);
            }
        }
        else {
            cout << " ▶ 해당하는 정보가 없습니다." << endl;
            Sleep(500);
        }
    }

    void searchPW() {
        cout << " 아 이 디 : ";
        cin >> id;
        cout << " 이 름 : ";
        cin >> name;
        cout << " 전 화 번 호 : ";
        cin >> phone;   
        while (true)
        {
            cout << " 생 년 월 일 : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "8자리로 입력해주세요.. (- 제외)" << endl;
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
                    cout << " 새로운 비밀번호를 입력하세요 : ";
                    char ch = ' ';
                    while (ch != 13) {
                        ch = _getch();
                        if (ch == 13) break; // Enter 키를 누르면 종료
                        if (ch == 8) { // backspace 경우
                            if (!new_pw.empty()) { // 입력된 문자가 있을경우
                                new_pw.pop_back(); // 마지막 문자를 삭제
                                cout << "\b \b"; // 커서 위치를 왼쪽으로 이동시켜 공백출력, 커서위치 원래대로 하기위함
                            }
                        }
                        else {
                            new_pw.push_back(ch);
                            cout << "*"; // 별표로 대체
                        }
                    }

                    cout << endl;

                    string renew_pw = "";
                    cout << " 다시 한 번 입력해주세요 : ";
                    char reCh = ' ';
                    while (reCh != 13) 
                    {
                        reCh = _getch();
                        if (reCh == 13) break; // Enter 키 입력시 종료
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
                        cout << " ▶ 새로운 비밀번호로 변경되었습니다." << endl;
                        Sleep(500);
                        break;
                    }
                    else {
                        cout << " ▶ 비밀번호가 다릅니다." << endl;
                        Sleep(500);
                    }

                }
            }
            else {
                cout << " ▶ 해당하는 정보가 없습니다. " << endl;
                Sleep(500);
            }
        }
    }

    void createUser() {
        while (true)
        {
            cout << " 아 이 디 : ";
            cin >> id;
            pstmt = con->prepareStatement("SELECT id FROM user WHERE id=?");
            pstmt->setString(1, id);
            result = pstmt->executeQuery();

            if (result->next()) {
                string db_id = result->getString(1);
                if (db_id == id) {
                    cout << " ▶ 중복된 ID가 있습니다." << endl;
                    continue;
                }
            }
            else {
                cout << " ▶ 중복체크 완료!" << endl;
                break;
            }
        }

        while (true)
        {
            cout << " 비 밀 번 호 : ";
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
            cout << endl << " 비 밀 번 호 재입력: ";
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
                cout << " ▶ 비밀번호가 다릅니다. 다시 확인 부탁드립니다." << endl;
                pw.clear();
            }
        }

        cout << " 이 름 : ";
        cin >> name;
        cout << " 전 화 번 호 : ";
        cin >> phone;
        while (true)
        {
            cout << "생 년 월 일 : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << " ▶ 생년월일은 8자리로 입력해주세요." << endl;
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
        cout << " 회원이 되신걸 축하드립니다!! :D" << endl;
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
            cout << "▶ 이 름 : " << result->getString("name") << endl;
            if (result -> getString("status") == "")
            {
                cout << " ▶ 상태메세지 : 없음" << endl;
            }
            else {
                cout << " ▶ 상태메세지 : " << result->getString("status") << endl;
            }

            if (result->getString("song") == "") {
                cout << " ▶ 노 래 : 없음" << endl;
            }
            else {
                cout << " ▶ 노 래 : " << result->getString("song") << endl;
            }
            cout << " ▶ 생 일 : " << result->getString("birth") << endl;
            cout << " ▶ 휴대폰 번호 : " << result->getString("phone") << endl;
            cout << "************************************************" << endl;
        }
    }

    void updateStatus() {
        cout << " ▶ 상태메세지 입 력 : ";
        cin.ignore(); // 표준입력 버퍼에 남은 개행문자 삭제, getline 함수 앞에 사용
        getline(cin, status);
        pstmt = con->prepareStatement("UPDATE user SET status = ? WHERE id = ?");
        pstmt->setString(1, status);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        cout << " ▶ 업데이트 되었습니다." << endl;
    }

    void updateSong() {
        cout << " 노 래 입 력 : ";
        cin.ignore();
        getline(cin, song);
        pstmt = con->prepareStatement("UPDATE user SET song=? WHERE id=?");
        pstmt->setString(1, song);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        cout << " ▶ 업데이트 되었습니다." << endl;
    }

    void friends() {
        pstmt = con->prepareStatement("SELECT name, status, song, birth, phone FROM user WHERE id != ?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result -> next())
        {
            cout << "************************************************" << endl;
            cout << " ▶ 이 름 : " << result->getString("name") << endl;
            if (result->getString("status") == "") {
                cout << " ▶ 상태메세지 : 없음" << endl;
            }
            else {
                cout << " ▶ 상태메세지 : " << result->getString("status") << endl;
            }

            if (result->getString("song") == "") {
                cout << " ▶ 노래 : 없음" << endl;
            }
            else {
                cout << " ▶ 노래 : " << result->getString("song") << endl;
            }

            cout << " ▶ 생 년 월 일 : " << result->getString("birth") << endl;
            cout << " ▶ 휴 대 폰 번 호 : " << result->getString("phone") << endl;
        }
    }

    void searchBirth() {
        string startDay;
        string endDay;
        cout << " 시작 || 월일 4자리로 입력해주세요. ex) 0101, 0315 ";
        cin >> startDay;
        cout << " 끝 || 월일 4자리로 입력해주세요. ex) 0101,0315 ";
        cin >> endDay;
        pstmt = con->prepareStatement("SELECT name, birth, phone FROM user WHERE DATE_FORMAT(birth, '%m%d') BETWEEN ? AND ? AND id != ?;");
        pstmt->setString(1, startDay);
        pstmt->setString(2, endDay);
        pstmt->setString(3, id);
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " 검색결과가 없습니다." << endl;
        }
        else {
            while (true)
            {
                cout << "************************************************" << endl;
                cout << " ▶ 이 름 :" << result->getString("name") << endl;
                cout << " ▶ 생 년 월 일 : " << result->getString("birth") << endl;
                cout << " ▶ 휴 대 폰 번 호 : " << result->getString("phone") << endl;
                if (!result->next()) break; // 더 이상 결과가 없으면 반복문 종료
            }
        }

    }

    void search_content_msg() {
        string content;
        cout << " 내용으로 대화 검색 : " << endl;
        cin >> content;
        pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting WHERE recv LIKE ?");
        pstmt->setString(1, "%" + content + "%");
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " 검색결과가 없습니다.." << endl;
        }
        else {
            while (true)
            {
                string chatname = result->getString(1);
                string time = result->getString(2);
                string recv = result->getString(3);
                cout << "************************************************" << endl;
                cout << " ▶ 보낸 사람 : " << chatname << " || 보낸 시간 : " << time << endl;
                cout << " ▶ 내 용 : " << recv << endl;
                if (!result->next()) break;
            }
        }
    }

    void search_day_msg() {
        string startDay;
        string endDay;
        cout << " 시작 || 월일 4자리로 입력해주세요. ex) 0101, 0315 ";
        cin >> startDay;
        cout << " 끝 || 월일 4자리로 입력해주세요. ex) 0101,0315 ";
        cin >> endDay;
        
        string startMonthDay = "2023" + startDay;
        string endMonthDay = "2023" + endDay;

        pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting WHERE time BETWEEN ? AND ?");
        pstmt->setString(1, startMonthDay);
        pstmt->setString(2, endMonthDay);
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << " 검색결과가 없습니다." << endl;
        }
        else {
            while (true)
            {
                string chatname = result->getString(1);
                string time = result->getString(2);
                string recv = result->getString(3);
                cout << "************************************************" << endl;
                cout << " ▶ 보낸 사람 : " << chatname << " || 보낸 시간 : " << time << endl;
                cout << " ▶ 내 용 : " << recv << endl;
                if (!result->next()) break;
            }
        }
    }

    void modifyPW() {
        cout << " 기존 비밀번호를 입력하세요 : ";
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
                cout << " 새로운 비밀번호를 입력해주세요 : ";
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
                cout << endl << " 다시 한번 입력해주세요 : ";
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
                    cout << " ▶ 비밀번호가 변경되었습니다." << endl;
                    break;
                }
                else {
                    cout << " ▶ 비밀번호가 다릅니다." << endl;
                }
            }
        }
        else {
            cout << " ▶ 비밀번호가 다릅니다." << endl;
        }
    }

    int deleteUser() {
        string exist_pw = "";
        char ch = ' ';
        cout << " 비밀번호를 입력해주세요 : ";
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
            string db_pw = result->getString(1); // DB 에 있는 pw
            if (db_pw == exist_pw) {
                cout << " 정말 삭제하시겠습니까? 1.예 2.아니요"; 
                char check;
                cin >> check;
                if (check == '1') {
                    pstmt = con->prepareStatement("DELETE FROM user WHERE id=?");
                    pstmt->setString(1, id);
                    result = pstmt->executeQuery();
                    cout << " 삭제되었습니다. 감사합니다." << endl;
                    return 1;
                }
                else if (check == '2') {
                    cout << "탁월한 선택이십니다.!" << endl;
                    return 2;
                }
                else {
                    cout << "다시 입력해주세요." << endl;
                }
            }
            else {
                cout << " 비밀번호가 다릅니다. 다시 한번 확인해주세요." << endl;
            }
        }
        else {
            cout << " 비밀번호가 다릅니다. 다시 한번 확인해주세요." << endl;
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
            msg[i] += "\n▶ 보낸 사람 : " + chatname[i] + "|| 보낸 시간 :  " + time[i] + "\n";
            msg[i] += "▶ 내 용 : " + recv[i] + "\n";
            msg[i] += "************************************************";
            cout << msg[i] << endl;
       
        }
    }
};

int main() {
    SQL sql;
    bool loginSuccess = false;

    // 시작화면
    while (!loginSuccess)
    {
        beginning(); // 시작화면
        char start = 0;
        cout << " ▶";
        cin >> start;
        switch (start)
        {
            case '1': // 로그인
                log_in();
                if (sql.login() == 1) {
                    loginSuccess = true;
                    break;
                }
                continue;

            case '2': // ID 찾기
                search_ID();
                sql.searchID();
                continue;

            case '3': // PW 찾기
                search_PW();
                sql.searchPW();
                continue;
            
            case '4': // 회원가입
                sign_up();
                sql.createUser();
                continue;

            case '0' : // 종료
                return -1;

            default: // 0 ~ 4 외에 다른번호 입력시
                cout << " 잘못된 입력입니다. 다시 입력해주세요." << endl;
                continue;
        }
    }

    // 메인화면 구현
    while (true)
    {
        mainMenu();
        int mainIn = 0;
        cout << "▶ ";
        cin >> mainIn;

        // 내 정보
        if (mainIn == 1) {
            myMenu();
            bool backButton = false;
            while (!backButton) {
                char information = 0;
                cout << "▶ ";
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
                        cout << "잘못된 입력입니다 다시 입력해주세요." << endl;
                        continue;
                }
            }
        }
        else  if (mainIn == 2) {    // 친구목록
            friends();
            bool backButton = false;
            while (!backButton)
            {
                char friendsIn = 0;
                cout << "▶ ";
                cin >> friendsIn;
                switch (friendsIn)
                {
                    case '1' :
                        sql.friends(); // 친구목록
                        continue;

                    case '2' :
                        sql.searchBirth(); // 생일검색
                        continue;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << " 잘못된 입력입니다. 다시 입력해주세요." << endl;
                        continue;
                }
            }
        }
        else if (mainIn == 3) { // 채팅방
            chatting(); // 친구화면
            bool backButton = false;
            int code = 0;
            while (!backButton)
            {
                char chattingIn = 0;
                cout << "▶ ";
                cin >> chattingIn;
                switch (chattingIn)
                {
                    case '1':
                        sql.beforeChat();
                        WSADATA wsa;
                        code = WSAStartup(MAKEWORD(2, 2), &wsa);    
                        if (!code) {
                            cout << " [ 채팅방에 입장합니다. ]" << endl;
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
                                    cout << " ※주의※ 지인을 사칭하여 금전을 요구할 수 있으니 의심 된다면 대화를 중단해주시길 바랍니다." << endl;
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
                                const char* buffer = text.c_str(); // string -> char *타입으로 변환
                                send(client_sock, buffer, strlen(buffer), 0);
                                if (text == "/종료") {
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
                        cout << " 잘못된 입력입니다. 다시 입력해주세요." << endl;
                        continue;
                }
            }
            
            }
        else if (mainIn == 4) { // 설정
            setting();
            bool backButton = false;
            while (!backButton)
            {
                char settinIn = 0;
                cout << "▶ ";
                cin >> settingIn;
                switch (settingIn)
                {
                    case '1':   
                        sql.modifyPW(); // 비밀번호 변경
                        continue;

                    case '2':
                        if (sql.deleteUser() == 1) return -1;
                        else backButton = true;

                    case '0':
                        backButton = true;
                        break;

                    default:
                        cout << " 잘못된 입력입니다. 다시 입력해주세요. " << endl;
                }
            }
            }
        else if (mainIn == 0) { // 종료
                cout << "프로그램을 종료합니다. Bye Bye~" << endl;
                return 0;
        }

        else {
            cout << " 잘못된 입력입니다. 다시 입력해주세요. " << endl;
        }

    }

    delete result;
    delete pstmt;
    delete stmt;
    delete con;
}