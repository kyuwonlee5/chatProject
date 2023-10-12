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

int msg_rect() {
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

    }

};