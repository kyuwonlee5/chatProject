#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <sstream>
#include <mysql/jdbc.h>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::string;
using std::vector;

#define MAX_SIZE 1024 // �������
#define MAX_CLIENT 3 // �� �ο� 3������ ����

const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "root"; // �����ͺ��̽� �����
const string password = "1234"; // �����ͺ��̽� ���� ��й�ȣ

struct SOCKET_INFO { // ����� ���� ������ ���� Ʋ ����
    SOCKET sck = 0;
    string user = "";
};

vector<SOCKET_INFO> sck_list; // ����� Ŭ���̾�Ʈ ���ϵ��� ������ �迭 ����.
SOCKET_INFO server_sock; // ���� ���Ͽ� ���� ������ ������ ���� ����.
int client_count = 0; // ���� ������ �ִ� Ŭ���̾�Ʈ�� count �� ���� ����.

//SQL
sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ �� 
sql::Connection* con;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;
sql::Statement* stmt;
void startSql(); //SQL���� - creatTable;

// �ý��� ����
void mainMenu();

//ä��
void server_init(); //������ ������ ����� �Լ�
void add_client(); //accept �Լ� ����ǰ� ���� ����
void send_msg(const char* msg); //send() ����
void send_msg_notMe(const char* msg, int sender_idx);
void sendWhisper(int position, string sbuf, int idx); // DM ���
void recv_msg(int idx); //recv() ����
void del_client(int idx); //Ŭ���̾�Ʈ���� ������ ���� ��
void print_clients();

int main() {

}

void mainMenu() {
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
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                 < SERVER ON >                 *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*                                               *\n";
    cout << " "; cout << "*************************************************\n\n";
}

void startSql()
{
    // MySQL Connector/C++ �ʱ�ȭ

    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        exit(1);
    }

    // �����ͺ��̽� ����                                                                
    con->setSchema("chat");

    // DB �ѱ� ������ ���� ����                                                             
    stmt = con->createStatement();
    stmt->execute("set names euckr");
    if (stmt) { delete stmt; stmt = nullptr; }
}

// ������ ����  �Լ�
void server_init() {
    server_sock.sck = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(7777); //123.0.0.1:7777 �߿� ------:7777�� ����
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //123.0.0.1:----�� �����Ѵ�.

    bind(server_sock.sck, (sockaddr*)&server_addr, sizeof(server_addr));

    listen(server_sock.sck, SOMAXCONN);

    server_sock.user = "server";
}

void add_client() {
    SOCKADDR_IN addr = {};
    int addrsize = sizeof(addr);
    char buf[MAX_SIZE] = { };

    ZeroMemory(&addr, addrsize);

    SOCKET_INFO new_client = {};

    new_client.sck = accept(server_sock.sck, (sockaddr*)&addr, &addrsize);
    recv(new_client.sck, buf, MAX_SIZE, 0);
    new_client.user = string(buf);

    string msg = "��" + new_client.user + " ���� �����߽��ϴ�.";
    cout << msg << endl;
    sck_list.push_back(new_client);
    print_clients();

    std::thread th(recv_msg, client_count);
    th.detach();
    client_count++;

    cout << "������ ������ �� : " << client_count << "��" << endl;
    send_msg(msg.c_str());
}

void send_msg(const char* msg)
{
    for (int i = 0; i < client_count; i++)
    {
        send(sck_list[i].sck, msg, MAX_SIZE, 0);
    }
}

void send_msg_notMe(const char* msg, int sender_idx)
{
    for (int i = 0; i < client_count; i++) {
        if (i != sender_idx) {
            send(sck_list[i].sck, msg, MAX_SIZE, 0);
        }
    }
}

void sendWhisper(int position, string sbuf, int idx)
{
    int cur_position = position + 1;
    position = sbuf.find(" ", cur_position);
    int len = position - cur_position;
    string receiver = sbuf.substr(cur_position, len);
    cur_position = position + 1;
    string dm = sbuf.substr(cur_position);
    string msg = "�رӼӸ� ���� [" + sck_list[idx].user + "] : " + dm;
    for (int i = 0; i < client_count; i++)
    {
        if (receiver.compare(sck_list[i].user) == 0)
            send(sck_list[i].sck, msg.c_str(), MAX_SIZE, 0);
    }
}

void recv_msg(int idx) {
    char buf[MAX_SIZE] = { };
    string msg = "";

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);

        if (recv(sck_list[idx].sck, buf, MAX_SIZE, 0) > 0) {  // ������ �߻����� ������ recv�� ���ŵ� ����Ʈ ���� ��ȯ. 0���� ũ�ٴ� ���� �޽����� �Դٴ� ��.
            string whisper(buf);
            int position = whisper.find(" ", 0);
            int message = position - 0;
            string flag = whisper.substr(0, message);
            if (string(buf) == "/����")
            {
                msg = "��" + sck_list[idx].user + " ���� �����߽��ϴ�.";
                cout << msg << endl;
                send_msg(msg.c_str());
                del_client(idx);
                return;
            }
            else if (flag.compare("/�Ӹ�") == 0)
            {
                sendWhisper(position, whisper, idx);
            }
            else {

                pstmt = con->prepareStatement("INSERT INTO chatting(chatname, time, recv) VALUE(?, NOW(),  ?)");
                pstmt->setString(1, sck_list[idx].user);
                pstmt->setString(2, whisper);
                pstmt->execute();

                pstmt = con->prepareStatement("SELECT chatname, time, recv FROM chatting ORDER BY time DESC LIMIT 1");
                result = pstmt->executeQuery();
                if (result->next())
                {
                    string chatname = result->getString(1);
                    string time = result->getString(2);
                    string recv = result->getString(3);
                    msg += "--------------------------------------------------";
                    msg += "\n���������: " + chatname + "  " + "�������ð�: " + time + "\n";
                    msg += "������ : " + recv + "\n";
                    msg += "--------------------------------------------------\n";
                    cout << msg << endl;
                    send_msg_notMe(msg.c_str(), idx);
                }
            }
        }
        else { //�׷��� ���� ��� ���忡 ���� ��ȣ�� �����Ͽ� ���� �޽��� ����
            msg = "[����] " + sck_list[idx].user + " ���� �����߽��ϴ�.";
            cout << msg << endl;
            send_msg(msg.c_str());
            del_client(idx); // Ŭ���̾�Ʈ ����
            return;
        }
    }
}

void del_client(int idx) {
    std::thread th(add_client);
    closesocket(sck_list[idx].sck);
    client_count--;
    cout << "������ ������ �� : " << client_count << "��" << endl;
    sck_list.erase(sck_list.begin() + idx);
    th.join();
}



void print_clients() {
    cout << "������ ���� : ";
    for (auto& client : sck_list) {
        cout << client.user << " ";
    }
    cout << endl;
}
